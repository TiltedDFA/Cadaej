#ifndef UTIL_HPP
#define UTIL_HPP

#include <bit>
#include <cassert>
#include <concepts>
#include "Tests.hpp"
#include "Types.hpp"


namespace Util
{
    template<u8 val>
    consteval u64 GenMask() 
    {
        static_assert(val != 0 && val < 64, "Attempted to generate invalid bitmask");
        return (1 << val) - 1;
    }

    template<u8 val, typename T>
    constexpr T LShift(T num)
    {
        static_assert(val < (sizeof(T) * 8), "Attempted to Lshift with too large val");
        return (num << val);
    }

    template<u8 val, typename T>
    constexpr T RShift(T num)
    {
        static_assert(val < (sizeof(T) * 8), "Attempted to Rshift with too large val");
        return (num >> val);
    }

    template<class T>
    requires std::same_as<T, Piece> //disables implicit casts / enforces Piece type parameter
    constexpr PieceType TypeOf(T p) 
    {
        return PieceType(u8(p) & u8(GenMask<3>()));
    }

    template<class T>
    requires std::same_as<T, Piece> //disables implicit casts / enforces Piece type parameter
    constexpr Colour ColourOf(T p) 
    {
        assert(p != Piece::None);
        return Colour(u8(p) & LShift<3>(GenMask<1>()));
    }

    constexpr BitBoard SqToBB(Square sq)
    {
        assert(Tests::IsOkSq(sq));
        return 1 << u8(sq);
    }

    constexpr int PopCount(BitBoard b)
    {
        return std::popcount<BitBoard>(b);
    }
}






#endif // #ifndef UTIL_HPP
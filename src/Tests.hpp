#ifndef TESTS_HPP
#define TESTS_HPP

#include <cassert>
#include "Types.hpp"

namespace Tests
{
    constexpr bool IsOkPromotion(PieceType p)
    {
        using enum PieceType;
        switch (p)
        {
        case None:
        case Queen:
        case Bishop:
        case Rook:
        case Knight: return true;
        default:break;
        }
        return false;
    }
    constexpr bool IsOkSq(Square s) {using enum Square; return s >= A1 && s <= H8;}
}
#endif // #ifndef TESTS_HPP
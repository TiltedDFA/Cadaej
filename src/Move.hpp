#ifndef MOVE_HPP
#define MOVE_HPP

#include "Tests.hpp"
#include "Types.hpp"
#include "Util.hpp"
/*
    6 bits - from                   (f)
    6 bits - to                     (t)
    3 bits - promotion piece type   (p) 
    2 bits - move type              (m)
    00000000 0000000m mppptttt ttffffff 
*/
enum class MoveType : u32
{
    Regular,
    Promotion   = 1 << 15,
    EnPassant   = 2 << 15,
    Castling    = 3 << 15
};
class Move
{
public:
    constexpr Move() = default;

    constexpr Move(Square from, Square to):
        data_(u32(u8(from) | Util::LShift<6>(u8(to)))){}

    template<MoveType Val = MoveType::Regular>
    static constexpr Move Encode(Square from, Square to, PieceType pt = PieceType::None)
    {
        using namespace Util;
        assert(Tests::IsOkPromotion(pt));
        return Move(u32(Val) | LShift<12>(u32(pt)) | LShift<6>(u32(to)) | u32(from));
    }
    constexpr Square From() const
    {
        using namespace Util;
        return Square(data_ & GenMask<6>());
    }
    constexpr Square To() const
    {
        using namespace Util;
        return Square(RShift<6>(data_) & GenMask<6>());
    }
    constexpr MoveType Type() const
    {
        using namespace Util;
        return MoveType(data_ & u32(LShift<15>(GenMask<2>())));
    }
    constexpr PieceType PromType() const
    {
        using namespace Util;
        return PieceType(RShift<12>(data_) & u32(GenMask<3>()));
    }
    constexpr explicit operator bool() const {return data_ != 0;}
private:
    u32 data_;
};
#endif // #ifndef MOVE_HPP
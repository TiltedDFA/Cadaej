#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>

#define DBG_MODE 1

#if DBG_MODE == 1
#define NEXCEPT 
#else
#define NDEBUG
#define NEXCEPT noexcept
#endif 

using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8  = uint8_t;

using i64 = int64_t;
using i32 = int32_t;
using i16 = int16_t;
using i8  = int8_t;

using BitBoard = u64;
using Sq = u8;

enum class Colour : u8
{
    White,
    Black,
    Len = 2
};
enum class CastlingRights : u8
{
    None,
    WhiteKing,
    WhiteQueen = WhiteKing << 1,
    BlackKing  = WhiteKing << 2,
    BlackQueen = WhiteKing << 3,

    FullWhite = WhiteKing | WhiteQueen,
    FullBlack = BlackKing | BlackQueen
};
enum class PieceType : u8
{
    None,
    Queen,
    Bishop,
    Knight,
    Rook,
    Pawn,
    King,
    All,
    Len = 8
};
enum class Piece : u8
{
    None,
    WhiteQueen = u8(PieceType::Queen),
    WhiteBishop,
    WhiteKnight,
    WhiteRook,
    WhitePawn,
    WhiteKing,
    BlackQueen = u8(PieceType::Queen) + 8,
    BlackBishop,
    BlackKnight,
    BlackRook,
    BlackPawn,
    BlackKing,
};
enum class Square : u8
{
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
    Null,

    Len = 64
};
constexpr Colour operator~(Colour c) {using enum Colour; return Colour(u8(c) ^ u8(Black));}
#endif // #ifndef TYPES_HPP
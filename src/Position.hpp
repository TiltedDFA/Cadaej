#ifndef POSITION_HPP
#define POSITION_HPP

#include <algorithm>
#include <array>
#include "Types.hpp"
#include "Util.hpp"

class Board
{
public:
    constexpr Board() NEXCEPT
    {
        std::fill(std::begin(board_),     std::end(board_),     Piece::None);
        std::fill(std::begin(by_colour_), std::end(by_colour_), 0ull);
        std::fill(std::begin(by_type_),   std::end(by_type_),   0ull);
    }
    Board(const Board&)=delete;
    Board(const Board&&)=delete;
    Board& operator=(const Board&)=delete;
    Board& operator=(const Board&&)=delete;

    constexpr BitBoard Pieces(PieceType pt) const NEXCEPT
    {
        return by_type_[u64(pt)];
    }
    constexpr BitBoard Pieces(Colour c) const NEXCEPT
    {
        return by_colour_[u64(c)];
    }
    template<typename... PieceTypes>
    constexpr BitBoard Pieces(PieceType p, PieceTypes... pt) const NEXCEPT
    {
        return Pieces(p) | Pieces(pt...);
    }
    template<typename... PieceTypes>
    constexpr BitBoard Pieces(Colour c, PieceTypes... p) const NEXCEPT
    {
        return Pieces(c) & Pieces(p...);
    }
    constexpr Piece PieceOn(Square s) const NEXCEPT
    {
        assert(Tests::IsOkSq(s));
        return board_[u64(s)];
    }
    constexpr void AddPiece(Piece p, Square s) NEXCEPT
    {
        using namespace Util;

        board_[u64(s)] = p;

        by_type_[u64(TypeOf(p))]      |= SqToBB(s);
        by_type_[u64(PieceType::All)] |= SqToBB(s);
        by_colour_[u64(ColourOf(p))]  |= SqToBB(s);
    }
    constexpr void RemovePiece(Square s) NEXCEPT
    {
        using namespace Util;

        const Piece p = board_[u64(s)];

        by_type_[u64(PieceType::All)]   &= ~SqToBB(s);
        by_type_[u64(TypeOf(p))]        &= ~SqToBB(s);
        by_colour_[u64(ColourOf(p))]    &= ~SqToBB(s);

        board_[u64(s)] = Piece::None;
    }
    constexpr void MovePiece(Square from, Square to) NEXCEPT
    {
        using namespace Util;
        assert((board_[u64(from)] != Piece::None));

        const Piece p = board_[u64(from)];
        const BitBoard move = SqToBB(from) | SqToBB(to);
        
        by_type_[u64(PieceType::All)]   ^= move;
        by_type_[u64(TypeOf(p))]        ^= move;
        by_colour_[u64(ColourOf(p))]    ^= move;

        board_[u64(from)]   = Piece::None;
        board_[u64(to)]     = p;

    }
private:
    Piece    board_[u64(Square::Len)];
    BitBoard by_colour_[u64(Colour::Len)];
    BitBoard by_type_  [u64(PieceType::Len)];
};

class Position
{
public:

private:
    Board board_;
    
};


#endif // #ifndef POSITION_HPP
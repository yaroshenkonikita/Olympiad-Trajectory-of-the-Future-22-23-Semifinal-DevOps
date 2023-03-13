#ifndef OLYMPIAD_TRAJECTORY_OF_THE_FUTURE_22_23_SEMIFINAL_DEVOPS_PIECE_H_
#define OLYMPIAD_TRAJECTORY_OF_THE_FUTURE_22_23_SEMIFINAL_DEVOPS_PIECE_H_

#include <utility>
#include <cstdint>

class Piece {
public:
    typedef enum ChessPiece {
        VOID = 0,
        PAWN = 3,
        ROOK = 5,
        BISHOP = 7,
        KNIGHT = 11,
        QUEEN = 13,
        KING = 17
    } PieceFigure;
    typedef enum ChessColor {
        NONE = 0,
        WHITE = 1,
        BLACK = 2
    } PieceColor;
    Piece() noexcept = default;
    Piece(PieceFigure figure, PieceColor color) noexcept;

    ~Piece() = default;

    uint8_t operator*() noexcept;

    Piece& operator=(Piece &other) noexcept;
    Piece& operator=(Piece &&other) noexcept;
    Piece& operator=(std::pair<PieceFigure, PieceColor> &pair) noexcept;

    PieceFigure GetPiece() const noexcept;

    PieceColor GetColor() const noexcept;

private:
    PieceFigure _piece{};
    PieceColor _color{};
};


#endif //OLYMPIAD_TRAJECTORY_OF_THE_FUTURE_22_23_SEMIFINAL_DEVOPS_PIECE_H_

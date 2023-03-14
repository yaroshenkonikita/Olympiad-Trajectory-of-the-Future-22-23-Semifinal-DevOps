
#include "Piece.h"

Piece::Piece(PieceFigure figure, PieceColor color) noexcept {
    _piece = figure;
    _color = color;
}

uint8_t Piece::operator*() noexcept {
    return _piece * _color;
}

Piece &Piece::operator=(Piece &other) noexcept {
    _piece = other._piece;
    _color = other._color;
    return *this;
}

Piece &Piece::operator=(Piece &&other) noexcept {
    _piece = std::exchange(other._piece, PieceFigure::VOID);
    _color = std::exchange(other._color, PieceColor::NONE);
    return *this;
}

Piece &Piece::operator=(std::pair<Piece::ChessPiece, Piece::PieceColor> &pair) noexcept {
    _piece = pair.first;
    _color = pair.second;
    return *this;
}


Piece::PieceFigure Piece::GetPiece() const noexcept {
    return _piece;
}

Piece::PieceColor Piece::GetColor() const noexcept {
    return _color;
}
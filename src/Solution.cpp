#include "Chess.h"

std::pair<uint8_t, uint8_t> Chess::FindWhiteKing() {
    for (int xAxis{}; xAxis < 8; xAxis++) {
        for (int yAxis{}; yAxis < 8; yAxis++) {
            Piece &current = ChessField[xAxis][yAxis];
            if (current.GetPiece() == Piece::PieceFigure::KING &&
                current.GetColor() == Piece::PieceColor::WHITE) {
                return {xAxis, yAxis};
            }
        }
    }
    throw std::logic_error("No white king on the field");
}

Chess::SolutionCheck Chess::Solution() {
    std::pair<uint8_t, uint8_t> PositionKing = FindWhiteKing();
    int res = IsUnderAttack(PositionKing.first, PositionKing.second);
    if (res == Piece::PieceFigure::BISHOP) {
        return CheckFromBishop;
    } else if (res == Piece::PieceFigure::ROOK) {
        return CheckFromRook;
    }
    return NoCheck;
}

std::ostream &operator<<(std::ostream &os, const Chess &field) {
    for (auto &field_row : field.ChessField) {
        os << '|';
        for (auto &piece : field_row) {
            char res = piece.GetPiece();
            if (res == Piece::VOID) {
                res = ' ';
            } else if (res == Piece::PAWN) {
                res = 'P';
            } else if (res == Piece::ROOK) {
                res = 'R';
            } else if (res == Piece::BISHOP) {
                res = 'B';
            } else if (res == Piece::KNIGHT) {
                res = 'N';
            } else if (res == Piece::QUEEN) {
                res = 'Q';
            } else if (res == Piece::KING) {
                res = 'K';
            }
            if (piece.GetColor() == Piece::BLACK) {
                res += 32;
            }
            os << res << '|';
        }
        os << std::endl;
    }
    return os;
}

#include "Chess.h"

Chess::Chess() {
    for (int AxisNumber{}; AxisNumber < 8; AxisNumber++) {
        if (AxisNumber == 2) AxisNumber += 4;
        for (int AxisMarker{}; AxisMarker < 8; AxisMarker++) {
            Piece::PieceColor color = Piece::NONE;
            if (AxisNumber > 5) {
                color = Piece::BLACK;
            } else if (AxisNumber < 2) {
                color = Piece::WHITE;
            }
            Piece::ChessPiece piece = Piece::VOID;
            if (AxisNumber == 1 || AxisNumber == 6) {
                piece = Piece::PAWN;
            } else if (AxisNumber == 0 || AxisMarker == 7) {
                if (AxisMarker == A || AxisMarker == H) {
                    piece = Piece::ROOK;
                } else if (AxisMarker == B || AxisMarker == G) {
                    piece = Piece::KNIGHT;
                } else if (AxisMarker == C || AxisMarker == F) {
                    piece = Piece::BISHOP;
                } else if (AxisMarker == D) {
                    piece = Piece::QUEEN;
                } else if (AxisMarker == E) {
                    piece = Piece::KING;
                }
            }
            ChessField[AxisNumber][AxisMarker] = Piece(piece, color);
        }
    }
}

Chess::Chess(Piece &piece_for_fill) {
    for (auto &RowPieces : ChessField) {
        for (auto &piece : RowPieces) {
            piece = piece_for_fill;
        }
    }
}

Piece &Chess::GetPiece(uint8_t positionNumber, uint8_t positionMarker) {
    if (positionNumber > 7 || positionMarker > 7) {
        throw std::out_of_range("GetPiece: Out of range: Position piece maybe from 0 to 7");
    }
    return ChessField[positionNumber][positionMarker];
}

int Chess::UnderAttackOnDiagonally(Piece::PieceColor ColorPiece, int xAxisPos, int yAxisPos) {
    int IncrementX = -1, IncrementY = -1;
    for (int i{}; i < 4; i++) {
        unsigned int xAxis = xAxisPos, yAxis = yAxisPos;
        while (true) {
            xAxis += IncrementX;
            yAxis += IncrementY;
            if (xAxis > 7 && yAxis > 7) break;
            std::cout << xAxis << " " << yAxis << std::endl;
            Piece &current(ChessField[xAxis][yAxis]);
            if (!*current) continue;
            if (current.GetPiece() == Piece::BISHOP && current.GetColor() != ColorPiece) {
                return Piece::BISHOP;
            } else if (current.GetPiece() == Piece::QUEEN && current.GetColor() != ColorPiece) {
                return Piece::QUEEN;
            } else if (fabs(xAxis - xAxisPos) == 1) {
                if (current.GetPiece() == Piece::KING && current.GetColor() != ColorPiece) {
                    return Piece::KING;
                } else if (current.GetPiece() == Piece::PAWN && current.GetColor() != ColorPiece) {
                    if (ColorPiece == Piece::PieceColor::WHITE && (yAxis - yAxisPos) == 1) {
                        return Piece::PAWN;
                    } else if (ColorPiece == Piece::PieceColor::BLACK && (yAxisPos - yAxis) == 1) {
                        return Piece::PAWN;
                    }
                }
            }
            break;
        }
        if (IncrementY == 1) {
            IncrementY = -1;
            IncrementX = 1;
        } else {
            IncrementY += 2;
        }
    }
    return 0;
}

int Chess::UnderAttackOnHorizontally(Piece::PieceColor ColorPiece, int xAxisPos, int yAxisPos) {
    int IncrementX = -1, IncrementY{};
    for (int i{}; i < 4; i++) {
        unsigned int xAxis = xAxisPos, yAxis = yAxisPos;
        while (true) {
            xAxis += IncrementX;
            yAxis += IncrementY;
            if (xAxis > 7 && yAxis > 7) break;
            std::cout << xAxis << " " << yAxis << std::endl;
            Piece &current(ChessField[xAxis][yAxis]);
            if (!*current) continue;
            if (current.GetPiece() == Piece::ROOK && current.GetColor() != ColorPiece) {
                return Piece::ROOK;
            } else if (current.GetPiece() == Piece::QUEEN && current.GetColor() != ColorPiece) {
                return Piece::QUEEN;
            } else if (fabs(xAxis - xAxisPos) == 1 || fabs(yAxis - yAxisPos) == 1) {
                if (current.GetPiece() == Piece::KING && current.GetColor() != ColorPiece) {
                    return Piece::KING;
                }
            }
            break;
        }
        if (IncrementY == 1) {
            IncrementY = -1;
            IncrementX = 0;
        } else {
            ++IncrementX;
            ++IncrementY;
        }
    }
    return 0;
}

int Chess::IsUnderAttack(uint8_t positionNumber, uint8_t positionMarker) {
    int res{};
    Piece &target = GetPiece(positionNumber, positionMarker);
    if (!*target) {
        return res;
    }
    res = UnderAttackOnDiagonally(target.GetColor(), positionNumber, positionMarker);
    if (res) {
        return res;
    }
    return UnderAttackOnHorizontally(target.GetColor(), positionNumber, positionMarker);
}

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

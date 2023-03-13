
#include "Chess.h"

Chess::Chess() {
    for (int AxisNumber{}; AxisNumber < 8; AxisNumber++) {
        if (AxisNumber == 2) AxisNumber += 4;
        for (int AxisMarker{}; AxisMarker < 8; AxisMarker++) {
            Piece::ChessColor color = Piece::NONE;
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
    for (auto &AxisNumber : ChessField) {
        for (auto &AxisMarker : AxisNumber) {
            AxisMarker = piece_for_fill;
        }
    }
}

Piece &Chess::GetPiece(ChessPosition positionMarker, uint8_t positionNumber) {
    if (positionNumber > 8 || !positionNumber) {
        throw std::out_of_range("GetPiece: Out of range: Position number maybe from 1 to 8");
    }
    return ChessField[positionNumber - 1][positionMarker];
}

int Chess::UnderAttackOnDiagonally(Piece::ChessColor ColorPiece, int xAxisPos, int yAxisPos) {
    int IncrementX = -1, IncrementY = -1;
    for (int i{}; i < 4; i++) {
        unsigned int xAxis = xAxisPos, yAxis = yAxisPos;
        while (xAxis < 8 && yAxis < 8) {
            xAxis += IncrementX;
            yAxis += IncrementY;
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
                    if (ColorPiece == Piece::ChessColor::WHITE && (yAxis - yAxisPos) == 1) {
                        return Piece::PAWN;
                    } else if (ColorPiece == Piece::ChessColor::BLACK && (yAxisPos - yAxis) == 1) {
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

int Chess::UnderAttackOnHorizontally(Piece::ChessColor ColorPiece, int xAxisPos, int yAxisPos) {
    int IncrementX = -1, IncrementY{};
    for (int i{}; i < 4; i++) {
        unsigned int xAxis = xAxisPos, yAxis = yAxisPos;
        while (xAxis < 8 && yAxis < 8) {
            xAxis += IncrementX;
            yAxis += IncrementY;
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

int Chess::IsUnderAttack(ChessPosition positionMarker, uint8_t positionNumber) {
    int res{};
    Piece &target = GetPiece(positionMarker, positionNumber--);
    if (!*target) {
        return res;
    }
    res = UnderAttackOnDiagonally(target.GetColor(), positionNumber, positionMarker);
    if (res) {
        return res;
    }
    return UnderAttackOnHorizontally(target.GetColor(), positionNumber, positionMarker);
}

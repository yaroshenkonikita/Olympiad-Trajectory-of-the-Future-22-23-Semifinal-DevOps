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

Chess::Chess(Piece piece_for_fill) {
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

int Chess::IsCheckOnDiagonally(int ColorKing, int xAxisPos, int yAxisPos) {
    int IncrementX = -1, IncrementY = -1;
    for (int i{}; i < 4; i++) {
        unsigned int xAxis = xAxisPos, yAxis = yAxisPos;
        while (xAxis < 8 && yAxis < 8) {
            xAxis += IncrementX;
            yAxis += IncrementY;
            Piece &current(ChessField[xAxis][yAxis]);
            if (!*current) continue;
            if (*current % Piece::BISHOP == 0 && *current / Piece::BISHOP != ColorKing) {
                return 7;
            } else if (*current % Piece::QUEEN == 0 && *current / Piece::QUEEN != ColorKing) {
                return 13;
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

int Chess::IsCheckOnHorizontally(int ColorKing, int xAxisPos, int yAxisPos) {
    int IncrementX = -1, IncrementY{};
    for (int i{}; i < 4; i++) {
        unsigned int xAxis = xAxisPos, yAxis = yAxisPos;
        while (xAxis < 8 && yAxis < 8) {
            xAxis += IncrementX;
            yAxis += IncrementY;
            Piece &current(ChessField[xAxis][yAxis]);
            if (!*current) continue;
            if (*current % Piece::ROOK == 0 && *current / Piece::ROOK != ColorKing) {
                return 5;
            } else if (*current % Piece::QUEEN == 0 && *current / Piece::QUEEN != ColorKing) {
                return 13;
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

int Chess::IsCheck(ChessPosition positionMarker, uint8_t positionNumber) {
    int res{};
    Piece &target = GetPiece(positionMarker, positionNumber--);
    if (*target % Piece::KING != 0 || !*target) {
        return res;
    }
    int ColorKing = *target / Piece::KING;
    if (res = IsCheckOnDiagonally(ColorKing, positionNumber, positionMarker)) {
        return res;
    }
    if (res = IsCheckOnHorizontally(ColorKing, positionNumber, positionMarker)) {
        return res;
    }
}

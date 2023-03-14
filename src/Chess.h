#ifndef OLYMPIAD_TRAJECTORY_OF_THE_FUTURE_22_23_SEMIFINAL_DEVOPS_CHESS_H_
#define OLYMPIAD_TRAJECTORY_OF_THE_FUTURE_22_23_SEMIFINAL_DEVOPS_CHESS_H_

#include "Piece.h"
#include <cmath>

class Chess {
public:
    static constexpr uint8_t ChessFieldSize = 8;
    enum ChessFieldMarker { A, B, C, D, E, F, G, H };

    Chess();
    Chess(Piece &piece_for_fill);
    ~Chess() = default;

    Piece &GetPiece(uint8_t positionNumber, uint8_t positionMarker);
    int UnderAttackOnDiagonally(Piece::PieceColor ColorKing, int xAxisPos, int yAxisPos);
    int UnderAttackOnHorizontally(Piece::PieceColor ColorKing, int xAxisPos, int yAxisPos);
    int IsUnderAttack(uint8_t positionMarker, uint8_t positionNumber);

    typedef enum CheckWhiteKing { NoCheck, CheckFromBishop, CheckFromRook } SolutionCheck;
    std::pair<uint8_t, uint8_t> FindWhiteKing();
    SolutionCheck Solution();


private:
    Piece ChessField[ChessFieldSize][ChessFieldSize]{};
};


#endif //OLYMPIAD_TRAJECTORY_OF_THE_FUTURE_22_23_SEMIFINAL_DEVOPS_CHESS_H_

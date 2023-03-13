#ifndef OLYMPIAD_TRAJECTORY_OF_THE_FUTURE_22_23_SEMIFINAL_DEVOPS_CHESS_H_
#define OLYMPIAD_TRAJECTORY_OF_THE_FUTURE_22_23_SEMIFINAL_DEVOPS_CHESS_H_

#include "Piece.h"
#include <cmath>
#include <stdexcept>

class Chess {
public:
    static constexpr uint8_t ChessFieldSize = 8;
    typedef enum ChessFieldMarker { A, B, C, D, E, F, G, H } ChessPosition;

    Chess();
    Chess(Piece &piece_for_fill);
    ~Chess() = default;

    Piece &GetPiece(ChessPosition positionMarker, uint8_t positionNumber);
    int UnderAttackOnDiagonally(Piece::PieceColor ColorKing, int xAxisPos, int yAxisPos);
    int UnderAttackOnHorizontally(Piece::PieceColor ColorKing, int xAxisPos, int yAxisPos);
    int IsUnderAttack(ChessPosition positionMarker, uint8_t positionNumber);

    typedef enum CheckWhiteKing { NoCheck, CheckFromBishop, CheckFromRook } SolutionCheck;
    std::pair<uint8_t, ChessPosition> FindWhiteKing();
    SolutionCheck Solution(uint8_t xAxisPos, ChessPosition yAxisPos);


private:
    Piece ChessField[ChessFieldSize][ChessFieldSize]{};
};


#endif //OLYMPIAD_TRAJECTORY_OF_THE_FUTURE_22_23_SEMIFINAL_DEVOPS_CHESS_H_

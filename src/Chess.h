#ifndef OLYMPIAD_TRAJECTORY_OF_THE_FUTURE_22_23_SEMIFINAL_DEVOPS_CHESS_H_
#define OLYMPIAD_TRAJECTORY_OF_THE_FUTURE_22_23_SEMIFINAL_DEVOPS_CHESS_H_

#include <cmath>

#include "Piece.h"

class Chess {
 public:
  /**
   * @brief Construct a new Chess object
   * @details field is default chess table
   *
   */
  Chess();
  /**
   * @brief Construct a new Chess object with argument
   *
   * @param piece_for_fill all field fill that piece
   */
  Chess(Piece &piece_for_fill);
  /**
   * @brief Destroy the Chess object
   *
   */
  ~Chess() = default;

  /**
   * @brief Get the Piece object from Private field
   *
   * @param positionNumber a number from 0 to 7 that represents the position of
   * the digit
   * @param positionMarker a number from 0 to 7 that represents the position of
   * the letter
   * @return Piece& reference on position in field
   */
  Piece &GetPiece(uint8_t positionNumber, uint8_t positionMarker);
  /**
   * @brief Check all Diagonally and find attack from another piece
   *
   * @param ColorPiece Color of piece
   * @param xAxisPos Position on digit
   * @param yAxisPos Position on letter
   * @return int Who take attack on piece
   */
  int UnderAttackOnDiagonally(Piece::PieceColor ColorPiece, int xAxisPos,
                              int yAxisPos);
  /**
   * @brief Check all Horizontally and find attack from another piece
   *
   * @param ColorPiece Color of piece
   * @param xAxisPos Position on digit
   * @param yAxisPos Position on letter
   * @return int Who take attack on piece
   */
  int UnderAttackOnHorizontally(Piece::PieceColor ColorPiece, int xAxisPos,
                                int yAxisPos);
  /**
   * @brief Find attack from another piece
   *
   * @param positionMarker Position on letter
   * @param positionNumber Position on digit
   * @return int Who take attack on piece
   */
  int IsUnderAttack(uint8_t positionMarker, uint8_t positionNumber);

  /**
   * @brief Enum for Solution
   *
   */
  typedef enum CheckWhiteKing {
    NoCheck,
    CheckFromBishop,
    CheckFromRook
  } SolutionCheck;
  /**
   * @brief Solution function on find white king
   *
   * @return std::pair<uint8_t, uint8_t> position white king on private field
   */
  std::pair<uint8_t, uint8_t> FindWhiteKing();
  /**
   * @brief Solution - Find check for white king from black bishop or knight
   *
   * @return SolutionCheck Result
   */
  SolutionCheck Solution();

 private:
  static constexpr uint8_t ChessFieldSize = 8;
  enum ChessFieldMarker { A, B, C, D, E, F, G, H };

  Piece ChessField[ChessFieldSize][ChessFieldSize]{};
};

#endif  // OLYMPIAD_TRAJECTORY_OF_THE_FUTURE_22_23_SEMIFINAL_DEVOPS_CHESS_H_

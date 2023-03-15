#ifndef OLYMPIAD_TRAJECTORY_OF_THE_FUTURE_22_23_SEMIFINAL_DEVOPS_PIECE_H_
#define OLYMPIAD_TRAJECTORY_OF_THE_FUTURE_22_23_SEMIFINAL_DEVOPS_PIECE_H_

#include <cstdint>
#include <stdexcept>
#include <utility>

/**
 * @brief
 *
 */
class Piece {
 public:
  /**
   * @brief Enum prime numbers so that can determine by division what kind of
   * figure
   *
   */
  typedef enum ChessPiece {
    VOID = 0,
    PAWN = 3,
    ROOK = 5,
    BISHOP = 7,
    KNIGHT = 11,
    QUEEN = 13,
    KING = 17
  } PieceFigure;

  /**
   * @brief Enum color of piece
   *
   */
  typedef enum ChessColor { NONE = 0, WHITE = 1, BLACK = 2 } PieceColor;

  /**
   * @brief Construct a new Piece object
   *
   */
  Piece() noexcept = default;
  /**
   * @brief Construct a new Piece object with arguments
   *
   * @param figure type PieceFigure
   * @param color type PieceColor
   */
  Piece(PieceFigure figure, PieceColor color) noexcept;
  /**
   * @brief Destroy the Piece object
   *
   */
  ~Piece() = default;

  /**
   * @brief Static function to get PieceFigure from int
   *
   * @param x int equivalent PieceFigure
   * @return PieceFigure
   */
  static PieceFigure FromIntToPieceFigure(int x);
  /**
   * @brief Static function to get PieceColor from int
   *
   * @param x int equivalent PieceColor
   * @return PieceColor
   */
  static PieceColor FromIntToPieceColor(int x);

  /**
   * @brief Operator dereferencing
   *
   * @return uint8_t return mul of private fields piece and color
   */
  uint8_t operator*() noexcept;

  Piece &operator=(Piece &other) noexcept;
  Piece &operator=(Piece &&other) noexcept;
  Piece &operator=(std::pair<PieceFigure, PieceColor> &pair) noexcept;
  bool operator==(Piece &other) noexcept;
  bool operator!=(Piece &other) noexcept;

  /**
   * @brief Get the Piece object
   *
   * @return PieceFigure
   */
  PieceFigure GetPiece() const noexcept;
  /**
   * @brief Get the Color object
   *
   * @return PieceColor
   */
  PieceColor GetColor() const noexcept;

 private:
  PieceFigure _piece{};
  PieceColor _color{};
};

#endif  // OLYMPIAD_TRAJECTORY_OF_THE_FUTURE_22_23_SEMIFINAL_DEVOPS_PIECE_H_

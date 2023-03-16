#include <gtest/gtest.h>

#include <iostream>
#include <pqxx/pqxx>

#include "../Chess.h"

TEST(Piece, default_constructor) {
  Piece x;
  EXPECT_EQ(x.GetPiece(), Piece::PieceFigure::VOID);
  EXPECT_EQ(x.GetColor(), Piece::PieceColor ::NONE);
}

TEST(Piece, constructor_with_arguments_and_getter) {
  Piece x(Piece::PieceFigure::KING, Piece::PieceColor::WHITE);
  EXPECT_EQ(x.GetPiece(), Piece::PieceFigure::KING);
  EXPECT_EQ(x.GetColor(), Piece::PieceColor::WHITE);
}

TEST(Piece, operator_mul) {
  Piece x(Piece::PieceFigure::KING, Piece::PieceColor::WHITE);
  EXPECT_EQ(*x, Piece::PieceFigure::KING * Piece::PieceColor::WHITE);
}

TEST(Piece, operators_equals) {
  Piece x(Piece::PieceFigure::KING, Piece::PieceColor::WHITE),
      a(Piece::PieceFigure::KING, Piece::PieceColor::WHITE),
      b(Piece::PieceFigure::KING, Piece::PieceColor::BLACK);
  EXPECT_FALSE(a == b);
  EXPECT_TRUE(a != b);
  EXPECT_TRUE(a == x);
  EXPECT_FALSE(a != x);
}

TEST(Piece, static_functions) {
  EXPECT_EQ(Piece::FromIntToPieceFigure(17), Piece::PieceFigure::KING);
  EXPECT_EQ(Piece::FromIntToPieceFigure(7), Piece::PieceFigure::BISHOP);
  EXPECT_EQ(Piece::FromIntToPieceColor(1), Piece::PieceColor::WHITE);
  EXPECT_EQ(Piece::FromIntToPieceColor(2), Piece::PieceColor::BLACK);
}

TEST(Piece, static_functions_except) {
  EXPECT_ANY_THROW(Piece::FromIntToPieceFigure(0));
  EXPECT_ANY_THROW(Piece::FromIntToPieceColor(0));
}

TEST(Piece, operator_assignments_and_move_and_getter) {
  Piece x1(Piece::PieceFigure::KING, Piece::PieceColor::WHITE),
      x2(Piece::PieceFigure::BISHOP, Piece::PieceColor::BLACK);
  Piece expect;
  expect = x1;
  EXPECT_EQ(17, expect.GetPiece());
  EXPECT_EQ(1, expect.GetColor());
  expect = std::move(x2);
  EXPECT_EQ(7, expect.GetPiece());
  EXPECT_EQ(2, expect.GetColor());
  EXPECT_EQ(0, x2.GetPiece());
  EXPECT_EQ(0, x2.GetColor());
}

TEST(Chess, default_constructor_and_getter) {
  Chess x;
  Piece void_none,
      king_black(Piece::PieceFigure::KING, Piece::PieceColor::BLACK),
      bishop_white(Piece::PieceFigure::BISHOP, Piece::PieceColor::WHITE),
      knight_black(Piece::PieceFigure::KNIGHT, Piece::PieceColor::BLACK),
      king_white(Piece::PieceFigure::KING, Piece::PieceColor::WHITE);
  EXPECT_TRUE(x.GetPiece(0, 4) == king_white);
  EXPECT_TRUE(x.GetPiece(0, 2) == bishop_white);
  EXPECT_TRUE(x.GetPiece(0, 5) == bishop_white);
  EXPECT_TRUE(x.GetPiece(7, 1) == knight_black);
  EXPECT_TRUE(x.GetPiece(7, 6) == knight_black);
  EXPECT_TRUE(x.GetPiece(7, 4) == king_black);
  EXPECT_TRUE(x.GetPiece(3, 4) == void_none);
  EXPECT_TRUE(x.GetPiece(5, 2) == void_none);
  EXPECT_TRUE(x.GetPiece(4, 7) == void_none);
}

TEST(Chess, constructor_for_fill_and_getter) {
  Piece void_none,
      king_black(Piece::PieceFigure::KING, Piece::PieceColor::BLACK);
  Chess expect1(void_none), expect2(king_black);
  EXPECT_TRUE(expect2.GetPiece(1, 4) == king_black);
  EXPECT_TRUE(expect2.GetPiece(1, 2) == king_black);
  EXPECT_TRUE(expect2.GetPiece(1, 5) == king_black);
  EXPECT_TRUE(expect2.GetPiece(7, 1) == king_black);
  EXPECT_TRUE(expect2.GetPiece(7, 6) == king_black);
  EXPECT_TRUE(expect2.GetPiece(7, 4) == king_black);
  EXPECT_TRUE(expect2.GetPiece(4, 3) == king_black);
  EXPECT_TRUE(expect1.GetPiece(1, 4) == void_none);
  EXPECT_TRUE(expect1.GetPiece(1, 2) == void_none);
  EXPECT_TRUE(expect1.GetPiece(1, 5) == void_none);
  EXPECT_TRUE(expect1.GetPiece(7, 1) == void_none);
  EXPECT_TRUE(expect1.GetPiece(7, 6) == void_none);
  EXPECT_TRUE(expect1.GetPiece(7, 4) == void_none);
  EXPECT_TRUE(expect1.GetPiece(4, 3) == void_none);
}

TEST(Chess, under_attack_on_diagonally_x_plus_y_plus) {
  Piece void_none,
      king_white(Piece::PieceFigure::KING, Piece::PieceColor::WHITE),
      bishop_black(Piece::PieceFigure::BISHOP, Piece::PieceColor::BLACK);
  Chess clear_field(void_none);
  uint8_t positionKingX = 4, positionKingY = 4;
  clear_field.GetPiece(positionKingX, positionKingY) = king_white;
  clear_field.GetPiece(5, 5) = bishop_black;
  EXPECT_EQ(clear_field.IsUnderAttack(positionKingX, positionKingY),
            Piece::PieceFigure::BISHOP);
}

TEST(Chess, under_attack_on_diagonally_x_plus_y_minus) {
  Piece void_none,
      king_white(Piece::PieceFigure::KING, Piece::PieceColor::WHITE),
      bishop_black(Piece::PieceFigure::BISHOP, Piece::PieceColor::BLACK);
  Chess clear_field(void_none);
  uint8_t positionKingX = 4, positionKingY = 4;
  clear_field.GetPiece(positionKingX, positionKingY) = king_white;
  clear_field.GetPiece(5, 3) = bishop_black;
  EXPECT_EQ(clear_field.IsUnderAttack(positionKingX, positionKingY),
            Piece::PieceFigure::BISHOP);
}

TEST(Chess, under_attack_on_diagonally_x_minus_y_plus) {
  Piece void_none,
      king_white(Piece::PieceFigure::KING, Piece::PieceColor::WHITE),
      bishop_black(Piece::PieceFigure::BISHOP, Piece::PieceColor::BLACK);
  Chess clear_field(void_none);
  uint8_t positionKingX = 4, positionKingY = 4;
  clear_field.GetPiece(positionKingX, positionKingY) = king_white;
  clear_field.GetPiece(3, 5) = bishop_black;
  EXPECT_EQ(clear_field.IsUnderAttack(positionKingX, positionKingY),
            Piece::PieceFigure::BISHOP);
}

TEST(Chess, under_attack_on_diagonally_x_minus_y_minus) {
  Piece void_none,
      king_white(Piece::PieceFigure::KING, Piece::PieceColor::WHITE),
      bishop_black(Piece::PieceFigure::BISHOP, Piece::PieceColor::BLACK);
  Chess clear_field(void_none);
  uint8_t positionKingX = 4, positionKingY = 4;
  clear_field.GetPiece(positionKingX, positionKingY) = king_white;
  clear_field.GetPiece(3, 3) = bishop_black;
  EXPECT_EQ(clear_field.IsUnderAttack(positionKingX, positionKingY),
            Piece::PieceFigure::BISHOP);
}

TEST(Chess, under_attack_on_horizontally_x_plus) {
  Piece void_none,
      king_white(Piece::PieceFigure::KING, Piece::PieceColor::WHITE),
      rook_black(Piece::PieceFigure::ROOK, Piece::PieceColor::BLACK);
  Chess clear_field(void_none);
  uint8_t positionKingX = 4, positionKingY = 4;
  clear_field.GetPiece(positionKingX, positionKingY) = king_white;
  clear_field.GetPiece(5, positionKingY) = rook_black;
  EXPECT_EQ(clear_field.IsUnderAttack(positionKingX, positionKingY),
            Piece::PieceFigure::ROOK);
}

TEST(Chess, under_attack_on_horizontally_x_minus) {
  Piece void_none,
      king_white(Piece::PieceFigure::KING, Piece::PieceColor::WHITE),
      rook_black(Piece::PieceFigure::ROOK, Piece::PieceColor::BLACK);
  Chess clear_field(void_none);
  uint8_t positionKingX = 4, positionKingY = 4;
  clear_field.GetPiece(positionKingX, positionKingY) = king_white;
  clear_field.GetPiece(3, positionKingY) = rook_black;
  EXPECT_EQ(clear_field.IsUnderAttack(positionKingX, positionKingY),
            Piece::PieceFigure::ROOK);
}

TEST(Chess, under_attack_on_horizontally_y_plus) {
  Piece void_none,
      king_white(Piece::PieceFigure::KING, Piece::PieceColor::WHITE),
      rook_black(Piece::PieceFigure::ROOK, Piece::PieceColor::BLACK);
  Chess clear_field(void_none);
  uint8_t positionKingX = 4, positionKingY = 4;
  clear_field.GetPiece(positionKingX, positionKingY) = king_white;
  clear_field.GetPiece(positionKingX, 7) = rook_black;
  EXPECT_EQ(clear_field.IsUnderAttack(positionKingX, positionKingY),
            Piece::PieceFigure::ROOK);
}

TEST(Chess, under_attack_on_horizontally_y_minus) {
  Piece void_none,
      king_white(Piece::PieceFigure::KING, Piece::PieceColor::WHITE),
      rook_black(Piece::PieceFigure::ROOK, Piece::PieceColor::BLACK);
  Chess clear_field(void_none);
  uint8_t positionKingX = 4, positionKingY = 4;
  clear_field.GetPiece(positionKingX, positionKingY) = king_white;
  clear_field.GetPiece(positionKingX, 2) = rook_black;
  EXPECT_EQ(clear_field.IsUnderAttack(positionKingX, positionKingY),
            Piece::PieceFigure::ROOK);
}

TEST(Solution, find_white_king) {
  Piece void_none,
      king_white(Piece::PieceFigure::KING, Piece::PieceColor::WHITE);
  Chess clear_field(void_none);
  uint8_t positionKingX = 4, positionKingY = 5;
  clear_field.GetPiece(positionKingX, positionKingY) = king_white;
  auto expect = clear_field.FindWhiteKing();
  EXPECT_EQ(expect.first, positionKingX);
  EXPECT_EQ(expect.second, positionKingY);
}

TEST(Solution, mini_test_solution) {
  Piece void_none,
      king_white(Piece::PieceFigure::KING, Piece::PieceColor::WHITE);
  Chess clear_field(void_none);
  uint8_t positionKingX = 4, positionKingY = 5;
  clear_field.GetPiece(positionKingX, positionKingY) = king_white;
  auto expect = clear_field.FindWhiteKing();
  EXPECT_EQ(expect.first, positionKingX);
  EXPECT_EQ(expect.second, positionKingY);
}

TEST(Solution, functional_tests_with_pgsql) {
  try {
    std::string conn_string =
        "host=localhost dbname=chess user=postgres password=1";
    pqxx::connection connectionObject(conn_string);
    pqxx::work worker(connectionObject, "Functional Test");

    for (int i = 1;; ++i) {
      Piece for_fill{Piece::VOID, Piece::NONE};
      Chess test(for_fill);

      std::ostringstream string_query("");
      string_query << "SELECT MOVE_ID, PIECE_ID, PIECE_COLOR, XAXISMARKER, "
                      "YAXISNUMBER FROM TEST_VALUES WHERE GAME_ID = "
                   << i
                   << " AND MOVE_ID = (SELECT DISTINCT MAX(MOVE_ID) FROM "
                      "TEST_VALUES WHERE GAME_ID = "
                   << i << ")";

      pqxx::result response = worker.exec(string_query.str());
      if (!response.size()) {
        if (i == 1) {
          throw std::logic_error("No tests in Data Base...");
        }
        std::cout << "Test Cases is Done!" << std::endl;
        std::cout << "Check result from test cases!" << std::endl;
        break;
      }
      std::cout << "Test " << i << " is start!" << std::endl;

      for (auto row_iter = response.begin(), row_end = response.end();
           row_iter != row_end; ++row_iter) {
        int piece = std::atoi(row_iter[1].c_str()),
            color = std::atoi(row_iter[2].c_str()),
            marker = *row_iter[3].c_str() - 'A',
            number = *row_iter[4].c_str() - '1';

        Piece figure(Piece::FromIntToPieceFigure(piece),
                     Piece::FromIntToPieceColor(color));
        test.GetPiece(number, marker) = figure;
      }
      Chess::SolutionCheck answer = test.Solution();

      std::ostringstream answer_query("");
      answer_query << "SELECT ANSWER FROM RESULT_VALUES WHERE ID = " << i;
      pqxx::result answer_check = worker.exec(answer_query.str());
      switch (answer) {
        case Chess::NoCheck:
          std::cout << "In Test " << i << " King haven't Check" << std::endl;
          break;
        case Chess::CheckFromBishop:
          std::cout << "In Test " << i << " King have Check from Bishop"
                    << std::endl;
          break;
        case Chess::CheckFromRook:
          std::cout << "In Test " << i << " King have Check from Rook"
                    << std::endl;
      }
      EXPECT_EQ(std::atoi(answer_check[0][0].c_str()), answer);
      std::cout << "Test " << i << " is complete!" << std::endl << std::endl;
    }
  } catch (std::exception const &e) {
    std::cerr << e.what() << std::endl;
    throw std::logic_error("Test cases SQL is Failure");
  }
}

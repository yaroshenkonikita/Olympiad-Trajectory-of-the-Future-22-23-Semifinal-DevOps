//#include <pqxx/connection>
//#include <pqxx/transaction>
#include <pqxx/pqxx>
#include <iostream>

#include "../Chess.h"

int main() {
    try {
        std::string conn_string = "host=localhost dbname=chess user=postgres password=1";
        pqxx::connection connectionObject(conn_string);
        pqxx::work worker(connectionObject, "Functional Test");

        for (int i = 1;; ++i) {
            Piece for_fill{Piece::VOID, Piece::NONE};
            Chess test(for_fill);

            std::ostringstream string_query("");
            string_query << "SELECT MAX(MOVE_ID), PIECE_ID, PIECE_COLOR, XAXISMARKER, YAXISNUMBER FROM TEST_VALUES "
                            "WHERE GAME_ID = " << i << " GROUP BY GAME_ID, 2, 3, 4, 5";

            pqxx::result response = worker.exec(string_query.str());
            if (!response.size()) {
                if (i == 1) {
                    std::cout << "No one test case..." << std::endl;
                    return EXIT_FAILURE;
                }
                std::cout << "Test Case is Done!" << std::endl;
                return EXIT_SUCCESS;
            }
            std::cout << "Test " << i << " is start!" << std::endl;

            for (auto row_iter = response.begin(), row_end = response.end(); row_iter != row_end; ++row_iter) {
                int piece = std::atoi(row_iter[1].c_str()),
                color = std::atoi(row_iter[2].c_str()),
                marker = *row_iter[3].c_str() - 'A',
                number = *row_iter[4].c_str() - '1';

                Piece figure(Piece::FromIntToPieceFigure(piece), Piece::FromIntToPieceColor(color));
                test.GetPiece(number, marker) = figure;
            }
            Chess::SolutionCheck answer = test.Solution();

            switch (answer) {
                case Chess::NoCheck:
                    std::cout << "In Test " << i << " King haven't Check" << std::endl;
                    break;
                case Chess::CheckFromBishop:
                    std::cout << "In Test " << i << " King have Check from Bishop" << std::endl;
                    break;
                case Chess::CheckFromRook:
                    std::cout << "In Test " << i << " King have Check from Rook" << std::endl;
            }
            std::cout << "Test " << i << " is complete!" << std::endl << std::endl;
        }
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
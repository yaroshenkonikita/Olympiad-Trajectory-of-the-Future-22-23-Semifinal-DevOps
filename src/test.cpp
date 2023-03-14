#include <iostream>
#include <pqxx/connection>
#include <pqxx/transaction>
#include <pqxx/pqxx>
#include <string>
#include <sstream>
#include "Chess.h"

void help()
{
    std::cout << "Usage: <host> <dbname> <user> <password>" << std::endl;
}

int main(int argc, char **argv) {
    if (argc != 5) {
        help();
        return EXIT_FAILURE;
    }
    std::ostringstream conn_string("");
    conn_string << "host=" << argv[1] << " dbname=" << argv[2] << " user=" << argv[3] << " password=" << argv[4];
    try {
        pqxx::connection connectionObject(conn_string.str());
        pqxx::work worker(connectionObject, "Test");

        for (int i = 1;; ++i) {

            Piece for_fill{Piece::VOID, Piece::NONE};
            Chess test(for_fill);

            std::ostringstream string_query("");
            string_query << "SELECT MAX(MOVE_ID), PIECE_ID, PIECE_COLOR, XAXISMARKER, YAXISNUMBER FROM TEST_VALUES "
                            "WHERE GAME_ID = " << i << " GROUP BY GAME_ID, 2, 3, 4, 5";
            std::cout << string_query.str() << std::endl;

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
            std::cout << "ok parser" << std::endl;

            for (pqxx::result::const_iterator iter_row = response.begin(), r_end = response.end(); iter_row != r_end; ++iter_row) {
                auto column = iter_row->begin();
                int piece = std::atoi((++column)->c_str()),
                color = std::atoi((++column)->c_str()),
                marker = *((++column)->c_str()) - 'A',
                number = *((++column)->c_str()) - '1';
                std::cout << "ok parser" << std::endl;

                Piece Figure(Piece::FromIntToPieceFigure(piece), Piece::FromIntToPieceColor(color));
                std::cout << "ok create piece" << std::endl;
                Piece &tmp = test.GetPiece(number, marker);
                tmp = Figure;
                std::cout << "ok setter in piece" << std::endl;
            }
            Chess::SolutionCheck answer = test.Solution();
            std::cout << "Solution is ok" << std::endl;

            switch (answer) {
                case Chess::NoCheck:
                    std::cout << "In Test " << i << "King haven't Check" << std::endl;
                    break;
                case Chess::CheckFromBishop:
                    std::cout << "In Test " << i << "King have Check from Bishop" << std::endl;
                    break;
                case Chess::CheckFromRook:
                    std::cout << "In Test " << i << "King have Check from Rook" << std::endl;
            }
            std::cout << "Test " << i << " is complete!" << std::endl;
        }
    }
    catch (std::exception const &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
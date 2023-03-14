#include <iostream>
#include <pqxx/connection>
#include <pqxx/transaction>
#include <pqxx/pqxx>
#include <string>
#include <sstream>

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

        pqxx::result response = worker.exec("SELECT PIECE_ID, PIECE_COLOR, XAXISMARKER, YAXISNUMBER FROM TEST_VALUES WHERE GAME_ID = 1 AND MOVE_ID = 20");
        if (!response.size()) {
            std::cout << "Empty result set." << std::endl;
            return EXIT_FAILURE;
        }
        for (pqxx::result::const_iterator i = response.begin(), r_end = response.end(); i != r_end; ++i) {
            for (auto f = i->begin(), f_end = i->end(); f != f_end; ++f) {
                std::cout << f->name() << " = '" << f->c_str() << "'" << std::endl;
            }
            std::cout << std::endl;
        }

    }
    catch (std::exception const &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
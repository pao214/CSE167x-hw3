#include "Parser.h"

int main(int argc, const char* argv[])
{
    // Usage checking.
    if (argc != 2)
    {
        std::cerr << "Usage: bin/main <inputFilename>" << std::endl;
        return 1;
    }

    // Main logic.
    Parser::parse(argv[1]);
    return 0;
}

#include <cstdlib>
#include <cstring>
#include "test.h"

int main(int argc, char* argv[])
{
    if( argc == 2 && (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "--test") == 0) ){
        test_main();
    }

    return EXIT_SUCCESS;
}

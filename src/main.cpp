#include <cstdlib>

#include "crocodin.hh"


int main(int argc, char* argv[])  {

    Crocodin crocodin;
    if (crocodin.run()) {
        return EXIT_SUCCESS;
    }
    else {
        return EXIT_FAILURE;
    }

}

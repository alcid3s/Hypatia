#include <iostream>
#include <sstream>
#include <vector>
#include "Args.h"

int main(int argc, char** argv) {

    // Parsing user input
    try {
        Args args(argc, argv);        
        std::stringstream ss(args.get_input_files());
        std::string t;
        char del = ',';

        std::vector<std::string> files;
        while(getline(ss, t, del)) {
            files.push_back(t);
        }

    } catch (const std::exception& e) {
        fprintf(stderr, "Error: %s\n", e.what());
        return 1;
    }

    return 0;
}
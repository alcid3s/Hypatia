#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include "Args.h"

int main(int argc, char** argv) {
    std::unique_ptr<Args> args = nullptr;

    // Parsing user input
    try {
        args = std::make_unique<Args>(argc, argv);        
    } catch (const std::exception& e) {
        fprintf(stderr, "Error: %s\n", e.what());
        return 1;
    }

    std::vector<std::string> files;
    if(args) {
        args->parse_files(files);
    }

    for (auto &&filename : files)
    {
        std::ifstream file(filename);
        std::string line;

        if(file.is_open()) {
            while(getline(file, line)) {
                std::cout << line << std::endl;
            }
        } else {
            fprintf(stderr, "Error: Could not open file %s\n", filename.c_str());
        }
    }
    

    return 0;
}
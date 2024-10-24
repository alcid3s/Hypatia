#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include "Args.h"
#include "Tokeniser.h"

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

    Tokeniser* tokeniser = new Tokeniser();
    for (auto &&filename : files)
    {
        std::ifstream file(filename);
        if(file.is_open()) {
            auto symbols = tokeniser->analyse(file);
            tokeniser->tokenise(symbols);
        } else {
            fprintf(stderr, "Error: Could not open file %s\n", filename.c_str());
        }
    }
    
    return 0;
}
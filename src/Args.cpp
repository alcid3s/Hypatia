#include "Args.h"

Args::Args(int argc, char** argv) {
    int opt;
    while((opt = getopt(argc, argv, "i:o:")) != -1) {
        switch(opt) {
            case 'i':
                this->input_files = optarg;
                break;
            case 'o':
                this->output_file = optarg;
                break;
            default:
                throw std::runtime_error("Usage: -o <output_file>");
        }
    }

    if(this->input_files.empty() || this->output_file.empty()) {
        throw std::runtime_error("Missing required arguments");
    }
}

Args::~Args() {

}
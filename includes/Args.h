#ifndef ARGS
#define ARGS

#include <string>
#include <stdexcept>
#include <unistd.h>

class Args {
    private:
    std::string input_files;
    std::string output_file;

    public:
        Args(int argc, char** argv);
        ~Args();

        const inline std::string& get_input_files() const { return this->input_files; }
        const inline std::string& get_output_file() const { return this->output_file; }
};

#endif
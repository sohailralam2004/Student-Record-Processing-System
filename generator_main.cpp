#include "StudentFileGenerator.h"
#include "StudentException.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    try {
        const std::string outputDirectory =
            argc > 1 ? argv[1] : "generated_data";
        StudentFileGenerator generator;
        generator.generateAll(outputDirectory);
        std::cout << "Generated student files in: " << outputDirectory << '\n';
        return 0;
    } catch (const StudentException& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}

#include "StudentFileGenerator.h"
#include "StudentException.h"

#include <filesystem>
#include <fstream>
#include <random>
#include <string>

std::vector<std::size_t> StudentFileGenerator::supportedRecordCounts() {
    return {1'000, 10'000, 100'000, 1'000'000, 10'000'000};
}

void StudentFileGenerator::generate(const std::string& fileName,
                                    std::size_t recordCount) const {
    if (recordCount == 0) {
        throw StudentException("Record count must be greater than zero.");
    }

    const std::filesystem::path outputPath(fileName);
    const std::filesystem::path parent = outputPath.parent_path();
    if (!parent.empty()) {
        std::error_code error;
        std::filesystem::create_directories(parent, error);
        if (error) {
            throw StudentException("Cannot create output directory: " +
                                   parent.string());
        }
    }

    std::ofstream output(outputPath);
    if (!output) {
        throw StudentException("Cannot create output file: " + fileName);
    }

    std::random_device seed;
    std::mt19937 generator(seed());
    std::uniform_int_distribution<int> score(0, 10);

    output << "Name Surname HW1 HW2 HW3 HW4 HW5 Exam\n";
    for (std::size_t index = 1; index <= recordCount; ++index) {
        output << "Name" << index << " Surname" << index;
        for (int homework = 0; homework < 5; ++homework) {
            output << ' ' << score(generator);
        }
        output << ' ' << score(generator) << '\n';
    }

    if (!output) {
        throw StudentException("Error while writing output file: " + fileName);
    }
}

void StudentFileGenerator::generateAll(const std::string& directory) const {
    for (const std::size_t recordCount : supportedRecordCounts()) {
        const std::string fileName = directory + "/Students_" +
                                     std::to_string(recordCount) + ".txt";
        generate(fileName, recordCount);
    }
}

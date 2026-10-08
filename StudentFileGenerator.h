#ifndef STUDENT_FILE_GENERATOR_H
#define STUDENT_FILE_GENERATOR_H

#include <cstddef>
#include <string>
#include <vector>

class StudentFileGenerator {
public:
    static std::vector<std::size_t> supportedRecordCounts();

    void generate(const std::string& fileName, std::size_t recordCount) const;
    void generateAll(const std::string& directory) const;
};

#endif

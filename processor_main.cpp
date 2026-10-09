#include "StudentException.h"
#include "StudentManager.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: processor <input> <passed-output> <failed-output>\n";
        return 1;
    }

    try {
        StudentManager manager;
        manager.loadFromFile(argv[1]);
        manager.splitByFinalGrade(argv[2], argv[3]);

        std::size_t passed = 0;
        for (const Person& student : manager.students()) {
            if (student.calculateFinalGrade() >= 5.0) {
                ++passed;
            }
        }
        const std::size_t failed = manager.students().size() - passed;

        std::cout << "Processed " << manager.students().size()
                  << " records: " << passed << " passed, " << failed
                  << " failed.\n";
        return 0;
    } catch (const StudentException& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}

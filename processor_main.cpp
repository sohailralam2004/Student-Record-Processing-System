#include "StudentException.h"
#include "StudentManager.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: processor <input> <passed-output> <failed-output>\n";
        return 1;
    }

    try {
        using Clock = std::chrono::steady_clock;
        using Milliseconds = std::chrono::duration<double, std::milli>;

        const auto totalStart = Clock::now();
        StudentManager manager;

        const auto readStart = Clock::now();
        manager.loadFromFile(argv[1]);
        const auto readEnd = Clock::now();

        const auto sortStart = Clock::now();
        manager.sortBySurname();
        const auto sortEnd = Clock::now();

        std::vector<Person> passedStudents;
        std::vector<Person> failedStudents;
        const auto splitStart = Clock::now();
        manager.splitByFinalGrade(passedStudents, failedStudents);
        const auto splitEnd = Clock::now();

        const auto writeStart = Clock::now();
        manager.writeStudentsToFile(argv[2], passedStudents);
        manager.writeStudentsToFile(argv[3], failedStudents);
        const auto writeEnd = Clock::now();

        const auto totalEnd = Clock::now();
        const auto elapsed = [](const auto start, const auto end) {
            return Milliseconds(end - start).count();
        };

        std::cout << "Processed " << manager.students().size()
                  << " records: " << passedStudents.size() << " passed, "
                  << failedStudents.size() << " failed.\n";
        std::cout << std::fixed << std::setprecision(3);
        std::cout << "Timing (milliseconds):\n"
                  << "  Read:  " << elapsed(readStart, readEnd) << "\n"
                  << "  Sort:  " << elapsed(sortStart, sortEnd) << "\n"
                  << "  Split: " << elapsed(splitStart, splitEnd) << "\n"
                  << "  Write: " << elapsed(writeStart, writeEnd) << "\n"
                  << "  Total: " << elapsed(totalStart, totalEnd) << "\n";
        return 0;
    } catch (const StudentException& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}

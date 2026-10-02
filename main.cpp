#include "Person.h"

#include <iomanip>
#include <iostream>
#include <string>

int main() {
    Person student;

    std::cout << "Enter: first name, surname, homework scores, -1, exam score\n";
    std::cout << "Example: Anna Smith 8 9 10 -1 9\n> ";

    if (!(std::cin >> student)) {
        std::cerr << "Invalid student data.\n";
        return 1;
    }

    int method = 1;
    std::cout << "Choose calculation method (1 - average, 2 - median): ";
    if (!(std::cin >> method) || (method != 1 && method != 2)) {
        std::cerr << "Invalid method. Average will be used.\n";
        method = 1;
    }

    const bool useMedian = method == 2;
    const double selectedHomeworkResult =
        useMedian ? student.homeworkMedian() : student.homeworkAverage();
    const double selectedFinalGrade =
        useMedian ? student.calculateFinalGradeByMedian()
                  : student.calculateFinalGrade();

    std::cout << "\nStudent: " << student << '\n';
    std::cout << "\n" << std::left << std::setw(15) << "Name"
              << std::setw(15) << "Surname"
              << std::right << std::setw(18)
              << (useMedian ? "Homework (Med.)" : "Homework (Avg.)")
              << std::setw(18)
              << (useMedian ? "Final (Med.)" : "Final (Avg.)") << '\n';
    std::cout << std::string(66, '-') << '\n';
    std::cout << std::left << std::setw(15) << student.firstName()
              << std::setw(15) << student.surname()
              << std::right << std::fixed << std::setprecision(2)
              << std::setw(18) << selectedHomeworkResult
              << std::setw(18) << selectedFinalGrade << '\n';

    // Simple checks that exercise the explicitly defined Rule of Three.
    Person copiedStudent(student);
    Person assignedStudent;
    assignedStudent = student;

    std::cout << "Copy constructor check: " << copiedStudent << '\n';
    std::cout << "Assignment operator check: " << assignedStudent << '\n';

    return 0;
}

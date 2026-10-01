#include "Person.h"

#include <iomanip>
#include <iostream>

int main() {
    Person student;

    std::cout << "Enter: first name, surname, homework count, homework scores, exam score\n";
    std::cout << "Example: Anna Smith 3 8 9 10 9\n> ";

    if (!(std::cin >> student)) {
        std::cerr << "Invalid student data.\n";
        return 1;
    }

    std::cout << "\nStudent: " << student << '\n';
    std::cout << std::fixed << std::setprecision(2)
              << "Final grade calculation result: "
              << student.calculateFinalGrade() << '\n';

    // Simple checks that exercise the copy constructor and assignment operator.
    Person copiedStudent(student);
    Person assignedStudent;
    assignedStudent = student;

    std::cout << "Copy constructor check: " << copiedStudent << '\n';
    std::cout << "Assignment operator check: " << assignedStudent << '\n';

    return 0;
}

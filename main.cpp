#include "Person.h"
#include "StudentException.h"
#include "StudentManager.h"

#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

int main() {
    try {
        Person student;
        StudentManager studentManager;

        int inputMode = 1;
        std::cout << "Choose data input (1 - manual, 2 - random, 3 - file): ";
        if (!(std::cin >> inputMode) || (inputMode < 1 || inputMode > 3)) {
            throw StudentException("Input mode must be 1, 2, or 3.");
        }

        if (inputMode == 1) {
            std::cout << "Enter: first name, surname, homework scores, -1, exam score\n";
            std::cout << "Example: Anna Smith 8 9 10 -1 9\n> ";

            if (!(std::cin >> student)) {
                throw StudentException(
                    "Invalid student data: scores must be between 0 and 10, "
                    "followed by -1 and an exam score.");
            }
        } else if (inputMode == 2) {
            std::string firstName;
            std::string surname;
            int homeworkCount = 0;

            std::cout << "Enter first name, surname and homework count: ";
            if (!(std::cin >> firstName >> surname >> homeworkCount) ||
                firstName.empty() || surname.empty() || homeworkCount < 0) {
                throw StudentException("Invalid random student data.");
            }

            std::random_device seed;
            std::mt19937 generator(seed());
            std::uniform_int_distribution<int> scoreDistribution(0, 10);

            std::vector<double> homework;
            for (int i = 0; i < homeworkCount; ++i) {
                homework.push_back(scoreDistribution(generator));
            }
            const double exam = scoreDistribution(generator);
            student = Person(firstName, surname, homework, exam);

            std::cout << "Random scores generated on the range 0..10.\n";
        } else {
            if (!studentManager.loadFromFile("Students.txt")) {
                throw StudentException("Could not read student records from Students.txt.");
            }
            studentManager.sortBySurname();
            std::cout << studentManager.students().size()
                      << " student records loaded and sorted by surname.\n";
            studentManager.printReport(std::cout);
            return 0;
        }

        int method = 1;
        std::cout << "Choose calculation method (1 - average, 2 - median): ";
        if (!(std::cin >> method) || (method != 1 && method != 2)) {
            throw StudentException("Calculation method must be 1 or 2.");
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

        Person copiedStudent(student);
        Person assignedStudent;
        assignedStudent = student;

        std::cout << "Copy constructor check: " << copiedStudent << '\n';
        std::cout << "Assignment operator check: " << assignedStudent << '\n';

        return 0;
    } catch (const StudentException& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}

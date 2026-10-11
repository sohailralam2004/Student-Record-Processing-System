#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "Person.h"

#include <deque>
#include <iosfwd>
#include <string>

class StudentManager {
public:
    bool loadFromFile(const std::string& fileName);
    void sortBySurname();
    void printReport(std::ostream& output) const;
    void splitByFinalGrade(std::deque<Person>& passedStudents,
                           std::deque<Person>& failedStudents) const;
    void writeStudentsToFile(const std::string& fileName,
                             const std::deque<Person>& students) const;

    const std::deque<Person>& students() const;

private:
    std::deque<Person> students_;
};

#endif

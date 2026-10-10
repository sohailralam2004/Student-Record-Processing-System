#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "Person.h"

#include <iosfwd>
#include <string>
#include <vector>

class StudentManager {
public:
    bool loadFromFile(const std::string& fileName);
    void sortBySurname();
    void printReport(std::ostream& output) const;
    void splitByFinalGrade(std::vector<Person>& passedStudents,
                           std::vector<Person>& failedStudents) const;
    void writeStudentsToFile(const std::string& fileName,
                             const std::vector<Person>& students) const;

    const std::vector<Person>& students() const;

private:
    std::vector<Person> students_;
};

#endif

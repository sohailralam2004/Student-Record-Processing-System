#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "Person.h"

#include <iosfwd>
#include <list>
#include <string>

class StudentManager {
public:
    bool loadFromFile(const std::string& fileName);
    void sortBySurname();
    void printReport(std::ostream& output) const;
    void splitByFinalGrade(std::list<Person>& passedStudents,
                           std::list<Person>& failedStudents) const;
    void writeStudentsToFile(const std::string& fileName,
                             const std::list<Person>& students) const;

    const std::list<Person>& students() const;

private:
    std::list<Person> students_;
};

#endif

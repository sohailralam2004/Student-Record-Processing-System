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

    const std::vector<Person>& students() const;

private:
    std::vector<Person> students_;
};

#endif

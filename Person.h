#ifndef PERSON_H
#define PERSON_H

#include <iosfwd>
#include <string>

class Person {
private:
    std::string firstName_;
    std::string surname_;
    double* homework_;
    int homeworkCount_;
    double exam_;
    double finalGrade_;

    void copyHomework(const double* homework, int count);

public:
    Person();
    Person(const std::string& firstName, const std::string& surname,
           const double* homework, int homeworkCount, double exam);

    // Rule of Three
    Person(const Person& other);
    Person& operator=(const Person& other);
    ~Person();

    double homeworkAverage() const;
    double calculateFinalGrade() const;

    const std::string& firstName() const;
    const std::string& surname() const;
    double finalGrade() const;

    friend std::istream& operator>>(std::istream& input, Person& person);
    friend std::ostream& operator<<(std::ostream& output, const Person& person);
};

#endif

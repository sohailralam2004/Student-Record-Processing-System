#ifndef PERSON_H
#define PERSON_H

#include <iosfwd>
#include <string>
#include <vector>

class Person {
private:
    std::string firstName_;
    std::string surname_;
    std::vector<double> homework_;
    double exam_;
    double finalGrade_;

public:
    Person();
    Person(const std::string& firstName, const std::string& surname,
           const std::vector<double>& homework, double exam);

    // Rule of Three, written explicitly as required by the assignment.
    Person(const Person& other);
    Person& operator=(const Person& other);
    ~Person();

    double homeworkAverage() const;
    double homeworkMedian() const;
    double calculateFinalGrade() const;
    double calculateFinalGradeByMedian() const;

    bool readFileLine(const std::string& line);

    const std::string& firstName() const;
    const std::string& surname() const;
    const std::vector<double>& homeworkScores() const;
    double exam() const;
    double finalGrade() const;

    friend std::istream& operator>>(std::istream& input, Person& person);
    friend std::ostream& operator<<(std::ostream& output, const Person& person);
};

#endif

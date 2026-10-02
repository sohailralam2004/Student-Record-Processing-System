#include "Person.h"

#include <iostream>

Person::Person()
    : firstName_(), surname_(), homework_(), exam_(0.0), finalGrade_(0.0) {}

Person::Person(const std::string& firstName, const std::string& surname,
               const std::vector<double>& homework, double exam)
    : firstName_(firstName), surname_(surname), homework_(homework),
      exam_(exam), finalGrade_(0.0) {}

Person::Person(const Person& other)
    : firstName_(other.firstName_), surname_(other.surname_),
      homework_(other.homework_), exam_(other.exam_),
      finalGrade_(other.finalGrade_) {}

Person& Person::operator=(const Person& other) {
    if (this != &other) {
        firstName_ = other.firstName_;
        surname_ = other.surname_;
        homework_ = other.homework_;
        exam_ = other.exam_;
        finalGrade_ = other.finalGrade_;
    }
    return *this;
}

Person::~Person() {
    // std::vector releases its own memory.
}

double Person::homeworkAverage() const {
    if (homework_.empty()) {
        return 0.0;
    }

    double sum = 0.0;
    for (double score : homework_) {
        sum += score;
    }
    return sum / homework_.size();
}

double Person::calculateFinalGrade() const {
    return 0.3 * homeworkAverage() + 0.7 * exam_;
}

const std::string& Person::firstName() const {
    return firstName_;
}

const std::string& Person::surname() const {
    return surname_;
}

double Person::finalGrade() const {
    return finalGrade_;
}

std::istream& operator>>(std::istream& input, Person& person) {
    input >> person.firstName_ >> person.surname_;
    if (!input) {
        return input;
    }

    std::vector<double> newHomework;
    double score = 0.0;
    while (input >> score && score != -1.0) {
        newHomework.push_back(score);
    }

    if (!input) {
        return input;
    }

    input >> person.exam_;
    if (!input) {
        return input;
    }

    person.homework_ = newHomework;
    person.finalGrade_ = 0.0;
    return input;
}

std::ostream& operator<<(std::ostream& output, const Person& person) {
    output << person.firstName_ << ' ' << person.surname_
           << " (homework: " << person.homework_.size()
           << ", exam: " << person.exam_ << ')';
    return output;
}

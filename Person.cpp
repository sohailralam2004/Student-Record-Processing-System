#include "Person.h"

#include <algorithm>
#include <iostream>
#include <sstream>

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

double Person::homeworkMedian() const {
    if (homework_.empty()) {
        return 0.0;
    }

    std::vector<double> sortedHomework = homework_;
    std::sort(sortedHomework.begin(), sortedHomework.end());

    const std::size_t middle = sortedHomework.size() / 2;
    if (sortedHomework.size() % 2 == 1) {
        return sortedHomework[middle];
    }
    return (sortedHomework[middle - 1] + sortedHomework[middle]) / 2.0;
}

double Person::calculateFinalGradeByMedian() const {
    return 0.3 * homeworkMedian() + 0.7 * exam_;
}

bool Person::readFileLine(const std::string& line) {
    std::istringstream row(line);
    std::string firstName;
    std::string surname;
    std::vector<double> values;
    double value = 0.0;

    if (!(row >> firstName >> surname)) {
        return false;
    }
    while (row >> value) {
        values.push_back(value);
    }

    if (values.empty()) {
        return false;
    }

    const double exam = values.back();
    values.pop_back();
    firstName_ = firstName;
    surname_ = surname;
    homework_ = values;
    exam_ = exam;
    finalGrade_ = 0.0;
    return true;
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

#include "Person.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>

void Person::copyHomework(const double* homework, int count) {
    if (count < 0) {
        throw std::invalid_argument("Homework count cannot be negative");
    }

    homeworkCount_ = count;
    homework_ = count > 0 ? new double[count] : nullptr;

    for (int i = 0; i < homeworkCount_; ++i) {
        homework_[i] = homework[i];
    }
}

Person::Person()
    : firstName_(), surname_(), homework_(nullptr), homeworkCount_(0),
      exam_(0.0), finalGrade_(0.0) {}

Person::Person(const std::string& firstName, const std::string& surname,
               const double* homework, int homeworkCount, double exam)
    : firstName_(firstName), surname_(surname), homework_(nullptr),
      homeworkCount_(0), exam_(exam), finalGrade_(0.0) {
    copyHomework(homework, homeworkCount);
}

Person::Person(const Person& other)
    : firstName_(other.firstName_), surname_(other.surname_), homework_(nullptr),
      homeworkCount_(0), exam_(other.exam_), finalGrade_(other.finalGrade_) {
    copyHomework(other.homework_, other.homeworkCount_);
}

Person& Person::operator=(const Person& other) {
    if (this != &other) {
        double* newHomework = other.homeworkCount_ > 0
                                  ? new double[other.homeworkCount_]
                                  : nullptr;
        for (int i = 0; i < other.homeworkCount_; ++i) {
            newHomework[i] = other.homework_[i];
        }

        delete[] homework_;
        homework_ = newHomework;
        homeworkCount_ = other.homeworkCount_;
        firstName_ = other.firstName_;
        surname_ = other.surname_;
        exam_ = other.exam_;
        finalGrade_ = other.finalGrade_;
    }
    return *this;
}

Person::~Person() {
    delete[] homework_;
}

double Person::homeworkAverage() const {
    double average = 0.0;
    if (homeworkCount_ > 0) {
        for (int i = 0; i < homeworkCount_; ++i) {
            average += homework_[i];
        }
        average /= homeworkCount_;
    }

    return average;
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
    int count = 0;
    input >> person.firstName_ >> person.surname_ >> count;

    if (!input) {
        return input;
    }
    if (count < 0) {
        input.setstate(std::ios::failbit);
        return input;
    }

    double* newHomework = count > 0 ? new double[count] : nullptr;
    for (int i = 0; i < count; ++i) {
        input >> newHomework[i];
    }
    input >> person.exam_;

    if (!input) {
        delete[] newHomework;
        return input;
    }

    delete[] person.homework_;
    person.homework_ = newHomework;
    person.homeworkCount_ = count;
    person.finalGrade_ = 0.0;
    return input;
}

std::ostream& operator<<(std::ostream& output, const Person& person) {
    output << person.firstName_ << ' ' << person.surname_
           << " (homework: " << person.homeworkCount_
           << ", exam: " << person.exam_ << ')';
    return output;
}

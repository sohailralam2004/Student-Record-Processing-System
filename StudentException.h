#ifndef STUDENT_EXCEPTION_H
#define STUDENT_EXCEPTION_H

#include <stdexcept>
#include <string>

class StudentException : public std::runtime_error {
public:
    explicit StudentException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif

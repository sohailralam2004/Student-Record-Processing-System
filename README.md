# Student Record Processing System

## Introduction

This project is a C++ systems programming application for processing student records. It stores each student's first name, surname, homework results, exam result, and calculated final grade. The application will be developed incrementally, starting with the `Person` class and later adding dynamic homework input, average and median calculations, random score generation, file processing, sorting, and formatted output.

The project uses the Rule of Three (`destructor`, `copy constructor`, and `copy-assignment operator`) as required by the assignment. Homework results will be represented using `std::vector` so that the program can support a variable number of homework assignments.

## Basic final-grade formula

The initial calculation uses the weighted formula:

```text
Final grade = 0.3 × homework result + 0.7 × exam result
```

Where `homework result` can later be calculated either as the arithmetic average or as the median of the homework scores. The program will display both calculation methods in the later stages of development.

## Data format

The supplied student data uses the following general structure:

```text
Name Surname ND1 ND2 ... NDn Egz.
```

The number of homework results is not fixed. The final implementation will read the homework values into a `std::vector` and treat the last numeric value as the exam result.

## Development status

- [x] Initial repository and README
- [ ] `Person` class and Rule of Three
- [ ] Average calculation
- [ ] Dynamic homework data with `std::vector`
- [ ] Median calculation
- [ ] Random score generation
- [ ] File input from `Students.txt`
- [ ] Sorting and formatted output
- [ ] Testing and release `v0.1`

## References

- [cppreference: Rule of Three](https://en.cppreference.com/w/cpp/language/rule_of_three)
- [GeeksforGeeks: Vector in C++ STL](https://www.geeksforgeeks.org/cpp/vector-in-cpp-stl/)

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
- [x] `Person` class and Rule of Three
- [x] Average calculation
- [x] Dynamic homework data with `std::vector`
- [x] Median calculation
- [x] Random score generation
- [x] Create `Students.txt` data file
- [x] Read one record from `Students.txt`
- [x] Read all records from `Students.txt` into `std::vector<Person>`
- [x] Display all final grades using average and median
- [x] Sort students by surname and finalize formatting
- [x] Test and clean the project
- [x] Release `v0.1`
- [x] Create `v0.2` branch from the stable `v0.1` version
- [x] Refactor student-file operations into `StudentManager.h/.cpp`
- [ ] Add exception handling for `v0.2`
- [ ] Generate large student files and measure performance

## Current version

The current `v0.2` development branch is based on the released `v0.1` program. The `Person` class remains responsible for one student's data and calculations, while the new `StudentManager` class is responsible for loading, sorting, and reporting a collection of students.

Homework input ends with `-1`, followed by the exam score. For example:

```text
Anna Smith 8 9 10 -1 9
```

After entering the record, choose `1` for the average or `2` for the median. For an even number of homework scores, the median is the average of the two middle sorted scores.

The program also supports random data generation. Choose `2`, then enter the first name, surname, and number of homework assignments. Homework and exam scores are generated as integers from `0` to `10`.

Choose `3` to open `Students.txt`, skip its header, read all valid student records, store them in `std::vector<Person>`, and sort them by surname. The program displays both final-grade calculations for every loaded student.

The project was tested with manual input, random input, file input, average calculation, median calculation, and an even number of homework scores. Temporary executable files are not kept in the repository.

The project also includes a preliminary `Students.txt` file with sample student records.

Compile and run it with:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp Person.cpp StudentManager.cpp -o students
./students
```

## References

- [cppreference: Rule of Three](https://en.cppreference.com/w/cpp/language/rule_of_three)
- [GeeksforGeeks: Vector in C++ STL](https://www.geeksforgeeks.org/cpp/vector-in-cpp-stl/)

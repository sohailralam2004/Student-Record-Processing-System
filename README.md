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
- [ ] Sorting and formatted output
- [ ] Testing and release `v0.1`

## Current version

The current `v0.1` stage contains a simple interactive test program. It reads one student record with a variable number of homework scores, lets the user choose the average or median method, calculates the selected result, and exercises the copy constructor and copy-assignment operator.

Homework input ends with `-1`, followed by the exam score. For example:

```text
Anna Smith 8 9 10 -1 9
```

After entering the record, choose `1` for the average or `2` for the median. For an even number of homework scores, the median is the average of the two middle sorted scores.

The program also supports random data generation. Choose `2`, then enter the first name, surname, and number of homework assignments. Homework and exam scores are generated as integers from `0` to `10`.

Choose `3` to open `Students.txt`, skip its header, read all valid student records, and store them in `std::vector<Person>`. The current output still displays the first loaded student; displaying the complete list will be added in the next stage.

The project also includes a preliminary `Students.txt` file with sample student records.

Compile and run it with:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp Person.cpp -o students
./students
```

## References

- [cppreference: Rule of Three](https://en.cppreference.com/w/cpp/language/rule_of_three)
- [GeeksforGeeks: Vector in C++ STL](https://www.geeksforgeeks.org/cpp/vector-in-cpp-stl/)

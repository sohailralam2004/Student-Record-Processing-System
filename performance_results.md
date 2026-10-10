# v0.2 Performance Results

## Test setup

- Container: `std::vector<Person>`
- Compiler: `g++` with `-O2 -std=c++17`
- Timing clock: `std::chrono::steady_clock`
- Measured stages: reading, sorting, splitting, writing, and total processing time
- Input data: randomly generated homework and exam scores from `0` to `10`
- Classification rule:
  - `final grade >= 5.0` -> `passed`
  - `final grade < 5.0` -> `failed`

The generated input and output files are stored locally in `generated_data/` and are excluded from Git because the largest input file is very large.

## Results

| Records | Passed | Failed | Read (ms) | Sort (ms) | Split (ms) | Write (ms) | Total (ms) |
|---:|---:|---:|---:|---:|---:|---:|---:|
| 1,000 | 510 | 490 | 1.324 | 0.400 | 0.062 | 1.184 | 2.971 |
| 10,000 | 5,015 | 4,985 | 12.857 | 5.948 | 0.875 | 10.906 | 30.588 |
| 100,000 | 50,541 | 49,459 | 131.568 | 85.251 | 9.590 | 105.864 | 332.275 |
| 1,000,000 | 502,382 | 497,618 | 1,139.618 | 976.225 | 105.010 | 1,065.992 | 3,286.846 |
| 10,000,000 | 5,024,460 | 4,975,540 | 12,726.496 | 12,139.119 | 1,015.560 | 10,484.363 | 36,365.540 |

## Observations

- The total processing time increases with the number of records.
- Reading, sorting, and writing are the largest operations for the largest input.
- Splitting is comparatively smaller because it only classifies already loaded students.
- The generated output files were checked to contain all input records, including the header in each output file.

These results are a single benchmark run on the development environment. They are useful for comparing the later `std::list` and `std::deque` implementations, but they should not be treated as hardware-independent absolute times.

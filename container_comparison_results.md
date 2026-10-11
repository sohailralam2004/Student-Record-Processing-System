# Container Performance Comparison

This benchmark compares the same student-record processing pipeline using three STL containers:

- `std::vector<Person>`
- `std::list<Person>`
- `std::deque<Person>`

For every run, the program measures reading, sorting, splitting, writing, and total processing time with `std::chrono::steady_clock`. Each container processes the same input file sequentially, and writes its own `passed` and `failed` output files.

## Results

Times are in milliseconds. The benchmark was run on the five required input sizes.

| Container | Records | Passed | Failed | Read | Sort | Split | Write | Total |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| vector | 1,000 | 510 | 490 | 1.517 | 0.492 | 0.214 | 1.323 | 3.547 |
| list | 1,000 | 510 | 490 | 1.107 | 0.102 | 0.103 | 1.612 | 2.925 |
| deque | 1,000 | 510 | 490 | 1.251 | 0.582 | 0.060 | 1.319 | 3.214 |
| vector | 10,000 | 5,015 | 4,985 | 62.202 | 7.273 | 3.375 | 21.885 | 94.739 |
| list | 10,000 | 5,015 | 4,985 | 17.230 | 1.558 | 1.677 | 22.017 | 42.484 |
| deque | 10,000 | 5,015 | 4,985 | 19.363 | 7.202 | 0.719 | 18.671 | 45.959 |
| vector | 100,000 | 50,541 | 49,459 | 178.444 | 117.264 | 36.404 | 157.212 | 489.328 |
| list | 100,000 | 50,541 | 49,459 | 117.374 | 17.117 | 15.549 | 131.779 | 281.822 |
| deque | 100,000 | 50,541 | 49,459 | 114.311 | 92.175 | 6.565 | 122.056 | 335.112 |
| vector | 1,000,000 | 502,382 | 497,618 | 1,232.393 | 1,155.046 | 256.054 | 1,366.727 | 4,010.222 |
| list | 1,000,000 | 502,382 | 497,618 | 1,162.462 | 229.220 | 160.170 | 1,483.562 | 3,035.417 |
| deque | 1,000,000 | 502,382 | 497,618 | 1,505.807 | 1,273.253 | 66.096 | 1,261.501 | 4,106.663 |
| vector | 10,000,000 | 5,024,460 | 4,975,540 | 13,409.603 | 14,460.098 | 4,067.682 | 12,520.711 | 44,458.098 |
| list | 10,000,000 | 5,024,460 | 4,975,540 | 12,533.538 | 3,450.241 | 1,916.251 | 13,721.643 | 31,621.676 |
| deque | 10,000,000 | 5,024,460 | 4,975,540 | 13,245.243 | 17,795.575 | 860.183 | 12,780.246 | 44,681.254 |

## Observations

- All three containers produced identical record counts for every input size.
- In this single benchmark run, `std::list` had the lowest total time for the tested sizes from 1,000 through 10,000,000 records.
- `std::list::sort` was faster than the random-access `std::sort` path in this run for the generated data, especially at the largest size.
- `std::deque` had the lowest split time for the larger datasets, while its sorting time was higher than the other containers in this run.
- `std::vector` remains the reference implementation from `v0.2`; the comparison shows that actual performance depends on the operation being measured and the data size.
- These results are environment-dependent. Repeating the benchmark on another machine or under a different system load may produce different timings.

## Reproducibility

Build the benchmark with:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -Wpedantic \
    container_benchmark.cpp Person.cpp -o container_benchmark
```

Run it for one input file with:

```bash
./container_benchmark generated_data/Students_100000.txt benchmark_output
```

The program prints CSV output with the columns:

```text
Container,Records,Passed,Failed,Read_ms,Sort_ms,Split_ms,Write_ms,Total_ms
```

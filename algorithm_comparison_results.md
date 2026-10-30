# v1.0 Algorithm Performance Comparison

This report compares the pre-refactoring implementation from commit `c95bce8` with the STL-algorithm implementation from stage 3. Both versions were compiled with `g++ -std=c++17 -O2 -Wall -Wextra -pedantic`, used the same generated input files, ran both strategies for `vector`, `list`, and `deque`, and included reading, sorting, splitting, writing, and total time.

## Important measurement note

The baseline run completed for 1,000, 10,000, 100,000, and 1,000,000 records. Its 10,000,000-record run did not finish within the available two-hour execution window, so no baseline value is invented for that size. The algorithm version completed all six 10,000,000-record cases successfully.

## Total time comparison for completed baseline sizes

| Records | Container | Strategy | Baseline total (ms) | Algorithm total (ms) | Change |
|---:|---|---:|---:|---:|---:|
| 1,000 | vector | 1 | 4.554 | 4.530 | -0.53% |
| 1,000 | vector | 2 | 8.244 | 4.210 | -48.93% |
| 1,000 | list | 1 | 3.939 | 3.983 | +1.12% |
| 1,000 | list | 2 | 3.978 | 3.990 | +0.30% |
| 1,000 | deque | 1 | 4.211 | 4.301 | +2.14% |
| 1,000 | deque | 2 | 5.976 | 4.321 | -27.69% |
| 10,000 | vector | 1 | 47.563 | 46.656 | -1.91% |
| 10,000 | vector | 2 | 459.771 | 43.853 | -90.46% |
| 10,000 | list | 1 | 41.543 | 40.032 | -3.64% |
| 10,000 | list | 2 | 41.427 | 39.784 | -3.97% |
| 10,000 | deque | 1 | 46.436 | 44.397 | -4.39% |
| 10,000 | deque | 2 | 219.994 | 44.355 | -79.84% |
| 100,000 | vector | 1 | 462.570 | 459.626 | -0.64% |
| 100,000 | vector | 2 | 38,093.089 | 445.848 | -98.83% |
| 100,000 | list | 1 | 400.988 | 399.786 | -0.30% |
| 100,000 | list | 2 | 405.139 | 431.487 | +6.50% |
| 100,000 | deque | 1 | 467.721 | 479.750 | +2.57% |
| 100,000 | deque | 2 | 17,889.148 | 465.536 | -97.40% |
| 1,000,000 | vector | 1 | 4,897.556 | 4,790.294 | -2.19% |
| 1,000,000 | vector | 2 | 3,826,103.003 | 4,745.844 | -99.88% |
| 1,000,000 | list | 1 | 4,189.321 | 4,125.795 | -1.52% |
| 1,000,000 | list | 2 | 4,197.833 | 4,226.456 | +0.68% |
| 1,000,000 | deque | 1 | 5,242.210 | 5,075.393 | -3.18% |
| 1,000,000 | deque | 2 | 2,478,795.678 | 5,039.047 | -99.80% |

## Algorithm version results for all five required sizes

| Records | Container | Strategy | Passed | Failed | Read ms | Sort ms | Split ms | Write ms | Total ms |
|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|
| 1,000 | vector | 1 | 494 | 506 | 1.932 | 0.401 | 0.148 | 2.048 | 4.530 |
| 1,000 | vector | 2 | 494 | 506 | 1.719 | 0.404 | 0.082 | 2.004 | 4.210 |
| 1,000 | list | 1 | 494 | 506 | 1.747 | 0.132 | 0.111 | 1.992 | 3.983 |
| 1,000 | list | 2 | 494 | 506 | 1.761 | 0.129 | 0.099 | 2.000 | 3.990 |
| 1,000 | deque | 1 | 494 | 506 | 1.722 | 0.454 | 0.103 | 2.021 | 4.301 |
| 1,000 | deque | 2 | 494 | 506 | 1.721 | 0.443 | 0.124 | 2.032 | 4.321 |
| 10,000 | vector | 1 | 4,991 | 5,009 | 19.260 | 5.870 | 1.775 | 19.751 | 46.656 |
| 10,000 | vector | 2 | 4,991 | 5,009 | 17.421 | 5.863 | 0.999 | 19.569 | 43.853 |
| 10,000 | list | 1 | 4,991 | 5,009 | 17.167 | 1.652 | 1.642 | 19.571 | 40.032 |
| 10,000 | list | 2 | 4,991 | 5,009 | 17.363 | 1.644 | 1.004 | 19.773 | 39.784 |
| 10,000 | deque | 1 | 4,991 | 5,009 | 16.819 | 6.672 | 1.033 | 19.872 | 44.397 |
| 10,000 | deque | 2 | 4,991 | 5,009 | 16.840 | 6.603 | 1.375 | 19.535 | 44.355 |
| 100,000 | vector | 1 | 50,122 | 49,878 | 174.278 | 77.603 | 16.522 | 191.223 | 459.626 |
| 100,000 | vector | 2 | 50,122 | 49,878 | 167.879 | 77.594 | 8.982 | 191.392 | 445.848 |
| 100,000 | list | 1 | 50,122 | 49,878 | 169.641 | 20.777 | 16.718 | 192.650 | 399.786 |
| 100,000 | list | 2 | 50,122 | 49,878 | 179.650 | 28.968 | 13.019 | 209.849 | 431.487 |
| 100,000 | deque | 1 | 50,122 | 49,878 | 185.417 | 91.102 | 11.024 | 192.202 | 479.750 |
| 100,000 | deque | 2 | 50,122 | 49,878 | 166.300 | 91.029 | 12.693 | 195.510 | 465.536 |
| 1,000,000 | vector | 1 | 502,669 | 497,331 | 1,686.590 | 1,031.417 | 144.365 | 1,927.921 | 4,790.294 |
| 1,000,000 | vector | 2 | 502,669 | 497,331 | 1,689.354 | 1,029.556 | 93.672 | 1,933.262 | 4,745.844 |
| 1,000,000 | list | 1 | 502,669 | 497,331 | 1,726.115 | 242.972 | 201.477 | 1,955.230 | 4,125.795 |
| 1,000,000 | list | 2 | 502,669 | 497,331 | 1,821.737 | 244.665 | 123.568 | 2,036.486 | 4,226.456 |
| 1,000,000 | deque | 1 | 502,669 | 497,331 | 1,757.418 | 1,248.558 | 113.637 | 1,955.776 | 5,075.393 |
| 1,000,000 | deque | 2 | 502,669 | 497,331 | 1,680.237 | 1,249.183 | 152.114 | 1,957.508 | 5,039.047 |
| 10,000,000 | vector | 1 | 5,025,211 | 4,974,789 | 17,653.170 | 12,953.882 | 1,705.834 | 19,269.278 | 51,582.164 |
| 10,000,000 | vector | 2 | 5,025,211 | 4,974,789 | 17,440.870 | 12,912.964 | 940.476 | 19,339.582 | 50,633.893 |
| 10,000,000 | list | 1 | 5,025,211 | 4,974,789 | 17,382.047 | 3,073.249 | 2,063.790 | 19,477.839 | 41,996.925 |
| 10,000,000 | list | 2 | 5,025,211 | 4,974,789 | 18,206.820 | 3,127.989 | 1,262.045 | 20,313.439 | 42,910.293 |
| 10,000,000 | deque | 1 | 5,025,211 | 4,974,789 | 17,516.741 | 16,032.797 | 1,142.138 | 19,445.157 | 54,136.839 |
| 10,000,000 | deque | 2 | 5,025,211 | 4,974,789 | 16,840.522 | 15,997.179 | 1,610.466 | 19,655.506 | 54,103.679 |

## Observations

- The algorithm version preserved the same passed/failed counts as the baseline for every completed comparison size.
- Strategy 2 is dramatically faster for `vector` and `deque` at large sizes because `std::stable_partition` avoids repeated middle erasures.
- For 1,000,000 records, `vector` Strategy 2 decreased from 3,826,103.003 ms to 4,745.844 ms, while `deque` Strategy 2 decreased from 2,478,795.678 ms to 5,039.047 ms.
- The 10,000,000-record algorithm results completed in approximately 42–54 seconds per container/strategy case; the baseline could not be completed within the available measurement window.
- These are single-run engineering measurements on the sandbox, so they document the observed trend rather than a statistical average.

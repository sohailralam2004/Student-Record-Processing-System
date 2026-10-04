#!/usr/bin/env python3
"""Large-data performance and correctness test for Student Record Processing System.

Examples:
    python3 tests/test_large_dataset.py
    python3 tests/test_large_dataset.py --students 1000000
    python3 tests/test_large_dataset.py --students 100000 --timeout 120

The test builds a temporary optimized binary, generates Students.txt in a
separate temporary directory, runs the program in file mode, and removes all
temporary files when it finishes. The repository's Students.txt is untouched.
"""

from __future__ import annotations

import argparse
import os
from pathlib import Path
import resource
import shutil
import subprocess
import sys
import tempfile
import time


ROOT = Path(__file__).resolve().parents[1]
SOURCE_FILES = [ROOT / "main.cpp", ROOT / "Person.cpp", ROOT / "Person.h"]


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--students",
        type=int,
        default=100_000,
        help="number of generated students (default: 100000; try 1000000)",
    )
    parser.add_argument(
        "--timeout",
        type=float,
        default=120.0,
        help="maximum runtime in seconds (default: 120)",
    )
    parser.add_argument(
        "--keep-temp",
        action="store_true",
        help="keep generated files and output for inspection",
    )
    args = parser.parse_args()
    if args.students < 1:
        parser.error("--students must be at least 1")
    if args.timeout <= 0:
        parser.error("--timeout must be positive")
    return args


def generate_students(path: Path, count: int) -> None:
    """Generate reverse-sorted, deterministic records with five homework scores."""
    with path.open("w", encoding="utf-8") as data_file:
        data_file.write("Name Surname HW1 HW2 HW3 HW4 HW5 Exam\n")
        for index in range(count - 1, -1, -1):
            scores = [(index + offset) % 11 for offset in range(5)]
            exam = (index + 5) % 11
            data_file.write(
                f"Name{index:07d} Surname{index:07d} "
                f"{' '.join(map(str, scores))} {exam}\n"
            )


def build_binary(output: Path) -> None:
    command = [
        "g++",
        "-std=c++17",
        "-O2",
        "-Wall",
        "-Wextra",
        "-Wpedantic",
        str(ROOT / "main.cpp"),
        str(ROOT / "Person.cpp"),
        "-o",
        str(output),
    ]
    subprocess.run(command, check=True, cwd=ROOT)


def run_test(binary: Path, workdir: Path, output_path: Path, count: int, timeout: float) -> tuple[float, int]:
    started = time.perf_counter()
    with output_path.open("w", encoding="utf-8") as output_file:
        subprocess.run(
            [str(binary)],
            input="3\n",
            text=True,
            stdout=output_file,
            stderr=subprocess.PIPE,
            cwd=workdir,
            timeout=timeout,
            check=True,
        )
    elapsed = time.perf_counter() - started
    # Linux reports child peak RSS in KiB. On macOS it is bytes; this suite is
    # intended for Linux, but keep the conversion explicit for portability.
    peak_rss = resource.getrusage(resource.RUSAGE_CHILDREN).ru_maxrss
    if sys.platform == "darwin":
        peak_rss //= 1024
    return elapsed, int(peak_rss)


def validate_output(output_path: Path, count: int) -> None:
    lines = output_path.read_text(encoding="utf-8").splitlines()
    result_lines = [
        line for line in lines if " | " in line and "Final (Avg.)" not in line
    ]

    if len(result_lines) != count:
        raise AssertionError(
            f"expected {count} result rows, found {len(result_lines)}"
        )
    if not lines or f"{count} student records loaded and sorted by surname." not in lines[0]:
        raise AssertionError("file-load confirmation line is missing")

    first = result_lines[0]
    last = result_lines[-1]
    if "Name0000000" not in first or "Surname0000000" not in first:
        raise AssertionError("students are not sorted: first row is incorrect")
    last_index = count - 1
    if f"Name{last_index:07d}" not in last or f"Surname{last_index:07d}" not in last:
        raise AssertionError("students are not sorted: last row is incorrect")

    # Every row must contain both formatted final-grade columns.
    if any(line.count(" | ") != 1 for line in result_lines):
        raise AssertionError("one or more rows has invalid table formatting")


def main() -> int:
    args = parse_args()
    temp_context = tempfile.TemporaryDirectory(
        prefix="student-record-large-test-",
        dir=None,
        ignore_cleanup_errors=args.keep_temp,
    )
    temp_dir = Path(temp_context.name)

    try:
        binary = temp_dir / "students"
        data_file = temp_dir / "Students.txt"
        output_file = temp_dir / "program-output.txt"

        print(f"Generating {args.students:,} student records...", flush=True)
        generate_students(data_file, args.students)
        print("Compiling optimized test binary...", flush=True)
        build_binary(binary)
        print("Running file-input test...", flush=True)
        elapsed, peak_rss_kib = run_test(
            binary, temp_dir, output_file, args.students, args.timeout
        )
        validate_output(output_file, args.students)

        data_mb = data_file.stat().st_size / (1024 * 1024)
        output_mb = output_file.stat().st_size / (1024 * 1024)
        print("PASS: large-data correctness and performance test")
        print(f"  students:       {args.students:,}")
        print(f"  input size:     {data_mb:.2f} MiB")
        print(f"  output size:    {output_mb:.2f} MiB")
        print(f"  runtime:        {elapsed:.3f} seconds")
        print(f"  peak child RSS: {peak_rss_kib / 1024:.2f} MiB")
        print("  checks:         row count, sorting, formatting, file loading")
        if args.keep_temp:
            print(f"  temporary dir:  {temp_dir}")
            temp_context.cleanup = lambda: None  # type: ignore[method-assign]
        return 0
    except subprocess.TimeoutExpired:
        print(f"FAIL: process exceeded timeout ({args.timeout:.1f}s)", file=sys.stderr)
        return 1
    except (subprocess.CalledProcessError, AssertionError) as error:
        print(f"FAIL: {error}", file=sys.stderr)
        return 1
    finally:
        if not args.keep_temp:
            temp_context.cleanup()


if __name__ == "__main__":
    raise SystemExit(main())

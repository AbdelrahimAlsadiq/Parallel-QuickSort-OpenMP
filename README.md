# Parallel Quicksort Implementation

This project implements serial and parallel versions of the Quicksort algorithm in C++ using OpenMP for parallelization. Quicksort is a widely used sorting algorithm known for its efficiency, and parallelizing it can further improve its performance, especially for large datasets.

## Introduction

Quicksort is a comparison sort and is efficient in practice. It's widely used due to its relatively low constant factors and good average-case performance. However, the standard serial implementation of Quicksort may not utilize all available computational resources efficiently, especially on multi-core systems. 

This project aims to demonstrate the benefits of parallelizing Quicksort by implementing both serial and parallel versions and comparing their performance.

## Features

- **Serial Quicksort:** The serial version of the Quicksort algorithm implemented in C++.
- **Parallel Quicksort:** The parallel version of the Quicksort algorithm utilizing OpenMP for parallelization.
- **Dynamic Thread Management:** The parallel version dynamically manages the number of threads based on the available hardware concurrency.

## Usage

To use this project, follow these steps:

1. Clone the repository to your local machine.
2. Compile the source code using a C++ compiler with OpenMP support.
3. Run the executable generated after compilation.
4. Follow the on-screen instructions to choose the array size and, optionally, the number of threads for parallel execution.

Ensure that your system supports OpenMP for parallel execution. Most modern compilers support OpenMP, but you may need to enable it during compilation.

## Performance

The performance of both serial and parallel versions of Quicksort is evaluated using timing metrics. The project includes a test function that generates random arrays of various sizes and measures the time taken by both algorithms to sort these arrays.

You can run the provided test cases or specify custom array sizes and the number of threads for parallel execution.
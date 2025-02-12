# Self-Attention Optimization in C

This repository contains an implementation of the self-attention mechanism in C. I performed a series of optimizations to improve the performance of the implementation.

## Performance Profiling

All performance measurements were conducted using `perf`. To profile the code:

```bash
perf record ./attention
perf report
```

Initial profiling showed that 99.6% of execution time was spent in matrix multiplication operations, so this was the main focus of optimization efforts.

## Build and Run

There is a Makefile that can be used to build the attention and test binaries:
```bash
make all
```

To run the program, use the following command:
```bash
./attention
```

To run the tests:
```bash
./test
```

## Performance Journey

Starting from a baseline implementation, I was able to make the following improvements:

| Version | Time (seconds) | Speedup |
|---------|---------------|-------------|
| Baseline | ~20.0 | - |
| With -O3 | ~9.0 | 2.2x |
| Loop Reordering | ~0.8 | 25x |
| Parallel Matmul | ~0.13 | 153x |
| march=native | ~0.12 | 166x |
| Parallel Softmax + Scaling + Transpose | ~0.09 | 222x |

In the end we get a 222x speedup over the baseline implementation. Still 80% of time is spent in matrix multiplication, so potentially there is still room for improvement here. Another 10% or so is spent on overhead from the OpenMP parallelization.

## Other considered optimizations

### Strassen Algorithm

I was thinking about this but didn't implement because:
- The matrices I am using are non-square so the algorithm would have to be adjusted to handle that
- The maximum matrix size I am using is 2048x2048 and Strassen is only beneficial for very large matrices

### Tiling
- Attempted but performance got worse, not sure why maybe I have done it incorrectly

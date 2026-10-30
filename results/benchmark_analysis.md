# Performance Benchmark and Scalability Analysis

This report documents the performance evaluation conducted for **Experiment 2: Parallel Programming with POSIX Threads and OpenMP**.

## 1. Experimental Setup
- **Operating System:** Ubuntu Linux on WSL2 (Kernel: x86_64)
- **Compiler:** GCC 15.2.0 (`gcc -O2`, `-pthread`, `-fopenmp`)
- **Workload:** High-iteration numeric summation of $N = 100,000,000$ double-precision values.
- **Computed Result:** `49999999500.00`
- **Sequential Baseline Time ($T_s$):** `1.385656` seconds

---

## 2. Benchmark Comparison Table

| Threads ($p$) | Sequential Time ($T_s$) | Pthreads Time ($T_p$) | Pthreads Speedup ($S_p$) | Pthreads Efficiency ($E_p$) | OpenMP Time ($T_{omp}$) | OpenMP Speedup ($S_{omp}$) | OpenMP Efficiency ($E_{omp}$) |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **1** | 1.385656 s | 1.370635 s | 1.01x | 101.1% | 1.365853 s | 1.01x | 101.5% |
| **2** | 1.385656 s | 0.716545 s | 1.93x | 96.7% | 0.717964 s | 1.93x | 96.5% |
| **4** | 1.385656 s | 0.358445 s | 3.87x | 96.6% | 0.358842 s | 3.86x | 96.5% |
| **6** | 1.385656 s | 0.241560 s | 5.74x | 95.6% | 0.241392 s | 5.74x | 95.7% |
| **16** | 1.385656 s | 0.143211 s | 9.68x | 60.5% | 0.140732 s | 9.85x | 61.5% |

---

## 3. Metrics and Formulas

1. **Speedup ($S$):**
   $$S = \frac{T_s}{T_p}$$
   Represents how many times faster parallel execution is compared to sequential execution.

2. **Parallel Efficiency ($E$):**
   $$E = \frac{S}{p} \times 100\%$$
   Measures hardware resource utilization per worker thread.

---

## 4. Key Observations & Inferences

1. **Near-Linear Scaling (1 to 6 Threads):**
   - Both Pthreads and OpenMP exhibit outstanding parallel efficiency (>95%) scaling almost linearly from 1 to 6 threads.
   - At 4 threads, speedup is **~3.87x** (ideal is 4.0x).
   - At 6 threads, speedup reaches **~5.74x** (ideal is 6.0x).

2. **Scaling to 16 Threads & Diminishing Returns:**
   - At 16 threads, speedup increases to **9.85x** for OpenMP and **9.68x** for Pthreads, reducing runtime to **~0.140 seconds**.
   - The parallel efficiency drops to **~61%**, illustrating:
     - **Hyperthreading limitations:** Physical CPU cores vs Logical simultaneous multithreading (SMT) cores.
     - **Memory bandwidth saturation:** Multiple cores competing for shared cache and DRAM bus access.
     - **Thread synchronization overhead:** Fork/join and reduction overhead becoming a larger fraction of total runtime as execution time drops beneath 150 milliseconds.

3. **Pthreads vs. OpenMP Comparison:**
   - Both models deliver virtually identical runtime performance across all thread counts.
   - OpenMP achieves this with significantly fewer lines of code and cleaner loop annotations (`#pragma omp parallel for reduction`), whereas Pthreads requires explicit struct definitions, pointer conversions, thread pool iteration, and explicit joining.

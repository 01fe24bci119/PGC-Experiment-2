import matplotlib.pyplot as plt
import numpy as np
import os

# Ensure output directory exists
output_dir = os.path.dirname(os.path.abspath(__file__))

# Data
threads = np.array([1, 2, 4, 6, 16])
seq_time = 1.385656

pthread_time = np.array([1.370635, 0.716545, 0.358445, 0.241560, 0.143211])
omp_time = np.array([1.365853, 0.717964, 0.358842, 0.241392, 0.140732])

pthread_speedup = seq_time / pthread_time
omp_speedup = seq_time / omp_time
ideal_speedup = threads.copy().astype(float)

pthread_efficiency = (pthread_speedup / threads) * 100
omp_efficiency = (omp_speedup / threads) * 100

# Plot configuration for clean, professional look
plt.rcParams.update({
    'font.size': 11,
    'axes.labelsize': 12,
    'axes.titlesize': 13,
    'xtick.labelsize': 10,
    'ytick.labelsize': 10,
    'legend.fontsize': 10,
    'figure.titlesize': 14,
    'lines.linewidth': 2.2,
    'lines.markersize': 7
})

# ----------------------------------------------------
# 1. Execution Time Graph
# ----------------------------------------------------
plt.figure(figsize=(8, 5), dpi=300)
plt.axhline(y=seq_time, color='#e74c3c', linestyle='--', label=f'Sequential Baseline ({seq_time:.2f}s)')
plt.plot(threads, pthread_time, marker='o', color='#2980b9', label='POSIX Threads (Pthreads)')
plt.plot(threads, omp_time, marker='s', color='#27ae60', linestyle='-.', label='OpenMP')

for t, pt, ot in zip(threads, pthread_time, omp_time):
    plt.annotate(f"{pt:.2f}s", (t, pt), textcoords="offset points", xytext=(-10, 8), ha='center', fontsize=9, color='#2980b9')
    if t == 16:
        plt.annotate(f"{ot:.2f}s", (t, ot), textcoords="offset points", xytext=(15, -12), ha='center', fontsize=9, color='#27ae60')

plt.title('Execution Time vs Number of Threads (Workload: 10^8 elements)')
plt.xlabel('Number of Threads')
plt.ylabel('Execution Time (seconds)')
plt.xticks(threads)
plt.grid(True, linestyle=':', alpha=0.6)
plt.legend(frameon=True, facecolor='white', framealpha=0.9)
plt.tight_layout()
plt.savefig(os.path.join(output_dir, 'execution_time_comparison.png'))
plt.close()

# ----------------------------------------------------
# 2. Speedup Comparison Graph
# ----------------------------------------------------
plt.figure(figsize=(8, 5), dpi=300)
plt.plot(threads, ideal_speedup, color='#95a5a6', linestyle='--', label='Ideal Linear Speedup (S = p)')
plt.plot(threads, pthread_speedup, marker='o', color='#2980b9', label='Pthreads Speedup')
plt.plot(threads, omp_speedup, marker='^', color='#27ae60', label='OpenMP Speedup')

for t, sp, so in zip(threads, pthread_speedup, omp_speedup):
    plt.annotate(f"{sp:.2f}x", (t, sp), textcoords="offset points", xytext=(-12, 8), ha='center', fontsize=9, color='#2980b9')
    if t == 16:
        plt.annotate(f"{so:.2f}x", (t, so), textcoords="offset points", xytext=(15, -10), ha='center', fontsize=9, color='#27ae60')

plt.title('Parallel Speedup vs Number of Threads')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup Factor (S = Ts / Tp)')
plt.xticks(threads)
plt.yticks(range(0, 18, 2))
plt.grid(True, linestyle=':', alpha=0.6)
plt.legend(frameon=True, facecolor='white', framealpha=0.9)
plt.tight_layout()
plt.savefig(os.path.join(output_dir, 'speedup_comparison.png'))
plt.close()

# ----------------------------------------------------
# 3. Efficiency Comparison Graph
# ----------------------------------------------------
plt.figure(figsize=(8, 5), dpi=300)
plt.axhline(y=100, color='#95a5a6', linestyle='--', label='Ideal Efficiency (100%)')
plt.plot(threads, pthread_efficiency, marker='o', color='#2980b9', label='Pthreads Efficiency')
plt.plot(threads, omp_efficiency, marker='D', color='#27ae60', linestyle='-.', label='OpenMP Efficiency')

for t, ep, eo in zip(threads, pthread_efficiency, omp_efficiency):
    plt.annotate(f"{ep:.1f}%", (t, ep), textcoords="offset points", xytext=(-10, 8), ha='center', fontsize=9, color='#2980b9')

plt.title('Parallel Efficiency vs Number of Threads')
plt.xlabel('Number of Threads')
plt.ylabel('Efficiency (%) [E = (S / p) * 100]')
plt.xticks(threads)
plt.ylim(40, 115)
plt.grid(True, linestyle=':', alpha=0.6)
plt.legend(frameon=True, facecolor='white', framealpha=0.9)
plt.tight_layout()
plt.savefig(os.path.join(output_dir, 'efficiency_comparison.png'))
plt.close()

# ----------------------------------------------------
# 4. Combined 3-in-1 Dashboard
# ----------------------------------------------------
fig, axes = plt.subplots(1, 3, figsize=(18, 5.5), dpi=300)

# Subplot 1: Runtime
axes[0].axhline(y=seq_time, color='#e74c3c', linestyle='--', label=f'Sequential ({seq_time:.2f}s)')
axes[0].plot(threads, pthread_time, marker='o', color='#2980b9', label='Pthreads')
axes[0].plot(threads, omp_time, marker='s', color='#27ae60', linestyle='-.', label='OpenMP')
axes[0].set_title('A. Execution Time (s)')
axes[0].set_xlabel('Thread Count')
axes[0].set_ylabel('Time in Seconds')
axes[0].set_xticks(threads)
axes[0].grid(True, linestyle=':', alpha=0.6)
axes[0].legend(frameon=True)

# Subplot 2: Speedup
axes[1].plot(threads, ideal_speedup, color='#95a5a6', linestyle='--', label='Ideal Linear')
axes[1].plot(threads, pthread_speedup, marker='o', color='#2980b9', label='Pthreads')
axes[1].plot(threads, omp_speedup, marker='^', color='#27ae60', label='OpenMP')
axes[1].set_title('B. Speedup Factor (Ts / Tp)')
axes[1].set_xlabel('Thread Count')
axes[1].set_ylabel('Speedup (x)')
axes[1].set_xticks(threads)
axes[1].set_yticks(range(0, 18, 2))
axes[1].grid(True, linestyle=':', alpha=0.6)
axes[1].legend(frameon=True)

# Subplot 3: Efficiency
axes[2].axhline(y=100, color='#95a5a6', linestyle='--', label='Ideal (100%)')
axes[2].plot(threads, pthread_efficiency, marker='o', color='#2980b9', label='Pthreads')
axes[2].plot(threads, omp_efficiency, marker='D', color='#27ae60', linestyle='-.', label='OpenMP')
axes[2].set_title('C. Parallel Efficiency (%)')
axes[2].set_xlabel('Thread Count')
axes[2].set_ylabel('Efficiency (%)')
axes[2].set_xticks(threads)
axes[2].set_ylim(40, 115)
axes[2].grid(True, linestyle=':', alpha=0.6)
axes[2].legend(frameon=True)

plt.suptitle('PGC Experiment 2: Comprehensive Multi-Core Scaling Dashboard (N = 100M)', fontsize=15, y=0.98)
plt.tight_layout()
plt.subplots_adjust(top=0.88)
plt.savefig(os.path.join(output_dir, 'combined_scaling_dashboard.png'))
plt.close()

print("All benchmark graphs successfully generated!")

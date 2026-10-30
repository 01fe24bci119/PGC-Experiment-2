CC = gcc
CFLAGS = -Wall -O2
PTHREAD_FLAGS = -pthread
OMP_FLAGS = -fopenmp

SRC_DIR = src
BIN_DIR = bin

PTHREAD_SRCS = $(wildcard $(SRC_DIR)/section1_pthreads/*.c)
PTHREAD_BINS = $(patsubst $(SRC_DIR)/section1_pthreads/%.c, $(BIN_DIR)/%, $(PTHREAD_SRCS))

OMP_SRCS = $(wildcard $(SRC_DIR)/section2_openmp/*.c)
OMP_BINS = $(patsubst $(SRC_DIR)/section2_openmp/%.c, $(BIN_DIR)/%, $(OMP_SRCS))

PERF_SRCS = $(wildcard $(SRC_DIR)/section3_performance/*.c)
PERF_BINS = $(patsubst $(SRC_DIR)/section3_performance/%.c, $(BIN_DIR)/%, $(PERF_SRCS))

ALL_BINS = $(PTHREAD_BINS) $(OMP_BINS) $(PERF_BINS)

.PHONY: all clean init section1 section2 section3

all: init $(ALL_BINS)

init:
	@mkdir -p $(BIN_DIR)

# Section 1: Pthreads targets
$(BIN_DIR)/thread1: $(SRC_DIR)/section1_pthreads/thread1.c
	$(CC) $(CFLAGS) $< -o $@ $(PTHREAD_FLAGS)

$(BIN_DIR)/thread2: $(SRC_DIR)/section1_pthreads/thread2.c
	$(CC) $(CFLAGS) $< -o $@ $(PTHREAD_FLAGS)

$(BIN_DIR)/thread_sum: $(SRC_DIR)/section1_pthreads/thread_sum.c
	$(CC) $(CFLAGS) $< -o $@ $(PTHREAD_FLAGS)

$(BIN_DIR)/race: $(SRC_DIR)/section1_pthreads/race.c
	$(CC) $(CFLAGS) $< -o $@ $(PTHREAD_FLAGS)

$(BIN_DIR)/mutex: $(SRC_DIR)/section1_pthreads/mutex.c
	$(CC) $(CFLAGS) $< -o $@ $(PTHREAD_FLAGS)

# Section 2: OpenMP targets
$(BIN_DIR)/omp1: $(SRC_DIR)/section2_openmp/omp1.c
	$(CC) $(CFLAGS) $< -o $@ $(OMP_FLAGS)

$(BIN_DIR)/omp_sum: $(SRC_DIR)/section2_openmp/omp_sum.c
	$(CC) $(CFLAGS) $< -o $@ $(OMP_FLAGS)

$(BIN_DIR)/omp_race: $(SRC_DIR)/section2_openmp/omp_race.c
	$(CC) $(CFLAGS) $< -o $@ $(OMP_FLAGS)

$(BIN_DIR)/omp_critical: $(SRC_DIR)/section2_openmp/omp_critical.c
	$(CC) $(CFLAGS) $< -o $@ $(OMP_FLAGS)

$(BIN_DIR)/omp_barrier: $(SRC_DIR)/section2_openmp/omp_barrier.c
	$(CC) $(CFLAGS) $< -o $@ $(OMP_FLAGS)

# Section 3: Performance Benchmark targets
$(BIN_DIR)/sequential: $(SRC_DIR)/section3_performance/sequential.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/pthread_perf: $(SRC_DIR)/section3_performance/pthread_perf.c
	$(CC) $(CFLAGS) $< -o $@ $(PTHREAD_FLAGS)

$(BIN_DIR)/omp_perf: $(SRC_DIR)/section3_performance/omp_perf.c
	$(CC) $(CFLAGS) $< -o $@ $(OMP_FLAGS)

section1: init $(PTHREAD_BINS)
section2: init $(OMP_BINS)
section3: init $(PERF_BINS)

clean:
	rm -rf $(BIN_DIR)

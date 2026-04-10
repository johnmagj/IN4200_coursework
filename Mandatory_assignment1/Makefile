ifeq ($(OS),Windows_NT)
    EXT = .exe
else
    EXT =
endif

EXECUTABLE = main$(EXT)

CODE_FILES = main.c \
		read_sparse_matrix_from_file.c \
		sampled_matrix_multiplication_coo.c \
		translate_coo_to_crs.c \
		sampled_matrix_multiplication_crs.c

all: build run

build:
	gcc $(CODE_FILES) -o $(EXECUTABLE)

run:
	./$(EXECUTABLE)

all_openmp: build_openmp run_openmp

build_openmp:
	gcc -fopenmp $(CODE_FILES) -o $(EXECUTABLE)

run_openmp:
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
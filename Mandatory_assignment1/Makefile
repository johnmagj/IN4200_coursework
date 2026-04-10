ifeq ($(OS),Windows_NT)
    EXT = .exe
else
    EXT =
endif

all: build run

build:
	gcc main.c \
	read_sparse_matrix_from_file.c \
	sampled_matrix_multiplication_coo.c \
	translate_coo_to_crs.c \
	sampled_matrix_multiplication_crs.c \
	-o main$(EXT)

run:
	.\main$(EXT)
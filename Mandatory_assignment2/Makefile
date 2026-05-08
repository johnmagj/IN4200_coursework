ifeq ($(OS),Windows_NT)
    EXT = .exe
	RM = del /Q /F
else
    EXT =
	RM = rm -f
endif

CC = gcc
MPICC = mpicc

EXECUTABLE_SERIAL = serial_code/serial_main$(EXT)

EXECUTABLE_PARALLEL = parallel_code/parallel_main$(EXT)

CODE_FILES_SERIAL = serial_code/serial_main.c \
		iso_diffusion_denoising.c

CODE_FILES_PARALLEL = parallel_code/parallel_main.c \
		iso_diffusion_denoising_parallel.c

CODE_FILES_SHARED = example_folder/simple-jpeg/import_export_jpeg.c \
		allocate_image.c \
		convert_jpeg_to_image.c \
		convert_image_to_jpeg.c \
		deallocate_image.c

all_serial: build_serial run_serial

build_serial:
	$(CC) $(CODE_FILES_SERIAL) $(CODE_FILES_SHARED) -o $(EXECUTABLE_SERIAL) -ljpeg

run_serial:
	./$(EXECUTABLE_SERIAL) 0.05 100 mona_lisa_noisy.jpg outfile_serial.jpg


all_parallel: build_parallel run_parallel

build_parallel:
	$(MPICC) $(CODE_FILES_PARALLEL) $(CODE_FILES_SHARED) -o $(EXECUTABLE_PARALLEL) -ljpeg

run_parallel:
	mpiexec -n 4 ./$(EXECUTABLE_PARALLEL) 0.05 100 mona_lisa_noisy.jpg test_outfile_parallel.jpg

clean:
	-$(RM) $(EXECUTABLE_SERIAL) $(EXECUTABLE_PARALLEL)


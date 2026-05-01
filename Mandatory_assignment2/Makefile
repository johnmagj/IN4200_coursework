ifeq ($(OS),Windows_NT)
    EXT = .exe
else
    EXT =
endif

EXECUTABLE = serial_code/serial_main$(EXT)

CODE_FILES = serial_code/serial_main.c \
		example_folder/simple-jpeg/import_export_jpeg.c \
		allocate_image.c \
		convert_jpeg_to_image.c \
		iso_diffusion_denoising.c \
		convert_image_to_jpeg.c \
		deallocate_image.c

all: build run

build:
	gcc $(CODE_FILES) -o $(EXECUTABLE) -ljpeg

run:
	./$(EXECUTABLE) 0.05 100 mona_lisa_noisy.jpg outfile.jpg

# all_openmp: build_openmp run_openmp

# build_openmp:
# 	gcc -fopenmp $(CODE_FILES) -o $(EXECUTABLE)

# run_openmp:
# 	./$(EXECUTABLE)

# clean:
# 	rm -f $(EXECUTABLE)
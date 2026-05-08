Note regarding the external library:
Had to remove jpeglib.h, jconfig.h, and jmorecfg.h from the external library due to them causing problems on Windows 11 with MSYS2 UCRT64 with libjpeg-turbo version 80. 
Tried to change the line: #define JPEG_LIB_VERSION  62	/* Version 6b */
in jpeglib.h, but this did cause other compatibility issues.
Now gcc is forced to solely use version 80 headers already installed in the MSYS2 system.

Makefile supplied to run both the serial and parallel code on example image, 100 iterations. Should be cross os compatible.

Build and run serial with: all_serial

Build and run parallel code with: all_parallel

Comment to code:
There is a big logical issue in the parallel code. The retrieved arrays the image processing are not sliced, therefore the halo values are also returned. This would most likely cause problems for the result.
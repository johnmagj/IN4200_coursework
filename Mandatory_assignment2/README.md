Note:
Regarding the external library:
Had to remove jpeglib.h, jconfig.h, and jmorecfg.h from the external library due to causing problems on Windows 11 with MSYS2 UCRT64 with libjpeg-turbo version 80. 
Tried to change the line: #define JPEG_LIB_VERSION  62	/* Version 6b */
in jpeglib.h, but did cause other compatibility issues.
Now gcc is forced to solely use version 80 headers already installed in the MSYS2 system

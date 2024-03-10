#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//PNG header and footer
unsigned char PNG_HEADER[] = {0x89, 0x50, 0x4e, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
unsigned char PNG_FOOTER[] = {0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82};

// JPEG header and footer
unsigned char JPEG_HEADER[] = {0xFF, 0xD8};
unsigned char JPEG_FOOTER[] = {0xFF, 0xD9};

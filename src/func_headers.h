
#ifndef FUNC_HEADERS_H
#define FUNC_HEADERS_H
#include "bmp_reader.h"
#include <vector>
#include <string>

bool saveBMPFile(const char* fname, BMPFile* bmp_file);

void rotate90(BMPFile* bmpf);
void printBMPHeaders(BMPFile* bmp_file);
void printpixels(BMPFile* bmp_file);
void rotate270(BMPFile* bmpf);



#endif

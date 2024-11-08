/* Ilya Pavlov st129535@student.spbu.ru
	lab-work-1
*/
#ifndef FUNC_HEADERS_H
#define FUNC_HEADERS_H
#include "bmp_reader.h"
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>

bool saveBMPFile(const char* fname, BMPFile* bmp_file);

void rotate90(const char* fname,BMPFile* bmpf);
void printBMPHeaders(BMPFile* bmp_file);
void printpixels(BMPFile* bmp_file);
void rotate270(const char* fname,BMPFile* bmpf);



#endif

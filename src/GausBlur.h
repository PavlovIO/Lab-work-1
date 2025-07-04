/* Ilya Pavlov st129535@student.spbu.ru
	lab-work-1
*/
#ifndef GAUSBLUR_H
#define GAUSBLUR_H
#include "bmp_reader.h"

std::vector<std::vector<float>> createGaussianKernel(int size, float sigma);
void applyGaussianBlur(const std::vector<unsigned int>& inputChannel, std::vector<unsigned int>& outputChannel,
                       int width, int height, const std::vector<std::vector<float>>& kernel);
void applyGaussianBlurParallel(const std::vector<unsigned int>& inputChannel, std::vector<unsigned int>& outputChannel, int width, int height, const std::vector<std::vector<float>>& kernel, int startY, int endY);


#endif

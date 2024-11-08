
#ifndef GAUSBLUR_H
#define GAUSBLUR_H
#include "func_headers.h"

std::vector<std::vector<float>> createGaussianKernel(int size, float sigma);
void applyGaussianBlur(const std::vector<unsigned int>& inputChannel, std::vector<uint8_t>& outputChannel,
                       int width, int height, const std::vector<std::vector<float>>& kernel);

void gaussianBlurImage(
    std::vector<unsigned int>& blueChannel,
    std::vector<unsigned int>& greenChannel,
    std::vector<unsigned int>& redChannel,
    std::vector<unsigned int>& alphaChannel,
    int width, int height, int kernelSize = 3, float sigma = 1.0f
);


void extractChannels(
    BMPFile* bmpFile,
    std::vector<unsigned int>& blueChannel,
    std::vector<unsigned int>& greenChannel,
    std::vector<unsigned int>& redChannel,
    std::vector<unsigned int>& alphaChannel // останется пустым, если альфа-канал отсутствует
);

char* mergeChannels(
    const std::vector<unsigned int>& blueChannel,
    const std::vector<unsigned int>& greenChannel,
    const std::vector<unsigned int>& redChannel,
    const std::vector<unsigned int>& alphaChannel, // пустой, если альфа отсутствует
    int width, int height
);
#endif

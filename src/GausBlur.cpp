/* Ilya Pavlov st129535@student.spbu.ru
	lab-work-1
*/
#include "GausBlur.h"


// Создание гауссова ядра
std::vector<std::vector<float>> createGaussianKernel(int size, float sigma)
{
    std::vector<std::vector<float>> kernel(size, std::vector<float>(size));
    float sum = 0.0;
    int half = size / 2;

    for (int y = -half; y <= half; ++y)
    {
        for (int x = -half; x <= half; ++x)
        {
            float value = std::exp(-(x * x + y * y) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            kernel[y + half][x + half] = value;
            sum += value;
        }
    }

    // Нормализация ядра
    for (int y = 0; y < size; ++y)
        for (int x = 0; x < size; ++x)
            kernel[y][x] /= sum;

    return kernel;
}

// Применение гауссова размытия к каналу
void applyGaussianBlur(const std::vector<unsigned int>& inputChannel, std::vector<unsigned int>& outputChannel,
                       int width, int height, const std::vector<std::vector<float>>& kernel)
{
    int half = kernel.size() / 2;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            float blurredValue = 0.0;

            // Применяем ядро к пикселю и его соседям
            for (int ky = -half; ky <= half; ++ky)
            {
                for (int kx = -half; kx <= half; ++kx)
                {
                    int nx = std::min(std::max(x + kx, 0), width - 1);   // Граничное ограничение по X
                    int ny = std::min(std::max(y + ky, 0), height - 1);  // Граничное ограничение по Y
                    blurredValue += inputChannel[ny * width + nx] * kernel[ky + half][kx + half];
                }
            }

            // Ограничиваем значение в пределах [0, 255] и сохраняем
            outputChannel[y * width + x] = static_cast<uint8_t>(std::min(std::max(int(blurredValue), 0), 255));
        }
    }
}

// Основная функция для размытия всех каналов изображения
void gaussianBlurImage(
    std::vector<unsigned int>& blueChannel,
    std::vector<unsigned int>& greenChannel,
    std::vector<unsigned int>& redChannel,
    std::vector<unsigned int>& alphaChannel,
    BMPFile& bmp_file, int kernelSize = 7, float sigma = 1.0f
)
{
    int width = static_cast<int>(bmp_file.dhdr._width);
    int height = static_cast<int>(bmp_file.dhdr._height);
    auto kernel = createGaussianKernel(kernelSize, sigma);

    // Создаем выходные векторы
    std::vector<unsigned int> blurredBlue(width * height);
    std::vector<unsigned int> blurredGreen(width * height);
    std::vector<unsigned int> blurredRed(width * height);
    std::vector<unsigned int> blurredAlpha;

    if (!alphaChannel.empty())
    {
        blurredAlpha.resize(width * height);
    }

    // Применяем гауссово размытие к каждому каналу
    applyGaussianBlur(blueChannel, blurredBlue, width, height, kernel);
    applyGaussianBlur(greenChannel, blurredGreen, width, height, kernel);
    applyGaussianBlur(redChannel, blurredRed, width, height, kernel);
    if (!alphaChannel.empty())
    {
        applyGaussianBlur(alphaChannel, blurredAlpha, width, height, kernel);
    }

    // Обновляем оригинальные каналы с размытыми данными
    blueChannel = blurredBlue;
    greenChannel = blurredGreen;
    redChannel = blurredRed;
    if (!alphaChannel.empty())
    {
        alphaChannel = blurredAlpha;
    }
}


void BMPFile::extractChannels(
    std::vector<unsigned int>& blueChannel,
    std::vector<unsigned int>& greenChannel,
    std::vector<unsigned int>& redChannel,
    std::vector<unsigned int>& alphaChannel // останется пустым, если альфа-канал отсутствует
)
{
    int width = dhdr._width;
    int height = dhdr._height;
    int bytesPerPixel = dhdr._bits_per_pixel / 8;
    bool hasAlpha = (bytesPerPixel == 4); // Проверка на альфа-канал

    // Рассчитываем фактический размер строки, включая паддинг
    int rowSize = (width * bytesPerPixel + 3) & ~3;

    // Резервируем память для векторов каналов
    blueChannel.resize(width * height);
    greenChannel.resize(width * height);
    redChannel.resize(width * height);
    if (hasAlpha)
    {
        alphaChannel.resize(width * height);
    }

    // Проход по каждому пикселю
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // Индекс начала пикселя в строке
            int pixelIndex = y * rowSize + x * bytesPerPixel;

            // Запись данных о каждом канале, преобразованных в unsigned int
            blueChannel[y * width + x] = static_cast<unsigned int>(static_cast<unsigned char>(_data[pixelIndex]));
            greenChannel[y * width + x] = static_cast<unsigned int>(static_cast<unsigned char>(_data[pixelIndex + 1]));
            redChannel[y * width + x] = static_cast<unsigned int>(static_cast<unsigned char>(_data[pixelIndex + 2]));
            if (hasAlpha)
            {
                alphaChannel[y * width + x] = static_cast<unsigned int>(static_cast<unsigned char>(_data[pixelIndex + 3]));
            }
        }
    }
}




void BMPFile::mergeChannels(
    const std::vector<unsigned int>& blueChannel,
    const std::vector<unsigned int>& greenChannel,
    const std::vector<unsigned int>& redChannel,
    const std::vector<unsigned int>& alphaChannel // пустой, если альфа отсутствует
)
{
    int width = static_cast<int>(dhdr._width);
    int height = static_cast<int>(dhdr._height);
    int bytesPerPixel = alphaChannel.empty() ? 3 : 4;
    int rowSize = (width * bytesPerPixel + 3) & ~3;  // Размер строки с учетом паддинга
    char* mergedData = new char[rowSize * height];   // Итоговый массив данных с учетом паддинга

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int pixelIndex = y * rowSize + x * bytesPerPixel;
            int channelIndex = y * width + x;

            // Записываем значения каналов в итоговый массив данных
            mergedData[pixelIndex] = static_cast<char>(blueChannel[channelIndex]);
            mergedData[pixelIndex + 1] = static_cast<char>(greenChannel[channelIndex]);
            mergedData[pixelIndex + 2] = static_cast<char>(redChannel[channelIndex]);
            if (bytesPerPixel == 4)
            {
                mergedData[pixelIndex + 3] = static_cast<char>(alphaChannel[channelIndex]);
            }
        }
    }

    _data=mergedData;
}













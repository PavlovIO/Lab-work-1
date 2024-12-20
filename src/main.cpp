/* Ilya Pavlov st129535@student.spbu.ru
	lab-work-1
*/

#include "GausBlur.h"

int main()
{
    // Указываем имя BMP файла для теста
    std::cout<<"Введите название файла: ";
    std::string bmp_filename;
    std::cin>>bmp_filename;

    // Загружаем BMP файл
    BMPFile bmp_file;
    bmp_file.loadBMPFile(bmp_filename);
    
    bmp_file.saveBMPFile("image.bmp");

    bmp_file.rotate90("90clock");
    bmp_file.rotate270("90aclock");

    std::vector<unsigned int> blue, green,red,alpha;
    bmp_file.extractChannels(blue,green,red,alpha);

    std::cout<<"Введите размер ядра(нечетное значение): ";
    int kernel_size;
    std::cin >> kernel_size;

    std::cout<<"Введите силу размытия(значение сигмы): ";
    int input;
    std::cin >> input;
    float sigma = static_cast<float>(input);

    gaussianBlurImage(blue, green, red, alpha, bmp_file, kernel_size, sigma);

    bmp_file.freeBMPFile();
    bmp_file.mergeChannels(blue,green,red,alpha);///

    bmp_file.saveBMPFile("blurred_image.bmp");

    bmp_file.rotate90("90clockblur");
    bmp_file.rotate270("90aclockblur");

    // Освобождаем память
    bmp_file.freeBMPFile();

    return 0;
}




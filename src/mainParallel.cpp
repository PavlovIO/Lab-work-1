/* Ilya Pavlov st129535@student.spbu.ru
	lab-work-1
*/

#include "GausBlur.h"

int main( int argc, char* argv[])
{
    if(argc < 4)
    {
        std::cout<<"Usage: ./output <file_name> <int(kernel size)> <float(sigma)>"<<std::endl;
        return 0;
    }
    
    std::string bmp_filename = argv[1];
    std::string kernel_input = argv[2];
    std::string sigma_input = argv[3];

    try
    {
        int kernel_size = std::stof(kernel_input);
        float sigma = std::stof(sigma_input);

        // Загружаем BMP файл
        BMPFile bmp_file;
        bmp_file.loadBMPFile(bmp_filename);

        bmp_file.saveBMPFile("image.bmp");

        bmp_file.rotate90("90clock");
        bmp_file.rotate270("90aclock");

        std::vector<unsigned int> blue, green,red,alpha;
        bmp_file.extractChannels(blue,green,red,alpha);

        gaussianBlurImageParallel(blue, green, red, alpha, bmp_file, kernel_size, sigma);

        bmp_file.freeBMPFile();
        bmp_file.mergeChannels(blue,green,red,alpha);///

        bmp_file.saveBMPFile("blurred_image.bmp");

        bmp_file.rotate90Parallel("90clockblur");
        bmp_file.rotate270Parallel("90aclockblur");

        // Освобождаем память
        bmp_file.freeBMPFile();

        return 0;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << "Invalid kernel_size(int) and sigma(float) arguments" << std::endl;
        return 1;
    }
    catch(...)
    {
        std::cerr << "Unidentified error" << std::endl;
        return 1;
    }
}




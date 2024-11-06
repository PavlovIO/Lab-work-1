/* Ilya Pavlov st129535@student.spbu.ru
	lab-work-1
*/
#include "bmp_reader.h"
#include "func_headers.h"

void printBMPHeaders(BMPFile* bmp_file)
{
// Выводим информацию о заголовке BMP
    std::cout << "BMP Header:" << std::endl;
    std::cout << "ID: " << bmp_file->bhdr._id[0] << bmp_file->bhdr._id[1] << std::endl;
    std::cout << "File size: " << bmp_file->bhdr._file_size << " bytes" << std::endl;
    std::cout << "Pixel offset: " << bmp_file->bhdr._pixel_offset << std::endl;

    // Выводим информацию о DIB заголовке
    std::cout << "\nDIB Header:" << std::endl;
    std::cout << "Header size: " << bmp_file->dhdr._header_size << " bytes" << std::endl;
    std::cout << "Width: " << bmp_file->dhdr._width << " pixels" << std::endl;
    std::cout << "Height: " << bmp_file->dhdr._height << " pixels" << std::endl;
    std::cout << "Color planes: " << bmp_file->dhdr._color_planes << std::endl;
    std::cout << "Bits per pixel: " << bmp_file->dhdr._bits_per_pixel << std::endl;
    std::cout << "Compression type: " << bmp_file->dhdr._compression << std::endl;
    std::cout << "Data size: " << bmp_file->dhdr._data_size << " bytes" << std::endl;
};

void printpixels(BMPFile* bmp_file)
{
    for (unsigned int i = 0; i<bmp_file->dhdr._data_size; ++i)
    {
        if (i%12 == 0)
        {
            std::cout<<""<<std::endl;
        };
        std::cout << std::hex << (static_cast<unsigned int>(static_cast<unsigned char>(bmp_file->_data[i]))) << " ";
    };

};

int main()
{
    // Указываем имя BMP файла для теста
    std::cout<<"Введите название файла: ";
    std::string bmp_filename;
    std::cin>>bmp_filename;
    // Загружаем BMP файл
    BMPFile* bmp_file = loadBMPFile(bmp_filename);

    //printBMPHeaders(bmp_file);
    //printpixels(bmp_file);


    rotate90(bmp_file);
    rotate270(bmp_file);

    // Освобождаем память
    freeBMPFile(bmp_file);

    return 0;
}




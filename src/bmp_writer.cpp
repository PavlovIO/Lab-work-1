/* Ilya Pavlov st129535@student.spbu.ru
	lab-work-1
*/
#include "func_headers.h"

bool saveBMPFile(const char* fname, BMPFile* bmp_file)
{
    std::ofstream fp(fname, std::ios::binary);
    if (!fp)
    {
        std::cerr << "Can't open the file for writing" << std::endl;
        return 1;
    }

    // Записываем BMP заголовок
    fp.write(reinterpret_cast<char*>(&bmp_file->bhdr), sizeof(BMPHeader));

    // Записываем DIB заголовок
    fp.write(reinterpret_cast<char*>(&bmp_file->dhdr), sizeof(DIBHeader));

    // Данные пикселей

    unsigned int row_size = bmp_file->dhdr._width * 4;  // Размер строки без паддинга
    unsigned int padding = (4 - row_size % 4) % 4;  // Паддинг, чтобы строка была кратна 4


    for (unsigned int y = 0; y <= bmp_file->dhdr._height - 1 ; y++)
    {
        fp.write(reinterpret_cast<char*>(&bmp_file->_data[y * row_size]), row_size);

        if (padding > 0)
        {
            std::vector<char> padding_bytes(padding, '\0');  // Создаём вектор для паддинга
            fp.write(padding_bytes.data(), padding);  // Записываем паддинг
        };
    };

    // Закрываем файл
    fp.close();
    return 0;
}

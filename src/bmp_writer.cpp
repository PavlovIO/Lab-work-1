/* Ilya Pavlov st129535@student.spbu.ru
	lab-work-1
*/
#include "bmp_reader.h"

bool BMPFile::saveBMPFile(const std::string fname)
{
    std::ofstream fp(fname, std::ios::binary);
    if (!fp)
    {
        std::cerr << "Can't open the file for writing" << std::endl;
        return false;
    }

    // Записываем BMP заголовок
    fp.write(reinterpret_cast<char*>(&bhdr), sizeof(BMPHeader));

    // Записываем DIB заголовок
    fp.write(reinterpret_cast<char*>(&dhdr), sizeof(DIBHeader));

    // Данные пикселей

    unsigned int row_size = dhdr._width * 4;  // Размер строки без паддинга
    unsigned int padding = (4 - row_size % 4) % 4;  // Паддинг, чтобы строка была кратна 4


    for (unsigned int y = 0; y <= dhdr._height - 1 ; y++)
    {
        fp.write(reinterpret_cast<char*>(&_data[y * row_size]), row_size);

        if (padding > 0)
        {
            std::vector<char> padding_bytes(padding, '\0');  // Создаём вектор для паддинга
            fp.write(padding_bytes.data(), padding);  // Записываем паддинг
        };
    };

    // Закрываем файл
    fp.close();
    return true;
}

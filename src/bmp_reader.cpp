/* Ilya Pavlov st129535@student.spbu.ru
	lab-work-1
*/
#include "bmp_reader.h"


bool BMPFile::loadBMPFile(std::string fname)
{
    std::ifstream fp(fname, std::ios::binary);
    if (!fp)
    {
        std::cerr<<"Can't load the file"<<std::endl;
        return false;
    };

    //Читаем бмп хедер
    fp.read(reinterpret_cast<char*>(&bhdr), sizeof(bhdr));

    fp.read(reinterpret_cast<char*>(&dhdr), sizeof(dhdr));

    unsigned int rdatasize = ((dhdr._width * dhdr._bits_per_pixel + 31) / 32) * 4 * dhdr._height;

    if (dhdr._data_size != rdatasize)
    {
        dhdr._data_size = rdatasize;
    }

    _data = new char[dhdr._data_size];
    fp.seekg(bhdr._pixel_offset,std::ios::beg);
    fp.read(_data, dhdr._data_size);

    fp.close();
    return true;
};

bool BMPFile::freeBMPFile()
{
    delete[] _data;
    return true;
};


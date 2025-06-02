/* Ilya Pavlov st129535@student.spbu.ru
	lab-work-1
*/
#include "bmp_reader.h"
// normal rotation
void BMPFile::rotate90(const std::string fname)
{

    BMPFile bmpf90;

    bmpf90.bhdr = bhdr;
    bmpf90.dhdr = dhdr;

    bmpf90.dhdr._height = dhdr._width;
    bmpf90.dhdr._width = dhdr._height;

    bmpf90.dhdr._prheight = dhdr._prwidth;
    bmpf90.dhdr._prwidth = dhdr._prheight;

    unsigned int bpp = dhdr._bits_per_pixel/8;

    unsigned int row_size = dhdr._width*bpp;
    unsigned int padding = (4 - row_size % 4) % 4;

    unsigned int row_size90 = bmpf90.dhdr._width*bpp;
    unsigned int padding90 = (4 - row_size90 % 4) % 4;

    unsigned int data_size = row_size90 * bmpf90.dhdr._height + padding90 * bmpf90.dhdr._height;
    bmpf90._data = new char[data_size];

    unsigned int i90 = 0;
    for(unsigned int i = row_size; i>0; i-=bpp)
    {

        for(unsigned int j = 0; j<dhdr._height; j++)
        {
            bmpf90._data[i90] = _data[(i)-3+(row_size+padding)*(j)];
            bmpf90._data[i90+1] = _data[(i)-2+(row_size+padding)*(j)];
            bmpf90._data[i90+2] = _data[(i)-1+(row_size+padding)*(j)];
            i90+=3;

        };
        for(unsigned int p = 0; p<padding90; ++p)
        {
            bmpf90._data[i90+p] = 0;
        };
        i90+=padding90;
    };
    bmpf90.bhdr._file_size = bhdr._file_size-dhdr._data_size+data_size;
    bmpf90.dhdr._data_size = data_size;

    bmpf90.saveBMPFile(fname);
    bmpf90.freeBMPFile();


};

void BMPFile::rotate270(const std::string fname)
{

    BMPFile bmpf90;

    bmpf90.bhdr = bhdr;
    bmpf90.dhdr = dhdr;

    bmpf90.dhdr._height = dhdr._width;
    bmpf90.dhdr._width = dhdr._height;

    bmpf90.dhdr._prheight = dhdr._prwidth;
    bmpf90.dhdr._prwidth = dhdr._prheight;

    unsigned int bpp = dhdr._bits_per_pixel/8;

    unsigned int row_size = dhdr._width*bpp;
    unsigned int padding = (4 - row_size % 4) % 4;

    unsigned int row_size90 = bmpf90.dhdr._width*bpp;
    unsigned int padding90 = (4 - row_size90 % 4) % 4;

    unsigned int data_size = row_size90 * bmpf90.dhdr._height + padding90 * bmpf90.dhdr._height;
    bmpf90._data = new char[data_size];

    unsigned int i90 = 0;
    for(unsigned int i = 0; i<row_size ; i+=bpp)
    {

        for(unsigned int j = dhdr._height; j>0; j--)
        {
            bmpf90._data[i90] = _data[(i)+(row_size+padding)*(j-1)];
            bmpf90._data[i90+1] = _data[(i)+1+(row_size+padding)*(j-1)];
            bmpf90._data[i90+2] = _data[(i)+2+(row_size+padding)*(j-1)];
            i90+=3;
        };
        for(unsigned int p = 0; p<padding90; ++p)
        {
            bmpf90._data[i90+p] = 0;
        };
        i90+=padding90;
    };
    bmpf90.bhdr._file_size = bhdr._file_size-dhdr._data_size+data_size;
    bmpf90.dhdr._data_size = data_size;
    bmpf90.saveBMPFile(fname);
    bmpf90.freeBMPFile();
};

//parallel rotation
void BMPFile::rotate90Parallel(const std::string fname)
{

    BMPFile bmpf90;

    bmpf90.bhdr = bhdr;
    bmpf90.dhdr = dhdr;

    bmpf90.dhdr._height = dhdr._width;
    bmpf90.dhdr._width = dhdr._height;

    bmpf90.dhdr._prheight = dhdr._prwidth;
    bmpf90.dhdr._prwidth = dhdr._prheight;

    unsigned int bpp = dhdr._bits_per_pixel/8;

    unsigned int row_size = dhdr._width*bpp;
    unsigned int padding = (4 - row_size % 4) % 4;

    unsigned int row_size90 = bmpf90.dhdr._width*bpp;
    unsigned int padding90 = (4 - row_size90 % 4) % 4;

    unsigned int data_size = row_size90 * bmpf90.dhdr._height + padding90 * bmpf90.dhdr._height;
    bmpf90._data = new char[data_size];

    //added paralleling

    auto rotate_part = [&](unsigned int start, unsigned int end)
    {
        //added support for smaller chunks (start end)
        unsigned int i90 = start * row_size90;
        for(unsigned int i = row_size - start * bpp; i > row_size - end * bpp; i -= bpp)
        {

            for(unsigned int j = 0; j<dhdr._height; j++)
            {
                bmpf90._data[i90] = _data[(i)-3+(row_size+padding)*(j)];
                bmpf90._data[i90+1] = _data[(i)-2+(row_size+padding)*(j)];
                bmpf90._data[i90+2] = _data[(i)-1+(row_size+padding)*(j)];
                i90+=3;

            };
            for(unsigned int p = 0; p<padding90; ++p)
            {
                bmpf90._data[i90+p] = 0;
            };
            i90+=padding90;
        }
    };
    //initialized chunk_sizes for threads and vector of threads
    unsigned int num_threads = std::thread::hardware_concurrency();
    unsigned int chunk_size = dhdr._width / num_threads;
    std::vector<std::thread> threads;

    //loop with threads
    for(unsigned int t = 0; t < num_threads; ++t)
    {
        unsigned int start = t * chunk_size;
        unsigned int end = ( t == num_threads - 1 ) ? dhdr._width : start + chunk_size;
        threads.emplace_back(rotate_part, start, end);
    }
    //joining
    for(auto& thread : threads)
    {
        thread.join();
    }


    bmpf90.bhdr._file_size = bhdr._file_size-dhdr._data_size+data_size;
    bmpf90.dhdr._data_size = data_size;

    bmpf90.saveBMPFile(fname);
    bmpf90.freeBMPFile();


};

//same changes as rotate90Parallel
void BMPFile::rotate270Parallel(const std::string fname)
{

    BMPFile bmpf90;

    bmpf90.bhdr = bhdr;
    bmpf90.dhdr = dhdr;

    bmpf90.dhdr._height = dhdr._width;
    bmpf90.dhdr._width = dhdr._height;

    bmpf90.dhdr._prheight = dhdr._prwidth;
    bmpf90.dhdr._prwidth = dhdr._prheight;

    unsigned int bpp = dhdr._bits_per_pixel/8;

    unsigned int row_size = dhdr._width*bpp;
    unsigned int padding = (4 - row_size % 4) % 4;

    unsigned int row_size90 = bmpf90.dhdr._width*bpp;
    unsigned int padding90 = (4 - row_size90 % 4) % 4;

    unsigned int data_size = row_size90 * bmpf90.dhdr._height + padding90 * bmpf90.dhdr._height;
    bmpf90._data = new char[data_size];

    auto rotate_part = [&](unsigned int start, unsigned int end)
    {
        unsigned int i90 = start * row_size90;
        for(unsigned int i = start * bpp; i < end * bpp; i += bpp)
        {

            for(unsigned int j = dhdr._height; j>0; j--)
            {
                bmpf90._data[i90] = _data[(i)+(row_size+padding)*(j-1)];
                bmpf90._data[i90+1] = _data[(i)+1+(row_size+padding)*(j-1)];
                bmpf90._data[i90+2] = _data[(i)+2+(row_size+padding)*(j-1)];
                i90+=3;
            };
            for(unsigned int p = 0; p<padding90; ++p)
            {
                bmpf90._data[i90+p] = 0;
            };
            i90+=padding90;
        }
    };
    unsigned int num_threads = std::thread::hardware_concurrency();
    unsigned int chunk_size = dhdr._width / num_threads;
    std::vector<std::thread> threads;

    for(unsigned int t = 0; t < num_threads; ++t)
    {
        unsigned int start = t * chunk_size;
        unsigned int end = ( t == num_threads - 1 ) ? dhdr._width : start + chunk_size;
        threads.emplace_back(rotate_part, start, end);
    }

    for(auto& thread : threads)
    {
        thread.join();
    }

    bmpf90.bhdr._file_size = bhdr._file_size-dhdr._data_size+data_size;
    bmpf90.dhdr._data_size = data_size;
    bmpf90.saveBMPFile(fname);
    bmpf90.freeBMPFile();
};








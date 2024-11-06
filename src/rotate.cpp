/* Ilya Pavlov st129535@student.spbu.ru
	lab-work-1
*/
#include "func_headers.h"

void rotate90(BMPFile* bmpf)
{

    BMPFile* bmpf90 = new BMPFile;

    bmpf90->bhdr = bmpf->bhdr;
    bmpf90->dhdr = bmpf->dhdr;

    bmpf90->dhdr._height = bmpf->dhdr._width;
    bmpf90->dhdr._width = bmpf->dhdr._height;

    bmpf90->dhdr._prheight = bmpf->dhdr._prwidth;
    bmpf90->dhdr._prwidth = bmpf->dhdr._prheight;

    unsigned int bpp = bmpf->dhdr._bits_per_pixel/8;

    unsigned int row_size = bmpf->dhdr._width*bpp;
    unsigned int padding = (4 - row_size % 4) % 4;

    unsigned int row_size90 = bmpf90->dhdr._width*bpp;
    unsigned int padding90 = (4 - row_size90 % 4) % 4;

    unsigned int data_size = row_size90 * bmpf90->dhdr._height + padding90 * bmpf90->dhdr._height;
    bmpf90->_data = new char[data_size];

    unsigned int i90 = 0;
    for(unsigned int i = row_size; i>0; i-=bpp)
    {

        for(unsigned int j = 0; j<bmpf->dhdr._height; j++)
        {
            bmpf90->_data[i90] = bmpf->_data[(i)-3+(row_size+padding)*(j)];
            bmpf90->_data[i90+1] = bmpf->_data[(i)-2+(row_size+padding)*(j)];
            bmpf90->_data[i90+2] = bmpf->_data[(i)-1+(row_size+padding)*(j)];
            i90+=3;
        };
        for(unsigned int p = 0; p<padding90; ++p)
        {
            bmpf90->_data[i90+p] = 0;
        };
        i90+=padding90;
    };
    saveBMPFile("rotate90clock.bmp",bmpf90);
    freeBMPFile(bmpf90);
};

void rotate270(BMPFile* bmpf)
{

    BMPFile* bmpf90 = new BMPFile;

    bmpf90->bhdr = bmpf->bhdr;
    bmpf90->dhdr = bmpf->dhdr;

    bmpf90->dhdr._height = bmpf->dhdr._width;
    bmpf90->dhdr._width = bmpf->dhdr._height;

    bmpf90->dhdr._prheight = bmpf->dhdr._prwidth;
    bmpf90->dhdr._prwidth = bmpf->dhdr._prheight;

    unsigned int bpp = bmpf->dhdr._bits_per_pixel/8;

    unsigned int row_size = bmpf->dhdr._width*bpp;
    unsigned int padding = (4 - row_size % 4) % 4;

    unsigned int row_size90 = bmpf90->dhdr._width*bpp;
    unsigned int padding90 = (4 - row_size90 % 4) % 4;

    unsigned int data_size = row_size90 * bmpf90->dhdr._height + padding90 * bmpf90->dhdr._height;
    bmpf90->_data = new char[data_size];

    unsigned int i90 = 0;
    for(unsigned int i = 0; i<row_size ; i+=bpp)
    {

        for(unsigned int j = bmpf->dhdr._height; j>0; j--)
        {
            bmpf90->_data[i90] = bmpf->_data[(i)+(row_size+padding)*(j-1)];
            bmpf90->_data[i90+1] = bmpf->_data[(i)+1+(row_size+padding)*(j-1)];
            bmpf90->_data[i90+2] = bmpf->_data[(i)+2+(row_size+padding)*(j-1)];
            i90+=3;
        };
        for(unsigned int p = 0; p<padding90; ++p)
        {
            bmpf90->_data[i90+p] = 0;
        };
        i90+=padding90;
    };
    saveBMPFile("rotate90anticlock.bmp",bmpf90);
    freeBMPFile(bmpf90);
};






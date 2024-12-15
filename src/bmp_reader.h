/* Ilya Pavlov st129535@student.spbu.ru
	lab-work-1
*/
#ifndef BMP_READER_H
#define BMP_READER_H
#include "func_headers.h"

#pragma pack(push, 1)

class BMPFile 
{
public:
    bool loadBMPFile(std::string fname);
    bool freeBMPFile();
    bool saveBMPFile(const std::string fname);
    void rotate90(const std::string fname);
    void rotate270(const std::string fname);
    
    void extractChannels(
        std::vector<unsigned int>& blueChannel,
        std::vector<unsigned int>& greenChannel,
        std::vector<unsigned int>& redChannel,
        std::vector<unsigned int>& alphaChannel // останется пустым, если альфа-канал отсутствует
    );
    void mergeChannels(
        const std::vector<unsigned int>& blueChannel,
        const std::vector<unsigned int>& greenChannel,
        const std::vector<unsigned int>& redChannel,
        const std::vector<unsigned int>& alphaChannel // пустой, если альфа отсутствует
    );

    friend void gaussianBlurImage(
        std::vector<unsigned int>& blueChannel,
        std::vector<unsigned int>& greenChannel,
        std::vector<unsigned int>& redChannel,
        std::vector<unsigned int>& alphaChannel,  BMPFile& bmp_file, int kernelSize , float sigma
    );    
    
private:
    
    struct BMPHeader
    {
        unsigned char _id[2];
        unsigned int _file_size;
        unsigned char _unused1[4];
        unsigned int _pixel_offset;
    };

    struct DIBHeader
    {
        unsigned int _header_size;
        unsigned int _width;   
        unsigned int _height;  
        unsigned short _color_planes;
        unsigned short _bits_per_pixel;
        unsigned int _compression;
        unsigned int _data_size;
        unsigned int _prwidth;   
        unsigned int _prheight;  
        unsigned int _colors_count;
        unsigned int _imp_colors_count;
    };

    BMPHeader bhdr;
    DIBHeader dhdr;
    char* _data;
};
#pragma pack(push,1)
#endif



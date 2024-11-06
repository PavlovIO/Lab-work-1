#ifndef BMP_READER_H
#define BMP_READER_H
#include <iostream>
#include <fstream> 

#pragma pack(push, 1)

struct BMPHeader {
    unsigned char _id[2];       
    unsigned int _file_size;    
    unsigned char _unused1[4];             
    unsigned int _pixel_offset;   
};

struct DIBHeader {
    unsigned int _header_size;   
    unsigned int _width;   //    
    unsigned int _height;  //            
    unsigned short _color_planes;       
    unsigned short _bits_per_pixel;    
    unsigned int _compression;        
    unsigned int _data_size;          
    unsigned int _prwidth;   //          
    unsigned int _prheight;  //        
    unsigned int _colors_count;       
    unsigned int _imp_colors_count;   
};

struct BMPFile {
    BMPHeader bhdr;              
    DIBHeader dhdr;       
    char* _data;           
};

BMPFile* loadBMPFile(std::string fname);
void freeBMPFile(BMPFile* bmp_file);
#endif



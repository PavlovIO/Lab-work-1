
#include "bmp_reader.h"


BMPFile* loadBMPFile(std::string fname) {
	std::ifstream fp(fname, std::ios::binary);
	if (!fp) {
		std::cerr<<"Can't load the file"<<std::endl;
		return nullptr;
	};
	
	BMPFile* bmp_file = new BMPFile;
	//Читаем бмп хедер
	fp.read((char*)&bmp_file->bhdr, sizeof(BMPHeader));
	fp.read((char*)&bmp_file->dhdr, sizeof(DIBHeader));
	
	bmp_file->_data = new char[bmp_file->dhdr._data_size];
	fp.seekg(bmp_file->bhdr._pixel_offset,std::ios::beg);
	fp.read(bmp_file->_data, bmp_file->dhdr._data_size);
	
    	fp.close();
    	return bmp_file;
};

void freeBMPFile(BMPFile* bmp_file) {
	if (bmp_file){
		delete[] bmp_file->_data;
		delete bmp_file;
	};

};


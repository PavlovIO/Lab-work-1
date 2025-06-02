# Lab-work-1
## Author
Павлов Илья Олегович, группа 24.Б81-мм
## Contacts
st129535@student.spbu.ru
## Description
Input - bmp file with 24/32 bits per pixel
Lab-work-1 - open and read bmp file, turn it 90 deg clockwise and anticlokwise, apply GaussBlur to the image and to the rotated images. || Addition of parallelization. make all - gives two object files output - no parallelization executes main file, outputParallel - with parallelization executes mainParallel.
## Build
make all
## Run
./output filename int float
## Run parallel
./outputParallel filename int float
## Test
make test ARGS="filename int float"

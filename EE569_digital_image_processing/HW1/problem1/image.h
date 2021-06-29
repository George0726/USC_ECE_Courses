//Qirui Sun
//USC ID: 1140685892
//qiruisun@usc.edu
//Submission Date: 2/7/2021
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include<fstream>
#include <cstdlib>
using namespace std;
unsigned char*** allocate_3D(int width, int height, int bpp);
void getImage3D(unsigned char * image1D, unsigned char ***image3D, int width, int height, int bpp);
void writeFile(const char * fileName,unsigned char ***image3D,int width, int height, int bpp);
void readFile(const char * fileName, unsigned char *image1D,int width, int height, int bpp);
unsigned char* allocate_1D(int width, int height, int bpp);
int check_length(int n, int Width);
int crop_pix(int value);
float *PSNR(unsigned char ***ground_truth, unsigned char ***test, int width, int height, int bpp);
void allocate_pixel_bilinear(unsigned char *p, unsigned char*** input,int sum1, int sum2, int sum3, int sum4,int i,int j);
void bilinear_demosaicing(unsigned char *** input, unsigned char *** output, int kernel_size, int width, int height, int bpp);
void allocate_pixel_mhc(unsigned char *p, unsigned char*** input,int sum1, int sum2, int sum3, int sum4,int i,int j);
void mhc_demosaicing(unsigned char *** input, unsigned char *** output, int kernel_size, int width, int height, int bpp);
void image_enhance_a(unsigned char*** input, unsigned char*** output,int width,int height,int BytesPerPixel);
void image_enhance_b(unsigned char*** input, unsigned char*** output, int width, int height, int bpp);
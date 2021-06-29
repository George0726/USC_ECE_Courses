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
using namespace std;
unsigned char*** allocate_3D(int width, int height, int bpp);
void getImage3D(unsigned char * image1D, unsigned char ***image3D, int width, int height, int bpp);
void writeFile(const char * fileName,unsigned char ***image3D,int width, int height, int bpp);
void readFile(const char * fileName, unsigned char *image1D,int width, int height, int bpp);
unsigned char* allocate_1D(int width, int height, int bpp);
int check_length(int n, int Width);
int crop_pix(int value);
float bilateral_weights(float sigmacs, float sigmass,int delta_x, int delta_y, float i1, float i2);
void uniform_filter( unsigned char ***input, unsigned char*** output, int kernel_size, int width, int height, int bpp);
float *PSNR(unsigned char ***ground_truth, unsigned char ***test, int width, int height, int bpp);
void guassian_filter( unsigned char ***input, unsigned char*** output, int kernel_size, int width, int height, int bpp);
void bilateral_filter( unsigned char ***input, unsigned char*** output, int kernel_size, int width, int height, int bpp,float sigma1, float sigma2);
void noise_hist(unsigned char ***noise_img,unsigned char ***ground_truth,int width, int height, int bpp);
void BubbleSort(int* h, int len);
void raiseArray(int* h, int len);
void median_filter(unsigned char ***input,unsigned char ***output,int kernel_size,int width, int height, int bpp);
//Qirui Sun
//USC ID: 1140685892
//qiruisun@usc.edu
//Submission Date: 2/7/2021
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <math.h>
using namespace std;

int check_length(int n, int Width);
int crop_pix(int value);
int quantize_pixel(int pixel_value,int ChannelPerValue);
int cal_color(int a, int b, int c, int channel_per_value);
int * recover_color( int color,int channel_per_value);
void raise_array(int * arr, int length);
unsigned char*** allocate_3D(int width, int height, int bpp);
void getImage3D(unsigned char * image1D, unsigned char ***image3D, int width, int height, int bpp);
void writeFile(const char * fileName,unsigned char ***image3D,int width, int height, int bpp);
void readFile(const char * fileName, unsigned char *image1D,int width, int height, int bpp);
unsigned char* allocate_1D(int width, int height, int bpp);
float *PSNR(unsigned char ***ground_truth, unsigned char ***test, int width, int height, int bpp);
void quantize_image(unsigned char ***input,unsigned char *** output, int quantize_size,int width, int height, int bpp);
void mean_filter_quant(unsigned char ***input,unsigned char *** output, int kernel_size,int quanti_size,int width, int height, int bpp);
void shuffle(float *a,int *b, int length);
void selectionSort(float *a, int *b,int n);
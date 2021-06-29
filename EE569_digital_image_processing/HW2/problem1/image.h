//Qirui Sun
//USC ID: 1140685892
//qiruisun@usc.edu
//Submission Date: 2/23/2021
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include<fstream>
using namespace std;
unsigned char* assign1d( int width, int height, int bbp);
unsigned char*** assign3d( int width, int height, int bbp);
void readraw(const char * imagename, unsigned char*img, int width, int height, int bbp);
void writeraw(const char * filename, unsigned char*** img, int width, int height, int bbp);
void img1d3d( unsigned char*img1d, unsigned char *** img3d, int width, int height, int bbp);
void rgb2gray(unsigned char*** input, unsigned char*** output, int width, int height, int bbp);
int check_length(int n, int Width);
int crop_pix(int value);
void sobel_edge(unsigned char *** input, unsigned char *** gradx, unsigned char*** grady,double*** magnitude, int kernel_size, int width, int height, int bpp);
void normalize_img(unsigned char *** img, int max, int min, int scale, int width, int height, int bbp);
void binary_img(double *** input, unsigned char *** output,float threshold, int width, int height, int bbp);
double*** assign3d_double( int width, int height, int bbp);
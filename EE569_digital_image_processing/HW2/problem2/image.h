// # (1) Name : Qirui Sun
// # (2) USC ID Number : 1140685892
// # (3) USC Email : qiruisun@usc.ed
// # (4) Submission Date : 02/07/2021

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include<fstream>
#include <stdlib.h>
using namespace std;
unsigned char* assign1d( int width, int height, int bbp);
unsigned char*** assign3d( int width, int height, int bbp);
void readraw(const char * imagename, unsigned char*img, int width, int height, int bbp);
void writeraw(const char * filename, unsigned char*** img, int width, int height, int bbp);
void img1d3d( unsigned char*img1d, unsigned char *** img3d, int width, int height, int bbp);
void rgb2gray(unsigned char*** input, unsigned char*** output, int width, int height, int bbp);
int check_length(int n, int Width);
int crop_pix(int value);
void fix_dither(unsigned char *** input, unsigned char*** output, int threshold,int width, int height, int bbp);
void random_dither(unsigned char *** input, unsigned char*** output,int max,int width, int height, int bbp);
int ** generate_matrix(int dim);
void matrix_dither(unsigned char *** input, unsigned char*** output,int dim,int width, int height, int bbp);
void error_diffusion_stucki(unsigned char *** input, unsigned char*** output,int width, int height, int bbp);
void error_diffusion_JJN(unsigned char *** input, unsigned char*** output,int width, int height, int bbp);
void error_diffusion_FS(unsigned char *** input, unsigned char*** output,int width, int height, int bbp);
void error_diffusion_FS_color(unsigned char *** input, unsigned char*** output,int width, int height, int bbp);
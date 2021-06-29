//Qirui Sun
//USC ID: 1140685892
//qiruisun@usc.edu
//Submission Date: 3/12/2021
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include<fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;
unsigned char* assign1d( int width, int height, int bbp);
unsigned char*** assign3d( int width, int height, int bbp);
void readraw(const char * imagename, unsigned char*img, int width, int height, int bbp);
void writeraw(const char * filename, unsigned char*** img, int width, int height, int bbp);
void img1d3d( unsigned char*img1d, unsigned char *** img3d, int width, int height, int bbp);
void rgb2gray(unsigned char*** input, unsigned char*** output, int width, int height, int bbp);
unsigned char *** geo_modification(unsigned char ***image_input,int Width);
float * find_ori(int x, int y, int half_sec,int width);
float* value_interpolated(unsigned char*** image, float* coor,int Width);
int check_len(float x, int length);
unsigned char *** reverse_geo_modification(unsigned char ***image_input,int Width0);
float * reverse_find_ori(int x, int y, int half_sec,int width);
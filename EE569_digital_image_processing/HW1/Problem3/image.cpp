//Qirui Sun
//USC ID: 1140685892
//qiruisun@usc.edu
//Submission Date: 2/7/2021
#include"image.h"
unsigned char* allocate_1D(int width, int height, int bpp)
{
	int total = width * height * bpp;
	unsigned char* Img = new unsigned char[total]();
	for (int i = 0; i < total; i++)
		Img[i] = 0;
	return Img;
}

unsigned char *** allocate_3D(int width, int height, int bpp){
    unsigned char*** Img = new unsigned char **[height];
    for (int i = 0; i < height; i++){
        Img[i] = new unsigned char *[width]();
		for (int j = 0; j < width; j++){
            Img[i][j] = new unsigned char [bpp]();
			for (int k = 0; k < bpp; k++){
                Img[i][j][k] = 255;
            }
        }
    }
    return Img;
}



void readFile(const char * fileName, unsigned char *image1D,int width, int height, int bpp)
{
	FILE* file = fopen(fileName, "rb");
	if (file == NULL)
	{
		cout << "File Open Failed." << endl;
		return;
	}
	else
		fread(image1D, sizeof(unsigned char), width*height*bpp, file);
	fclose(file);
	cout << "File Read Successfully." << endl;
}

void writeFile(const char * fileName,unsigned char ***image3D,int width, int height, int bpp)
{
   	FILE* out_file = fopen(fileName, "wb");
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < bpp; k++)
				fprintf(out_file, "%c", image3D[i][j][k]);
	cout << "File Write Successfully." << endl;
	fclose(out_file);
}

void getImage3D(unsigned char * image1D, unsigned char ***image3D, int width, int height, int bpp)
{
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			for (int k = 0; k < bpp; k++)
			{
				int temp = (i * width + j) * bpp + k;
				image3D[i][j][k] = image1D[temp];
			}
        }
    }
}

int check_length(int n, int Width)
{
 if(n<0){
     return -n;
 }
 if(n>=Width)
    {
        return 2*Width-n-2;
    }
 return n;
}
int crop_pix(int value)
{
	if(value > 255)
	{
		return 255;
	}
	else if(value < 0 )
	{
		return 0;
	}
	else
	{
		return value;
	}
}
int cal_color(int a, int b, int c, int channel_per_value){
    int bin = 256/channel_per_value;
    int x,y,z;
    x = (a - bin/2)/bin;
    y = (b - bin/2)/bin;
    z = (c - bin/2)/bin; 

    return x * channel_per_value *channel_per_value + y *channel_per_value + z;
}
int * recover_color( int color,int channel_per_value){
    int * p = new int[3]();
    int bin = 256/channel_per_value;
    p[0] = (color/(channel_per_value*channel_per_value) )* bin + bin/2;
    p[1] = ((color - p[0]*(channel_per_value*channel_per_value))/channel_per_value) * bin +bin/2;
    p[2] = (color - p[0] *(channel_per_value*channel_per_value) - p[1] * channel_per_value) * bin + bin/2;

    return p;

}
void raise_array(int * arr, int length){
    for( int i = 0; i < length; i ++){
        arr[i] = 0;
    }
}

int quantize_pixel(int pixel_value,int ChannelPerValue){
    int bin = 256/ChannelPerValue;
    for(int i = 0; i < ChannelPerValue; i++){
        if((pixel_value>=0 +bin*i)&&(pixel_value<=bin + bin*i)){
            return bin/2 + bin*i;
        }
    }
    return 0;

}

float *PSNR(unsigned char ***ground_truth, unsigned char ***test, int width, int height, int bpp){
	float *p = new float[bpp]();
	float max = 255.0;

	for(int k = 0; k<bpp; k++){
		float sum = 0;
		int iter = 0;
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				iter++;
				sum = sum + pow(((float) ground_truth[i][j][k] - (float) test[i][j][k]),2.0);
			}
		}
		float MSE = sum/iter;
		p[k] =10 * log10((max*max/MSE));
	}
	return p;

}

void quantize_image(unsigned char ***input,unsigned char *** output, int quantize_size,int width, int height, int bpp){

    float ChannelPerValue = pow(quantize_size,1.0/3.0);
    cout<<"Value Per channel is: "<<ChannelPerValue<<endl;
    int bin = 256/ChannelPerValue;

    for(int i=0; i<height;i++){
        for(int j = 0; j< width; j++){
            for(int k = 0; k<bpp; k ++){
                output[i][j][k] = (unsigned char) quantize_pixel((int)input[i][j][k],ChannelPerValue);
            }
        }
    }
}
void mean_filter_quant(unsigned char ***input,unsigned char *** output, int kernel_size,int quanti_size,int width, int height, int bpp){
    int ChannelPerValue = pow(quanti_size,1.0/3.0);
    int * I_hist = new int[ChannelPerValue]();
    int bin = 256/ChannelPerValue;
    int row,col;
    int half_kernel = (kernel_size-1)/2;
    float sum_weigth;

    for( int i =0; i< height; i++){
        for(int j =0; j<width; j++){
            for(int k = 0; k<bpp;k++){
                int max_color = 0, max_count = 0;
                raise_array(I_hist,ChannelPerValue);
                for (int m = -half_kernel; m <= half_kernel; m++)
                {
                    for (int n = -half_kernel; n <= half_kernel; n++)
                    {  
                        row = check_length(i+m,height);
                        col = check_length(j+n,width);
                        int color = ((int)input[row][col][k] - bin/2)/bin;
                        I_hist[color]++;
                        if(I_hist[color]>max_count){
                            max_count = I_hist[color];
                            max_color = input[row][col][k];
                        }

                    }
                    output[i][j][k] = max_color;
                }
            }   
        }
    }
}

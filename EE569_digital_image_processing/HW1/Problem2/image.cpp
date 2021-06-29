#include"image.h"
//Qirui Sun
//USC ID: 1140685892
//qiruisun@usc.edu
//Submission Date: 2/7/2021
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
		cout << "File Open Failed!!!" << endl;
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
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < bpp; k++)
			{
				int temp = (i * width + j) * bpp + k;
				image3D[i][j][k] = image1D[temp];
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

void uniform_filter( unsigned char ***input, unsigned char*** output, int kernel_size, int width, int height, int bpp){
	
	float sum_uni=0.0,temp;
	int row,col,iter;
	int half_kernel = (kernel_size-1)/2;

	for(int i = 0; i < height; i++){
		for(int j = 0; j<width; j ++){
			for(int k = 0;k < bpp;k++){
				sum_uni=0.0;
				iter = 0;
 				for (int m = -half_kernel; m <= half_kernel; m++)
                {
                    for (int n = -half_kernel; n <= half_kernel; n++)
                    {  
						iter++;
                        row = check_length(i+m,height);
                        col = check_length(j+n,width);
                        temp=(float)input[row][col][k];
                        sum_uni = sum_uni + temp;
                    }
                }	
				output[i][j][k] = (unsigned char)crop_pix(ceil(sum_uni/iter));
			}		
		}
	}
	cout<<"uniform denoise completed! "<< endl;
}

void guassian_filter( unsigned char ***input, unsigned char*** output, int kernel_size, int width, int height, int bpp){
	
	float sum_gua=0.0,temp,sum_weigth;
	int row,col;
	int half_kernel = (kernel_size-1)/2;

	for(int i = 0; i < height; i++){
		for(int j = 0; j<width; j ++){
			for(int k = 0;k < bpp;k++){
				sum_gua=0.0;
				sum_weigth = 0.0;
 				for (int m = -half_kernel; m <= half_kernel; m++)
                {
                    for (int n = -half_kernel; n <= half_kernel; n++)
                    {  
                        row = check_length(i+m,height);
                        col = check_length(j+n,width);
                        temp=(float)input[row][col][k];
						sum_gua= sum_gua + temp * exp(-(pow((float)m,2)+(pow((float)n,2)))/2);
                        sum_weigth = sum_weigth+exp(-(pow((float)m,2)+(pow((float)n,2)))/2);
                    }
                }	
				output[i][j][k] = (unsigned char)crop_pix(ceil(sum_gua/sum_weigth));
			}
		}
	}
	cout<<"guassian denoise completed! "<< endl;
}

void bilateral_filter( unsigned char ***input, unsigned char*** output, int kernel_size, int width, int height, int bpp,float sigma1, float sigma2){
	
	float sum_bi=0.0,temp,sum_weigth,weight;
	int row,col;
	int half_kernel = (kernel_size-1)/2;
	float sigma_s = sigma1;
	float sigma_c = sigma2;

	for(int i = 0; i < height; i++){
		for(int j = 0; j<width; j ++){
			for(int k = 0;k < bpp;k++){
				sum_bi=0.0;
				sum_weigth = 0.0;
 				for (int m = -half_kernel; m <= half_kernel; m++)
                {
                    for (int n = -half_kernel; n <= half_kernel; n++)
                    {  
                        row = check_length(i+m,height);
                        col = check_length(j+n,width);
                        temp=(float)input[row][col][k];
						weight = bilateral_weights(sigma_c,sigma_s,m,n,temp,(float)input[i][j][k]);
						sum_bi= sum_bi + temp * weight;
                        sum_weigth = sum_weigth + weight;
                    }
                }	
				output[i][j][k] = (unsigned char)crop_pix(ceil(sum_bi/sum_weigth));
			}
		}
	}
	cout<<"bilateral denoise completed! "<< endl;
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
float bilateral_weights(float sigmacs, float sigmass,int delta_x, int delta_y, float i1, float i2){
    float w = 0, special, intensity;
    special = exp(-(pow(abs(delta_x),2.0)+pow(abs(delta_y),2.0))/(2*pow(sigmacs,2.0)));
    intensity = exp(-pow(abs(i1-i2),2.0)/(2*pow(sigmass,2.0)));
    w = special*intensity;
    return w;
}

void noise_hist(unsigned char ***noise_img,unsigned char ***ground_truth,int width, int height, int bpp)
{
   	// FILE* hist_file = fopen(fileName, "wb");
	ofstream hist_file;
	std::string file = "noise_hist.csv";
	hist_file.open(file);
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			if(bpp ==3){
				hist_file<<(float)noise_img[i][j][0] - (float) ground_truth[i][j][0]<<","<<(float)noise_img[i][j][1] - (float) ground_truth[i][j][1]<<","<<(float)noise_img[i][j][2] - (float) ground_truth[i][j][2]<<std::endl;
			}
			if(bpp==1){
				hist_file<<(float)noise_img[i][j][0] - (float) ground_truth[i][j][0]<<std::endl;
			}
		}

	}
	cout << "Noise Histogram calculate successfully." << endl;
	hist_file.close();
}

void median_filter(unsigned char ***input,unsigned char ***output,int kernel_size,int width, int height, int bpp){
	int total = kernel_size * kernel_size;
	int row,col;
	int half_kernel = (kernel_size-1)/2;
	int median = (total-1)/2;
	//sort array for sort
	int *sortArray = new int[total]();
	float temp;

	for(int i = 0; i < height; i++){
		for(int j = 0; j<width; j ++){
			for(int k = 0;k < bpp;k++){
				int counter = 0;
 				for (int m = -half_kernel; m <= half_kernel; m++)
                {
                    for (int n = -half_kernel; n <= half_kernel; n++)
                    {  
                        row = check_length(i+m,height);
                        col = check_length(j+n,width);
                        temp=(float)input[row][col][k];
						sortArray[counter] = temp;
						counter++;

					}
                }
				BubbleSort(sortArray,total);	
				output[i][j][k] = (unsigned char) sortArray[median];
			}
		}
	}
}

void BubbleSort(int* h, int len)
{
	for(int i=0;i<len-1;++i){
		for(int j=0;j<len-1-i;++j){
			if(h[j]>h[j+1]){
				int temp = h[j];
				h[j] = h[j+1];
				h[j+1] = temp;
			}
		}
	}
} 

void raiseArray(int* h, int len)
{
	for(int i = 0; i <len; i++){
		h[i] = 0;
	}
}
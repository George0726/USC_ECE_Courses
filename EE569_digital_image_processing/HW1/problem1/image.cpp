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
		cout << "File Open Failed!!" << endl;
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
	//cout << "Get 3D Image Completed." << endl;
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
float *PSNR(unsigned char ***ground_truth, unsigned char ***test, int width, int height, int bpp){
	float *p = new float[bpp]();
	float max = 255.0;

	for(int k = 0; k<bpp; k++){
		float sum = 0;
		float iter = 0;
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

void bilinear_demosaicing(unsigned char *** input, unsigned char *** output, int kernel_size, int width, int height, int bpp){
    float conv1[3][3]={{0.0,1/2.0,0.0},{0.0,0.0,0.0},{0.0,1/2.0,0.0}};
    float conv2[3][3]={{0.0,0.0,0.0},{1/2.0,0.0,1/2.0},{0.0,0.0,0.0}};
    float conv3[3][3]={{0.0,1/4.0,0.0},{1/4.0,0.0,1/4.0},{0.0,1/4.0,0.0}};
    float conv4[3][3]={{1/4.0,0.0,1/4.0},{0.0,0.0,0.0},{1/4.0,0.0,1/4.0}};
    float sum1,sum2,sum3,sum4;
    float temp;
	int half_kernel = (kernel_size-1)/2;
    int row ,col;
    unsigned char *p = new unsigned char[3]();

    for(int i = 0; i < height; i++){
		for(int j = 0; j<width; j ++){
            sum1=0.0;
            sum2=0.0;
            sum3=0.0;
            sum4=0.0;   

            for (int m = -half_kernel; m <= half_kernel; m++)
            {
                for (int n = -half_kernel; n <= half_kernel; n++)
                {  
                row = check_length(i+m,height);
                col = check_length(j+n,width);
                temp=(float)input[row][col][0];
                sum1= sum1 + temp* (conv1[m+half_kernel][n+half_kernel]);
                sum2= sum2 + temp* (conv2[m+half_kernel][n+half_kernel]);
                sum3= sum3 + temp* (conv3[m+half_kernel][n+half_kernel]);
                sum4= sum4 + temp* (conv4[m+half_kernel][n+half_kernel]);
                }
            }

            sum1=crop_pix(ceil(sum1));
            sum2=crop_pix(ceil(sum2));
            sum3=crop_pix(ceil(sum3));
            sum4=crop_pix(ceil(sum4));	

            allocate_pixel_bilinear(p,input,sum1,sum2,sum3,sum4,i,j);

            output[i][j][0] = p[0];
            output[i][j][1] = p[1];
            output[i][j][2] = p[2];

		}
	}
}

void allocate_pixel_bilinear(unsigned char *p, unsigned char*** input,int sum1, int sum2, int sum3, int sum4,int i,int j){
    if((i%2==0)&&(j%2==0))
        {
            p[0]=(unsigned char)sum2;
            p[1]=input[i][j][0];
            p[2]=(unsigned char)sum1;
        }

    if((i%2==0)&&(j%2!=0))
        {
            p[1]=input[i][j][0];
            p[2]=(unsigned char)sum3;
            p[3]=(unsigned char)sum4;
        }

    if((i%2!=0)&&(j%2!=0))
        {
            p[0]=(unsigned char)sum1;
            p[1]=input[i][j][0];;
            p[2]=(unsigned char)sum2;
        }

    if((i%2!=0)&&(j%2==0))
        {
            p[0]=(unsigned char)sum4;
            p[1]=(unsigned char)sum3;
            p[2]=input[i][j][0];;
        }
}

void mhc_demosaicing(unsigned char *** input, unsigned char *** output, int kernel_size, int width, int height, int bpp){
    float conv1[5][5]={{0.0,0.0,-1/8.0,0.0,0.0},{0.0,0.0,1/4.0,0.0,0.0},{-1/8.0,1/4.0,1/2.0,1/4.0,-1/8.0},{0.0,0.0,1/4.0,0.0,0.0},{0.0,0.0,-1/8.0,0.0,0.0}};
    float conv2[5][5]={{0.0,0.0,1/16.0,0.0,0.0},{0.0,-1/8.0,0.0,-1/8.0,0.0},{-1/8.0,1/2.0,5/8.0,1/2.0,-1/8.0},{0.0,-1/8.0,0.0,-1/8.0,0.0},{0.0,0.0,1/16.0,0.0,0.0}};
    float conv3[5][5]={{0.0,0.0,-1/8.0,0.0,0.0},{0.0,-1/8.0,1/2.0,-1/8.0,0.0},{1/16.0,0.0,5/8.0,0.0,1/16.0},{0.0,-1/8.0,1/2.0,-1/8.0,0.0},{0.0,0.0,-1/8.0,0.0,0.0}};
    float conv4[5][5]={{0.0,0.0,-3/16.0,0.0,0.0},{0.0,1/4.0,0.0,1/4.0,0.0},{-3/16.0,0.0,6/8.0,0.0,-3/16.0},{0.0,1/4.0,0.0,1/4.0,0.0},{0.0,0.0,-3/16.0,0.0,0.0}};

    float sum1,sum2,sum3,sum4;
    float temp;
	int half_kernel = (kernel_size-1)/2;
    int row ,col;
    unsigned char *p = new unsigned char[3]();

    for(int i = 0; i < height; i++){
		for(int j = 0; j<width; j ++){
            sum1=0.0;
            sum2=0.0;
            sum3=0.0;
            sum4=0.0;   

            for (int m = -half_kernel; m <= half_kernel; m++)
            {
                for (int n = -half_kernel; n <= half_kernel; n++)
                {  
                row = check_length(i+m,height);
                col = check_length(j+n,width);
                temp=(float)input[row][col][0];
                sum1= sum1 + temp* (conv1[m+half_kernel][n+half_kernel]);
                sum2= sum2 + temp* (conv2[m+half_kernel][n+half_kernel]);
                sum3= sum3 + temp* (conv3[m+half_kernel][n+half_kernel]);
                sum4= sum4 + temp* (conv4[m+half_kernel][n+half_kernel]);
                }
            }

            sum1=crop_pix(ceil(sum1));
            sum2=crop_pix(ceil(sum2));
            sum3=crop_pix(ceil(sum3));
            sum4=crop_pix(ceil(sum4));	

            allocate_pixel_mhc(p,input,sum1,sum2,sum3,sum4,i,j);

            output[i][j][0] = p[0];
            output[i][j][1] = p[1];
            output[i][j][2] = p[2];

		}
	}
}

void allocate_pixel_mhc(unsigned char *p, unsigned char*** input,int sum1, int sum2, int sum3, int sum4,int i,int j){
    if((i%2==0)&&(j%2==0))
        {
            p[0]=(unsigned char)sum2;
            p[1]=input[i][j][0];
            p[2]=(unsigned char)sum3;
        }

    if((i%2==0)&&(j%2!=0))
        {
            p[1]=input[i][j][0];
            p[2]=(unsigned char)sum1;
            p[3]=(unsigned char)sum4;
        }

    if((i%2!=0)&&(j%2!=0))
        {
            p[0]=(unsigned char)sum3;
            p[1]=input[i][j][0];;
            p[2]=(unsigned char)sum2;
        }

    if((i%2!=0)&&(j%2==0))
        {
            p[0]=(unsigned char)sum4;
            p[1]=(unsigned char)sum1;
            p[2]=input[i][j][0];;
        }
}

void image_enhance_a(unsigned char*** input, unsigned char*** output,int width,int height,int BytesPerPixel){
    
    ofstream hist_file;
    std::string filename = "hist_result_a.csv";
    float freq[BytesPerPixel][256],pdf[BytesPerPixel][256],cdf[BytesPerPixel][256];
    float temp;

    // initialize the matrix
    for (int i = 0 ; i <BytesPerPixel;i++){
        for (int j=0; j<256;j++){
            freq[i][j] = 0.0;
            pdf[i][j] = 0.0;
            cdf[i][j] = 0.0;
        }
    }

    // calculate the frequency
    for(int k = 0; k<BytesPerPixel; k++){
        for (int i =0; i<height; i++){
            for(int j=0; j<width;j++){
                freq[k][(int)input[i][j][k]]++;
            }
        }
    }
    // assign the prob
    for (int col =0; col<256;col++){
        for(int row=0; row<BytesPerPixel;row++){
            pdf[row][col] = freq[row][col]/(width*height);
        }
    }
    // calculate the cdf
    for(int row=0; row<BytesPerPixel;row++){
        temp = 0.0;
        for (int col =0; col<256;col++){
            temp += pdf[row][col];
            cdf[row][col] = temp;
        }
    }

    // mapping function
    for(int i = 0; i<3; i++){
        for (int col =0; col<height;col++){
            for(int row=0; row<width;row++){
                output[col][row][i] = (unsigned char) crop_pix(ceil((cdf[i][(int)input[col][row][i]] * 255.0)));
                // cout<<(int)output[col][row][i] <<endl;
            }
        }
    }

    hist_file.open(filename);
    for(int c=0;c<256;c++){
        hist_file << c<< "," << cdf[0][c] * 255.0<<std::endl;
     }
    hist_file.close();

}

void image_enhance_b(unsigned char*** input, unsigned char*** output, int width, int height, int bpp)
{
    ofstream hist_file;
    std::string filename = "hist_result_b.csv";

	int total = width * height;
	int bin = width * height / 256;
	//sort array for sort
	int** sortArray = new int*[bpp]();
	for (int i = 0; i < bpp; i++)
	{
		sortArray[i] = new int[total]();
		for (int j = 0; j < total; j++)
			sortArray[i][j] = 0;
	}

	//Store Array By Pixel
	for (int k = 0; k < bpp; k++)
	{
		int count = 0;
		for (int m = 0; m < 256; m++){
			for (int i = 0; i < height; i++){
				for (int j = 0; j < width; j ++){
					if (input[i][j][k] == m)
					{
						sortArray[k][count] = i * width + j;
						count++;
					}
                }
            }
        }
	}
	//rearrange the new value by pixel
	for (int k = 0; k < bpp; k++){
		for (int m = 0; m < 256; m++){
			for (int i = 0; i < bin; i++)
			{
				int index = sortArray[k][m * bin + i];
				int row = index / width;
				int col = index - row * width;
				output[row][col][k] = m;
			}
        }
    }
    int count = 0;
    hist_file.open(filename);
    for(int c=0;c<256;c++){
        count = count +bin;
        hist_file << c<< "," << count<<std::endl;
     }
    hist_file.close();
}


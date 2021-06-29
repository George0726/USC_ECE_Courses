//Qirui Sun
//USC ID: 1140685892
//qiruisun@usc.edu
//Submission Date: 2/23/2021
#include"image.h"
unsigned char* assign1d( int width, int height, int bbp){
    int total = width*height*bbp;
    unsigned char * pnt = new unsigned char[total]();
    for (int i =0; i<total; i++){
        pnt[i] =  255;
    }
    return pnt;
}

unsigned char*** assign3d( int width, int height, int bbp){
    unsigned char ***pnt = new unsigned char**[height];
    for(int i = 0; i<height; i++){
        pnt[i] = new unsigned char*[width]();
        for(int j = 0; j<width;j++){
            pnt[i][j] = new unsigned char[bbp];
            for(int k = 0; k <bbp; k++){
                pnt[i][j][k] = 255;
            }
        }
    }

    return pnt;
}

double*** assign3d_double( int width, int height, int bbp){
    double ***pnt = new double**[height];
    for(int i = 0; i<height; i++){
        pnt[i] = new double*[width]();
        for(int j = 0; j<width;j++){
            pnt[i][j] = new double[bbp];
            for(int k = 0; k <bbp; k++){
                pnt[i][j][k] = 255;
            }
        }
    }

    return pnt;
}

void readraw(const char * imagename, unsigned char*img, int width, int height, int bbp){
    FILE * file;
	file = fopen(imagename,"rb");
    if(file == NULL){
        cout<<"raw file failed to open!!!"<<endl;
        return;
    }
    else
    {
        fread(img,sizeof(unsigned char), width*height*bbp, file);
    fclose;
    cout<< "well done!"<<endl;
    }
}

void writeraw(const char * filename, unsigned char*** img, int width, int height, int bbp){
	FILE * file;
	file = fopen(filename,"wb");
	for(int i = 0; i<height;i++){
		for(int j = 0; j<width;j++){
			for(int k = 0 ; k< bbp; k++){
				fprintf(file,"%c",img[i][j][k]);
			}
		}
	}
	cout<<"well done!"<<endl;

}
void img1d3d( unsigned char*img1d, unsigned char *** img3d, int width, int height, int bbp){
	for(int i = 0; i< height; i++){
		for(int j = 0; j<width;j++){
			for(int k =0; k<bbp;k++)
			{
				int index =( i * width + j ) * bbp + k;
				img3d[i][j][k] = img1d[index];
			}
		}
	}
}
void rgb2gray(unsigned char*** input, unsigned char*** output, int width, int height, int bbp){

	for(int i = 0; i<height; i ++){
		for(int j = 0;j<width;j++){
			float temp = 0.2989 * (float) input[i][j][0] + 0.5870 * (float) input[i][j][1] + 0.1140 * input[i][j][2];
			output[i][j][0] = (unsigned char) temp;
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

void sobel_edge(unsigned char *** input, unsigned char *** gradx, unsigned char*** grady,double*** magnitude, int kernel_size, int width, int height, int bpp){
    float conv1[3][3]={{0.25,0,-0.25},{0.5,0.0,-0.5},{0.25,0,-0.25}};
    float conv2[3][3]={{-0.25,-0.5,-0.25},{0,0.0,0},{0.25,0.5,0.25}};
    float sum1,sum2;
    float temp;
	int half_kernel = (kernel_size-1)/2;
    int row ,col;
	float maxx = 0.0,maxy=0.0,minx=0.0,miny=0.0;

    for(int i = 0; i < height; i++){
		for(int j = 0; j<width; j ++){
            sum1=0.0;
            sum2=0.0;

            for (int m = -half_kernel; m <= half_kernel; m++)
            {
                for (int n = -half_kernel; n <= half_kernel; n++)
                {  
                row = check_length(i+m,height);
                col = check_length(j+n,width);
                temp=(float)input[row][col][0];
                sum1= sum1 + temp* (conv1[m+half_kernel][n+half_kernel]);
                sum2= sum2 + temp* (conv2[m+half_kernel][n+half_kernel]);

                }
            }

            sum1=crop_pix(ceil(sum1));
            sum2=crop_pix(ceil(sum2));
			gradx[i][j][0] = (unsigned char) sum1;
			grady[i][j][0] = (unsigned char) sum2;
			if(sum1> maxx){
				maxx = sum1;
			}
			if(sum2> maxy){
				maxy = sum2;
			}
			if(sum1<minx){
				minx = sum1;
			}
			if(sum2<miny){
				miny = sum2;
			}
		}
	}
	for(int i = 0; i<height;i++){
		for(int j = 0; j<width; j++){
			float temp = (float) gradx[i][j][0] * (float) gradx[i][j][0] + (float) grady[i][j][0] *(float) grady[i][j][0];
			magnitude[i][j][0] = sqrt(temp)/sqrt(255.0 *255.0 *2);
		}
	}

	normalize_img(gradx,maxx,minx,255,width,height,1);
	normalize_img(grady,maxy,miny,255,width,height,1);

	// for(int i = 0; i<height;i++){
	// 	for(int j = 0; j<width; j++){
	// 		gradx[i][j][0] = (unsigned char)(255.0 - (float)(gradx[i][j][0]));
	// 		grady[i][j][0] = (unsigned char)(255.0 - (float)(grady[i][j][0]));
	// 	}
	// }
}
void normalize_img(unsigned char *** img, int max, int min, int scale, int width, int height, int bbp){
	for(int i = 0; i<height;i++){
		for(int j = 0; j<width;j++){
			for(int k = 0 ;k < bbp;k++){
				float temp = (float)img[i][j][k];
				img[i][j][k] = (unsigned char) (temp - (float)min)/((float) max-(float)min)*(float)scale;
			}
		}
	}
}
void binary_img(double *** input, unsigned char *** output,float threshold, int width, int height, int bbp){
	int * freq = new int[width*height*bbp]();
	int iter = 0;
	for(int m = 0; m<256;m++){
		for(int i = 0; i<height;i++){
			for(int j = 0; j<width;j++){
				if((int)(input[i][j][0] *255.0)==m){
					freq[iter]=m;
					iter++;
				}
			}
		}
	}
	int value = freq[(int)(threshold*width *height*bbp)];
	for(int i = 0; i<height;i++){
		for(int j = 0; j<width;j++){
			if((int)(input[i][j][0] *255.0 > value)){
				output[i][j][0] = (unsigned char) 0;
			}
			else{
				 output[i][j][0] = (unsigned char) 255;
			}
		}
	}
}


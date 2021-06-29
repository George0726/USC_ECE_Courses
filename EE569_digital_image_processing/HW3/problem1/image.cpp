//Qirui Sun
//USC ID: 1140685892
//qiruisun@usc.edu
//Submission Date: 3/12/2021
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

unsigned char *** geo_modification(unsigned char ***image_input,int Width0){

	// create a new panel
    int Width = Width0;
    if(Width0%2==1)
            Width=Width0+1;

    int half_ori = Width/2;
	int length = (int) (sqrt(2.0) * half_ori)*2;
    int half_sec = length/2;

	unsigned char ***image_ouput = new unsigned char**[length]();
    for(int i = 0; i<length; i++){
        image_ouput[i] = new unsigned char*[length]();
        for(int j = 0; j<length;j++){
            image_ouput[i][j] = new unsigned char[3];
            for(int k = 0; k <3; k++){
                image_ouput[i][j][k] = 255;
            }
        }
    }

    cout<<"output pattern: " <<length<<endl;
    for(int i=0; i<length; i++){
        for(int j=0; j<length; j++){
            float *coor,*value;
            coor = find_ori(i,j,half_sec,Width);//mapping to original
            value = value_interpolated(image_input,coor,Width0);//bilinear interpolation
            for(int k = 0; k<3; k++){
                image_ouput[i][j][k] = (int)value[k];
            }
            if(((i-half_sec)*(i-half_sec)+(j-half_sec)*(j-half_sec))>=(half_sec*half_sec)){
                for(int k =0; k<3;k++){
                    image_ouput[i][j][k] =0;
                }
            }
        }
    }
    return image_ouput;
}

unsigned char *** reverse_geo_modification(unsigned char ***image_input,int Width0){

	// create a new panel
    int Width = Width0;
    if(Width0%2==1)
            Width=Width0+1;

    int half_ori = Width/2;
	int length = (int) (1/sqrt(2.0)*half_ori*2);
    if(length%2==1)
        length += 1;
    int half_sec = length/2;

	unsigned char ***image_ouput = new unsigned char**[length]();
    for(int i = 0; i<length; i++){
        image_ouput[i] = new unsigned char*[length]();
        for(int j = 0; j<length;j++){
            image_ouput[i][j] = new unsigned char[3];
            for(int k = 0; k <3; k++){
                image_ouput[i][j][k] = 255;
            }
        }
    }

    unsigned char ***image_ouput_final = new unsigned char**[length-1]();
    for(int i = 0; i<length-1; i++){
        image_ouput_final[i] = new unsigned char*[length-1]();
        for(int j = 0; j<length-1;j++){
            image_ouput_final[i][j] = new unsigned char[3];
            for(int k = 0; k <3; k++){
                image_ouput_final[i][j][k] = 255;
            }
        }
    }

    cout<<"output pattern: " <<length-1<<endl;
    for(int i=0; i<length; i++){
        for(int j=0; j<length; j++){
            float *coor,*value;
            coor = reverse_find_ori(i,j,half_sec,Width);//mapping to original
            value = value_interpolated(image_input,coor,Width0);//bilinear interpolation
            for(int k = 0; k<3; k++){
                image_ouput[i][j][k] = (int)value[k];
            }
        }
    }

    for (int i =0; i<length-1; i++)
        for(int j =0;j<length-1;j++)
            for(int k=0; k<3;k++)
                image_ouput_final[i][j][k] = image_ouput[i][j][k];
    return image_ouput_final;
}

float * reverse_find_ori(int x, int y, int half_sec,int width){
    float *pnt0 = new float[2];
    float half_width = (float) width/2;
    float deltax_1=0.0;
    float deltay_1 = 0.0;

    float deltax = x-half_sec;
    float deltay = half_sec-y;

    if((deltax!=0)&&(deltay!=0)){
        if(abs(deltay/deltax)<1){
            float edge = abs(deltay/deltax) *half_sec;
            float ratio = half_width/sqrt(edge*edge + half_sec*half_sec);
            deltax_1 = ratio*deltax;
            deltay_1 = ratio*deltay;
        }
        else{
            float edge = abs(deltax/deltay) *half_sec;
            float ratio = half_width/sqrt(edge*edge + half_sec*half_sec);
            deltax_1 = ratio*deltax;
            deltay_1 = ratio*deltay;
        }
    }
    else{
            float ratio = sqrt(2);
            deltax_1 = ratio*deltax;
            deltay_1 = ratio*deltay;
    }

    pnt0[0] = deltax_1 + (int) half_width;
    pnt0[1] = (int) half_width - deltay_1;

    return pnt0;
}

float * find_ori(int x, int y, int half_sec,int width){
    float *pnt0 = new float[2];
    float half_width = (float) width/2;
    float deltax_1=0.0;
    float deltay_1 = 0.0;

    float deltax = x-half_sec;
    float deltay = half_sec-y;

    if((deltax!=0)&&(deltay!=0)){
        if(abs(deltay/deltax)<1){
            float edge = abs(deltay/deltax) *half_width;
            float ratio = sqrt(edge*edge + half_width*half_width)/half_sec;
            deltax_1 = ratio*deltax;
            deltay_1 = ratio*deltay;
        }
        else{
            float edge = abs(deltax/deltay) *half_width;
            float ratio = sqrt(edge*edge + half_width*half_width)/half_sec;
            deltax_1 = ratio*deltax;
            deltay_1 = ratio*deltay;
        }
    }
    else{
            float ratio = 1/sqrt(2);
            deltax_1 = ratio*deltax;
            deltay_1 = ratio*deltay;
    }

    pnt0[0] = deltax_1 + (int) half_width;
    pnt0[1] = (int) half_width - deltay_1;

    return pnt0;
}

float* value_interpolated(unsigned char*** image, float* coor,int Width){
    float *pnt1 = new float[3];
    float x = coor[0] - (int)coor[0];
    float y = coor[1] - (int)coor[1];



    int x0 = check_len((int)coor[0],Width);
    int x1 =check_len((int)coor[0]+1,Width);
    int y0 = check_len((int)coor[1],Width);
    int y1 =check_len((int)coor[1]+1,Width);

    for(int k = 0;k < 3; k++){
        pnt1[k] = x*y*image[x1][y1][k] + (1-x)*(1-y)*image[x0][y0][k]+ (1-x)*y*image[x0][y1][k] + x*(1-y)*image[x1][y0][k];
    }
    return pnt1;
}

int check_len(float x, int length){

    if((int)x>=length){
        return length-1;
    }

    if((int)x<0){
        return 0;
    }

    return (int)x;
}
// # (1) Name : Qirui Sun
// # (2) USC ID Number : 1140685892
// # (3) USC Email : qiruisun@usc.ed
// # (4) Submission Date : 02/07/2021

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

void fix_dither(unsigned char *** input, unsigned char*** output, int threshold,int width, int height, int bbp){

	for(int i = 0; i<height;i++){
		for(int j = 0; j<width;j++){
			for (int k=0;k<bbp;k++){
				if(int(input[i][j][k])>threshold){
					output[i][j][k] = (unsigned char)255;
				}
				else{
					output[i][j][k] = (unsigned char) 0;
				}
			}
		}
	}
}

void random_dither(unsigned char *** input, unsigned char*** output,int max,int width, int height, int bbp){

	for(int i = 0; i<height;i++){
		for(int j = 0; j<width;j++){
			for (int k=0;k<bbp;k++){
				int threshold = rand()%max+100;
				if(int(input[i][j][k])>threshold){
					output[i][j][k] = (unsigned char)255;
				}
				else{
					output[i][j][k] = (unsigned char) 0;
				}
			}
		}
	}
}
void matrix_dither(unsigned char *** input, unsigned char*** output,int dim,int width, int height, int bbp){
	// int ** matrix = new int *[dim]();
	// for(int i = 0; i<dim;i++){
	// 	matrix[i] = new int[dim]();
	// }
	if(dim==2){
		int matrix[2][2] = {{1,2},{3,0}};
	}

	int **matrix;
	float**threshold = new float*[dim];
	matrix = generate_matrix(dim);
	for(int i = 0; i<dim;i++){
		threshold[i] = new float[dim]();
		for(int j =0;j<dim;j++){
			threshold[i][j] = ((float) matrix[i][j] +0.5)/(dim*dim) *255.0;
			// cout<<matrix[i][j]<<" "<<threshold[i][j]<<endl;
		}
	}

	for(int i = 0; i<height;i++){
		for(int j = 0; j<width;j++){
			for (int k=0;k<bbp;k++){
				if((float)input[i][j][k]>threshold[i%dim][j%dim]){
					output[i][j][k] = (unsigned char)255;
				}
				else{
					output[i][j][k] = (unsigned char) 0;					
				}
			}
		}
	}
}

int ** generate_matrix(int dim){
	if(dim%2!=0){
		cout<<"wrong dimension"<<endl;
	}
	int ** matrix = new int*[dim]();
	for(int i =0;i<dim;i++){
		matrix[i] = new int[dim]();
	}
	if(dim==2){
		matrix[0][0] = 1;
		matrix[0][1] = 2;
		matrix[1][0] = 3;
		matrix[1][1] = 0;
		return matrix;
	}

	for(int i = 0; i <dim;i++){
		for(int j =0; j<dim;j++){
			if(i/(dim/2)==0 && j/(dim/2)==0){
				matrix[i][j] = generate_matrix(dim/2)[i][j] *4 +1;
			}
			if(i/(dim/2)==1 && j/(dim/2)==0){
				matrix[i][j] = generate_matrix(dim/2)[i-dim/2][j] *4 +3;
			}
			if(i/(dim/2)==0 && j/(dim/2)==1){
				matrix[i][j] = generate_matrix(dim/2)[i][j-dim/2] *4 +2;
			}
			if(i/(dim/2)==1 && j/(dim/2)==1){
				matrix[i][j] = generate_matrix(dim/2)[i-dim/2][j-dim/2] *4;
			}
		}
	}

	// return matrix;

}

void error_diffusion_stucki(unsigned char *** input, unsigned char*** output,int width, int height, int bbp){
	float matrix[5][5] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,8.0/42.0,4.0/42.0},{2.0/42.0,4.0/42.0,8.0/42.0,4.0/42.0,2.0/42.0},{1.0/42.0,2.0/42.0,4.0/42.0,2.0/42.0,1.0/42.0}};
	float matrix_flipped[5][5] = {{0,0,0,0,0},{0,0,0,0,0},{4.0/42.0,8.0/42.0,0,0,0},{2.0/42.0,4.0/42.0,8.0/42.0,4.0/42.0,2.0/42.0},{1.0/42.0,2.0/42.0,4.0/42.0,2.0/42.0,1.0/42.0}};
	int dim=5;
	cout<<"use stucki diffusion matrix"<<endl;

	int half_kernel = (dim-1)/2;

	float ***temp = new float**[height];
    for(int i = 0; i<height; i++){
        temp[i] = new float*[width]();
        for(int j = 0; j<width;j++){
            temp[i][j] = new float[bbp];
            for(int k = 0; k <bbp; k++){
                temp[i][j][k] = (float) input[i][j][k];
            }
        }
    }

	float error = 0.0;
	int iter = 0;
	for(int i =0; i<height;i++){
		if(i%2==0){
			for(int j =0;j<width;j++){
				if(temp[i][j][0]<=127.0){
					output[i][j][0] = (unsigned char)0;
					error = temp[i][j][0];
				}
				else if(temp[i][j][0]>127.0){
					output[i][j][0] = (unsigned char)255;
					error = temp[i][j][0] - 255.0;				
				}
				for (int m = -half_kernel; m <= half_kernel; m++)
                {
                    for (int n = -half_kernel; n <= half_kernel; n++)
                    { 	
						// cout<<"test"<<endl;
						if((m+i>=0)&&(m+i<height)&&(n+j>=0)&&(n+j<width)){
							int col = m+i;
							int row = n+j;
							temp[col][row][0] = temp[col][row][0]+ error*matrix[m+half_kernel][n+half_kernel];
						}
                    }
                }	


			}
		}
		else if(i%2==1){
			for(int j = width-1; j>=0;j--){
				if(temp[i][j][0]<=127.0){
					output[i][j][0] = (unsigned char)0;
					error = temp[i][j][0];
				}
				else if(temp[i][j][0]>127.0){
					output[i][j][0] = (unsigned char)255;
					error = temp[i][j][0] - 255.0;				
				}
				for (int m = -half_kernel; m <= half_kernel; m++)
                {
                    for (int n = -half_kernel; n <= half_kernel; n++)
                    {  
						if((m+i>=0)&&(m+i<height)&&(n+j>=0)&&(n+j<width)){
							int col = m+i;
							int row = n+j;
							temp[col][row][0] = temp[col][row][0]+ error*matrix_flipped[m+half_kernel][n+half_kernel];
						}
                    }
                }	

			}

		}
	}
}

void error_diffusion_FS(unsigned char *** input, unsigned char*** output,int width, int height, int bbp){
	cout<<"use Floyd-Steinberg diffusion matrix"<<endl;
	float matrix[3][3] = {{0,0,0},{0,0,7.0/16.0},{3.0/16.0,5.0/16.0,1.0/16.0}};
	float matrix_flipped[3][3] = {{0,0,0},{7.0/16.0,0,0},{1.0/16.0,5.0/16.0,3.0/16.0}};
	int dim=3;

	int half_kernel = (dim-1)/2;

	float ***temp = new float**[height];
    for(int i = 0; i<height; i++){
        temp[i] = new float*[width]();
        for(int j = 0; j<width;j++){
            temp[i][j] = new float[bbp];
            for(int k = 0; k <bbp; k++){
                temp[i][j][k] = (float) input[i][j][k];
            }
        }
    }

	float error = 0.0;
	int iter = 0;
	for(int i =0; i<height;i++){
		if(i%2==0){
			for(int j =0;j<width;j++){
				if(temp[i][j][0]<=127.0){
					output[i][j][0] = (unsigned char)0;
					error = temp[i][j][0];
				}
				else if(temp[i][j][0]>127.0){
					output[i][j][0] = (unsigned char)255;
					error = temp[i][j][0] - 255.0;				
				}
				for (int m = -half_kernel; m <= half_kernel; m++)
                {
                    for (int n = -half_kernel; n <= half_kernel; n++)
                    { 	
						// cout<<"test"<<endl;
						if((m+i>=0)&&(m+i<height)&&(n+j>=0)&&(n+j<width)){
							int col = m+i;
							int row = n+j;
							temp[col][row][0] = temp[col][row][0]+ error*matrix[m+half_kernel][n+half_kernel];
						}
                    }
                }	


			}
		}
		else if(i%2==1){
			for(int j = width-1; j>=0;j--){
				if(temp[i][j][0]<=127.0){
					output[i][j][0] = (unsigned char)0;
					error = temp[i][j][0];
				}
				else if(temp[i][j][0]>127.0){
					output[i][j][0] = (unsigned char)255;
					error = temp[i][j][0] - 255.0;				
				}
				for (int m = -half_kernel; m <= half_kernel; m++)
                {
                    for (int n = -half_kernel; n <= half_kernel; n++)
                    {  
						if((m+i>=0)&&(m+i<height)&&(n+j>=0)&&(n+j<width)){
							int col = m+i;
							int row = n+j;
							temp[col][row][0] = temp[col][row][0]+ error*matrix_flipped[m+half_kernel][n+half_kernel];
						}
                    }
                }	

			}

		}
	}
}
void error_diffusion_JJN(unsigned char *** input, unsigned char*** output,int width, int height, int bbp){
	cout<<"use JJN diffusion matrix"<<endl;
	float matrix[5][5] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,7.0/48.0,5.0/48.0},{3.0/48.0,5.0/48.0,7.0/48.0,5.0/48.0,3.0/48.0},{1.0/48.0,3.0/48.0,5.0/48.0,3.0/48.0,1.0/48.0}};
	float matrix_flipped[5][5] = {{0,0,0,0,0},{0,0,0,0,0},{5.0/48.0,7.0/48.0,0,0,0},{3.0/48.0,5.0/48.0,7.0/48.0,5.0/48.0,3.0/48.0},{1.0/48.0,3.0/48.0,5.0/48.0,3.0/48.0,1.0/48.0}};
	int dim=5;

	int half_kernel = (dim-1)/2;

	float ***temp = new float**[height];
    for(int i = 0; i<height; i++){
        temp[i] = new float*[width]();
        for(int j = 0; j<width;j++){
            temp[i][j] = new float[bbp];
            for(int k = 0; k <bbp; k++){
                temp[i][j][k] = (float) input[i][j][k];
            }
        }
    }

	float error = 0.0;
	int iter = 0;
	for(int i =0; i<height;i++){
		if(i%2==0){
			for(int j =0;j<width;j++){
				if(temp[i][j][0]<=127.0){
					output[i][j][0] = (unsigned char)0;
					error = temp[i][j][0];
				}
				else if(temp[i][j][0]>127.0){
					output[i][j][0] = (unsigned char)255;
					error = temp[i][j][0] - 255.0;				
				}
				for (int m = -half_kernel; m <= half_kernel; m++)
                {
                    for (int n = -half_kernel; n <= half_kernel; n++)
                    { 	
						// cout<<"test"<<endl;
						if((m+i>=0)&&(m+i<height)&&(n+j>=0)&&(n+j<width)){
							int col = m+i;
							int row = n+j;
							temp[col][row][0] = temp[col][row][0]+ error*matrix[m+half_kernel][n+half_kernel];
						}
                    }
                }	


			}
		}
		else if(i%2==1){
			for(int j = width-1; j>=0;j--){
				if(temp[i][j][0]<=127.0){
					output[i][j][0] = (unsigned char)0;
					error = temp[i][j][0];
				}
				else if(temp[i][j][0]>127.0){
					output[i][j][0] = (unsigned char)255;
					error = temp[i][j][0] - 255.0;				
				}
				for (int m = -half_kernel; m <= half_kernel; m++)
                {
                    for (int n = -half_kernel; n <= half_kernel; n++)
                    {  
						if((m+i>=0)&&(m+i<height)&&(n+j>=0)&&(n+j<width)){
							int col = m+i;
							int row = n+j;
							temp[col][row][0] = temp[col][row][0]+ error*matrix_flipped[m+half_kernel][n+half_kernel];
						}
                    }
                }	

			}

		}
	}
}


void error_diffusion_FS_color(unsigned char *** input, unsigned char*** output,int width, int height, int bbp){
	cout<<"use Floyd-Steinberg diffusion matrix"<<endl;
	float matrix[3][3] = {{0,0,0},{0,0,7.0/16.0},{3.0/16.0,5.0/16.0,1.0/16.0}};
	float matrix_flipped[3][3] = {{0,0,0},{7.0/16.0,0,0},{1.0/16.0,5.0/16.0,3.0/16.0}};
	int dim=3;

	int half_kernel = (dim-1)/2;

	float ***temp = new float**[height];
    for(int i = 0; i<height; i++){
        temp[i] = new float*[width]();
        for(int j = 0; j<width;j++){
            temp[i][j] = new float[bbp];
            for(int k = 0; k <bbp; k++){
                temp[i][j][k] = 255.0 - (float) input[i][j][k];
            }
        }
    }

	float error = 0.0;
	int iter = 0;
	for(int k =0;k<bbp;k++){
		for(int i =0; i<height;i++){
			if(i%2==0){
				for(int j =0;j<width;j++){
					if(temp[i][j][k]<=127.0){
						output[i][j][k] = (unsigned char)255;
						error = temp[i][j][k];
					}
					else if(temp[i][j][k]>127.0){
						output[i][j][k] = (unsigned char)0;
						error = temp[i][j][k] - 255.0;				
					}
					for (int m = -half_kernel; m <= half_kernel; m++)
					{
						for (int n = -half_kernel; n <= half_kernel; n++)
						{ 	
							// cout<<"test"<<endl;
							if((m+i>=0)&&(m+i<height)&&(n+j>=0)&&(n+j<width)){
								int col = m+i;
								int row = n+j;
								temp[col][row][k] = temp[col][row][k]+ error*matrix[m+half_kernel][n+half_kernel];
							}
						}
					}	
				}
			}
			else if(i%2==1){
				for(int j = width-1; j>=0;j--){
					if(temp[i][j][k]<=127.0){
						output[i][j][k] = (unsigned char)255;
						error = temp[i][j][k];
					}
					else if(temp[i][j][k]>127.0){
						output[i][j][k] = (unsigned char)0;
						error = temp[i][j][k] - 255.0;				
					}
					for (int m = -half_kernel; m <= half_kernel; m++)
					{
						for (int n = -half_kernel; n <= half_kernel; n++)
						{  
							if((m+i>=0)&&(m+i<height)&&(n+j>=0)&&(n+j<width)){
								int col = m+i;
								int row = n+j;
								temp[col][row][k] = temp[col][row][k]+ error*matrix_flipped[m+half_kernel][n+half_kernel];
							}
						}
					}	

				}

			}
		}
	}
}
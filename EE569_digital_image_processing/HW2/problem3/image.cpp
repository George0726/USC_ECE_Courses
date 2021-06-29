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

void error_diffusion_FS_color(unsigned char *** input, unsigned char*** output,int width, int height, int bbp){
	cout<<"use Floyd-Steinberg diffusion matrix"<<endl;
	double matrix[3][3] = {{0,0,0},{0,0,7.0/16.0},{3.0/16.0,5.0/16.0,1.0/16.0}};
	double matrix_flipped[3][3] = {{0,0,0},{7.0/16.0,0,0},{1.0/16.0,5.0/16.0,3.0/16.0}};
	int dim=3;

	int half_kernel = (dim-1)/2;

	double ***temp = new double**[height];
    for(int i = 0; i<height; i++){
        temp[i] = new double*[width]();
        for(int j = 0; j<width;j++){
            temp[i][j] = new double[bbp];
            for(int k = 0; k <bbp; k++){
                temp[i][j][k] = 255.0 - (double) input[i][j][k];//to cmy color scale
            }
        }
    }

	double error = 0.0;
	int iter = 0;
	for(int k =0;k<bbp;k++){
		for(int i =0; i<height;i++){
			if(i%2==0){
				for(int j =0;j<width;j++){
					if(temp[i][j][k]<=127.0){
						output[i][j][k] = (unsigned char)255;//back to rgb
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

void MBVQ_fs(unsigned char *** input, unsigned char*** output,int width, int height, int bbp){
	cout<<"MBVQ, use Floyd-Steinberg diffusion matrix"<<endl;
	double matrix[3][3] = {{0,0,0},{0,0,7.0/16.0},{3.0/16.0,5.0/16.0,1.0/16.0}};
	double matrix_flipped[3][3] = {{0,0,0},{7.0/16.0,0,0},{1.0/16.0,5.0/16.0,3.0/16.0}};
	int dim=3;

	int half_kernel = (dim-1)/2;

	double ***img_copy_const = new double**[height];
	double ***img_copy = new double**[height];

    for(int i = 0; i<height; i++){
        img_copy[i] = new double*[width]();
		img_copy_const[i] = new double*[width]();
        for(int j = 0; j<width;j++){
            img_copy[i][j] = new double[bbp];
			img_copy_const[i][j] = new double[bbp];
            for(int k = 0; k <bbp; k++){
                img_copy[i][j][k] = (double) input[i][j][k];
				img_copy_const[i][j][k] = (double) input[i][j][k];
            }
        }
    }
	double * pnt =new double[3]();
	double * error = new double[3]();

	for(int i = 0; i <height;i++){
		if(i%2==0){
			for(int j=0; j<width;j++){
				int quad = assign_quad(img_copy_const[i][j]);
				int vertex = findVertex(quad, img_copy[i][j]);
				pnt = getColors(vertex);
				error[0] = img_copy[i][j][0] - pnt[0],error[1] = img_copy[i][j][1] - pnt[1],error[2] = img_copy[i][j][2] - pnt[2];
				img_copy[i][j][0] = pnt[0];img_copy[i][j][1] = pnt[1];img_copy[i][j][2] = pnt[2];
				for(int k = 0;k<bbp;k++){
					for (int m = -half_kernel; m <= half_kernel; m++)
					{
						for (int n = -half_kernel; n <= half_kernel; n++)
						{ 	
							// cout<<"test"<<endl;
							if((m+i>=0)&&(m+i<height)&&(n+j>=0)&&(n+j<width)){
								int col = m+i;
								int row = n+j;
								img_copy[col][row][k] = img_copy[col][row][k]+ error[k]*matrix[m+half_kernel][n+half_kernel];
							}
						}
					}	
				}
			}
		}

		else if(i%2==1){
			for(int j=width-1; j>=0;j--){
				int quad = assign_quad(img_copy_const[i][j]);
				int vertex = findVertex(quad, img_copy[i][j]);
				pnt = getColors(vertex);
				error[0] = img_copy[i][j][0] - pnt[0],error[1] = img_copy[i][j][1] - pnt[1],error[2] = img_copy[i][j][2] - pnt[2];
				img_copy[i][j][0] = pnt[0];img_copy[i][j][1] = pnt[1];img_copy[i][j][2] = pnt[2];
				for(int k = 0;k<bbp;k++){
					for (int m = -half_kernel; m <= half_kernel; m++){
						for (int n = -half_kernel; n <= half_kernel; n++){ 	
							// cout<<"test"<<endl;
							if((m+i>=0)&&(m+i<height)&&(n+j>=0)&&(n+j<width)){
								int col = m+i;
								int row = n+j;
								img_copy[col][row][k] = img_copy[col][row][k]+ error[k]*matrix_flipped[m+half_kernel][n+half_kernel];
							}
						}
					}	
				}
			}
		}
	}

	for (int i = 0; i<height;i++)
		for( int j=0; j<width;j++)
			for(int k = 0; k<bbp; k++)
				output[i][j][k] = (unsigned char) img_copy[i][j][k];
}

int assign_quad(double * p){
	if((p[0]+p[1])>255)
		if((p[1]+p[2])>255)
			if((p[0]+p[1]+p[2])>510)	return 1;
			else 	return 2;
		else	return 3;
	else
		if(!((p[1]+p[2])>255))
			if(!((p[0]+p[1]+p[2])>255))	return 4;
			else 	return 5;
		else	return 6;
}

int findVertex(int quad, double* pixel)
{

	//Extract Three Colors
	double R = pixel[0];
	double G = pixel[1];
	double B = pixel[2];
	double threshold = 128;

	switch(quad)
	{

		case 1:
			if (R < threshold)
				if (R <= G)
					if (R <= B)
						return 3;	//Cyan
			if (G < threshold)
				if (G <= R)
					if (G <= B)
						return 4;	//Magenta
			if (B < threshold)
				if (B <= R)
					if (B <= G)
						return 2;	//Yellow
			return 1;				//White

		case 2:
			if (G >= B)
				if (R >= B)
				{
					if (R >= threshold)
						return 2;	//Yellow
					else
						return 5;	//Green
				}
			if (G >= R)
				if (B >= R)
				{
					if (B >= threshold)
						return 3;	//Cyan
					else
						return 5;	//Green
				}
			return 4;				//Magenta

		case 3:
			if (B > threshold)
            	if (R > threshold)
            	{
                	if (B >= G)
                    	return 4;	//Magenta
                	else
                    	return 2;	//Yellow
                }
            	else
            	{
                	if (G > B + R)
                    	return 5;	//Green
               		else 
                    	return 4;	//Magenta
                }
        	else
	            if (R >= threshold)
	            {
	                if (G >= threshold)
	                    return 2;	//Yellow
	                else
	                    return 6;	//Red
	            }
	            else
	            {
	                if (R >= G)
	                    return 6;	//Red
	                else
	                    return 5;	//Green
	            }

		case 4:
			if (B > threshold)
				if (B >= R)
					if (B >= G)
						return 7;	//Blue
			if (G > threshold)
				if (G >= B)
					if (G >= R)
						return 5;	//Green
			if (R > threshold)
				if (R >= B)
					if (R >= G)
						return 6;	//Red
			return 8;				//Black

		case 5:
			if (R > G)
				if (R >= B)
				{
					if (B < threshold)
						return 6;	//Red
					else
						return 4;	//Magenta
				}
			if (B > G)
				if (B >= R)
				{
					if (R < threshold)
						return 7;	//Blue
					else
						return 4;	//Magenta
				}
			return 5;				//Green

		case 6:
			if (B > threshold)
				if (R > threshold)
				{
					if (G >= R)
						return 3;	//Cyan
					else
						return 4;	//Magenta
				}
				else
				{
					if (G > threshold)
						return 3;	//Cyan
					else
						return 7;	//Blue
				}
			else
				if (R > threshold)
				{
					if (R - G + B >= threshold)
						return 4;	//Magenta
					else
						return 5;	//Green
				}
				else
				{
					if (G >= B)
						return 5;	//Green
					else
						return 7;	//Blue
				}
	}
	return 0;
}

double* getColors(int vertex)
{
	double R = 0.0;
	double G = 0.0;
	double B = 0.0;
	switch(vertex)
	{
		//White
		case 1:
			R = 255.0;
			G = 255.0;
			B = 255.0;
			break;
		//Yellow
		case 2:
			R = 255.0;
			G = 255.0;
			B = 0.0;
			break;
		//Cyan
		case 3:
			R = 0.0;
			G = 255.0;
			B = 255.0;
			break;
		//Magenta
		case 4:
			R = 255.0;
			G = 0.0;
			B = 255.0;
			break;
		//Green
		case 5:
			R = 0.0;
			G = 255.0;
			B = 0.0;
			break;
		//Red
		case 6:
			R = 255.0;
			G = 0.0;
			B = 0.0;
			break;
		//Blue
		case 7:
			R = 0.0;
			G = 0.0;
			B = 255.0;
			break;
		//Black
		case 8:
			R = 0.0;
			G = 0.0;
			B = 0.0;
			break;
	}
	//Update Pixel Values
	double* pnt = new double[3]();
	pnt[0] = R;
	pnt[1] = G;
	pnt[2] = B;
	return pnt;
}


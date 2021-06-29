//Qirui Sun
//USC ID: 1140685892
//qiruisun@usc.edu
//Submission Date: 2/23/2021
#include"image.h"

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	//argv[0] program name
	//argv[1] input image
	//argv[2] thershold
	//argv[3] Width
	//argv[4] Height

	FILE *file;
	int BytesPerPixel = 3;
	int Width=481;
	int Height=321;
	int Size=256;
	float thershold= 0.9;
	// Check for proper syntax
	if (argc < 2){
			cout << "program_name input_image.raw [thershold = 0.9][Width = 481] [Height = 321]" << endl;
			return 0;
	}
	if(argc>2){
		thershold = atof(argv[2]);
	}
	if(argc>3){
		Width = atoi(argv[3]);
	}
	if(argc>4){
		Height = atoi(argv[4]);
	}




    unsigned char *image1D; 
    unsigned char ***image_input,***image_gray,***gradx,***grady, *** binary,***char_magnitude;

	image1D = assign1d(Width,Height,BytesPerPixel);

	image_input = assign3d(Width,Height,BytesPerPixel);		
	image_gray = assign3d(Width,Height,1);
	gradx = assign3d(Width,Height,1);
	grady = assign3d(Width,Height,1);
	char_magnitude = assign3d(Width,Height,1);
	// magnitude = assign3d(Width,Height,1);
	binary = assign3d(Width,Height,1);

	double ***magnitude = assign3d_double(Width,Height,1);

	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
    readraw(argv[1], image1D,Width,Height,BytesPerPixel);

    img1d3d(image1D,image_input, Width,Height,BytesPerPixel);
	rgb2gray(image_input,image_gray,Width,Height,BytesPerPixel);

	// sobel_edge(unsigned char *** input, unsigned char *** gradx, unsigned char*** grady,unsigned char*** magnitude, int kernel_size, int width, int height, int bpp)
	sobel_edge(image_gray,gradx,grady,magnitude,3,Width,Height,1);
	// void binary_img(unsigned char *** input, unsigned char *** output,float threshold, int width, int height, int bbp)
	binary_img(magnitude,binary,thershold, Width,Height,1);

	for (int i=0; i<Height;i++){
		for(int j = 0; j<Width;j++){
		char_magnitude[i][j][0]	= (unsigned char)(magnitude[i][j][0]*255.0);
		}
	}

    writeraw("gray.raw",image_gray,Width,Height,1);
	writeraw("gradientx.raw",gradx,Width,Height,1);
	writeraw("gradienty.raw",grady,Width,Height,1);
	writeraw("magnitude.raw",char_magnitude,Width,Height,1);
	writeraw("binary.raw",binary,Width,Height,1);
    return 0 ;
}

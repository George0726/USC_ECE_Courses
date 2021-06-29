#include"image.h"
//Qirui Sun
//USC ID: 1140685892
//qiruisun@usc.edu
//Submission Date: 2/7/2021

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	//argv[0] program name
	//argv[1] input image
	//argv[2] output image
	//argv[3] BytesPerPixel
	//argv[4] Width=500;
	//argv[5] Height=400;

	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel = 1;
	int Width=500;
	int Height=400;
	int Size=256;
	// Check for proper syntax
	if (argc < 3){
			cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
			cout << "program_name input_image.raw  ground_truth.raw [BytesPerPixel = 1] [Width = 500] [Height = 400]" << endl;
			return 0;
	}

	if (argc>3){
		BytesPerPixel = atoi(argv[4]);
		cout<<"channel is: "<<BytesPerPixel<<endl;
	}
	if (argc  >4){
		Width = atoi(argv[5]);
	}

	if (argc  >5){
		Height = atoi(argv[6]);
	}
	
	// Allocate image data array
	// unsigned char Imagedata[Size][Size][BytesPerPixel];
    unsigned char *image1D, *ground_1D; 
    unsigned char ***image_input,***ground_3D;

	image1D = allocate_1D(Width,Height,BytesPerPixel);
	ground_1D = allocate_1D(Width,Height,BytesPerPixel);
	image_input = allocate_3D(Width,Height,BytesPerPixel);		
	ground_3D = allocate_3D(Width,Height,BytesPerPixel);

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
    readFile(argv[1], image1D,Width,Height,BytesPerPixel);
	readFile(argv[2], ground_1D,Width,Height,BytesPerPixel);

    getImage3D(image1D,image_input, Width,Height,BytesPerPixel);
	getImage3D(ground_1D,ground_3D, Width,Height,BytesPerPixel);

	// apply noise hist calculation
    noise_hist(image_input,ground_3D,Width,Height,BytesPerPixel);

    return 0 ;
}

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
	//argv[3] ground truth
	//argv[4] Width 
	//argv[5] Height

	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel = 1;
	int kernel_size = 3;
	int Width=580;
	int Height=440;
	int Size=256;
	// Check for proper syntax
	if (argc < 4){
			cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
			cout << "program_name input_image.raw output_image.raw ground_truth.raw [Width = 580] [Height = 440]" << endl;
			return 0;
	}

	if (argc  >4){
		Width = atoi(argv[4]);
	}

	if (argc  >5){
		Height = atoi(argv[5]);
	}

	// Allocate image data array
	// unsigned char Imagedata[Size][Size][BytesPerPixel];
    unsigned char *image1D,*groud1D; 
    unsigned char ***image_input, ***image_output,***groud_3D;

	image1D = allocate_1D(Width,Height,BytesPerPixel);
	groud1D = allocate_1D(Width,Height,BytesPerPixel);;
	image_input = allocate_3D(Width,Height,BytesPerPixel);		
	image_output = allocate_3D(Width,Height,3);
	groud_3D = allocate_3D(Width,Height,3);

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
    readFile(argv[1], image1D,Width,Height,BytesPerPixel);
	readFile(argv[3], groud1D,Width,Height,BytesPerPixel);

    getImage3D(image1D,image_input, Width,Height,BytesPerPixel);
	getImage3D(groud1D,groud_3D, Width,Height,BytesPerPixel);

    // bilinear demosaicing
    bilinear_demosaicing(image_input, image_output, kernel_size, Width, Height, BytesPerPixel);

	float* p_out = PSNR(image_output,groud_3D,Width,Height,BytesPerPixel*3);
	// float* p_in = PSNR(image_input,groud_3D,Width,Height,BytesPerPixel);

	cout<<"PSNR after demosaicing: "<<p_out[0]<<" "<<p_out[1]<<" "<<p_out[2]<<" "<<endl;


	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}

    writeFile(argv[2],image_output,Width,Height,3);
    return 0 ;
}

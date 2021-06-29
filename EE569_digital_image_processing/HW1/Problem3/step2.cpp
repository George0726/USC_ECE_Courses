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
	//argv[4] quantize_size
	//argv[5] Width
	//argv[6] Height
	//argv[7] BytesPerPixel

	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel = 3;
    int quantize_size = 64;
	int Width=500;
	int Height=400;
	int Size=256;
    int kernel_size = 3;

	// Check for proper syntax
	if (argc < 3){
			cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
			cout << "program_name quantized_input.raw output_image.raw [kernel_size = 3] [quantize_size = 64]" << endl;
			return 0;
	}

    if (argc>3){
        kernel_size = atoi(argv[3]);
        cout<<"kernel size is: "<<kernel_size<<endl;
    }

    if (argc>4){
        quantize_size = atoi(argv[4]);
        cout<<"the image has "<<quantize_size<<" color"<<endl;
    }
	if (argc  >5){
		Width = atoi(argv[5]);
	}

	if (argc  >6){
		Height = atoi(argv[6]);
	}
	if (argc  >7){
		BytesPerPixel = atoi(argv[7]);
	}
	// Allocate image data array
	// unsigned char Imagedata[Size][Size][BytesPerPixel];
    unsigned char *image1D; 
    unsigned char ***image_input, ***image_output;

	image1D = allocate_1D(Width,Height,BytesPerPixel);
	image_input = allocate_3D(Width,Height,BytesPerPixel);		
	image_output = allocate_3D(Width,Height,BytesPerPixel);

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
    readFile(argv[1], image1D,Width,Height,BytesPerPixel);

    getImage3D(image1D,image_input, Width,Height,BytesPerPixel);

	// apply uniform filter to denoise
    mean_filter_quant(image_input,image_output,kernel_size,quantize_size,Width,Height,BytesPerPixel);

	float* p_out = PSNR(image_output,image_input,Width,Height,BytesPerPixel);

	cout<<"After quantize: "<<p_out[0]<<" "<<p_out[1]<<" "<<p_out[2]<<endl;



	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}

    writeFile(argv[2],image_output,Width,Height,BytesPerPixel);
    return 0 ;
}

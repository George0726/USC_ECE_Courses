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
	//argv[3] Width
	// argv[4] Height

	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel = 1;
	int kernel_size = 3;
	int Width=400;
	int Height=560;
	// Check for proper syntax
	if (argc < 3){
			cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
			cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 3] [Width = 400] [Height = 560]" << endl;
			return 0;
	}
    if(argc>3){
        BytesPerPixel = atoi(argv[3]);
        cout<<"channel: "<<BytesPerPixel<<endl;
    }
	if (argc  >4){
		Width = atoi(argv[4]);
	}

	if (argc  >5){
		Height = atoi(argv[5]);
	}

	// Allocate image data array
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

    // histogram transform A
    image_enhance_a(image_input, image_output,Width, Height, BytesPerPixel);

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}

    writeFile(argv[2],image_output,Width,Height,BytesPerPixel);
    return 0 ;
}

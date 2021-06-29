//Qirui Sun
//USC ID: 1140685892
//qiruisun@usc.edu
//Submission Date: 3/12/2021
#include"image.h"

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	//argv[0] program name
	//argv[1] input image
	//argv[2] output image
	//argv[3] Width


	FILE *file;
	int BytesPerPixel = 3;
	int Width=466;
	int Height=466;
	// Check for proper syntax
	if (argc < 3){
			cout << "program_name input_image.raw output_image.raw" << endl;
			return 0;
	}



    unsigned char *image1D; 
    unsigned char ***image_input,***image_ouput;

	image1D = assign1d(Width,Height,BytesPerPixel);

	image_input = assign3d(Width,Height,BytesPerPixel);		


	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
    readraw(argv[1], image1D,Width,Height,BytesPerPixel);

    img1d3d(image1D,image_input, Width,Height,BytesPerPixel);

	image_ouput = reverse_geo_modification(image_input,Width);

	writeraw(argv[2],image_ouput,329,329,3);
    return 0 ;
}

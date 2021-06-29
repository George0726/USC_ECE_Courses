// # (1) Name : Qirui Sun
// # (2) USC ID Number : 1140685892
// # (3) USC Email : qiruisun@usc.ed
// # (4) Submission Date : 02/07/2021

#include"image.h"

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	//argv[0] program name
	//argv[1] input image
	//argv[2] output image
	//argv[3] Width
	//argv[4] Height

	FILE *file;
	int BytesPerPixel = 1;
	int Width=501;
	int Height=332;
	// Check for proper syntax
	if (argc < 3){
			cout << "program_name input_image.raw ouput.raw [Width = 481] [Height = 321]" << endl;
			return 0;
	}
	if(argc>3){
		Width = atoi(argv[3]);
	}
	if(argc>4){
		Height = atoi(argv[4]);
	}




    unsigned char *image1D; 
    unsigned char ***image_input,***image_ouput;

	image1D = assign1d(Width,Height,BytesPerPixel);

	image_input = assign3d(Width,Height,BytesPerPixel);		
	image_ouput = assign3d(Width,Height,1);


	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
    readraw(argv[1], image1D,Width,Height,BytesPerPixel);

    img1d3d(image1D,image_input, Width,Height,BytesPerPixel);

	error_diffusion_FS(image_input,image_ouput,Width,Height,BytesPerPixel);
	writeraw(argv[2],image_ouput,Width,Height,1);
    return 0 ;
}

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
	//argv[3] dim
	//argv[4] Width
	//argv[5] Height

	FILE *file;
	int BytesPerPixel = 1;
	int Width=501;
	int Height=332;
	int dim=2;
	// Check for proper syntax
	if (argc < 2){
			cout << "program_name input_image.raw output.raw [dimension=2] [Width = 481] [Height = 321]" << endl;
			return 0;
	}
    if(argc>3){
        dim = atoi(argv[3]);
        cout<<"matrix dimension: "<<dim<<endl;
    }
	if(argc>4){
		Width = atoi(argv[4]);
	}
	if(argc>5){
		Height = atoi(argv[5]);
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

// void fix_dither(unsigned char *** input, unsigned char*** output, int threshold,int width, int height, int bbp){
	matrix_dither(image_input,image_ouput,dim,Width,Height,BytesPerPixel);
	writeraw(argv[2],image_ouput,Width,Height,1);
    return 0 ;
}

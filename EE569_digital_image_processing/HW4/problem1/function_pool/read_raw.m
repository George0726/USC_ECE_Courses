function G = read_raw(filename)

	fid=fopen(filename,'rb');

	pixel = fread(fid, inf, 'uchar');
	fclose(fid);

	[Y ,X]=size(pixel);
	Size=(Y*X);
	
	G = zeros(Y,X);

	G(1:Size) = pixel(1:Size);

	% Transpose matrix, to orient it properly
end %function

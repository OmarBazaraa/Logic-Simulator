#include "../CMUgraphicsLib/PNG.h"
#include <iostream>

void ReadPNG(vector<unsigned char>& Image, unsigned int &width, unsigned int& height, const char * filename)
{
	//decode
	unsigned error = lodepng::decode(Image, width, height, filename);
	//if there's an error, display it
	if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}
void WritePNG(window * pWind, image &screen, int x, int y, vector<unsigned char>& Image, unsigned int width, unsigned int height)
{
	pWind->StoreImage(screen, x, y, width, height);
	unsigned char * Arr = screen.GetArr();
	int Size = Image.size();
	long long i;
	for (i = 0; i < Size; i += 4)
	{
		if (Image[i + 3])
		{
			Arr[i] = Image[i + 2];
			Arr[i + 1] = Image[i + 1];
			Arr[i + 2] = Image[i];
		}

	}
	screen.SetArr(Arr);
}

void DrawPNGImage(window * pWind, string r_filename, int x, int y)
{
	const char * filename = r_filename.c_str();
	vector<unsigned char> Image;
	unsigned int width, height;
	image screen;
	ReadPNG(Image, width, height, filename);
	WritePNG(pWind, screen, x, y, Image, width, height);
	pWind->DrawImage(screen, x, y);
}
#include "Beautify.h"
#include <stdio.h>
#include <windows.h>
#include "Gaussian.h"
#include "libutils.h"

#pragma comment(lib, "libutils.lib")

#define INT_MULT(a,b,t)  ((t) = (a) * (b) + 0x80, ((((t) >> 8) + (t)) >> 8))

namespace e
{
	void BlendProc(uint8* dst, uint8* src, int width, int height, int bitCount)
	{
		int lineBytes = WIDTHBYTES(bitCount * width);
		int bpp = bitCount / 8;

		int temp = 0;
		for (int y = 0; y < height; y++)
		{
			uint8* p0 = src + y * lineBytes;
			uint8* p1 = dst + y * lineBytes;

			for (int x = 0; x < width; x++)
			{
				//screen op
				*(p0 + 0) = 255 - INT_MULT((255 - *(p0 + 0)), (255 - *(p1 + 0)), temp);
				*(p0 + 1) = 255 - INT_MULT((255 - *(p0 + 1)), (255 - *(p1 + 1)), temp);
				*(p0 + 2) = 255 - INT_MULT((255 - *(p0 + 2)), (255 - *(p1 + 2)), temp);

				p0 += bpp;
				p1 += bpp;
			}
		}
	}

	Beautify::Beautify(int width, int height)
	{
		this->sigma = 5.0f;
		this->width = width;
		this->height = height;
		this->enable = true;
		this->src = new uint8[width * height * 4];
		this->tmp = new uint8[width * height * 4];
	}


	Beautify::~Beautify()
	{
		if (src)
		{
			delete[] src;
		}

		if (tmp)
		{
			delete[] tmp;
		}
	}

	void Beautify::Process(uint8* buffer, int width, int height, int bitCount)
	{
		int bytes = WIDTHBYTES(width * bitCount) * height;
		memcpy(src, buffer, bytes);

		Gaussian(tmp, src, width, height, bitCount, sigma);
		Gaussian(src, tmp, height, width, bitCount, sigma);

		if (enable)
		{
			BlendProc(buffer, src, width, height, bitCount);
		}
		else
		{
			memcpy(buffer, src, bytes);
		}
	}

	void Beautify::KeyDown(int key)
	{
		if (key == 65) sigma += 0.1f;//a
		if (key == 68) sigma -= 0.1f;//d
		if (key == 70) enable = !enable;
	}
}

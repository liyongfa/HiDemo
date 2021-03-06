#ifndef __CORE_GAUSSIAN_H__
#define __CORE_GAUSSIAN_H__

#include "Defines.h"

namespace e
{
	enum
	{ 
		SIMPLE8 = 0, 
		HIGHT8 = 1, 
		SIMPLE24 = 2, 
		HIGHT24 = 3 
	};

	void Gaussian(uint8* dst
		, uint8* src
		, int width
		, int height
		, int bitCount
		, float sigma
		, int mode);
}

#endif
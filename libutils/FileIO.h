#ifndef __CORE_FILEIO_H__
#define __CORE_FILEIO_H__

namespace e
{
	class FileIO
	{
	public:
		// ���ļ�����bmp�ļ�
		static bool _LoadBitmap(const char* fileName, void** bits, int& size, int&width, int&height, int&channels);
		//����bmp���ļ�
		static bool _SaveBitmap(const char* fileName, const void* bits, int size, int width, int height, int channels);
	};
}

#endif
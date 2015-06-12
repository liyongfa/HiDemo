#include "MainWin.h"
#include <assert.h>
#include "Camera.h"
#include "Beautify.h"

#define WIN_CLASS_NAME (TEXT("BeautifyClass"))

namespace e
{
	static void _UnregisterClass(void)
	{
		::UnregisterClass(WIN_CLASS_NAME, NULL);
	}

	MainWin::MainWin(void)
	{
		hWnd = 0;
		hBitmap = 0;
		beautify = 0;
		beautify = new Beautify(480, 360);
		assert(beautify);
	}

	MainWin::~MainWin(void)
	{
		if (beautify)
		{
			delete beautify;
		}
	}

	bool MainWin::Create(void)
	{
		WNDCLASSEX wc;
		memset(&wc, 0, sizeof(wc));

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpszClassName = WIN_CLASS_NAME;
		wc.lpfnWndProc = MainWin::_WindowProc;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.hIcon = ::LoadIcon(::GetModuleHandle(0), MAKEINTRESOURCE(101));

		if (wc.hIcon == NULL)
		{
			wc.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
		}

		wc.hIconSm = (HICON)::LoadImage(GetModuleHandle(0)
			, MAKEINTRESOURCE(101)
			, IMAGE_ICON
			, 16
			, 16
			, LR_DEFAULTCOLOR);

		if (wc.hIconSm == NULL)
		{
			wc.hIconSm = ::LoadIcon(NULL, IDI_APPLICATION);
		}

		wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
		wc.lpszMenuName = NULL;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = NULL;

		if (RegisterClassEx(&wc))
		{
			atexit(&_UnregisterClass);
		}
		else
		{
			return false;
		}

		DWORD ws = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
		int x = 100, y = 100, w = 600, h = 500;
		hWnd = ::CreateWindowEx(WS_EX_APPWINDOW
			, WIN_CLASS_NAME
			, TEXT("BeautifyDemo")
			, ws
			, x, y, w, h
			, NULL
			, NULL
			, ::GetModuleHandle(NULL)
			, 0);

		if (hWnd == 0)
		{
			return false;
		}

		::SetWindowLongPtr(hWnd, GWL_USERDATA, (UINT_PTR)this);

		return true;
	}

	void MainWin::ShowWindow(void)
	{
		assert(hWnd);
		::ShowWindow(hWnd, SW_SHOW);
	}

	void MainWin::OnCreate(void)
	{

	}

	void MainWin::OnKeyDown(int key)
	{
		if (key == 82) Camera::Start();//r
		if (key == 83) Camera::Stop();//s

		beautify->KeyDown(key);
	}

	void MainWin::OnDestroy(void)
	{
		delete this;
	}

	HBITMAP MainWin::CreateBitmap(int width, int height, int bitCount)
	{
		BITMAPINFOHEADER bi = { 0 };
		int sizeImage = WIDTHBYTES(width * bitCount) * height;
		bi.biSize = sizeof(bi);
		bi.biWidth = width;
		bi.biHeight = height;
		bi.biBitCount = bitCount;
		bi.biPlanes = 1;
		bi.biSizeImage = sizeImage;
		bi.biCompression = 0;
		bi.biClrImportant = 0;
		bi.biClrUsed = 0;
		bi.biHeight = -bi.biHeight;

		HDC hDC = ::GetDC(hWnd);
		HBITMAP hBitmap = CreateDIBitmap(hDC
			, &bi
			, CBM_INIT
			, NULL
			, (BITMAPINFO*)&bi
			, DIB_RGB_COLORS);

		::ReleaseDC(hWnd, hDC);

		return hBitmap;
	}

	void MainWin::SetBitmap(uint8* bits, int width, int height, int bitCount)
	{
		int size = WIDTHBYTES(width * bitCount) * height;
		::SetBitmapBits(hBitmap, size, (void*)bits);
	}

	void MainWin::DrawBitmap(HDC hDC, HBITMAP hBitmap, int width, int height)
	{
		HDC hMemDC = CreateCompatibleDC(hDC);
		::SelectObject(hMemDC, hBitmap);
		::BitBlt(hDC, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY);
		::DeleteDC(hMemDC);
	}

	void MainWin::UpdateView(void)
	{
		if (hBitmap != 0 && hWnd != 0)
		{
			HDC hDC = ::GetDC(hWnd);
			RECT rect;
			::GetClientRect(hWnd, &rect);

			::FillRect(hDC, &rect, (HBRUSH)::GetStockObject(WHITE_BRUSH));

			DrawBitmap(hDC, hBitmap, 480, 360);
			::ReleaseDC(hWnd, hDC);
		}
	}

	void MainWin::MainLoop(void)
	{
		MSG msg;
		while (::GetMessage(&msg, 0, 0, 0))
		{
			if (msg.message == WM_QUIT) break;

			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}

	LRESULT CALLBACK MainWin::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_CREATE:
			OnCreate();
			break;
		case WM_PAINT:
			ValidateRect(hWnd, NULL);
			UpdateView();
			break;
		case WM_KEYDOWN:
			OnKeyDown((int)wParam);
			break;
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		case WM_DESTROY:
			OnDestroy();
			break;
		default:
			return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		return 0;
	}

	LRESULT CALLBACK MainWin::_WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		MainWin* win = (MainWin*)::GetWindowLongPtr(hWnd, GWL_USERDATA);
		if (win)
		{
			return win->WindowProc(hWnd, uMsg, wParam, lParam);
		}
		else if (uMsg == WM_ERASEBKGND)
		{
			RECT rect;
			::GetClientRect(hWnd, &rect);
			::FillRect((HDC)wParam, &rect, (HBRUSH)::GetStockObject(WHITE_BRUSH));
			return 0;
		}
		else
		{
			return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}

	void MainWin::SampleHandle(uchar* buffer, int width, int height, int bitCount)
	{
		if (beautify)
		{
			beautify->Process(buffer, width, height, bitCount);

			if (hBitmap == 0)
			{
				hBitmap = CreateBitmap(width, height, bitCount);
				assert(hBitmap);
			}

			SetBitmap(buffer, width, height, bitCount);

			assert(hWnd);
			HDC hDC = ::GetDC(hWnd);
			DrawBitmap(hDC, hBitmap, width, height);
			::ReleaseDC(hWnd, hDC);
		}
	}
}

// xy-safety
// i have no idea why someone else didnt do this but anyways uhhhhhhhhhhhhhgico8d7pskhjjtjkftgkjfkik
// credits to jazzstuff

#include <windows.h>
#include <tchar.h>
//#include <ctime>
//#include <iostream>
//#include <windowsx.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"Msimg32.lib")
#include <math.h>
//#include <time.h>
#define M_PI   3.14159265358979323846264338327950288
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;

namespace Colors
{
	//These HSL functions was made by Wipet, credits to him!
	//OBS: I used it in 3 payloads

	//Btw ArTicZera created HSV functions, but it sucks unfortunatelly
	//So I didn't used in this malware.

	HSL rgb2hsl(RGBQUAD rgb)
	{
		HSL hsl;

		BYTE r = rgb.rgbRed;
		BYTE g = rgb.rgbGreen;
		BYTE b = rgb.rgbBlue;

		FLOAT _r = (FLOAT)r / 255.f;
		FLOAT _g = (FLOAT)g / 255.f;
		FLOAT _b = (FLOAT)b / 255.f;

		FLOAT rgbMin = fmin(fmin(_r, _g), _b);
		FLOAT rgbMax = fmax(fmax(_r, _g), _b);

		FLOAT fDelta = rgbMax - rgbMin;
		FLOAT deltaR;
		FLOAT deltaG;
		FLOAT deltaB;

		FLOAT h = 0.f;
		FLOAT s = 0.f;
		FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

		if (fDelta != 0.f)
		{
			s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
			deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

			if (_r == rgbMax)      h = deltaB - deltaG;
			else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
			else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
			if (h < 0.f)           h += 1.f;
			if (h > 1.f)           h -= 1.f;
		}

		hsl.h = h;
		hsl.s = s;
		hsl.l = l;
		return hsl;
	}

	RGBQUAD hsl2rgb(HSL hsl)
	{
		RGBQUAD rgb;

		FLOAT r = hsl.l;
		FLOAT g = hsl.l;
		FLOAT b = hsl.l;

		FLOAT h = hsl.h;
		FLOAT sl = hsl.s;
		FLOAT l = hsl.l;
		FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

		FLOAT m;
		FLOAT sv;
		FLOAT fract;
		FLOAT vsf;
		FLOAT mid1;
		FLOAT mid2;

		INT sextant;

		if (v > 0.f)
		{
			m = l + l - v;
			sv = (v - m) / v;
			h *= 6.f;
			sextant = (INT)h;
			fract = h - sextant;
			vsf = v * sv * fract;
			mid1 = m + vsf;
			mid2 = v - vsf;

			switch (sextant)
			{
			case 0:
				r = v;
				g = mid1;
				b = m;
				break;
			case 1:
				r = mid2;
				g = v;
				b = m;
				break;
			case 2:
				r = m;
				g = v;
				b = mid1;
				break;
			case 3:
				r = m;
				g = mid2;
				b = v;
				break;
			case 4:
				r = mid1;
				g = m;
				b = v;
				break;
			case 5:
				r = v;
				g = m;
				b = mid2;
				break;
			}
		}

		rgb.rgbRed = (BYTE)(r * 255.f);
		rgb.rgbGreen = (BYTE)(g * 255.f);
		rgb.rgbBlue = (BYTE)(b * 255.f);

		return rgb;
	}
}
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) { //Credits to Void_/GetMBR
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}
/*COLORREF RndRGB() {
	int clr = rand() % 5;
	if (clr == 0) return RGB(255, 0, 0); if (clr == 1) return RGB(0, 255, 0); if (clr == 2) return RGB(0, 0, 255); if (clr == 3) return RGB(255, 0, 255); if (clr == 4) return RGB(255, 255, 0);
}*/
DWORD WINAPI cur1(LPVOID lpParam) {
	POINT cursor;
	while (true) {
		INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
		int X = rand() % w;
		int Y = rand() % h;
		HDC hdc = GetDC(NULL);
		DrawIcon(hdc, X, Y, LoadCursor(NULL, IDC_ARROW));
		ReleaseDC(NULL, hdc);
		Sleep(10);
		if ((rand() % 900 + 301) % 900 == 80) RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
	}
	return 0x00;
}
DWORD WINAPI cur2(LPVOID lpParam) {
	while (true) {
		HDC hdc = GetDC(HWND_DESKTOP);
		int icon_x = GetSystemMetrics(SM_CXICON);
		int icon_y = GetSystemMetrics(SM_CYICON);
		POINT cursor;
		GetCursorPos(&cursor);
		DrawIcon(hdc, cursor.x - icon_x, cursor.y - icon_y, LoadCursor(NULL, IDC_HAND));
		ReleaseDC(NULL, hdc);
	}
	return 0x00;
}
DWORD WINAPI PRGBtriple1(LPVOID lpstart) {
	HDC desk = GetDC(0);
	HWND wnd = GetDesktopWindow();
	int sw = GetSystemMetrics(SM_CXSCREEN); // Use SM_CXSCREEN for screen width
	int sh = GetSystemMetrics(SM_CYSCREEN); // Use SM_CYSCREEN for screen height
	BITMAPINFO bmi = { 40, sw, sh, 1, 24 };
	PRGBTRIPLE rgbtriple;

	// Create a color modifier variable to control the color effect
	int colorModifier = 0;

	for (;;) {
		desk = GetDC(0);
		HDC deskMem = CreateCompatibleDC(desk);
		HBITMAP scr = CreateDIBSection(desk, &bmi, 0, (void**)&rgbtriple, 0, 0);
		SelectObject(deskMem, scr);
		BitBlt(deskMem, 0, 0, sw, sh, desk, 0, 0, SRCCOPY);

		for (int i = 0; i < sw * sh; i++) {
			int x = i % sw, y = i / sw;

			// Apply a color effect based on colorModifier
			rgbtriple[i].rgbtRed += GetRValue(x ^ y) + colorModifier;
			rgbtriple[i].rgbtGreen += GetGValue(x + y) - colorModifier;
			rgbtriple[i].rgbtRed += GetRValue(x ^ y) + colorModifier;

			// Change colorModifier to create dynamic color variation
			colorModifier = (colorModifier + 1) % 1;
		}

		BitBlt(desk, 0, 0, sw, sh, deskMem, 0, 0, SRCCOPY);
		ReleaseDC(wnd, desk);
		DeleteDC(desk);
		DeleteDC(deskMem);
		DeleteObject(scr);
	}
}
DWORD WINAPI PRGBtriple2(LPVOID lpstart) {
	HDC desk = GetDC(0);
	HWND wnd = GetDesktopWindow();
	int sw = GetSystemMetrics(SM_CXSCREEN); // Use SM_CXSCREEN for screen width
	int sh = GetSystemMetrics(SM_CYSCREEN); // Use SM_CYSCREEN for screen height
	BITMAPINFO bmi = { 40, sw, sh, 1, 24 };
	PRGBTRIPLE rgbtriple;

	// Create a color modifier variable to control the color effect
	int colorModifier = 0;

	for (;;) {
		desk = GetDC(0);
		HDC deskMem = CreateCompatibleDC(desk);
		HBITMAP scr = CreateDIBSection(desk, &bmi, 0, (void**)&rgbtriple, 0, 0);
		SelectObject(deskMem, scr);
		BitBlt(deskMem, 0, 0, sw, sh, desk, 0, 0, SRCCOPY);

		for (int i = 0; i < sw * sh; i++) {
			int x = i % sw, y = i / sw;

			// Apply a color effect based on colorModifier
			rgbtriple[i].rgbtRed += GetRValue(x & y) + colorModifier;
			rgbtriple[i].rgbtGreen += GetGValue(x * y) - colorModifier;
			rgbtriple[i].rgbtBlue += GetBValue(x * y) + colorModifier;

			// Change colorModifier to create dynamic color variation
			colorModifier = (colorModifier + 13) % 44;
		}

		BitBlt(desk, 0, 0, sw, sh, deskMem, 0, 0, SRCCOPY);
		ReleaseDC(wnd, desk);
		DeleteDC(desk);
		DeleteDC(deskMem);
		DeleteObject(scr);
	}
}
DWORD WINAPI PRGBtriple3(LPVOID lpstart) {
	HDC desk = GetDC(0);
	HWND wnd = GetDesktopWindow();
	int sw = GetSystemMetrics(SM_CXSCREEN); // Use SM_CXSCREEN for screen width
	int sh = GetSystemMetrics(SM_CYSCREEN); // Use SM_CYSCREEN for screen height
	BITMAPINFO bmi = { 40, sw, sh, 1, 24 };
	PRGBTRIPLE rgbtriple;

	// Create a color modifier variable to control the color effect
	int colorModifier = 0;

	for (;;) {
		desk = GetDC(0);
		HDC deskMem = CreateCompatibleDC(desk);
		HBITMAP scr = CreateDIBSection(desk, &bmi, 0, (void**)&rgbtriple, 0, 0);
		SelectObject(deskMem, scr);
		BitBlt(deskMem, 0, 0, sw, sh, desk, 0, 0, SRCCOPY);

		for (int i = 0; i < sw * sh; i++) {
			int x = i % sw, y = i / sw;

			// Apply a color effect based on colorModifier
			rgbtriple[i].rgbtRed += GetGValue(x & y ^ x * y + x & y) + colorModifier;
			rgbtriple[i].rgbtGreen += GetBValue(255) - colorModifier;
			rgbtriple[i].rgbtBlue += GetGValue(x ^ y) + colorModifier;

			// Change colorModifier to create dynamic color variation
			colorModifier = (colorModifier + 420) % 69; //im not funny
		}

		BitBlt(desk, 0, 0, sw, sh, deskMem, 0, 0, SRCCOPY);
		ReleaseDC(wnd, desk);
		DeleteDC(desk);
		DeleteDC(deskMem);
		DeleteObject(scr);
	}
}
DWORD WINAPI Octagon(LPVOID lpstart) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;

	while (true) {
		HDC hdc = GetDC(NULL);
		x += incrementor * signX;
		y += incrementor * signY;

		int centerX = x + 50;
		int centerY = y + 50;
		int radius = 50;

		POINT octagonPoints[8];
		for (int i = 0; i < 8; ++i) {
			double angle = 2.0 * M_PI * i / 8;
			octagonPoints[i].x = centerX + static_cast<int>(radius * sqrt(angle));
			octagonPoints[i].y = centerY + static_cast<int>(radius * sin(angle));
		}

		HBRUSH brush = CreateSolidBrush(Hue(239));
		SelectObject(hdc, brush);
		Polygon(hdc, octagonPoints, 8);

		if (centerY >= GetSystemMetrics(SM_CYSCREEN)) {
			signY = -1;
		}

		if (centerX >= GetSystemMetrics(SM_CXSCREEN)) {
			signX = -1;
		}

		if (centerY <= 0) {
			signY = 1;
		}

		if (centerX <= 0) {
			signX = 1;
		}

		Sleep(1);
		DeleteObject(brush);
		ReleaseDC(NULL, hdc);
	}
}
DWORD WINAPI PlgBlt1(LPVOID lpstart) {
	HDC hdc = GetDC(NULL);
	RECT wRect;
	POINT wPt[3];
	while (true) {
		hdc = GetDC(NULL);
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left + 6;
		wPt[0].y = wRect.top - 6;
		wPt[1].x = wRect.right + 6;
		wPt[1].y = wRect.top + 6;
		wPt[2].x = wRect.left - 6;
		wPt[2].y = wRect.bottom + 6;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right + wRect.left, wRect.bottom + wRect.top, 0, 0, 0);
		ReleaseDC(NULL, hdc);
	}
}
DWORD WINAPI PRGBQUAD1(LPVOID lpstart) {
	HDC hdcScreen = GetDC(NULL), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(NULL);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].g += 5;
			rgbScreen[i].b += x + y * x & y;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI Textout1(LPVOID lpstart) {
	int x = GetSystemMetrics(0); int y = GetSystemMetrics(1);
	LPCSTR text = 0;
	while (true) {
		for (int i = 0; i < x; i++) {
			HDC hdc = GetDC(NULL);
			text = "larped computer";
			SetBkColor(hdc, RGB(rand() % 2, rand() % 2, rand() % 2));
			SetTextColor(hdc, Hue(239));
			TextOutA(hdc, rand() % x, rand() % y, text, strlen(text));
			Sleep(10);
			ReleaseDC(NULL, hdc);
		}
		if ((rand() % 100 + 1) % 67 == 0) InvalidateRect(0, 0, 0);
	}
	return 0x00;
}
DWORD WINAPI gradientfilltriangle(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);


	while (1)
	{
		hdc = GetDC(NULL);
		// Create an array of TRIVERTEX structures that describe
// positional and color values for each vertex.
		TRIVERTEX vertex[3];
		vertex[0].x = rand() % w;
		vertex[0].y = rand() % h;
		vertex[0].Red = 0xbf00;
		vertex[0].Green = 0xff00;
		vertex[0].Blue = 0x0000;
		vertex[0].Alpha = 0x0000;

		vertex[1].x = rand() % w;
		vertex[1].y = rand() % h;
		vertex[1].Red = 0xf000;
		vertex[1].Blue = 0xb000;
		vertex[1].Blue = 0x9000;
		vertex[1].Alpha = 0x0000;

		vertex[2].x = rand() % w;
		vertex[2].y = rand() % h;
		vertex[2].Red = 0xfb00;
		vertex[2].Green = 0xb800;
		vertex[2].Red = 0x0000;
		vertex[2].Alpha = 0x0000;

		// Create a GRADIENT_TRIANGLE structure that
		// references the TRIVERTEX vertices.
		GRADIENT_TRIANGLE gTriangle;
		gTriangle.Vertex1 = 0;
		gTriangle.Vertex2 = 1;
		gTriangle.Vertex3 = 2;

		// Draw a shaded triangle.
		GradientFill(hdc, vertex, 3, &gTriangle, 1, GRADIENT_FILL_TRIANGLE);
		ReleaseDC(0, hdc);
		Sleep(1);
	}

	return 0x00;
}
DWORD WINAPI HSL1(LPVOID lpstart) {
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				int fx = x & y + x * i;

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = (float)fmod((double)hslcolor.h + (double)(fx) / 100000.0 + 0.09, 1.0);
				hslcolor.s = 1.f;

				if (hslcolor.l < .4f)
				{
					hslcolor.l += .4f;
				}

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI Blur1(LPVOID lpvd) {
	//Credits to ArTicZera and Rekto
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	RECT rekt;
	POINT wPt[3];
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);

	BITMAPINFO bmpi = { 0 };
	BLENDFUNCTION blur;
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	bmp = CreateDIBSection(hdc, &bmpi, 0, 0, NULL, 0);
	SelectObject(hdcCopy, bmp);

	blur.BlendOp = AC_SRC_OVER;
	blur.BlendFlags = 0;
	blur.AlphaFormat = 0;
	blur.SourceConstantAlpha = 10;

	while (1) {
		hdc = GetDC(NULL);
		//StretchBlt(hdcCopy, 0, 10, w, h + 20, hdc, 0, 0, w, h, 0x999999);
		GetWindowRect(GetDesktopWindow(), &rekt);
		wPt[0].x = rekt.left - 10;
		wPt[0].y = rekt.top - 10;
		wPt[1].x = rekt.right;
		wPt[1].y = rekt.top - 10;
		wPt[2].x = rekt.left - 10;
		wPt[2].y = rekt.bottom + 10;
		PlgBlt(hdcCopy, wPt, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
		AlphaBlend(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, blur);
		//Sleep(rand() % 25);
		ReleaseDC(0, hdc);
	}
	return 0x00;
}
DWORD WINAPI staticFinale(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb = (rand() % 0x100) * 0x010101;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * t * (1 + (t >> 6 & t >> 8)) & 128);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * t * (5 + (t >> 6 & t >> 12)) & 36728);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * t * (2 + (t >> 3 & t >> 9)) & 128);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound4() { //credits to Wooshydudebro (he did this ig)
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8100, 8100, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8100 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(64 * ((t >> 9 ^ (t >> 5) - 5 ^ 5) % 13 * t / 10) + 128);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound5() { //credits to Wooshydudebro (he did this ig)
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(5 * (t + (t ^ t >> 9) ^ 9) | 19 * (5 * t >> 43 | 15 * t >> 4) & (7 * t >> 172) / 2 * t * ((t >> 9 | t >> 13) & 15) & 129 | t * ((t >> 9 | 3 < t) & 25 & t >> 10));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
HHOOK hHook = NULL;

LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HCBT_ACTIVATE)
	{
		HWND hDlg = (HWND)wParam;
		HWND hBtnWnd = GetDlgItem(hDlg, IDOK);
		if (hBtnWnd != NULL)
			EnableWindow(hBtnWnd, FALSE);
	}

	return CallNextHookEx(hHook, nCode, wParam, lParam);
}
DWORD WINAPI error(LPVOID lpParam) {
	//...

	hHook = SetWindowsHookEx(WH_CBT, &CBTProc, NULL, GetCurrentThreadId());

	MessageBoxW(NULL, L"HOWK DOIUROAUYORYE OYO YU STOAEMA YMN E DSYDSNBES$%#!#!&%#!$&%#!$%&& THGSANT KSBUIT. YO URED BGOUNRCED  GFDRSEW4IJERTGEWOOERTED GIOFEHE DO R6ER59867386795733967896783459678978624596869724598672459687259687BN YEHARDA!!!$&%!twr%!#", NULL, MB_ICONERROR);

	if (hHook != NULL)
		UnhookWindowsHookEx(hHook);

	//...
	return 0;
}
int CALLBACK WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, int       nCmdShow
)
{
	if (MessageBoxW(NULL, L"This is a Safety Malware.\nClick yes to run.\nClick no to exit.", L"xy.exe by Kaieko (GDI Only by Maxi)", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"Are you sure? It still contains flashing lights - NOT for epilepsy", L"Final Warning - xy.exe (GDI Only by Maxi)", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			Sleep(2000);
			CreateThread(0, 0, error, 0, 0, 0);
			Sleep(2000);
			HANDLE threadCursor1 = CreateThread(0, 0, cur1, 0, 0, 0);
			Sleep(1000);
			HANDLE threadCursor2 = CreateThread(0, 0, cur2, 0, 0, 0);
			//CreateThread(0, 0, polygon1, 0, 0, 0);
			//CreateThread(0, 0, notaskbar, 0, 0, 0);
			Sleep(1000);
			HANDLE thread1 = CreateThread(0, 0, PRGBtriple1, 0, 0, 0);
			sound1();
			Sleep(30000);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
			//TerminateThread(thread1dot1, 0);
			//CloseHandle(thread1dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread2 = CreateThread(0, 0, PRGBtriple2, 0, 0, 0);
			sound2();
			Sleep(30000);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
			//TerminateThread(thread1dot1, 0);
			//CloseHandle(thread1dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread3 = CreateThread(0, 0, PRGBtriple3, 0, 0, 0);
			HANDLE thread3dot1 = CreateThread(0, 0, Octagon, 0, 0, 0);
			sound3();
			Sleep(30000);
			TerminateThread(thread3, 0);
			CloseHandle(thread3);
			//TerminateThread(thread3dot1, 0);
			//CloseHandle(thread3dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread4 = CreateThread(0, 0, PRGBQUAD1, 0, 0, 0);
			HANDLE thread4dot1 = CreateThread(0, 0, PlgBlt1, 0, 0, 0);
			HANDLE thread4dot2 = CreateThread(0, 0, Textout1, 0, 0, 0);
			sound4();
			Sleep(30000);
			TerminateThread(thread4, 0);
			CloseHandle(thread4);
			TerminateThread(thread4dot1, 0);
			CloseHandle(thread4dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread5 = CreateThread(0, 0, HSL1, 0, 0, 0);
			HANDLE thread5dot1 = CreateThread(0, 0, gradientfilltriangle, 0, 0, 0);
			HANDLE thread5dot2 = CreateThread(0, 0, Blur1, 0, 0, 0);
			sound5();
			Sleep(30000);
			TerminateThread(thread5, 0);
			CloseHandle(thread5);
			TerminateThread(thread5dot2, 0);
			CloseHandle(thread5dot2);
			InvalidateRect(0, 0, 0);
			HANDLE threadFINAL = CreateThread(0, 0, staticFinale, 0, 0, 0);
			Sleep(1000);
			return 0;
		}
	}
}
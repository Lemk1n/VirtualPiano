#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <stdio.h>
#include <gdiplus.h>
#include <mmsystem.h>

#pragma comment(lib, "Winmm.lib")

#pragma comment(lib, "gdiplus.lib")



using namespace Gdiplus;
using std::string;

Gdiplus::Image* KB;
Gdiplus::Image* Press;

bool PressFlag = false;

int xPress = 10000;
int yPress = 10000;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndKBProc(HWND, UINT, WPARAM, LPARAM);

void DrawImage(HDC hdc, HWND hKBWnd, PAINTSTRUCT ps)//3
{
	HDC          hdcMem;
	HBITMAP      hbmMem;
	HANDLE       hOld;

	RECT clientArea;
	GetWindowRect(hKBWnd, &clientArea);

	// —оздаем off-screen DC дл€ двойной буферизации

	hdcMem = CreateCompatibleDC(hdc); //breakPoint
	hbmMem = CreateCompatibleBitmap(hdc, 1000, 1000);
	hOld = SelectObject(hdcMem, hbmMem);

	// «десь рисуем в hdcMem
	FillRect(hdcMem, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
	Graphics graphics(hdcMem);

	SelectObject(hdc, GetStockObject(DC_BRUSH)); //делаем кисть активной
	SetDCBrushColor(hdc, RGB(255, 0, 0));

	graphics.DrawImage(KB, 0, 0);
	//graphics.DrawImage(Press, 0000, 0000);
	
	if (PressFlag)
	{
		graphics.DrawImage(Press, xPress, yPress);
	}

	// ¬ыводим построенное  изображение и пам€ти на экран
	BitBlt(hdc, 0, 0, 1000, 1000, hdcMem, 0, 0, SRCCOPY);

	// ќсвобождаем пам€ть
	SelectObject(hdcMem, hOld);
	DeleteObject(hbmMem);
	DeleteDC(hdcMem);
}

void CreateKBWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wcexKB;
	HWND hKBWnd; //hWndKB

	wcexKB.cbClsExtra = 0;
	wcexKB.cbWndExtra = 0;
	wcexKB.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcexKB.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcexKB.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcexKB.hIconSm = wcexKB.hIcon;
	wcexKB.hInstance = hInstance;
	wcexKB.lpfnWndProc = (WNDPROC)WndKBProc;
	wcexKB.cbSize = sizeof(WNDCLASSEX);
	wcexKB.style = CS_VREDRAW | CS_HREDRAW;
	wcexKB.lpszMenuName = NULL;
	wcexKB.lpszClassName = "KBWndClass";

	RegisterClassEx(&wcexKB);
}

HWND hKBWnd;

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

	Gdiplus::GdiplusStartupInput gdiplusStartupInput; // —в€зано с загрузкой картинки
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL); // ¬ключаем GDI+

	MSG msg;
	HDC hdc;

	CreateKBWindow(hInstance);
	hKBWnd = CreateWindow("KBWndClass", " лавиатура", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, 646, 313, 646, 313, NULL, NULL, hInstance, NULL);
	hdc = GetDC(hKBWnd);
	ShowWindow(hKBWnd, nCmdShow);
	UpdateWindow(hKBWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;

}

void SetCoordinates(char actual)
{
	switch (actual)
	{
	case '1':
	{
		xPress = 1;
		yPress = 181;
		break;
	}
	case '2':
	{
		xPress = 46;
		yPress = 181;
		break;
	}
	case '3':
	{
		xPress = 91;
		yPress = 181;
		break;
	}
	case '4':
	{
		xPress = 136;
		yPress = 181;
		break;
	}
	case '5':
	{
		xPress = 181;
		yPress = 181;
		break;
	}
	case '6':
	{
		xPress = 226;
		yPress = 181;
		break;
	}
	case '7':
	{
		xPress = 271;
		yPress = 181;
		break;
	}
	case '8':
	{
		xPress = 316;
		yPress = 181;
		break;
	}
	case '9':
	{
		xPress = 361;
		yPress = 181;
		break;
	}
	case '0':
	{
		xPress = 406;
		yPress = 181;
		break;
	}
	case '-':
	{
		xPress = 451;
		yPress = 181;
		break;
	}
	case '=':
	{
		xPress = 496;
		yPress = 181;
		break;
	}
	case 'q':
	{
		xPress = 541;
		yPress = 181;
		break;
	}
	case 'й':
	{
		xPress = 541;
		yPress = 181;
		break;
	}
	case 'w':
	{
		xPress = 586;
		yPress = 181;
		break;
	}
	case 'ц':
	{
		xPress = 586;
		yPress = 181;
		break;
	}
	default:
		xPress = 10000;
		yPress = 10000;
		break;
	}
}

LRESULT CALLBACK WndKBProc(HWND hKBWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(EXIT_SUCCESS);
		break;
	}

	case WM_CREATE: //при создании окна
	{	

		KB = Gdiplus::Image::FromFile(L"E://_STUDY//_T–≈“№я„»//_ урсач//pianoKeys.jpg");
		Press = Gdiplus::Image::FromFile(L"E://_STUDY//_T–≈“№я„»//_ урсач//Press.jpg");
		InvalidateRect(hKBWnd, NULL, FALSE);
		break;
	}

	case WM_CHAR:
	{//breakPoint
		char ch1 = (char)wParam;
		if (ch1 != NULL)
		{
			PressFlag = true;
			InvalidateRect(hKBWnd, NULL, FALSE);
		}
		else
			PressFlag = false;
	
		SetCoordinates(ch1);
		InvalidateRect(hKBWnd, NULL, FALSE);
	
		//E://_STUDY//_T–≈“№я„»//_ урсач//1Octave//
		switch (wParam)
		{
		case '1':
		{
			PlaySound("1до.wav", NULL, SND_SYNC);
			break;
		}
		case '2':
		{
			PlaySound("2ре.wav", NULL, SND_ASYNC);
			break;
		}
		case '3':
		{
			PlaySound("3ми.wav", NULL, SND_ASYNC);
			break;
		}
		case '4':
		{
			PlaySound("4фа.wav", NULL, SND_ASYNC);
			break;
		}
		case '5':
		{
			PlaySound("5соль.wav", NULL, SND_ASYNC);
			break;
		}
		case '6':
		{
			PlaySound("6л€.wav", NULL, SND_ASYNC);
			break;
		}
		case '7':
		{
			PlaySound("7си.wav", NULL, SND_ASYNC);
			break;
		}
		case '8':
		{
			PlaySound("8до.wav", NULL, SND_ASYNC);
			break;
		}
		case '9':
		{
			PlaySound("9ре.wav", NULL, SND_ASYNC);
			break;
		}
		case '0':
		{
			PlaySound("0ми.wav", NULL, SND_ASYNC);
			break;
		}
		case '-':
		{
			PlaySound("-фа.wav", NULL, SND_ASYNC);
			break;
		}
		case '=':
		{
			PlaySound("=соль.wav", NULL, SND_ASYNC);
			break;
		}
		case 'q':
		{
			PlaySound("qл€.wav", NULL, SND_ASYNC);
			break;
		}
		case 'й':
		{
			PlaySound("qл€.wav", NULL, SND_ASYNC);
			break;
		}
		case 'w':
		{
			PlaySound("wси.wav", NULL, SND_ASYNC);
			break;
		}
		case 'ц':
		{
			PlaySound("wси.wav", NULL, SND_ASYNC);
			break;
		}
		default:
			break;
		}
		break;
	}
	case WM_SIZE: //при изменении размера окна
	{

	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hKBWnd, &ps);

		DrawImage(hdc, hKBWnd, ps);

		EndPaint(hKBWnd, &ps);
	}

	}
	return DefWindowProc(hKBWnd, message, wParam, lParam);

}





#pragma once
#include "My_Hook.h"


HHOOK g_hHOOK = NULL;			//��L�_�l
HHOOK mouse_HOOK = NULL;		//�ƹ��_�l
HHOOK m_hook = NULL;			//�i�{

bool MOD1 = TRUE;
bool MOD2 = false;

float Speed = 2; //�[�t����  0�O��t

DWORD MIN1 = 0;
DWORD MAX1 = 0;

LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	return CallNextHookEx(m_hook, nCode, wParam, lParam);
}


LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	//if (nCode < 0)  return CallNextHookEx(mouse_HOOK, nCode, wParam, lParam);

	/*
	snprintf(tmp, sizeof(wParam), "%d", wParam);
	OutputDebugStringA(tmp);
	*/
	switch (wParam) {
	case WM_LBUTTONDOWN:		//"���U�ƹ�����";
		break;
	case WM_LBUTTONUP:		//"��}�ƹ�����";
		break;
	case WM_MBUTTONDOWN:		//"���U�ƹ�����";
								//MOD2 = TRUE;
		break;
	case WM_MBUTTONUP:		//"��}�ƹ�����";
							//MOD2 = FALSE;
		break;
	case WM_MOUSEMOVE:		//"�ƹ����ʤ�";
		break;
	case WM_MOUSEWHEEL:		// "���ʺu��";
		break;
	case WM_RBUTTONDOWN:		// "���U�ƹ��k��";
		break;
	case WM_RBUTTONUP:		// "��}�ƹ��k��";
		break;
	}
	return CallNextHookEx(mouse_HOOK, nCode, wParam, lParam);
}



int value1 = 0, value2 = 0, value3 = 0;
LRESULT CALLBACK HookKeyboardMsg(int nCode, WPARAM wParam, LPARAM lParam)	//��Lhook
{

	/*	�ΨӧP�_ALT�O�_���U
	if (lParam & 0x20000000)
	{
	bKeyAlt = TRUE;
	}
	*/


	if ((lParam & 0x80000000) == 0)	//1=�u�_  0=���U
	{
		switch (wParam)
		{
		case VK_NUMPAD0:		//V1��
			Speed = 0;
			//MyTextOut(L"NumVertices");
			//MyTextOut(IntToWchar_t(value1));
			//MyTextOut(L"\r\n");
			break;

		case VK_NUMPAD1:		//v2��
			MOD1 = !MOD1;
/*
			MyTextOut(L"startIndex");
			MyTextOut(IntToWchar_t(value2));
			MyTextOut(L"\r\n");*/
			break;
		case VK_NUMPAD2:		//v3��
			//MyTextOut(L"primCount");
			//MyTextOut(IntToWchar_t(value3));
			//MyTextOut(L"\r\n");
			break;
		case VK_NUMPAD3:

			break;
		case VK_NUMPAD4:
			//value2 -= 5;
			break;
		case VK_NUMPAD5:
			//value3 -= 5;
			break;
		case VK_NUMPAD6:

			break;
		case VK_NUMPAD7:
			//value2 += 5;
			break;
		case VK_NUMPAD8:
			//value3 += 5;
			break;
		case VK_NUMPAD9:
			//MyTextOut(L"�h�X����");
			//MOD2 = !MOD2;
			break;
		case VK_UP:
			//value1 += 1;
			Speed += 0.01;
			break;
		case VK_DOWN:
			Speed -= 0.01;
			//value1 -= 1;
			break;
		case VK_RIGHT:
			
			break;
		default:
			break;
		}

	}

	//-------------------------
	/*
	if ( wParam != 257 )return CallNextHookEx(g_hHOOK, nCode, wParam, lParam);


	if (GetAsyncKeyState(VK_NUMPAD7) & 0x8000)
	{

	//MyTextOut(L"MIN");
	//MyTextOut(IntToWchar_t(value2));
	}
	if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
	{
	value2 -= 5;
	//MyTextOut(L"MIN");
	//MyTextOut(IntToWchar_t(value2));
	}
	if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000)
	{
	value3 += 5;
	//MyTextOut(L"MAX");
	//MyTextOut(IntToWchar_t(value3));
	}
	if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
	{
	value3 -= 5;
	//MyTextOut(L"MAX");
	//MyTextOut(IntToWchar_t(value3));
	}

	//********************


	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
	value1 +=5 ;
	MyTextOut(IntToWchar_t(value1));


	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
	value1 -= 5 ;
	MyTextOut(IntToWchar_t(value1));
	}
	//--------***********************
	if (GetAsyncKeyState(VK_NUMPAD9) & 0x8000) MOD2 = !MOD2;
	//if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000) MOD1 = !MOD1;
	//****************************

	if (GetAsyncKeyState(VK_NUMPAD0) & 0x8000)
	{
	MyTextOut(L"NumVertices");
	MyTextOut(IntToWchar_t(value1));
	}//NumVertices, startIndex, primCount

	if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
	{
	MyTextOut(L"startIndex");
	MyTextOut(IntToWchar_t(value2));
	}
	if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
	{
	MyTextOut(L"primCount");
	MyTextOut(IntToWchar_t(value3));
	}
	*/


	return CallNextHookEx(g_hHOOK, nCode, wParam, lParam);
}

void mouse_auto()
{
	/*
	if (MOD2 == TRUE)
	{
	HDC PIXE1 = GetDC(hwnd);			//����
	int nScreenWidth =INT( GetDeviceCaps(PIXE1, HORZSIZE)) / 2;
	int nScreenHeight =INT( GetDeviceCaps(PIXE1, VERTSIZE)) / 2;
	//COLORREF SF_COLO = GetPixel(PIXE1, nScreenWidth, nScreenHeight);		//���ը��C��P�O  ���G�����D
	COLORREF SF_COLO = GetPixel(PIXE1, 100, 100);

	//mouse_event(MOUSEEVENTF_MOVE, 1, 0, NULL, NULL);
	MOD2 = FALSE;

	int iRed = ( GetRValue(SF_COLO));
	int iGreen =( GetGValue(SF_COLO));
	int iBlue =( GetBValue(SF_COLO));

	snprintf(tmp, sizeof(SF_COLO), "%d", SF_COLO);
	OutputDebugStringA(tmp);
	snprintf(tmp, sizeof(iRed), "%d", iRed);
	OutputDebugStringA(tmp);
	snprintf(tmp, sizeof(iGreen), "%d", iGreen);
	OutputDebugStringA(tmp);
	snprintf(tmp, sizeof(iBlue), "%d", iBlue);
	OutputDebugStringA(tmp);

	ReleaseDC(hwnd, PIXE1);
	//Release(PIXE1);
	}

	*/
}


/*
MSG msg;
while (1)
{
GetMessageW(&msg, NULL, 0, 0);
TranslateMessage(&msg);
DispatchMessage(&msg);
};

KillTimer(NULL, 1);

*/



#pragma once

HWND hwndCalc;// = FindWindow(NULL, L"OOXX1");
HWND hwndCalc2;// = FindWindowEx(hwndCalc, 0, NULL, L"TB1");

void MyTextOut(wchar_t* AA)	//¤å¦r¿é¥X
{
	if ((hwndCalc = FindWindow(NULL, L"OOXX1")) != 0)
	{
		hwndCalc = FindWindow(NULL, L"OOXX1");
		hwndCalc2 = FindWindowEx(hwndCalc, 0, NULL, L"TB1");
		SendMessage(hwndCalc2, WM_SETTEXT, 0, (LPARAM)(AA));
	}
}
wchar_t* IntToWchar_t(int val1)
{
	wchar_t str[255];
	wsprintfW(str, L"%d", val1); 
	return str;
}
wchar_t* FloatToWchar_t(float val1)
{
	wchar_t str[255];
	wsprintfW(str, L"%f", val1); 
	return str;
}
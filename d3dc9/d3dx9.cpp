// game.cpp : 定義 DLL 應用程式的匯出函式。
//

#include "stdafx.h"
#include "game.h"
#include "d3d9.h"
#include "d3dx9math.h"
#include "stdio.h"
#include<stdlib.h> 
#include<wchar.h>
#include<windows.h>
#include <iostream> 
#include <string> 
#include <d3d9types.h>
#include "string.h"
#include "My_Text_OUT.h"
#include "My_Hook.h"
#include "My_D3dHook.h"
#include "M_G_Hook.h"


HWND hwnd;

const wchar_t *game_name1 = NULL;//L"SpecialForce";
const wchar_t *game_name2 = L"Counter-Strike";//NULL;//L"D3D"; //L"Counter-Strike";// 
/*
//穿越火?
//SpecialForce sf
//LaunchUnrealUWindowsClient SF2
//Counter-Strike Online	//Alliance of Valiant Arms	//新瑪奇 mabinogi	//百變兵團	//穿越火?
*/

void check()
{

		//MyTextOut(L"_文1字2測3試_");
		
		hwnd = ::FindWindowW(game_name1, game_name2);
		DWORD pid;
		DWORD PID2 = GetWindowThreadProcessId(hwnd ,&pid);

		if (GetCurrentProcessId() == pid)
		{
			
			get_all_address();
			MyTextOut(L"注入成功");
			MessageBox(hwnd, L"祥製做 \n 透視外掛測試", L"注入成功", 0);
			g_hHOOK = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)HookKeyboardMsg, GetModuleHandle(NULL), PID2);		//鍵盤鉤子	
		/*
			//mouse_HOOK = SetWindowsHookEx(WH_MOUSE, (HOOKPROC)LowLevelMouseProc, NULL, PID2);	//滑鼠鉤子
		*/
			HookDrawIndexedPrimitive();		//繪圖函數
			HookCreateQuery();				//剔除函數
			Hook_GetTickCount();			//時間函數	(sf檢測 且沒用)
			Hook_QueryPerformanceCounter();	//時間函數	(sf檢測 且沒用)
			Hook_timeGetTime();				//時間函數
		}
		else
		{
			UnHook();
		}
}

 GAME_API void SetHook()
 {
	 m_hook = SetWindowsHookEx(WH_CBT, CBTProc, GetModuleHandle(L"x91.dll"), 0);
	 HHOOK d = m_hook;
 }
 GAME_API void UnHook()
 {
	 if (g_hHOOK || m_hook || mouse_HOOK)
	 {

		 NO_HOOK_SPEED();
		 NO_HOOK_D3d();

		 UnhookWindowsHookEx(g_hHOOK);
		 UnhookWindowsHookEx(m_hook);
		 UnhookWindowsHookEx(mouse_HOOK);
		 


		 MyTextOut(L"脫離成功");
		 //und3dhook();

	 }
 }

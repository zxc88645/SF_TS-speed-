#pragma once
#include "My_AobScan.h"
#include "My_D3dHook.h"
#include"M_G_Hook.h"

DWORD dwVTable[2] = { 0 };

//HHOOK GetTickCount_HOOK = NULL;		//GetTickCount鉤子


//float Speed = 0; //加速倍數  0是原速  放在MG HOOK

//-----------------------timeGetTime-------------
DWORD timeGetTime_office = 0; //0x1B300;可動態
BOOL timeGetTime_EN = 0;
BYTE  NO_timeGetTime[5];					//還原修改用
DWORD original_timeGetTime_1 = 0;			//上次返回时间 (修改過啊
DWORD original_timeGetTime_2;				//上次正常时间 (阿不就沒修改過  

//-----------------------GetTickCount---------------
//DWORD GetTickCount_address;
DWORD GetTickCount_office = 0;  // 0x25EB0;可動態
BOOL GetTickCount_EN = 0;
BYTE  NO_GetTickCount[5];					//還原修改用
DWORD original_GetTickCount_1 = 0;			//上次返回时间 (修改過啊
DWORD original_GetTickCount_2;				//上次正常时间 (阿不就沒修改過  
											//還有一個目前取得正常時間 在函數內 看不到啊
//----------------------QueryPerformanceCounter---------

DWORD QueryPerformanceCounter_office = 0; // 0x138A0; 可動態
BOOL QueryPerformanceCounte_EN = 0;
DWORD RtlQueryPerformanceCounter_Address;	// JMP ntd中的QPFC 構建成偽API時用到
BYTE NO_QueryPerformanceCounter[5];	//結束進程時返回用
LARGE_INTEGER orginal_lpPerformanceCount;	//上次返回时间 (修改過啊
LARGE_INTEGER orginal_lpPerformanceCount_2;	//上次正常时间 (阿不就沒修改過  
											//還有一個目前取得正常時間 在函數內 看不到啊





ULONG_PTR Get_GetTickCount_Address()
{
	HANDLE handle = GetModuleHandle(L"KERNEL32.dll");
	if (handle == INVALID_HANDLE_VALUE)	return NULL;

	return (ULONG_PTR)handle + GetTickCount_office + 7;

}


ULONG_PTR Get_QueryPerformanceCounter_Address()
{

	HANDLE handle = GetModuleHandle(L"KERNEL32.dll");
	if (handle == INVALID_HANDLE_VALUE)	return NULL;
	
	RtlQueryPerformanceCounter_Address = ((DWORD)handle + QueryPerformanceCounter_office + 8);
	DWORD *temp = (DWORD*)RtlQueryPerformanceCounter_Address;
	RtlQueryPerformanceCounter_Address = *temp;
	temp = (DWORD*)RtlQueryPerformanceCounter_Address;
	RtlQueryPerformanceCounter_Address = *temp;

	return (ULONG_PTR)handle + QueryPerformanceCounter_office;
}


VOID NO_HOOK_SPEED()
{
	HANDLE handle = GetModuleHandle(L"KERNEL32.dll");

	if (QueryPerformanceCounte_EN == TRUE) 
	{	
		DWORD QueryPerformanceCounter_address = (ULONG_PTR)GetProcAddress((HMODULE)handle, "QueryPerformanceCounter");
			if (VirtualProtect((LPVOID)QueryPerformanceCounter_address, 5, PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				_memccpy((void*)(DWORD)QueryPerformanceCounter_address, NO_QueryPerformanceCounter, 5, 5);
				VirtualProtect((LPVOID)QueryPerformanceCounter_address, 5, oldProtect, &oldProtect);
			}
	}


	if (GetTickCount_EN == TRUE)
	{
		DWORD GetTickCount_address = (ULONG_PTR)GetProcAddress((HMODULE)handle, "GetTickCount") + 8;
		if (VirtualProtect((LPVOID)GetTickCount_address, 5, PAGE_EXECUTE_READWRITE, &oldProtect))
		{
			_memccpy((void*)(DWORD)GetTickCount_address, NO_GetTickCount, 5, 5);
			//UnhookWindowsHookEx(GetTickCount_HOOK);
			VirtualProtect((LPVOID)GetTickCount_address, 5, oldProtect, &oldProtect);
		}
	}
	if (timeGetTime_EN == TRUE)
	{
		DWORD timeGetTime_address = (ULONG_PTR)GetProcAddress((HMODULE)handle, "timeGetTime") + 0x5a;

		if (VirtualProtect((LPVOID)timeGetTime_address, 5, PAGE_EXECUTE_READWRITE, &oldProtect))
		{
			_memccpy((void*)(DWORD)timeGetTime_address, NO_timeGetTime, 5, 5);
			VirtualProtect((LPVOID)timeGetTime_address, 5, oldProtect, &oldProtect);
		}
	}

}


void get_all_address()
{


	//GetProcAddress
	MyTextOut(L"stat");
	//-----KERNEL32.dll------
	HMODULE handle = GetModuleHandle(L"KERNEL32.dll");
	timeGetTime_office = (DWORD)GetProcAddress(handle, "timeGetTime") - (DWORD)handle;
	GetTickCount_office = (DWORD)GetProcAddress(handle, "GetTickCount") - (DWORD)handle;
	QueryPerformanceCounter_office = (DWORD)GetProcAddress(handle, "QueryPerformanceCounter") - (DWORD)handle;


	//MyTextOut(IntToWchar_t((INT)timeGetTime_office));				//ok
	//MyTextOut(IntToWchar_t((INT)GetTickCount_office));			//ok
	//MyTextOut(IntToWchar_t((INT)QueryPerformanceCounter_office));	//ok

	//MyTextOut(L"TOP ok")c;
	//-----D3D9.dll------

	handle = LoadLibrary(L"d3d9.dll");
	handle = GetModuleHandle(L"d3d9.dll");
	DWORD dwDXDevice = FindPattern((DWORD)(handle), 0x128000, (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
	DWORD* pdwVTable;

	//MyTextOut(L"FindPattern ok");

	memcpy(&pdwVTable, (VOID*)(dwDXDevice + 2), 4);

	MyTextOut(L"memcpy ok");

	DrawIndexedPrimitive_office = (DWORD)pdwVTable[82] - (DWORD)handle;
	CreateQueryAddress_office = pdwVTable[118] - (DWORD)handle;
	memcpy(&moveax1_office, (VOID*)((INT)CreateQueryAddress_office + (3 + (INT)handle)), 4);

	//MyTextOut(IntToWchar_t((INT)DrawIndexedPrimitive_office));	//ok
	//MyTextOut(IntToWchar_t((INT)CreateQueryAddress_office));		//ok
	//MyTextOut(IntToWchar_t((INT)moveax1_office));					//ok

	MyTextOut(L"office_ok");	
}


 DWORD WINAPI HookFunc_GetTickCount()	//GetTickCount
{
	
	DWORD now_GetTickCount;		//当前返回时间 now
	__asm	mov now_GetTickCount, eax	//不管怎樣 先記錄起來目前時間

	if (original_GetTickCount_1 == 0)	//初始化上次正常時間與上次返回時間
	{
		original_GetTickCount_1 = now_GetTickCount;
		original_GetTickCount_2 = now_GetTickCount;
		return  now_GetTickCount;
	}
		
	//Result: = 上次返回时间 + Round((当前返回时间 - 上次正常时间) * Power(2, 倍数));

	original_GetTickCount_1 = original_GetTickCount_1 + round((now_GetTickCount - original_GetTickCount_2) * pow(2, Speed));

	return original_GetTickCount_1;
}



_declspec(naked) BOOL WINAPI My_QueryPerformanceCounter_3(LARGE_INTEGER *lpPerformanceCount)	//構建偽API用以自己呼叫 內容無改動
{
	__asm
	{

		mov edi, edi
		push ebp
			mov ebp, esp
			pop ebp
			jmp RtlQueryPerformanceCounter_Address
	}
}

BOOL WINAPI My_QueryPerformanceCounter_2(LARGE_INTEGER *lpPerformanceCount)	//HOOK後會先跳來這裡  需要構建成原本的樣子 以接受參數
{

	if (orginal_lpPerformanceCount.QuadPart == 0)
	{
		BOOL Q1 = My_QueryPerformanceCounter_3(lpPerformanceCount);
		orginal_lpPerformanceCount = *lpPerformanceCount;			//上次返回時間
		orginal_lpPerformanceCount_2 = *lpPerformanceCount;		//上次正常時間		 
		return Q1;
	}


	BOOL R1 = My_QueryPerformanceCounter_3(lpPerformanceCount);
	LARGE_INTEGER lpc = *lpPerformanceCount;	//Result用的 而且是當前取到的
	//printf("修改前 = %d\n", lpc.QuadPart);
//---------------------Result := 上次返回时间 + Round((当前返回时间 - 上次正常时间) * Power(2,倍数));
	lpc.QuadPart = orginal_lpPerformanceCount.QuadPart + round((lpc.QuadPart - orginal_lpPerformanceCount_2.QuadPart) * pow(2,Speed));		//修改
//---------------------

	orginal_lpPerformanceCount.QuadPart = lpc.QuadPart; //保存成上次返回時間
	orginal_lpPerformanceCount_2 = *lpPerformanceCount;	//保存上次正常時間
	*lpPerformanceCount = lpc;
	//printf("修改過 = %d\n", lpc.QuadPart);
	return R1;
}



DWORD WINAPI timeGetTime()			//timeGetTime
{
	DWORD now_timeGetTime;		//当前返回时间 now
	__asm	mov now_timeGetTime, eax	//不管怎樣 先記錄起來目前時間

	if (original_timeGetTime_1 == 0)	//初始化上次正常時間與上次返回時間
	{
		original_timeGetTime_1 = now_timeGetTime;
		original_timeGetTime_2 = now_timeGetTime;
		return  now_timeGetTime;
	}

	//Result: = 上次返回时间 + Round((当前返回时间 - 上次正常时间) * Power(2, 倍数));

	original_timeGetTime_1 = original_timeGetTime_1 + round((now_timeGetTime - original_timeGetTime_2) * pow(2, Speed));

	return original_timeGetTime_1;
}



bool Hook_QueryPerformanceCounter()		//HOOK QueryPerformanceCounter 執行一次 修改HOOK
{
	ULONG_PTR address = Get_QueryPerformanceCounter_Address();		//這裡不好簡化 之後再用
	
	if (VirtualProtect((LPVOID)address, 5, PAGE_EXECUTE_READWRITE, &oldProtect))
	{
		QueryPerformanceCounte_EN = TRUE;
		//MyTextOut(L"複製ING....");
		_memccpy(NO_QueryPerformanceCounter, (ULONG_PTR*)address, 5, 5);		//先保存原先的
		//MyTextOut(L"複製好了");
		DWORD value = (DWORD)My_QueryPerformanceCounter_2 - address - 5;		//更改
		_asm
		{
			mov eax, address
			mov byte ptr[eax], 0xe9		//0xe9 = jmp
				add eax, 1
				mov ebx, value
				mov dword ptr[eax], ebx
		}
		VirtualProtect((LPVOID)address, 5, oldProtect, &oldProtect);

		//MyTextOut(L"qp還原了");
	}
	return true;
}



bool Hook_GetTickCount()		//GetTickCount
{
	HMODULE handle = GetModuleHandle(L"KERNEL32.dll");
	ULONG_PTR  address = (ULONG_PTR)GetProcAddress((HMODULE)handle, "GetTickCount") + 8;		//在返回時候才hook，所以+8，然後不用紀錄返回點 ， 在程式中直接ret就行了
//	JmpTo_GetTickCount = address + 5;

	if (VirtualProtect((LPVOID)address, 5, PAGE_EXECUTE_READWRITE, &oldProtect))
	{
		GetTickCount_EN = TRUE;
		_memccpy(NO_GetTickCount, (ULONG_PTR*)address, 5, 5);		//先保存原先的
		DWORD value = (DWORD)HookFunc_GetTickCount - address - 5;		//更改
		_asm
		{
			mov eax, address
			mov byte ptr[eax], 0xe9		//0xe9 = jmp
				add eax, 1
				mov ebx, value
				mov dword ptr[eax], ebx
		}
		VirtualProtect((LPVOID)address, 5, oldProtect, &oldProtect);
	}
	return true;
}

BOOL Hook_timeGetTime()
{
	HMODULE handle = GetModuleHandle(L"KERNEL32.dll");
	ULONG_PTR  address = (ULONG_PTR)GetProcAddress((HMODULE)handle, "timeGetTime") +0x5a;

	if (VirtualProtect((LPVOID)address, 5, PAGE_EXECUTE_READWRITE, &oldProtect))
	{

		timeGetTime_EN = TRUE;
		
		_memccpy(NO_timeGetTime, (ULONG_PTR*)address, 5, 5);		//先保存原先的
		//DWORD value = (ULONG_PTR)GetProcAddress((HMODULE)handle, "GetTickCount") - address - 5;	
		DWORD value = (DWORD)timeGetTime - address - 5;		//更改
		_asm
		{
			mov eax, address
			mov byte ptr[eax], 0xe9		//0xe9 = jmp
				add eax, 1
				mov ebx, value
				mov dword ptr[eax], ebx
		}
		VirtualProtect((LPVOID)address, 5, oldProtect, &oldProtect);
	}
	return true;

}






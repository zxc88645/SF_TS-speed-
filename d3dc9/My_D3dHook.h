#pragma once
#include "M_G_Hook.h"


DWORD DrawIndexedPrimitive_office = 0;// 0x678A0;可動態
DWORD moveax1_office = 0;				// 0x87BB6; 可動態
DWORD CreateQueryAddress_office = 0; // 0x67CF0;可動態

BYTE NO_CreateQuery[5];	//保存以還原

DWORD oldProtect = 0;

DWORD jmpto = 0;
DWORD jmpto2 = 0;
DWORD moveax1 = 0;


HRESULT result = S_OK;

__declspec(naked) HRESULT WINAPI Orginal_DrawIndexedPrimitive(LPDIRECT3DDEVICE9 m_pDevice, D3DPRIMITIVETYPE type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	_asm
	{
		mov edi, edi
		push ebp
			mov ebp, esp

			mov eax, jmpto
			jmp eax
	}

}
HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppd3dtex, DWORD colour32)	//創建紋理
{
	if (FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppd3dtex, NULL)))
		return E_FAIL;

	WORD colour16 =
		((WORD)((colour32 >> 28) & 0xF) << 12)
		| (WORD)(((colour32 >> 20) & 0xF) << 8)
		| (WORD)(((colour32 >> 12) & 0xF) << 4)
		| (WORD)(((colour32 >> 4) & 0xF) << 0);

	D3DLOCKED_RECT d3dlr;
	(*ppd3dtex)->LockRect(0, &d3dlr, 0, 0);
	WORD *pDst16 = (WORD*)d3dlr.pBits;
	for (int xy = 0; xy < 8 * 8; xy++)
		*pDst16++ = colour16;
	(*ppd3dtex)->UnlockRect(0);
	return S_OK;
}
HRESULT WINAPI MyDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{

	//if (MOD2 == TRUE)  //安全退出
	//{
	//	und3dhook();
	//	UnHook();
	//	result = Orginal_DrawIndexedPrimitive(pDevice, type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
	//	return result;
	//}


	//DrawFont(600, 50, D3DCOLOR_ARGB(255, 0, 255, 255), "小键盘-> 0 文字提示, 1 准星开关，人物透视");
	DWORD Enable1;		//緩衝
	DWORD Enable2;		//總是返回FALSE
						//	DWORD Enable3;		//線條實心樣式
	DWORD Enable4;		//光線
	DWORD Enable5;		//關閉Z軸計算	
	pDevice->GetRenderState(D3DRS_ZENABLE, &Enable1);
	pDevice->GetRenderState(D3DRS_ZFUNC, &Enable2);
	//pDevice->GetRenderState(D3DRS_FILLMODE, &Enable3);
	pDevice->GetRenderState(D3DRS_LIGHTING, &Enable4);
	pDevice->GetRenderState(D3DRS_ZWRITEENABLE, &Enable5);


	IDirect3DVertexBuffer9* pStreamData = NULL;
	UINT ioffsetInBytes, istride;
	if (pDevice->GetStreamSource(0, &pStreamData, &ioffsetInBytes, &istride) == D3D_OK)
		pStreamData->Release();
	IDirect3DTexture9 *texture1 = NULL;

	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_ARGB(255, 255, 255, 255));  //光源



	if (istride == 64 && MOD1 == TRUE)		//固定模型後，測試頂點1  人物模型  AVA.SF2=32 SF=64
	{

		GenerateTexture(pDevice, &texture1, D3DCOLOR_ARGB(255, 0, 255, 0));


		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);		//開關深度緩衝	Enable1
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			//關閉Z軸計算	Enable5
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);			//總返回false	Enable3
																	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);		//線條OR實心透視	// D3DFILL_POINT） //点填充模式，D3D在多边形的每个顶点绘制一个像素 D3DFILL_WIREFRAME） //线填充模式，D3D在多边形的每个边绘制一条线 D3DFILL_SOLID）   //面模式，D3D默认模式，对多边形的面进行填充
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);				//禁用光線		Enable4
																	//pDevice->SetRenderState(D3DRS_COLORVERTEX, FALSE);			//肯能會高量	
																	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);		//肯能會高量2

		pDevice->SetTexture(0, texture1);			//人物上色


													//SF的頭上色
		if (NumVertices == 119 || NumVertices == 387 || NumVertices == 476 || NumVertices == 577 || NumVertices == 596 || NumVertices == 596 || NumVertices == 616 || NumVertices == 621 || NumVertices == 634 || NumVertices == 640 || NumVertices == 641 || NumVertices == 661 || NumVertices == 667 || NumVertices == 699 || NumVertices == 834 || NumVertices == 834 || NumVertices == 979 || NumVertices == 810 || NumVertices == 800 || NumVertices == 792 || NumVertices == 815 || NumVertices == 895 || NumVertices == 1028 || NumVertices == 1171 || NumVertices == 1190)
		{
			texture1->Release();
			GenerateTexture(pDevice, &texture1, D3DCOLOR_ARGB(255, 255, 0, 0));		//頭上紅色
			pDevice->SetTexture(0, texture1);
		}
		if (NumVertices == MAX1)
		{
			texture1->Release();
			GenerateTexture(pDevice, &texture1, D3DCOLOR_ARGB(255, 255, 0, 0));		//紅色
			pDevice->SetTexture(0, texture1);
		}


		//D3DFILL_WIREFRAME	線條填充
		//D3DFILL_SOLID		實心


	}

/*
sf2測試馬
if ( MOD1 ==TRUE && istride == 32)
{
pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);		//開關深度緩衝	Enable1

D3DXMATRIXA16 matWorld, mat;
D3DXMATRIX matView, matProjection;
D3DVIEWPORT9 viewport;

D3DXVECTOR3 result, screenPoint;
POINT p_mouse;

pDevice->GetViewport(&viewport);
pDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
pDevice->GetTransform(D3DTS_VIEW, &matView);



pDevice->GetTransform(D3DTS_WORLD, &matWorld);

D3DXMatrixIdentity(&matWorld);



MyTextOut(FloatToWchar_t(matProjection._11));
MyTextOut(FloatToWchar_t(matProjection._12));
MyTextOut(FloatToWchar_t(matProjection._13));
MyTextOut(FloatToWchar_t(matProjection._14));

MyTextOut(FloatToWchar_t(matView._21));
MyTextOut(FloatToWchar_t(matView._22));
MyTextOut(FloatToWchar_t(matView._23));
MyTextOut(FloatToWchar_t(matView._24));

MyTextOut(FloatToWchar_t(matWorld._31));
MyTextOut(FloatToWchar_t(matWorld._32));
MyTextOut(FloatToWchar_t(matWorld._33));
MyTextOut(FloatToWchar_t(matWorld._34));

MyTextOut(FloatToWchar_t(matView._41));
MyTextOut(FloatToWchar_t(matView._42));
MyTextOut(FloatToWchar_t(matView._43));
MyTextOut(FloatToWchar_t(matView._44));


//D3DXVec3Unproject(&result, &screenPoint, &viewport, &matProjection, &matView, &matWorld);
}

*/
/*
if( MOD1 == TRUE  )if ( istride == 32 || istride == 12 ) pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
//if (NumVertices >= value2 && NumVertices <= value3)

if (primCount >= value1 && primCount <= value1+2 )
{
//if 	 ( value2 >= NumVertices &&	NumVertices <= value3 )
pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);		//開關深度緩衝	Enable1
pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			//關閉Z軸計算	Enable5
}

*/

	result = Orginal_DrawIndexedPrimitive(pDevice, type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);

	pDevice->SetRenderState(D3DRS_ZENABLE, Enable1);		//還原深度緩衝
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, Enable5);
	pDevice->SetRenderState(D3DRS_ZFUNC, Enable2);			//總返回false
															//pDevice->SetRenderState(D3DRS_FILLMODE, Enable3);		//線條透視
	pDevice->SetRenderState(D3DRS_LIGHTING, Enable4);		//還原光線


															//mouse_auto();		//暫時關閉


	if (texture1)
	{
		texture1->Release();
	}
	return result;
}


/*
if (value1 >= NumVertices && value1 <= NumVertices + 5)
{
pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);		//開關深度緩衝	Enable1
}
if ( value2 >= startIndex && value2 <= startIndex + 5 ) 	{
pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);		//開關深度緩衝
}
if ( value3 >= primCount && value3 <= primCount + 5 )
{
pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);		//開關深度緩衝
}
*/

	


ULONG_PTR Get_DrawIndexedPrimitive_Address()
{
	HANDLE handle = GetModuleHandle(L"d3d9.dll");
	if (handle == INVALID_HANDLE_VALUE)return NULL;

	return (ULONG_PTR)handle + DrawIndexedPrimitive_office;  // 筆電
															 //更改8.1 0x2F700;			
															 //更改10  0x67CD0
															 //memb、文琪更改10  0x678A0											
}



/*
67E9F700 - 67E70000 = 2F700	 原DrawIndexedPrimitive
675EF700  mov         edi, edi
675EF702  push        ebp
675EF703  mov         ebp, esp
*/


bool HookDrawIndexedPrimitive()		//緩衝
{
	ULONG_PTR address = Get_DrawIndexedPrimitive_Address();
	jmpto = address + 5;


	if (VirtualProtect((LPVOID)address, 5, PAGE_EXECUTE_READWRITE, &oldProtect))
	{
		DWORD value = (DWORD)MyDrawIndexedPrimitive - address - 5;		//更改
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

/*
64E31DA0 - 64E10000 = 21DA0		原CreateQuery

64E31DA0 6A 14                push        14h
64E31DA2 B8 1C AA E8 64       mov         eax, 64E8AA1Ch
64E31DA7 E8 15 DA FE FF       call        __EH_prolog3_GS + 2BFh(64E1F7C1h)
64E31DAC 8B 75 08             mov         esi, dword ptr[ebp + 8]
64E31DAF 85 F6                test        esi, esi
*/




BYTE hkquery[7];

ULONG_PTR Get_CreateQuery_Address()
{
	HANDLE handle = GetModuleHandle(L"d3d9.dll");
	if (handle == INVALID_HANDLE_VALUE)return NULL;
	moveax1 = (ULONG_PTR)handle + moveax1_office;	//筆電				//8.1 0x7AA1C		10 0x832A6
	return (ULONG_PTR)handle + CreateQueryAddress_office;		//筆電		//8.1 0x21DA0		10 0x68120
}

__declspec(naked) HRESULT WINAPI oCreateQuery(LPDIRECT3DDEVICE9 pDevice, D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery)
{
	_asm
	{
		//popfd
		//popad

		push     14h
		mov      eax, moveax1// 6845AA1Ch

			mov esi, jmpto2
			jmp esi
			//esi
	}
}
HRESULT WINAPI myCreateQuery(LPDIRECT3DDEVICE9 pDevice, D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery)
{
	if (Type == D3DQUERYTYPE_OCCLUSION)
	{
		//Type = D3DQUERYTYPE_EVENT;
		Type = D3DQUERYTYPE_TIMESTAMP;
	}
	return  oCreateQuery(pDevice, Type, ppQuery);;
}
bool HookCreateQuery()			//剔除函數
{
	ULONG_PTR address2 = Get_CreateQuery_Address();
	jmpto2 = address2 + 7;
	DWORD oldProtect = 0;

	//memcpy(&hkquery, &address2, 7);
	if (VirtualProtect((LPVOID)address2, 5, PAGE_EXECUTE_READWRITE, &oldProtect))
	{
		_memccpy(NO_CreateQuery, (ULONG_PTR*)address2, 5, 5);		//先保存原先的
		DWORD value2 = (DWORD)myCreateQuery - address2 - 5;		//更改
		_asm
		{
			//pushad
			//pushfd
			mov eax, address2
			mov byte ptr[eax], 0xe9		//0xe9 = jmp
				add eax, 1
				mov ebx, value2
				mov dword ptr[eax], ebx

		}

		VirtualProtect((LPVOID)address2, 5, oldProtect, &oldProtect);
	}
	return true;
}


void Un_Hook_DrawIndexedPrimitive()
{

	MyTextOut(L"進入卸載");
	ULONG_PTR address = Get_DrawIndexedPrimitive_Address();

	if (VirtualProtect((LPVOID)address, 5, PAGE_EXECUTE_READWRITE, &oldProtect))
	{

		MyTextOut(L"權限取得成功");
		_asm
		{
			mov eax, address
			mov byte ptr[eax], 0x8B
				add eax, 1
				mov byte ptr[eax], 0xFF
				add eax, 1
				mov byte ptr[eax], 0x55
				add eax, 1
				mov byte ptr[eax], 0x8B
				add eax, 1
				mov byte ptr[eax], 0xEC
				add eax, 1

				//mov edi, edi
				//push ebp
				//mov ebp, esp



				/*
				還原
				700978A0 8B FF                mov         edi,edi
				700978A2 55                   push        ebp
				700978A3 8B EC                mov         ebp,esp
				*/

		}

		MyTextOut(L"修改完畢");
		VirtualProtect((LPVOID)address, 5, oldProtect, &oldProtect);
	}

}



void Un_Hook_CreateQuery()
{

	//MyTextOut(L"進入卸載");
	ULONG_PTR address = Get_CreateQuery_Address();

	if (VirtualProtect((LPVOID)address, 5, PAGE_EXECUTE_READWRITE, &oldProtect))
	{
		_memccpy((void*)(DWORD)address, NO_CreateQuery, 5, 5);
		VirtualProtect((LPVOID)address, 5, oldProtect, &oldProtect);		
	}

	MyTextOut(L"修改完畢");
	VirtualProtect((LPVOID)address, 5, oldProtect, &oldProtect);
	

}




void  NO_HOOK_D3d()
{

	Un_Hook_DrawIndexedPrimitive();
	Un_Hook_CreateQuery();

}
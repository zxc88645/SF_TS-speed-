
// d3d透視正式.h : PROJECT_NAME 應用程式的主要標頭檔
//

#pragma once

#ifndef __AFXWIN_H__
	#error "對 PCH 包含此檔案前先包含 'stdafx.h'"
#endif

#include "resource.h"		// 主要符號


// Cd3d透視正式App: 
// 請參閱實作此類別的 d3d透視正式.cpp
//

class Cd3d透視正式App : public CWinApp
{
public:
	Cd3d透視正式App();

// 覆寫
public:
	virtual BOOL InitInstance();

// 程式碼實作

	DECLARE_MESSAGE_MAP()
};

extern Cd3d透視正式App theApp;
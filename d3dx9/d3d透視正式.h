
// d3d�z������.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// Cd3d�z������App: 
// �аѾ\��@�����O�� d3d�z������.cpp
//

class Cd3d�z������App : public CWinApp
{
public:
	Cd3d�z������App();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern Cd3d�z������App theApp;
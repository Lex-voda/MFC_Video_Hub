
// MFC_TEST.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once
#include "stdafx.h"
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_TESTApp: 
// �йش����ʵ�֣������ MFC_TEST.cpp
//

class CVideo_Hub_App : public CWinApp
{
public:
	CVideo_Hub_App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CVideo_Hub_App theApp;
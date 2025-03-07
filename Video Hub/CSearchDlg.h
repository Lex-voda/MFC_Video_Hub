#pragma once
#include "stdafx.h"
#include"stdlate.h"		//数据库

// CSearchDlg 对话框

class CSearchDlg : public CDialogEx
{

public:
	CSearchDlg(CWnd* pParent = nullptr);   // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCH_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	//对话框背景
	CBrush m_Brush;//背景画刷
	CRect temprect;		//窗口位置
	//输入框

	CEdit m_User_Search;	//输入框控件

	CFont font;		//文字字体

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//鼠标光标设置
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	void DrawSearchMenu(CDC* pDC);		//绘制用户界面
	void DrawButtle(CDC* pDC);//自绘按钮

	afx_msg void OnClose();

	CRect m_Line;		//分界线
	CRect m_crPort;		//头像
	CRect m_crUserName;

	CRect m_rtResultHead;
	CRect m_rtPortBMP;
	CRect m_rtVideoBMP;
	int m_offset_value;		//偏移量

	BOOL m_bIsClose;

	BOOL m_bCanShow = FALSE;		//是否高亮按钮标志
	BOOL m_bLauShow = FALSE;
	BOOL m_bMyVidShow = FALSE;

	CString m_search_str;

	//后端数据
	Interface m_OnlineUserList;	//用户链表，可读可写
	string m_serach;
};

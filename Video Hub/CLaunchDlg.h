#pragma once
#include "stdafx.h"
#include"stdlate.h"		//数据库

// CLaunchDlg 对话框

class CLaunchDlg : public CDialogEx
{

public:
	CLaunchDlg(CWnd* pParent = nullptr);   // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LAUNCH_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
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

	CFont font;		//文字字体

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//鼠标光标设置
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	void DrawUpdateMenu(CDC* pDC);		//绘制发布界面
	void DrawButtle(CDC* pDC);//自绘按钮

	afx_msg void OnLButtonDown(UINT nHitTest, CPoint point);//响应登录、取消消息
	afx_msg void OnMouseMove(UINT nHitTest, CPoint point);//响应鼠标瞄准
	afx_msg void OnClose();

	CRect m_crLaunch_Flag;
	CRect m_crLaunch_Table;

	CRect m_crVideo_Name;
	CRect m_crVideo_Size;
	CRect m_crVideo_LaunchTime;

	CRect m_crLaunchButton;
	CRect m_crCancelButon;

	CString m_Edit_VideoName;
	CString m_Edit_VideoSize;
	CString m_Edit_VideoTime;

	BOOL m_bIsClose;

	BOOL m_bCanShow = FALSE;		//是否高亮按钮标志
	BOOL m_bLauShow = FALSE;

	//后端数据
	Interface m_OnlineUserList;	//用户链表
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

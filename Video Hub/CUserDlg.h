//CUserDlg.h：头文件
#pragma once
#include "stdafx.h"
#include "CVideoDlg.h"
#include "CLaunchDlg.h"
#include "CSearchDlg.h"
#include"stdlate.h"		//数据库

// CUserDlg 对话框

class CUserDlg : public CDialogEx
{
	// 构造
public:
	CUserDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


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

	CEdit m_User_Search;	//输入框控件

	CFont font;		//文字字体

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//鼠标光标设置
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void DrawUserMenu(CDC* pDC);		//绘制用户界面
	void DrawButtle(CDC* pDC);//自绘按钮

	afx_msg void OnLButtonDown(UINT nHitTest, CPoint point);//响应登录、取消消息
	afx_msg void OnMouseMove(UINT nHitTest, CPoint point);//响应鼠标瞄准
	afx_msg void OnClose();

	CRect m_Line;		//分界线
	CRect m_crPort;		//头像
	CRect m_crUserName;

	CRect m_crMyVideo;
	CRect m_crLaunch;
	CRect m_crCan;
	CRect m_crSearch;
	CRect m_crbmpsearch;
	BOOL m_bIsClose;
  
	BOOL m_bCanShow = FALSE;		//是否高亮按钮标志
	BOOL m_bLauShow = FALSE;
	BOOL m_bMyVidShow = FALSE;

	CString m_search_str;
	//子窗口
	CVideoDlg* m_Video;
	CLaunchDlg* m_Launch;
	CSearchDlg* m_Search;
	//后端数据
	Interface m_OnlineUserList;	//用户链表，可读可写
	string m_User_Gender;
};

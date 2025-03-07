//CLoginDlg.h ：头文件
#pragma once 
#include "stdafx.h"
#include"stdlate.h"		//数据库
// CLoginDlg 对话框
class CLoginDlg : public CDialogEx
{
	// 构造
public:
	CLoginDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
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

	CFont font;		//文字字体
	CEdit m_Login_UserName;	//输入框控件
	CEdit m_Login_UserKey;	

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//鼠标光标设置
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//输入框响应回车
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void DrawMenuLogo();		//绘制菜单Logo
	void DrawButtle(CDC* pDC);//自绘按钮

	CRect m_rtEditUserName;		//登录输入框位置
	CRect m_rtEditUserKey;	//密码输入框位置

	CRect m_rtButtLog;		//登录按钮位置
	CRect m_rtButtCan;		//取消按钮位置

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);//响应鼠标瞄准
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);//响应登录、取消消息
	afx_msg void OnClose();

	BOOL m_bIsClose;

	BOOL m_bLogShow = FALSE;		//是否高亮按钮标志
	BOOL m_bCanShow = FALSE;

	//输入框值
	CString m_Login_Name;
	CString m_Login_Key;
};
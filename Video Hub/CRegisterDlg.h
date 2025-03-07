#pragma once
#include "stdafx.h"
#include"stdlate.h"		//数据库
// CRegisterDlg 对话框

class CRegisterDlg : public CDialogEx
{

public:
	CRegisterDlg(CWnd* pParent = nullptr);   // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTER_DIALOG };
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
	COLORREF m_BlackColor;
	COLORREF m_TextColor;

	CFont font;		//文字字体

	CEdit m_Register_UserName;	//控件
	CEdit m_Register_UserKey;
	CButton m_Male;
	CButton m_Female;
	

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//鼠标光标设置
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedRegisterMale();

	void DrawMenuLogo();		//绘制菜单Logo
	void DrawButtle(CDC* pDC);//自绘按钮

	CRect m_rtButtExit;    // 关闭按钮位置
	CRect m_rtButtMax;    // 最大化按钮位置
	CRect m_rtButtMin;    // 最小化按钮位置

	CRect m_rtEditUserName;		//账号输入框位置
	CRect m_rtEditUserKey;	//密码输入框位置
	CRect m_rtEditUserMale;	//性别选择位置
	CRect m_rtEditUserFemale;
	CRect m_rtEditUserDonno;
	

	CRect m_rtButtReg;		//注册按钮位置
	CRect m_rtButtCan;		//取消按钮位置

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);//响应按钮消息
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);//响应鼠标瞄准
	afx_msg void OnClose();

	BOOL m_bIsClose;
	BOOL m_bCloseShow = FALSE;//是否高亮按钮标志
	BOOL m_bMiniShow = FALSE;
	BOOL m_bMaxShow = FALSE;

	BOOL m_bRegShow = FALSE;
	BOOL m_bCanShow = FALSE;

	CString m_Register_Name;	//用户值
	CString m_Register_Key;	
	//用户数据库接口

	int m_Gende_Value;
};

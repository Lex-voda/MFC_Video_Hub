
// Video_Hub_Dlg.h : 头文件
#pragma once
#include "stdafx.h"
#include <afxinet.h>
#include "CLoginDlg.h"
#include "CRegisterDlg.h"
#include"CUserDlg.h"
#include"stdlate.h"		//数据库



// CMFC_TESTDlg 对话框
class CVideoHubDlg : public CDialogEx
{
// 构造
public:
	CVideoHubDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDEO_HUB_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon; 
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OpenNewDlg(WPARAM wParam, LPARAM lParam);		//接受消息打开用户窗口
	DECLARE_MESSAGE_MAP()

public:
	//对话框背景
	CBrush m_Brush;//背景画刷
	CRect temprect;		//窗口位置
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//鼠标光标设置
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	//自绘标题栏
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	void DrawMenuLogo(CDC* pDC);		//绘制菜单Logo
	void DrawTitleBar(CDC *pDC);//自绘标题栏
	void DrawButtle(CDC* pDC);//自绘按钮
	void DrawCloseButton(CDC *pDC);//根据是否鼠标落在按钮区域显示是否高亮

	CRect m_MeueLogo;    // 菜单logo位置

	CRect m_rtButtExit;    // 关闭按钮位置
	CRect m_rtButtMax;    // 最大化按钮位置
	CRect m_rtButtMin;    // 最小化按钮位置

	CRect m_rtButtLog;    // 登录按钮位置
	CRect m_rtButtRis;    // 注册按钮位置
	CRect m_rtButtVis;    // 访客按钮位置
	CRect m_rtButtExi;    // 退出按钮位置

	CRect m_rtIcon;        // 图标位置
	afx_msg LRESULT OnNcHitTest(CPoint point);//为了移动对话框
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);//响应最大化、最小化、关闭消息
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);//响应鼠标瞄准

	afx_msg void OnNcButtonUser(UINT nHitTest, CPoint point);//响应用户区按钮

	BOOL m_bCloseShow = FALSE;//是否高亮按钮标志
	BOOL m_bMiniShow = FALSE;
	BOOL m_bMaxShow = FALSE;

	BOOL m_bLogShow = FALSE;
	BOOL m_bRisShow = FALSE;
	BOOL m_bVisShow = FALSE;
	BOOL m_bExiShow = FALSE;

	//子窗口
	CLoginDlg* Log;
	CRegisterDlg* Reg;
	CUserDlg* User;
	//来自子窗口的数据
	CString	m_Log_User;	//主用户
	//后端数据
	Interface m_VH_OnlineUserList;	//在线用户对象
};

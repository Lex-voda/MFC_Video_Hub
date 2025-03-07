//CVideoDlg.h：头文件
#pragma once
#include "stdafx.h"
#include"stdlate.h"		//后端数据库
// CVideoDlg 对话框

class CVideoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVideoDlg)

public:
	CVideoDlg(CWnd* pParent = nullptr);   // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDEO_DIALOG };
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClose();

	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CRect m_rtVideoHead;		//第一个视频的位置
	CRect m_rtVideoInf;		//视频信息位置
	int m_offset_value;		//视频块偏移量
	CRect m_rtVideoBMP;

	CRect m_crVideoDelete1;	//删除视频按钮位置
	CRect m_crVideoDelete2;	
	CRect m_crEditDelete;
	CRect m_crTextDelete;

	CPoint m_pt_Up[4];		//向上翻页按钮点位
	CPoint m_pt_Down[4];	//向下翻页按钮点位
	CRgn m_rgn_Up;		//向上翻页按钮区域
	CRgn m_rgn_Down;	//向下翻页按钮区域

	void DrawVideoMenu(CDC* pDC);	//绘制视频界面
	void DrawButtle(CDC* pDC);	//绘制按钮

	BOOL m_bIsClose;
	
	BOOL m_bUpShow = FALSE;		//是否高亮按钮标志
	BOOL m_bDownShow = FALSE;
	BOOL m_bDeleteShow = FALSE;
	//后端数据
	Interface m_OnlineUserList;	//用户链表，可读可写
	List<Video>* m_OnlineUser_Video;	//在线用户的视频
	Iterator<Video> m_Video_Node;		//视频链表断点
	int m_step = 3;		//视频输出步长最大值
	
	CString m_Delete_videoname;
};

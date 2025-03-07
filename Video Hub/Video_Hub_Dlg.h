
// Video_Hub_Dlg.h : ͷ�ļ�
#pragma once
#include "stdafx.h"
#include <afxinet.h>
#include "CLoginDlg.h"
#include "CRegisterDlg.h"
#include"CUserDlg.h"
#include"stdlate.h"		//���ݿ�



// CMFC_TESTDlg �Ի���
class CVideoHubDlg : public CDialogEx
{
// ����
public:
	CVideoHubDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDEO_HUB_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon; 
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OpenNewDlg(WPARAM wParam, LPARAM lParam);		//������Ϣ���û�����
	DECLARE_MESSAGE_MAP()

public:
	//�Ի��򱳾�
	CBrush m_Brush;//������ˢ
	CRect temprect;		//����λ��
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//���������
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	//�Ի������
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	void DrawMenuLogo(CDC* pDC);		//���Ʋ˵�Logo
	void DrawTitleBar(CDC *pDC);//�Ի������
	void DrawButtle(CDC* pDC);//�Ի水ť
	void DrawCloseButton(CDC *pDC);//�����Ƿ�������ڰ�ť������ʾ�Ƿ����

	CRect m_MeueLogo;    // �˵�logoλ��

	CRect m_rtButtExit;    // �رհ�ťλ��
	CRect m_rtButtMax;    // ��󻯰�ťλ��
	CRect m_rtButtMin;    // ��С����ťλ��

	CRect m_rtButtLog;    // ��¼��ťλ��
	CRect m_rtButtRis;    // ע�ᰴťλ��
	CRect m_rtButtVis;    // �ÿͰ�ťλ��
	CRect m_rtButtExi;    // �˳���ťλ��

	CRect m_rtIcon;        // ͼ��λ��
	afx_msg LRESULT OnNcHitTest(CPoint point);//Ϊ���ƶ��Ի���
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);//��Ӧ��󻯡���С�����ر���Ϣ
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);//��Ӧ�����׼

	afx_msg void OnNcButtonUser(UINT nHitTest, CPoint point);//��Ӧ�û�����ť

	BOOL m_bCloseShow = FALSE;//�Ƿ������ť��־
	BOOL m_bMiniShow = FALSE;
	BOOL m_bMaxShow = FALSE;

	BOOL m_bLogShow = FALSE;
	BOOL m_bRisShow = FALSE;
	BOOL m_bVisShow = FALSE;
	BOOL m_bExiShow = FALSE;

	//�Ӵ���
	CLoginDlg* Log;
	CRegisterDlg* Reg;
	CUserDlg* User;
	//�����Ӵ��ڵ�����
	CString	m_Log_User;	//���û�
	//�������
	Interface m_VH_OnlineUserList;	//�����û�����
};

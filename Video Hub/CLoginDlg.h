//CLoginDlg.h ��ͷ�ļ�
#pragma once 
#include "stdafx.h"
#include"stdlate.h"		//���ݿ�
// CLoginDlg �Ի���
class CLoginDlg : public CDialogEx
{
	// ����
public:
	CLoginDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	//�Ի��򱳾�
	CBrush m_Brush;//������ˢ
	CRect temprect;		//����λ��
	//�����

	CFont font;		//��������
	CEdit m_Login_UserName;	//�����ؼ�
	CEdit m_Login_UserKey;	

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//���������
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//�������Ӧ�س�
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void DrawMenuLogo();		//���Ʋ˵�Logo
	void DrawButtle(CDC* pDC);//�Ի水ť

	CRect m_rtEditUserName;		//��¼�����λ��
	CRect m_rtEditUserKey;	//���������λ��

	CRect m_rtButtLog;		//��¼��ťλ��
	CRect m_rtButtCan;		//ȡ����ťλ��

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);//��Ӧ�����׼
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);//��Ӧ��¼��ȡ����Ϣ
	afx_msg void OnClose();

	BOOL m_bIsClose;

	BOOL m_bLogShow = FALSE;		//�Ƿ������ť��־
	BOOL m_bCanShow = FALSE;

	//�����ֵ
	CString m_Login_Name;
	CString m_Login_Key;
};
//LoginDlg.cpp ��ʵ���ļ�
#include "stdafx.h"
#include "Video_Hub_App.h"	
#include "CLoginDlg.h"
#include "Video_Hub_Dlg.h"
//LoginDlg�Ի���

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
	, m_Login_Name(_T(""))
	, m_Login_Key(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LOGIN_USERNAME, m_Login_Name);
	DDX_Text(pDX, IDC_LOGIN_USERKEY, m_Login_Key);
}

BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()

	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_CLOSE()
	
END_MESSAGE_MAP()

BOOL CLoginDlg_LoadImageResource(CImage* pImage, UINT nResID, LPCTSTR lpTyp)
{
	if (pImage == NULL)
		return false;
	pImage->Destroy();
	// ������Դ
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
	if (hRsrc == NULL)
		return false;
	// ������Դ
	HGLOBAL hImgData = ::LoadResource(AfxGetResourceHandle(), hRsrc);
	if (hImgData == NULL)
	{
		::FreeResource(hImgData);
		return false;
	}
	// �����ڴ��е�ָ����Դ
	LPVOID lpVoid = ::LockResource(hImgData);
	LPSTREAM pStream = NULL;
	DWORD dwSize = ::SizeofResource(AfxGetResourceHandle(), hRsrc);
	HGLOBAL hNew = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);
	// ����ڴ��е�ָ����Դ
	::GlobalUnlock(hNew);
	// ��ָ���ڴ洴��������
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if (ht != S_OK)
	{
		GlobalFree(hNew);
	}
	else
	{
		// ����ͼƬ
		pImage->Load(pStream);
		GlobalFree(hNew);
	}
	// �ͷ���Դ
	::FreeResource(hImgData);
	return true;
}

BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//��ʼ�����ڳߴ�
	int width = GetSystemMetrics(SM_CXFULLSCREEN) * 4 / 5;
	int heigh = GetSystemMetrics(SM_CYFULLSCREEN) * 4 / 5;
	GetWindowRect(&temprect);
	ScreenToClient(&temprect);
	temprect.BottomRight().x = temprect.TopLeft().x + width;
	temprect.BottomRight().y = temprect.TopLeft().y + heigh;
	temprect.TopLeft().y += 50;
	CWnd::SetWindowPos(NULL, temprect.TopLeft().x, temprect.TopLeft().y, temprect.Width(), temprect.Height(), SWP_NOZORDER );
	
	font.CreateFont(50, 22, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("AST"));
	
	m_Brush.CreateSolidBrush(RGB(0, 0, 0));

	m_bIsClose = FALSE;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLoginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*************************************************************** �� �� �� �� �� *************************************************************/

HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (pWnd->GetDlgCtrlID() == IDC_LOGIN_USERNAME) {
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(194, 89, 136));  
		pDC->SelectObject(&font); //ѡ���µ����� 
	}
	if (pWnd->GetDlgCtrlID() == IDC_LOGIN_USERKEY) {
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(194, 89, 136));
		pDC->SelectObject(&font); //ѡ���µ����� 
	}
	return m_Brush;
}

/*************************************************************** �� �� �� �� �� �� *************************************************************/

BOOL CLoginDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	HCURSOR hcur = ::LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	::SetCursor(hcur);
	return TRUE;
	//return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}

//ϵͳ��Ϣ��Ӧ�����ػ溯��
LRESULT CLoginDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT lrst = CDialog::DefWindowProc(message, wParam, lParam);
	if (!::IsWindow(m_hWnd))
		return lrst;

	if (
		message == WM_MOVE
		|| message == WM_PAINT
		|| message == WM_NCACTIVATE
		|| message == WM_NOTIFY
		)
	{
		CDC* pWinDC = GetWindowDC();
		if (pWinDC) {
			DrawMenuLogo();
			DrawButtle(pWinDC);
		}
		ReleaseDC(pWinDC);
	}
	return lrst;
}

void CLoginDlg::OnClose()
{
	m_bIsClose = TRUE;
	CDialogEx::OnClose();
}

//������ƶ��������ж��Ƿ�ѡ�а�ť
void CLoginDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_rtButtLog.PtInRect(point))
	{
		m_bLogShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bLogShow)
	{
		m_bLogShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	if (m_rtButtCan.PtInRect(point))
	{
		m_bCanShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bCanShow)
	{
		m_bCanShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

//��Ӧ��ť��Ϣ
void CLoginDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_rtButtLog.PtInRect(point)) {
		UpdateData(true);
		CVideoHubDlg* pParent = (CVideoHubDlg*)GetParent();	 //�����ڵ�ָ��
		//��¼����
		string username = m_Login_Name.GetBuffer(0);
		string userkey = m_Login_Key.GetBuffer(0);
		Interface New_User;
		New_User.initialize();
		if (New_User.signIn(username, userkey)) {		//��¼�ɹ����˺�����Ϸ�
			pParent->m_VH_OnlineUserList = New_User;
			pParent->m_Log_User = m_Login_Name;
			HWND hTemp = ::GetParent(this->GetSafeHwnd());	//��ø����ڵľ��
			::SendMessage(hTemp, WM_OPENNEWDLG, 0, 0);
			SendMessage(WM_CLOSE);
		}
		else {
			MessageBox("��¼ʧ�ܣ������˺�����");
		}
	}
	else if (m_rtButtCan.PtInRect(point))
		SendMessage(WM_CLOSE);
	CDialogEx::OnLButtonDown(nFlags, point);
}
//����LOGO
void CLoginDlg::DrawMenuLogo() {
	CRect m_MeueLogo;    // �˵�logoλ��
	CWnd* pWnd = GetDlgItem(IDC_LOGIN_COVER);
	if (pWnd) {
		//����LOGOλ��
		GetWindowRect(&m_MeueLogo);		//Logoλ��
		ScreenToClient(&m_MeueLogo);
		m_MeueLogo.TopLeft().x += m_MeueLogo.Width() / 2 - 657;
		m_MeueLogo.TopLeft().y += m_MeueLogo.Height() * 0.25;
		m_MeueLogo.BottomRight().x = m_MeueLogo.TopLeft().x + 1314;
		m_MeueLogo.BottomRight().y = m_MeueLogo.TopLeft().y + 299;
		m_MeueLogo.TopLeft().y -= 50;
		m_MeueLogo.BottomRight().y -= 50;
		pWnd->MoveWindow(m_MeueLogo);
	}
}
//�Ի水ť
void CLoginDlg::DrawButtle(CDC * pDC) {
	if (m_hWnd) {
		//���ư�ť
		CBrush HighLine(RGB(134, 52, 53));		//������ˢ
		CBrush BrushLine(RGB(194, 89, 136));	//�����ˢ
		//���Ƶ�¼�����
		GetWindowRect(&m_rtEditUserName);
		ScreenToClient(&m_rtEditUserName);
		m_rtEditUserName.TopLeft().x += m_rtEditUserName.Width() / 3;
		m_rtEditUserName.TopLeft().y += m_rtEditUserName.Height() * 0.6;
		m_rtEditUserName.BottomRight().x -= m_rtEditUserName.TopLeft().x;
		m_rtEditUserName.BottomRight().y = m_rtEditUserName.TopLeft().y + 60;
		
		GetWindowRect(&m_rtEditUserKey);
		ScreenToClient(&m_rtEditUserKey);

		m_rtEditUserKey.TopLeft().x = m_rtEditUserName.TopLeft().x;
		m_rtEditUserKey.TopLeft().y = m_rtEditUserName.TopLeft().y + 120;
		m_rtEditUserKey.BottomRight().x = m_rtEditUserName.BottomRight().x;
		m_rtEditUserKey.BottomRight().y = m_rtEditUserKey.TopLeft().y + 60;
		
		//��¼�����
		CWnd* pWnd;
		pWnd = GetDlgItem(IDC_LOGIN_USERNAME);    //��ȡ�ؼ�ָ��
		if (pWnd) {
			pWnd->SetWindowPos(NULL, m_rtEditUserName.TopLeft().x + 80, m_rtEditUserName.TopLeft().y, m_rtEditUserName.Width() - 80, m_rtEditUserName.Height(), SWP_NOZORDER);
			//����
			pWnd->SetFont(&font);
		}
		pWnd = GetDlgItem(IDC_LOGIN_USERKEY);    //��ȡ�ؼ�ָ��
		if (pWnd) {
			pWnd->SetWindowPos(NULL, m_rtEditUserKey.TopLeft().x + 80, m_rtEditUserKey.TopLeft().y, m_rtEditUserKey.Width() - 80, m_rtEditUserKey.Height(), SWP_NOZORDER);
			//����
			pWnd->SetFont(&font);
		}

		//���Ƶ�¼��ť
		GetWindowRect(&m_rtButtLog);
		ScreenToClient(&m_rtButtLog);
		m_rtButtLog.TopLeft().x = m_rtEditUserName.TopLeft().x+50;
		m_rtButtLog.TopLeft().y = m_rtEditUserName.TopLeft().y + 4 * m_rtEditUserName.Height();
		m_rtButtLog.BottomRight().x = m_rtButtLog.TopLeft().x + 200;
		m_rtButtLog.BottomRight().y = m_rtButtLog.TopLeft().y + 50;
		if (m_bLogShow)
			pDC->SelectObject(&HighLine);
		else
			pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_rtButtLog.TopLeft().x, m_rtButtLog.TopLeft().y, m_rtButtLog.Width(), m_rtButtLog.Height(), PATCOPY);
		pDC->SelectObject(&BrushLine);
		//����ȡ����ť
		m_rtButtCan.BottomRight().x = m_rtEditUserName.BottomRight().x-50;
		m_rtButtCan.TopLeft().x = m_rtButtCan.BottomRight().x - 200;
		m_rtButtCan.TopLeft().y = m_rtButtLog.TopLeft().y;
		m_rtButtCan.BottomRight().y = m_rtButtCan.TopLeft().y + 50;
		if (m_bCanShow)
			pDC->SelectObject(&HighLine);
		else
			pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_rtButtCan.TopLeft().x, m_rtButtCan.TopLeft().y, m_rtButtCan.Width(), m_rtButtCan.Height(), PATCOPY);
		pDC->SelectObject(&BrushLine);

		int nOldMode = pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(&font); //ѡ���µ�����
		pDC->SetTextColor(RGB(255, 255, 255));	//�޸���ɫ
		pDC->SetBkColor(TRANSPARENT);
		CString m_strButtle = "�û�����";
		CRect rect = m_rtEditUserName;
		rect.TopLeft().x -= 100;
		rect.BottomRight().x = rect.TopLeft().x + 200;
		pDC->DrawText(m_strButtle, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_strButtle = "�� �룺";
		rect = m_rtEditUserKey;
		rect.TopLeft().x -= 100;
		rect.BottomRight().x = rect.TopLeft().x + 200;
		pDC->DrawText(m_strButtle, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_strButtle = "�� ¼";
		pDC->DrawText(m_strButtle, &m_rtButtLog, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_strButtle = "ȡ ��";
		pDC->DrawText(m_strButtle, &m_rtButtCan, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->SetBkMode(nOldMode);
	}
}

BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_LOGIN_USERNAME)//���»س��������ǰ���������˺ſ�
		{
			UpdateData(true);
			GetDlgItem(IDC_LOGIN_USERKEY)->SetFocus();
		}
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


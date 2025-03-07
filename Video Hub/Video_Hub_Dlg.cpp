// MFC_TESTDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Video_Hub_App.h"
#include "Video_Hub_Dlg.h"


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_TESTDlg �Ի���


CVideoHubDlg::CVideoHubDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VIDEO_HUB_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVideoHubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVideoHubDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()	
	ON_WM_SETCURSOR()

	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCMOUSEMOVE()

	ON_MESSAGE(WM_OPENNEWDLG, OpenNewDlg)
END_MESSAGE_MAP()


// CMFC_TESTDlg ��Ϣ�������

//# ����Դ����ͼ�꺯�� #
BOOL LoadImageFromResource(CImage *pImage, UINT nResID, LPCTSTR lpTyp)
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

BOOL CVideoHubDlg::OnInitDialog()
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
	temprect = { 0, 0, width,heigh };
	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width(), temprect.Height(), SWP_NOZORDER | SWP_NOMOVE);
	
	m_Brush.CreateSolidBrush(RGB(0,0,0));
	//�Ӵ���
	Log = nullptr;
	Reg = nullptr;
	User = nullptr;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CVideoHubDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVideoHubDlg::OnPaint()
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
HCURSOR CVideoHubDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*************************************************************** �� �� �� �� �� *************************************************************/

HBRUSH CVideoHubDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	pDC->SetBkMode(TRANSPARENT);
	return m_Brush;
	//HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	//return hbr;
}

/*************************************************************** �� �� �� �� �� �� *************************************************************/

BOOL CVideoHubDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	HCURSOR hcur = ::LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	::SetCursor(hcur);
	return TRUE;
	//return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


/*************************************************************** �� �� �� �� �� �� �� �� �� *************************************************************/
//ϵͳ��Ϣ��Ӧ�����ػ溯��
LRESULT CVideoHubDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT lrst = CDialog::DefWindowProc(message, wParam, lParam);
	if (!::IsWindow(m_hWnd))
		return lrst;

	if (
		message == WM_MOVE
		|| message == WM_PAINT
		|| message == WM_NCPAINT
		|| message == WM_NCACTIVATE
		|| message == WM_NOTIFY
		)
	{
		CDC* pWinDC = GetWindowDC();
		if (pWinDC) {
			DrawTitleBar(pWinDC);
			if (Log && !Log->m_bIsClose)
				return lrst;
			if (Reg && !Reg->m_bIsClose)
				return lrst;
			if (User && !User->m_bIsClose)
				return lrst;
			DrawMenuLogo(pWinDC);
			DrawButtle(pWinDC);
		}
		ReleaseDC(pWinDC);
	}
	return lrst;
}

// �ػ������
void CVideoHubDlg::DrawTitleBar(CDC *pDC)
{
	if (m_hWnd)
	{
		CBrush Brush(RGB(0, 0, 0));
		CBrush* pOldBrush = pDC->SelectObject(&Brush);

		CRect rtWnd, rtTitle, rtButtons;
		GetWindowRect(&rtWnd);
		//ȡ�ñ�������λ��
		rtTitle.left = GetSystemMetrics(SM_CXFRAME);
		rtTitle.top = GetSystemMetrics(SM_CYFRAME);
		rtTitle.right = rtWnd.right - rtWnd.left - GetSystemMetrics(SM_CXFRAME);
		rtTitle.bottom = rtTitle.top + GetSystemMetrics(SM_CYSIZE);

		CPoint point;
		
		//������������
		CBrush BrushLine(RGB(21, 18, 17));
		pDC->SelectObject(&BrushLine);
		point.x = rtWnd.Width() - 0;
		point.y = GetSystemMetrics(SM_CYSIZE) + GetSystemMetrics(SM_CYFRAME);
		pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
		pDC->SelectObject(pOldBrush);

		//׼����XP���ť
		CBitmap* pBitmap = new CBitmap;
		CBitmap* pOldBitmap;
		CDC* pDisplayMemDC = new CDC;
		pDisplayMemDC->CreateCompatibleDC(pDC);

		//�ػ��ر�button
		rtButtons.left = rtTitle.right - 50;
		rtButtons.top = rtTitle.top;
		rtButtons.right = rtButtons.left + 50;
		rtButtons.bottom = rtButtons.top + 50;
		if (m_bCloseShow)
			pBitmap->LoadBitmap(IDB_BITMAP_CLOSE2);
		else
			pBitmap->LoadBitmap(IDB_BITMAP_CLOSE);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtExit = rtButtons;
		m_rtButtExit.OffsetRect(rtWnd.TopLeft());
		pBitmap->DeleteObject();

		//�ػ����/�ָ�button
		rtButtons.right = rtButtons.left - 2;
		rtButtons.left = rtButtons.right - 50;
		if (IsZoomed())//�����������󻯣��򷵻�ֵΪ���㣻�������δ��󻯣��򷵻�ֵΪ�㡣
		{
			if (m_bMaxShow)
				pBitmap->LoadBitmap(IDB_BITMAP_SHRINK2);
			else
				pBitmap->LoadBitmap(IDB_BITMAP_SHRINK);
		}			
		else
		{
			if (m_bMaxShow)
				pBitmap->LoadBitmap(IDB_BITMAP_MAX2);
			else
				pBitmap->LoadBitmap(IDB_BITMAP_MAX);
		}
		
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtMax = rtButtons;
		m_rtButtMax.OffsetRect(rtWnd.TopLeft());
		pBitmap->DeleteObject();

		//�ػ���С��button
		rtButtons.right = rtButtons.left - 2;
		rtButtons.left = rtButtons.right - 50;
		if (m_bMiniShow)
			pBitmap->LoadBitmap(IDB_BITMAP_MINI2);
		else
			pBitmap->LoadBitmap(IDB_BITMAP_MINI);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtMin = rtButtons;
		m_rtButtMin.OffsetRect(rtWnd.TopLeft());
		pBitmap->DeleteObject();

		//�ػ�caption
		int nOldMode = pDC->SetBkMode(TRANSPARENT);
		rtTitle.left = 80;
		rtTitle.top = 4;
		rtTitle.bottom = rtTitle.top + 50;

		CFont font;
		font.CreateFont(50, 22, 0, 0, FW_THIN, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("AST"));          
		//�Զ�������
		pDC->SelectObject(&font); //ѡ���µ�����
		pDC->SetTextColor(RGB(194, 89, 136));	//�޸���ɫ
		CString m_strTitle = "Video Hub";
		pDC->DrawText(m_strTitle, &rtTitle, DT_LEFT);
		pDC->SetBkMode(nOldMode);

		DeleteObject(&font);
		//ͼ��
		rtButtons.left = 0;
		rtButtons.top = 4;
		rtButtons.right = rtButtons.left + 80;
		rtButtons.bottom = rtButtons.top + 50;
		pBitmap->LoadBitmap(IDB_BITMAP_LOGO);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

		ReleaseDC(pDisplayMemDC);
		delete pDisplayMemDC;
		delete pBitmap;
	}
}

// �ػ�ر���С����ť
void CVideoHubDlg::DrawCloseButton(CDC *pDC)
{
	if (m_hWnd)
	{
		CRect rtWnd, rtTitle, rtButtons;
		GetWindowRect(&rtWnd);
		//ȡ�ñ�������λ��
		rtTitle.left = GetSystemMetrics(SM_CXFRAME);
		rtTitle.top = GetSystemMetrics(SM_CYFRAME);
		rtTitle.right = rtWnd.right - rtWnd.left - GetSystemMetrics(SM_CXFRAME);
		rtTitle.bottom = rtTitle.top + GetSystemMetrics(SM_CYSIZE);

		//׼����XP���ť
		CBitmap* pBitmap = new CBitmap;
		CBitmap* pOldBitmap;
		CDC* pDisplayMemDC = new CDC;
		pDisplayMemDC->CreateCompatibleDC(pDC);

		//�ػ��ر�button
		rtButtons.left = rtTitle.right - 50;
		rtButtons.top = rtTitle.top + 0;
		rtButtons.right = rtButtons.left + 50;
		rtButtons.bottom = rtButtons.top + 50;
		if (m_bCloseShow)
			pBitmap->LoadBitmap(IDB_BITMAP_CLOSE2);
		else
			pBitmap->LoadBitmap(IDB_BITMAP_CLOSE);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtExit = rtButtons;
		m_rtButtExit.OffsetRect(rtWnd.TopLeft());
		pBitmap->DeleteObject();

		//�ػ���С��button
		rtButtons.right = rtButtons.left - 50;
		rtButtons.left = rtButtons.right - 50;
		if (m_bMiniShow)
			pBitmap->LoadBitmap(IDB_BITMAP_MINI2);
		else
			pBitmap->LoadBitmap(IDB_BITMAP_MINI);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtMin = rtButtons;
		m_rtButtMin.OffsetRect(rtWnd.TopLeft());
		pBitmap->DeleteObject();

		ReleaseDC(pDisplayMemDC);
		delete pDisplayMemDC;
		delete pBitmap;
	}
}
/*************************************************************** �� �� �� �� �� �� �� �� �� *************************************************************/
// ���Ʋ˵�Logo
void CVideoHubDlg::DrawMenuLogo(CDC* pDC) {
	if (m_hWnd)
	{
		//��ʼ��LOGO����
		CBrush BrushBack(RGB(0, 0, 0));
		pDC->SelectObject(&BrushBack);
		pDC->PatBlt(m_MeueLogo.TopLeft().x, m_MeueLogo.TopLeft().y, m_MeueLogo.Width(), m_MeueLogo.Height(), PATCOPY);

		GetWindowRect(&m_MeueLogo);
		ScreenToClient(&m_MeueLogo);
		m_MeueLogo.TopLeft().x += m_MeueLogo.Width() / 2 - 657;
		m_MeueLogo.TopLeft().y += m_MeueLogo.Height() * 0.25;

		CBitmap* pBitmap = new CBitmap;
		CBitmap* pOldBitmap;
		CDC* pDisplayMemDC = new CDC;
		pDisplayMemDC->CreateCompatibleDC(pDC);
		pBitmap->LoadBitmap(IDB_BITMAP_COVER);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(m_MeueLogo.left, m_MeueLogo.top, m_MeueLogo.Width(), m_MeueLogo.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();
		ReleaseDC(pDisplayMemDC);
		delete pDisplayMemDC;
		delete pBitmap;
	}
}
//���ư�ť
void CVideoHubDlg::DrawButtle(CDC* pDC) {
	if (m_hWnd) {
		//��ʼ����ť����
		CBrush BrushBack(RGB(0, 0, 0));
		pDC->SelectObject(&BrushBack);
		pDC->PatBlt(m_rtButtLog.TopLeft().x, m_rtButtLog.TopLeft().y, m_rtButtLog.Width(), 360, PATCOPY);

		//���ư�ť
		CBrush HighLine(RGB(134, 52, 53));		//������ˢ
		CBrush BrushLine(RGB(194, 89, 136));	//�����ˢ
		//���Ƶ�¼��ť
		GetWindowRect(&m_rtButtLog);
		ScreenToClient(&m_rtButtLog);
		m_rtButtLog.TopLeft().x += m_rtButtLog.Width() / 3;
		m_rtButtLog.TopLeft().y += m_rtButtLog.Height() * 0.6;
		m_rtButtLog.BottomRight().x -= m_rtButtLog.TopLeft().x;
		m_rtButtLog.BottomRight().y = m_rtButtLog.TopLeft().y + 60;
		if (m_bLogShow)
			pDC->SelectObject(&HighLine);
		else
			pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_rtButtLog.TopLeft().x, m_rtButtLog.TopLeft().y, m_rtButtLog.Width(), m_rtButtLog.Height(), PATCOPY);
		pDC->SelectObject(&BrushLine);
		//����ע�ᰴť
		m_rtButtRis = m_rtButtLog;
		m_rtButtRis.BottomRight().y += 100;
		m_rtButtRis.TopLeft().y += 100;
		if (m_bRisShow)
			pDC->SelectObject(&HighLine);
		else
			pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_rtButtRis.TopLeft().x, m_rtButtRis.TopLeft().y, m_rtButtRis.BottomRight().x - m_rtButtRis.TopLeft().x, 60, PATCOPY);
		pDC->SelectObject(&BrushLine);
		//���ƷÿͰ�ť
		m_rtButtVis = m_rtButtRis;
		m_rtButtVis.BottomRight().y += 100;
		m_rtButtVis.TopLeft().y += 100;
		if (m_bVisShow)
			pDC->SelectObject(&HighLine);
		else
			pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_rtButtVis.TopLeft().x, m_rtButtVis.TopLeft().y, m_rtButtVis.BottomRight().x - m_rtButtVis.TopLeft().x, 60, PATCOPY);
		pDC->SelectObject(&BrushLine);
		//�����˳���ť
		m_rtButtExi = m_rtButtVis;
		m_rtButtExi.BottomRight().y += 100;
		m_rtButtExi.TopLeft().y += 100;
		if (m_bExiShow)
			pDC->SelectObject(&HighLine);
		else
			pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_rtButtExi.TopLeft().x, m_rtButtExi.TopLeft().y, m_rtButtExi.BottomRight().x - m_rtButtExi.TopLeft().x, 60, PATCOPY);
		pDC->SelectObject(&BrushLine);
		//�����ť����
		int nOldMode = pDC->SetBkMode(TRANSPARENT);
		CFont font;
		font.CreateFont(50, 22, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("AST"));
		//�Զ�������
		pDC->SelectObject(&font); //ѡ���µ�����
		pDC->SetTextColor(RGB(255, 255, 255));	//�޸���ɫ
		CString m_strButtle = "�� ¼";
		pDC->DrawText(m_strButtle, &m_rtButtLog, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_strButtle = "ע ��";
		pDC->DrawText(m_strButtle, &m_rtButtRis, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_strButtle = "�� �� �� �� �� �� ¼";
		pDC->DrawText(m_strButtle, &m_rtButtVis, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_strButtle = "�� ��";
		pDC->DrawText(m_strButtle, &m_rtButtExi, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->SetBkMode(nOldMode);

		DeleteObject(&font);
	}
}
//��Ӧ�Ի�����ƶ�
LRESULT CVideoHubDlg::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return HTCAPTION;
	return CDialogEx::OnNcHitTest(point);
}

//��Ӧ��󻯡���С�����ر���Ϣ
void CVideoHubDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_rtButtExit.PtInRect(point))
		SendMessage(WM_CLOSE);
	else if (m_rtButtMin.PtInRect(point))
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, MAKELPARAM(point.x, point.y));
	else if (m_rtButtMax.PtInRect(point))
		if (IsZoomed())
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, MAKELPARAM(point.x, point.y));
		else
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, MAKELPARAM(point.x, point.y));
	//�û�����ť
	CRect Fixrect;
	GetWindowRect(Fixrect);
	CPoint Fixpoint;
	Fixpoint.x = point.x - Fixrect.TopLeft().x;
	Fixpoint.y = point.y - Fixrect.TopLeft().y;
	if (   m_rtButtLog.PtInRect(Fixpoint)
		|| m_rtButtRis.PtInRect(Fixpoint)
		|| m_rtButtVis.PtInRect(Fixpoint)) {
		OnNcButtonUser(nHitTest, Fixpoint);
	}
	else if (m_rtButtExi.PtInRect(Fixpoint))
		SendMessage(WM_CLOSE);
	CDialogEx::OnNcLButtonDown(nHitTest, point);
}

//������ƶ��������ж��Ƿ�ѡ�а�ť
void CVideoHubDlg::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_rtButtExit.PtInRect(point))
	{
		m_bCloseShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawTitleBar(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if(m_bCloseShow)
	{
		m_bCloseShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawTitleBar(pWinDC);
		ReleaseDC(pWinDC);
	}
	if (m_rtButtMin.PtInRect(point))
	{
		m_bMiniShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawTitleBar(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if(m_bMiniShow)
	{
		m_bMiniShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawTitleBar(pWinDC);
		ReleaseDC(pWinDC);
	}
	if (m_rtButtMax.PtInRect(point))
	{
		m_bMaxShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawTitleBar(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bMaxShow)
	{
		m_bMaxShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawTitleBar(pWinDC);
		ReleaseDC(pWinDC);
	}

	if (Log && !Log->m_bIsClose) 
		return;
	if (Reg && !Reg->m_bIsClose) 
		return;
	if (User && !User->m_bIsClose)
		return;

	CRect Fixrect;
	GetWindowRect(Fixrect);
	CPoint Fixpoint;
	Fixpoint.x = point.x - Fixrect.TopLeft().x;
	Fixpoint.y = point.y - Fixrect.TopLeft().y;
	if (m_rtButtLog.PtInRect(Fixpoint)) {
		m_bLogShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bLogShow) {
		m_bLogShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	if (m_rtButtRis.PtInRect(Fixpoint)) {
		m_bRisShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bRisShow) {
		m_bRisShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	if (m_rtButtVis.PtInRect(Fixpoint)) {
		m_bVisShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bVisShow) {
		m_bVisShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	if (m_rtButtExi.PtInRect(Fixpoint )) {
		m_bExiShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bExiShow) {
		m_bExiShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	CDialogEx::OnNcMouseMove(nHitTest, point);
}

/********************************�ؼ��͹���************************************/
//��Ӧ�˵���ť�������˵����Ӵ���
void CVideoHubDlg::OnNcButtonUser(UINT nHitTest, CPoint point) {
	if (m_rtButtLog.PtInRect(point)) {
		if (Log) {
			delete[]Log;
			Log = nullptr;
		}
		Log = new CLoginDlg(this);
		Log->Create(IDD_LOGIN_DIALOG,this);
		Log->ShowWindow(SW_SHOW);
	}
	else if (m_rtButtRis.PtInRect(point)) {
		if (Reg) {
			delete[]Reg;
			Reg = nullptr;
		}
		Reg = new CRegisterDlg(this);
		Reg->Create(IDD_REGISTER_DIALOG, this);
		Reg->ShowWindow(SW_SHOW);
	}
	else if (m_rtButtVis.PtInRect(point)) {
		Interface New_User;
		New_User.initialize();
		string username = "�ÿ�";
		string userkey = "1";
		if (New_User.signIn(username, userkey)) {		//��¼�ɹ����˺�����Ϸ�
			m_VH_OnlineUserList = New_User;
			m_Log_User = "�ÿ�";
			::SendMessage(this->m_hWnd,WM_OPENNEWDLG, 0, 0);
		}
	}
}
//������Ϣ���û�����
LRESULT CVideoHubDlg::OpenNewDlg(WPARAM wParam, LPARAM lParam) {
	if (User) {
		delete[]User;
		User = nullptr;
	}
	User = new CUserDlg(this);
	User->Create(IDD_USER_DIALOG, this);
	User->m_OnlineUserList = m_VH_OnlineUserList;
	User->ShowWindow(SW_SHOW);
	return 0;
}
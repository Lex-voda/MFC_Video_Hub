// CRegisterDlg.cpp: 实现文件

#pragma once
#include "stdafx.h"
#include "Video_Hub_App.h"
#include "Video_Hub_Dlg.h"
#include "CRegisterDlg.h"
// CRegisterDlg 对话框

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGISTER_DIALOG, pParent)
	, m_Register_Name(_T(""))
	, m_Register_Key(_T(""))
	, m_Gende_Value(0){
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bIsClose = FALSE;
}


void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REGISTER_USERNAME, m_Register_UserName);	//控件消息映射
	DDX_Control(pDX, IDC_REGISTER_USERKEY, m_Register_UserKey);
	DDX_Text(pDX, IDC_REGISTER_USERNAME, m_Register_Name);
	DDX_Text(pDX, IDC_REGISTER_USERKEY, m_Register_Key);
	DDX_Radio(pDX, IDC_REGISTER_MALE, m_Gende_Value);
}

BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()

	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CHAR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_REGISTER_MALE, &CRegisterDlg::OnBnClickedRegisterMale)
END_MESSAGE_MAP()

BOOL LoadResource(CImage* pImage, UINT nResID, LPCTSTR lpTyp)
{
	if (pImage == NULL)
		return false;
	pImage->Destroy();
	// 查找资源
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
	if (hRsrc == NULL)
		return false;
	// 加载资源
	HGLOBAL hImgData = ::LoadResource(AfxGetResourceHandle(), hRsrc);
	if (hImgData == NULL)
	{
		::FreeResource(hImgData);
		return false;
	}
	// 锁定内存中的指定资源
	LPVOID lpVoid = ::LockResource(hImgData);
	LPSTREAM pStream = NULL;
	DWORD dwSize = ::SizeofResource(AfxGetResourceHandle(), hRsrc);
	HGLOBAL hNew = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);
	// 解除内存中的指定资源
	::GlobalUnlock(hNew);
	// 从指定内存创建流对象
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if (ht != S_OK)
	{
		GlobalFree(hNew);
	}
	else
	{
		// 加载图片
		pImage->Load(pStream);
		GlobalFree(hNew);
	}
	// 释放资源
	::FreeResource(hImgData);
	return true;
}

BOOL CRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码
	//初始化窗口尺寸
	int width = GetSystemMetrics(SM_CXFULLSCREEN) * 4 / 5;
	int heigh = GetSystemMetrics(SM_CYFULLSCREEN) * 4 / 5;
	GetWindowRect(&temprect);
	ScreenToClient(&temprect);
	temprect.BottomRight().x = temprect.TopLeft().x + width;
	temprect.BottomRight().y = temprect.TopLeft().y + heigh;
	temprect.TopLeft().y += 50;
	CWnd::SetWindowPos(NULL, temprect.TopLeft().x, temprect.TopLeft().y, temprect.Width(), temprect.Height(), SWP_NOZORDER);

	font.CreateFont(50, 22, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("AST"));

	m_Brush.CreateSolidBrush(RGB(0, 0, 0));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRegisterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRegisterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*************************************************************** 对 话 框 背 景 *************************************************************/

HBRUSH CRegisterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (pWnd->GetDlgCtrlID() == IDC_REGISTER_USERNAME) {
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(194, 89, 136));
		pDC->SelectObject(&font); //选上新的字体 
	}
	if (pWnd->GetDlgCtrlID() == IDC_REGISTER_USERKEY) {
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(194, 89, 136));
		pDC->SelectObject(&font); //选上新的字体 
	}
	if (pWnd->GetDlgCtrlID() == IDC_REGISTER_MALE) {
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(194, 89, 136));
		pDC->SelectObject(&font); //选上新的字体 
	}
	if (pWnd->GetDlgCtrlID() == IDC_REGISTER_FEMALE) {
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(194, 89, 136));
		pDC->SelectObject(&font); //选上新的字体 
	}
	if (pWnd->GetDlgCtrlID() == IDC_REGISTER_DUNNO) {
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(194, 89, 136));
		pDC->SelectObject(&font); //选上新的字体 
	}
	return m_Brush;
}

/*************************************************************** 鼠 标 光 标 设 定 *************************************************************/

BOOL CRegisterDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	HCURSOR hcur = ::LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	::SetCursor(hcur);
	return TRUE;
	//return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}

//系统消息响应调用重绘函数
LRESULT CRegisterDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
//响应按钮
void CRegisterDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_rtButtReg.PtInRect(point)) {
		UpdateData(true);
		Interface New_User;
		New_User.initialize();
		string s_user_name = m_Register_Name.GetBuffer(0);
		string s_user_key = m_Register_Key.GetBuffer(0);
		int s_user_gende = m_Gende_Value;
		if (New_User.signUp(s_user_name, s_user_key, s_user_gende)) {
			//跳出提示框
			MessageBox("注册成功");
			//传参，打开用户界面
			New_User.signIn(s_user_name, s_user_key);
			CVideoHubDlg* pParent = (CVideoHubDlg*)GetParent();
			pParent->m_VH_OnlineUserList = New_User;
			New_User.save();
			pParent->m_Log_User = m_Register_Name;
			HWND hTemp = ::GetParent(this->GetSafeHwnd());	//获得父窗口的句柄
			::SendMessage(hTemp, WM_OPENNEWDLG, 0, 0);
			SendMessage(WM_CLOSE);
		}
		else {
			MessageBox("注册失败，用户名已存在");
		}
	}
	else if (m_rtButtCan.PtInRect(point))
		SendMessage(WM_CLOSE);
	CDialogEx::OnLButtonDblClk(nFlags, point);
}

//在鼠标移动函数中判断是否选中按钮
void CRegisterDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (m_rtButtReg.PtInRect(point))
	{
		m_bRegShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bRegShow)
	{
		m_bRegShow = FALSE;
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

void CRegisterDlg::OnClose()
{
	m_bIsClose = TRUE;
	CDialogEx::OnClose();
}
//绘制LOGO
void CRegisterDlg::DrawMenuLogo() {
	CRect m_MeueLogo;    // 菜单logo位置
	CWnd* pWnd = GetDlgItem(IDC_REGISTER_COVER);
	if (pWnd) {
		//调整LOGO位置
		GetWindowRect(&m_MeueLogo);		//Logo位置
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
//自绘按钮
void CRegisterDlg::DrawButtle(CDC* pDC) {
	if (m_hWnd) {

		//设置控件位置
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
		
		//绘制性别选择按钮

		GetWindowRect(&m_rtEditUserMale);
		ScreenToClient(&m_rtEditUserMale);

		m_rtEditUserMale.TopLeft().x = m_rtEditUserKey.TopLeft().x;
		m_rtEditUserMale.TopLeft().y = m_rtEditUserKey.TopLeft().y + 120;
		m_rtEditUserMale.BottomRight().x = m_rtEditUserMale.TopLeft().x + 200;
		m_rtEditUserMale.BottomRight().y = m_rtEditUserMale.TopLeft().y + 60;
		
		GetWindowRect(&m_rtEditUserFemale); 
		ScreenToClient(&m_rtEditUserFemale);

		m_rtEditUserFemale.TopLeft().x = m_rtEditUserMale.TopLeft().x + m_rtEditUserMale.Width() * 1.6;
		m_rtEditUserFemale.TopLeft().y = m_rtEditUserMale.TopLeft().y;
		m_rtEditUserFemale.BottomRight().x = m_rtEditUserFemale.TopLeft().x + 200;
		m_rtEditUserFemale.BottomRight().y = m_rtEditUserFemale.TopLeft().y + 60;
		
		GetWindowRect(&m_rtEditUserDonno);
		ScreenToClient(&m_rtEditUserDonno);

		m_rtEditUserDonno.TopLeft().x = m_rtEditUserFemale.TopLeft().x + m_rtEditUserFemale.Width() * 1.6;
		m_rtEditUserDonno.TopLeft().y = m_rtEditUserFemale.TopLeft().y;
		m_rtEditUserDonno.BottomRight().x = m_rtEditUserDonno.TopLeft().x + 400;
		m_rtEditUserDonno.BottomRight().y = m_rtEditUserDonno.TopLeft().y + 60;

		//注册输入框
		CWnd* pWnd;
		pWnd = GetDlgItem(IDC_REGISTER_USERNAME);    //获取控件指针
		if (pWnd) {
			pWnd->SetWindowPos(NULL, m_rtEditUserName.TopLeft().x + 80, m_rtEditUserName.TopLeft().y, m_rtEditUserName.Width() - 80, m_rtEditUserName.Height(), SWP_NOZORDER);
			//字体
			pWnd->SetFont(&font);
		}
		pWnd = GetDlgItem(IDC_REGISTER_USERKEY);    //获取控件指针
		if (pWnd) {
			pWnd->SetWindowPos(NULL, m_rtEditUserKey.TopLeft().x + 80, m_rtEditUserKey.TopLeft().y, m_rtEditUserKey.Width() - 80, m_rtEditUserKey.Height(), SWP_NOZORDER);
			//字体
			pWnd->SetFont(&font);
		}

		//性别选择框
		pWnd = GetDlgItem(IDC_REGISTER_MALE);    //获取控件指针
		if (pWnd) {
			pWnd->SetWindowPos(NULL, m_rtEditUserMale.TopLeft().x + 80, m_rtEditUserMale.TopLeft().y, m_rtEditUserMale.Width() - 80, m_rtEditUserMale.Height(), SWP_NOZORDER);
			//字体
			pWnd->SetFont(&font);
		}
		pWnd = GetDlgItem(IDC_REGISTER_FEMALE);    //获取控件指针
		if (pWnd) {
			pWnd->SetWindowPos(NULL, m_rtEditUserFemale.TopLeft().x + 80, m_rtEditUserFemale.TopLeft().y, m_rtEditUserFemale.Width() - 80, m_rtEditUserFemale.Height(), SWP_NOZORDER);
			//字体
			pWnd->SetFont(&font);
		}
		pWnd = GetDlgItem(IDC_REGISTER_DUNNO);    //获取控件指针
		if (pWnd) {
			pWnd->SetWindowPos(NULL, m_rtEditUserDonno.TopLeft().x + 80, m_rtEditUserDonno.TopLeft().y, m_rtEditUserDonno.Width() - 80, m_rtEditUserDonno.Height(), SWP_NOZORDER);
			//字体
			pWnd->SetFont(&font);
		}

		//绘制注册按钮
		CBrush HighLine(RGB(134, 52, 53));		//高亮笔刷
		CBrush BrushLine(RGB(194, 89, 136));	//常规笔刷

		GetWindowRect(&m_rtButtReg);
		ScreenToClient(&m_rtButtReg);
		m_rtButtReg.TopLeft().x = m_rtEditUserMale.TopLeft().x + 50;
		m_rtButtReg.TopLeft().y = m_rtEditUserMale.TopLeft().y + 3 * m_rtEditUserMale.Height();
		m_rtButtReg.BottomRight().x = m_rtButtReg.TopLeft().x + 200;
		m_rtButtReg.BottomRight().y = m_rtButtReg.TopLeft().y + 50;
		if (m_bRegShow)
			pDC->SelectObject(&HighLine);
		else
			pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_rtButtReg.TopLeft().x, m_rtButtReg.TopLeft().y, m_rtButtReg.Width(), m_rtButtReg.Height(), PATCOPY);
		pDC->SelectObject(&BrushLine);
		//绘制取消按钮
		m_rtButtCan.BottomRight().x = m_rtEditUserKey.BottomRight().x - 50;
		m_rtButtCan.TopLeft().x = m_rtButtCan.BottomRight().x - 200;
		m_rtButtCan.TopLeft().y = m_rtButtReg.TopLeft().y;
		m_rtButtCan.BottomRight().y = m_rtButtCan.TopLeft().y + 50;
		if (m_bCanShow)
			pDC->SelectObject(&HighLine);
		else
			pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_rtButtCan.TopLeft().x, m_rtButtCan.TopLeft().y, m_rtButtCan.Width(), m_rtButtCan.Height(), PATCOPY);
		pDC->SelectObject(&BrushLine);

		int nOldMode = pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(&font); //选上新的字体
		pDC->SetTextColor(RGB(255, 255, 255));	//修改颜色
		pDC->SetBkColor(TRANSPARENT);
		CString m_strButtle = "用户名：";
		CRect rect = m_rtEditUserName;
		rect.TopLeft().x -= 100;
		rect.BottomRight().x = rect.TopLeft().x + 200;
		pDC->DrawText(m_strButtle, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_strButtle = "密 码：";
		rect = m_rtEditUserKey;
		rect.TopLeft().x -= 100;
		rect.BottomRight().x = rect.TopLeft().x + 200;
		pDC->DrawText(m_strButtle, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_strButtle = "性 别：";
		rect = m_rtEditUserMale;
		rect.TopLeft().x -= 100;
		rect.BottomRight().x = rect.TopLeft().x + 200;
		pDC->DrawText(m_strButtle, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_strButtle = "注 册";
		pDC->DrawText(m_strButtle, &m_rtButtReg, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_strButtle = "取 消";
		pDC->DrawText(m_strButtle, &m_rtButtCan, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->SetBkMode(nOldMode);
	}
}


BOOL CRegisterDlg::PreTranslateMessage(MSG* pMsg)		//输入框响应回车
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_REGISTER_USERNAME)//按下回车，如果当前焦点是在账号框
		{
			UpdateData(true);
			GetDlgItem(IDC_REGISTER_USERKEY)->SetFocus();
		}
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CRegisterDlg::OnBnClickedRegisterMale()		//更新Radio控件的值
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}

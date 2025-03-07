// CVideoDlg.cpp: 实现文件
//
#include "stdafx.h"
#include "Video_Hub_App.h"
#include "CUserDlg.h"
#include "CVideoDlg.h"


// CVideoDlg 对话框

IMPLEMENT_DYNAMIC(CVideoDlg, CDialogEx)

CVideoDlg::CVideoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIDEO_DIALOG, pParent)
	, m_Delete_videoname(_T(""))
{
	 
}

void CVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DELETE_NAME, m_Delete_videoname);
}


BEGIN_MESSAGE_MAP(CVideoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

BOOL VideoDlg_LoadUserResource(CImage* pImage, UINT nResID, LPCTSTR lpTyp)
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
BOOL CVideoDlg::OnInitDialog()
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
	CUserDlg* pParent = (CUserDlg*)GetParent();
	CRect CrLine = pParent->m_Line;

	temprect.TopLeft().x = CrLine.BottomRight().x + 50;;
	temprect.TopLeft().y = CrLine.TopLeft().y + 150;
	temprect.BottomRight().x = temprect.TopLeft().x + width - CrLine.BottomRight().x -100;
	temprect.BottomRight().y = temprect.TopLeft().y + heigh - 250;
	
	CWnd::SetWindowPos(NULL, temprect.TopLeft().x, temprect.TopLeft().y, temprect.Width(), temprect.Height(), SWP_NOZORDER);

	GetWindowRect(&temprect);
	ScreenToClient(&temprect);

	font.CreateFont(50, 22, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("AST"));

	m_Brush.CreateSolidBrush(RGB(0, 0, 0));
	//设置视频块的大小和头位置
	m_rtVideoHead.TopLeft().x = 50;
	m_rtVideoHead.TopLeft().y = 50;
	m_rtVideoHead.BottomRight().x = temprect.Width() - 150;
	m_rtVideoHead.BottomRight().y = m_rtVideoHead.TopLeft().y + temprect.Height() / 5 + 50;
	m_offset_value = m_rtVideoHead.Height() + 50;		//视频块间隔
	//设置上下翻页按钮位置
	m_pt_Up[0].x = temprect.Width() / 2 - 100;
	m_pt_Up[0].y = temprect.Height() - 200;
	m_pt_Up[1].x = m_pt_Up[0].x + 50;
	m_pt_Up[1].y = m_pt_Up[0].y + 50;
	m_pt_Up[2].x = m_pt_Up[0].x - 50;
	m_pt_Up[2].y = m_pt_Up[1].y;
	m_pt_Up[3] = m_pt_Up[0];

	m_pt_Down[0].x = temprect.Width() / 2 + 100;
	m_pt_Down[0].y = m_pt_Up[0].y + 50;
	m_pt_Down[1].x = m_pt_Down[0].x + 50;
	m_pt_Down[1].y = m_pt_Down[0].y - 50;
	m_pt_Down[2].x = m_pt_Down[0].x - 50;
	m_pt_Down[2].y = m_pt_Down[1].y;
	m_pt_Down[3] = m_pt_Down[0];

	m_rgn_Up.CreatePolygonRgn(m_pt_Up, 3, ALTERNATE); //创建区域  
	m_rgn_Down.CreatePolygonRgn(m_pt_Down, 3, ALTERNATE);
	//视频链表对接
	m_Video_Node = Iterator<Video>();
	if (m_OnlineUserList.online->video_list != nullptr) {
		m_OnlineUser_Video = m_OnlineUserList.online->video_list;
		//初始化视频断点
		m_Video_Node = m_OnlineUser_Video->begin();
	}
	//删除框初始不可见
	GetDlgItem(IDC_DELETE_NAME)->ShowWindow(SW_HIDE); 
	GetDlgItem(IDC_DELETE_TEXT)->ShowWindow(SW_HIDE); 
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVideoDlg::OnPaint()
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
HCURSOR CVideoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*************************************************************** 对 话 框 背 景 *************************************************************/

HBRUSH CVideoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (pWnd->GetDlgCtrlID() == IDC_DELETE_NAME) {
		pDC->SetTextColor(RGB(194, 89, 136));
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SelectObject(&font); //选上新的字体 
	}
	if (pWnd->GetDlgCtrlID() == IDC_DELETE_TEXT) {
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(194, 89, 136));
		pDC->SelectObject(&font); //选上新的字体 
	}
	return m_Brush;
}

/*************************************************************** 鼠 标 光 标 设 定 *************************************************************/

BOOL CVideoDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	HCURSOR hcur = ::LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	::SetCursor(hcur);
	return TRUE;
}
  
//系统消息响应调用重绘函数
LRESULT CVideoDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
			DrawVideoMenu(pWinDC);
			DrawButtle(pWinDC);
		}
		ReleaseDC(pWinDC);
	}
	return lrst;
}

void CVideoDlg::OnClose()
{
	m_bIsClose = TRUE;
	CDialogEx::OnClose();
}
//绘制视频界面
void CVideoDlg::DrawVideoMenu(CDC* pDC) {
	if (m_hWnd) {
		CBrush BrushLine(RGB(194, 89, 136));	//常规笔刷
		CRect crVideoNext = m_rtVideoHead;
		m_rtVideoInf = { crVideoNext.TopLeft().x + 50,crVideoNext.TopLeft().y + 100,crVideoNext.Width() - 50,50 };
		int i = 0;
		Iterator<Video> it = m_Video_Node;
		if (it != Iterator<Video>()) {
			for (Iterator<Video> it = m_Video_Node; it != m_OnlineUser_Video->end(); it++) {
				string titletext;
				CRect textrect = m_rtVideoInf;

				pDC->SelectObject(&BrushLine);
				pDC->PatBlt(crVideoNext.TopLeft().x, crVideoNext.TopLeft().y, crVideoNext.Width(), crVideoNext.Height(), PATCOPY);

				pDC->SelectObject(&font); //选上新的字体
				pDC->SetTextColor(RGB(255, 255, 255));	//修改颜色
				pDC->SetBkColor(RGB(194, 89, 136));
				titletext = "视频名称：" + it->video_name;
				CString CSvideo_name = titletext.c_str();
				pDC->DrawText(CSvideo_name, &textrect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				
				OffsetRect(textrect, 0, 80);

				titletext = "视频大小：" + it->video_size + "MB";
				CString CSvideo_size = titletext.c_str();
				pDC->DrawText(CSvideo_size, &textrect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

				OffsetRect(textrect, 0, 80);

				titletext = "视频时长：" + it->video_time + "Min";;
				CString CSvideo_time = titletext.c_str();
				pDC->DrawText(CSvideo_time, &textrect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

				OffsetRect(textrect, 0, 80);

				titletext = "视频发布者：" + it->video_uploader;
				CString CSvideo_uploader = titletext.c_str();
				pDC->DrawText(CSvideo_uploader, &textrect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				
				m_rtVideoBMP.BottomRight().x = crVideoNext.BottomRight().x - 200;
				m_rtVideoBMP.BottomRight().y = crVideoNext.BottomRight().y - 30;
				m_rtVideoBMP.TopLeft().y = crVideoNext.TopLeft().y + 30;
				m_rtVideoBMP.TopLeft().x = m_rtVideoBMP.BottomRight().x - 450;

				CBitmap* pBitmap = new CBitmap;
				CBitmap* pOldBitmap;
				CDC* pDisplayMemDC = new CDC;
				pDisplayMemDC->CreateCompatibleDC(pDC);
				pBitmap->LoadBitmap(IDB_BITMAP_VIDEO);
				pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
				pDC->BitBlt(m_rtVideoBMP.left, m_rtVideoBMP.top, m_rtVideoBMP.Width(), m_rtVideoBMP.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
				pDisplayMemDC->SelectObject(pOldBitmap);
				pBitmap->DeleteObject();

				i++;
				if (i == m_step)
					break;
				OffsetRect(&crVideoNext, 0, m_offset_value);
				OffsetRect(&m_rtVideoInf, 0, m_offset_value);
			}
		}
		DeleteObject(BrushLine);
	}
}
//绘制按钮
void CVideoDlg::DrawButtle(CDC* pDC) {
	if (m_hWnd) {
		CBrush BrushLine(RGB(194, 89, 136));	//常规笔刷
		CBrush HighLine(RGB(134, 52, 53));		//高亮笔刷
		if(m_bUpShow)
			pDC->SelectObject(&HighLine);
		else
			pDC->SelectObject(&BrushLine);
		pDC->Polygon(m_pt_Up, 3);
		if (m_bDownShow)
			pDC->SelectObject(&HighLine);
		else
			pDC->SelectObject(&BrushLine);
		pDC->Polygon(m_pt_Down, 3);

		m_crVideoDelete1.BottomRight().y = temprect.BottomRight().y - 50;
		m_crVideoDelete1.BottomRight().x = m_rtVideoHead.BottomRight().x;
		m_crVideoDelete1.TopLeft().x = m_crVideoDelete1.BottomRight().x - 110;
		m_crVideoDelete1.TopLeft().y = m_crVideoDelete1.BottomRight().y - 120;
		m_crVideoDelete2 = m_crVideoDelete1;
		m_crVideoDelete2.TopLeft().y -= 28;
		m_crVideoDelete2.TopLeft().x += 4;
		//删除输入框的位置
		m_crEditDelete.BottomRight().x = m_crVideoDelete1.TopLeft().x - 50;
		m_crEditDelete.BottomRight().y = m_crVideoDelete1.BottomRight().y;
		m_crEditDelete.TopLeft().x = m_crEditDelete.BottomRight().x - 450;
		m_crEditDelete.TopLeft().y = m_crEditDelete.BottomRight().y - 50;

		pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_crVideoDelete1.TopLeft().x, m_crVideoDelete2.TopLeft().y, m_crVideoDelete2.Width(), m_crVideoDelete2.Height(), PATCOPY);
		CBitmap* pDBitmap = new CBitmap;
		CBitmap* pDOldBitmap;
		CDC* pDDisplayMemDC = new CDC;
		pDDisplayMemDC->CreateCompatibleDC(pDC);
		if (m_bDeleteShow) {
			pDBitmap->LoadBitmap(IDB_BITMAP_DELETE2);
			pDOldBitmap = (CBitmap*)pDDisplayMemDC->SelectObject(pDBitmap);
			pDC->BitBlt(m_crVideoDelete2.left, m_crVideoDelete2.top, m_crVideoDelete2.Width(), m_crVideoDelete2.Height(), pDDisplayMemDC, 0, 0, SRCCOPY);
		}
		else {
			pDBitmap->LoadBitmap(IDB_BITMAP_DELETE1);
			pDOldBitmap = (CBitmap*)pDDisplayMemDC->SelectObject(pDBitmap);
			pDC->BitBlt(m_crVideoDelete1.left, m_crVideoDelete1.top, m_crVideoDelete1.Width(), m_crVideoDelete1.Height(), pDDisplayMemDC, 0, 0, SRCCOPY);
		}
		pDDisplayMemDC->SelectObject(pDOldBitmap);
		pDBitmap->DeleteObject();
		DeleteObject(BrushLine);
		DeleteObject(HighLine);
	}
}

//响应鼠标按下
void CVideoDlg::OnLButtonDown(UINT nFlags, CPoint point)	
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//上下翻页
	if (m_rgn_Up.PtInRegion(point) && !m_OnlineUserList.online->video_list->empty() ){
		if (m_Video_Node != m_OnlineUser_Video->begin()) {
			m_Video_Node--;
			SendMessage(WM_PAINT);
		}
	}
	else if (m_rgn_Down.PtInRegion(point) && !m_OnlineUserList.online->video_list->empty()) {
		if (m_Video_Node != m_OnlineUser_Video->end() - m_step) {
			m_Video_Node++;
			SendMessage(WM_PAINT);
		}	
	}
	else if (m_crVideoDelete1.PtInRect(point)) {
		CWnd* pWnd;
		pWnd = GetDlgItem(IDC_DELETE_NAME);    //获取控件指针
		if (pWnd) {
			pWnd->SetWindowPos(NULL, m_crEditDelete.TopLeft().x, m_crEditDelete.TopLeft().y, m_crEditDelete.Width(), m_crEditDelete.Height(), SWP_NOZORDER);
			//字体
			pWnd->SetFont(&font);
		}
		if (pWnd->GetStyle() & WS_VISIBLE) 
			GetDlgItem(IDC_DELETE_NAME)->ShowWindow(SW_HIDE);
		else
			GetDlgItem(IDC_DELETE_NAME)->ShowWindow(SW_SHOW);

		pWnd = GetDlgItem(IDC_DELETE_TEXT);    //获取控件指针
		if (pWnd) {
			m_crTextDelete = m_crEditDelete;
			OffsetRect(&m_crTextDelete, 0, -60);
			pWnd->SetWindowPos(NULL, m_crTextDelete.TopLeft().x, m_crTextDelete.TopLeft().y, m_crTextDelete.Width(), m_crTextDelete.Height(), SWP_NOZORDER);
			//字体
			pWnd->SetFont(&font);
		}
		if (pWnd->GetStyle() & WS_VISIBLE)
			GetDlgItem(IDC_DELETE_TEXT)->ShowWindow(SW_HIDE);
		else
			GetDlgItem(IDC_DELETE_TEXT)->ShowWindow(SW_SHOW);
		}
	CDialogEx::OnLButtonDown(nFlags, point);
}

//响应鼠标瞄准
void CVideoDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_rgn_Up.PtInRegion(point))
	{
		m_bUpShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC) 
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bUpShow)
	{
		m_bUpShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC) 
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	if (m_rgn_Down.PtInRegion(point))
	{
		m_bDownShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC) 
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bDownShow)
	{
		m_bDownShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC) 
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	if (m_crVideoDelete1.PtInRect(point))
	{
		m_bDeleteShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bDeleteShow)
	{
		m_bDeleteShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL CVideoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_DELETE_NAME)//按下回车，如果当前焦点是在删除框
		{
			UpdateData(true);
			if (MessageBox("确定要删除该视频吗？", "删除视频", MB_YESNO) == IDYES) {
				string v_name = m_Delete_videoname.GetBuffer(0);
				if (m_OnlineUserList.online->deleteVideo(v_name)) {
					m_OnlineUserList.save();
					CUserDlg* pParent = (CUserDlg*)GetParent();	//父窗口指针
					pParent->m_OnlineUserList = m_OnlineUserList;
					MessageBox("删除成功！");
					SendMessage(WM_CLOSE);
				}
				else {
					MessageBox("您没有这个视频！");
				}
			}
		}
			return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
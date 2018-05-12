// ChartViewerDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ChartViewer.h"
#include "ChartViewerDlg.h"

#include <afxdao.h>
#include "../Common.h"
#include "../License.h"
#include "../AutoTraderDef.h"
#include "ChartViewerDef.h"
#include "RemitRegDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartViewerDlg ダイアログ

CChartViewerDlg::CChartViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChartViewerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChartViewerDlg)
		// メモ: この位置に ClassWizard によってメンバの初期化が追加されます。
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hHook = NULL;
	m_hMapping = NULL;
	m_pMappingView = NULL;
	m_pMappingViewOffset = NULL;
	m_pMappingViewCell = NULL;
	m_nWMUserTimer = 100;
	m_bUserCall = FALSE;
}

void CChartViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartViewerDlg)
		// メモ: この場所には ClassWizard によって DDX と DDV の呼び出しが追加されます。
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChartViewerDlg, CDialog)
	//{{AFX_MSG_MAP(CChartViewerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
//	ON_WM_LBUTTONDBLCLK()
//	ON_WM_RBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER, OnUser)
	ON_MESSAGE(WM_USER + 1, OnUser1)
	ON_MESSAGE(WM_USER + 2, OnUser2)
	ON_MESSAGE(WM_USER + 3, OnUser3)
	ON_MESSAGE(WM_USER + 4, OnUser4)
	ON_MESSAGE(WM_USER + 5, OnUser5)
	ON_MESSAGE(WM_USER + 6, OnUser6)
	ON_MESSAGE(WM_USER + 7, OnUser7)
	ON_MESSAGE(WM_USER + 8, OnUser8)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartViewerDlg メッセージ ハンドラ

BOOL CChartViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。

	SetWindowText(m_strChartViewerWndName);

	ModifyStyle(WS_CAPTION, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);

	CRect RectWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, NULL, &RectWorkArea, 0);

	CRect RectDlg;
	::GetWindowRect(m_hWnd, &RectDlg);

//	RectDlg.DeflateRect(0, 0, 0, 26);

//	RectDlg.OffsetRect(RectWorkArea.Width() - RectDlg.Width(), 0);
//	RectDlg.OffsetRect(- RectDlg.left + 1000, - RectDlg.top);
	RectDlg.OffsetRect(- RectDlg.left + 1003, - RectDlg.top);
	RectDlg.right = RectWorkArea.right;
	MoveWindow(&RectDlg);

	ShowWindow(SW_SHOW);
	UpdateWindow();

	if (CheckLicense()) {
		PostQuitMessage(0);
		return TRUE;
	}

	GetClientRect(&m_rc);
	m_x0 = m_rc.left;
	m_y0 = m_rc.top;
	m_x1 = m_rc.right;
	m_y1 = m_rc.bottom;
	m_w = m_x1 - m_x0;
	m_h = m_y1 - m_y0;

	m_Pen0.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	m_Pen1.CreatePen(PS_SOLID, 0, RGB(0, 0, 255));
	m_Pen2.CreatePen(PS_SOLID, 0, RGB(0, 255, 255));
	m_Pen3.CreatePen(PS_SOLID, 0, RGB(127, 127, 127));
	m_Pen4.CreatePen(PS_SOLID, 0, RGB(255, 255, 127));
//	m_Pen5.CreatePen(PS_SOLID, 0, RGB(127, 127, 255));
//	m_Pen6.CreatePen(PS_SOLID, 0, RGB(127, 255, 127));
//	m_Pen7.CreatePen(PS_SOLID, 0, RGB(255, 255, 127));
	m_Pen8.CreatePen(PS_SOLID, 0, RGB(255, 255, 127));
	m_Pen9.CreatePen(PS_SOLID, 0, RGB(255, 0, 255));
	m_Pen10.CreatePen(PS_DOT, 0, RGB(255, 0, 255));
	m_Pen11.CreatePen(PS_SOLID, 0, RGB(191, 191, 0));
	m_Pen12.CreatePen(PS_SOLID, 0, RGB(223, 223, 223));
	m_Pen13.CreatePen(PS_DOT, 0, RGB(223, 223, 223));
	m_Pen14.CreatePen(PS_SOLID, 0, RGB(0, 255, 0));

	LOGFONT LfCtrl;
	GetFont()->GetLogFont(&LfCtrl);
	LfCtrl.lfHeight = -75;
	m_Font.CreatePointFontIndirect(&LfCtrl);

	CDC* pDC = GetDC();
	m_MemoryDC.CreateCompatibleDC(pDC);
	m_Bitmap.CreateCompatibleBitmap(pDC, m_w, m_h);

	m_pOldBitmap = m_MemoryDC.SelectObject(&m_Bitmap);
	m_pOldPen = m_MemoryDC.SelectObject(&m_Pen0);
	m_pOldFont = m_MemoryDC.SelectObject(&m_Font);

	m_MemoryDC.GetTextMetrics(&m_Metrics);

	ReleaseDC(pDC);

	GetTempPath(MAX_PATH, m_strTempDir.GetBuffer(MAX_PATH));
	m_strTempDir.ReleaseBuffer();
//	m_strTempCompressDir = m_strTempDir + "Compress";

	if (m_nExecMode)
		m_strMeigaraIniFPath = m_strDataDir + "\\" FNAME_MEIGARARTS;
	else
		m_strMeigaraIniFPath = m_strDataDir + "\\" FNAME_MEIGARA;
	m_strNewsIniFPath = m_strDataDir + "\\" FNAME_NEWS;
	if (m_nExecMode == 2)
//		m_strDBFPath = m_strTempCompressDir + "\\" FNAME_RTSDB;
		m_strDBFPath = m_strTempDir + FNAME_RTSDB;
	else
//		m_strDBFPath = m_strTempCompressDir + "\\" FNAME_DB;
		m_strDBFPath = m_strTempDir + FNAME_DB;

	m_nPage = 0;

	// メモリマップドファイルの生成
	DWORD dwMemMapInfoSize = GetAllocationSize(sizeof(DWORD) * 2);
	m_hMapping = ::CreateFileMapping(
		(HANDLE)0xffffffff,	// 共有メモリの場合は0xffffffffを指定
		NULL,				// セキュリティ属性。NULLでよい
		PAGE_READWRITE,		// プロテクト属性を読み書き可能に指定
		0,					// ファイルサイズの上位32ビット
		dwMemMapInfoSize,	// ファイルサイズの下位32ビット
		StrFormat("Funashi_SharedMemory_%06d", m_nThisVer) + m_strUlExeMode);	// メモリマップドファイルの名前
	if (! m_hMapping) {
		DispErrorLog("共有メモリオープンエラー: %s\n", GetLastErrorMessage());
		PostQuitMessage(0);
		return TRUE;
	}

	// プロセス内のアドレス空間にファイルのビューをマップ
	m_pMappingView = (char *)::MapViewOfFile(m_hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (! m_pMappingView) {
		DispErrorLog("共有メモリマップエラー: %s\n", GetLastErrorMessage());
		PostQuitMessage(0);
		return TRUE;
	}
	DWORD dwMemMapSize = *(DWORD *)m_pMappingView;
	DWORD dwMemMapAllPaSize = *((DWORD *)m_pMappingView + 1);

	::UnmapViewOfFile(m_pMappingView);
	m_pMappingView = NULL;
	::CloseHandle(m_hMapping);

	// メモリマップドファイルの生成
	m_hMapping = ::CreateFileMapping(
		(HANDLE)0xffffffff,	// 共有メモリの場合は0xffffffffを指定
		NULL,				// セキュリティ属性。NULLでよい
		PAGE_READWRITE,		// プロテクト属性を読み書き可能に指定
		0,					// ファイルサイズの上位32ビット
		dwMemMapSize,		// ファイルサイズの下位32ビット
		StrFormat("Funashi_SharedMemory_%06d", m_nThisVer) + m_strUlExeMode);	// メモリマップドファイルの名前
	if (! m_hMapping) {
		DispErrorLog("共有メモリオープンエラー: %s\n", GetLastErrorMessage());
		PostQuitMessage(0);
		return TRUE;
	}

	// プロセス内のアドレス空間にファイルのビューをマップ
	m_pMappingViewOffset = (char *)::MapViewOfFile(m_hMapping, FILE_MAP_ALL_ACCESS, 0, dwMemMapInfoSize, dwMemMapAllPaSize);
	if (! m_pMappingViewOffset) {
		DispErrorLog("オフセット共有メモリマップエラー: %d %s\n", GetLastError(), GetLastErrorMessage());
		PostQuitMessage(0);
		return TRUE;
	}

	m_pMappingViewCell = (char *)::MapViewOfFile(m_hMapping, FILE_MAP_ALL_ACCESS, 0, dwMemMapInfoSize + dwMemMapAllPaSize, 0);
	if (! m_pMappingViewCell) {
		DispErrorLog("セル共有メモリマップエラー: %d %s\n", GetLastError(), GetLastErrorMessage());
		PostQuitMessage(0);
		return TRUE;
	}

	DlData0();
	User2();
	User7();

//	SetWMUserTimer(0, 2, NULL);
	User1();

	m_hHook = SetWindowsHookEx( WH_GETMESSAGE, GetMsgProc, NULL, GetCurrentThreadId() );
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CChartViewerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDC* pDC = GetDC();
		pDC->BitBlt(m_x0, m_y0, m_w, m_h, &m_MemoryDC, 0, 0, SRCCOPY);
		ReleaseDC(pDC);

		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CChartViewerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

LRESULT CChartViewerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	// OnWndMsg does most of the work, except for DefWindowProc call
	LRESULT lResult = 0;
	if (message != WM_TIMER  && message < WM_USER)
		nPumpWaitingMessages ++;
	if (!OnWndMsg(message, wParam, lParam, &lResult))
		lResult = DefWindowProc(message, wParam, lParam);
	if (message != WM_TIMER  && message < WM_USER)
		nPumpWaitingMessages --;
	return lResult;
	
//	return CDialog::WindowProc(message, wParam, lParam);
}

void CChartViewerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください

	// ★ファイルのビューをアンマップし、マップのハンドルをクローズ
	if (m_pMappingViewCell)
		::UnmapViewOfFile(m_pMappingViewCell);
	if (m_pMappingViewOffset)
		::UnmapViewOfFile(m_pMappingViewOffset);
	if (m_pMappingView)
		::UnmapViewOfFile(m_pMappingView);
	if (m_hMapping)
		::CloseHandle(m_hMapping);

	m_MemoryDC.SelectObject(m_pOldFont);
	m_MemoryDC.SelectObject(m_pOldPen);
	m_MemoryDC.SelectObject(m_pOldBitmap);
	m_MemoryDC.DeleteDC();

	if (m_hHook)
		UnhookWindowsHookEx( m_hHook );
}

void CChartViewerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
//	if (nIDEvent < 100) {
//		if (PreUser(nIDEvent, 0, NULL)) {
//			nPumpWaitingMessages ++;
//			switch (nIDEvent) {
//			default:
//			}
//			nPumpWaitingMessages --;
//		}
//	} else {
		KillTimer(nIDEvent);
		WMParam WMParamTemp;
		m_MltwmpWMUserTimer.Lookup(nIDEvent, WMParamTemp);
		m_MltwmpWMUserTimer.RemoveKey(nIDEvent);
		if (WMParamTemp.lpUserFunc)
			(this->*WMParamTemp.lpUserFunc)(WMParamTemp.wParam, WMParamTemp.lParam);
		else
			OnTimer(WMParamTemp.wParam);
//	}
	
	CDialog::OnTimer(nIDEvent);
}

void CChartViewerDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
	CDialog::OnOK();
}

void CChartViewerDlg::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	
	CDialog::OnCancel();
}

void CChartViewerDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CWnd* pWnd;
	if (pWnd = FindWindow(NULL, m_strTradeHelperWndName)) {
		int nIndex = point.y / 94;
		pWnd->PostMessage(WM_USER + 1, 0, m_nPage && nIndex ? m_SaNiceCode.GetSize() + (m_nPage - 1) * 10 + (nIndex - 1) : nIndex);
	}
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CChartViewerDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if (m_nPage == 0) {
		CWnd* pWnd;
		if (pWnd = FindWindow(NULL, m_strMainExeWndName))
			pWnd->PostMessage(WM_USER + 1, atoi(m_SaNiceCode[point.y / 94].Left(4)), 1);
	}
	
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CChartViewerDlg::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if (m_nPage == 0) {
		CWnd* pWnd;
		if (pWnd = FindWindow(NULL, m_strMainExeWndName))
			pWnd->PostMessage(WM_USER + 1, atoi(m_SaNiceCode[point.y / 94].Left(4)), 0);
		m_DwaNiceBuy[point.y / 94] = 0L;
	} else
		m_DwaSelBuy[(m_nPage - 1) * 10 + (point.y / 94 - 1)] = 0L;
	
	CDialog::OnRButtonDblClk(nFlags, point);
}

LRESULT CChartViewerDlg::OnUser(WPARAM wParam, LPARAM lParam)
{
	if (! PreUser(wParam, lParam))
		return 0;
	nPumpWaitingMessages ++;
	switch (wParam) {
//	case 1:
//		DestroyWindow();
//		break;
	case 2:
//		COleDateTime DtCur = GetCurrentTimeEx();
//		int nMinute = DtCur.GetMinute();
//		int nSecond0 = DtCur.GetSecond() / TIMEUNIT * TIMEUNIT;

		User1();

//		DtCur = GetCurrentTimeEx();
//		int nSecond = DtCur.GetSecond();
//		int nSecond1 = nSecond / TIMEUNIT * TIMEUNIT;
//		SetWMUserTimer(DtCur.GetMinute() == nMinute  &&  nSecond1 == nSecond0  ? (TIMEUNIT - nSecond % TIMEUNIT) * 1000 : 0, wParam, NULL);
		break;
	case 3:
		User2();
		break;
	case 4:
		User3();
		break;
	case 5:
		User4(lParam);
		break;
	case 6:
		User5(lParam);
		break;
	case 7:
		User6(lParam);
		break;
	case 8:
		User7();
		break;
	case 9:
		User8();
	}
	nPumpWaitingMessages --;
	return 0;
}

LRESULT CChartViewerDlg::OnUser1(WPARAM wParam, LPARAM lParam)
{
	if (m_nExecMode == 2) {
		COleDateTimeSpan Dts(wParam, lParam / (60 * 60), lParam / 60 % 60, lParam % 60);
		if (Dts != DtsCurrentTime) {
			DtsCurrentTime = Dts;
			DlData0();
			User2();
		}
	}

	KillWMUserTimer(2);
	SetWMUserTimer(0, 2, NULL);

	return 0;
}

LRESULT CChartViewerDlg::OnUser2(WPARAM wParam, LPARAM lParam)
{
	KillWMUserTimer(3);
	SetWMUserTimer(0, 3, NULL);

	return 0;
}

LRESULT CChartViewerDlg::OnUser3(WPARAM wParam, LPARAM lParam)
{
	KillWMUserTimer(4);
	SetWMUserTimer(0, 4, NULL);

	return 0;
}

LRESULT CChartViewerDlg::OnUser4(WPARAM wParam, LPARAM lParam)
{
	m_DwaParamUser4.Add(wParam);
	SetWMUserTimer(0, 5, lParam);

	return 0;
}

LRESULT CChartViewerDlg::OnUser5(WPARAM wParam, LPARAM lParam)
{
	SetWMUserTimer(0, 6, wParam);
	return 0;
}

LRESULT CChartViewerDlg::OnUser6(WPARAM wParam, LPARAM lParam)
{
	SetWMUserTimer(0, 7, wParam);
	return 0;
}

LRESULT CChartViewerDlg::OnUser7(WPARAM wParam, LPARAM lParam)
{
	KillWMUserTimer(8);
	SetWMUserTimer(0, 8, NULL);

	return 0;
}

LRESULT CChartViewerDlg::OnUser8(WPARAM wParam, LPARAM lParam)
{
	KillWMUserTimer(9);
	SetWMUserTimer(0, 9, NULL);

	return 0;
}

BOOL CChartViewerDlg::PreUser(WPARAM wParam, LPARAM lParam, USERPROC lpUserFunc)
{
	while (m_bUserCall == FALSE  &&  nPumpWaitingMessages == 0  &&  m_WmpaUser.GetSize()) {
		WMParam& WMParamTemp = m_WmpaUser[0];
		m_bUserCall = TRUE;
		if (WMParamTemp.lpUserFunc)
			(this->*WMParamTemp.lpUserFunc)(WMParamTemp.wParam, WMParamTemp.lParam);
		else
			OnTimer(WMParamTemp.wParam);
		m_bUserCall = FALSE;
		m_WmpaUser.RemoveAt(0);
	}
	if (lpUserFunc == OnUser  &&  wParam == 0) {
		if (m_WmpaUser.GetSize())
			SetWMUserTimer(100);
		return FALSE;
	}
	if (nPumpWaitingMessages) {
		WMParam WMParamTemp;
		WMParamTemp.wParam = wParam;
		WMParamTemp.lParam = lParam;
		WMParamTemp.lpUserFunc = lpUserFunc;
		if (m_WmpaUser.Add(WMParamTemp) == 0)
			SetWMUserTimer(100);
		return FALSE;
	}
	return TRUE;
}

BOOL CChartViewerDlg::SetWMUserParam(UINT nIDEvent, WPARAM wParam, LPARAM lParam, USERPROC lpUserFunc)
{
	WMParam WMParamTemp;
	if (m_MltwmpWMUserTimer.Lookup(nIDEvent, WMParamTemp))
		return FALSE;
	WMParamTemp.wParam = wParam;
	WMParamTemp.lParam = lParam;
	WMParamTemp.lpUserFunc = lpUserFunc;
	m_MltwmpWMUserTimer[nIDEvent] = WMParamTemp;
	return TRUE;
}

void CChartViewerDlg::SetWMUserTimer(UINT nElapse, WPARAM wParam, LPARAM lParam, USERPROC lpUserFunc)
{
	WMParam WMParamTemp;
	while (m_MltwmpWMUserTimer.Lookup(m_nWMUserTimer, WMParamTemp)) {
		if (++ m_nWMUserTimer < 100U)
			m_nWMUserTimer = 100;
		PumpWaitingMessages();
	}
	WMParamTemp.wParam = wParam;
	WMParamTemp.lParam = lParam;
	WMParamTemp.lpUserFunc = lpUserFunc;
	m_MltwmpWMUserTimer[m_nWMUserTimer] = WMParamTemp;
	SetTimer(m_nWMUserTimer, nElapse, NULL);
	if (++ m_nWMUserTimer < 100U)
		m_nWMUserTimer = 100;
}

void CChartViewerDlg::KillWMUserTimer(WPARAM wParam)
{
	POSITION pos = m_MltwmpWMUserTimer.GetStartPosition();
	UINT nIDEvent;
	WMParam WMParamTemp;
	while (pos) {
		m_MltwmpWMUserTimer.GetNextAssoc(pos, nIDEvent, WMParamTemp);
		if (WMParamTemp.wParam == wParam) {
			KillTimer(nIDEvent);
			m_MltwmpWMUserTimer.RemoveKey(nIDEvent);
			break;
		}
	}
}

int CChartViewerDlg::DlData0()
{
	int nRv = -1;

	CDaoDatabase Database;

	try
	{
		COleDateTime DtCur;
		COleVariant pKeyArray[2];
		COleVariant var;
		CString strCode;

		Database.Open(m_strDBFPath, FALSE, TRUE);

		CDaoRecordset RsHiashiPreDate(&Database);
		RsHiashiPreDate.Open(dbOpenTable, TBL_HIASHI);
		RsHiashiPreDate.SetCurrentIndex(pszPrimaryKey);

		DtCur = GetCurrentTimeEx();
		if (DtCur.GetHour() < 8) {
			CDaoRecordset RsFunashiDateTime(&Database);
			RsFunashiDateTime.Open(dbOpenTable, TBL_FUNASHIDATETIME);
			RsFunashiDateTime.SetCurrentIndex(pszPrimaryKey);

			pKeyArray[0] = COleVariant(DtCur);
			if (RsFunashiDateTime.Seek("<=", pKeyArray, 1)) {
				RsFunashiDateTime.GetFieldValue(0, var);
				m_DtDate = var.date;
				m_DtDate.SetDate(m_DtDate.GetYear(), m_DtDate.GetMonth(), m_DtDate.GetDay());
			}
		} else
			m_DtDate.SetDate(DtCur.GetYear(), DtCur.GetMonth(), DtCur.GetDay());

		pKeyArray[0] = COleVariant(m_DtDate);
		if (RsHiashiPreDate.Seek("<", pKeyArray, 2)) {
			RsHiashiPreDate.GetFieldValue(0, var);
			m_DtPreDate = var.date;
		}
	}
	catch (CException* pEx) {
		DispErrorLog("銘柄分足データダウンロードエラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
		goto CleanUp;
	}

	nRv = 0;

CleanUp:

	return nRv;
}

int CChartViewerDlg::HiashiAnalyze(LPCTSTR lpszCode)
{
	int nRv = -1;

	int i;
	int j;
	int k;
	int imax;
	int jmax;
	COleDateTime DtDate;
	COleDateTime DtStartDate;
	COleDateTime DtCur;
	CDaoDatabase Database;

	DtCur = GetCurrentTimeEx();
	DtDate.SetDate(DtCur.GetYear(), DtCur.GetMonth(), DtCur.GetDay());
	DtStartDate = DtDate - COleDateTimeSpan(60, 0, 0, 0);

	if (lpszCode == NULL) {
		m_PaFunashi.RemoveAll();

		m_SaHiashiCode.RemoveAll();
		m_SaHiashiName.RemoveAll();
		m_SaHiashiType.RemoveAll();
		m_WaHiashiUnit.RemoveAll();
		m_DwaHiashiPreEndPrice.RemoveAll();
		m_DwaHiashiPreEndTradeCount.RemoveAll();
		m_DwaHiashiStartPrice.RemoveAll();
		m_DwaHiashiPriceAve25.RemoveAll();
	}

	try
	{
		CString strName;
		CString strType;
		CString strCode;
		CString strCurCode;
		CStringBuffer sbSql;
		COleVariant pKeyArray[1];
		COleVariant var;
		long plPrice[25];
		long lPreEndPrice;
		long lPreEndTradeCount;
		long lHiashiStartPrice;
		long lPriceSum;

		Database.Open(m_strDBFPath, FALSE, TRUE);

		CDaoRecordset RsInfo(&Database);
		if (lpszCode)
			sbSql = StrFormat("= '%s'", lpszCode);
		else
			if (imax = m_SaSelCode.GetSize()) {
				sbSql = "IN (";
				for (i = 0; i < imax; i ++) {
					if (i)
						sbSql += ',';
					sbSql += StrFormat("'%s'", m_SaSelCode[i]);
				}
				sbSql += ")";
			}
		if (sbSql.GetLength())
			RsInfo.Open(
				dbOpenSnapshot,
				StrFormat(
					"SELECT *"
					" FROM " TBL_INFO
					" WHERE " FLD_IN_CODE " %s"
					" ORDER BY " FLD_IN_CODE,
					sbSql
				),
				dbForwardOnly
			);

		if (lpszCode == NULL) {
			m_SaHiashiCode.Add("101");
			m_SaHiashiName.Add("日経平均225先物");
			m_SaHiashiType.Add(pszEmpty);
			m_WaHiashiUnit.Add(1);
		}

		if (sbSql.GetLength()) {
			while (! RsInfo.IsEOF()) {
				RsInfo.GetFieldValue(0, var);
				m_SaHiashiCode.Add(V_BSTRT((LPVARIANT)var));

				RsInfo.GetFieldValue(1, var);
				m_SaHiashiName.Add(V_BSTRT((LPVARIANT)var));

				RsInfo.GetFieldValue(3, var);
				m_SaHiashiType.Add(V_BSTRT((LPVARIANT)var));

				RsInfo.GetFieldValue(4, var);
				m_WaHiashiUnit.Add(var.iVal);

				RsInfo.MoveNext();
			}

			RsInfo.Close();
		}

		jmax = m_SaHiashiCode.GetSize();

		m_DwaHiashiPreEndPrice.SetSize(jmax);
		m_DwaHiashiPreEndTradeCount.SetSize(jmax);
		m_DwaHiashiStartPrice.SetSize(jmax);
		m_DwaHiashiPriceAve25.SetSize(jmax);

		for (i = lpszCode ? jmax - 1 : 0; i < jmax; i ++)
			m_PaFunashi.Add(m_pMappingViewOffset + MEMMAPPASIZE * i + sizeof(long));

		CDaoRecordset RsHiashi(&Database);
		if (lpszCode)
			sbSql = StrFormat(" = '%s'", lpszCode);
		else
			if (imax = m_SaSelCode.GetSize()) {
				sbSql = "IN (";
				for (i = 0; i < imax; i ++) {
					if (i)
						sbSql += ',';
					sbSql += StrFormat("'%s'", m_SaSelCode[i]);
				}
				sbSql += ")";
			}
		if (sbSql.GetLength()) {
			RsHiashi.Open(
				dbOpenSnapshot,
				StrFormat(
					"SELECT "
						FLD_HI_DATE ", "
						FLD_HI_CODE ", "
						FLD_HI_STARTPRICE ", "
						FLD_HI_PRICE ", "
						FLD_HI_TRADECOUNT
					" FROM " TBL_HIASHI
					" WHERE "
						FLD_HI_DATE " >= #%s#"
						" AND " FLD_HI_DATE " <= #%s#"
						" AND " FLD_HI_CODE " %s"
					" ORDER BY "
						FLD_HI_CODE ", "
						FLD_HI_DATE " DESC",
					DtStartDate.Format("%Y/%m/%d"), DtDate.Format("%Y/%m/%d"), sbSql
				),
				dbForwardOnly
			);

			for (i = lpszCode ? jmax - 1 : 0, imax = m_SaHiashiCode.GetSize(); i < imax; i ++) {
				strCode = m_SaHiashiCode[i];

				lPreEndTradeCount = lHiashiStartPrice = 0L;

				for (j = 0; j < 25; ) {
					if (RsHiashi.IsEOF())
						break;

					RsHiashi.GetFieldValue(1, var);
					strCurCode = V_BSTRT((LPVARIANT)var);

					if (strCurCode > strCode)
						break;

					if (strCurCode == strCode) {
						RsHiashi.GetFieldValue(0, var);
						if ((COleDateTime)var.date == DtDate) {
							RsHiashi.GetFieldValue(2, var);
							lHiashiStartPrice = var.lVal;
						} else {
							RsHiashi.GetFieldValue(3, var);
							plPrice[j] = var.lVal;

							if (j == 0) {
								RsHiashi.GetFieldValue(4, var);
								lPreEndTradeCount = var.lVal;
							}

							j ++;
						}
					}

					RsHiashi.MoveNext();
				}

				if (j) {
					lPreEndPrice = plPrice[0];
				} else
					lPreEndPrice = 0L;
				m_DwaHiashiPreEndPrice[i] = lPreEndPrice;
				m_DwaHiashiPreEndTradeCount[i] = lPreEndTradeCount;
				m_DwaHiashiStartPrice[i] = lHiashiStartPrice;
				lPriceSum = 0L;
				for (k = 0; k < j; k ++)
					lPriceSum += plPrice[k];
				m_DwaHiashiPriceAve25[i] = j ? lPriceSum / j : 0L;
			}
		}
	}
	catch (CException* pEx) {
		DispErrorLog("銘柄日足データ分析エラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
		goto CleanUp;
	}

	if (lpszCode)
		m_MstpHiashiCode[lpszCode] = (void *)m_SaHiashiCode.GetUpperBound();
	else {
		m_MstpHiashiCode.RemoveAll();
		for (i = 0; i < m_SaHiashiCode.GetSize(); i ++)
			m_MstpHiashiCode[m_SaHiashiCode[i]] = (void *)i;
	}

	nRv = 0;

CleanUp:

	return nRv;
}

CFunashi0 CChartViewerDlg::GetFunashi(long* plFunashi, int nIndex)
{
	static CFunashi0 Funashi0;
	static CFunashi0* pFunashi0;
	static CFunashi2* pFunashi2;

	pFunashi0 = (CFunashi0 *)(m_pMappingViewCell + plFunashi[nIndex]);

	switch (pFunashi0->m_nType) {
	case 0:
		return *pFunashi0;
	case 1:
		*(CFunashi1 *)&Funashi0 = *(CFunashi1 *)pFunashi0;
		Funashi0.m_dVwap = 0.0;
		Funashi0.m_Kehai.Empty();
		break;
	default:
		pFunashi2 = (CFunashi2 *)pFunashi0;
		Funashi0.m_DtDateTime = pFunashi2->m_DtDateTime;
		Funashi0.m_lPrice = pFunashi2->m_lPrice;
		Funashi0.m_dVwap = 0.0;
		Funashi0.m_Kehai.Empty();
		Funashi0.m_Kehai.m_plKehaiPrice[4] = pFunashi2->m_Kehai.m_plKehaiPrice[0];
		Funashi0.m_Kehai.m_plKehaiPrice[5] = pFunashi2->m_Kehai.m_plKehaiPrice[1];
		Funashi0.m_Kehai.m_plKehaiCount[4] = pFunashi2->m_Kehai.m_plKehaiCount[0];
		Funashi0.m_Kehai.m_plKehaiCount[5] = pFunashi2->m_Kehai.m_plKehaiCount[1];
	}

	return Funashi0;
}

CFunashi0 CChartViewerDlg::GetFunashi(int nIndex0, int nIndex1)
{
	return GetFunashi((long *)m_PaFunashi[nIndex0], nIndex1);
}

void CChartViewerDlg::DispChart() 
{
	int i;
	int j;
	float k;
	int l;
//	int m;
	int n;
	int imax;
	int jmax;
	COleDateTime DtCur;
	COleDateTime DtCurMinute;
	COleDateTime DtStartMinute0;
	COleDateTime DtStartMinute1;
	COleDateTime Dt;
	COleDateTime DtNew;
	COleDateTime DtDateTime;
	COleDateTime DtEmpty;
	int nCurYear;
	int nCurMonth;
	int nCurDay;
	int nCurHour;
	int nCurMinute;
	int nCurSecond;
	short sUnit;
	long* plFunashi;
	CKehai0 KehaiWork0;
	CKehai0 KehaiWork1;
	CFunashi0 FunashiWork0;
	CFunashi0 FunashiWork1;
	long lPrice;
//	long lTradeCount;
//	long lPreTradeCount;
	long lTradeCount0;
	long lTradeCount1;
	long lTradeCount01;
	long lMaxTradeCount;
	double dVwap0;
	double dVwap1;
	long lNari;
	long lDiff;
	long lStopDiff;
	long lPreEndPrice;
	long lStartPrice;
	CFunashi0 FunashiLast;
	long lLastPrice;
	long lLastTradeCount;
	long lLastDiff;
	int nSkip0Minutes;
	int nTotalMinutes;
	float fTimeUnit;
	BOOL b0900;
	BOOL b1230;
	long lMaxKehaiPrice;
	long lMinKehaiPrice;
	long lKehaiPriceRange;
	long lSellKehaiPriceRange;
	long lBuyKehaiPriceRange;
	long lSumSellKehaiCount;
	long lSumBuyKehaiCount;
	long lKehaiPower;
	long lKehaiPowerCount;
	CString strCode;
	CString strDispCode;
	CString strSijo;
	CString strName;
	COLORREF crDefaultTextColor;
	BOOL bValueOK;
	int nPreJ;
//	int nPreJ2;
	int nIndex;
	CString strText;
	CSize Size;
	void* pVoid;
	COLORREF crKehaiPower;
	LOGPEN LogPen;
	int base;
	int top;
	int bottom;
	BOOL tradecountcalc;
	double tradecountmul;
	long kehaicount;
//	int max = 0;
//	int min = INT_MAX;
	int ax0;
	int ay0;
	int ax1;
	int ay1;
	int bx0;
	int by0;
	int bx1;
	int by1;
	int cx0;
	int cy0;
	int cx1;
	int cy1;
	int dx1;
	int dy1;
//	int ex0;
//	int ey0;
//	int ex1;
//	int ey1;
//	int fx0;
//	int fy0;
//	int fx1;
//	int fy1;
	int gx0;
	int gy0;
	int gx1;
	int gy1;
	long l0;
	long l1;
	long l2;
	double d0;
	double d1;
//	double d2;
//	double d3;
//	double d4;
//	double d5;
//	double d6;

	m_MemoryDC.FillSolidRect(0, 0, m_w, m_h, RGB(255, 255, 255));

//	DtCur = GetCurrentTimeEx();
	for (i = 0, imax = m_PaFunashi.GetSize(); i < imax; i ++) {
		plFunashi = (long *)m_PaFunashi[i];
		j = plFunashi[-1] - 1;
		if (j != -1) {
			Dt = ((CFunashi0 *)(m_pMappingViewCell + plFunashi[j]))->m_DtDateTime;
			if (Dt > DtCur)
				DtCur = Dt;
		}
	}
	if (DtCur == DtEmpty)
		DtCur.SetDateTime(m_DtDate.GetYear(), m_DtDate.GetMonth(), m_DtDate.GetDay(), 7, 59, 59);

	nCurHour = DtCur.GetHour();

	if (nCurHour < 8) {
		nCurYear = m_DtDate.GetYear();
		nCurMonth = m_DtDate.GetMonth();
		nCurDay = m_DtDate.GetDay();
		nCurHour = 15;
		nCurMinute = 0;
		nCurSecond = 0;
	} else {
		nCurYear = DtCur.GetYear();
		nCurMonth = DtCur.GetMonth();
		nCurDay = DtCur.GetDay();
		nCurMinute = DtCur.GetMinute();
		nCurSecond = DtCur.GetSecond();
	}

	DtCurMinute.SetDateTime(nCurYear, nCurMonth, nCurDay, nCurHour, nCurMinute, nCurSecond / TIMEUNIT * TIMEUNIT);

	COleDateTime Dt0800(nCurYear, nCurMonth, nCurDay, 8, 0, 0);
	COleDateTime Dt0900(nCurYear, nCurMonth, nCurDay, 9, 0, 0);
//	COleDateTime Dt1059(nCurYear, nCurMonth, nCurDay, 11, 0, 60 - TIMEUNIT);
	COleDateTime Dt1059(nCurYear, nCurMonth, nCurDay, 11, 30, 60 - TIMEUNIT);
	COleDateTime Dt1100(nCurYear, nCurMonth, nCurDay, 11, 1, 0);
//	COleDateTime Dt1130(nCurYear, nCurMonth, nCurDay, 11, 30, 0);
	COleDateTime Dt1130(nCurYear, nCurMonth, nCurDay, 12, 0, 0);
	COleDateTime Dt1205(nCurYear, nCurMonth, nCurDay, 12, 5, 0);
	COleDateTime Dt1230(nCurYear, nCurMonth, nCurDay, 12, 30, 0);
	COleDateTime Dt1459(nCurYear, nCurMonth, nCurDay, 15, 15, 60 - TIMEUNIT);
	COleDateTime Dt1500(nCurYear, nCurMonth, nCurDay, 15, 16, 0);
	COleDateTime Dt1530(nCurYear, nCurMonth, nCurDay, 15, 30, 0);

	if (DtCurMinute > Dt1100  &&  DtCurMinute < Dt1205)
		DtCurMinute = Dt1100;
	if (DtCurMinute > Dt1500)
		DtCurMinute = Dt1500;

//	DtStartMinute = FixDateTime(DtCurMinute - COleDateTimeSpan(0, 0, 0, TIMEUNIT * (m_w / 3) - 4));
//	DtStartMinute0 = FixDateTime(DtCurMinute - COleDateTimeSpan(0, 0, 0, TIMEUNIT * 5 * (m_w / 3) + TIMEUNIT * (m_w / 3) - 4));
	DtStartMinute0 = FixDateTime(DtCurMinute - COleDateTimeSpan(0, 0, 0, TIMEUNIT * 5 * (m_w / 3) + TIMEUNIT * (m_w / 3)));
//	DtStartMinute1 = FixDateTime(DtCurMinute - COleDateTimeSpan(0, 0, 0, TIMEUNIT * (m_w / 3) - 4));
	DtStartMinute1 = FixDateTime(DtCurMinute - COleDateTimeSpan(0, 0, 0, TIMEUNIT * (m_w / 3)));

	if (DtStartMinute0 < Dt0800)
		DtStartMinute0 = Dt0800;
	if (DtStartMinute1 < Dt0800)
		DtStartMinute1 = Dt0800;

//	nSkip0Minutes = DtStartMinute0 < Dt1100 ? 0 : (DtStartMinute0 < Dt1205 ? (int)(DtStartMinute0 - Dt1100).GetTotalSeconds() : 64 * 60);
	nSkip0Minutes = DtStartMinute0 < Dt1100 ? 0 : (DtStartMinute0 < Dt1205 ? (int)(DtStartMinute0 - Dt1100).GetTotalSeconds() : 34 * 60);
	nTotalMinutes = ((int)(DtStartMinute0 - Dt0800).GetTotalSeconds() - nSkip0Minutes) / TIMEUNIT;

//	fTimeUnit = (float)(m_w * 2 / 3) / nTotalMinutes;
	fTimeUnit = nTotalMinutes ? (float)(m_w / 3) / nTotalMinutes : 0.0F;

	for (n = 0; n < 11; n ++) {
		if (n) {
			if (m_nPage) {
				nIndex = (m_nPage - 1) * 10 + (n - 1);
				if (nIndex > m_SaSelCode.GetUpperBound())
					break;
				strCode = m_SaSelCode[nIndex];
			} else {
				nIndex = n;
				if (nIndex > m_SaNiceCode.GetUpperBound())
					break;
				strCode = m_SaNiceCode[nIndex];
			}
		} else {
			nIndex = 0;
			strCode = m_SaNiceCode[nIndex];
		}
		if (m_MstpHiashiCode.Lookup(strCode, pVoid)) {
			i = (int)pVoid;

			if (i)
				strSijo = strCode.Mid(5);

			sUnit = m_WaHiashiUnit[i];

			plFunashi = (long *)m_PaFunashi[i];

			jmax = plFunashi[-1] - 1;

			if (i) {
				lStartPrice = m_DwaHiashiStartPrice[i];
				if (
					lStartPrice == 0L
					&&  jmax >= 0
					&&  ! ((CFunashi0 *)(m_pMappingViewCell + plFunashi[0]))->m_lPrice
					&&  ((CFunashi0 *)(m_pMappingViewCell + plFunashi[jmax]))->m_lPrice
				)
					for (j = 0; j <= jmax; j ++)
						if (lPrice = ((CFunashi0 *)(m_pMappingViewCell + plFunashi[j]))->m_lPrice) {
							lStartPrice = m_DwaHiashiStartPrice[i] = lPrice;
							break;
						}

				lPreEndPrice = m_DwaHiashiPreEndPrice[i];
				if (lPreEndPrice == 0L)
					lPreEndPrice = lStartPrice;
			}

			lStopDiff = GetStopDiff(lPreEndPrice);
			lLastPrice = lLastDiff = lKehaiPower = lKehaiPowerCount = lNari = 0L;

			top = n * 94;
			bottom = top + 94;
			base = top + 94 / 2;

			CRgn Rgn;
			Rgn.CreateRectRgn(0, top, m_w, bottom);
			m_MemoryDC.SelectClipRgn(&Rgn);

			if (jmax >= 0) {
				FunashiLast = GetFunashi(plFunashi, jmax);
//				lLastPrice = pDwaPlice->GetAt(jmax);
				const CKehai0& KehaiLast = FunashiLast.m_Kehai;
				lLastPrice = KehaiLast.m_plKehaiPrice[5] ? KehaiLast.m_plKehaiPrice[5] : FunashiLast.m_lPrice;
				lLastTradeCount = FunashiLast.m_lTradeCount;
//				lLastDiff = GetDiff(lLastPrice ? lLastPrice : KehaiLast.m_plKehaiPrice[5]);
				lLastDiff = GetDiff(lLastPrice);

				lMaxKehaiPrice = lMinKehaiPrice = 0L;
				for (j = 0; j < 5; j ++)
					if (lMaxKehaiPrice = KehaiLast.m_plKehaiPrice[j])
						break;
				for (j = 9; j >= 5; j --)
					if (lMinKehaiPrice = KehaiLast.m_plKehaiPrice[j])
						break;

				crKehaiPower = RGB(255, 255, 255);

				if (lMaxKehaiPrice && lMinKehaiPrice) {
					lKehaiPriceRange = __min(lMaxKehaiPrice - KehaiLast.m_plKehaiPrice[4], KehaiLast.m_plKehaiPrice[5] - lMinKehaiPrice);
					lSellKehaiPriceRange = KehaiLast.m_plKehaiPrice[4] + lKehaiPriceRange;
					lBuyKehaiPriceRange = KehaiLast.m_plKehaiPrice[5] - lKehaiPriceRange;
					lSumSellKehaiCount = lSumBuyKehaiCount = 0L;
					for (j = 0; j < 5; j ++)
						if (KehaiLast.m_plKehaiPrice[j] <= lSellKehaiPriceRange)
							lSumSellKehaiCount += labs(KehaiLast.m_plKehaiCount[j]);
					for (j = 5; j < 10; j ++)
						if (KehaiLast.m_plKehaiPrice[j] >= lBuyKehaiPriceRange)
							lSumBuyKehaiCount += labs(KehaiLast.m_plKehaiCount[j]);
					lKehaiPowerCount = lSumBuyKehaiCount - lSumSellKehaiCount;
					if (lKehaiPowerCount <= 0) {
						lKehaiPower = lSumSellKehaiCount == 0 ? 0 : (long)(64i64 * lKehaiPowerCount / lSumSellKehaiCount);
						crKehaiPower = RGB(255 + lKehaiPower, 255, 255 + lKehaiPower);
						m_MemoryDC.FillSolidRect(0, n * 94, m_w / 3, 94, crKehaiPower);
					} else {
						lKehaiPower = lSumBuyKehaiCount == 0 ? 0 : (long)(64i64 * lKehaiPowerCount / lSumBuyKehaiCount);
						crKehaiPower = RGB(255, 255 - lKehaiPower, 255 - lKehaiPower);
						m_MemoryDC.FillSolidRect(0, n * 94, m_w / 3, 94, crKehaiPower);
					}
					lKehaiPowerCount /= sUnit;
				}

				if (i) {
					switch (lLastDiff) {
					case 5L:
					case 50L:
					case 500L:
					case 5000L:
					case 50000L:
						l0 = lLastDiff * 2;
						break;
					default:
						l0 = lLastDiff;
					}

					m_MemoryDC.SetBkColor(crKehaiPower);

					for (l1 = lLastPrice; (ay0 = base - (l1 - lLastPrice) / lLastDiff * CHART_PRICEDOT) >= top; l1 += lLastDiff) {
						l2 = l1 % (l0 * 10);
						if (! l2) {
							m_MemoryDC.SelectObject(&m_Pen12);
							m_MemoryDC.MoveTo(0, ay0);
							m_MemoryDC.LineTo(m_w, ay0);
						} else if (l2 == l0 * 5) {
							m_MemoryDC.SelectObject(&m_Pen13);
							m_MemoryDC.MoveTo(0, ay0);
							m_MemoryDC.LineTo(m_w / 3, ay0);
						}
					}
					for (l1 = lLastPrice; (ay0 = base - (l1 - lLastPrice) / lLastDiff * CHART_PRICEDOT) < bottom; l1 -= lLastDiff) {
						l2 = l1 % (l0 * 10);
						if (! l2) {
							m_MemoryDC.SelectObject(&m_Pen12);
							m_MemoryDC.MoveTo(0, ay0);
							m_MemoryDC.LineTo(m_w, ay0);
						} else if (l2 == l0 * 5) {
							m_MemoryDC.SelectObject(&m_Pen13);
							m_MemoryDC.MoveTo(0, ay0);
							m_MemoryDC.LineTo(m_w / 3, ay0);
						}
					}

					m_MemoryDC.SetBkColor(RGB(255, 255, 255));

					for (l1 = lLastPrice; (ay0 = base - (l1 - lLastPrice) / lLastDiff * CHART_PRICEDOT) >= top; l1 += lLastDiff) {
						l2 = l1 % (l0 * 10);
						if (l2 == l0 * 5) {
							m_MemoryDC.SelectObject(&m_Pen13);
							m_MemoryDC.MoveTo(m_w / 3, ay0);
							m_MemoryDC.LineTo(m_w, ay0);
						}
					}
					for (l1 = lLastPrice; (ay0 = base - (l1 - lLastPrice) / lLastDiff * CHART_PRICEDOT) < bottom; l1 -= lLastDiff) {
						l2 = l1 % (l0 * 10);
						if (l2 == l0 * 5) {
							m_MemoryDC.SelectObject(&m_Pen13);
							m_MemoryDC.MoveTo(m_w / 3, ay0);
							m_MemoryDC.LineTo(m_w, ay0);
						}
					}

					if ((ay0 = base - (lStartPrice - lLastPrice) / lLastDiff * CHART_PRICEDOT) >= top  &&  ay0 < bottom) {
						m_MemoryDC.SelectObject(&m_Pen11);
						m_MemoryDC.MoveTo(0, ay0);
						m_MemoryDC.LineTo(m_w, ay0);
					}

					if (lPreEndPrice == lStartPrice) {
						m_Pen11.GetLogPen(&LogPen);
						m_MemoryDC.SetBkColor(LogPen.lopnColor);
					} else
						m_MemoryDC.SetBkColor(crKehaiPower);

					if ((ay0 = base - (lPreEndPrice - lLastPrice) / lLastDiff * CHART_PRICEDOT) >= top  &&  ay0 < bottom) {
						m_MemoryDC.SelectObject(&m_Pen10);
						m_MemoryDC.MoveTo(0, ay0);
						m_MemoryDC.LineTo(m_w / 3, ay0);
					}

					if (lPreEndPrice != lStartPrice)
						m_MemoryDC.SetBkColor(RGB(255, 255, 255));

					if ((ay0 = base - (lPreEndPrice - lLastPrice) / lLastDiff * CHART_PRICEDOT) >= top  &&  ay0 < bottom) {
						m_MemoryDC.SelectObject(&m_Pen10);
						m_MemoryDC.MoveTo(m_w / 3, ay0);
						m_MemoryDC.LineTo(m_w, ay0);
					}

					if ((ay0 = base - ((lPreEndPrice + lStopDiff) - lLastPrice) / lLastDiff * CHART_PRICEDOT) >= top  &&  ay0 < bottom) {
						m_MemoryDC.SelectObject(&m_Pen9);
						m_MemoryDC.MoveTo(0, ay0);
						m_MemoryDC.LineTo(m_w, ay0);
					}
					if ((ay0 = base - ((lPreEndPrice - lStopDiff) - lLastPrice) / lLastDiff * CHART_PRICEDOT) < bottom  &&  ay0 >= top) {
						m_MemoryDC.SelectObject(&m_Pen9);
						m_MemoryDC.MoveTo(0, ay0);
						m_MemoryDC.LineTo(m_w, ay0);
					}
				} else {
					l0 = 10L;
					for (l1 = lLastPrice; (ay0 = base - (l1 - lLastPrice) / lLastDiff * CHART_PRICEDOT) >= top; l1 += lLastDiff) {
						l2 = l1 % (l0 * 10);
						if (! l2) {
							m_MemoryDC.SelectObject(&m_Pen12);
							m_MemoryDC.MoveTo(0, ay0);
							m_MemoryDC.LineTo(m_w, ay0);
						} else if (l2 == l0 * 5) {
							m_MemoryDC.SelectObject(&m_Pen13);
							m_MemoryDC.MoveTo(0, ay0);
							m_MemoryDC.LineTo(m_w, ay0);
						}
					}
					for (l1 = lLastPrice; (ay0 = base - (l1 - lLastPrice) / lLastDiff * CHART_PRICEDOT) < bottom; l1 -= lLastDiff) {
						l2 = l1 % (l0 * 10);
						if (! l2) {
							m_MemoryDC.SelectObject(&m_Pen12);
							m_MemoryDC.MoveTo(0, ay0);
							m_MemoryDC.LineTo(m_w, ay0);
						} else if (l2 == l0 * 5) {
							m_MemoryDC.SelectObject(&m_Pen13);
							m_MemoryDC.MoveTo(0, ay0);
							m_MemoryDC.LineTo(m_w, ay0);
						}
					}
				}

				Dt = GetFunashi(i, 0).m_DtDateTime;
//				k = ((int)(Dt - DtStartMinute0).GetTotalSeconds() - (Dt < Dt1205 ? 0 : 64 * 60)) / TIMEUNIT * fTimeUnit;
				if (Dt < DtStartMinute0)
//					k = ((int)(Dt - Dt0800).GetTotalSeconds() - (Dt < Dt1205 ? 0 : 64 * 60)) / TIMEUNIT * fTimeUnit;
					k = ((int)(Dt - Dt0800).GetTotalSeconds() - (Dt < Dt1205 ? 0 : 34 * 60)) / TIMEUNIT * fTimeUnit;
				else {
					if (DtStartMinute0 < Dt0800)
						k = (float)(m_w / 3);
					else
						k = ((int)(DtStartMinute0 - Dt0800).GetTotalSeconds() - nSkip0Minutes) / TIMEUNIT * fTimeUnit;
					if (Dt < DtStartMinute1)
						k += (int)(Dt - DtStartMinute0).GetTotalSeconds() / TIMEUNIT * 0.2f;
					else {
						k += (int)(DtStartMinute1 - DtStartMinute0).GetTotalSeconds() / TIMEUNIT * 0.2f;
						k += (int)(Dt - DtStartMinute1).GetTotalSeconds() / TIMEUNIT * 1.0f;
					}
				}
//				tradecountmul = 1.0 / ((double)(lLastTradeCount / sUnit) / nTotalMinutes);
//				ax0 = bx0 = cx0 = ex0 = fx0 = gx0 = -1;
				ax0 = bx0 = cx0 = gx0 = -1;
//				ay0 = by0 = cy0 = ey0 = fy0 = gy0 = base;
				ay0 = by0 = cy0 = gy0 = base;
				b0900 = b1230 = FALSE;
				for (j = 0, jmax ++; j < jmax; j ++) {
					FunashiWork0 = GetFunashi(plFunashi, j);
					Dt = FunashiWork0.m_DtDateTime;
					DtDateTime = j < jmax - 1 ? GetFunashi(plFunashi, j + 1).m_DtDateTime : FixDateTime(Dt + COleDateTimeSpan(0, 0, 0, TIMEUNIT));

					lPrice = FunashiWork0.m_lPrice;
					dVwap0 = FunashiWork0.m_dVwap;
					const CKehai0& Kehai0 = FunashiWork0.m_Kehai;

					lDiff = GetDiff(lPrice ? lPrice : Kehai0.m_plKehaiPrice[5]);

/*
					if (Kehai0.m_plKehaiPrice[4] > max)
						max = Kehai0.m_plKehaiPrice[4];
					if (Kehai0.m_plKehaiPrice[5]  &&  Kehai0.m_plKehaiPrice[5] < min)
						min = Kehai0.m_plKehaiPrice[5];
*/

					if (i) {
						bValueOK = FALSE;
						if (j >= 8)
/*
							if (strSijo == "JQ") {
								for (l = 1; l <= 4; l ++)
									if (memcmp(&FunashiWork0.m_Kehai, &GetFunashi(plFunashi, j - l).m_Kehai, sizeof(CKehai0)))
										break;
								nPreJ = j - (l == 5 ? 1 : l);
								KehaiWork0 = GetFunashi(plFunashi, nPreJ).m_Kehai;
								for (l = 1; l <= 4; l ++)
									if (memcmp(&KehaiWork0, &GetFunashi(plFunashi, nPreJ - l).m_Kehai, sizeof(CKehai0)))
										break;
								nPreJ2 = nPreJ - (l == 5 ? 1 : l);
								KehaiWork1 = GetFunashi(plFunashi, nPreJ2).m_Kehai;
								if (
									KehaiWork0.m_plKehaiPrice[4] >= KehaiWork1.m_plKehaiPrice[4] + GetDiff(KehaiWork1.m_plKehaiPrice[4] + 1L) * 2
									&&  KehaiWork1.m_plKehaiPrice[3] == KehaiWork1.m_plKehaiPrice[4] + GetDiff(KehaiWork1.m_plKehaiPrice[4] + 1L)
									||  KehaiWork0.m_plKehaiPrice[5] <= KehaiWork1.m_plKehaiPrice[5] - GetDiff(KehaiWork1.m_plKehaiPrice[5]) * 2
									&&  KehaiWork1.m_plKehaiPrice[6] == KehaiWork1.m_plKehaiPrice[5] - GetDiff(KehaiWork1.m_plKehaiPrice[5])
								)
									nPreJ = nPreJ2;
							} else
*/
								nPreJ = j - 1;
						else
							nPreJ = 0;
						KehaiWork0 = GetFunashi(plFunashi, nPreJ).m_Kehai;
						if (j >= 8) {
							FunashiWork1 = GetFunashi(plFunashi, j - 1);
							lTradeCount0 = FunashiWork0.m_lTradeCount;
							lTradeCount1 = FunashiWork1.m_lTradeCount;
							lTradeCount01 = lTradeCount0 - lTradeCount1;
							dVwap1 = FunashiWork1.m_dVwap;
							if (
								KehaiWork0.m_plKehaiPrice[4]
								&&  KehaiWork0.m_plKehaiPrice[5]
								&&  dVwap1 > 0.0
								&&  dVwap0 > 0.0
								&&  lTradeCount1
								&&  lTradeCount0
								&&  KehaiWork0.m_plKehaiPrice[4] != KehaiWork0.m_plKehaiPrice[5]
							) {
//									l1 = lTradeCount01 / sUnit;
								l1 = lTradeCount01 * GetDiff(lLastPrice) / 1000;
								d1 = ((dVwap0 * lTradeCount0 - dVwap1 * lTradeCount1) / lTradeCount01 - (double)(KehaiWork0.m_plKehaiPrice[4] + KehaiWork0.m_plKehaiPrice[5]) / 2) / lDiff;
								if (l1)
									TRACE("a\n");
								if (d1 <= -0.5)
									lNari -= l1;
								else if (d1 >= 0.5)
									lNari += l1;
								else
									lNari += (long)(l1 * (d1 * 2.0));
								bValueOK = TRUE;
							}
						}
					}

					tradecountcalc = FALSE;
					while (Dt < DtDateTime) {
/*
						if (max) {
							ex1 = (long)k;
							ey1 = base - (max - lLastPrice) / lDiff * CHART_PRICEDOT;
							if (ex0 == -1)
								ex0 = ex1;
							m_MemoryDC.SelectObject(&m_Pen5);
							m_MemoryDC.MoveTo(ex0, ey0);
							m_MemoryDC.LineTo(ex1, ey1);
							ex0 = ex1;
							ey0 = ey1;
						}

						if (min < INT_MAX) {
							fx1 = (long)k;
							fy1 = base - (min - lLastPrice) / lDiff * CHART_PRICEDOT;
							if (fx0 == -1)
								fx0 = fx1;
							m_MemoryDC.SelectObject(&m_Pen6);
							m_MemoryDC.MoveTo(fx0, fy0);
							m_MemoryDC.LineTo(fx1, fy1);
							fx0 = fx1;
							fy0 = fy1;
						}
*/

						if (i) {
							if (Dt >= DtStartMinute1) {
//								d0 = d1 = d2 = d3 = 0.0;
								d0 = d1 = 0.0;
								if (! tradecountcalc) {
									if (bValueOK) {
										d0 = ((dVwap0 * lTradeCount0 - dVwap1 * lTradeCount1) - KehaiWork0.m_plKehaiPrice[5] * (double)lTradeCount01) / (KehaiWork0.m_plKehaiPrice[4] - KehaiWork0.m_plKehaiPrice[5]);
										d0 = (d0 + sUnit / 2) / sUnit;
										lTradeCount01 /= sUnit;
										if (d0 < 0.0)
											d0 = 0.0;
										else if (d0 > lTradeCount01)
											d0 = lTradeCount01;
										d1 = lTradeCount01 - d0;
/*
										if (Kehai0.m_plKehaiPrice[4]) {
											m = -1;
											for (l = 0; l < 5; l ++)
												if (KehaiWork0.m_plKehaiPrice[l] == Kehai0.m_plKehaiPrice[4]) {
													m = l;
													break;
												}
											d2 = (double)labs(Kehai0.m_plKehaiCount[4]);
											if (m != -1)
												d2 -= (double)labs(KehaiWork0.m_plKehaiCount[m]);
											switch (m) {
											case 4:
												d2 += d0;
												break;
											case 5:
												d2 += d1;
											}
											d2 /= sUnit;
										}
										if (Kehai0.m_plKehaiPrice[5]) {
											m = -1;
											for (l = 5; l < 10; l ++)
												if (KehaiWork0.m_plKehaiPrice[l] == Kehai0.m_plKehaiPrice[5]) {
													m = l;
													break;
												}
											d3 = (double)labs(Kehai0.m_plKehaiCount[5]);
											if (m != -1)
												d3 -= (double)labs(KehaiWork0.m_plKehaiCount[m]);
											switch (m) {
											case 4:
												d3 += d0;
												break;
											case 5:
												d3 += d1;	
											}
											d3 /= sUnit;
										}
										d0 /= sUnit;
										d1 /= sUnit;
*/
									}
//									d4 = d0 - d2;
//									d5 = d1 - d3;
//									d6 = d4 - d5;
//									d6 = d0 - d1;

/*
									if (j) {
										lTradeCount = lTradeCount0;
										lPreTradeCount = lTradeCount1;
										d6 = lTradeCount && lPreTradeCount ? lTradeCount - lPreTradeCount : 0.0;
									} else
										d6 = 0.0;
*/

									kehaicount = 0L;
									for (l = 0; l < 10; l ++)
										kehaicount += Kehai0.m_plKehaiCount[l];

									tradecountmul = 94 / 4 / ((double)(kehaicount / sUnit) / 10);
									tradecountcalc = TRUE;
								}

								dx1 = (long)k;
								m_MemoryDC.SelectObject(&m_Pen3);

								dy1 = base - (long)(d0 * tradecountmul);
								m_MemoryDC.MoveTo(dx1, base);
								m_MemoryDC.LineTo(dx1, dy1);

								dy1 = base - (long)(- d1 * tradecountmul);
								m_MemoryDC.MoveTo(dx1, base);
								m_MemoryDC.LineTo(dx1, dy1);
							}

							cx1 = (long)k;
							if (cx0 == -1)
								cx0 = cx1;
							if (dVwap0 > 0.0) {
								cy1 = base - (long)((dVwap0 - lLastPrice) / lDiff * CHART_PRICEDOT);
								if (cx1 != cx0  ||  cy1 != cy0) {
									m_MemoryDC.SelectObject(&m_Pen2);
									m_MemoryDC.MoveTo(cx0, cy0);
									m_MemoryDC.LineTo(cx1, cy1);
								}
								cy0 = cy1;
							}
							cx0 = cx1;
						}

						if (Dt >= Dt0900) {
							gx1 = (long)k;
							if (gx0 == -1)
								gx0 = gx1;
							if (lPrice) {
								gy1 = base - (lPrice - lLastPrice) / lDiff * CHART_PRICEDOT;
								if (gx1 != gx0  ||  gy1 != gy0) {
									m_MemoryDC.SelectObject(&m_Pen14);
									m_MemoryDC.MoveTo(gx0, gy0);
									m_MemoryDC.LineTo(gx1, gy1);
								}
								gy0 = gy1;
							}
							gx0 = gx1;
						}

						if (Dt >= DtStartMinute0) {
							ax1 = (long)k;
							if (ax0 == -1)
								ax0 = ax1;
							if (Kehai0.m_plKehaiPrice[4]) {
								ay1 = base - (Kehai0.m_plKehaiPrice[4] - lLastPrice) / lDiff * CHART_PRICEDOT;
								if ((ax1 != ax0  ||  ay1 != ay0)  &&  Dt > DtStartMinute0) {
									m_MemoryDC.SelectObject(&m_Pen0);
									m_MemoryDC.MoveTo(ax0, ay0);
									m_MemoryDC.LineTo(ax1, ay1);
								}
								ay0 = ay1;
							}
							ax0 = ax1;
						}

						bx1 = (long)k;
						if (bx0 == -1)
							bx0 = bx1;
//						if (Kehai0.m_plKehaiPrice[5] || lPrice) {
						if (Kehai0.m_plKehaiPrice[5]) {
//							by1 = base - ((Kehai0.m_plKehaiPrice[5] ? Kehai0.m_plKehaiPrice[5] : lPrice) - lLastPrice) / lDiff * CHART_PRICEDOT;
							by1 = base - (Kehai0.m_plKehaiPrice[5] - lLastPrice) / lDiff * CHART_PRICEDOT;
							if (bx1 != bx0  ||  by1 != by0) {
								m_MemoryDC.SelectObject(&m_Pen1);
								if (Dt < Dt0900 || Dt >= Dt1205 && Dt < Dt1230 || Dt >= DtStartMinute0) {
									m_MemoryDC.MoveTo(bx0, by0);
									m_MemoryDC.LineTo(bx1, by1);
								} else
									m_MemoryDC.MoveTo(bx1, by1);
							}
							by0 = by1;
						}
						bx0 = bx1;

						DtNew = FixDateTime(Dt + COleDateTimeSpan(0, 0, 0, TIMEUNIT));
						if (DtNew > Dt1059  &&  DtNew <= Dt1130) {
							DtNew = Dt1205;
							m_MemoryDC.SelectObject(&m_Pen4);
							m_MemoryDC.MoveTo(bx0 + 1, n * 94);
							m_MemoryDC.LineTo(bx0 + 1, (n + 1) * 94);
						} else if (DtNew > Dt1459  &&  DtNew < Dt1530)
							DtNew = Dt1530;

						if (! b0900  &&  DtNew >= Dt0900) {
							m_MemoryDC.SelectObject(&m_Pen8);
							m_MemoryDC.MoveTo(bx0 + 1, n * 94);
							m_MemoryDC.LineTo(bx0 + 1, (n + 1) * 94);
							b0900 = TRUE;
						}

						if (! b1230  &&  DtNew >= Dt1230) {
							m_MemoryDC.SelectObject(&m_Pen8);
							m_MemoryDC.MoveTo(bx0 + 1, n * 94);
							m_MemoryDC.LineTo(bx0 + 1, (n + 1) * 94);
							b1230 = TRUE;
						}

						if (DtNew == DtStartMinute0  ||  DtNew == DtStartMinute1) {
							m_MemoryDC.SelectObject(&m_Pen12);
							m_MemoryDC.MoveTo(bx0 + 1, n * 94);
							m_MemoryDC.LineTo(bx0 + 1, (n + 1) * 94);
						}

						if (Dt < DtStartMinute0  &&  DtNew >= DtStartMinute0  ||  Dt < DtStartMinute1  &&  DtNew >= DtStartMinute1) {
							if (DtNew < DtStartMinute0)
//								k = ((int)(DtNew - Dt0800).GetTotalSeconds() - 64 * 60) / TIMEUNIT * fTimeUnit - fTimeUnit;
								k = ((int)(DtNew - Dt0800).GetTotalSeconds() - 34 * 60) / TIMEUNIT * fTimeUnit - fTimeUnit;
							else {
								if (DtStartMinute0 < Dt0800)
									k = (float)(m_w / 3);
								else
									k = ((int)(DtStartMinute0 - Dt0800).GetTotalSeconds() - nSkip0Minutes) / TIMEUNIT * fTimeUnit;
								if (DtNew < DtStartMinute1)
									k += (int)(DtNew - DtStartMinute0).GetTotalSeconds() / TIMEUNIT * 0.2f - 0.2f;
								else {
									k += (int)(DtStartMinute1 - DtStartMinute0).GetTotalSeconds() / TIMEUNIT * 0.2f;
									k += (int)(DtNew - DtStartMinute1).GetTotalSeconds() / TIMEUNIT * 1.0f - 1.0f;
								}
							}
						}
						Dt = DtNew;

						if (Dt >= DtStartMinute1)
							k += 1.0f;
						else if (Dt >= DtStartMinute0)
							k += 0.2f;
						else
							k += fTimeUnit;
					}
				}
			}

			m_MemoryDC.SetBkColor(RGB(255, 255, 255));
			if (i) {
				strName.Empty();
				lMaxTradeCount = 0L;
				strDispCode.Empty();
				CodeToName(strCode, strName, NULL, NULL, NULL, NULL, NULL, &lMaxTradeCount, &strDispCode);
				if (strDispCode.IsEmpty()) {
					CodeToName(strCode, strName);
					strDispCode = strCode;
				}
				m_MemoryDC.SetTextAlign(TA_UPDATECP);
				crDefaultTextColor = m_MemoryDC.GetTextColor();
				m_MemoryDC.MoveTo(0, n * 94);
				m_MemoryDC.SetTextColor(RGB(0, 0, 0));
				m_MemoryDC.TextOut(0, 0, StrFormat("%s %s", strDispCode, StrConvHalfWidth(strName).Left(20)));
				m_MemoryDC.SetTextColor(RGB(255, 0, 255));
				m_MemoryDC.TextOut(0, 0, StrFormat(" %ld", lPreEndPrice + lStopDiff));
				m_MemoryDC.SetTextColor(RGB(0, 0, 0));
				m_MemoryDC.TextOut(0, 0, "/");
				m_MemoryDC.SetTextColor(RGB(0, 0, 255));
				m_MemoryDC.TextOut(0, 0, StrFormat("%ld", lLastPrice));
				m_MemoryDC.SetTextColor(RGB(0, 0, 0));
				m_MemoryDC.TextOut(0, 0, "/");
				m_MemoryDC.SetTextColor(RGB(255, 0, 255));
				m_MemoryDC.TextOut(0, 0, StrFormat("%ld", lPreEndPrice - lStopDiff));
				m_MemoryDC.MoveTo(0, n * 94 + m_Metrics.tmHeight);
				m_MemoryDC.SetTextColor(RGB(0, 0, 0));
				m_MemoryDC.TextOut(0, 0, StrFormat(" %ld", lKehaiPower));
//				m_MemoryDC.SetTextColor(RGB(0, 0, 255));
//				m_MemoryDC.TextOut(0, 0, StrFormat(" %ld", m_DwaHiashiPriceAve25[i]));
//				m_MemoryDC.SetTextColor(RGB(0, 0, 0));
//				m_MemoryDC.TextOut(0, 0, "/");
				m_MemoryDC.SetTextColor(RGB(255, 0, 255));
				m_MemoryDC.TextOut(0, 0, StrFormat(" %ld", m_DwaHiashiPreEndPrice[i]));
				m_MemoryDC.SetTextColor(RGB(0, 0, 0));
				m_MemoryDC.TextOut(0, 0, "/");
				m_MemoryDC.SetTextColor(RGB(127, 127, 0));
				m_MemoryDC.TextOut(0, 0, StrFormat("%ld", lStartPrice));
				m_MemoryDC.SetTextColor(RGB(255, 0, 255));
				m_MemoryDC.TextOut(0, 0, StrFormat(" %ld", lMaxTradeCount * GetDiff(lPreEndPrice) / 1000));
				m_MemoryDC.SetTextColor(RGB(0, 0, 0));
				m_MemoryDC.TextOut(0, 0, "/");
				m_MemoryDC.SetTextColor(RGB(0, 0, 255));
				m_MemoryDC.TextOut(0, 0, StrFormat("%ld", lLastTradeCount * lLastDiff / 1000));
				m_MemoryDC.SetTextColor(RGB(0, 0, 0));
				m_MemoryDC.TextOut(0, 0, "/");
				m_MemoryDC.SetTextColor(RGB(255, 0, 0));
				m_MemoryDC.TextOut(0, 0, StrFormat("%ld", lNari));
				m_MemoryDC.SetTextColor(RGB(0, 0, 0));
				m_MemoryDC.TextOut(0, 0, StrFormat(" %ld", lLastPrice ? (lPreEndPrice + lStopDiff - lLastPrice) / lLastDiff  : 0));
				m_MemoryDC.SetTextColor(RGB(0, 0, 255));
				m_MemoryDC.TextOut(0, 0, StrFormat(" %ld", lLastPrice ? (lLastPrice - lPreEndPrice) * 100 / lStopDiff : 0));
				m_MemoryDC.MoveTo(0, n * 94 + m_Metrics.tmHeight * 2);
				if (m_MstpNewsCode.Lookup(strCode, pVoid)) {
					m_MemoryDC.SetTextColor(RGB(255, 0, 0));
					m_MemoryDC.TextOut(0, 0, "★");
				} else if (m_MstpNewsCode2.Lookup(strCode, pVoid)) {
					m_MemoryDC.SetTextColor(RGB(255, 0, 0));
					m_MemoryDC.TextOut(0, 0, "☆");
				}
				if (m_nPage) {
					m_MemoryDC.SetTextColor(RGB(255, 0, 255));
					m_MemoryDC.TextOut(0, 0, (m_DwaSelBuy[nIndex] ? StrFormat(" ● %ld", m_DwaSelBuy[nIndex]) : pszEmpty));
				} else {
					m_MemoryDC.SetTextColor(RGB(255, 0, 255));
					m_MemoryDC.TextOut(0, 0, (m_DwaNiceBuy[nIndex] ? StrFormat(" ● %ld", m_DwaNiceBuy[nIndex]) : pszEmpty));
					m_MemoryDC.SetTextColor(RGB(255, 0, 0));
					m_MemoryDC.TextOut(0, 0, (m_DwaNiceLockOn[nIndex] ? StrFormat(" ◆ %ld", m_DwaNiceLockOn[nIndex]) : pszEmpty));
				}
				m_MemoryDC.SetTextColor(crDefaultTextColor);
				m_MemoryDC.SetTextAlign(TA_NOUPDATECP);
			} else {
				m_MemoryDC.TextOut(0, n * 94, StrFormat("%s %s %ld", strCode, StrConvHalfWidth(m_SaHiashiName[i]).Left(20), lLastPrice));
				m_MemoryDC.TextOut(0, n * 94 + m_Metrics.tmHeight, StrFormat("%ld", lKehaiPower));
			}

			m_MemoryDC.SelectClipRgn(NULL);
		}
	}
	strText = StrFormat("%d/%d", m_nPage, 1 + m_SaSelCode.GetUpperBound() / 10);
	Size = m_MemoryDC.GetOutputTabbedTextExtent(strText, 0, NULL);
	m_MemoryDC.TextOut(m_w - Size.cx, 0, strText);

	CDC* pDC = GetDC();
	pDC->BitBlt(m_x0, m_y0, m_w, m_h, &m_MemoryDC, 0, 0, SRCCOPY);
	ReleaseDC(pDC);
}

void CChartViewerDlg::DispErrorLog(LPCTSTR lpszFormat, ...)
{
	CStringBuffer sb;

	va_list vl;
	va_start(vl, lpszFormat);
	sb.FormatV(lpszFormat, vl);
	va_end(vl);

	sb = COleDateTime::GetCurrentTime().Format("%H:%M:%S ") + sb;

	MessageBox(sb);
}

int CChartViewerDlg::CodeToName(CString& strCode, CString& strName, CString* pstrSijoName, short* psUnit, long* plHighPrice, long* plLowPrice, long* plPreEndPrice, long* plTradeCount, CString* pstrCodeEx) 
{
	int nRv = -1;

	if (strCode.GetLength() < 4) {
		strName.Empty();
		if (pstrSijoName)
			pstrSijoName->Empty();
		if (psUnit)
			*psUnit = 1;
		if (plHighPrice)
			*plHighPrice = 0L;
		if (plLowPrice)
			*plLowPrice = 0L;
		if (plPreEndPrice)
			*plPreEndPrice = 0L;
		if (plTradeCount)
			*plTradeCount = 0L;
		if (pstrCodeEx)
			pstrCodeEx->Empty();
		return nRv;
	}

	MainCodeName MainCodeName;
	if (m_MstmCodeMainCodeName.Lookup(strCode, MainCodeName) && (pstrSijoName == NULL  ||  MainCodeName.strSijoName.GetLength()) && (psUnit == NULL  ||  MainCodeName.sUnit) && (plHighPrice == NULL  ||  MainCodeName.lHighPrice) && (plLowPrice == NULL  ||  MainCodeName.lLowPrice) && (plPreEndPrice == NULL  ||  MainCodeName.lPreEndPrice) && (plTradeCount == NULL  ||  MainCodeName.lTradeCount) && (pstrCodeEx == NULL  ||  MainCodeName.strMainCodeEx.GetLength()  &&  MainCodeName.nNewsCount == m_MstpNewsCode.GetCount())) {
		strCode = MainCodeName.strMainCode;
		strName = MainCodeName.strName;
		if (pstrSijoName)
			*pstrSijoName = MainCodeName.strSijoName;
		if (psUnit)
			*psUnit = MainCodeName.sUnit;
		if (plHighPrice)
			*plHighPrice = MainCodeName.lHighPrice;
		if (plLowPrice)
			*plLowPrice = MainCodeName.lLowPrice;
		if (plPreEndPrice)
			*plPreEndPrice = MainCodeName.lPreEndPrice;
		if (plTradeCount)
			*plTradeCount = MainCodeName.lTradeCount;
		if (pstrCodeEx)
			*pstrCodeEx = MainCodeName.strMainCodeEx;
		return 0;
	}

	CDaoDatabase Database;

	while (1) {
		try
		{
			Database.Open(m_strDBFPath, FALSE, TRUE);

			CDaoRecordset RsInfo(&Database);
			if (plHighPrice == NULL  &&  plLowPrice == NULL  &&  plPreEndPrice == NULL  &&  plTradeCount == NULL)
				RsInfo.Open(
					dbOpenSnapshot,
					StrFormat(
						"SELECT "
							FLD_IN_CODE ", "
							FLD_IN_NAME ", "
							FLD_IN_SIJO ", "
							FLD_IN_UNIT
						" FROM " TBL_INFO
						" WHERE "
							FLD_IN_CODE " Like '%s*'",
						strCode
					)
				);

			if (plHighPrice  ||  plLowPrice  ||  plPreEndPrice  ||  plTradeCount  ||  ! RsInfo.IsEOF()) {
				CDaoRecordset* pRsWork = &RsInfo;
				CDaoRecordset RsInHi(&Database);

				if (plHighPrice == NULL  &&  plLowPrice == NULL  &&  plPreEndPrice == NULL  &&  plTradeCount == NULL)
					RsInfo.MoveLast();
				if (plHighPrice  ||  plLowPrice  ||  plPreEndPrice  ||  plTradeCount  ||  RsInfo.GetRecordCount() >= 2) {
					RsInHi.Open(
						dbOpenSnapshot,
						StrFormat(
							"SELECT "
								TBL_INFO "." FLD_IN_CODE ", "
								TBL_INFO "." FLD_IN_NAME ", "
								TBL_INFO "." FLD_IN_SIJO ", "
								TBL_INFO "." FLD_IN_UNIT ", "
								TBL_HIASHI "." FLD_HI_DATE ", "
								TBL_HIASHI "." FLD_HI_STARTPRICE ", "
								TBL_HIASHI "." FLD_HI_HIGHPRICE ", "
								TBL_HIASHI "." FLD_HI_LOWPRICE ", "
								TBL_HIASHI "." FLD_HI_TRADECOUNT
							" FROM " TBL_INFO ", " TBL_HIASHI
							" WHERE "
								TBL_INFO "." FLD_IN_CODE " = " TBL_HIASHI "." FLD_HI_CODE
								" AND " TBL_HIASHI "." FLD_HI_DATE " >= #%s#"
								" AND " TBL_HIASHI "." FLD_HI_TRADECOUNT " > 0"
								" AND " TBL_INFO "." FLD_IN_CODE " Like '%s*'"
							" ORDER BY "
								TBL_HIASHI "." FLD_HI_DATE " DESC, "
								TBL_HIASHI "." FLD_HI_TRADECOUNT " DESC",
							(GetCurrentTimeEx() - COleDateTimeSpan(37, 0, 0, 0)).Format("%Y/%m/%d"), strCode
						),
						dbForwardOnly
					);
					if (RsInHi.IsEOF()) {
						if (plHighPrice == NULL  &&  plLowPrice == NULL  &&  plPreEndPrice == NULL  &&  plTradeCount == NULL)
							RsInfo.MoveFirst();
					} else
						pRsWork = &RsInHi;
				}

				if (plHighPrice == NULL  &&  plLowPrice == NULL  &&  plPreEndPrice == NULL  &&  plTradeCount == NULL  ||  pRsWork == &RsInHi) {
					COleVariant var;
					CString strMainCode;
					CString strSijoName;

					pRsWork->GetFieldValue(0, var);
					strMainCode = V_BSTRT((LPVARIANT)var);

					pRsWork->GetFieldValue(1, var);
					strName = V_BSTRT((LPVARIANT)var);

					if (pstrSijoName || pstrCodeEx) {
						pRsWork->GetFieldValue(2, var);
						strSijoName = V_BSTRT((LPVARIANT)var);

						if (pstrSijoName)
							*pstrSijoName = strSijoName;
					}

					if (psUnit) {
						pRsWork->GetFieldValue(3, var);
						*psUnit = var.iVal;
					}

					if ((plHighPrice || plLowPrice || plPreEndPrice || plTradeCount)  &&  pRsWork == &RsInHi) {
						COleDateTime DtDate;
						long lStartPrice;
						long lHighPrice;
						long lLowPrice;
						long lPreEndPrice;
						long lTradeCount = 0;
						COleVariant pKeyArray[2];

						do {
							pRsWork->GetFieldValue(8, var);
							if (var.lVal > lTradeCount) {
								lTradeCount = var.lVal;

								pRsWork->GetFieldValue(4, var);
								DtDate = var.date;

								pRsWork->GetFieldValue(5, var);
								lStartPrice = var.lVal;

								pRsWork->GetFieldValue(6, var);
								lHighPrice = var.lVal;

								pRsWork->GetFieldValue(7, var);
								lLowPrice = var.lVal;
							}
							pRsWork->MoveNext();
						} while (! pRsWork->IsEOF());

						CDaoRecordset RsHiashi(&Database);
						RsHiashi.Open(dbOpenTable, TBL_HIASHI);
						RsHiashi.SetCurrentIndex(pszPrimaryKey);

						pKeyArray[0] = COleVariant(DtDate - COleDateTimeSpan(1, 0, 0, 0));
						pKeyArray[1] = COleVariant(strMainCode, VT_BSTRT);
						if (RsHiashi.Seek("=", pKeyArray, 2)) {
							RsHiashi.GetFieldValue(5, var);
							lPreEndPrice = var.lVal;
						} else
							lPreEndPrice = lStartPrice;

						*plTradeCount = lTradeCount;
						if (plHighPrice)
							*plHighPrice = lHighPrice;
						if (plLowPrice)
							*plLowPrice = lLowPrice;
						if (plPreEndPrice)
							*plPreEndPrice = lPreEndPrice;
					}

					if (pstrCodeEx) {
						void* pVoid;
						CString strSijo;

						*pstrCodeEx = strMainCode;
						if (m_MstpNewsCode.Lookup(strMainCode, pVoid))
							(*pstrCodeEx).SetAt(4, '*');
						else if (m_MstpNewsCode2.Lookup(strMainCode, pVoid))
							(*pstrCodeEx).SetAt(4, '+');
						strSijo = strMainCode.Mid(5);
						if (strSijo == "T") {
							if (strSijoName.Left(10) == "東証ﾏｻﾞｰｽﾞ")
								*pstrCodeEx += 'M';
							else if (strSijoName.Left(8) == "東証２部")
								*pstrCodeEx += '2';
						} else if (strSijo == "O")
							if (strSijoName.Left(8) == "大証２部")
								*pstrCodeEx += '2';
					}

					MainCodeName.strMainCode = strMainCode;
					MainCodeName.strName = strName;
					MainCodeName.strSijoName = pstrSijoName ? *pstrSijoName : pszEmpty;
					MainCodeName.sUnit = psUnit ? *psUnit : 0;
					MainCodeName.lHighPrice = plHighPrice ? *plHighPrice : 0;
					MainCodeName.lLowPrice = plLowPrice ? *plLowPrice : 0;
					MainCodeName.lPreEndPrice = plPreEndPrice ? *plPreEndPrice : 0;
					MainCodeName.lTradeCount = plTradeCount ? *plTradeCount : 0;
					MainCodeName.strMainCodeEx = pstrCodeEx ? *pstrCodeEx : pszEmpty;
					MainCodeName.nNewsCount = m_MstpNewsCode.GetCount();

					m_MstmCodeMainCodeName[strCode] = MainCodeName;

					strCode = strMainCode;

					nRv = 0;
				}
			}
		}
		catch (CDaoException* pEx) {
			if (
				pEx->m_scode == E_DAO_FileLockingUnavailable
				||  pEx->m_scode == E_DAO_TooManyActiveUsers
				||  pEx->m_scode == DBDAOERR(3734)
			) {
				Sleep(100);
				continue;
			}
			DispErrorLog("DAO 銘柄名取得エラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();
		}
		catch (CException* pEx) {
			DispErrorLog("銘柄名取得エラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();
		}

		break;
	}

	return nRv;
}

void CChartViewerDlg::User1() 
{
	DispChart();
}

void CChartViewerDlg::User2() 
{
	int i;
	int imax;
	CStringBuffer sbI;
	char pszBuf[MAX_PATH];
	CStringArray SaHiashiCode;

	m_SaNiceCode.RemoveAll();
	m_DwaNiceLockOn.RemoveAll();
	m_DwaNiceBuy.RemoveAll();
	m_SaSelCode.RemoveAll();
	m_DwaSelBuy.RemoveAll();
	m_MstpSelCode.RemoveAll();

	m_SaNiceCode.Add("101");
	m_DwaNiceLockOn.Add(0L);
	m_DwaNiceBuy.Add(0L);
	for (i = 0; ; i ++) {
		sbI = IToA(i);
		if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_CODE + sbI, pszX, pszBuf, MAX_PATH, m_strMeigaraIniFPath) == 1)
			break;
		else
			m_SaNiceCode.Add(pszBuf);
		if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_LOCKON + sbI, pszEmpty, pszBuf, MAX_PATH, m_strMeigaraIniFPath))
			m_DwaNiceLockOn.Add(atol(pszBuf));
		m_DwaNiceBuy.Add(0L);
	}
	for (i = 0; ; i ++) {
		if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_SELCODE + IToA(i), pszEmpty, pszBuf, MAX_PATH, m_strMeigaraIniFPath)) {
			m_SaSelCode.Add(pszBuf);
			m_MstpSelCode[pszBuf] = NULL;
		} else
			break;
		m_DwaSelBuy.Add(0L);
	}
	for (i = 0; ; i ++)
		if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_HIASHICODE + IToA(i), pszEmpty, pszBuf, MAX_PATH, m_strMeigaraIniFPath))
			SaHiashiCode.Add(pszBuf);
		else
			break;

	HiashiAnalyze();
	for (i = 0, imax = SaHiashiCode.GetSize(); i < imax; i ++)
		HiashiAnalyze(SaHiashiCode[i]);

	KillWMUserTimer(2);
	SetWMUserTimer(0, 2, NULL);
}

void CChartViewerDlg::User3() 
{
	int i;
	char pszBuf[MAX_PATH];

	m_DwaNiceLockOn.RemoveAll();

	m_DwaNiceLockOn.Add(FALSE);
	for (i = 0; ; i ++)
		if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_LOCKON + IToA(i), pszEmpty, pszBuf, MAX_PATH, m_strMeigaraIniFPath))
			m_DwaNiceLockOn.Add(atol(pszBuf));
		else
			break;

	KillWMUserTimer(2);
	SetWMUserTimer(0, 2, NULL);
}

void CChartViewerDlg::User4(LPARAM lParam) 
{
	WPARAM wParam = m_DwaParamUser4[0];
	m_DwaParamUser4.RemoveAt(0);

	int i;
	int imax;
	CString strStk = IToA(wParam);
	BOOL bFound = FALSE;

	for (i = 1, imax = m_SaNiceCode.GetSize(); i < imax; i ++)
		if (m_SaNiceCode[i].Left(4) == strStk) {
			m_nPage = 0;
			m_DwaNiceBuy[i] = lParam;
			bFound = TRUE;
			break;
		}
	if (! bFound)
		for (i = 1, imax = m_SaSelCode.GetSize(); i < imax; i ++)
			if (m_SaSelCode[i].Left(4) == strStk) {
				m_nPage = 1 + i / 10;
				m_DwaSelBuy[i] = lParam;
				break;
			}

	KillWMUserTimer(2);
	SetWMUserTimer(0, 2, NULL);
}

void CChartViewerDlg::User5(WPARAM wParam) 
{
	m_nPage = wParam;
	KillWMUserTimer(2);
	SetWMUserTimer(0, 2, NULL);
}

void CChartViewerDlg::User6(WPARAM wParam) 
{
	switch (wParam) {
	case 0:
		if (-- m_nPage < 0)
			m_nPage = 1 + m_SaSelCode.GetUpperBound() / 10;
		break;
	case 1:
		m_nPage = 0;
		break;
	default:
		if (++ m_nPage > 1 + m_SaSelCode.GetUpperBound() / 10)
			m_nPage = 0;
	}
	KillWMUserTimer(2);
	SetWMUserTimer(0, 2, NULL);
}

void CChartViewerDlg::User7() 
{
	int i;
	char pszBuf[MAX_PATH];

	m_MstpNewsCode.RemoveAll();
	m_MstpNewsCode2.RemoveAll();
	for (i = 0; ; i ++) {
		if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_NEWSCODE + IToA(i), pszEmpty, pszBuf, MAX_PATH, m_strNewsIniFPath))
			m_MstpNewsCode[pszBuf] = NULL;
		else
			break;
	}
	for (i = 0; ; i ++) {
		if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_NEWSCODE2 + IToA(i), pszEmpty, pszBuf, MAX_PATH, m_strNewsIniFPath))
			m_MstpNewsCode2[pszBuf] = NULL;
		else
			break;
	}
	KillWMUserTimer(2);
	SetWMUserTimer(0, 2, NULL);
}

void CChartViewerDlg::User8() 
{
	m_MstmCodeMainCodeName.RemoveAll();
	KillWMUserTimer(2);
	SetWMUserTimer(0, 2, NULL);
}

int CChartViewerDlg::CheckLicense()
{
	// 変数
	LPBYTE lpRegData;
	DWORD cbRegDataSize;
	BOOL bNeedRemit = FALSE;
	// レジストリオープン
	HKEY hKey;
	BOOL bRegOpen = FALSE;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, REG_SUBKEY_AUTOTRADER, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
		bRegOpen = TRUE;
	else
		bNeedRemit = TRUE;
	// 初回起動日取得
	DWORD dwIYear;
	DWORD dwIMon;
	DWORD dwIDay;
	CTime TIDate;
	BOOL bIDate = FALSE;
	if (bRegOpen) {
		cbRegDataSize = sizeof(dwIYear);
		if (RegQueryValueEx(hKey, REG_KEY_IYEAR, NULL, NULL, (LPBYTE)&dwIYear, &cbRegDataSize) == ERROR_SUCCESS) {
			cbRegDataSize = sizeof(dwIMon);
			if (RegQueryValueEx(hKey, REG_KEY_IMON, NULL, NULL, (LPBYTE)&dwIMon, &cbRegDataSize) == ERROR_SUCCESS) {
				cbRegDataSize = sizeof(dwIDay);
				if (RegQueryValueEx(hKey, REG_KEY_IDAY, NULL, NULL, (LPBYTE)&dwIDay, &cbRegDataSize) == ERROR_SUCCESS) {
					dwIYear = DecodeSecretDWord(dwIYear);
					dwIMon = DecodeSecretDWord(dwIMon);
					dwIDay = DecodeSecretDWord(dwIDay);
					TIDate = CTime::CTime(dwIYear, dwIMon, dwIDay, 0, 0, 0);
					bIDate = TRUE;
				}
			}
		}
	}
	// 最新インストールバージョン
	DWORD dwIVer;
	BOOL bIVer = FALSE;
	if (bIDate) {
		cbRegDataSize = sizeof(dwIVer);
		if (RegQueryValueEx(hKey, REG_KEY_IVER, NULL, NULL, (LPBYTE)&dwIVer, &cbRegDataSize) == ERROR_SUCCESS) {
			dwIVer = DecodeSecretDWord(dwIVer);
			bIVer = TRUE;
		}
	}
	// 登録メールアドレス取得
	CString strMailAddr;
	if (! bNeedRemit) {
		lpRegData = (LPBYTE)new _TCHAR[MADDR_BUFLEN];
		cbRegDataSize = MADDR_BUFLEN;
		if (RegQueryValueEx(hKey, REG_KEY_MADDR, NULL, NULL, lpRegData, &cbRegDataSize) == ERROR_SUCCESS)
			strMailAddr = lpRegData;
		else
			bNeedRemit = TRUE;
		delete [] lpRegData;
	}
	// ライセンスキー取得
	CString strLicenseKey;
	if (! bNeedRemit) {
		lpRegData = (LPBYTE)new _TCHAR[LKEY_BUFLEN];
		cbRegDataSize = LKEY_BUFLEN;
		if (RegQueryValueEx(hKey, REG_KEY_LKEY, NULL, NULL, lpRegData, &cbRegDataSize) == ERROR_SUCCESS)
			strLicenseKey = lpRegData;
		else
			bNeedRemit = TRUE;
		delete [] lpRegData;
	}
	// レジストリクローズ
	if (bRegOpen)
		RegCloseKey(hKey);
	if (! bNeedRemit) {
		// デコード
		strMailAddr = DecodeSecretString(strMailAddr);
		strLicenseKey = DecodeSecretString(strLicenseKey);
		// ライセンスチェック
		if (! CheckLicenseKey(SECRET_KEY, strMailAddr, strLicenseKey))
			bNeedRemit = TRUE;
		else {
			// ライセンス開始日チェック
			if (strMailAddr.GetLength() <= 8)
				bNeedRemit = TRUE;
			else {
				CString strDate = strMailAddr.Right(8);
				COleDateTime DtDate;
				if (DtDate.SetDate(atoi(strDate.Left(4)), atoi(strDate.Mid(4, 2)), atoi(strDate.Mid(6))))
					bNeedRemit = TRUE;
				else {
					COleDateTime DtCur = COleDateTime::GetCurrentTime();
					if (DtCur < DtDate  ||  DtCur >= DtDate + COleDateTimeSpan(30, 0, 0, 0))
						bNeedRemit = TRUE;
				}
			}
		}
	}
	// 送金登録ダイアログ
	if (bNeedRemit) {
		CRemitRegDlg dlg;
		dlg.m_bIDate = bIDate;
		dlg.m_TIDate = TIDate;
		dlg.m_bIVer = bIVer;
		dlg.m_dwIVer = dwIVer;
		if (dlg.DoModal() == IDCANCEL)
			return -1;
	}

	return 0;
}

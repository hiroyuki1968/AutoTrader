// KehaiViewerDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "KehaiViewer.h"
#include "KehaiViewerDlg.h"

#include <afxdao.h>
#include "../Common.h"
#include "../License.h"
#include "../AutoTraderDef.h"
#include "KehaiViewerDef.h"
#include "RemitRegDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKehaiViewerDlg ダイアログ

CKehaiViewerDlg::CKehaiViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKehaiViewerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKehaiViewerDlg)
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

void CKehaiViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKehaiViewerDlg)
		// メモ: この場所には ClassWizard によって DDX と DDV の呼び出しが追加されます。
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKehaiViewerDlg, CDialog)
	//{{AFX_MSG_MAP(CKehaiViewerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER, OnUser)
	ON_MESSAGE(WM_USER + 1, OnUser1)
	ON_MESSAGE(WM_USER + 2, OnUser2)
	ON_MESSAGE(WM_USER + 4, OnUser4)
	ON_MESSAGE(WM_USER + 5, OnUser5)
	ON_MESSAGE(WM_USER + 6, OnUser6)
	ON_MESSAGE(WM_USER + 7, OnUser7)
	ON_MESSAGE(WM_USER + 8, OnUser8)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKehaiViewerDlg メッセージ ハンドラ

BOOL CKehaiViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。

	SetWindowText(m_strKehaiViewerWndName);

	ModifyStyle(WS_CAPTION, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);

	CRect RectDlg;
	::GetWindowRect(m_hWnd, &RectDlg);

	RectDlg.OffsetRect(- RectDlg.left, - RectDlg.top);
//	RectDlg.right = 1003;
	RectDlg.right = 1000;
	RectDlg.bottom = 516;
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

	LOGFONT LfCtrl;
	GetFont()->GetLogFont(&LfCtrl);
	LfCtrl.lfHeight = -75;
	m_Font.CreatePointFontIndirect(&LfCtrl);

	CDC* pDC = GetDC();
	m_MemoryDC.CreateCompatibleDC(pDC);
	m_Bitmap.CreateCompatibleBitmap(pDC, m_w, m_h);

	m_pOldBitmap = m_MemoryDC.SelectObject(&m_Bitmap);
	m_pOldFont = m_MemoryDC.SelectObject(&m_Font);

	m_MemoryDC.GetTextMetrics(&m_Metrics);

	ReleaseDC(pDC);

	ZeroMemory(m_plPrice, sizeof(m_plPrice));
	ZeroMemory(m_plTradeCount, sizeof(m_plTradeCount));
	ZeroMemory(m_pnPriceDirec, sizeof(m_pnPriceDirec));
	ZeroMemory(m_pplKehaiPrice, sizeof(m_pplKehaiPrice));
	ZeroMemory(m_pplKehaiCount, sizeof(m_pplKehaiCount));
	int i;
	int j;
	for (i = 0; i < 11; i ++) {
		m_pcrPriceTextColor[i] = RGB(255, 255, 255);
		m_pcrPriceDirecTextColor[i] = RGB(255, 255, 255);
		for (j = 0; j < 10; j ++) {
			m_ppcrKehaiPriceBkColor[i][j] = RGB(255, 255, 255);
			m_ppcrKehaiCountBkColor[i][j] = RGB(255, 255, 255);
		}
	}

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

	m_hHook = SetWindowsHookEx( WH_GETMESSAGE, GetMsgProc, NULL, GetCurrentThreadId() );
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CKehaiViewerDlg::OnPaint() 
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
		pDC->BitBlt(m_x0, m_h - m_Size.cy, m_Size.cx * 2, m_Size.cy, &m_MemoryDC, m_x0, m_h - m_Size.cy, SRCCOPY);
		ReleaseDC(pDC);

		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CKehaiViewerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

LRESULT CKehaiViewerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
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

void CKehaiViewerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください

	// ★ファイルのビューをアンマップし、マップのハンドルをクローズ
	if (m_pMappingView)
		::UnmapViewOfFile(m_pMappingView);
	if (m_hMapping)
		::CloseHandle(m_hMapping);

	m_MemoryDC.SelectObject(m_pOldFont);
	m_MemoryDC.SelectObject(m_pOldBitmap);
	m_MemoryDC.DeleteDC();

	if (m_hHook)
		UnhookWindowsHookEx( m_hHook );
}

void CKehaiViewerDlg::OnTimer(UINT nIDEvent) 
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

void CKehaiViewerDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	KillWMUserTimer(2);
	SetWMUserTimer(0, 2, NULL);
	
	CDialog::OnOK();
}

void CKehaiViewerDlg::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	KillWMUserTimer(3);
	SetWMUserTimer(0, 3, NULL);
	
	CDialog::OnCancel();
}

HBRUSH CKehaiViewerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: この位置で DC のアトリビュートを変更してください
	int nID = pWnd->GetDlgCtrlID();
	if (nID >= IDC_EDIT1  &&  nID <= IDC_EDIT200) {
		int nBase = nID - IDC_EDIT1;
		int nMeigara = nBase / 20;
		int nIndex = nBase % 20;
		if (nIndex < 10) {
#ifdef DISPFX
			pDC->SetBkColor(m_ppcrKehaiPriceBkColor[nMeigara][nIndex]);
#else
			pDC->SetBkColor(m_ppcrKehaiPriceBkColor[nMeigara + 1][nIndex]);
#endif
		} else {
			nIndex -= 10;
#ifdef DISPFX
			pDC->SetBkColor(m_ppcrKehaiCountBkColor[nMeigara][nIndex]);
#else
			pDC->SetBkColor(m_ppcrKehaiCountBkColor[nMeigara + 1][nIndex]);
#endif
		}
	} else if (nID >= IDC_EDIT221  &&  nID <= IDC_EDIT230) {
		int nMeigara = nID - IDC_EDIT221;
#ifdef DISPFX
		pDC->SetBkColor(m_pcrPriceTextColor[nMeigara]);
#else
		pDC->SetBkColor(m_pcrPriceTextColor[nMeigara + 1]);
#endif
	} else if (nID >= IDC_EDIT231  &&  nID <= IDC_EDIT240) {
		int nMeigara = nID - IDC_EDIT231;
		pDC->SetBkColor(RGB(255, 255, 255));
#ifdef DISPFX
		pDC->SetTextColor(m_pcrPriceDirecTextColor[nMeigara]);
#else
		pDC->SetTextColor(m_pcrPriceDirecTextColor[nMeigara + 1]);
#endif
	}
	
	// TODO: デフォルトのブラシが望みのものでない場合には、違うブラシを返してください
	return hbr;
}

LRESULT CKehaiViewerDlg::OnUser(WPARAM wParam, LPARAM lParam)
{
	if (! PreUser(wParam, lParam))
		return 0;
	nPumpWaitingMessages ++;
	switch (wParam) {
//	case 1:
//		DestroyWindow();
//		break;
	case 2:
		User1();
		break;
	case 3:
		User2();
		break;
	case 4:
		EraseDisp();
		DispKehai();
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

LRESULT CKehaiViewerDlg::OnUser1(WPARAM wParam, LPARAM lParam)
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

LRESULT CKehaiViewerDlg::OnUser2(WPARAM wParam, LPARAM lParam)
{
	KillWMUserTimer(3);
	SetWMUserTimer(0, 3, NULL);

	return 0;
}

LRESULT CKehaiViewerDlg::OnUser4(WPARAM wParam, LPARAM lParam)
{
	SetWMUserTimer(0, 5, wParam);
	return 0;
}

LRESULT CKehaiViewerDlg::OnUser5(WPARAM wParam, LPARAM lParam)
{
	SetWMUserTimer(0, 6, wParam);
	return 0;
}

LRESULT CKehaiViewerDlg::OnUser6(WPARAM wParam, LPARAM lParam)
{
	SetWMUserTimer(0, 7, wParam);
	return 0;
}

LRESULT CKehaiViewerDlg::OnUser7(WPARAM wParam, LPARAM lParam)
{
	KillWMUserTimer(8);
	SetWMUserTimer(0, 8, NULL);

	return 0;
}

LRESULT CKehaiViewerDlg::OnUser8(WPARAM wParam, LPARAM lParam)
{
	KillWMUserTimer(9);
	SetWMUserTimer(0, 9, NULL);

	return 0;
}

BOOL CKehaiViewerDlg::PreUser(WPARAM wParam, LPARAM lParam, USERPROC lpUserFunc)
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

BOOL CKehaiViewerDlg::SetWMUserParam(UINT nIDEvent, WPARAM wParam, LPARAM lParam, USERPROC lpUserFunc)
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

void CKehaiViewerDlg::SetWMUserTimer(UINT nElapse, WPARAM wParam, LPARAM lParam, USERPROC lpUserFunc)
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

void CKehaiViewerDlg::KillWMUserTimer(WPARAM wParam)
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

int CKehaiViewerDlg::DlData0()
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

int CKehaiViewerDlg::HiashiAnalyze(LPCTSTR lpszCode)
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

CFunashi0 CKehaiViewerDlg::GetFunashi(long* plFunashi, int nIndex)
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

CFunashi0 CKehaiViewerDlg::GetFunashi(int nIndex0, int nIndex1)
{
	return GetFunashi((long *)m_PaFunashi[nIndex0], nIndex1);
}

void CKehaiViewerDlg::DispKehai() 
{
	int i;
	int j;
	int n;
	long* plFunashi;
	CFunashi0 Funashi0;
	long lPrice;
	long lTradeCount;
	long lKehaiPrice;
	long lKehaiCount;
	CEdit* pEdit;
	CString strCode;
	CString strDispCode;
	CString strName;
	int nIndex;
	CString strText;
	void* pVoid;
	BOOL bKehai;
	BOOL bSold;

	m_MemoryDC.FillSolidRect(0, 0, m_w, m_h, GetSysColor(COLOR_3DFACE));

#ifdef DISPFX
	for (n = 0; n < 10; n ++) {
#else
	for (n = 1; n < 11; n ++) {
#endif
		if (m_nPage) {
#ifdef DISPFX
			nIndex = (m_nPage - 1) * 10 + n;
#else
			nIndex = (m_nPage - 1) * 10 + (n - 1);
#endif
			if (nIndex > m_SaSelCode.GetUpperBound())
				break;
			strCode = m_SaSelCode[nIndex];
		} else {
			if (n > m_SaNiceCode.GetUpperBound())
				break;
			strCode = m_SaNiceCode[n];
		}
		if (m_MstpHiashiCode.Lookup(strCode, pVoid)) {
			i = (int)pVoid;

			CodeToName(strCode, strName, NULL, NULL, NULL, NULL, NULL, NULL, &strDispCode);

#ifdef DISPFX
			GetDlgItem(IDC_EDIT201 + n)->SetWindowText(strDispCode);
			GetDlgItem(IDC_EDIT211 + n)->SetWindowText((m_MstpNewsCode.Lookup(strCode, pVoid) ? "★" : m_MstpNewsCode2.Lookup(strCode, pVoid) ? "☆" : pszEmpty) + StrConvHalfWidth(strName));
#else
			GetDlgItem(IDC_EDIT201 + (n - 1))->SetWindowText(strDispCode);
			GetDlgItem(IDC_EDIT211 + (n - 1))->SetWindowText((m_MstpNewsCode.Lookup(strCode, pVoid) ? "★" : m_MstpNewsCode2.Lookup(strCode, pVoid) ? "☆" : pszEmpty) + StrConvHalfWidth(strName));
#endif

			plFunashi = (long *)m_PaFunashi[i];
			j = plFunashi[-1] - 1;
			if (j != -1) {
				Funashi0 = GetFunashi(plFunashi, j);
				CKehai0& KehaiWork = Funashi0.m_Kehai;

				bSold = j >= 1 ? Funashi0.m_lTradeCount != GetFunashi(plFunashi, j - 1).m_lTradeCount : FALSE;

				lPrice = Funashi0.m_lPrice;
#ifdef DISPFX
				pEdit = (CEdit *)GetDlgItem(IDC_EDIT221 + n);
#else
				pEdit = (CEdit *)GetDlgItem(IDC_EDIT221 + (n - 1));
#endif
				pEdit->SetWindowText(LToA(lPrice));
				m_pcrPriceTextColor[n] = lPrice == m_plPrice[n] ? RGB(255, 255, 255) : RGB(255, 255, 0);
				pEdit->Invalidate();

				lTradeCount = Funashi0.m_lTradeCount;
#ifdef DISPFX
				pEdit = (CEdit *)GetDlgItem(IDC_EDIT231 + n);
#else
				pEdit = (CEdit *)GetDlgItem(IDC_EDIT231 + (n - 1));
#endif
				if (m_plPrice[n] == 0 || m_pnPriceDirec[n] == -1 && lPrice == m_plPrice[n] && lTradeCount == m_plTradeCount[n]) {
					pEdit->SetWindowText("・");
					m_pcrPriceDirecTextColor[n] = RGB(0, 255, 0);

					m_pnPriceDirec[n] = -1;
				} else if (lPrice > m_plPrice[n] || lPrice == m_plPrice[n] && m_pnPriceDirec[n] == 2) {
					pEdit->SetWindowText("↑");
					m_pcrPriceDirecTextColor[n] = RGB(255, 0, 0);

					m_pnPriceDirec[n] = 2;
				} else if (lPrice < m_plPrice[n] || lPrice == m_plPrice[n] && m_pnPriceDirec[n] == 1) {
					pEdit->SetWindowText("↓");
					m_pcrPriceDirecTextColor[n] = RGB(0, 0, 255);

					m_pnPriceDirec[n] = 1;
				} else {
					pEdit->SetWindowText("→");
					m_pcrPriceDirecTextColor[n] = RGB(0, 255, 0);

					m_pnPriceDirec[n] = 0;
				}
				pEdit->Invalidate();

				m_plPrice[n] = lPrice;
				m_plTradeCount[n] = lTradeCount;

				bKehai = FALSE;
				for (j = 0; j < 10; j ++)
					if (KehaiWork.m_plKehaiPrice[j]) {
						bKehai = TRUE;
						break;
					}
				for (j = 0; j < 10; j ++) {
					lKehaiPrice = KehaiWork.m_plKehaiPrice[j];
					lKehaiCount = KehaiWork.m_plKehaiCount[j];

					if (! bKehai  &&  j == 5)
						lKehaiPrice = Funashi0.m_lPrice;

#ifdef DISPFX
					pEdit = (CEdit *)GetDlgItem(IDC_EDIT1 + n * 20 + j);
#else
					pEdit = (CEdit *)GetDlgItem(IDC_EDIT1 + (n - 1) * 20 + j);
#endif
					pEdit->SetWindowText(LToA(lKehaiPrice));
//					pEdit->SetReadOnly(lKehaiPrice == m_pplKehaiPrice[n][j]);
					m_ppcrKehaiPriceBkColor[n][j] = lKehaiPrice == m_pplKehaiPrice[n][j] ? RGB(255, 255, 255) : RGB(0, 255, 255);
					pEdit->Invalidate();

#ifdef DISPFX
					pEdit = (CEdit *)GetDlgItem(IDC_EDIT11 + n * 20 + j);
#else
					pEdit = (CEdit *)GetDlgItem(IDC_EDIT11 + (n - 1) * 20 + j);
#endif
					pEdit->SetWindowText(LToA(lKehaiCount));
//					pEdit->SetReadOnly(! bKehai  ||  lKehaiPrice == m_pplKehaiPrice[n][j]  &&  lKehaiCount == m_pplKehaiCount[n][j]);
					m_ppcrKehaiCountBkColor[n][j] = ! bKehai  ||  lKehaiPrice == m_pplKehaiPrice[n][j]  &&  lKehaiCount == m_pplKehaiCount[n][j]  ? RGB(255, 255, 255) : lKehaiCount < 0 && (j == 4 || j == 5) ? RGB(255, 0, 0) : bSold && (j == 4 || j == 5) ? RGB(255, 255, 0) : RGB(0, 255, 255);
					pEdit->Invalidate();

					m_pplKehaiPrice[n][j] = lKehaiPrice;
					m_pplKehaiCount[n][j] = lKehaiCount;
				}
			}
		}
	}
	m_MemoryDC.SetBkColor(RGB(255, 255, 255));
	strText = StrFormat("%d/%d", m_nPage, 1 + m_SaSelCode.GetUpperBound() / 10);
	m_Size = m_MemoryDC.GetOutputTabbedTextExtent(strText, 0, NULL);
	m_MemoryDC.TextOut(0, m_h - m_Size.cy, strText);

	CDC* pDC = GetDC();
	pDC->BitBlt(m_x0, m_h - m_Size.cy, m_Size.cx * 2, m_Size.cy, &m_MemoryDC, m_x0, m_h - m_Size.cy, SRCCOPY);
	ReleaseDC(pDC);
}

void CKehaiViewerDlg::EraseDisp() 
{
	int i;
	int j;
	CEdit* pEdit;

	for (i = 0; i < 10; i ++) {
		GetDlgItem(IDC_EDIT201 + i)->SetWindowText(pszEmpty);
		GetDlgItem(IDC_EDIT211 + i)->SetWindowText(pszEmpty);
		GetDlgItem(IDC_EDIT221 + i)->SetWindowText(pszEmpty);
		GetDlgItem(IDC_EDIT231 + i)->SetWindowText(pszEmpty);

#ifdef DISPFX
		m_pcrPriceTextColor[i] = RGB(255, 255, 255);
		m_pcrPriceDirecTextColor[i] = RGB(255, 255, 255);
#else
		m_pcrPriceTextColor[i + 1] = RGB(255, 255, 255);
		m_pcrPriceDirecTextColor[i + 1] = RGB(255, 255, 255);
#endif

		for (j = 0; j < 10; j ++) {
			pEdit = (CEdit *)GetDlgItem(IDC_EDIT1 + i * 20 + j);
			pEdit->SetWindowText(pszEmpty);
//			pEdit->SetReadOnly(TRUE);
#ifdef DISPFX
			m_ppcrKehaiPriceBkColor[i][j] = RGB(255, 255, 255);
#else
			m_ppcrKehaiPriceBkColor[i + 1][j] = RGB(255, 255, 255);
#endif
			pEdit->Invalidate();

			pEdit = (CEdit *)GetDlgItem(IDC_EDIT11 + i * 20 + j);
			pEdit->SetWindowText(pszEmpty);
//			pEdit->SetReadOnly(TRUE);
			m_ppcrKehaiCountBkColor[i][j] = RGB(255, 255, 255);
			pEdit->Invalidate();
		}
	}

	ZeroMemory(m_plPrice, sizeof(m_plPrice));
	ZeroMemory(m_plTradeCount, sizeof(m_plTradeCount));
	ZeroMemory(m_pnPriceDirec, sizeof(m_pnPriceDirec));
	ZeroMemory(m_pplKehaiPrice, sizeof(m_pplKehaiPrice));
	ZeroMemory(m_pplKehaiCount, sizeof(m_pplKehaiCount));
}

void CKehaiViewerDlg::DispErrorLog(LPCTSTR lpszFormat, ...)
{
	CStringBuffer sb;

	va_list vl;
	va_start(vl, lpszFormat);
	sb.FormatV(lpszFormat, vl);
	va_end(vl);

	sb = COleDateTime::GetCurrentTime().Format("%H:%M:%S ") + sb;

	MessageBox(sb);
}

int CKehaiViewerDlg::CodeToName(CString& strCode, CString& strName, CString* pstrSijoName, short* psUnit, long* plHighPrice, long* plLowPrice, long* plPreEndPrice, long* plTradeCount, CString* pstrCodeEx) 
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

void CKehaiViewerDlg::User1() 
{
	DispKehai();
}

void CKehaiViewerDlg::User2() 
{
	int i;
	int imax;
	char pszBuf[MAX_PATH];
	CStringArray SaHiashiCode;

	m_SaNiceCode.RemoveAll();
	m_SaSelCode.RemoveAll();
	m_MstpSelCode.RemoveAll();

	m_SaNiceCode.Add("101");
	for (i = 0; ; i ++)
		if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_CODE + IToA(i), pszX, pszBuf, MAX_PATH, m_strMeigaraIniFPath) == 1)
			break;
		else
			m_SaNiceCode.Add(pszBuf);
	for (i = 0; ; i ++)
		if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_SELCODE + IToA(i), pszEmpty, pszBuf, MAX_PATH, m_strMeigaraIniFPath)) {
			m_SaSelCode.Add(pszBuf);
			m_MstpSelCode[pszBuf] = NULL;
		} else
			break;
	for (i = 0; ; i ++)
		if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_HIASHICODE + IToA(i), pszEmpty, pszBuf, MAX_PATH, m_strMeigaraIniFPath))
			SaHiashiCode.Add(pszBuf);
		else
			break;

	HiashiAnalyze();
	for (i = 0, imax = SaHiashiCode.GetSize(); i < imax; i ++)
		HiashiAnalyze(SaHiashiCode[i]);

	KillWMUserTimer(4);
	SetWMUserTimer(0, 4, NULL);
}

void CKehaiViewerDlg::User4(WPARAM wParam) 
{
	int i;
	int imax;
	CString strStk = IToA(wParam);
	BOOL bFound = FALSE;

	for (i = 1, imax = m_SaNiceCode.GetSize(); i < imax; i ++)
		if (m_SaNiceCode[i].Left(4) == strStk) {
			m_nPage = 0;
			bFound = TRUE;
			break;
		}
	if (! bFound)
		for (i = 1, imax = m_SaSelCode.GetSize(); i < imax; i ++)
			if (m_SaSelCode[i].Left(4) == strStk) {
				m_nPage = 1 + i / 10;
				break;
			}

	KillWMUserTimer(4);
	SetWMUserTimer(0, 4, NULL);
}

void CKehaiViewerDlg::User5(WPARAM wParam) 
{
	m_nPage = wParam;
	KillWMUserTimer(4);
	SetWMUserTimer(0, 4, NULL);
}

void CKehaiViewerDlg::User6(WPARAM wParam) 
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
	KillWMUserTimer(4);
	SetWMUserTimer(0, 4, NULL);
}

void CKehaiViewerDlg::User7() 
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

void CKehaiViewerDlg::User8() 
{
	m_MstmCodeMainCodeName.RemoveAll();
	KillWMUserTimer(2);
	SetWMUserTimer(0, 2, NULL);
}

int CKehaiViewerDlg::CheckLicense()
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

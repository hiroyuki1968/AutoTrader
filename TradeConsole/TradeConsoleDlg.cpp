// TradeConsoleDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "TradeConsole.h"
#include "TradeConsoleDlg.h"

#include "webbrowser2.h"
#include "../Common.h"
#include "../License.h"
#include "../Html.h"
#include "LoginDlg.h"
#include "RemitRegDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTradeConsoleDlg ダイアログ

CTradeConsoleDlg::CTradeConsoleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTradeConsoleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTradeConsoleDlg)
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTradeConsoleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTradeConsoleDlg)
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl1);
	DDX_Control(pDX, IDC_EXPLORER1, m_WebBrowser21);
	DDX_Control(pDX, IDC_EXPLORER2, m_WebBrowser22);
	DDX_Control(pDX, IDC_EXPLORER3, m_WebBrowser23);
	DDX_Control(pDX, IDC_EXPLORER4, m_WebBrowser24);
	DDX_Control(pDX, IDC_EXPLORER5, m_WebBrowser25);
	DDX_Control(pDX, IDC_EXPLORER6, m_WebBrowser26);
	DDX_Control(pDX, IDC_EXPLORER7, m_WebBrowser27);
	DDX_Control(pDX, IDC_EXPLORER8, m_WebBrowser28);
	DDX_Control(pDX, IDC_EXPLORER9, m_WebBrowser29);
	DDX_Control(pDX, IDC_EXPLORER10, m_WebBrowser210);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTradeConsoleDlg, CDialog)
	//{{AFX_MSG_MAP(CTradeConsoleDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER, OnUser)
	ON_MESSAGE(WM_USER + 1, OnUser1)
	ON_MESSAGE(WM_USER + 2, OnUser2)
	ON_MESSAGE(WM_USER + 3, OnUser3)
	ON_MESSAGE(WM_USER + 4, OnUser4)
	ON_MESSAGE(WM_USER + 5, OnUser5)
	ON_MESSAGE(WM_USER + 6, OnUser6)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CTradeConsoleDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CTradeConsoleDlg)
	ON_EVENT(CTradeConsoleDlg, IDC_EXPLORER1, 259 /* DocumentComplete */, OnDocumentCompleteExplorer1, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CTradeConsoleDlg, IDC_EXPLORER2, 259 /* DocumentComplete */, OnDocumentCompleteExplorer2, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CTradeConsoleDlg, IDC_EXPLORER5, 259 /* DocumentComplete */, OnDocumentCompleteExplorer5, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CTradeConsoleDlg, IDC_EXPLORER3, 252 /* NavigateComplete2 */, OnNavigateComplete2Explorer3, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CTradeConsoleDlg, IDC_EXPLORER6, 252 /* NavigateComplete2 */, OnNavigateComplete2Explorer6, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CTradeConsoleDlg, IDC_EXPLORER7, 252 /* NavigateComplete2 */, OnNavigateComplete2Explorer7, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CTradeConsoleDlg, IDC_EXPLORER2, 251 /* NewWindow2 */, OnNewWindow2Explorer2, VTS_PDISPATCH VTS_PBOOL)
	ON_EVENT(CTradeConsoleDlg, IDC_EXPLORER5, 251 /* NewWindow2 */, OnNewWindow2Explorer5, VTS_PDISPATCH VTS_PBOOL)
	ON_EVENT(CTradeConsoleDlg, IDC_EXPLORER6, 251 /* NewWindow2 */, OnNewWindow2Explorer6, VTS_PDISPATCH VTS_PBOOL)
	ON_EVENT(CTradeConsoleDlg, IDC_EXPLORER3, 259 /* DocumentComplete */, OnDocumentCompleteExplorer3, VTS_DISPATCH VTS_PVARIANT)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTradeConsoleDlg メッセージ ハンドラ

BOOL CTradeConsoleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。

	m_hHook = NULL;
	m_nWMUserTimer = 100;
	m_bUserCall =
	m_bStreamerWide =
	m_bStreamerSel =
	m_bWebBrowser21MenuClickInterval =
		FALSE;
	m_bWebBrowser21 = TRUE;
	m_nOnNewWindow2Explorer2 = 0;

	SetWindowText(m_strTradeConsoleWndName);

	ModifyStyle(WS_CAPTION, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);

	::GetWindowRect(m_hWnd, &m_RectDlg);
	m_RectDlg.OffsetRect(- m_RectDlg.left, - m_RectDlg.top);
	MoveWindow(&m_RectDlg);

	m_WebBrowser23.GetWindowRect(&m_RectWB2);

	int i;

	for (i = IDC_EXPLORER2; i <= IDC_EXPLORER10; i ++)
		::ShowWindow(GetDlgItem(i)->m_hWnd, SW_HIDE);

	ShowWindow(SW_SHOW);
	UpdateWindow();

	m_TabCtrl1.InsertItem(i = 0, "そしあす証券");
	m_TabCtrl1.InsertItem(++ i, "松井証券");
	m_TabCtrl1.InsertItem(++ i, "株価ボード");
	m_TabCtrl1.InsertItem(++ i, "QUICK情報");
	m_TabCtrl1.InsertItem(++ i, "コスモ証券");
	m_TabCtrl1.InsertItem(++ i, "マーケットサーチ");
	m_TabCtrl1.InsertItem(++ i, "登録銘柄 自動更新");
	m_TabCtrl1.InsertItem(++ i, "NIKKEI NET 日経平均株価");
	m_TabCtrl1.InsertItem(++ i, "国内主要指数チャート");
	m_TabCtrl1.InsertItem(++ i, "【デイトレードアイランド】");

	if (CheckLicense()) {
		PostQuitMessage(0);
		return TRUE;
	}

	HKEY hKey;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, REG_SUBKEY_AUTOTRADER, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
		LPBYTE lpRegData;
		DWORD cbRegDataSize;

		lpRegData = (LPBYTE)new _TCHAR[IDPWD_BUFLEN];

		cbRegDataSize = IDPWD_BUFLEN;
		if (RegQueryValueEx(hKey, REG_KEY_TREASUREID, NULL, NULL, lpRegData, &cbRegDataSize) == ERROR_SUCCESS  &&  cbRegDataSize > 1)
			m_strTreasureId = DecodeSecretString(CString(lpRegData));
		cbRegDataSize = IDPWD_BUFLEN;
		if (RegQueryValueEx(hKey, REG_KEY_TREASUREPWD, NULL, NULL, lpRegData, &cbRegDataSize) == ERROR_SUCCESS  &&  cbRegDataSize > 1)
			m_strTreasurePasswd = DecodeSecretString(CString(lpRegData));
		cbRegDataSize = IDPWD_BUFLEN;
		if (RegQueryValueEx(hKey, REG_KEY_MATSUIID, NULL, NULL, lpRegData, &cbRegDataSize) == ERROR_SUCCESS  &&  cbRegDataSize > 1)
			m_strMatsuiId = DecodeSecretString(CString(lpRegData));
		cbRegDataSize = IDPWD_BUFLEN;
		if (RegQueryValueEx(hKey, REG_KEY_MATSUIPWD, NULL, NULL, lpRegData, &cbRegDataSize) == ERROR_SUCCESS  &&  cbRegDataSize > 1)
			m_strMatsuiPasswd = DecodeSecretString(CString(lpRegData));
		cbRegDataSize = IDPWD_BUFLEN;
		if (RegQueryValueEx(hKey, REG_KEY_COSMOID, NULL, NULL, lpRegData, &cbRegDataSize) == ERROR_SUCCESS  &&  cbRegDataSize > 1)
			m_strCosmoId = DecodeSecretString(CString(lpRegData));
		cbRegDataSize = IDPWD_BUFLEN;
		if (RegQueryValueEx(hKey, REG_KEY_COSMOPWD, NULL, NULL, lpRegData, &cbRegDataSize) == ERROR_SUCCESS  &&  cbRegDataSize > 1)
			m_strCosmoPasswd = DecodeSecretString(CString(lpRegData));

		delete [] lpRegData;
		RegCloseKey(hKey);
	}
	if (
		m_strTreasureId.IsEmpty()
		|| m_strTreasurePasswd.IsEmpty()
		|| m_strMatsuiId.IsEmpty()
		|| m_strMatsuiPasswd.IsEmpty()
		|| m_strCosmoId.IsEmpty()
		|| m_strCosmoPasswd.IsEmpty()
	) {
		MessageBox("ID、パスワード未設定エラー");
		PostQuitMessage(0);
		return TRUE;
	}

/*
	CLoginDlg LoginDlg;
	if (LoginDlg.DoModal() == IDOK) {
		if (LoginDlg.m_strPasswd != m_strKazakaPasswd) {
			MessageBox("パスワードが正しくありません", NULL, MB_ICONSTOP);
			PostQuitMessage(0);
			return TRUE;
		}
	} else {
		PostQuitMessage(0);
		return TRUE;
	}
*/
	
	for (i = 2; i >= 0; i --) {
		if (m_bMentenance0  &&  i == 0) continue;
		if (m_bMentenance1  &&  i == 1) continue;
		if (m_bMentenance2  &&  i == 2) continue;

		switch (i) {
		case 0:
			m_WebBrowser21.Navigate(URL_LOGIN0, NULL, NULL, NULL, NULL);
			SetWMUserParam(1, 100, NULL);
			SetTimer(1, 1740000U, NULL);
			break;
		case 1:
			m_WebBrowser22.Navigate(URL_LOGIN1, NULL, NULL, NULL, NULL);
			SetWMUserParam(2, 200, NULL);
			SetTimer(2, 29 * 60 * 1000, NULL);
			break;
		default:
			m_WebBrowser25.Navigate(URL_LOGIN2, NULL, NULL, NULL, NULL);
			SetWMUserParam(5, 300, NULL);
			SetTimer(3, 10740000U, NULL);
		}
	}

	m_WebBrowser28.Navigate("http://www.nikkei.com/markets/kabu/", NULL, NULL, NULL, NULL);
	m_WebBrowser29.Navigate("http://sp03.hp.infoseek.co.jp/chart-index.html", NULL, NULL, NULL, NULL);
	m_WebBrowser210.Navigate("http://daytrade-island.com/", NULL, NULL, NULL, NULL);

	m_WebBrowser21.SetFocus();

	m_hHook = SetWindowsHookEx( WH_GETMESSAGE, GetMsgProc, NULL, GetCurrentThreadId() );
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CTradeConsoleDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CTradeConsoleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTradeConsoleDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	if (m_hHook)
		UnhookWindowsHookEx( m_hHook );
}

void CTradeConsoleDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
//	CDialog::OnOK();
}

void CTradeConsoleDlg::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	for (int i = 1; i <= 3; i ++)
		KillTimer(i);
	
	CDialog::OnCancel();
}

void CTradeConsoleDlg::OnTimer(UINT nIDEvent)
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if (nIDEvent < 100) {
		if (PreUser(nIDEvent, 0, NULL)) {
			nPumpWaitingMessages ++;
			switch (nIDEvent) {
			case 1:
				if (m_bWebBrowser21)
					break;
				m_bWebBrowser21 = TRUE;
				m_WebBrowser21.Refresh();
				SetWMUserParam(1, 101, 0);
				break;
			case 2:
				UpdateStreamer();
				break;
			case 3:
				m_WebBrowser25.Refresh();
			}
			nPumpWaitingMessages --;
		}
	} else {
		KillTimer(nIDEvent);
		WMParam WMParamTemp;
		m_MltwmpWMUserTimer.Lookup(nIDEvent, WMParamTemp);
		m_MltwmpWMUserTimer.RemoveKey(nIDEvent);
		if (WMParamTemp.lpUserFunc)
			(this->*WMParamTemp.lpUserFunc)(WMParamTemp.wParam, WMParamTemp.lParam);
		else
			OnTimer(WMParamTemp.wParam);
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CTradeConsoleDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	SelchangeTab1();
	
	*pResult = 0;
}

void CTradeConsoleDlg::OnDocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	WMParam WMParamTemp;
	if (m_MltwmpWMUserTimer.Lookup(1, WMParamTemp)) {
		m_MltwmpWMUserTimer.RemoveKey(1);
		PostMessage(WM_USER, WMParamTemp.wParam, WMParamTemp.lParam);
	}
}

void CTradeConsoleDlg::OnDocumentCompleteExplorer2(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	WMParam WMParamTemp;
	if (m_MltwmpWMUserTimer.Lookup(2, WMParamTemp)) {
		m_MltwmpWMUserTimer.RemoveKey(2);
		PostMessage(WM_USER, WMParamTemp.wParam, WMParamTemp.lParam);
	}
}

void CTradeConsoleDlg::OnDocumentCompleteExplorer3(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if (!m_bStreamerSel) {
		CString strUrl = URL->bstrVal;
		if (strUrl.Find("/QS01.cgi?") != -1) {
			Sleep(100);
			m_TabCtrl1.SetCurSel(2);
			SelchangeTab1();
			m_bStreamerSel = TRUE;
		}
	}
	
}

void CTradeConsoleDlg::OnDocumentCompleteExplorer5(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	WMParam WMParamTemp;
	if (m_MltwmpWMUserTimer.Lookup(5, WMParamTemp)) {
		m_MltwmpWMUserTimer.RemoveKey(5);
		PostMessage(WM_USER, WMParamTemp.wParam, WMParamTemp.lParam);
	}
}

void CTradeConsoleDlg::OnNavigateComplete2Explorer3(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString strUrl = URL->bstrVal;
	if (strUrl.Find("/QS01.cgi?") == -1)
		m_WebBrowser23.MoveWindow(&m_RectWB2);
	else
		m_WebBrowser23.MoveWindow(&CRect(0, 0, 1016, 516));
}

void CTradeConsoleDlg::OnNavigateComplete2Explorer6(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_WebBrowser26.MoveWindow(&m_RectWB2);
}

void CTradeConsoleDlg::OnNavigateComplete2Explorer7(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString strUrl = URL->bstrVal;
	TCITEM TabCtrlItem;
	TabCtrlItem.mask = TCIF_TEXT;
	if (strUrl.Find("/cb_cr_kabukaboard.aspx?") == -1)
		TabCtrlItem.pszText = "マーケットサーチポップアップ";
	else
		TabCtrlItem.pszText = "登録銘柄 自動更新";
	m_TabCtrl1.SetItem(6, &TabCtrlItem);
}

void CTradeConsoleDlg::OnNewWindow2Explorer2(LPDISPATCH FAR* ppDisp, BOOL FAR* Cancel) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if (m_nOnNewWindow2Explorer2)
		*ppDisp = m_WebBrowser24.GetApplication();
	else {
		*ppDisp = m_WebBrowser23.GetApplication();
		m_nOnNewWindow2Explorer2 ++;
	}
}

void CTradeConsoleDlg::OnNewWindow2Explorer5(LPDISPATCH FAR* ppDisp, BOOL FAR* Cancel) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	*ppDisp = m_WebBrowser26.GetApplication();
}

void CTradeConsoleDlg::OnNewWindow2Explorer6(LPDISPATCH FAR* ppDisp, BOOL FAR* Cancel) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	*ppDisp = m_WebBrowser27.GetApplication();
}

LRESULT CTradeConsoleDlg::OnUser(WPARAM wParam, LPARAM lParam)
{
	if (! PreUser(wParam, lParam))
		return 0;
	nPumpWaitingMessages ++;
	switch (wParam) {
//	case 1:
//		DestroyWindow();
//		break;
	case 2:
		m_bWebBrowser21MenuClickInterval = FALSE;
		break;
	case 100:
		SetWebBrowser2(m_WebBrowser21, NULL, NULL, NULL, "customer", 0, "value", m_strTreasureId);
		SetWebBrowser2(m_WebBrowser21, NULL, NULL, NULL, "pass", 0, "value", m_strTreasurePasswd);
		ClickWebBrowser2(m_WebBrowser21, NULL, NULL, "href", "submit", 0);
		SetWMUserParam(1, wParam + 1, NULL);
		break;
	case 101:
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", NULL, NULL, "AREA_00_0_linkarea", 0);
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", NULL, NULL, "AREA_ST_1_linkarea", 0);
		m_bWebBrowser21MenuClickInterval = TRUE;
		SetWMUserTimer(500, 2, lParam);
		m_bWebBrowser21 = FALSE;
		break;
	case 200:
		SetWebBrowser2(m_WebBrowser22, NULL, NULL, NULL, "clientCD", 0, "value", m_strMatsuiId);
		SetWebBrowser2(m_WebBrowser22, NULL, NULL, NULL, "passwd", 0, "value", m_strMatsuiPasswd);
		ClickWebBrowser2(m_WebBrowser22, NULL, NULL, NULL, "btn_opn_login", 0);
		SetWMUserParam(2, wParam + 1, NULL);
		break;
	case 201:
		ClickWebBrowser2(m_WebBrowser22, "GM", NULL, "href", "FraInfoVariousToolLst", 0);
		SetWMUserParam(2, wParam + 1, NULL);
		break;
	case 202:
		ClickWebBrowser2(m_WebBrowser22, "CT", NULL, "href", "QBoardConnect", 0);
		PostMessage(WM_USER, wParam + 1, NULL);
		break;
	case 203:
		ClickWebBrowser2(m_WebBrowser22, "CT", NULL, "href", "FraInfoQuick", 0);
		SetWMUserParam(2, wParam + 1, NULL);
		break;
	case 204:
		ClickWebBrowser2(m_WebBrowser22, "CT", NULL, "href", "QuickReadAgree", 0);
		PostMessage(WM_USER, wParam + 1, NULL);
		break;
	case 205:
		GoBackWebBrowser2(m_WebBrowser22);
		GoBackWebBrowser2(m_WebBrowser22);
		break;
	case 300:
		SetWebBrowser2(m_WebBrowser25, NULL, NULL, NULL, "KOB", 0, "value", m_strCosmoId);
		SetWebBrowser2(m_WebBrowser25, NULL, NULL, NULL, "PSW", 0, "value", m_strCosmoPasswd);
		ClickWebBrowser2(m_WebBrowser25, NULL, NULL, NULL, "LOGIN", 0);
		SetWMUserParam(5, wParam + 1, NULL);
		break;
	case 301:
		ClickWebBrowser2(m_WebBrowser25, NULL, NULL, NULL, "mvbasicplus", 0);
		break;
	case 1000:
		m_bWebBrowser21 = TRUE;
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", NULL, NULL, "AREA_ST_0_linkarea", 0);
		m_bWebBrowser21MenuClickInterval = TRUE;
		SetWMUserTimer(500, 2, lParam);
		SetTimer(1, 1740000U, NULL);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 1001:
		SetWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "txt_k_exe_meigara_cd", 0, "value", IToA((int)(lParam >> (1 + 1 + 1))));
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", "id", "cmd_exe", 0);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 1002:
		if ((lParam >> (1 + 1)) & 0x1)
			ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "uri", 0);
		else
			ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "kai", 0);
		SetWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "txt_chu_suryo", 0, "value", LToA(m_DwaBuySuryo[0]));
		SetWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "sel_shikkou_jyoken", 0, "value", IToA(lParam & 0x1));
		SetWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "sel_chu_kigen", 0, "value", IToA((lParam >> 1) & 0x1));
		if ((lParam & 0x1) == 0)
			SetWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "txt_chu_tanka", 0, "value", LToA(m_DwaBuyKakaku[0]));
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "cmd_order_btn", 0);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 1003:
		SetWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "txt_exec_pwd", 0, "value", m_strTreasurePasswd);
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "cmd_save_shinki", 0);
		SetTimer(1, 1740000U, NULL);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 1004:
		Buy();
		m_bWebBrowser21 = FALSE;
		break;
	case 2000:
		m_bWebBrowser21 = TRUE;
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", NULL, NULL, "AREA_ST_1_linkarea", 0);
		m_bWebBrowser21MenuClickInterval = TRUE;
//		SetWMUserTimer(500, wParam + 100, lParam);
		SetWMUserTimer(500, 2, lParam);
		SetTimer(1, 1740000U, NULL);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 2001:
		if (GetState(0) == FALSE) {
			ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "cmd_next", 0);
			SetWMUserParam(1, wParam, lParam);
			break;
		}
/*
		m_bWebBrowser21MenuClickInterval = FALSE;
		break;
	case 2100:
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", NULL, NULL, "AREA_ST_2_linkarea", 0);
		m_bWebBrowser21MenuClickInterval = TRUE;
		SetWMUserTimer(500, 2, lParam);
		SetTimer(1, 1740000U, NULL);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 2101:
		if (GetState(1) == FALSE) {
			ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "cmd_next", 0);
			SetTimer(1, 1740000U, NULL);
			SetWMUserParam(1, wParam, lParam);
			break;
		}
*/
		m_bWebBrowser21 = FALSE;
		break;
	case 3000:
		m_bWebBrowser21 = TRUE;
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", NULL, NULL, "AREA_ST_1_linkarea", 0);
		m_bWebBrowser21MenuClickInterval = TRUE;
		SetWMUserTimer(500, 2, lParam);
		SetTimer(1, 1740000U, NULL);
		m_nChkItem = GetChkItem(lParam);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 3001:
		if (m_nChkItem >= 10) {
			ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "cmd_next", 0);
			m_nChkItem -= 10;
			SetWMUserParam(1, wParam, lParam);
			break;
		}
		SetWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "chk_item", m_nChkItem, "checked", "true");
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "cmd_cancel", 0);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 3002:
		SetWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "txt_exec_pwd", 0, "value", m_strTreasurePasswd);
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "cmd_order_btn", 0);
		SetTimer(1, 1740000U, NULL);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 3003:
		DelOdr(lParam);
		m_bWebBrowser21 = FALSE;
		break;
	case 4000:
		m_bWebBrowser21 = TRUE;
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", NULL, NULL, "AREA_ST_1_linkarea", 0);
		m_bWebBrowser21MenuClickInterval = TRUE;
		SetWMUserTimer(500, 2, lParam);
		SetTimer(1, 1740000U, NULL);
		m_nChkItem = GetChkItem(m_DwaChangeOdrReceiptNo[0]);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 4001:
		if (m_nChkItem >= 10) {
			ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "cmd_next", 0);
			m_nChkItem -= 10;
			SetWMUserParam(1, wParam, lParam);
			break;
		}
		SetWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "chk_item", m_nChkItem, "checked", "true");
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "cmd_correct", 0);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 4002:
		SetWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "txt_chu_suryo", 0, "value", LToA(m_DwaChangeOdrSuryo[0]));
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "cmd_confirm", 0);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 4003:
		SetWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "txt_sikko_password", 0, "value", m_strTreasurePasswd);
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "cmd_save", 0);
		SetTimer(1, 1740000U, NULL);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 4004:
		ChangeOdr(0, lParam);
		m_bWebBrowser21 = FALSE;
		break;
	case 5000:
		m_bWebBrowser21 = TRUE;
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", NULL, NULL, "AREA_ST_1_linkarea", 0);
		m_bWebBrowser21MenuClickInterval = TRUE;
		SetWMUserTimer(500, 2, lParam);
		SetTimer(1, 1740000U, NULL);
		m_nChkItem = GetChkItem(m_DwaChangeOdrReceiptNo[0]);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 5001:
		if (m_nChkItem >= 10) {
			ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "cmd_next", 0);
			m_nChkItem -= 10;
			SetWMUserParam(1, wParam, lParam);
			break;
		}
		if (GetBodyHtmlWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm").Find("訂正中") != -1) {
			PostMessage(WM_USER, wParam + 1, lParam);
			m_bWebBrowser21 = FALSE;
			break;
		}
		SetWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "chk_item", m_nChkItem, "checked", "true");
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "cmd_correct", 0);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 5002:
		SetWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "sel_shikkou_jyoken", 0, "value", IToA(lParam & 0x1));
		if ((lParam & 0x1) == 0)
			SetWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "txt_chu_tanka", 0, "value", LToA(m_DwaChangeOdrKakaku[0]));
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "cmd_confirm", 0);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 5003:
		SetWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "txt_sikko_password", 0, "value", m_strTreasurePasswd);
		ClickWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm", NULL, "cmd_save", 0);
		SetTimer(1, 1740000U, NULL);
		SetWMUserParam(1, wParam + 1, lParam);
		break;
	case 5004:
		ChangeOdr(1, lParam);
		m_bWebBrowser21 = FALSE;
	}
	nPumpWaitingMessages --;
	return 0;
}

LRESULT CTradeConsoleDlg::OnUser1(WPARAM wParam, LPARAM lParam)
{
	m_DwaBuyReceiptNo.Add(wParam);
	m_DwaBuySuryo.Add(lParam);
	return 0;
}

LRESULT CTradeConsoleDlg::OnUser2(WPARAM wParam, LPARAM lParam)
{
	m_DwaBuyKakaku.Add(lParam);
	OnUser(1000, wParam);
	return 0;
}

LRESULT CTradeConsoleDlg::OnUser3(WPARAM wParam, LPARAM lParam)
{
	OnUser(2000, 0);
	return 0;
}

LRESULT CTradeConsoleDlg::OnUser4(WPARAM wParam, LPARAM lParam)
{
	if (GetChkItem(wParam) == -1)
		OnUser(2000, 0);
	OnUser(3000, wParam);
	return 0;
}

LRESULT CTradeConsoleDlg::OnUser5(WPARAM wParam, LPARAM lParam)
{
	m_DwaChangeOdrReceiptNo.Add(wParam);
	m_DwaChangeOdrSuryo.Add(lParam);
	return 0;
}

LRESULT CTradeConsoleDlg::OnUser6(WPARAM wParam, LPARAM lParam)
{
	m_DwaChangeOdrKakaku.Add(lParam);
	if (GetChkItem(m_DwaChangeOdrReceiptNo[m_DwaChangeOdrReceiptNo.GetUpperBound()]) == -1)
		OnUser(2000, 0);
	if (wParam & 0x4)
		OnUser(4000, wParam);
	if (wParam & 0x2)
		OnUser(5000, wParam);
	return 0;
}

BOOL CTradeConsoleDlg::PreUser(WPARAM wParam, LPARAM lParam, USERPROC lpUserFunc)
{
	int i = 0;
	while (m_bUserCall == FALSE  &&  nPumpWaitingMessages == 0  &&  i < m_WmpaUser.GetSize()) {
		WMParam& WMParamTemp = m_WmpaUser[i];
		if (
			WMParamTemp.lpUserFunc == OnUser
			&&  WMParamTemp.wParam >= 1000
			&&  (m_bWebBrowser21  &&  WMParamTemp.wParam % 1000 == 0  ||  m_bWebBrowser21MenuClickInterval  &&  WMParamTemp.wParam % 100 == 0)
		) {
			i ++;
			continue;
		}
		m_bUserCall = TRUE;
		if (WMParamTemp.lpUserFunc)
			(this->*WMParamTemp.lpUserFunc)(WMParamTemp.wParam, WMParamTemp.lParam);
		else
			OnTimer(WMParamTemp.wParam);
		m_bUserCall = FALSE;
		m_WmpaUser.RemoveAt(i);
	}
	if (lpUserFunc == OnUser  &&  wParam == 0) {
		if (m_WmpaUser.GetSize())
			SetWMUserTimer(100);
		return FALSE;
	}
	if (
		nPumpWaitingMessages
		||  m_bUserCall == FALSE
		&&  lpUserFunc == OnUser
		&&  wParam >= 1000
		&&  (m_bWebBrowser21  &&  wParam % 1000 == 0  ||  m_bWebBrowser21MenuClickInterval  &&  wParam % 100 == 0)
	) {
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

BOOL CTradeConsoleDlg::SetWMUserParam(UINT nIDEvent, WPARAM wParam, LPARAM lParam, USERPROC lpUserFunc)
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

void CTradeConsoleDlg::SetWMUserTimer(UINT nElapse, WPARAM wParam, LPARAM lParam, USERPROC lpUserFunc)
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

void CTradeConsoleDlg::SelchangeTab1()
{
	CWnd* pWnd;
	int nCurSel = m_TabCtrl1.GetCurSel();

	for (int i = IDC_EXPLORER1; i <= IDC_EXPLORER10; i ++) {
		pWnd = GetDlgItem(i);
		if (i - IDC_EXPLORER1 == nCurSel) {
			::ShowWindow(pWnd->m_hWnd, SW_SHOW);
			pWnd->SetFocus();
		} else
			::ShowWindow(pWnd->m_hWnd, SW_HIDE);
	}

	switch (nCurSel) {
	case 2:
		if (m_WebBrowser23.GetLocationURL().Find("/QS01.cgi?") == -1) {
			MoveWindow(&m_RectDlg);
			m_TabCtrl1.ShowWindow(SW_SHOW);
		} else {
			m_TabCtrl1.ShowWindow(SW_HIDE);

			if (! m_bStreamerWide) {
				CPoint Point;
				::GetCursorPos(&Point);

				int nX;
				int nY;

				nX = 843 * (65536 / 1920);
				nY = 20 * (65536 / 1080);
				::mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
				::mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
				::mouse_event(MOUSEEVENTF_LEFTUP   | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);

				::SetCursorPos(Point.x, Point.y);

				PumpWaitingMessages();

				m_WebBrowser23.MoveWindow(&CRect(0, -38, 1019, 516));

				m_bStreamerWide = TRUE;
			}

//			MoveWindow(&CRect(0, 0, 1000, 516));
			MoveWindow(&CRect(0, 0, 1003, 516));
		}
		break;
	case 6:
		if (m_WebBrowser27.GetLocationURL().Find("/cb_cr_kabukaboard.aspx?") == -1) {
			MoveWindow(&m_RectDlg);
			m_TabCtrl1.ShowWindow(SW_SHOW);
		} else {
			m_TabCtrl1.ShowWindow(SW_HIDE);
			MoveWindow(&CRect(0, 0, 715, 543));
		}
		break;
	default:
		MoveWindow(&m_RectDlg);
		m_TabCtrl1.ShowWindow(SW_SHOW);
	}
}

void CTradeConsoleDlg::DispErrorLog(LPCTSTR lpszFormat, ...)
{
	CStringBuffer sb;

	va_list vl;
	va_start(vl, lpszFormat);
	sb.FormatV(lpszFormat, vl);
	va_end(vl);

	sb = COleDateTime::GetCurrentTime().Format("%H:%M:%S ") + sb;

	MessageBox(sb);
}

int CTradeConsoleDlg::CheckLicense()
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

void CTradeConsoleDlg::UpdateStreamer()
{
	CRect Rect;
	GetWindowRect(&Rect);
	if (Rect.left == 0  &&  Rect.top == 0  &&  Rect.right == 1003  &&  Rect.bottom == 516) {
		SetAbsoluteForegroundWindow(m_hWnd);

		CPoint Point;
		::GetCursorPos(&Point);

		int nX = 818 * (65536 / 1920);
		int nY = 31 * (65536 / 1080);

		::mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
		::mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
		::mouse_event(MOUSEEVENTF_LEFTUP   | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);

		::SetCursorPos(Point.x, Point.y);

		CWnd* pWnd;
		if ((pWnd = FindWindow(NULL, m_strTradeHelperWndName)) != NULL)
			SetAbsoluteForegroundWindow(pWnd->m_hWnd);
	}
}

void CTradeConsoleDlg::WaitWebBrowser2Ready(CWebBrowser2& WebBrowser2)
{
	while (WebBrowser2.GetReadyState() != 4  ||  WebBrowser2.GetBusy()) {
		Sleep(100);
		PumpWaitingMessages();
	}
}

CComQIPtr<IHTMLDocument2> CTradeConsoleDlg::GetWebBrowser2Document(CWebBrowser2& WebBrowser2, LPCTSTR lpszFrameName0, LPCTSTR lpszFrameName1)
{
	CComQIPtr<IHTMLDocument2> pDocument ;

	// document の取得
	CComPtr<IDispatch> pDisp ;
	pDisp = WebBrowser2.GetDocument() ;
	CComQIPtr<IHTMLDocument2> pDoc = pDisp ;

	CComQIPtr<IHTMLFramesCollection2> pFrameCollection ;
	pDoc->get_frames(&pFrameCollection);

	long lLength;
	pFrameCollection->get_length(&lLength);
	if (lLength  ||  lpszFrameName0 == NULL) {
		CComVariant  varIndex( lpszFrameName0) ;
		CComVariant  varResult ;
		if (lpszFrameName0)
			pFrameCollection->item(&varIndex, &varResult);

		CComQIPtr<IHTMLWindow2> pWindow ;
		if (lpszFrameName0)
			varResult.pdispVal->QueryInterface(IID_IHTMLWindow2, (void**) &pWindow);

		CComQIPtr<IHTMLDocument2> pDoc2 ;
		if (lpszFrameName0)
			pWindow->get_document(&pDoc2);

		CComQIPtr<IHTMLFramesCollection2> pFrameCollection2 ;
		if (lpszFrameName0)
			pDoc2->get_frames(&pFrameCollection2);

		long lLength = 0;
		if (lpszFrameName0)
			pFrameCollection2->get_length(&lLength);
		if (lLength  ||  lpszFrameName1 == NULL) {
			CComVariant  varIndex( lpszFrameName1) ;
			CComVariant  varResult ;
			if (lpszFrameName1)
				pFrameCollection2->item(&varIndex, &varResult);

			CComQIPtr<IHTMLWindow2> pWindow2 ;
			if (lpszFrameName1)
				varResult.pdispVal->QueryInterface(IID_IHTMLWindow2, (void**) &pWindow2);

			CComQIPtr<IHTMLDocument2> pDoc3 ;
			if (lpszFrameName1)
				pWindow2->get_document(&pDoc3);

			if (lpszFrameName1)
				pDocument = pDoc3 ;
			else if (lpszFrameName0)
				pDocument = pDoc2 ;
			else
				pDocument = pDoc ;
		}
	}

	return pDocument;
}

CComQIPtr<IHTMLElement> CTradeConsoleDlg::GetWebBrowser2Element(CWebBrowser2& WebBrowser2, LPCTSTR lpszFrameName0, LPCTSTR lpszFrameName1, LPCTSTR lpszAttributeName, LPCTSTR lpszName, int nIndex)
{
	CComQIPtr<IHTMLElement> pElement ;

	// document の取得
	CComQIPtr<IHTMLDocument2> pDoc = GetWebBrowser2Document(WebBrowser2, lpszFrameName0, lpszFrameName1);

	// all の取得
	CComPtr<IHTMLElementCollection> pCol ;
	pDoc->get_all( &pCol) ;
	long lSize ;
	pCol->get_length( &lSize);

	if( lSize != 0)
	{
		if (lpszAttributeName == NULL  ||  stricmp(lpszAttributeName, "name") == 0  ||  stricmp(lpszAttributeName, "id") == 0) {
			CComVariant  vintName( lpszName) ;
			CComVariant  vintIndex( nIndex) ;
			CComPtr<IDispatch>  pdsp2 ;
			if (pCol->item( vintName, vintIndex, &pdsp2) == S_OK  &&  pdsp2)
				pElement = pdsp2 ;
		}
		if (pElement == NULL) {
			USES_CONVERSION ;

			// all の内容をリストアップ
			for( int j = 0; j < 2; j++) {
				int nItemIndex = 0;
				for( long i = 0; i < lSize; i++)
				{
					CComQIPtr<IHTMLElement> pElement2 ;
					CComVariant  vintName( i) ;
					CComVariant  vintIndex( 0) ;
					CComPtr<IDispatch>  pdsp2 ;
					if (pCol->item( vintName, vintIndex, &pdsp2) == S_OK  &&  pdsp2) {
						pElement2 = pdsp2 ;

						// href が lpszName なら
						CComVariant  AttributeValue ;
						HRESULT hr = pElement2->getAttribute((CComBSTR)lpszAttributeName, 0, &AttributeValue) ;
						if (hr == S_OK && AttributeValue.vt == VT_BSTR) {
							char* pszBuf = AttributeValue.bstrVal ? OLE2T( AttributeValue.bstrVal) : "" ;
							if( j == 0 && strcmp( pszBuf, lpszName) == 0 || j && strstr( pszBuf, lpszName))
							{
								if (nItemIndex ++ == nIndex) {
									pElement = pElement2;
									break;
								}
							}
						}
					}
				}
				if (pElement)
					break;
			}
		}
	}

	return pElement;
}

void CTradeConsoleDlg::SetWebBrowser2(CWebBrowser2& WebBrowser2, LPCTSTR lpszFrameName0, LPCTSTR lpszFrameName1, LPCTSTR lpszAttributeName0, LPCTSTR lpszName, int nIndex, LPCTSTR lpszAttributeName1, LPCTSTR lpszValue)
{
	WaitWebBrowser2Ready(WebBrowser2);
	CComQIPtr<IHTMLElement> pElement = GetWebBrowser2Element(WebBrowser2, lpszFrameName0, lpszFrameName1, lpszAttributeName0, lpszName, nIndex);
	if (pElement)
		pElement->setAttribute((CComBSTR)lpszAttributeName1, (CComVariant)lpszValue, 0) ;
}

CString CTradeConsoleDlg::GetWebBrowser2(CWebBrowser2& WebBrowser2, LPCTSTR lpszFrameName0, LPCTSTR lpszFrameName1, LPCTSTR lpszAttributeName0, LPCTSTR lpszName, int nIndex, LPCTSTR lpszAttributeName1)
{
	CString strValue;

	WaitWebBrowser2Ready(WebBrowser2);
	CComQIPtr<IHTMLElement> pElement = GetWebBrowser2Element(WebBrowser2, lpszFrameName0, lpszFrameName1, lpszAttributeName0, lpszName, nIndex);
	CComVariant  AttributeValue ;
	if (pElement && pElement->getAttribute((CComBSTR)lpszAttributeName1, 0, &AttributeValue) == S_OK && AttributeValue.vt == VT_BSTR)
		strValue = AttributeValue.bstrVal;

	return strValue;
}

BOOL CTradeConsoleDlg::ClickWebBrowser2(CWebBrowser2& WebBrowser2, LPCTSTR lpszFrameName0, LPCTSTR lpszFrameName1, LPCTSTR lpszAttributeName, LPCTSTR lpszName, int nIndex)
{
	WaitWebBrowser2Ready(WebBrowser2);
	CComQIPtr<IHTMLElement> pElement = GetWebBrowser2Element(WebBrowser2, lpszFrameName0, lpszFrameName1, lpszAttributeName, lpszName, nIndex);
	return pElement ? pElement->click() == S_OK : FALSE;
}

void CTradeConsoleDlg::GoBackWebBrowser2(CWebBrowser2& WebBrowser2)
{
	WaitWebBrowser2Ready(WebBrowser2);
	WebBrowser2.GoBack();
}

CString CTradeConsoleDlg::GetBodyHtmlWebBrowser2(CWebBrowser2& WebBrowser2, LPCTSTR lpszFrameName0, LPCTSTR lpszFrameName1)
{
	USES_CONVERSION ;

	// document の取得
	CComQIPtr<IHTMLDocument2> pDoc = GetWebBrowser2Document(WebBrowser2, lpszFrameName0, lpszFrameName1);

	// body の取得
	CComQIPtr<IHTMLElement> pElement ;
	pDoc->get_body(&pElement);

	CComBSTR bstrHtml;
	pElement->get_innerHTML(&bstrHtml);
	return bstrHtml ? OLE2T( bstrHtml) : "" ;
}

void CTradeConsoleDlg::Buy()
{
	CString strHtml = GetBodyHtmlWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm");
	strHtml.Replace("\r", pszEmpty);
	int nDummyReceiptNo = m_DwaBuyReceiptNo[0];
	int nReceiptNo;
	int nPtr0;
	int nPtr1;
	if ((nPtr0 = strHtml.Find("ご注文を承りました。")) != -1  ||  (nPtr0 = strHtml.Find("ご注文予約を承りました。")) != -1)
		if ((nPtr0 = strHtml.Find("受付番号　", nPtr0)) != -1  &&  (nPtr1 = strHtml.Find('<', nPtr0)) != -1) {
			nPtr0 += sizeof("受付番号　") - 1;
			nReceiptNo = atoi(strHtml.Mid(nPtr0, nPtr1 - nPtr0));
		} else
			nReceiptNo = -2;
	else
		nReceiptNo = -1;

	CWnd* pWnd;
	if ((pWnd = FindWindow(NULL, m_strTradeHelperWndName)) != NULL)
		pWnd->PostMessage(WM_USER + 8, nDummyReceiptNo, nReceiptNo);

	m_DwaBuyReceiptNo.RemoveAt(0);
	m_DwaBuySuryo.RemoveAt(0);
	m_DwaBuyKakaku.RemoveAt(0);
}

BOOL CTradeConsoleDlg::GetState(int nMode)
{
	CString strHtml = GetBodyHtmlWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm");
	strHtml.Replace("\r", pszEmpty);
	if (nMode == 0)
		m_SaGetStateOrderList.Add(strHtml);
	else
		m_SaGetStateSoldList.Add(strHtml);
	BOOL bNext = strHtml.Find("次へ") != -1;
	if (bNext)
		return FALSE;
//	if (nMode == 0)
//		return TRUE;
	int i;
	int imax;
	long lZan;
	CUIntArray UiaStatus;
	CDWordArray DwaSuryo;
	CDWordArray DwaPrice;
	CDWordArray DwaSoldSuryo;
	CDWordArray DwaSoldPrice;
	LPARAM lParam = 0;
	try {
		int j;
		int jmax;
		int nPtr0;
		CHtmlTokenizer HtmlTokenizer;
		CString strTag;
		CString strValue;
		long lReceiptNo;
		int nStatus;
		long lSuryo;
		long lPrice;
		long lSoldSuryo;
		long lSoldPrice;

		m_DwaGetStateReceiptNo.RemoveAll();
		strHtml = m_SaGetStateOrderList[0];

		if ((nPtr0 = strHtml.Find("買付余力")) == -1)
			throw 0;
		if ((nPtr0 = StrFindNoCase(strHtml, "<td ", nPtr0)) == -1)
			throw 0;
		HtmlTokenizer.SetHtml(strHtml);
		HtmlTokenizer.m_nHtmlPtr = nPtr0;
		for (j = 0; j < 2; j ++)
			if (HtmlTokenizer.HtmlTok() == 0)
				throw 0;
		strTag = HtmlTokenizer.m_strTag;
		strTag.Replace("&nbsp;", pszEmpty);
		strTag.Replace(",", pszEmpty);
		lZan = atol(strTag);

		for (i = 0, imax = m_SaGetStateOrderList.GetSize(); i < imax; i ++) {
			strHtml = m_SaGetStateOrderList[i];

			if ((nPtr0 = strHtml.Find("口座")) == -1)
				break;
			HtmlTokenizer.SetHtml(strHtml);
			while (1) {
				nStatus = 0;

				if ((nPtr0 = StrFindNoCase(strHtml, "<tr ", nPtr0)) == -1)
					break;
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				if (HtmlTokenizer.HtmlTok() == 0)
					throw 0;
				if (HtmlTokenizer.FindTagAttr("class", strValue) != 2)
					break;
				if (StrQTrim(strValue) != "body")
					break;
				if ((nPtr0 = StrFindNoCase(strHtml, "<td ", nPtr0)) == -1)
					throw 0;
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				for (j = 0; j < 4; j ++)
					if (HtmlTokenizer.HtmlTok() == 0)
						throw 0;
				strTag = HtmlTokenizer.m_strTag;
				if (strTag == "取消済")
					nStatus |= 0x1;
				else if (strTag == "訂正中")
					nStatus |= 0x4;
				nPtr0 = HtmlTokenizer.m_nHtmlPtr;
				for (j = 0; j < 4; j ++)
					if ((nPtr0 = StrFindNoCase(strHtml, "<td ", nPtr0 + 1)) == -1)
						throw 0;
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				for (j = 0; j < 2; j ++)
					if (HtmlTokenizer.HtmlTok() == 0)
						throw 0;
				strTag = HtmlTokenizer.m_strTag;
				strTag.Replace(",", pszEmpty);
				lSuryo = atol(strTag);
				nPtr0 = HtmlTokenizer.m_nHtmlPtr;
				if ((nPtr0 = StrFindNoCase(strHtml, "<td ", nPtr0)) == -1)
					throw 0;
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				for (j = 0; j < 2; j ++)
					if (HtmlTokenizer.HtmlTok() == 0)
						throw 0;
				strTag = HtmlTokenizer.m_strTag;
				if (strTag == "成行")
					lPrice = -1;
				else {
					strTag.Replace("指値", pszEmpty);
					strTag.Replace("&nbsp;", pszEmpty);
					strTag.Replace(",", pszEmpty);
					lPrice = atol(strTag);
				}
				nPtr0 = HtmlTokenizer.m_nHtmlPtr;
				for (j = 0; j < 2; j ++)
					if ((nPtr0 = StrFindNoCase(strHtml, "<td ", nPtr0 + 1)) == -1)
						throw 0;
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				for (j = 0; j < 2; j ++)
					if (HtmlTokenizer.HtmlTok() == 0)
						throw 0;
				strTag = HtmlTokenizer.m_strTag;
				lReceiptNo = atol(strTag);
				nPtr0 = HtmlTokenizer.m_nHtmlPtr;

				if ((nPtr0 = StrFindNoCase(strHtml, "<tr ", nPtr0)) == -1)
					throw 0;
				for (j = 0; j < 2; j ++)
					if ((nPtr0 = StrFindNoCase(strHtml, "<td ", nPtr0 + 1)) == -1)
						throw 0;
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				for (j = 0; j < 2; j ++)
					if (HtmlTokenizer.HtmlTok() == 0)
						throw 0;
				strTag = HtmlTokenizer.m_strTag;
				strTag.Replace(",", pszEmpty);
				if (lSoldSuryo = atol(strTag))
					nStatus |= 0x2;
				nPtr0 = HtmlTokenizer.m_nHtmlPtr;

				m_DwaGetStateReceiptNo.Add(lReceiptNo);
				UiaStatus.Add(nStatus);
				DwaSuryo.Add(lSuryo);
				DwaPrice.Add(lPrice);
				DwaSoldSuryo.Add(lSoldSuryo);
				DwaSoldPrice.Add(lPrice);
			}
		}

		for (i = 0, imax = m_SaGetStateSoldList.GetSize(); i < imax; i ++) {
			strHtml = m_SaGetStateSoldList[i];

			if ((nPtr0 = strHtml.Find("口座")) == -1)
				break;
			HtmlTokenizer.SetHtml(strHtml);
			while (1) {
				if ((nPtr0 = StrFindNoCase(strHtml, "<tr ", nPtr0 + 1)) == -1)
					break;
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				if (HtmlTokenizer.HtmlTok() == 0)
					throw 0;
				if (HtmlTokenizer.FindTagAttr("class", strValue) != 2)
					break;
				if (StrQTrim(strValue) != "body")
					break;
				for (j = 0; j < 6; j ++)
					if ((nPtr0 = StrFindNoCase(strHtml, "<td ", nPtr0 + 1)) == -1)
						throw 0;
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				for (j = 0; j < 2; j ++)
					if (HtmlTokenizer.HtmlTok() == 0)
						throw 0;
				strTag = HtmlTokenizer.m_strTag;
				strTag.Replace(",", pszEmpty);
				lSoldPrice = atol(strTag);
				nPtr0 = HtmlTokenizer.m_nHtmlPtr;
				for (j = 0; j < 2; j ++)
					if ((nPtr0 = StrFindNoCase(strHtml, "<td ", nPtr0 + 1)) == -1)
						throw 0;
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				for (j = 0; j < 2; j ++)
					if (HtmlTokenizer.HtmlTok() == 0)
						throw 0;
				strTag = HtmlTokenizer.m_strTag;
				lReceiptNo = atol(strTag);
				nPtr0 = HtmlTokenizer.m_nHtmlPtr;

				if ((nPtr0 = StrFindNoCase(strHtml, "<tr ", nPtr0)) == -1)
					throw 0;

				for (j = 0, jmax = m_DwaGetStateReceiptNo.GetSize(); j < jmax; j ++)
					if ((long)m_DwaGetStateReceiptNo[j] == lReceiptNo) {
						DwaSoldPrice[j] = lSoldPrice;
						break;
					}
			}
		}
	}
	catch (int) {
		lParam = -1;
	}

	CWnd* pWnd;
	if ((pWnd = FindWindow(NULL, m_strTradeHelperWndName)) != NULL) {
		for (i = 0, imax = m_DwaGetStateReceiptNo.GetSize(); i < imax; i ++) {
			pWnd->PostMessage(WM_USER + 9, m_DwaGetStateReceiptNo[i], UiaStatus[i]);
			pWnd->PostMessage(WM_USER + 9, DwaSuryo[i], DwaPrice[i]);
			pWnd->PostMessage(WM_USER + 9, DwaSoldSuryo[i], DwaSoldPrice[i]);
		}
		pWnd->PostMessage(WM_USER + 10, lZan, lParam);
	}

	m_SaGetStateOrderList.RemoveAll();
	m_SaGetStateSoldList.RemoveAll();

	return TRUE;
}

int CTradeConsoleDlg::GetChkItem(long lReceiptNo)
{
	int nRv = -1;
	for (int i = 0, imax = m_DwaGetStateReceiptNo.GetSize(); i < imax; i ++)
		if ((long)m_DwaGetStateReceiptNo[i] == lReceiptNo) {
			nRv = i;
			break;
		}
	return nRv;
}

void CTradeConsoleDlg::DelOdr(long lReceiptNo)
{
	CString strHtml = GetBodyHtmlWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm");
	strHtml.Replace("\r", pszEmpty);
	LPARAM lParam;
	int nPtr0;
	if ((nPtr0 = strHtml.Find("取消を承りました")) != -1  ||  (nPtr0 = strHtml.Find("予約注文の取消を承りました。")) != -1)
		lParam = 0;
	else
		lParam = -1;

	CWnd* pWnd;
	if ((pWnd = FindWindow(NULL, m_strTradeHelperWndName)) != NULL)
		pWnd->PostMessage(WM_USER + 11, lReceiptNo, lParam);
}

void CTradeConsoleDlg::ChangeOdr(int nMode, int nStatus)
{
	CString strHtml = GetBodyHtmlWebBrowser2(m_WebBrowser21, "dmmain_frm", "main_frm");
	strHtml.Replace("\r", pszEmpty);
	LPARAM lParam;
	int nPtr0;
	if ((nPtr0 = strHtml.Find("ご注文の訂正を承りました")) != -1  ||  (nPtr0 = strHtml.Find("予約注文の訂正を承りました。")) != -1)
		lParam = 0;
	else
		lParam = -1;

	if (nMode == 0  &&  (nStatus & 0x2)  &&  lParam == 0)
		return;

	CWnd* pWnd;
	if ((pWnd = FindWindow(NULL, m_strTradeHelperWndName)) != NULL) {
		pWnd->PostMessage(WM_USER + 12, m_DwaChangeOdrReceiptNo[0], lParam);
		pWnd->PostMessage(WM_USER + 13, m_DwaChangeOdrSuryo[0], m_DwaChangeOdrKakaku[0]);
	}

	m_DwaChangeOdrReceiptNo.RemoveAt(0);
	m_DwaChangeOdrSuryo.RemoveAt(0);
	m_DwaChangeOdrKakaku.RemoveAt(0);
}

// TradeHelperDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "TradeHelper.h"
#include "TradeHelperDlg.h"

#include <afxdao.h>
#include "webbrowser2.h"
#include "../Common.h"
#include "../License.h"
#include "../Html.h"
#include "../AutoTraderDef.h"
#include "TradeHelperDef.h"
#include "LoginDlg.h"
#include "RemitRegDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTradeHelperDlg ダイアログ

CTradeHelperDlg::CTradeHelperDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTradeHelperDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTradeHelperDlg)
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nWMUserTimer = 100;
	m_bUserCall = FALSE;
	m_hStockAveBeepThread = NULL;
	m_pDispWB2Thread2 =
	m_pDispWB2Thread3 =
		NULL;
	m_pDispStockAveThread =
		NULL;
	m_pDispRankingThread0 =
	m_pDispRankingThread1 =
	m_pDispRankingThread2 =
		NULL;
	m_pDispNewsThread0 =
	m_pDispNewsThread1 =
		NULL;
	m_bInitDialog =
	m_bSelchangeList3 =
	m_bUser3 =
//	m_bStockAveThread =
	m_bDisp =
	m_bShift =
	m_bCtrl =
	m_bChkThreadTimerRun =
	m_bSetFocusEdit1 =
	m_bLicenseCanceled =
		FALSE;
	m_nList2CurSel =
	m_nList3CurSel =
	m_nList2PreCurSel =
		LB_ERR;
	m_nDispStockAveThreadTimeoutCount =
	m_nSetStreamer =
	m_nSelStreamer =
		0;
	m_lZan = -1L;
	m_nDummyReceiptNo = -1;
	m_hHook = NULL;
	for (int i = 0; ppszUrlLogin[i]; i ++)
		m_ppSession[i] = NULL;
}

void CTradeHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTradeHelperDlg)
	DDX_Control(pDX, IDC_BUTTON15, m_Btn15);
	DDX_Control(pDX, IDC_CHECK1, m_Check1);
	DDX_Control(pDX, IDC_CHECK2, m_Check2);
	DDX_Control(pDX, IDC_CHECK3, m_Check3);
	DDX_Control(pDX, IDC_CHECK4, m_Check4);
	DDX_Control(pDX, IDC_CHECK5, m_Check5);
	DDX_Control(pDX, IDC_CHECK6, m_Check6);
	DDX_Control(pDX, IDC_CHECK7, m_Check7);
	DDX_Control(pDX, IDC_CHECK8, m_Check8);
	DDX_Control(pDX, IDC_CHECK9, m_Check9);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_EDIT3, m_Edit3);
	DDX_Control(pDX, IDC_EDIT4, m_Edit4);
	DDX_Control(pDX, IDC_EDIT5, m_Edit5);
	DDX_Control(pDX, IDC_EDIT6, m_Edit6);
	DDX_Control(pDX, IDC_EDIT7, m_Edit7);
	DDX_Control(pDX, IDC_EDIT8, m_Edit8);
	DDX_Control(pDX, IDC_EDIT9, m_Edit9);
	DDX_Control(pDX, IDC_EDIT10, m_Edit10);
	DDX_Control(pDX, IDC_EDIT11, m_Edit11);
	DDX_Control(pDX, IDC_EDIT12, m_Edit12);
	DDX_Control(pDX, IDC_EDIT13, m_Edit13);
	DDX_Control(pDX, IDC_EDIT14, m_Edit14);
	DDX_Control(pDX, IDC_EDIT15, m_Edit15);
	DDX_Control(pDX, IDC_EDIT16, m_Edit16);
	DDX_Control(pDX, IDC_EDIT17, m_Edit17);
	DDX_Control(pDX, IDC_EDIT18, m_Edit18);
	DDX_Control(pDX, IDC_EDIT19, m_Edit19);
	DDX_Control(pDX, IDC_LIST1, m_List1);
	DDX_Control(pDX, IDC_LIST2, m_List2);
	DDX_Control(pDX, IDC_LIST3, m_List3);
	DDX_Control(pDX, IDC_LIST4, m_List4);
	DDX_Control(pDX, IDC_LIST5, m_List5);
	DDX_Control(pDX, IDC_LIST6, m_List6);
	DDX_Control(pDX, IDC_LIST7, m_List7);
	DDX_Control(pDX, IDC_LIST8, m_List8);
	DDX_Control(pDX, IDC_EXPLORER1, m_WebBrowser21);
	DDX_Control(pDX, IDC_EXPLORER2, m_WebBrowser22);
	DDX_Control(pDX, IDC_EXPLORER3, m_WebBrowser23);
	DDX_Control(pDX, IDC_EXPLORER4, m_WebBrowser24);
	DDX_Control(pDX, IDC_EXPLORER5, m_WebBrowser25);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_MonthCalCtrl1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTradeHelperDlg, CDialog)
	//{{AFX_MSG_MAP(CTradeHelperDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON13, OnButton13)
	ON_BN_CLICKED(IDC_BUTTON14, OnButton14)
	ON_BN_CLICKED(IDC_BUTTON15, OnButton15)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_SETFOCUS(IDC_EDIT1, OnSetfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_LBN_SELCHANGE(IDC_LIST2, OnSelchangeList2)
	ON_LBN_SELCHANGE(IDC_LIST3, OnSelchangeList3)
	ON_LBN_SELCHANGE(IDC_LIST4, OnSelchangeList4)
	ON_LBN_SELCHANGE(IDC_LIST5, OnSelchangeList5)
	ON_LBN_SELCHANGE(IDC_LIST6, OnSelchangeList6)
	ON_LBN_SELCHANGE(IDC_LIST7, OnSelchangeList7)
	ON_LBN_SELCHANGE(IDC_LIST8, OnSelchangeList8)
	ON_LBN_DBLCLK(IDC_LIST6, OnDblclkList6)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_BN_CLICKED(IDC_RADIO8, OnRadio8)
	ON_BN_CLICKED(IDC_RADIO9, OnRadio9)
	ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
	ON_BN_CLICKED(IDC_RADIO11, OnRadio11)
	ON_BN_CLICKED(IDC_RADIO12, OnRadio12)
	ON_BN_CLICKED(IDC_RADIO13, OnRadio13)
	ON_BN_CLICKED(IDC_RADIO14, OnRadio14)
	ON_BN_CLICKED(IDC_RADIO15, OnRadio15)
	ON_BN_CLICKED(IDC_RADIO16, OnRadio16)
	ON_BN_CLICKED(IDC_RADIO17, OnRadio17)
	ON_BN_CLICKED(IDC_RADIO18, OnRadio18)
	ON_BN_CLICKED(IDC_RADIO19, OnRadio19)
	ON_BN_CLICKED(IDC_RADIO20, OnRadio20)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, OnSelchangeMonthcalendar1)
	//}}AFX_MSG_MAP
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	ON_MESSAGE(WM_USER, OnUser)
	ON_MESSAGE(WM_USER + 1, OnUser1)
	ON_MESSAGE(WM_USER + 2, OnUser2)
	ON_MESSAGE(WM_USER + 3, OnUser3)
	ON_MESSAGE(WM_USER + 4, OnUser4)
	ON_MESSAGE(WM_USER + 5, OnUser5)
	ON_MESSAGE(WM_USER + 6, OnUser6)
	ON_MESSAGE(WM_USER + 7, OnUser7)
	ON_MESSAGE(WM_USER + 8, OnUser8)
	ON_MESSAGE(WM_USER + 9, OnUser9)
	ON_MESSAGE(WM_USER + 10, OnUser10)
	ON_MESSAGE(WM_USER + 11, OnUser11)
	ON_MESSAGE(WM_USER + 12, OnUser12)
	ON_MESSAGE(WM_USER + 13, OnUser13)
	ON_MESSAGE(WM_USER + 14, OnUser14)
	ON_MESSAGE(WM_USER + 15, OnUser15)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTradeHelperDlg メッセージ ハンドラ

BOOL CTradeHelperDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。

	SetWindowText(m_strTradeHelperWndName);

	ModifyStyle(WS_CAPTION, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);

	CRect RectWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, NULL, &RectWorkArea, 0);

	CRect RectDlg;
	::GetWindowRect(m_hWnd, &RectDlg);

//	RectDlg.DeflateRect(0, 0, 0, 26);

//	RectDlg.OffsetRect(0, RectWorkArea.Height() - RectDlg.Height());
//	RectDlg.OffsetRect(- RectDlg.left, - RectDlg.top + 542);
	RectDlg.OffsetRect(- RectDlg.left, - RectDlg.top + 516);
//	RectDlg.right = 1000;
	RectDlg.right = 1003;
	RectDlg.bottom = RectWorkArea.bottom;
	MoveWindow(&RectDlg);

	ShowWindow(SW_SHOW);
	UpdateWindow();

	CHtmlTokenizer HtmlTokenizer;
	CStringTokenizer StringTokenizer;
	CStringBuffer sbTag;
	CStringBuffer sbValue;
	int i;
	CMapStringToString MstsSearch;
	CString strFPath;
	CString strLine;
	CString strCode;
	CString strName;
	CString strSijo;
	BOOL bData;
	int nPtr0;
	int nPtr1;
	CDaoDatabase Database;
	COleVariant pKeyArray[2];
	COleVariant var;
	COleDateTime DtCur;
	COleDateTime DtDate;
	int nMonth;
	int nDay;
	int nDayOfWeek;
	int nDayOfWeekWork;
	int nContractYear0;
	int nContractMonth0;
	int nContractYear1;
	int nContractMonth1;

	m_List6.SetHorizontalExtent(1024);

	LOGFONT LfCtrl;
	m_List1.GetFont()->GetLogFont(&LfCtrl);
	LfCtrl.lfHeight = -75;
	m_FontListBox.CreatePointFontIndirect(&LfCtrl);
	m_Edit17.SetFont(&m_FontListBox);
	m_List1.SetFont(&m_FontListBox);
	m_List2.SetFont(&m_FontListBox);
	m_List3.SetFont(&m_FontListBox);
	m_List4.SetFont(&m_FontListBox);
	m_List5.SetFont(&m_FontListBox);
	m_List6.SetFont(&m_FontListBox);
	m_List7.SetFont(&m_FontListBox);
	m_List8.SetFont(&m_FontListBox);

	CheckRadioButton(IDC_RADIO1, IDC_RADIO9, IDC_RADIO2);
	CheckRadioButton(IDC_RADIO10, IDC_RADIO11, IDC_RADIO10);
	CheckRadioButton(IDC_RADIO12, IDC_RADIO20, IDC_RADIO12);

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
		|| m_strDataDir.IsEmpty()
	) {
		MessageBox("ID、パスワード未設定エラー", NULL, MB_ICONSTOP);
		PostQuitMessage(0);
		return TRUE;
	}

/*
	CLoginDlg LoginDlg;
	if (LoginDlg.DoModal() == IDOK) {
		if (LoginDlg.m_strPasswd != m_strTreasurePasswd) {
			MessageBox("パスワードが正しくありません", NULL, MB_ICONSTOP);
			PostQuitMessage(0);
			return TRUE;
		}
	} else {
		PostQuitMessage(0);
		return TRUE;
	}
*/

	GetTempPath(MAX_PATH, m_strTempDir.GetBuffer(MAX_PATH));
	m_strTempDir.ReleaseBuffer();
//	m_strTempCompressDir = m_strTempDir + "Compress";

	m_pServer = NULL;
	m_sbCosmoLoginUrl = URL_LOGIN2;
	m_sbCosmoQuoteUrl = URL_COSMOQUOTE;
	if (m_nExecMode)
		m_strMeigaraIniFPath = m_strDataDir + "\\" FNAME_MEIGARARTS;
	else
		m_strMeigaraIniFPath = m_strDataDir + "\\" FNAME_MEIGARA;
	m_strNewsIniFPath = m_strDataDir + "\\" FNAME_NEWS;
	m_nNewsCount = 0;
	if (m_nExecMode == 2)
//		m_strDBFPath = m_strTempCompressDir + "\\" FNAME_RTSDB;
		m_strDBFPath = m_strTempDir + FNAME_RTSDB;
	else {
//		m_strDBFPath = m_strTempCompressDir + "\\" FNAME_DB;
		m_strDBFPath = m_strTempDir + FNAME_DB;
		if (! CFile::GetStatus(m_strDBFPath, m_FileStatus))
			m_strDBFPath = m_strDataDir + "\\" FNAME_DB;
	}
	CString strFName;
#ifdef LOGNAME_THREADID
	strFName.Format(TRADEHELPER_EXENAME "Ranking%s%d.txt", COleDateTime::GetCurrentTime().Format("%Y%m%d"), AfxGetThread()->m_nThreadID);
#else
	strFName.Format(TRADEHELPER_EXENAME "Ranking%s.txt", COleDateTime::GetCurrentTime().Format("%Y%m%d"));
#endif
	m_strRankingFPath = m_strDataDir + "\\Log\\" + strFName;
	m_strTempRankingFPath = m_strTempDir + strFName;
#ifdef LOGNAME_THREADID
	strFName.Format(TRADEHELPER_EXENAME "AllRanking%s%d.txt", COleDateTime::GetCurrentTime().Format("%Y%m%d"), AfxGetThread()->m_nThreadID);
#else
	strFName.Format(TRADEHELPER_EXENAME "AllRanking%s.txt", COleDateTime::GetCurrentTime().Format("%Y%m%d"));
#endif
	m_strRankingAllFPath = m_strDataDir + "\\Log\\" + strFName;
	m_strTempRankingAllFPath = m_strTempDir + strFName;

	strFPath = m_strDataDir + "\\" FNAME_NEWS;
	if (CFile::GetStatus(strFPath, m_FileStatus))
		if (! DeleteFile(strFPath)) {
			DispErrorLog("適時開示速報ファイル削除エラー: %s\n", GetLastErrorMessage());
			goto CleanUp;
		}

#ifndef LOGNAME_THREADID
	strFPath.Format("%s\\Log\\" TRADEHELPER_EXENAME "%s.txt", m_strDataDir, COleDateTime::GetCurrentTime().Format("%Y%m%d"));
	{
		CStdioFile StdioFile(strFPath, CFile::modeCreate | CFile::modeWrite);
		StdioFile.Close();
	}
#endif
	
	try
	{
		for (i = 0; ppszUrlLogin[i]; i ++) {
			if (i == 0) continue;
			if (m_bMentenance1  &&  i == 1) continue;

//			switch (i) {
//			default:
				DispLog("%s 初期化ダウンロード - 松井証券\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
//			}

			if (! AfxParseURL(ppszUrlLogin[i], m_dwServiceType, m_strServerName, m_strObject, m_nPort) || m_dwServiceType != AFX_INET_SERVICE_HTTPS) {
				DispErrorLog("URL 解析エラー: %s\n", ppszUrlLogin[i]);
				goto CleanUp;
			}

			m_ppSession[i] = new CInternetSession(_T("Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; Trident/4.0; GTB6.6; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.1; .NET4.0C)"));

			m_ppSession[i]->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 10000);
			m_ppSession[i]->SetOption(INTERNET_OPTION_CONTROL_SEND_TIMEOUT, 10000);
			m_ppSession[i]->SetOption(INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT, 10000);
			m_ppSession[i]->SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 10000);
			m_ppSession[i]->SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 10000);
			m_ppSession[i]->SetOption(INTERNET_OPTION_LISTEN_TIMEOUT, 10000);
			m_ppSession[i]->SetOption(INTERNET_OPTION_DISCONNECTED_TIMEOUT, 10000);

			m_pServer = m_ppSession[i]->GetHttpConnection(m_strServerName, m_nPort);

			if (DlHtml(CHttpConnection::HTTP_VERB_GET, INTERNET_FLAG_SECURE))
				goto CleanUp;

//			if (ppszObjLogin[i])
				m_strObject = ppszObjLogin[i];
//			switch (i) {
//			default:
				m_sbOptional.Format(ppszOptLogin[i], m_strMatsuiId, m_strMatsuiPasswd);
//			}
			if (DlHtml(CHttpConnection::HTTP_VERB_POST, INTERNET_FLAG_SECURE, HEA_POST, m_sbOptional))
				goto CleanUp;

			bData = FALSE;

			switch (i) {
			case 1:
				if ((nPtr0 = StrFindNoCase(m_sbHtml, "<FRAME ")) == -1)
					goto DataCleanUp1;
				HtmlTokenizer.SetHtml(m_sbHtml);
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				if (! HtmlTokenizer.HtmlTok())
					goto DataCleanUp1;
				if (HtmlTokenizer.FindTagAttr("src", sbValue) != 2)
					goto DataCleanUp1;
				m_strObject = StrQTrim(sbValue);
				if ((nPtr0 = m_strObject.Find(';')) == -1)
					goto DataCleanUp1;
				m_strObject = OBJ_QUICKREAD + m_strObject.Mid(nPtr0, m_strObject.ReverseFind('?') - nPtr0) + "?" OPT_QUICKREAD;
				if (DlHtml(CHttpConnection::HTTP_VERB_GET))
					goto CleanUp;
				if ((nPtr0 = StrFindNoCase(m_sbHtml, "<FORM ")) == -1)
					goto DataCleanUp1;
				HtmlTokenizer.SetHtml(m_sbHtml);
				HtmlTokenizer.m_nHtmlPtr = nPtr0;
				if (! HtmlTokenizer.HtmlTok())
					goto DataCleanUp1;
				if (HtmlTokenizer.FindTagAttr("action", sbValue) != 2)
					goto DataCleanUp1;
				sbValue = StrQTrim(sbValue);
				if ((nPtr0 = StrReverseFindEx(sbValue, "/qsearch.exe")) == -1)
					goto DataCleanUp1;
				sbValue.Delete(nPtr0 + 1, sbValue.GetLength());
				m_sbQuickInfoUrl = sbValue;
			}

			bData = TRUE;

DataCleanUp1:
			if (! bData) {
				DispErrorLog("「QUICK情報」リンク取得エラー\n");
				goto CleanUp;
			}

			m_pServer->Close();
			delete m_pServer;
			m_pServer = NULL;
		}

		if (! m_bMentenance2) {
			DispLog("%s 初期化ダウンロード - コスモ証券\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));

			m_SessionCosmo.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 10000);
			m_SessionCosmo.SetOption(INTERNET_OPTION_CONTROL_SEND_TIMEOUT, 10000);
			m_SessionCosmo.SetOption(INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT, 10000);
			m_SessionCosmo.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 10000);
			m_SessionCosmo.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 10000);
			m_SessionCosmo.SetOption(INTERNET_OPTION_LISTEN_TIMEOUT, 10000);
			m_SessionCosmo.SetOption(INTERNET_OPTION_DISCONNECTED_TIMEOUT, 10000);

			if (! AfxParseURL(m_sbCosmoLoginUrl, m_dwServiceType, m_strServerName, m_strObject, m_nPort) || m_dwServiceType != AFX_INET_SERVICE_HTTPS) {
				DispErrorLog("URL 解析エラー: %s\n", m_sbCosmoLoginUrl);
				goto CleanUp;
			}

			m_pServer = m_SessionCosmo.GetHttpConnection(m_strServerName, m_nPort);

			if (DlHtml(CHttpConnection::HTTP_VERB_GET, INTERNET_FLAG_SECURE))
				goto CleanUp;

			bData = FALSE;

			if ((nPtr0 = m_sbHtml.Find("JSESSIONID")) == -1)
				goto DataCleanUp2;
			if ((nPtr0 = StrReverseFindEx(m_sbHtml, "<INPUT ", nPtr0, true)) == -1)
				goto DataCleanUp2;
			HtmlTokenizer.SetHtml(m_sbHtml);
			HtmlTokenizer.m_nHtmlPtr = nPtr0;
			if (! HtmlTokenizer.HtmlTok())
				goto DataCleanUp2;
			if (HtmlTokenizer.FindTagAttr("value", sbValue) != 2)
				goto DataCleanUp2;
			sbValue = StrQTrim(sbValue);

			bData = TRUE;

DataCleanUp2:
			if (! bData) {
				DispErrorLog("JSESSIONID取得エラー\n");
				goto CleanUp;
			}

			m_sbOptional.Format(OPT_LOGIN2, sbValue, m_strCosmoId, m_strCosmoPasswd);

			if (DlHtml(CHttpConnection::HTTP_VERB_POST, INTERNET_FLAG_SECURE, HEA_POST, m_sbOptional))
				goto CleanUp;

			bData = FALSE;

			if ((nPtr0 = m_sbHtml.Find("cb_hashcheck.aspx")) == -1)
				goto DataCleanUp3;
			if ((nPtr0 = StrReverseFindEx(m_sbHtml, "<A ", nPtr0, true)) == -1)
				goto DataCleanUp3;
			HtmlTokenizer.SetHtml(m_sbHtml);
			HtmlTokenizer.m_nHtmlPtr = nPtr0;
			if (! HtmlTokenizer.HtmlTok())
				goto DataCleanUp3;
			if (HtmlTokenizer.FindTagAttr("onClick", sbValue) != 2)
				goto DataCleanUp3;
			nPtr0 = sbValue.Find('\'');
			nPtr1 = sbValue.ReverseFind('\'');
			sbValue = sbValue.Mid(nPtr0 + 1, nPtr1 - nPtr0 - 2);

			bData = TRUE;

DataCleanUp3:
			if (! bData) {
				DispErrorLog("「マーケットサーチ」リンク取得エラー\n");
				goto CleanUp;
			}

			m_pServer->Close();
			delete m_pServer;
			m_pServer = NULL;

			if (! AfxParseURL(sbValue, m_dwServiceType, m_strServerName, m_strObject, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
				DispErrorLog("URL 解析エラー: %s\n", sbValue);
				goto CleanUp;
			}

			m_pServer = m_SessionCosmo.GetHttpConnection(m_strServerName, m_nPort);

			if (DlHtml(CHttpConnection::HTTP_VERB_GET))
				goto CleanUp;

			m_pServer->Close();
			delete m_pServer;
			m_pServer = NULL;
		}
	}
	catch (CException* pEx) {
		DispErrorLog("初期化ダウンロードエラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
		goto CleanUp;
	}

	strFPath = m_strDataDir + "\\" FNAME_ORDER;
	if (CFile::GetStatus(strFPath, m_FileStatus)) {
		bData = FALSE;

		CStdioFile StdioFile(strFPath, CFile::modeRead);
		while (StdioFile.ReadString(strLine)) {
			StringTokenizer.SetStrSep((CStringBuffer)strLine, ",");
			if (! StringTokenizer.StrTok())
				goto DataCleanUp4;
			m_SaCode.Add(StrQTrim(StringTokenizer.m_strTok));
			if (! StringTokenizer.StrTok())
				goto DataCleanUp4;
			m_SaName.Add(StrQTrim(StringTokenizer.m_strTok));
			if (! StringTokenizer.StrTok())
				goto DataCleanUp4;
			m_UiaReceiptNo.Add(atoi(StringTokenizer.m_strTok));
			if (! StringTokenizer.StrTok())
				goto DataCleanUp4;
			m_UiaState.Add(atoi(StringTokenizer.m_strTok));
			if (! StringTokenizer.StrTok())
				goto DataCleanUp4;
			m_DwaBuyPrice.Add(atol(StringTokenizer.m_strTok));
			if (! StringTokenizer.StrTok())
				goto DataCleanUp4;
			m_DwaSellPrice.Add(atol(StringTokenizer.m_strTok));
			if (! StringTokenizer.StrTok())
				goto DataCleanUp4;
			m_DwaSuryo.Add(atol(StringTokenizer.m_strTok));
			if (! StringTokenizer.StrTok())
				goto DataCleanUp4;
			m_DwaBuySoldSuryo.Add(atol(StringTokenizer.m_strTok));
			if (! StringTokenizer.StrTok())
				goto DataCleanUp4;
			m_DwaSellSuryo.Add(atol(StringTokenizer.m_strTok));
			if (! StringTokenizer.StrTok())
				goto DataCleanUp4;
			m_DwaSellSoldSuryo.Add(atol(StringTokenizer.m_strTok));
			if (! StringTokenizer.StrTok())
				goto DataCleanUp4;
			m_UiaTick.Add(atoi(StringTokenizer.m_strTok));
			if (! StringTokenizer.StrTok())
				goto DataCleanUp4;
			m_WaUnit.Add(atoi(StringTokenizer.m_strTok));
			if (! StringTokenizer.StrTok())
				goto DataCleanUp4;
			m_UiaSemiAuto.Add(atoi(StringTokenizer.m_strTok));
		}
		StdioFile.Close();

		bData = TRUE;

DataCleanUp4:
		if (! bData) {
			DispErrorLog("CSV 読込エラー\n");
			goto CleanUp;
		}

		Disp();
	}

	PostMessage(WM_USER + 2);

	DtCur = COleDateTime::GetCurrentTime();
	DtDate.SetDate(DtCur.GetYear(), DtCur.GetMonth(), DtCur.GetDay());

	while (1) {
		try {
			Database.Open(m_strDBFPath, FALSE, TRUE);

			CDaoRecordset RsHiashi(&Database);
			RsHiashi.Open(dbOpenTable, TBL_HIASHI);

			RsHiashi.SetCurrentIndex(pszPrimaryKey);
			pKeyArray[0] = COleVariant(DtDate);
			if (RsHiashi.Seek("<", pKeyArray, 2)) {
				RsHiashi.GetFieldValue(0, var);
				m_DtPreDate = m_DtNewsPreDate = var.date;
			}

			CDaoRecordset RsFunashiDateTime(&Database);
			RsFunashiDateTime.Open(dbOpenTable, TBL_FUNASHIDATETIME);

			RsFunashiDateTime.SetCurrentIndex(pszPrimaryKey);
			if (! RsFunashiDateTime.IsEOF()) {
				RsFunashiDateTime.MoveLast();
				RsFunashiDateTime.GetFieldValue(0, var);
				DtDate = var.date;
				DtDate.SetDate(DtDate.GetYear(), DtDate.GetMonth(), DtDate.GetDay());
				pKeyArray[0] = COleVariant(DtDate);
				if (RsHiashi.Seek("<", pKeyArray, 2)) {
					RsHiashi.GetFieldValue(0, var);
					m_DtPreDate = var.date;
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
			DispErrorLog(StrFormat("DAO 前営業日取得エラー: %s\n", GetExceptionErrorMessage(pEx)));
			pEx->Delete();
		}
		catch (CException* pEx) {
			DispErrorLog("前営業日取得エラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();
		}

		break;
	}

	ReadInfo();

	nContractYear0 = DtDate.GetYear();
	nMonth = DtDate.GetMonth();
	nDay = DtDate.GetDay();
	nContractMonth0 = nMonth / 3 * 3;
	if (nMonth % 3  ||  nDay >= 14)
		nContractMonth0 += 3;
	else if (nDay >= 8) {
		nDayOfWeek = DtDate.GetDayOfWeek();
		nDayOfWeekWork = nDayOfWeek - (nDay - 8);
		if (nDayOfWeekWork <= 6  &&  nDayOfWeek >= 6  ||  nDayOfWeekWork <= -1)
			nContractMonth0 += 3;
	}
	if (nContractMonth0 > 12) {
		nContractYear0 ++;
		nContractMonth0 -= 12;
	}
	nContractYear1 = nContractYear0;
	if ((nContractMonth1 = nContractMonth0 + 3) > 12) {
		nContractYear1 ++;
		nContractMonth1 -= 12;
	}
	nContractYear0 %= 100;
	nContractYear1 %= 100;
	m_strContractMonth0.Format("%02d%02d", nContractYear0, nContractMonth0);
	m_strContractMonth1.Format("%02d%02d", nContractYear1, nContractMonth1);
	m_strContractMonth0S.Format("%02d/%02d", nContractYear0, nContractMonth0);

//	if (! m_bMentenance0  &&  ! m_bMentenance1)
	if (! m_bMentenance1)
		DispStockAve();
	if (! m_bMentenance1)
		DispChart();
	DispRanking(0);
	DispRanking(1);
	DispNews();
	DispNews(1);

	m_bInitDialog = TRUE;

//	if (! m_bMentenance0) {
		GetState();
		Disp();
//	}

//	m_Check7.SetCheck(1);
	m_Check8.SetCheck(1);
	m_Check4.SetCheck(1);
	OnCheck4();
	m_Check3.SetCheck(1);
	OnCheck3();
	m_Check1.SetCheck(1);
	OnCheck1();

	SetTimer(2, 1000, NULL);
//	if (! m_bMentenance0)
		SetWMUserTimer(1000, 3, NULL);
//	if (! m_bMentenance0  ||  ! m_bMentenance1)
	if (! m_bMentenance1)
		SetWMUserTimer(1000, 4, NULL);
	if (! m_bMentenance1  ||  m_Check5.GetCheck() == 1)
		SetWMUserTimer(2000, 6, NULL);
//	if (! m_bMentenance0  ||  ! m_bMentenance1)
	if (! m_bMentenance1)
		SetWMUserTimer(5000, 13, NULL);
	if (! m_bMentenance2)
		SetWMUserTimer(10000, 14, NULL);
	SetWMUserTimer((60 - COleDateTime::GetCurrentTime().GetSecond()) % 20 * 1000, 18, NULL);

CleanUp:
	if (m_pServer) {
		m_pServer->Close();
		delete m_pServer;
	}

	m_hHook = SetWindowsHookEx( WH_GETMESSAGE, GetMsgProc, NULL, GetCurrentThreadId() );

	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CTradeHelperDlg::OnPaint() 
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
HCURSOR CTradeHelperDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

LRESULT CTradeHelperDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
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

void CTradeHelperDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	if (m_hHook)
		UnhookWindowsHookEx( m_hHook );
}

void CTradeHelperDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if (nIDEvent < 100) {
		if (PreUser(nIDEvent, 0, NULL)) {
			nPumpWaitingMessages ++;
			switch (nIDEvent) {
			case 2:
				m_Edit10.SetWindowText(GetCurrentTimeEx().Format("%H:%M:%S"));
				break;
			case 33:
				SetWMUserTimer(0U, 31, NULL);
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

void CTradeHelperDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
//	CDialog::OnOK();
}

void CTradeHelperDlg::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	SetWMUserTimer(0, 1, NULL);
	
//	CDialog::OnCancel();
}

void CTradeHelperDlg::OnButton2() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_bShift = GetKeyState(VK_SHIFT) < 0;
	m_bCtrl = GetKeyState(VK_CONTROL) < 0;
	AddOdr(0);
	Buy();
	m_bCtrl = FALSE;
	m_bShift = FALSE;
	Disp();
}

void CTradeHelperDlg::OnButton3() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if (GetKeyState(VK_CONTROL) < 0)
		PostMessage(WM_USER + 15);
	else {
		m_bShift = GetKeyState(VK_SHIFT) < 0;
		if (m_bShift)
			GetState(1);
		else
			DelOdr();
		m_bShift = FALSE;
		Disp();
	}
}

void CTradeHelperDlg::OnButton4() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_bShift = GetKeyState(VK_SHIFT) < 0;
	m_bCtrl = GetKeyState(VK_CONTROL) < 0;
	AddOdr(2);
	Buy();
	m_bCtrl = FALSE;
	m_bShift = FALSE;
	Disp();
}

void CTradeHelperDlg::OnButton5() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_bShift = GetKeyState(VK_SHIFT) < 0;
	m_bCtrl = GetKeyState(VK_CONTROL) < 0;
	AddOdr(1);
	Buy();
	m_bCtrl = FALSE;
	m_bShift = FALSE;
	Disp();
}

void CTradeHelperDlg::OnButton6() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if (m_nList3CurSel != LB_ERR) {
		int nState = m_UiaState[m_nList3CurSel];

		if (nState == 2  ||  nState == 6  ||  nState == 7) {
			long lSellPrice;

			m_bShift = GetKeyState(VK_SHIFT) < 0;
			m_bCtrl = GetKeyState(VK_CONTROL) < 0;

			if (m_bShift)
				lSellPrice = ~ 0UL;
			else {
				CString strSellPrice;

				m_Edit3.GetWindowText(strSellPrice);
				lSellPrice = atol(strSellPrice);

				if (lSellPrice == 0L) {
					CKehai0 KehaiWork;

					if (GetKehai(m_sbKehaiHtml, KehaiWork))
						DispErrorLog("複数気配取得エラー\n");
					else
						if (m_bCtrl) {
							lSellPrice = KehaiWork.m_plKehaiPrice[4];
							lSellPrice -= GetDiff(lSellPrice);
						} else
							lSellPrice = KehaiWork.m_plKehaiPrice[5];
				}
			}

			if (lSellPrice) {
//				if (lSellPrice >= (long)m_DwaBuyPrice[m_nList3CurSel]) {
					m_UiaState[m_nList3CurSel] = 3U;
					m_DwaSellPrice[m_nList3CurSel] = lSellPrice;

					Sell();
//				}
			}

			m_bCtrl = FALSE;
			m_bShift = FALSE;
			Disp();
		}
	}
}

void CTradeHelperDlg::OnButton7() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_bShift = GetKeyState(VK_SHIFT) < 0;
	m_bCtrl = GetKeyState(VK_CONTROL) < 0;
	AddOdr(3);
	Buy();
	m_bCtrl = FALSE;
	m_bShift = FALSE;
	Disp();
}

void CTradeHelperDlg::OnButton8() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if (GetKeyState(VK_SHIFT) < 0) {
		if (GetKeyState(VK_CONTROL) < 0) {
			int nList2CurSel = m_List2.GetCurSel();
			int nNiceCodeUpperBound = m_SaNiceCode.GetUpperBound();
			if (
				nList2CurSel != LB_ERR
				&&  nList2CurSel <= nNiceCodeUpperBound
				&&  m_nList2PreCurSel != LB_ERR
				&&  m_nList2PreCurSel <= nNiceCodeUpperBound
				&&  nList2CurSel != m_nList2PreCurSel
			) {
				BOOL bLShift = GetKeyState(VK_LSHIFT);
				do {
					Sleep(100);
					PumpWaitingMessages();
				} while (GetKeyState(VK_SHIFT) < 0  ||  GetKeyState(VK_CONTROL) < 0);
				CWnd* pWnd;
				if ((pWnd = FindWindow(NULL, m_strMainExeWndName))) {
					CString strStk;
					CString strPreStk;
					if (bLShift < 0) {
						strStk = m_SaNiceCode[nList2CurSel].Left(4);
						strPreStk = m_SaNiceCode[m_nList2PreCurSel].Left(4);
						if (strStk != strPreStk) {
							m_nSetStreamer ++;
							m_nSelStreamer ++;
							pWnd->PostMessage(WM_USER + 4, m_nList2PreCurSel + 1, atoi(strStk));
							m_nSetStreamer ++;
							m_nSelStreamer ++;
							pWnd->PostMessage(WM_USER + 4, nList2CurSel + 1, atoi(strPreStk));
						}
					} else {
						int i;
						if (m_nList2PreCurSel < nList2CurSel) {
							for (i = m_nList2PreCurSel; i < nList2CurSel; i ++) {
								strStk = m_SaNiceCode[i + 1].Left(4);
								strPreStk = m_SaNiceCode[i].Left(4);
								if (strStk != strPreStk) {
									m_nSetStreamer ++;
									m_nSelStreamer ++;
									pWnd->PostMessage(WM_USER + 4, i + 1, atoi(strStk));
								}
							}
						} else {
							for (i = m_nList2PreCurSel; i > nList2CurSel; i --) {
								strStk = m_SaNiceCode[i - 1].Left(4);
								strPreStk = m_SaNiceCode[i].Left(4);
								if (strStk != strPreStk) {
									m_nSetStreamer ++;
									m_nSelStreamer ++;
									pWnd->PostMessage(WM_USER + 4, i + 1, atoi(strStk));
								}
							}
						}
						strStk = m_SaNiceCode[m_nList2PreCurSel].Left(4);
						strPreStk = m_SaNiceCode[i].Left(4);
						if (strStk != strPreStk) {
							m_nSetStreamer ++;
							m_nSelStreamer ++;
							pWnd->PostMessage(WM_USER + 4, i + 1, atoi(strStk));
						}
					}
				}
			}
		} else {
			if (GetKeyState(VK_LSHIFT) < 0) {
				do {
					Sleep(100);
					PumpWaitingMessages();
				} while (GetKeyState(VK_SHIFT) < 0);
				m_SaNiceCode.RemoveAll();
				m_nSetStreamer ++;
				PostMessage(WM_USER + 2);
			} else
				PostMessage(WM_USER + 14);
		}
	} else if (GetKeyState(VK_CONTROL) < 0) {
		CWnd* pWnd;
		if ((pWnd = FindWindow(NULL, m_strMainExeWndName)))
			pWnd->PostMessage(WM_USER + 5);
	} else {
		CWnd* pWnd;
		if ((pWnd = FindWindow(NULL, m_strMainExeWndName))) {
			int nList2CurSel = m_List2.GetCurSel();
			int nNiceCodeUpperBound = m_SaNiceCode.GetUpperBound();
			if (nList2CurSel == LB_ERR  ||  nList2CurSel > nNiceCodeUpperBound)
				nList2CurSel = 9;

			if (nList2CurSel > nNiceCodeUpperBound  ||  m_SaNiceCode[nList2CurSel].Left(4) != m_strEntryStk) {
				m_nSetStreamer ++;
				m_nSelStreamer ++;
				pWnd->PostMessage(WM_USER + 4, nList2CurSel + 1, atoi(m_strEntryStk));
			}
		}
	}
}

void CTradeHelperDlg::OnButton10() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	
	int i;
	int imax;
	CString strEdit1;
	int nReceiptNo;
	BOOL bSell;
	CKehai0 KehaiWork;
	long lPrice;

	m_bCtrl = GetKeyState(VK_CONTROL) < 0;

	m_Edit1.GetWindowText(strEdit1);
	nReceiptNo = atoi(strEdit1);

	for (i = 0, imax = m_UiaReceiptNo.GetSize(); i < imax; i ++)
		if ((int)m_UiaReceiptNo[i] == nReceiptNo)
			break;
	bSell = i < imax  &&  m_UiaState[i] != 2  &&  m_UiaState[i] != 6;

	if (GetKehai(m_sbKehaiHtml, KehaiWork))
		DispErrorLog("複数気配取得エラー\n");
	else
		if (m_bCtrl) {
			lPrice = KehaiWork.m_plKehaiPrice[4];
			(bSell ? m_Edit3 : m_Edit2).SetWindowText(LToA(lPrice - GetDiff(lPrice)));
		} else {
			lPrice = KehaiWork.m_plKehaiPrice[5];
			(bSell ? m_Edit3 : m_Edit2).SetWindowText(LToA(lPrice));
		}

	m_bCtrl = FALSE;
}

void CTradeHelperDlg::OnButton11() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	
	int i;
	int imax;
	CString strEdit1;
	int nReceiptNo;
	BOOL bSell;
	CKehai0 KehaiWork;
	long lPrice;

	m_bCtrl = GetKeyState(VK_CONTROL) < 0;

	m_Edit1.GetWindowText(strEdit1);
	nReceiptNo = atoi(strEdit1);

	for (i = 0, imax = m_UiaReceiptNo.GetSize(); i < imax; i ++)
		if ((int)m_UiaReceiptNo[i] == nReceiptNo)
			break;
	bSell = i < imax  &&  m_UiaState[i] != 2  &&  m_UiaState[i] != 6;

	if (GetKehai(m_sbKehaiHtml, KehaiWork))
		DispErrorLog("複数気配取得エラー\n");
	else
		if (m_bCtrl) {
			lPrice = KehaiWork.m_plKehaiPrice[4];
			(bSell ? m_Edit3 : m_Edit2).SetWindowText(LToA(lPrice));
		} else {
			lPrice = KehaiWork.m_plKehaiPrice[5];
			(bSell ? m_Edit3 : m_Edit2).SetWindowText(LToA(lPrice + GetDiff(lPrice + 1L)));
		}

	m_bCtrl = FALSE;
}

void CTradeHelperDlg::OnButton12() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	
	if (GetKeyState(VK_SHIFT) < 0  &&  GetKeyState(VK_CONTROL) < 0)
		m_Edit4.SetWindowText("1");
	else {
		int i;
		int imax;
		CString strEdit1;
		int nReceiptNo;
		long lPrice;

		m_Edit1.GetWindowText(strEdit1);
		nReceiptNo = atoi(strEdit1);

		for (i = 0, imax = m_UiaReceiptNo.GetSize(); i < imax; i ++)
			if ((int)m_UiaReceiptNo[i] == nReceiptNo) {
				lPrice = m_DwaBuyPrice[i];
				m_Edit3.SetWindowText(LToA(GetKeyState(VK_CONTROL) < 0 ? lPrice + GetDiff(lPrice + 1L) : lPrice));
				break;
			}
	}
}

void CTradeHelperDlg::OnButton13() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	
	if (GetKeyState(VK_SHIFT) < 0) {
		CString strEdit4;
		m_Edit4.GetWindowText(strEdit4);
		if (strEdit4.GetLength())
			m_Edit4.SetWindowText(IToA(atoi(strEdit4) - 1));
	} else {
		int i;
		int imax;
		CString strEdit;
		int nReceiptNo;
		BOOL bSell;
		long lPrice;

		m_Edit1.GetWindowText(strEdit);
		nReceiptNo = atoi(strEdit);

		for (i = 0, imax = m_UiaReceiptNo.GetSize(); i < imax; i ++)
			if ((int)m_UiaReceiptNo[i] == nReceiptNo)
				break;
		bSell = i < imax  &&  m_UiaState[i] != 2  &&  m_UiaState[i] != 6;

		CEdit& Edit = bSell ? m_Edit3 : m_Edit2;
		Edit.GetWindowText(strEdit);
		lPrice = atol(strEdit);
		if (lPrice > 1)
			Edit.SetWindowText(LToA(lPrice - GetDiff(lPrice)));
	}
}

void CTradeHelperDlg::OnButton14() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	
	if (GetKeyState(VK_SHIFT) < 0) {
		CString strEdit4;
		m_Edit4.GetWindowText(strEdit4);
		if (strEdit4.GetLength())
			m_Edit4.SetWindowText(IToA(atoi(strEdit4) + 1));
	} else {
		int i;
		int imax;
		CString strEdit;
		int nReceiptNo;
		BOOL bSell;
		long lPrice;

		m_Edit1.GetWindowText(strEdit);
		nReceiptNo = atoi(strEdit);

		for (i = 0, imax = m_UiaReceiptNo.GetSize(); i < imax; i ++)
			if ((int)m_UiaReceiptNo[i] == nReceiptNo)
				break;
		bSell = i < imax  &&  m_UiaState[i] != 2  &&  m_UiaState[i] != 6;

		CEdit& Edit = bSell ? m_Edit3 : m_Edit2;
		Edit.GetWindowText(strEdit);
		lPrice = atol(strEdit);
		Edit.SetWindowText(LToA(lPrice + GetDiff(lPrice + 1L)));
	}
}

void CTradeHelperDlg::OnButton15() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	int i;
	int imax;
	CString strEdit;
	int nReceiptNo;
	int nCurSel;
	int nFindIndex;

	m_Edit1.GetWindowText(strEdit);

	nReceiptNo = atoi(strEdit);
	for (i = 0, imax = m_UiaReceiptNo.GetSize(); i < imax; i ++)
		if ((int)m_UiaReceiptNo[i] == nReceiptNo) {
			strEdit = m_SaCode[i];
			break;
		}

	nCurSel = m_List6.GetCurSel();
	if ((nFindIndex = m_List6.FindString(nCurSel == LB_ERR ? -1 : nCurSel, strEdit.Left(4))) != LB_ERR)
		m_List6.SetCurSel(nFindIndex);
	nCurSel = m_List7.GetCurSel();
	if ((nFindIndex = m_List7.FindString(nCurSel == LB_ERR ? -1 : nCurSel, strEdit.Left(4))) != LB_ERR)
		m_List7.SetCurSel(nFindIndex);
}

void CTradeHelperDlg::OnCheck1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	BOOL bCheck1 = m_Check1.GetCheck() == 1;
	BOOL bCheck2 = m_Check2.GetCheck() == 1;
	BOOL bCheck4 = m_Check4.GetCheck() == 1;
	m_List5.ShowWindow(bCheck1  &&  ! bCheck2  ? SW_SHOW : SW_HIDE);
	m_List6.ShowWindow(bCheck1 ? SW_SHOW : SW_HIDE);
	m_List7.ShowWindow(bCheck1 && bCheck2 ? SW_SHOW : SW_HIDE);
	m_List8.ShowWindow(bCheck1 ? SW_SHOW : SW_HIDE);
//	if (! bCheck1  &&  bCheck4) {
//		m_Check4.SetCheck(0);
//		OnCheck4();
//	}
}

void CTradeHelperDlg::OnCheck2() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnCheck1();
}

void CTradeHelperDlg::OnCheck3() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	::ShowWindow(m_WebBrowser22.m_hWnd, m_Check3.GetCheck() == 0 ? SW_SHOW : SW_HIDE);
}

void CTradeHelperDlg::OnCheck4() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

//	BOOL bCheck1 = m_Check1.GetCheck() == 1;
	BOOL bCheck4 = m_Check4.GetCheck() == 1;
	CRect Rect;
	CRect Rect4;

	m_List4.GetWindowRect(&Rect4);
	ScreenToClient(&Rect4);

	m_WebBrowser22.GetWindowRect(&Rect);
	ScreenToClient(&Rect);
	if (bCheck4) {
		Rect.left = Rect4.right;
		Rect.right = Rect4.right + 180;
	} else {
		Rect.left = 0;
		Rect.right = Rect4.right;
	}
	m_WebBrowser22.MoveWindow(&Rect);
	m_WebBrowser25.MoveWindow(&Rect);

//	if (! bCheck1  &&  bCheck4) {
//		m_Check1.SetCheck(1);
//		OnCheck1();
//	}
}

void CTradeHelperDlg::OnCheck5() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	COleDateTime DtCur = GetCurrentTimeEx();
	COleDateTime DtDate = DtCur;
	COleDateTimeSpan Dts1Day(1, 0, 0, 0);
	int nCurYear = DtCur.GetYear();
	int nCurMonth = DtCur.GetMonth();
	int nCurDay = DtCur.GetDay();
	int nCurHour = DtCur.GetHour();
	int nDayOfWeek;
	CRect Rect;
	CRect Rect1;
	CRect Rect3;

	m_List1.GetWindowRect(&Rect1);
	ScreenToClient(&Rect1);
	m_List3.GetWindowRect(&Rect3);
	ScreenToClient(&Rect3);

	while (
		(nDayOfWeek = DtDate.GetDayOfWeek()) == 1
		||  nDayOfWeek == 7
		||  ! m_nExecMode  &&  nCurHour < 17  &&  DtDate.GetYear() == nCurYear  &&  DtDate.GetMonth() == nCurMonth  &&  DtDate.GetDay() == nCurDay
	)
		DtDate -= Dts1Day;
	m_MonthCalCtrl1.SetCurSel(DtDate);

	if (m_Check5.GetCheck() == 1) {
		m_MonthCalCtrl1.GetWindowRect(&Rect);
		ScreenToClient(&Rect);
		Rect1.right = Rect.left;
		Rect3.right = Rect.left;
		m_List1.MoveWindow(&Rect1);
		m_List3.MoveWindow(&Rect3);
		m_MonthCalCtrl1.ShowWindow(SW_SHOW);
	} else {
		m_MonthCalCtrl1.ShowWindow(SW_HIDE);
		m_Edit7.GetWindowRect(&Rect);
		ScreenToClient(&Rect);
		Rect1.right = Rect.left;
		Rect3.right = Rect.left;
		m_List1.MoveWindow(&Rect1);
		m_List3.MoveWindow(&Rect3);
	}

	SetWMUserTimer(0, 9, NULL);
	SetWMUserTimer(0, 10, NULL);
	SetWMUserTimer(0, 15, NULL);
}

void CTradeHelperDlg::OnChangeEdit1() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	static CString strPreEdit;
	CString strEdit;

	m_Edit1.GetWindowText(strEdit);
	if (strEdit != strPreEdit) {
		strPreEdit = strEdit;

		int i;
		int imax;
		BOOL bBtn15Enable = FALSE;
		int nEditLen;

		if ((nEditLen = strEdit.GetLength()) >= 4) {
			int nReceiptNo = atoi(strEdit);
			for (i = 0, imax = m_UiaReceiptNo.GetSize(); i < imax; i ++)
				if ((int)m_UiaReceiptNo[i] == nReceiptNo)
					break;
			if (i == imax) {
				CString strName;
				CodeToName(strEdit, strName);
				if (strName.GetLength()) {
					m_Edit1.SetWindowText(strEdit);
					m_Edit17.SetWindowText(StrConvHalfWidth(strName));

					void* pVoid;
					if (m_MstpNewsCode.Lookup(strEdit, pVoid) || m_MstpNewsCode2.Lookup(strEdit, pVoid))
						bBtn15Enable = TRUE;

					if (m_bSetFocusEdit1) {
						EntryStk();

						m_List2.SetCurSel(-1);
						m_List2.SetTopIndex(0);

						m_List3.SetCurSel(-1);
						m_List3.SetTopIndex(0);

						m_List4.SetCurSel(-1);
						m_List4.SetTopIndex(0);

						m_List5.SetCurSel(-1);
						m_List5.SetTopIndex(0);

						m_List6.SetCurSel(-1);
						m_List6.SetTopIndex(0);

						m_List7.SetCurSel(-1);
						m_List7.SetTopIndex(0);

						m_List8.SetCurSel(-1);
						m_List8.SetTopIndex(0);
					}

					OnRadio10();

					SetWMUserTimer(0, 5, NULL);
					SetWMUserTimer(0, 24, NULL);
				}
			}
		} else {
			m_Edit17.SetWindowText(pszEmpty);
			if (! nEditLen) {
				if (m_bSetFocusEdit1)
					EntryStk();
				SetWMUserTimer(0, 5, NULL);
			}
		}
		KillWMUserTimer(27);
		KillWMUserTimer(28);
		SetWMUserTimer(0, bBtn15Enable ? 27 : 28, NULL);
	}
}

void CTradeHelperDlg::OnSetfocusEdit1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_bSetFocusEdit1 = TRUE;
	SetWMUserTimer(0, 24, NULL);
}

void CTradeHelperDlg::OnKillfocusEdit1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_bSetFocusEdit1 = FALSE;
}

void CTradeHelperDlg::OnSelchangeList2() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	m_nList2PreCurSel = m_nList2CurSel;
	m_nList2CurSel = m_List2.GetCurSel();

	if (m_nList2CurSel == LB_ERR) {
		m_Edit1.SetWindowText(pszEmpty);
		m_Edit17.SetWindowText(pszEmpty);
	} else {
		CString strText;
		CString strCode;
		CString strName;

		m_List2.GetText(m_nList2CurSel, strText);
		if (strText.GetLength()) {
			strCode = strText.Left(strText.Find(' '));
			strCode.SetAt(4, '/');
			if (strCode.GetLength() == 7) {
				char chSijoEx = strCode[6];
				if (chSijoEx == 'M'  ||  chSijoEx == '2')
					strCode.Delete(6);
			}
			CodeToName(strCode, strName);
		}

		m_Edit1.SetWindowText(strCode);
		m_Edit17.SetWindowText(StrConvHalfWidth(strName));

		if (m_nList2CurSel < m_SaNiceCode.GetSize())
			SelStreamer(m_nList2CurSel);
		else
			EntryStk();
	}

	m_Edit2.SetWindowText(pszEmpty);
	m_Edit3.SetWindowText(pszEmpty);
	m_Edit4.SetWindowText(pszEmpty);
	m_Edit5.SetWindowText(pszEmpty);
	m_Edit6.SetWindowText(pszEmpty);

	m_List3.SetCurSel(-1);
	m_List3.SetTopIndex(0);

	m_List4.SetCurSel(-1);
	m_List4.SetTopIndex(0);

	m_List5.SetCurSel(-1);
	m_List5.SetTopIndex(0);

	m_List6.SetCurSel(-1);
	m_List6.SetTopIndex(0);

	m_List7.SetCurSel(-1);
	m_List7.SetTopIndex(0);

	m_List8.SetCurSel(-1);
	m_List8.SetTopIndex(0);

	if (! m_bDisp)
		OnRadio10();
}

void CTradeHelperDlg::OnSelchangeList3() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	m_nList3CurSel = m_List3.GetCurSel();
	BOOL bBtn15Enable = FALSE;

	if (m_nList3CurSel != LB_ERR) {
		int nReceiptNo;
		long lPrice;
		CString strCode;
		void* pVoid;

		nReceiptNo = m_UiaReceiptNo[m_nList3CurSel];
		strCode = m_SaCode[m_nList3CurSel];
		m_Edit1.SetWindowText(nReceiptNo ? IToA(nReceiptNo) : strCode);

		lPrice = m_DwaBuyPrice[m_nList3CurSel];
		m_Edit2.SetWindowText(lPrice ? LToA(lPrice) : pszEmpty);

		lPrice = m_DwaSellPrice[m_nList3CurSel];
		m_Edit3.SetWindowText(lPrice ? LToA(lPrice) : pszEmpty);

		m_Edit4.SetWindowText(LToA(m_DwaSuryo[m_nList3CurSel] / m_WaUnit[m_nList3CurSel]));
		m_Edit5.SetWindowText(IToA(m_UiaTick[m_nList3CurSel]));
		m_Edit6.SetWindowText(LToA(m_UiaState[m_nList3CurSel]));
		m_Edit17.SetWindowText(StrConvHalfWidth(m_SaName[m_nList3CurSel]));

		if (m_MstpNiceCode.Lookup(strCode, pVoid))
			SelStreamer((int)pVoid);

		if (m_MstpNewsCode.Lookup(strCode, pVoid) || m_MstpNewsCode2.Lookup(strCode, pVoid))
			bBtn15Enable = TRUE;

		m_List2.SetCurSel(-1);
		m_List2.SetTopIndex(0);

		m_List4.SetCurSel(-1);
		m_List4.SetTopIndex(0);

		m_List5.SetCurSel(-1);
		m_List5.SetTopIndex(0);

		m_List6.SetCurSel(-1);
		m_List6.SetTopIndex(0);

		m_List7.SetCurSel(-1);
		m_List7.SetTopIndex(0);

		m_List8.SetCurSel(-1);
		m_List8.SetTopIndex(0);

		switch (m_UiaState[m_nList3CurSel]) {
		case 2U:
		case 4U:
		case 6U:
			m_bSelchangeList3 = TRUE;
		}

		if (! m_bDisp)
			OnRadio10();

		SetWMUserTimer(0, 5, NULL);
	}
	KillWMUserTimer(27);
	KillWMUserTimer(28);
	SetWMUserTimer(0, bBtn15Enable ? 27 : 28, NULL);
}

void CTradeHelperDlg::OnSelchangeList4() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	int nCurSel = m_List4.GetCurSel();

	if (nCurSel != LB_ERR) {
		CString strText;
		CString strCode;
		CString strName;

		m_List4.GetText(nCurSel, strText);
		strCode = strText.Left(strText.Find(' '));
		strCode.SetAt(4, '/');
		if (strCode.GetLength() == 7) {
			char chSijoEx = strCode[6];
			if (chSijoEx == 'M'  ||  chSijoEx == '2')
				strCode.Delete(6);
		}
		CodeToName(strCode, strName);

		m_Edit1.SetWindowText(strCode);
		m_Edit2.SetWindowText(pszEmpty);
		m_Edit3.SetWindowText(pszEmpty);
		m_Edit4.SetWindowText(pszEmpty);
		m_Edit5.SetWindowText(pszEmpty);
		m_Edit6.SetWindowText(pszEmpty);
		m_Edit17.SetWindowText(StrConvHalfWidth(strName));

		m_List2.SetCurSel(-1);
		m_List2.SetTopIndex(0);

		m_List3.SetCurSel(-1);
		m_List3.SetTopIndex(0);

		m_List5.SetCurSel(-1);
		m_List5.SetTopIndex(0);

		m_List6.SetCurSel(-1);
		m_List6.SetTopIndex(0);

		m_List7.SetCurSel(-1);
		m_List7.SetTopIndex(0);

		m_List8.SetCurSel(-1);
		m_List8.SetTopIndex(0);

		EntryStk();

		OnRadio10();
	}
}

void CTradeHelperDlg::OnSelchangeList5() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	int nCurSel = m_List5.GetCurSel();

	if (nCurSel != LB_ERR) {
		CString strText;
		CString strCode;
		CString strName;

		m_List5.GetText(nCurSel, strText);
		strCode = strText.Left(strText.Find(' '));
		strCode.SetAt(4, '/');
		if (strCode.GetLength() == 7) {
			char chSijoEx = strCode[6];
			if (chSijoEx == 'M'  ||  chSijoEx == '2')
				strCode.Delete(6);
		}
		CodeToName(strCode, strName);

		m_Edit1.SetWindowText(strCode);
		m_Edit2.SetWindowText(pszEmpty);
		m_Edit3.SetWindowText(pszEmpty);
		m_Edit4.SetWindowText(pszEmpty);
		m_Edit5.SetWindowText(pszEmpty);
		m_Edit6.SetWindowText(pszEmpty);
		m_Edit17.SetWindowText(StrConvHalfWidth(strName));

		m_List2.SetCurSel(-1);
		m_List2.SetTopIndex(0);

		m_List3.SetCurSel(-1);
		m_List3.SetTopIndex(0);

		m_List4.SetCurSel(-1);
		m_List4.SetTopIndex(0);

		m_List6.SetCurSel(-1);
		m_List6.SetTopIndex(0);

		m_List7.SetCurSel(-1);
		m_List7.SetTopIndex(0);

		m_List8.SetCurSel(-1);
		m_List8.SetTopIndex(0);

		EntryStk();

		OnRadio10();
	}
}

void CTradeHelperDlg::OnSelchangeList6() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	int nCurSel = m_List6.GetCurSel();

	if (nCurSel != LB_ERR) {
		CString strText;
		CString strCode;
		CString strName;

		m_List6.GetText(nCurSel, strText);
		strCode = strText.Left(strText.Find(' '));
		strCode.SetAt(4, '/');
		if (strCode.GetLength() == 7) {
			char chSijoEx = strCode[6];
			if (chSijoEx == 'M'  ||  chSijoEx == '2')
				strCode.Delete(6);
		}
		CodeToName(strCode, strName);

		m_Edit1.SetWindowText(strCode);
		m_Edit2.SetWindowText(pszEmpty);
		m_Edit3.SetWindowText(pszEmpty);
		m_Edit4.SetWindowText(pszEmpty);
		m_Edit5.SetWindowText(pszEmpty);
		m_Edit6.SetWindowText(pszEmpty);
		m_Edit17.SetWindowText(StrConvHalfWidth(strName));

		m_List2.SetCurSel(-1);
		m_List2.SetTopIndex(0);

		m_List3.SetCurSel(-1);
		m_List3.SetTopIndex(0);

		m_List4.SetCurSel(-1);
		m_List4.SetTopIndex(0);

		m_List5.SetCurSel(-1);
		m_List5.SetTopIndex(0);

		m_List7.SetCurSel(-1);
		m_List7.SetTopIndex(0);

		m_List8.SetCurSel(-1);
		m_List8.SetTopIndex(0);

		SetWMUserTimer(100, 25, NULL);

		OnRadio10();
	}
}

void CTradeHelperDlg::OnSelchangeList7() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	
	int nCurSel = m_List7.GetCurSel();

	if (nCurSel != LB_ERR) {
		CString strText;
		CString strCode;
		CString strName;

		m_List7.GetText(nCurSel, strText);
		strCode = strText.Left(strText.Find(' '));
		strCode.SetAt(4, '/');
		if (strCode.GetLength() == 7) {
			char chSijoEx = strCode[6];
			if (chSijoEx == 'M'  ||  chSijoEx == '2')
				strCode.Delete(6);
		}
		CodeToName(strCode, strName);

		m_Edit1.SetWindowText(strCode);
		m_Edit2.SetWindowText(pszEmpty);
		m_Edit3.SetWindowText(pszEmpty);
		m_Edit4.SetWindowText(pszEmpty);
		m_Edit5.SetWindowText(pszEmpty);
		m_Edit6.SetWindowText(pszEmpty);
		m_Edit17.SetWindowText(StrConvHalfWidth(strName));

		m_List2.SetCurSel(-1);
		m_List2.SetTopIndex(0);

		m_List3.SetCurSel(-1);
		m_List3.SetTopIndex(0);

		m_List4.SetCurSel(-1);
		m_List4.SetTopIndex(0);

		m_List5.SetCurSel(-1);
		m_List5.SetTopIndex(0);

		m_List6.SetCurSel(-1);
		m_List6.SetTopIndex(0);

		m_List8.SetCurSel(-1);
		m_List8.SetTopIndex(0);

		EntryStk();

		OnRadio10();
	}
}

void CTradeHelperDlg::OnSelchangeList8() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	
	int nCurSel = m_List8.GetCurSel();

	if (nCurSel != LB_ERR) {
		CString strText;
		CString strCode;
		CString strName;

		m_List8.GetText(nCurSel, strText);
		strCode = strText.Left(strText.Find(' '));
		strCode.SetAt(4, '/');
		if (strCode.GetLength() == 7) {
			char chSijoEx = strCode[6];
			if (chSijoEx == 'M'  ||  chSijoEx == '2')
				strCode.Delete(6);
		}
		CodeToName(strCode, strName);

		m_Edit1.SetWindowText(strCode);
		m_Edit2.SetWindowText(pszEmpty);
		m_Edit3.SetWindowText(pszEmpty);
		m_Edit4.SetWindowText(pszEmpty);
		m_Edit5.SetWindowText(pszEmpty);
		m_Edit6.SetWindowText(pszEmpty);
		m_Edit17.SetWindowText(StrConvHalfWidth(strName));

		m_List2.SetCurSel(-1);
		m_List2.SetTopIndex(0);

		m_List3.SetCurSel(-1);
		m_List3.SetTopIndex(0);

		m_List4.SetCurSel(-1);
		m_List4.SetTopIndex(0);

		m_List5.SetCurSel(-1);
		m_List5.SetTopIndex(0);

		m_List6.SetCurSel(-1);
		m_List6.SetTopIndex(0);

		m_List7.SetCurSel(-1);
		m_List7.SetTopIndex(0);

		EntryStk();

		OnRadio10();
	}
}

void CTradeHelperDlg::OnDblclkList6() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if ((int)ShellExecute(m_hWnd, _T("open"), m_SaNewsUrl[m_List6.GetCurSel()], NULL, NULL, SW_SHOWNORMAL) <= 32)
		DispErrorLog("適時開示速報ブラウザ表示エラー\n");
}

void CTradeHelperDlg::OnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	SetWMUserTimer(0, 9, NULL);
	SetWMUserTimer(0, 10, NULL);
	SetWMUserTimer(0, 15, NULL);
	
	*pResult = 0;
}

void CTradeHelperDlg::OnRadio1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	SetWMUserTimer(0, 9, NULL);
}

void CTradeHelperDlg::OnRadio2() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio1();
}

void CTradeHelperDlg::OnRadio3() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio1();
}

void CTradeHelperDlg::OnRadio4() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio1();
}

void CTradeHelperDlg::OnRadio5() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio1();
}

void CTradeHelperDlg::OnRadio6() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio1();
}

void CTradeHelperDlg::OnRadio7() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio1();
}

void CTradeHelperDlg::OnRadio8() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio1();
}

void CTradeHelperDlg::OnRadio9() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio1();
}

void CTradeHelperDlg::OnRadio10() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	SetWMUserTimer(0, 10, NULL);
}

void CTradeHelperDlg::OnRadio11() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio10();
}

void CTradeHelperDlg::OnRadio12() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	COleDateTime DtCur = GetCurrentTimeEx();
	int nDayOfWeek = DtCur.GetDayOfWeek();
	int nHour = DtCur.GetHour();
	int nMinute = DtCur.GetMinute();
	if (! (nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 9  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16))) {
		m_MstrCodeRankingAttr.RemoveAll();
		m_MstrCodeRankingAttr2.RemoveAll();
	}
	SetWMUserTimer(0, 26, NULL);
	SetWMUserTimer(0, 15, NULL);
	SetWMUserTimer(0, 16, NULL);
}

void CTradeHelperDlg::OnRadio13() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio12();
}

void CTradeHelperDlg::OnRadio14() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio12();
}

void CTradeHelperDlg::OnRadio15() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio12();
}

void CTradeHelperDlg::OnRadio16() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio12();
}

void CTradeHelperDlg::OnRadio17() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio12();
}

void CTradeHelperDlg::OnRadio18() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio12();
}

void CTradeHelperDlg::OnRadio19() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio12();
}

void CTradeHelperDlg::OnRadio20() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnRadio12();
}

void CTradeHelperDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	switch (nIDCtl) {
	case IDC_LIST4:
	case IDC_LIST8:
		{
			CListBox* pListBox = (CListBox *)GetDlgItem(nIDCtl);

			// Calculate appropriate font height.
			int newHeight = 0;
			CFont* pFont = (CFont*)pListBox->GetFont();
			if (pFont) {
				LOGFONT lf;
				pFont->GetLogFont(&lf);
				newHeight = (lf.lfHeight > 0) ? lf.lfHeight : -lf.lfHeight;
			} else {
				CDC* pDC = GetDC();
				newHeight = -MulDiv(-75, GetDeviceCaps(pDC->m_hDC, LOGPIXELSY), 72) / 10;
				ReleaseDC(pDC);
				newHeight = (newHeight > 0) ? newHeight : -newHeight;
			}

			// Set new itemHeight, use 14 as default height.
			lpMeasureItemStruct->itemHeight = newHeight ? newHeight : 14;
		}
		break;
	default:
		CWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
	}
}

void CTradeHelperDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	switch (nIDCtl) {
	case IDC_LIST4:
	case IDC_LIST8:
		{
			CListBox* pListBox = (CListBox *)GetDlgItem(nIDCtl);

			ASSERT(lpDrawItemStruct->CtlType == ODT_LISTBOX);
//			LPCTSTR lpszText = (LPCTSTR) lpDrawItemStruct->itemData;
//			ASSERT(lpszText != NULL);
			CDC dc;

			dc.Attach(lpDrawItemStruct->hDC);

			// Save these value to restore them when done drawing.
			COLORREF crOldTextColor = dc.GetTextColor();
			COLORREF crOldBkColor = dc.GetBkColor();

			int nCount = pListBox->GetCount();

			// If this item is selected, set the background color 
			// and the text color to appropriate values. Also, erase
			// rect by filling it with the background color.
			if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&
				(lpDrawItemStruct->itemState & ODS_SELECTED))
			{
				// 選択色
				dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
				dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
				dc.FillSolidRect(&lpDrawItemStruct->rcItem, 
				  ::GetSysColor(COLOR_HIGHLIGHT));
			}
			else {
				// 非選択色
				COLORREF crBkColor = crOldBkColor;
				if (nCount != LB_ERR  &&  lpDrawItemStruct->itemID < (UINT)nCount) {
					DWORD dwItemData;
					if ((dwItemData = pListBox->GetItemData(lpDrawItemStruct->itemID)) != LB_ERR  &&  dwItemData)
						crBkColor = RGB(255, 0, 255);
				}
				dc.FillSolidRect(&lpDrawItemStruct->rcItem, crBkColor);
			}

			// Draw the text.
			if (nCount != LB_ERR  &&  lpDrawItemStruct->itemID < (UINT)nCount) {
				CString strText;
				pListBox->GetText(lpDrawItemStruct->itemID, strText);
				if (strText.GetLength())
					dc.DrawText(
//						lpszText,
						strText,
//						(int)_tcslen(lpszText),
						strText.GetLength(),
						CRect(&lpDrawItemStruct->rcItem) + CRect(-2, 0, -2, 0),
						DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);
			}

			// If this item has the focus, draw a focus style frame around the
			// item's rect.
			if ((lpDrawItemStruct->itemAction | ODA_FOCUS) &&
				(lpDrawItemStruct->itemState & ODS_FOCUS))
			{
				// フォーカス枠
				dc.DrawFocusRect(&lpDrawItemStruct->rcItem);
			}

			// Reset the background color and the text color back to their
			// original values.
			dc.SetTextColor(crOldTextColor);
			dc.SetBkColor(crOldBkColor);

			dc.Detach();
		}
		break;
	default:
		CWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
	}
}

LRESULT CTradeHelperDlg::OnUser(WPARAM wParam, LPARAM lParam)
{
	if (! PreUser(wParam, lParam))
		return 0;
	nPumpWaitingMessages ++;
	switch (wParam) {
	case 1:
		KillTimer(2);
		KillWMUserTimer(3);
		KillWMUserTimer(4);
		KillWMUserTimer(6);
		KillWMUserTimer(13);
		KillWMUserTimer(14);
		KillWMUserTimer(18);

		if (m_pDispWB2Thread2  &&  WaitForSingleObject(m_pDispWB2Thread2->m_hThread, 0) != WAIT_TIMEOUT) {
			delete m_pDispWB2Thread2;
			m_pDispWB2Thread2 = NULL;
		}
		if (m_pDispWB2Thread3  &&  WaitForSingleObject(m_pDispWB2Thread3->m_hThread, 0) != WAIT_TIMEOUT) {
			delete m_pDispWB2Thread3;
			m_pDispWB2Thread3 = NULL;
		}
		if (m_pDispStockAveThread  &&  WaitForSingleObject(m_pDispStockAveThread->m_hThread, 0) != WAIT_TIMEOUT) {
			delete m_pDispStockAveThread;
			m_pDispStockAveThread = NULL;
		}
		if (m_pDispRankingThread0  &&  WaitForSingleObject(m_pDispRankingThread0->m_hThread, 0) != WAIT_TIMEOUT) {
			delete m_pDispRankingThread0;
			m_pDispRankingThread0 = NULL;
		}
		if (m_pDispRankingThread1  &&  WaitForSingleObject(m_pDispRankingThread1->m_hThread, 0) != WAIT_TIMEOUT) {
			delete m_pDispRankingThread1;
			m_pDispRankingThread1 = NULL;
		}
		if (m_pDispRankingThread2  &&  WaitForSingleObject(m_pDispRankingThread2->m_hThread, 0) != WAIT_TIMEOUT) {
			delete m_pDispRankingThread2;
			m_pDispRankingThread2 = NULL;
		}
		if (m_pDispNewsThread0  &&  WaitForSingleObject(m_pDispNewsThread0->m_hThread, 0) != WAIT_TIMEOUT) {
			delete m_pDispNewsThread0;
			m_pDispNewsThread0 = NULL;
		}
		if (m_pDispNewsThread1  &&  WaitForSingleObject(m_pDispNewsThread1->m_hThread, 0) != WAIT_TIMEOUT) {
			delete m_pDispNewsThread1;
			m_pDispNewsThread1 = NULL;
		}
		if (m_hStockAveBeepThread  &&  WaitForSingleObject(m_hStockAveBeepThread, 0) != WAIT_TIMEOUT)
			CloseHandle(m_hStockAveBeepThread);
			m_hStockAveBeepThread = NULL;
		if (
			m_pDispWB2Thread2
			|| m_pDispWB2Thread3
			|| m_pDispStockAveThread
			|| m_pDispRankingThread0
			|| m_pDispRankingThread1
			|| m_pDispRankingThread2
			|| m_pDispNewsThread0
			|| m_pDispNewsThread1
			|| m_hStockAveBeepThread
		)
			SetWMUserTimer(100, wParam, NULL);
		else {
			m_Edit11.SetWindowText("E");
			PumpWaitingMessages();

			SaveState();

			if (! MoveFile(m_strTempRankingFPath, m_strRankingFPath))
				DispErrorLog("%s %s 移動エラー: %s\n", m_strTempRankingFPath, m_strRankingFPath, GetLastErrorMessage());
			if (! MoveFile(m_strTempRankingAllFPath, m_strRankingAllFPath))
				DispErrorLog("%s %s 移動エラー: %s\n", m_strTempRankingAllFPath, m_strRankingAllFPath, GetLastErrorMessage());

			for (int i = 0; ppszUrlLogin[i]; i ++)
				if (m_ppSession[i])
					delete m_ppSession[i];

			DestroyWindow();
		}
		break;
	case 3:
	case 4:
	case 6:
	case 13:
	case 14:
		{
			COleDateTime DtCur = COleDateTime::GetCurrentTime();
			int nDayOfWeek = DtCur.GetDayOfWeek();
			int nHour = DtCur.GetHour();
			int nMinute = DtCur.GetMinute();
			switch (wParam) {
			case 3:
				if (nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 6  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16)) {
					GetState();
					Sell();
					Disp();
				}
				SetWMUserTimer(1000, wParam, NULL);
				break;
			case 4:
//				if (nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 8  &&  nHour < 11  ||  nHour == 11  &&  nMinute <= 1  ||  nHour == 12  &&  nMinute >= 5  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16)) {
				if (nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 8  &&  nHour < 11  ||  nHour == 11  &&  nMinute <= 31  ||  nHour == 12  &&  nMinute >= 5  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16)) {
					static int nPreMinute = 0;
					if (! m_bLicenseCanceled  &&  (nMinute % 5  ||  nMinute == nPreMinute  ||  (nPreMinute = nMinute, ! (m_bLicenseCanceled = CheckLicense()))))
						DispStockAve();
				}
				SetWMUserTimer(1000, wParam, NULL);
				break;
			case 6:
//				if (nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 9  &&  nHour < 11  ||  nHour == 11  &&  nMinute <= 1  ||  nHour == 12  &&  nMinute >= 30  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16))
				if (nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 9  &&  nHour < 11  ||  nHour == 11  &&  nMinute <= 31  ||  nHour == 12  &&  nMinute >= 30  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16))
					if (! m_bLicenseCanceled)
						DispChart();
				SetWMUserTimer(2000, wParam, NULL);
				break;
			case 13:
//				if (nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 9  &&  nHour < 11  ||  nHour == 11  &&  nMinute <= 1  ||  nHour == 12  &&  nMinute >= 30  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16))
				if (nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 9  &&  nHour < 11  ||  nHour == 11  &&  nMinute <= 31  ||  nHour == 12  &&  nMinute >= 30  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16))
					if (! m_bLicenseCanceled)
						DispRanking(1);
				SetWMUserTimer(5000, wParam, NULL);
				break;
			case 14:
//				if (nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 8  &&  nHour < 11  ||  nHour == 11  &&  nMinute <= 1  ||  nHour == 12  &&  nMinute >= 5  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16))
				if (nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 8  &&  nHour < 11  ||  nHour == 11  &&  nMinute <= 31  ||  nHour == 12  &&  nMinute >= 5  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16))
					if (! m_bLicenseCanceled)
						DispRanking(2);
				SetWMUserTimer(10000, wParam, NULL);
			}
		}
		break;
	case 5:
		DispStockAve();
		break;
	case 7:
		DispChart(0);
		break;
	case 8:
		DispChart(1);
		break;
	case 9:
		if (m_pDispWB2Thread2)
			SetWMUserTimer(100, wParam, NULL);
		else
			DispChart(0);
		break;
	case 10:
		if (m_pDispWB2Thread3)
			SetWMUserTimer(100, wParam, NULL);
		else
			DispChart(1);
		break;
	case 11:
		if (m_pDispWB2Thread2)
			SetWMUserTimer(100, wParam, NULL);
		else {
			CheckRadioButton(IDC_RADIO10, IDC_RADIO11, IDC_RADIO10);
			DispChart(1);
		}
		break;
	case 12:
		if (m_pDispWB2Thread3)
			SetWMUserTimer(100, wParam, NULL);
		else {
			CheckRadioButton(IDC_RADIO10, IDC_RADIO11, IDC_RADIO11);
			DispChart(1);
		}
		break;
	case 15:
		DispRanking(0);
		break;
	case 16:
		DispRanking(1);
		break;
	case 17:
		DispRanking(2);
		break;
	case 18:
		DispNews();
		SetWMUserTimer((60 - COleDateTime::GetCurrentTime().GetSecond()) % 20 * 1000, wParam, NULL);
		break;
	case 19:
		DispNews();
		break;
	case 20:
		DispNews(1);
		break;
	case 21:
		{
			CWinThread* pDlThread;
			for (int i = 0; i < m_PaThreadTimeout.GetSize(); i ++) {
				pDlThread = (CWinThread *)m_PaThreadTimeout[i];
				if (WaitForSingleObject(pDlThread->m_hThread, 0) == WAIT_OBJECT_0) {
					if (pDlThread->IsKindOf(RUNTIME_CLASS(CDispWB2Thread)))
						delete (CDispWB2Thread *)pDlThread;
					else if (pDlThread->IsKindOf(RUNTIME_CLASS(CDispStockAveThread)))
						delete (CDispStockAveThread *)pDlThread;
					else if (pDlThread->IsKindOf(RUNTIME_CLASS(CDispRankingThread)))
						delete (CDispRankingThread *)pDlThread;
					else if (pDlThread->IsKindOf(RUNTIME_CLASS(CDispNewsThread)))
						delete (CDispNewsThread *)pDlThread;
					m_PaThreadTimeout.RemoveAt(i --);
					m_nDispStockAveThreadTimeoutCount --;
				}
			}
			m_Edit19.SetWindowText(IToA(m_nDispStockAveThreadTimeoutCount));
			if (m_PaThreadTimeout.GetSize())
				SetWMUserTimer(1000, wParam, NULL);
			else
				m_bChkThreadTimerRun = FALSE;
		}
		break;
	case 22:
		{
			int nTopIndex;

			nTopIndex = m_List4.GetTopIndex();
			if (nTopIndex > 0)
				m_List4.SetTopIndex(nTopIndex > 16 ? nTopIndex - 16 : 0);

			nTopIndex = m_List5.GetTopIndex();
			if (nTopIndex > 0)
				m_List5.SetTopIndex(nTopIndex > 5 ? nTopIndex - 5 : 0);

			nTopIndex = m_List6.GetTopIndex();
			if (nTopIndex > 0)
				m_List6.SetTopIndex(nTopIndex > 7 ? nTopIndex - 7 : 0);

			nTopIndex = m_List7.GetTopIndex();
			if (nTopIndex > 0)
				m_List7.SetTopIndex(nTopIndex > 5 ? nTopIndex - 5 : 0);

			nTopIndex = m_List8.GetTopIndex();
			if (nTopIndex > 0)
				m_List8.SetTopIndex(nTopIndex > 20 ? nTopIndex - 20 : 0);
		}
		break;
	case 23:
		{
			int nTopIndex;

			nTopIndex = m_List4.GetTopIndex();
			if (nTopIndex + 16 < m_List4.GetCount())
				m_List4.SetTopIndex(nTopIndex + 16);

			nTopIndex = m_List5.GetTopIndex();
			if (nTopIndex + 5 < m_List5.GetCount())
				m_List5.SetTopIndex(nTopIndex + 5);

			nTopIndex = m_List6.GetTopIndex();
			if (nTopIndex + 7 < m_List6.GetCount())
				m_List6.SetTopIndex(nTopIndex + 7);

			nTopIndex = m_List7.GetTopIndex();
			if (nTopIndex + 5 < m_List7.GetCount())
				m_List7.SetTopIndex(nTopIndex + 5);

			nTopIndex = m_List8.GetTopIndex();
			if (nTopIndex + 16 < m_List8.GetCount())
				m_List8.SetTopIndex(nTopIndex + 16);
		}
		break;
	case 24:
		m_Edit1.SetSel(0, -1);
		break;
	case 25:
		EntryStk();
		break;
	case 26:
		SetCheckedDiffPrice();
		break;
	case 27:
		if (! m_Btn15.IsWindowEnabled())
			m_Btn15.EnableWindow();
		break;
	case 28:
		if (m_Btn15.IsWindowEnabled())
			m_Btn15.EnableWindow(FALSE);
		break;
	case 29:
		if (m_WebBrowser23.GetLocationURL().GetLength())
			m_WebBrowser23.GetTopWindow()->GetTopWindow()->PostMessage(WM_HSCROLL, SB_PAGERIGHT);
		break;
	case 30:
		if (m_WebBrowser23.GetLocationURL().GetLength())
			m_WebBrowser23.GetTopWindow()->GetTopWindow()->PostMessage(WM_HSCROLL, SB_PAGELEFT);
		break;
	case 31:
		if (m_WebBrowser24.GetLocationURL().GetLength())
			m_WebBrowser24.GetTopWindow()->GetTopWindow()->PostMessage(WM_HSCROLL, SB_PAGERIGHT);
		break;
	case 32:
		if (m_WebBrowser24.GetLocationURL().GetLength())
			m_WebBrowser24.GetTopWindow()->GetTopWindow()->PostMessage(WM_HSCROLL, SB_PAGELEFT);
		break;
	case 34:
		KillTimer(33);
	}
	nPumpWaitingMessages --;
	return 0;
}

LRESULT CTradeHelperDlg::OnUser1(WPARAM wParam, LPARAM lParam)
{
	if (m_nSelStreamer)
		m_nSelStreamer --;

	if (m_nSelStreamer == 0) {
		if (lParam)
			m_List2.SetCurSel(lParam - 1);
		else {
			m_List2.SetCurSel(-1);
			m_List2.SetTopIndex(0);
		}

		OnSelchangeList2();

		if (m_nSetStreamer)
			m_nSetStreamer --;

		if (! lParam)
			EntryStk();
	}

	return 0;
}

LRESULT CTradeHelperDlg::OnUser2(WPARAM wParam, LPARAM lParam)
{
	if (! PreUser(wParam, lParam, OnUser2))
		return 0;
	nPumpWaitingMessages ++;

	int i;
	char pszBuf[MAX_PATH];
	CString strCode;
	int nSize = m_SaNiceCode.GetSize();
	CStringArray SaNiceCode;
	CWnd* pWnd = NULL;
	BOOL bStreamer = FALSE;
	CRect Rect;
	CPoint Point;

	SaNiceCode.Copy(m_SaNiceCode);

	m_SaNiceCode.RemoveAll();
	m_MstpNiceCode.RemoveAll();
	m_SaSelCode.RemoveAll();
	m_MstpSelCode.RemoveAll();
	for (i = 0; ; i ++)
		if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_CODE + IToA(i), pszX, pszBuf, MAX_PATH, m_strMeigaraIniFPath) == 1)
			break;
		else {
			strCode = pszBuf;
			m_SaNiceCode.Add(strCode);
			m_MstpNiceCode[strCode] = (void *)i;
			if (m_nSetStreamer  &&  (i >= nSize  ||  strCode != SaNiceCode[i])) {
				if (! pWnd)
//					if (pWnd = FindWindow(pszStreamerClassName, pszStreamerWndName)) {
					if (pWnd = FindWindow(NULL, m_strTradeConsoleWndName)) {
						::GetWindowRect(pWnd->m_hWnd, &Rect);
						if (Rect.left == 0  &&  Rect.top == 0  &&  Rect.right == 1003  &&  Rect.bottom == 516) {
							pWnd->SetForegroundWindow();
							::GetCursorPos(&Point);
							Sleep(100);
							bStreamer = TRUE;
						}
					}
				if (bStreamer)
					SetStreamer(i, strCode);
			}
		}
	if (pWnd) {
		::SetCursorPos(Point.x, Point.y);
		SetForegroundWindow();
	}
	if (m_nSetStreamer)
		m_nSetStreamer --;
	for (i = 0; ; i ++)
		if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_SELCODE + IToA(i), pszEmpty, pszBuf, MAX_PATH, m_strMeigaraIniFPath)) {
			strCode = pszBuf;
			m_SaSelCode.Add(strCode);
			m_MstpSelCode[strCode] = (void *)i;
		} else
			break;
	SetCodeList();

	if (m_nSetStreamer == 0  &&  m_nSelStreamer == 0) {
		m_List2.SetCurSel(-1);
		OnSelchangeList2();
	}

	nPumpWaitingMessages --;

	return 0;
}

LRESULT CTradeHelperDlg::OnUser3(WPARAM wParam, LPARAM lParam)
{
/*
	OnUser1(0, wParam);
	m_Edit2.SetWindowText(LToA(lParam));

	m_bUser3 = TRUE;
	OnButton5();
	m_bUser3 = FALSE;
*/

	return 0;
}

LRESULT CTradeHelperDlg::OnUser4(WPARAM wParam, LPARAM lParam)
{
/*
	CString strItem = IToA(wParam) + "/";
	int nIndex;

	if ((nIndex = m_List3.FindString(-1, strItem)) != LB_ERR)
		m_List3.SetCurSel(nIndex);
	else {
		m_List3.SetCurSel(-1);
		m_List3.SetTopIndex(0);
	}

	OnSelchangeList3();

	m_Edit3.SetWindowText(LToA(lParam));
	OnButton6();
*/

	return 0;
}

LRESULT CTradeHelperDlg::OnUser5(WPARAM wParam, LPARAM lParam)
{
	switch (wParam) {
	case 0:
		SetWMUserTimer(0U, 29, NULL);
		SetWMUserTimer(0U, 31, NULL);
		break;
	case 1:
		SetWMUserTimer(0U, 22, NULL);
		break;
	case 2:
		SetWMUserTimer(0U, 11, NULL);
		break;
	case 3:
		SetWMUserTimer(0U, 30, NULL);
		SetWMUserTimer(0U, 32, NULL);
		break;
	case 4:
		SetWMUserTimer(0U, 23, NULL);
		break;
	case 5:
		SetWMUserTimer(0U, 12, NULL);
		break;
	case 6:
		ButtonF2();
		break;
	case 7:
		ButtonF3();
		break;
	case 8:
		ButtonF4();
		break;
	case 9:
		ButtonF5();
		break;
	case 10:
		ButtonF6();
		break;
	case 11:
		ButtonF7();
		break;
	case 12:
		ButtonF8();
		break;
	case 13:
		ButtonF9();
		break;
	case 14:
		ButtonF11();
		break;
	default:
		ButtonF12();
	}

	return 0;
}

LRESULT CTradeHelperDlg::OnUser6(WPARAM wParam, LPARAM lParam)
{
	if (! PreUser(wParam, lParam, OnUser6))
		return 0;
	nPumpWaitingMessages ++;

	ReadInfo();
	m_MstmCodeMainCodeName.RemoveAll();
	SetCodeList();
	SetNewsList1();
	SetNewsList2();

	nPumpWaitingMessages --;

	return 0;
}

LRESULT CTradeHelperDlg::OnUser7(WPARAM wParam, LPARAM lParam)
{
	if (m_nExecMode == 2)
		DtsCurrentTime.SetDateTimeSpan(wParam, lParam / (60 * 60), lParam / 60 % 60, lParam % 60);

	SetWMUserTimer(0, 15, NULL);

	return 0;
}

LRESULT CTradeHelperDlg::OnUser8(WPARAM wParam, LPARAM lParam)
{
	if (! PreUser(wParam, lParam, OnUser8))
		return 0;
	nPumpWaitingMessages ++;

	if ((int)wParam >= 0)
		SellBack(wParam, lParam);
	else
		BuyBack(wParam, lParam);
	Disp();

	nPumpWaitingMessages --;

	return 0;
}

LRESULT CTradeHelperDlg::OnUser9(WPARAM wParam, LPARAM lParam)
{
	if (! PreUser(wParam, lParam, OnUser9))
		return 0;
	nPumpWaitingMessages ++;

	m_DwaGetStateWParam.Add(wParam);
	m_DwaGetStateLParam.Add(lParam);

	nPumpWaitingMessages --;

	return 0;
}

LRESULT CTradeHelperDlg::OnUser10(WPARAM wParam, LPARAM lParam)
{
	if (! PreUser(wParam, lParam, OnUser10))
		return 0;
	nPumpWaitingMessages ++;

	SetForegroundWindow();

	for (int i = 0, imax = m_DwaGetStateWParam.GetSize(); i < imax; ) {
		m_DwaGetStateReceiptNo.Add(m_DwaGetStateWParam[i]);
		m_UiaGetStateStatus.Add(m_DwaGetStateLParam[i ++]);
		m_DwaGetStateSuryo.Add(m_DwaGetStateWParam[i]);
		m_DwaGetStatePrice.Add(m_DwaGetStateLParam[i ++]);
		m_DwaGetStateSoldSuryo.Add(m_DwaGetStateWParam[i]);
		m_DwaGetStateSoldPrice.Add(m_DwaGetStateLParam[i ++]);
	}

	m_DwaGetStateWParam.RemoveAll();
	m_DwaGetStateLParam.RemoveAll();

	GetStateBack(wParam, lParam);
	Disp();

	m_DwaGetStateReceiptNo.RemoveAll();
	m_UiaGetStateStatus.RemoveAll();
	m_DwaGetStateSuryo.RemoveAll();
	m_DwaGetStatePrice.RemoveAll();
	m_DwaGetStateSoldSuryo.RemoveAll();
	m_DwaGetStateSoldPrice.RemoveAll();

	nPumpWaitingMessages --;

	return 0;
}

LRESULT CTradeHelperDlg::OnUser11(WPARAM wParam, LPARAM lParam)
{
	if (! PreUser(wParam, lParam, OnUser11))
		return 0;
	nPumpWaitingMessages ++;

	DelOdrBack(wParam, lParam);
	Disp();

	nPumpWaitingMessages --;

	return 0;
}

LRESULT CTradeHelperDlg::OnUser12(WPARAM wParam, LPARAM lParam)
{
	if (! PreUser(wParam, lParam, OnUser12))
		return 0;
	nPumpWaitingMessages ++;

	m_lChangeOdrWParam = wParam;
	m_lChangeOdrLParam = lParam;

	nPumpWaitingMessages --;

	return 0;
}

LRESULT CTradeHelperDlg::OnUser13(WPARAM wParam, LPARAM lParam)
{
	if (! PreUser(wParam, lParam, OnUser13))
		return 0;
	nPumpWaitingMessages ++;

	ChangeOdrBack(wParam, lParam);
	Disp();

	nPumpWaitingMessages --;

	return 0;
}

LRESULT CTradeHelperDlg::OnUser14(WPARAM wParam, LPARAM lParam)
{
	if (! PreUser(wParam, lParam, OnUser14))
		return 0;
	nPumpWaitingMessages ++;

	CWnd* pWndTradeConsole;
	CWnd* pWndMainExe;

	if ((pWndTradeConsole = FindWindow(NULL, m_strTradeConsoleWndName)) && (pWndMainExe = FindWindow(NULL, m_strMainExeWndName))) {
		CRect Rect;

		::GetWindowRect(pWndTradeConsole->m_hWnd, &Rect);
		if (Rect.left == 0  &&  Rect.top == 0  &&  Rect.right == 1003  &&  Rect.bottom == 516) {
			CPoint Point;
			CString strStk;

			pWndTradeConsole->SetForegroundWindow();
			::GetCursorPos(&Point);
			do {
				Sleep(100);
				PumpWaitingMessages();
			} while (GetKeyState(VK_SHIFT) < 0  ||  GetKeyState(VK_CONTROL) < 0);

			for (int i = 0; i < 10; i ++) {
				strStk = CopyStreamer(20, 84 + (453 - 75) / 9 * i);
				if (strStk.GetLength()) {
					m_nSelStreamer ++;
					pWndMainExe->PostMessage(WM_USER + 4, i + 1, atoi(strStk));
				}
			}

			::SetCursorPos(Point.x, Point.y);
			SetForegroundWindow();
		}
	}

	nPumpWaitingMessages --;

	return 0;
}

LRESULT CTradeHelperDlg::OnUser15(WPARAM wParam, LPARAM lParam)
{
	if (! PreUser(wParam, lParam, OnUser15))
		return 0;
	nPumpWaitingMessages ++;

	CWnd* pWnd;

	if (pWnd = FindWindow(NULL, m_strTradeConsoleWndName)) {
		CRect Rect;

		::GetWindowRect(pWnd->m_hWnd, &Rect);
		if (Rect.left == 0  &&  Rect.top == 0  &&  Rect.right == 1003  &&  Rect.bottom == 516) {
			CPoint Point;

			pWnd->SetForegroundWindow();
			::GetCursorPos(&Point);
			do {
				Sleep(100);
				PumpWaitingMessages();
			} while (GetKeyState(VK_SHIFT) < 0  ||  GetKeyState(VK_CONTROL) < 0);

			for (int i = 0; i < 10; i ++)
				DelStreamer(i);

			::SetCursorPos(Point.x, Point.y);
			SetForegroundWindow();
		}
	}

	nPumpWaitingMessages --;

	return 0;
}

BOOL CTradeHelperDlg::PreUser(WPARAM wParam, LPARAM lParam, USERPROC lpUserFunc)
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

BOOL CTradeHelperDlg::SetWMUserParam(UINT nIDEvent, WPARAM wParam, LPARAM lParam, USERPROC lpUserFunc)
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

void CTradeHelperDlg::SetWMUserTimer(UINT nElapse, WPARAM wParam, LPARAM lParam, USERPROC lpUserFunc)
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

void CTradeHelperDlg::KillWMUserTimer(WPARAM wParam)
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

void CTradeHelperDlg::AddOdr(int nMode)
{
	int i;
	int imax;
	CString strEdit1;
	CString strBuyPrice;
	CString strSellPrice;
	CString strSuryo;
	CString strTick;
	CString strEditState;
	CString strCode;
	int nReceiptNo = 0;
	int nState;
	long lBuyPrice;
	long lSellPrice;
	long lSuryo;
	int nTick;
	int nEditState;

	m_Edit1.GetWindowText(strEdit1);
	m_Edit2.GetWindowText(strBuyPrice);
	m_Edit3.GetWindowText(strSellPrice);
	m_Edit4.GetWindowText(strSuryo);
	m_Edit5.GetWindowText(strTick);
	m_Edit6.GetWindowText(strEditState);

	strBuyPrice.Replace(",", pszEmpty);
	strSellPrice.Replace(",", pszEmpty);

	lBuyPrice = atol(strBuyPrice);
	lSellPrice = atol(strSellPrice);
	lSuryo = atol(strSuryo);
	nTick = atoi(strTick);
	nEditState = atoi(strEditState);

	if (strEdit1.Find('/') == -1) {
		nReceiptNo = atoi(strEdit1);
		switch (nMode) {
		case 1:
		case 3:
			nState = 6;
			break;
		default:
			nState = 2;
		}

		for (i = 0, imax = m_UiaReceiptNo.GetSize(); i < imax; i ++)
			if ((int)m_UiaReceiptNo[i] == nReceiptNo) {
				nState = m_UiaState[i];
				break;
			}
	} else {
		strCode = strEdit1;
		switch (nMode) {
		case 1:
			nState = 5;
			break;
		case 2:
			nState = 8;
			break;
		case 3:
			nState = 9;
			break;
		default:
			nState = 1;
		}

		for (i = 0, imax = m_SaCode.GetSize(); i < imax; i ++)
			if (m_SaCode[i] == strCode  &&  m_UiaReceiptNo[i] == 0U)
				break;
	}

	if (i < imax) {
		m_UiaState[i] = nEditState;
		m_UiaTick[i] = nTick;
		if (m_bShift  ||  lBuyPrice != (long)m_DwaBuyPrice[i]  ||  lSuryo != (long)m_DwaSuryo[i]) {
			if (nEditState == 2  ||  nEditState  == 6)
				ChangeOdr(i, lBuyPrice, lSuryo);
		}
		if (m_bShift  ||  lSellPrice != (long)m_DwaSellPrice[i]) {
			if (nEditState == 4)
				ChangeOdr(i, lSellPrice, lSuryo);
			else
				if (lSellPrice >= (long)m_DwaBuyPrice[i]  ||  lSellPrice == 0L)
					m_DwaSellPrice[i] = lSellPrice;
		}
	} else {
		m_SaCode.Add(strCode);
		m_SaName.Add(pszEmpty);
		m_UiaReceiptNo.Add(nReceiptNo);
		m_UiaState.Add(nState);
		m_DwaBuyPrice.Add(lBuyPrice);
		m_DwaSellPrice.Add(lSellPrice);
		m_DwaSuryo.Add(0UL);
		m_DwaBuySoldSuryo.Add(0UL);
		m_DwaSellSuryo.Add(0UL);
		m_DwaSellSoldSuryo.Add(0UL);
		m_UiaTick.Add(nTick ? nTick : 1);
		m_WaUnit.Add(0);
		m_UiaSemiAuto.Add(FALSE);
	}
}

void CTradeHelperDlg::ChangeOdr(int nIndex, long lNewPrice, long lNewSuryo)
{
	long lPrice;
	long lSuryo;

	CString strCode;
	CString strName;
	short sUnit;
	int nNariSasiKbn;

	strCode = m_SaCode[nIndex];
	lPrice = m_DwaBuyPrice[nIndex];
	lSuryo = m_DwaSuryo[nIndex];

	if (lNewSuryo > lSuryo) {
		DispErrorLog("増数訂正エラー\n");
		return;
	}

	CodeToName(strCode, strName, NULL, &sUnit);

	if (m_bShift) {
		nNariSasiKbn = 1;
		lNewPrice = 0;
	} else
		nNariSasiKbn = 0;

	switch (m_UiaState[nIndex]) {
	case 2:
	case 6:
		if ((lNewPrice != 0  ||  lPrice != ~ 0UL)  &&  lNewPrice != lPrice) {
			long lZan;
			long lZanSuryo;
			long lDefaultSuryo;
			Info InfoWork;

			lZan = m_lZan + lPrice * lSuryo;
			if (lPrice == ~ 0UL) {
				if (! m_MstiCodeInfo.Lookup(strCode, InfoWork)) {
					DispErrorLog("銘柄情報検索エラー\n");
					return;
				}
				lPrice = InfoWork.lPreEndPrice + GetStopDiff(InfoWork.lPreEndPrice);
			}

#ifdef ZAN_TRADE
			lZanSuryo = (__min(lZan, ZAN_TRADE) - ZAN_OUTPUT) / (lPrice * sUnit);
#else
			lZanSuryo = (lZan - ZAN_OUTPUT) / (lPrice * sUnit);
#endif
#ifdef SURYO
			lDefaultSuryo = SURYO;
#else
			lDefaultSuryo = lZanSuryo;
			if (lDefaultSuryo >= 2  &&  m_Check6.GetCheck() == 1)
				lDefaultSuryo /= 2;
#endif
			lDefaultSuryo *= sUnit;

			if (lSuryo == lDefaultSuryo) {
				if (lPrice != ~ 0UL  &&  m_bShift) {
					if (! m_MstiCodeInfo.Lookup(strCode, InfoWork)) {
						DispErrorLog("銘柄情報検索エラー\n");
						return;
					}
					lNewPrice = InfoWork.lPreEndPrice + GetStopDiff(InfoWork.lPreEndPrice);
				}

#ifdef ZAN_TRADE
				lZanSuryo = (__min(lZan, ZAN_TRADE) - ZAN_OUTPUT) / (lNewPrice * sUnit);
#else
				lZanSuryo = (lZan - ZAN_OUTPUT) / (lNewPrice * sUnit);
#endif
#ifdef SURYO
				lDefaultSuryo = SURYO;
#else
				lDefaultSuryo = lZanSuryo;
				if (lDefaultSuryo >= 2  &&  m_Check6.GetCheck() == 1)
					lDefaultSuryo /= 2;
#endif
				if (! lZanSuryo  ||  lDefaultSuryo > lZanSuryo) {
					DispErrorLog("残高不足エラー\n");
					m_lZan = -1;
					return;
				}

				if (lDefaultSuryo < lSuryo)
					lNewSuryo = lDefaultSuryo;
			}
		}
	}
	lNewSuryo *= sUnit;

	CWnd* pWnd;
	if ((pWnd = FindWindow(NULL, m_strTradeConsoleWndName)) == NULL) {
		DispErrorLog("TradeConsole ウィンドウ検索エラー\n");
		return;
	}
	pWnd->PostMessage(WM_USER + 5, m_UiaReceiptNo[nIndex], lNewSuryo);
	pWnd->PostMessage(WM_USER + 6, ((lNewSuryo != lSuryo) << (1 + 1)) | ((lNewPrice != lPrice) << 1) | nNariSasiKbn, lNewPrice);
}

void CTradeHelperDlg::ChangeOdrBack(WPARAM wParam, LPARAM lParam)
{
	int i;
	int imax;
	for (i = 0, imax = m_UiaReceiptNo.GetSize(); i < imax; i ++)
		if ((int)m_UiaReceiptNo[i] == m_lChangeOdrWParam)
			break;

	if (m_lChangeOdrLParam < 0) {
		DispErrorLog("注文訂正エラー\n");
		return;
	}

	lParam = lParam ? lParam : ~ 0UL;

	switch (m_UiaState[i]) {
	case 2U:
	case 6U:
		DispLog(
			"%s 買訂 No.%05d %s %s %ld円 → %ld円 %ld株 → %ld株\n",
			GetCurrentTimeEx().Format("%H:%M:%S"),
			m_UiaReceiptNo[i], m_SaCode[i], StrConvHalfWidth(m_SaName[i]).Left(20), m_DwaBuyPrice[i], lParam, m_DwaSuryo[i], wParam
		);
		break;
	case 4U:
		DispLog(
			"%s 売訂 No.%05d %s %s %ld円 → %ld円\n",
			GetCurrentTimeEx().Format("%H:%M:%S"),
			m_UiaReceiptNo[i], m_SaCode[i], StrConvHalfWidth(m_SaName[i]).Left(20), m_DwaSellPrice[i], lParam
		);
	}
	MessageBeep(MB_OK);

	switch (m_UiaState[i]) {
	case 2U:
		m_UiaState[i] = 13U;
		break;
	case 6U:
		m_UiaState[i] = 14U;
		break;
	case 4U:
		m_UiaState[i] = 15U;
	}
}

void CTradeHelperDlg::DelOdr()
{
	if (m_nList3CurSel == LB_ERR  ||  m_nList3CurSel > m_UiaReceiptNo.GetUpperBound()  ||  (int)m_UiaReceiptNo[m_nList3CurSel] <= 0)
		return;

	CWnd* pWnd;
	if ((pWnd = FindWindow(NULL, m_strTradeConsoleWndName)) == NULL) {
		DispErrorLog("TradeConsole ウィンドウ検索エラー\n");
		return;
	}
	pWnd->PostMessage(WM_USER + 4, m_UiaReceiptNo[m_nList3CurSel]);
}

void CTradeHelperDlg::DelOdrBack(WPARAM wParam, LPARAM lParam)
{
	int i;
	int imax;
	for (i = 0, imax = m_UiaReceiptNo.GetSize(); i < imax; i ++)
		if ((int)m_UiaReceiptNo[i] == wParam)
			break;

	if (lParam < 0) {
		DispErrorLog("注文取消エラー\n");
		return;
	}

	switch (m_UiaState[i]) {
	case 2U:
	case 6U:
		DispLog(
			"%s 買消 No.%05d %s %s\n",
			GetCurrentTimeEx().Format("%H:%M:%S"),
			m_UiaReceiptNo[i], m_SaCode[i], StrConvHalfWidth(m_SaName[i]).Left(20)
		);
		break;
	case 4U:
		DispLog(
			"%s 売消 No.%05d %s %s\n",
			GetCurrentTimeEx().Format("%H:%M:%S"),
			m_UiaReceiptNo[i], m_SaCode[i], StrConvHalfWidth(m_SaName[i]).Left(20)
		);
	}
	MessageBeep(MB_OK);

	switch (m_UiaState[i]) {
	case 2U:
		m_UiaState[i] = 10U;
		break;
	case 6U:
		m_UiaState[i] = 11U;
		break;
	case 4U:
		m_UiaState[i] = 12U;
	}
}

void CTradeHelperDlg::SetCodeList()
{
	int i;
	int imax;
	CString strCode;
	CString strCodeEx;
	CString strName;

	m_List2.ResetContent();
	for (i = 0, imax = m_SaNiceCode.GetSize(); i < imax; i ++) {
		strCode = m_SaNiceCode[i];
		if (strCode.IsEmpty())
			m_List2.AddString(pszEmpty);
		else {
			CodeToName(strCode, strName, NULL, NULL, NULL, NULL, NULL, NULL, &strCodeEx);
			m_List2.AddString((strCodeEx + "  ").Left(8) + StrConvHalfWidth(strName));
		}
	}
	for (i = 0, imax = m_SaSelCode.GetSize(); i < imax; i ++) {
		strCode = m_SaSelCode[i];
		CodeToName(strCode, strName, NULL, NULL, NULL, NULL, NULL, NULL, &strCodeEx);
		m_List2.AddString((strCodeEx + "  ").Left(8) + StrConvHalfWidth(strName));
	}
}

void CTradeHelperDlg::SetNewsList1()
{
	int i;
	int imax;
	CString strCode;
	CString strCodeEx;
	CString strName;

	m_List6.ResetContent();
	for (i = 0, imax = m_SaNewsDateTime.GetSize(); i < imax; i ++) {
		strCode = m_SaNewsCode[i];
		CodeToName(strCode, strName, NULL, NULL, NULL, NULL, NULL, NULL, &strCodeEx);
		m_List6.AddString((strCodeEx + ' ').Left(7) + ' ' + (StrConvHalfWidth(strName) + "     ").Left(6) + ' ' + (' ' + m_SaNewsDateTime[i]).Right(5) + ' ' + m_SaNewsTitle[i]);
	}
}

void CTradeHelperDlg::SetNewsList2()
{
	int i;
	int imax;
	CString strCode;
	CString strCodeEx;
	CString strName;

	m_List7.ResetContent();
	for (i = 0, imax = m_SaNewsCode2.GetSize(); i < imax; i ++) {
		strCode = m_SaNewsCode2[i];
		CodeToName(strCode, strName, NULL, NULL, NULL, NULL, NULL, NULL, &strCodeEx);
		m_List7.AddString((strCodeEx + ' ').Left(7) + ' ' + (StrConvHalfWidth(strName) + CStringBuffer(' ', 15)).Left(16) + ' ' + m_SaNewsDateTime2[i]);
	}
}

void CTradeHelperDlg::EntryStk() 
{
	CString strCode;

	m_Edit1.GetWindowText(strCode);
	m_strEntryStk = strCode.Left(4);

	HGLOBAL hMem = NULL;
	BOOL bOpenClipboard = FALSE;
	do {
		if ((hMem = GlobalAlloc(GHND, m_strEntryStk.GetLength() + 1)) == NULL) {
			DispErrorLog("銘柄登録メモリ割り当てエラー: %s\n", GetLastErrorMessage());
			break;
		}
		LPVOID lpMem;
		if ((lpMem = GlobalLock(hMem)) == NULL) {
			DispErrorLog("銘柄登録メモリロックエラー: %s\n", GetLastErrorMessage());
			break;
		}
		lstrcpy((LPTSTR)lpMem, m_strEntryStk);
		if (! GlobalUnlock(hMem)  &&  GetLastError() != NO_ERROR) {
			DispErrorLog("銘柄登録メモリロック解除エラー: %s\n", GetLastErrorMessage());
			break;
		}
		if (! ::OpenClipboard(NULL)) {
			DispErrorLog("銘柄登録クリップボードオープンエラー: %s\n", GetLastErrorMessage());
			break;
		}
		bOpenClipboard = TRUE;
		// Remove the current Clipboard contents
		if(! EmptyClipboard()) {
			DispErrorLog("銘柄登録クリップボード削除エラー: %s\n", GetLastErrorMessage());
			break;
		}
		// For the appropriate data formats...
		if (SetClipboardData(CF_TEXT, hMem) == NULL)
			DispErrorLog("銘柄登録クリップボードデータ格納エラー: %s\n", GetLastErrorMessage());
		hMem = NULL;
	} while (0);
	if (bOpenClipboard  &&  ! CloseClipboard())
		DispErrorLog("銘柄登録クリップボードクローズエラー: %s\n", GetLastErrorMessage());
	if (hMem  &&  GlobalFree(hMem))
		DispErrorLog("銘柄登録メモリ解放エラー: %s\n", GetLastErrorMessage());
}

int CTradeHelperDlg::DlHtml(int nVerb, DWORD dwFlags, LPCTSTR lpszHeaders, LPCTSTR lpszOptional)
{
	int nRv = -1;

	int i;
	BOOL bReload = FALSE;
	DWORD dwStatusCode;
	char sz[DL_BUFLEN + 1];
	int nRdLen;
	CStringBuffer sbHtml;
	DWORD dwErr;

	srand( (unsigned)time( NULL ) );
	sbHtml = IToA(rand());

	m_pFile = NULL;

	for (i = 0; i < 80; i ++) {
		if (m_pFile) {
			m_pFile->Close();
			delete m_pFile;
			m_pFile = NULL;
		}

		if (bReload)
			dwFlags |= INTERNET_FLAG_RELOAD;

		try
		{
			m_pFile = m_pServer->OpenRequest(nVerb, m_strObject, NULL, 1, NULL, NULL, dwFlags | INTERNET_FLAG_DONT_CACHE);

			m_pFile->SendRequest(lpszHeaders, lpszHeaders ? strlen(lpszHeaders) : 0, (LPVOID)lpszOptional, lpszOptional ? strlen(lpszOptional) : 0);

			if (m_pFile->QueryInfoStatusCode(dwStatusCode) == 0) {
				DispErrorLog("QueryInfoStatusCode Error: %s\n", GetLastErrorMessage());
				break;
			}

			if (dwStatusCode != HTTP_STATUS_OK) {
				DispErrorLog("HttpStatus Error: %s\n", GetHttpStatusText(dwStatusCode));

				switch (dwStatusCode) {
				case HTTP_STATUS_FORBIDDEN:
				case HTTP_STATUS_SERVER_ERROR:
				case HTTP_STATUS_BAD_GATEWAY:
					Sleep(250);
					bReload = TRUE;
					continue;
				}

				break;
			}

			m_sbHtml.Empty();
			while (nRdLen = m_pFile->Read(sz, DL_BUFLEN)) {
				sz[nRdLen] = '\0';
				m_sbHtml += sz;
			}

			if (StrReverseFindEx(m_sbHtml, "</html>", true) == -1) {
				DispErrorLog("Http Read Error\n");

				if (m_sbHtml == sbHtml)
					break;
				sbHtml = m_sbHtml;
				Sleep(250);
				bReload = TRUE;
				continue;
			}

			nRv = 0;
		}
		catch (CInternetException* pEx) {
			dwErr = pEx->m_dwError;
			DispErrorLog("ダウンロードエラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();

			if (
				dwErr == ERROR_INTERNET_TIMEOUT
				||  dwErr == ERROR_INTERNET_NAME_NOT_RESOLVED
				||  dwErr == ERROR_INTERNET_CANNOT_CONNECT
//				||  dwErr == ERROR_INTERNET_CONNECTION_RESET
				||  dwErr == ERROR_HTTP_INVALID_SERVER_RESPONSE
			) {
				Sleep(250);
				bReload = TRUE;
				continue;
			}
		}
		catch (CException* pEx) {
			DispErrorLog("ダウンロードエラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();
		}

		break;
	}

	if (m_pFile) {
		m_pFile->Close();
		delete m_pFile;
	}

	return nRv;
}

int CTradeHelperDlg::GetState(int nMode)
{
	int nRv = -1;

	int i;
	int imax;
	int nState;
	CKehai0 KehaiWork;

	for (i = 0, imax = m_UiaState.GetSize(); i < imax; i ++) {
		nState = m_UiaState[i];
		if (nState != 7  &&  nState < 100)
			if (nState == 2  ||  nState == 4  ||  nState == 6) {
				if (m_SaCode[i] == m_strKehaiCode  &&  GetKehai(m_sbKehaiHtml, KehaiWork))
					if (nState == 4) {
						if (KehaiWork.m_plKehaiPrice[4] >= (long)m_DwaSellPrice[i])
							break;
					} else {
						if (KehaiWork.m_plKehaiPrice[5] <= (long)m_DwaBuyPrice[i])
							break;
					}
			} else
				break;
	}

//	if ((nHour >= 9  &&  nHour < 11  ||  (nHour == 12  &&  nMinute >= 30  ||  nHour >= 13)  &&  nHour < 15)  &&  i < imax) {
	if (i < imax  ||  m_lZan == -1  ||  m_bSelchangeList3  ||  nMode) {
		CString strEdit11;
		m_Edit11.GetWindowText(strEdit11);
		if (strEdit11.IsEmpty()) {
			CWnd* pWnd;
			if ((pWnd = FindWindow(NULL, m_strTradeConsoleWndName)) == NULL)
				goto CleanUp;
			pWnd->PostMessage(WM_USER + 3);

			m_Edit11.SetWindowText("○");
		}
		m_bSelchangeList3 = FALSE;
	}

	nRv = 0;

CleanUp:

	return nRv;
}

int CTradeHelperDlg::GetStateBack(WPARAM wParam, LPARAM lParam)
{
	int nRv = -1;

	int i;
	int j;
	int imax;
	int jmax;

	CString strCode;
	long lSuryo;
	long lSoldSuryo;
	int nReceiptNo;
	CString strName;
	long lPrice;
	long lSoldPrice;
	long lDiff;
	BOOL bSold;
	BOOL bCanceled;
	BOOL bChanged;
	CWnd* pWnd;

	if (lParam < 0) {
		DispErrorLog("約定状態取得エラー\n");
		goto CleanUp;
	}

	for (i = 0, imax = m_DwaGetStateReceiptNo.GetSize(); i < imax; i ++) {
		nReceiptNo = m_DwaGetStateReceiptNo[i];
		bSold = m_UiaGetStateStatus[i] & 0x2;
		bCanceled = m_UiaGetStateStatus[i] & 0x1;
		lSuryo = m_DwaGetStateSuryo[i];
		lPrice = m_DwaGetStatePrice[i];
		lSoldSuryo = m_DwaGetStateSoldSuryo[i];
		lSoldPrice = m_DwaGetStateSoldPrice[i];

		for (j = 0, jmax = m_UiaReceiptNo.GetSize(); j < jmax; j ++)
			if ((int)m_UiaReceiptNo[j] == nReceiptNo)
				break;
		if (j == jmax)
			continue;

		bChanged =
			(m_UiaGetStateStatus[i] & 0x4) == 0
			&&  (
				m_UiaState[j] >= 13U  &&  m_UiaState[j] <= 14U  &&  (lSuryo != (long)m_DwaSuryo[j]  ||  lPrice != (long)m_DwaBuyPrice[j])
				||  m_UiaState[j] == 15U  &&  (lSuryo != (long)m_DwaSellSuryo[j]  ||  lPrice != (long)m_DwaSellPrice[j])
			);

		strCode = m_SaCode[j];
		CodeToName(strCode, strName);
		strName = StrConvHalfWidth(strName);

		if (bSold || bCanceled || bChanged) {
			m_SaCode[j] = strCode;
			m_SaName[j] = strName;

			/*
				1 - 買（買売）
				2 - 買待（買売）
				3 - 売
				4 - 売待
				5 - 買↑
				6 - 買待
				7 - 所有中
				8 - 買↑（買売）
				9 - 買
				10 - 消待（買売）
				11 - 消待（買）
				12 - 消待（売）
				13 - 訂待（買売）
				14 - 訂待（買）
				15 - 訂待（売）
				101 - 買注（買売）
				103 - 売注
				105 - 買注↑
				108 - 買注↑（買売）
				109 - 買注
			*/
			if (bSold || bChanged) {
				switch (m_UiaState[j]) {
				case 13U:
				case 14U:
					if (bChanged) {
						DispLog(
							"%s 買訂済 No.%05d %s %s %ld円 → %ld円 %ld株 → %ld株\n",
							GetCurrentTimeEx().Format("%H:%M:%S"),
							nReceiptNo, strCode, strName.Left(20), m_DwaBuyPrice[j], lPrice, m_DwaSuryo[j], lSuryo
						);
						MessageBeep(MB_OK);

						m_DwaBuyPrice[j] = lPrice;
						m_DwaSuryo[j] = lSuryo;
						m_lZan = -1;
					} else {
						DispLog(
							"%s 買訂E No.%05d %s %s %ld円 → %ld円 %ld株 → %ld株\n",
							GetCurrentTimeEx().Format("%H:%M:%S"),
							nReceiptNo, strCode, strName.Left(20), m_DwaBuyPrice[j], lPrice, m_DwaSuryo[j], lSuryo
						);
						MessageBeep(MB_OK);

						m_DwaBuyPrice[j] = lSoldPrice;

						if (m_UiaState[j] == 14) {
							lDiff = GetDiff(lSoldPrice + 1L);
							m_DwaSellPrice[j] = (lSoldPrice + lDiff - 1L) / lDiff * lDiff;
						}

						m_lZan = -1;
					}
					break;
				case 15U:
					if (bChanged) {
						DispLog(
							"%s 売訂済 No.%05d %s %s %ld円 → %ld円\n",
							GetCurrentTimeEx().Format("%H:%M:%S"),
							nReceiptNo, strCode, strName.Left(20), m_DwaSellPrice[j], lPrice
						);
						MessageBeep(MB_OK);

						m_DwaSellPrice[j] = lPrice;
					} else {
						DispLog(
							"%s 売訂E No.%05d %s %s %ld円 → %ld円\n",
							GetCurrentTimeEx().Format("%H:%M:%S"),
							nReceiptNo, strCode, strName.Left(20), m_DwaSellPrice[j], lPrice
						);
						MessageBeep(MB_OK);

						m_DwaSellPrice[j] = lSoldPrice;
						m_lZan = -1;
					}
				}
				switch (m_UiaState[j]) {
				case 13U:
					m_UiaState[j] = 2U;
					SaveState();
					break;
				case 14U:
					m_UiaState[j] = 6U;
					SaveState();
					break;
				case 15U:
					m_UiaState[j] = 4U;
					SaveState();
				}
			}
			switch (m_UiaState[j]) {
			case 2U:
			case 6U:
				if (lSoldSuryo > (long)m_DwaBuySoldSuryo[j]) {
					DispLog(
						"%s 買済 No.%05d %s %s %ld円 x%ld/%ld\n",
						GetCurrentTimeEx().Format("%H:%M:%S"),
						nReceiptNo, strCode, strName.Left(20), lSoldPrice, lSoldSuryo - m_DwaBuySoldSuryo[j], lSuryo
					);
					MessageBeep(MB_ICONEXCLAMATION);

					switch (m_UiaState[j]) {
					case 2U:
#ifdef TIMESFREE
						if (lSoldSuryo > (long)__max(m_DwaBuySoldSuryo[j], m_DwaSellSuryo[j])) {
#else
						if (lSoldSuryo == lSuryo) {
#endif
							m_UiaState[j] = 3U;

							if (m_DwaSellPrice[j] == 0UL) {
								lDiff = GetDiff(lSoldPrice + 1L);
								m_DwaSellPrice[j] = lSoldPrice / lDiff * lDiff + lDiff * GetTick(lSoldPrice, m_WaUnit[j]) * m_UiaTick[j];
							}
						}
						break;
					default:
						if (lSoldSuryo == lSuryo) {
							if (m_UiaSemiAuto[j]  &&  (pWnd = FindWindow(NULL, m_strMainExeWndName)))
								pWnd->PostMessage(WM_USER + 2, atoi(strCode.Left(4)), lSoldPrice);

							m_UiaState[j] = 7U;
						}

						if (m_DwaSellPrice[j] == 0UL) {
							lDiff = GetDiff(lSoldPrice + 1L);
							m_DwaSellPrice[j] = (lSoldPrice + lDiff - 1L) / lDiff * lDiff;
						}
					}

					m_DwaBuyPrice[j] = lSoldPrice;
					m_DwaSuryo[j] = lSuryo;
					m_DwaBuySoldSuryo[j] = lSoldSuryo;

					m_lZan = -1;

					SaveState();
				}
				break;
			case 4U:
				if (lSoldSuryo > (long)m_DwaSellSoldSuryo[j]) {
					DispLog(
						"%s 売済 No.%05d %s %s %ld円 x%ld/%ld\n",
						GetCurrentTimeEx().Format("%H:%M:%S"),
						nReceiptNo, strCode, strName.Left(20), lSoldPrice, lSoldSuryo - m_DwaSellSoldSuryo[j], lSuryo
					);
					MessageBeep(MB_ICONASTERISK);

					m_DwaSellSoldSuryo[j] = lSoldSuryo;

					m_lZan = -1;
				}

				if (lSoldSuryo == lSuryo) {
					if (m_UiaSemiAuto[j]  &&  (pWnd = FindWindow(NULL, m_strMainExeWndName)))
						pWnd->PostMessage(WM_USER + 3, atoi(strCode.Left(4)), lSoldPrice);

					if (m_nList3CurSel == j)
						m_nList3CurSel = LB_ERR;

					m_SaCode.RemoveAt(j);
					m_SaName.RemoveAt(j);
					m_UiaReceiptNo.RemoveAt(j);
					m_UiaState.RemoveAt(j);
					m_DwaBuyPrice.RemoveAt(j);
					m_DwaSellPrice.RemoveAt(j);
					m_DwaSuryo.RemoveAt(j);
					m_DwaBuySoldSuryo.RemoveAt(j);
					m_DwaSellSuryo.RemoveAt(j);
					m_DwaSellSoldSuryo.RemoveAt(j);
					m_UiaTick.RemoveAt(j);
					m_WaUnit.RemoveAt(j);
					m_UiaSemiAuto.RemoveAt(j);
				}

				SaveState();
				break;
			case 10U:
			case 11U:
				if (bCanceled  ||  bSold  &&  lSuryo == lSoldSuryo  &&  lSuryo == (long)m_DwaSuryo[j]  &&  lSoldSuryo == (long)m_DwaBuySoldSuryo[j]) {
					DispLog(
						"%s 買消済 No.%05d %s %s\n",
						GetCurrentTimeEx().Format("%H:%M:%S"),
						nReceiptNo, strCode, strName.Left(20)
					);
					MessageBeep(MB_OK);

					if (m_nList3CurSel == j)
						m_nList3CurSel = LB_ERR;

					m_SaCode.RemoveAt(j);
					m_SaName.RemoveAt(j);
					m_UiaReceiptNo.RemoveAt(j);
					m_UiaState.RemoveAt(j);
					m_DwaBuyPrice.RemoveAt(j);
					m_DwaSellPrice.RemoveAt(j);
					m_DwaSuryo.RemoveAt(j);
					m_DwaBuySoldSuryo.RemoveAt(j);
					m_DwaSellSuryo.RemoveAt(j);
					m_DwaSellSoldSuryo.RemoveAt(j);
					m_UiaTick.RemoveAt(j);
					m_WaUnit.RemoveAt(j);
					m_UiaSemiAuto.RemoveAt(j);

					m_lZan = -1;

					SaveState();
				} else if (bSold) {
					DispLog(
						"%s 買消E No.%05d %s %s %ld円 x%ld/%ld\n",
						GetCurrentTimeEx().Format("%H:%M:%S"),
						nReceiptNo, strCode, strName.Left(20), lSoldPrice, lSoldSuryo - m_DwaBuySoldSuryo[j], lSuryo
					);
					MessageBeep(MB_ICONEXCLAMATION);

					switch (m_UiaState[j]) {
					case 10U:
#ifdef TIMESFREE
						if (lSoldSuryo > (long)__max(m_DwaBuySoldSuryo[j], m_DwaSellSuryo[j])) {
#else
						if (lSoldSuryo == lSuryo) {
#endif
							m_UiaState[j] = 3U;

							if (m_DwaSellPrice[j] == 0UL) {
								lDiff = GetDiff(lSoldPrice + 1L);
								m_DwaSellPrice[j] = lSoldPrice / lDiff * lDiff + lDiff * GetTick(lSoldPrice, m_WaUnit[j]) * m_UiaTick[j];
							}
						}
						break;
					default:
						if (lSoldSuryo == lSuryo) {
							if (m_UiaSemiAuto[j]  &&  (pWnd = FindWindow(NULL, m_strMainExeWndName)))
								pWnd->PostMessage(WM_USER + 2, atoi(strCode.Left(4)), lSoldPrice);

							m_UiaState[j] = 7U;
						}

						if (m_DwaSellPrice[j] == 0UL) {
							lDiff = GetDiff(lSoldPrice + 1L);
							m_DwaSellPrice[j] = (lSoldPrice + lDiff - 1L) / lDiff * lDiff;
						}
					}

					m_DwaBuyPrice[j] = lSoldPrice;
					m_DwaSuryo[j] = lSuryo;
					m_DwaBuySoldSuryo[j] = lSoldSuryo;

					m_lZan = -1;

					SaveState();
				}
				break;
			case 12U:
				if (bCanceled  ||  bSold  &&  lSoldSuryo == (long)m_DwaSellSoldSuryo[j]) {
					DispLog(
						"%s 売消済 No.%05d %s %s\n",
						GetCurrentTimeEx().Format("%H:%M:%S"),
						nReceiptNo, strCode, strName.Left(20)
					);
					MessageBeep(MB_OK);

					m_UiaState[j] = 7U;
					m_DwaSellSuryo[j] = m_DwaSellSoldSuryo[j];

					SaveState();
				} else if (bSold) {
					DispLog(
						"%s 売消E No.%05d %s %s %ld円 x%ld/%ld\n",
						GetCurrentTimeEx().Format("%H:%M:%S"),
						nReceiptNo, strCode, strName.Left(20), lSoldPrice, lSoldSuryo - m_DwaSellSoldSuryo[j], lSuryo
					);
					MessageBeep(MB_ICONASTERISK);

					if (lSoldSuryo == lSuryo) {
						if (m_UiaSemiAuto[j]  &&  (pWnd = FindWindow(NULL, m_strMainExeWndName)))
							pWnd->PostMessage(WM_USER + 3, atoi(strCode.Left(4)), lSoldPrice);

						if (m_nList3CurSel == j)
							m_nList3CurSel = LB_ERR;

						m_SaCode.RemoveAt(j);
						m_SaName.RemoveAt(j);
						m_UiaReceiptNo.RemoveAt(j);
						m_UiaState.RemoveAt(j);
						m_DwaBuyPrice.RemoveAt(j);
						m_DwaSellPrice.RemoveAt(j);
						m_DwaSuryo.RemoveAt(j);
						m_DwaBuySoldSuryo.RemoveAt(j);
						m_DwaSellSuryo.RemoveAt(j);
						m_DwaSellSoldSuryo.RemoveAt(j);
						m_UiaTick.RemoveAt(j);
						m_WaUnit.RemoveAt(j);
						m_UiaSemiAuto.RemoveAt(j);
					}

					m_lZan = -1;

					SaveState();
				}
			}
		}
	}

	if (m_lZan == -1)
		m_lZan = wParam;

	nRv = 0;

CleanUp:
	m_Edit11.SetWindowText(pszEmpty);

	return nRv;
}

void CTradeHelperDlg::Sell()
{
	int i;
	int imax;
	long lPrice;
	int nReceiptNo;
	CString strName;

	CString strCode;
	CString strMeigCd;
	int nMeigCd;
	long lSuryo;
	int nNariSasiKbn;
	long lKakaku;
	int nYukokikan;
	CWnd* pWnd;

	for (i = 0, imax = m_UiaReceiptNo.GetSize(); i < imax; i ++)
		if (m_UiaState[i] == 3U) {
			lPrice = m_DwaSellPrice[i];

			strCode = m_SaCode[i];
			strMeigCd = strCode.Left(4);
			if (m_bShift) {
				nNariSasiKbn = 1;
				lKakaku = 0;
				nYukokikan = 1;
			} else {
				nNariSasiKbn = 0;
				lKakaku = lPrice;
//				nYukokikan = 0;
				nYukokikan = 1;
			}

			lSuryo = m_DwaBuySoldSuryo[i] - m_DwaSellSuryo[i];

			if ((pWnd = FindWindow(NULL, m_strTradeConsoleWndName)) == NULL) {
				DispErrorLog("TradeConsole ウィンドウ検索エラー\n");
				if (m_DwaSellSuryo[i] < m_DwaSuryo[i])
					m_UiaState[i] = 2U;
				else
					m_UiaState[i] = 7U;
				return;
			}
			nReceiptNo = m_UiaReceiptNo[i];
			nMeigCd = atoi(strMeigCd);
			pWnd->PostMessage(WM_USER + 1, nReceiptNo, lSuryo);
			pWnd->PostMessage(WM_USER + 2, (nMeigCd << (1 + 1 + 1)) | (1 << (1 + 1)) | (nYukokikan << 1) | nNariSasiKbn, lKakaku);

			lPrice = m_bShift ? ~ 0UL : lPrice;

			m_UiaState[i] = 103U;
			m_DwaSellPrice[i] = lPrice;

			SaveState();
		}
}

void CTradeHelperDlg::SellBack(WPARAM wParam, LPARAM lParam)
{
	int i;
	int imax;
	long lPrice;
	int nReceiptNo = lParam;
	CString strName;

	CString strCode;
	CString strMeigCd;
	long lSuryo;
	CString strStkName;

	for (i = 0, imax = m_UiaReceiptNo.GetSize(); i < imax; i ++)
		if ((int)m_UiaReceiptNo[i] == wParam) {
			lPrice = m_DwaSellPrice[i];
			strCode = m_SaCode[i];
			strName = m_SaName[i];
			lSuryo = m_DwaBuySoldSuryo[i] - m_DwaSellSuryo[i];

			DispLog(
				"%s 売 No.%05d → No.%05d %s %s %ld円 x%ld/%ld\n",
				GetCurrentTimeEx().Format("%H:%M:%S"),
				wParam, nReceiptNo, strCode, StrConvHalfWidth(strName).Left(20), lPrice, lSuryo, m_DwaSuryo[i]
			);
			MessageBeep(MB_OK);

			m_SaCode.Add(strCode);
			m_SaName.Add(strName);
			m_UiaReceiptNo.Add(nReceiptNo);
			m_UiaState.Add(4U);
			m_DwaBuyPrice.Add(m_DwaBuyPrice[i]);
			m_DwaSellPrice.Add(lPrice);
			m_DwaSuryo.Add(lSuryo);
			m_DwaBuySoldSuryo.Add(lSuryo);
			m_DwaSellSuryo.Add(lSuryo);
			m_DwaSellSoldSuryo.Add(0UL);
			m_UiaTick.Add(m_UiaTick[i]);
			m_WaUnit.Add(m_WaUnit[i]);
			m_UiaSemiAuto.Add(m_UiaSemiAuto[i]);

			m_DwaSellSuryo[i] += lSuryo;

			if (m_DwaSellSuryo[i] < m_DwaSuryo[i])
				m_UiaState[i] = 2U;
			else {
				if (m_nList3CurSel == i)
					m_nList3CurSel = LB_ERR;

				m_SaCode.RemoveAt(i);
				m_SaName.RemoveAt(i);
				m_UiaReceiptNo.RemoveAt(i);
				m_UiaState.RemoveAt(i);
				m_DwaBuyPrice.RemoveAt(i);
				m_DwaSellPrice.RemoveAt(i);
				m_DwaSuryo.RemoveAt(i);
				m_DwaBuySoldSuryo.RemoveAt(i);
				m_DwaSellSuryo.RemoveAt(i);
				m_DwaSellSoldSuryo.RemoveAt(i);
				m_UiaTick.RemoveAt(i);
				m_WaUnit.RemoveAt(i);
				m_UiaSemiAuto.RemoveAt(i);

				i --;
				imax --;
			}

			SaveState();
		}
}

void CTradeHelperDlg::Buy()
{
	int i;
	int imax;
	long lPrice;
	int nReceiptNo;

	BOOL bData;
	CString strCode;
	CString strName;
	short sUnit;
	CKehai0 KehaiWork;
	long lZan;
	long lZanSuryo;
	long lSuryo;
	CString strSuryo;
	CString strMeigCd;
	int nMeigCd;
	int nNariSasiKbn;
	int nYukokikan;
	long lKakaku;
	void* pVoid;
	Info InfoWork;
	CWnd* pWnd;

	for (i = 0, imax = m_SaCode.GetSize(); i < imax; i ++)
		if (m_UiaState[i] == 1U  ||  m_UiaState[i] == 5U  ||  m_UiaState[i] == 8U  ||  m_UiaState[i] == 9U) {
			strCode = m_SaCode[i];
			lPrice = m_DwaBuyPrice[i];

			bData = FALSE;

			if (lPrice == 0L)
				if (GetKehai(m_sbKehaiHtml, KehaiWork)) {
					DispErrorLog("複数気配取得エラー\n");
					continue;
				}
			CodeToName(strCode, strName, NULL, &sUnit);

			if (lPrice == 0L)
				if (m_bCtrl) {
					lPrice = KehaiWork.m_plKehaiPrice[4];
					if (! (m_UiaState[i] == 5U  ||  m_UiaState[i] == 8U))
						lPrice -= GetDiff(lPrice);
//				} else if (m_bShift) {
//					lPrice = KehaiWork.m_plKehaiPrice[4] + GetDiff(lPrice) * 2;
//					m_bShift = FALSE;
				} else {
					lPrice = KehaiWork.m_plKehaiPrice[5];
					if (m_UiaState[i] == 5U  ||  m_UiaState[i] == 8U)
						lPrice += GetDiff(lPrice + 1L);
				}

			strMeigCd = strCode.Left(4);
			if (m_bShift) {
				nNariSasiKbn = 1;
				lKakaku = 0;
				nYukokikan = 1;
			} else {
				nNariSasiKbn = 0;
				lKakaku = lPrice;
//				nYukokikan = 0;
				nYukokikan = 1;
			}

			lZan = m_lZan;
			if (m_bShift) {
				if (! m_MstiCodeInfo.Lookup(strCode, InfoWork)) {
					DispErrorLog("銘柄情報検索エラー\n");
					goto DataCleanUp;
				}
				lPrice = InfoWork.lPreEndPrice + GetStopDiff(InfoWork.lPreEndPrice);
			}

#ifdef ZAN_TRADE
			lZanSuryo = (__min(lZan, ZAN_TRADE) - ZAN_OUTPUT) / (lPrice * sUnit);
#else
			lZanSuryo = (lZan - ZAN_OUTPUT) / (lPrice * sUnit);
#endif
#ifdef SURYO
			lSuryo = SURYO;
#else
			m_Edit4.GetWindowText(strSuryo);
			if (strSuryo.IsEmpty()) {
				lSuryo = lZanSuryo;
				if (lSuryo >= 2  &&  m_Check6.GetCheck() == 1)
					lSuryo /= 2;
			} else
				lSuryo = atol(strSuryo);
#endif
			if (! lZanSuryo  ||  lSuryo > lZanSuryo) {
				DispErrorLog("残高不足エラー\n");
				m_lZan = -1;
				goto DataCleanUp;
			}
			lSuryo *= sUnit;

			if ((pWnd = FindWindow(NULL, m_strTradeConsoleWndName)) == NULL) {
				DispErrorLog("TradeConsole ウィンドウ検索エラー\n");
				goto DataCleanUp;
			}
			nReceiptNo = m_nDummyReceiptNo;
			if (-- m_nDummyReceiptNo >= 0)
				m_nDummyReceiptNo = -1;
			nMeigCd = atoi(strMeigCd);
			pWnd->PostMessage(WM_USER + 1, nReceiptNo, lSuryo);
			pWnd->PostMessage(WM_USER + 2, (nMeigCd << (1 + 1 + 1)) | (0 << (1 + 1)) | (nYukokikan << 1) | nNariSasiKbn, lKakaku);

			bData = TRUE;

DataCleanUp:
			if (! bData) {
				if (m_nList3CurSel == i)
					m_nList3CurSel = LB_ERR;

				m_SaCode.RemoveAt(i);
				m_SaName.RemoveAt(i);
				m_UiaReceiptNo.RemoveAt(i);
				m_UiaState.RemoveAt(i);
				m_DwaBuyPrice.RemoveAt(i);
				m_DwaSellPrice.RemoveAt(i);
				m_DwaSuryo.RemoveAt(i);
				m_DwaBuySoldSuryo.RemoveAt(i);
				m_DwaSellSuryo.RemoveAt(i);
				m_DwaSellSoldSuryo.RemoveAt(i);
				m_UiaTick.RemoveAt(i);
				m_WaUnit.RemoveAt(i);
				m_UiaSemiAuto.RemoveAt(i);

				i --;
				imax --;

				continue;
			}

			lPrice = m_bShift ? ~ 0UL : lPrice;

			switch (m_UiaState[i]) {
			case 1U:
				m_UiaState[i] = 101U;
				break;
			case 8U:
				m_UiaState[i] = 108U;
				break;
			case 5U:
				m_UiaState[i] = 105U;
				break;
			case 9U:
				m_UiaState[i] = 109U;
			}

			m_SaName[i] = strName;
			m_UiaReceiptNo[i] = nReceiptNo;
			m_DwaBuyPrice[i] = lPrice;
			m_DwaSuryo[i] = lSuryo;
			m_WaUnit[i] = sUnit;
			if (m_bUser3)
				m_UiaSemiAuto[i] = TRUE;

			if (! m_MstpNiceCode.Lookup(strCode, pVoid)) {
				CWnd* pWnd;
				if ((pWnd = FindWindow(NULL, m_strMainExeWndName))) {
					int nIndex0 = 9;
					if (nIndex0 > m_SaNiceCode.GetUpperBound()  ||  m_SaNiceCode[nIndex0].Left(4) != strMeigCd) {
						m_nSetStreamer ++;
						m_nSelStreamer ++;
						pWnd->PostMessage(WM_USER + 4, nIndex0 + 1, nMeigCd);
					}
				}
			}

			SaveState();

			break;
		}
}

void CTradeHelperDlg::BuyBack(WPARAM wParam, LPARAM lParam)
{
	int i;
	int imax;
	long lPrice;
	int nReceiptNo = lParam;

	CString strCode;
	CString strName;
	long lSuryo;

	for (i = 0, imax = m_UiaReceiptNo.GetSize(); i < imax; i ++)
		if ((int)m_UiaReceiptNo[i] == wParam) {
			if (nReceiptNo < 0) {
				switch (nReceiptNo) {
				case -2:
					DispErrorLog("受付番号取得エラー\n");
					break;
				default:
					DispErrorLog("買い注文エラー\n");
				}

				if (m_nList3CurSel == i)
					m_nList3CurSel = LB_ERR;

				m_SaCode.RemoveAt(i);
				m_SaName.RemoveAt(i);
				m_UiaReceiptNo.RemoveAt(i);
				m_UiaState.RemoveAt(i);
				m_DwaBuyPrice.RemoveAt(i);
				m_DwaSellPrice.RemoveAt(i);
				m_DwaSuryo.RemoveAt(i);
				m_DwaBuySoldSuryo.RemoveAt(i);
				m_DwaSellSuryo.RemoveAt(i);
				m_DwaSellSoldSuryo.RemoveAt(i);
				m_UiaTick.RemoveAt(i);
				m_WaUnit.RemoveAt(i);
				m_UiaSemiAuto.RemoveAt(i);

				break;
			}

			strCode = m_SaCode[i];
			strName = m_SaName[i];
			lPrice = m_DwaBuyPrice[i];
			lSuryo = m_DwaSuryo[i];

			DispLog(
				"%s 買 No.%05d %s %s %ld円 x%ld\n",
				GetCurrentTimeEx().Format("%H:%M:%S"),
				nReceiptNo, strCode, StrConvHalfWidth(strName).Left(20), lPrice, lSuryo
			);
			MessageBeep(MB_OK);

			switch (m_UiaState[i]) {
			case 101U:
			case 108U:
				m_UiaState[i] = 2U;
				break;
			case 105U:
			case 109U:
				m_UiaState[i] = 6U;
			}

			m_UiaReceiptNo[i] = nReceiptNo;

			SaveState();

			break;
		}
}

void CTradeHelperDlg::DispWB2(BOOL bFile, int nMode, CWebBrowser2& WebBrowser2, const CString& strUrl)
{
	BrowserNavConstants BrowserNavConstantsFlags;
	BrowserNavConstantsFlags = (BrowserNavConstants)(navNoReadFromCache | navNoWriteToCache);

	while (WebBrowser2.GetBusy()) {
		Sleep(100);
		PumpWaitingMessages();
	}

	CString strLocationUrl = WebBrowser2.GetLocationURL();

	if (strLocationUrl.IsEmpty()  ||  strLocationUrl == "about:blank"  &&  strUrl != strLocationUrl)
		WebBrowser2.Navigate(strUrl, (COleVariant)(long)BrowserNavConstantsFlags, NULL, NULL, NULL);
	else if (! bFile  &&  nMode != 1  &&  strLocationUrl != strUrl) {
		WebBrowser2.Navigate(strUrl, (COleVariant)(long)BrowserNavConstantsFlags, NULL, NULL, NULL);
		if (strUrl != "about:blank") {
			while (WebBrowser2.GetBusy()) {
				Sleep(100);
				PumpWaitingMessages();
			}
			WebBrowser2.Refresh();
		}
	} else if (nMode != 2)
		WebBrowser2.Refresh();
}

void CTradeHelperDlg::DispStockAve()
{
	static int nWaitThreadCount;
	static long lDiff255;
	static double dPrice = 0.0;
	static double dPrePrice = 0.0;
	static long lPrePrice255[60] = {0L};
	static CString strTime;
	static double dDiff;

	int i;
	int imax;
	CString strEdit1;
	CString strCode;
	int nReceiptNo = 0;
	RankingAttr RankingAttr;

	m_Edit1.GetWindowText(strEdit1);

	if (strEdit1.GetLength()) {
		if (strEdit1.Find('/') == -1) {
			nReceiptNo = atoi(strEdit1);

			for (i = 0, imax = m_UiaReceiptNo.GetSize(); i < imax; i ++)
				if ((int)m_UiaReceiptNo[i] == nReceiptNo) {
					strCode = m_SaCode[i];
					break;
				}
		} else
			strCode = strEdit1;
	}

	if (m_MstrCodeRankingAttr.Lookup(strCode, RankingAttr)) {
		RankingAttr.lCheckedTradeCount1000 = RankingAttr.plTradeCount1000[5 - 1];
		RankingAttr.lCheckedDiffPrice = RankingAttr.lDiffPrice;
		m_MstrCodeRankingAttr[strCode] = RankingAttr;
	}
	if (m_MstrCodeRankingAttr2.Lookup(strCode, RankingAttr)) {
		RankingAttr.lCheckedTradeCount1000 = RankingAttr.plTradeCount1000[5 - 1];
		RankingAttr.lCheckedDiffPrice = RankingAttr.lDiffPrice;
		m_MstrCodeRankingAttr2[strCode] = RankingAttr;
	}

//	if (! m_bMentenance0  ||  ! m_bMentenance1) {
	if (! m_bMentenance1) {
		if (m_pDispStockAveThread == NULL) {
			CString strDiff255;
			short sUnit = 1;
			long lMaxTradeCount;
			CString strCodeEx;
			CString strName;

			m_Edit12.SetWindowText("○");

			if (strCode.GetLength()) {
				CodeToName(strCode, strName, NULL, &sUnit, NULL, NULL, NULL, &lMaxTradeCount, &strCodeEx);
				switch (sUnit) {
				case 5L:
				case 50L:
				case 500L:
				case 5000L:
				case 50000L:
					lMaxTradeCount /= sUnit / 5;
					break;
				default:
					lMaxTradeCount /= sUnit;
				}
			}

			m_pDispStockAveThread = new CDispStockAveThread;
			m_pDispStockAveThread->m_bMentenance1 = m_bMentenance1;
			m_pDispStockAveThread->m_bMentenance2 = m_bMentenance2;
			m_pDispStockAveThread->m_strDataDir = m_strDataDir;
			m_pDispStockAveThread->m_pSession = &m_SessionCosmo;
			m_pDispStockAveThread->m_sbQuickInfoUrl = m_sbQuickInfoUrl;
			m_pDispStockAveThread->m_sbCosmoQuoteUrl = m_sbCosmoQuoteUrl;
			m_pDispStockAveThread->m_strContractMonth0 = m_strContractMonth0;
//			m_pDispStockAveThread->m_strContractMonth1 = m_strContractMonth1;
			m_pDispStockAveThread->m_strContractMonth0S = m_strContractMonth0S;
			m_Edit7.GetWindowText(strDiff255);
			m_pDispStockAveThread->m_lDiff255 = lDiff255 = atol(strDiff255);
			m_pDispStockAveThread->m_dPrice = dPrice;
			m_pDispStockAveThread->m_dPrePrice = dPrePrice;
			CopyMemory(m_pDispStockAveThread->m_lPrePrice255, lPrePrice255, sizeof(lPrePrice255));
			m_pDispStockAveThread->m_strTime = strTime;
			m_pDispStockAveThread->m_strCode = strCode;
			m_pDispStockAveThread->m_strName = strName;
			m_pDispStockAveThread->m_sUnit = sUnit;
			m_pDispStockAveThread->m_lMaxTradeCount = lMaxTradeCount;
			m_pDispStockAveThread->m_strCodeEx = strCodeEx;
			m_pDispStockAveThread->m_strFPath0 = m_strTempDir + FNAME_STOCKAVE;
			m_pDispStockAveThread->m_strFPath1 = m_strTempDir + FNAME_QUOTE0;
			m_pDispStockAveThread->m_strFPath2 = m_strTempDir + FNAME_QUOTE1;
//			m_pDispStockAveThread->m_DtCur = GetCurrentTimeEx();
//			m_pDispStockAveThread->m_bStockAveThread = m_bStockAveThread;
			m_pDispStockAveThread->m_bAutoDelete = FALSE;
			m_pDispStockAveThread->CreateThread();

			nWaitThreadCount = 0;
			SetWMUserTimer(0, 5, NULL);

//			m_bStockAveThread = TRUE;
		} else {
			if (WaitForSingleObject(m_pDispStockAveThread->m_hThread, 0) == WAIT_TIMEOUT) {
//				if (nWaitThreadCount ++ < 200)
//					SetWMUserTimer(0, 5, NULL);
//				if (++ nWaitThreadCount < 9) {
				if (++ nWaitThreadCount < 18) {
					KillWMUserTimer(5);
					SetWMUserTimer(100, 5, NULL);
				} else {
					m_Edit12.SetWindowText("●");
					m_Edit19.SetWindowText(IToA(++ m_nDispStockAveThreadTimeoutCount));

					m_PaThreadTimeout.Add(m_pDispStockAveThread);
					m_pDispStockAveThread = NULL;
					if (! m_bChkThreadTimerRun) {
						m_bChkThreadTimerRun = TRUE;
						SetWMUserTimer(1000, 21, NULL);
					}
				}
			} else {
//				BOOL bFPath0 = m_pDispStockAveThread->m_strFPath0.GetLength();

//				if (bFPath0) {
					if (m_pDispStockAveThread->m_lDiff255 != lDiff255)
						m_Edit7.SetWindowText(LToA(m_pDispStockAveThread->m_lDiff255));
					m_Edit8.SetWindowText(StrFormat("%.2f", dDiff = m_pDispStockAveThread->m_dDiff));
					m_Edit9.SetWindowText(StrFormat("%.2f", m_pDispStockAveThread->m_dPrice - m_pDispStockAveThread->m_dPrePrice));
//				}

				m_strKehaiCode = m_pDispStockAveThread->m_strCode;

//				if (bFPath0)
					DispWB2(TRUE, 1, m_WebBrowser21, m_pDispStockAveThread->m_strFPath0);
				DispWB2(TRUE, 1, m_WebBrowser22, m_pDispStockAveThread->m_strFPath1);
				DispWB2(TRUE, 1, m_WebBrowser25, m_strKehaiCode.IsEmpty() ? "about:blank" : m_pDispStockAveThread->m_strFPath2);

				if (m_hStockAveBeepThread  &&  WaitForSingleObject(m_hStockAveBeepThread, 0) != WAIT_TIMEOUT) {
					CloseHandle(m_hStockAveBeepThread);
					m_hStockAveBeepThread = NULL;
				}
				if (! m_hStockAveBeepThread) {
//				if (bFPath0  &&  ! m_hStockAveBeepThread) {
					COleDateTime DtCur = GetCurrentTimeEx();
					int nDayOfWeek = DtCur.GetDayOfWeek();
					int nHour = DtCur.GetHour();
					int nMinute = DtCur.GetMinute();
					BOOL bTradeTime;

//					bTradeTime = nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 9  &&  nHour < 11  ||  nHour == 11  &&  nMinute <= 1  ||  nHour == 12  &&  nMinute >= 30  ||  nHour >= 13  &&  nHour < 15);
					bTradeTime = nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 9  &&  nHour < 11  ||  nHour == 11  &&  nMinute <= 31  ||  nHour == 12  &&  nMinute >= 30  ||  nHour >= 13  &&  nHour < 15);

					if (bTradeTime) {
						CWinThread* pWinThread = AfxBeginThread(StockAveBeepThreadProc, &dDiff, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
						if (DuplicateHandle(GetCurrentProcess(), pWinThread->m_hThread, GetCurrentProcess(), &m_hStockAveBeepThread, 0, FALSE, DUPLICATE_SAME_ACCESS)) {
							if (pWinThread->ResumeThread() == 0xffffffff) {
								delete pWinThread;
								m_hStockAveBeepThread = NULL;
							}
						} else {
							delete pWinThread;
							m_hStockAveBeepThread = NULL;
						}
					}
				}

//				if (bFPath0) {
					dPrice = m_pDispStockAveThread->m_dPrice;
					dPrePrice = m_pDispStockAveThread->m_dPrePrice;
					CopyMemory(lPrePrice255, m_pDispStockAveThread->m_lPrePrice255, sizeof(lPrePrice255));
					strTime = m_pDispStockAveThread->m_strTime;
//				}

				m_sbKehaiHtml = m_pDispStockAveThread->m_sbKehaiHtml;

				delete m_pDispStockAveThread;
				m_pDispStockAveThread = NULL;

				m_Edit12.SetWindowText(pszEmpty);
			}
		}
	}
}

void CTradeHelperDlg::DispChart(int nMode)
{
	static int nSel = 0;
	static int nWaitThreadCount0;
	static int nWaitThreadCount1;

	int nCheck5 = m_Check5.GetCheck();

	if (! m_bMentenance1  ||  nCheck5 == 1) {
		int i;
		int imax;
		CString strFPath;
		CString strName;
		CString strSijoName;
		SYSTEMTIME StDate;
		CString strSrcFPath;

		if (nMode != -1)
			nSel = nMode;

		if (nSel == 0) {
			if (m_pDispWB2Thread2 == NULL) {
				int nCheckedRadioButton0 = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO9);
				CString strUrl0;
				CString strDName;

				m_Edit13.SetWindowText("○");

				nMode = nCheckedRadioButton0 == IDC_RADIO8 ? 2 : 0;
				strFPath = m_strTempDir + FNAME_CHART0;

				if (nCheck5 == 1) {
					switch (nCheckedRadioButton0) {
					case IDC_RADIO2:
						strDName = "0000 FX MinuteChart";
						break;
					case IDC_RADIO6:
						strDName = "0000 TM MinuteChart";
						break;
					case IDC_RADIO7:
						strDName = "0000 JQ MinuteChart";
					}

					m_MonthCalCtrl1.GetCurSel(&StDate);
					strSrcFPath.Format(
						"%s\\Chart\\%s\\%d%02d%02d.gif",
						m_strDataDir, strDName,
						StDate.wYear, StDate.wMonth, StDate.wDay
					);

					if (! CopyFile(strSrcFPath, strFPath, FALSE))
						DispErrorLog("%s %s コピーエラー: %s\n", strSrcFPath, strFPath, GetLastErrorMessage());
					else {
						DispWB2(TRUE, nMode, m_WebBrowser23, strFPath);
						SetWMUserTimer(0, 29, NULL);
					}

					m_Edit13.SetWindowText(pszEmpty);
				} else {
					switch (nCheckedRadioButton0) {
					case IDC_RADIO1:
						strUrl0.Format(OBJ_INDEX_CHART_L, m_sbQuickInfoUrl, "101");	// 日経平均株価２２５種
						break;
					case IDC_RADIO2:
						strUrl0.Format(OBJ_INDEX_CHART_L, m_sbQuickInfoUrl, "101." + m_strContractMonth0);	// 日経225先物 1限月
						break;
					case IDC_RADIO3:
						strUrl0.Format(OBJ_INDEX_CHART_L, m_sbQuickInfoUrl, "101." + m_strContractMonth1);	// 日経225先物 2限月
						break;
					case IDC_RADIO4:
						strUrl0.Format(OBJ_INDEX_CHART_L, m_sbQuickInfoUrl, "103");	// 日経株価指数３００
						break;
					case IDC_RADIO5:
						strUrl0.Format(OBJ_INDEX_CHART_L, m_sbQuickInfoUrl, "151");	// ＴＯＰＩＸ（東証１部株価指数）
						break;
					case IDC_RADIO6:
						strUrl0.Format(OBJ_INDEX_CHART_L, m_sbQuickInfoUrl, "154");	// 東証マザーズ指数
						break;
					case IDC_RADIO7:
						strUrl0.Format(OBJ_INDEX_CHART_L, m_sbQuickInfoUrl, "191");	// 日経ジャスダック平均株価
						break;
					case IDC_RADIO8:
						strUrl0.Format(OBJ_INDEX_DAYCHART_L, m_sbQuickInfoUrl, "101");	// 日経平均株価２２５種 日足
						break;
					default:
						strUrl0.Format(OBJ_KABU_CHART_L, m_sbQuickInfoUrl, "9984/T");	// ソフトバンク
					}

					m_pDispWB2Thread2 = new CDispWB2Thread;
					m_pDispWB2Thread2->m_nMode = nMode;
					m_pDispWB2Thread2->m_strDataDir = m_strDataDir;
					m_pDispWB2Thread2->m_strPreUrl = m_strDispWB2Url0;
					m_pDispWB2Thread2->m_strUrl = m_strDispWB2Url0 = strUrl0;
					m_pDispWB2Thread2->m_strFPath = strFPath;
					m_pDispWB2Thread2->m_bAutoDelete = FALSE;
					m_pDispWB2Thread2->CreateThread();

					nWaitThreadCount0 = 0;
					SetWMUserTimer(0, 7, NULL);
				}
			} else {
				if (WaitForSingleObject(m_pDispWB2Thread2->m_hThread, 0) == WAIT_TIMEOUT) {
//					if (nWaitThreadCount0 ++ < 800)
//						SetWMUserTimer(0, 7, NULL);
//					if (++ nWaitThreadCount0 < 37) {
					if (++ nWaitThreadCount0 < 74) {
						KillWMUserTimer(7);
						SetWMUserTimer(100, 7, NULL);
					} else {
						m_Edit13.SetWindowText("●");
						m_Edit19.SetWindowText(IToA(++ m_nDispStockAveThreadTimeoutCount));

						m_PaThreadTimeout.Add(m_pDispWB2Thread2);
						m_pDispWB2Thread2 = NULL;
						if (! m_bChkThreadTimerRun) {
							m_bChkThreadTimerRun = TRUE;
							SetWMUserTimer(1000, 21, NULL);
						}
					}
				} else {
					DispWB2(TRUE, m_pDispWB2Thread2->m_nMode, m_WebBrowser23, m_pDispWB2Thread2->m_strUrl);
					SetWMUserTimer(0, 29, NULL);

					delete m_pDispWB2Thread2;
					m_pDispWB2Thread2 = NULL;

					m_Edit13.SetWindowText(pszEmpty);
				}
			}

			nSel = 1;
		} else {
			if (m_pDispWB2Thread3 == NULL) {
				int nCheckedRadioButton1 = GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO11);
				CString strEdit1;
				CString strCode;
				int nReceiptNo = 0;
				CString strUrl1;
				int nCodeLen;

				m_Edit13.SetWindowText("□");

				m_Edit1.GetWindowText(strEdit1);

				strCode.Empty();
				if (strEdit1.GetLength())
					if (strEdit1.Find('/') == -1) {
						nReceiptNo = atoi(strEdit1);

						for (i = 0, imax = m_UiaReceiptNo.GetSize(); i < imax; i ++)
							if ((int)m_UiaReceiptNo[i] == nReceiptNo) {
								strCode = m_SaCode[i];
								break;
							}
					} else
						strCode = strEdit1;
				nCodeLen = strCode.GetLength();

				nMode = nCheckedRadioButton1 == IDC_RADIO11 ? 2 : 0;

				if (nCodeLen)
					strFPath = m_strTempDir + FNAME_CHART1;

				if (nCheck5 == 1) {
					CodeToName(strCode, strName, &strSijoName);
					if (nCodeLen > 4) {
						if (strName[0] == '!')
							strName.Delete(0);
						if (nCheckedRadioButton1 == IDC_RADIO10) {
							m_MonthCalCtrl1.GetCurSel(&StDate);
							strSrcFPath.Format(
								"%s\\Chart\\%s\\%s %s %s\\%d%02d%02d.gif",
								m_strDataDir, strSijoName,
								strCode.Left(4), strCode.Mid(5), strName,
								StDate.wYear, StDate.wMonth, StDate.wDay
							);
						} else
							strSrcFPath.Format(
								"%s\\Chart\\0000 Today DayChart\\%s\\%s %s %s.gif",
								m_strDataDir, strSijoName,
								strCode.Left(4), strCode.Mid(5), strName
							);

						if (! CopyFile(strSrcFPath, strFPath, FALSE))
							DispErrorLog("%s %s コピーエラー: %s\n", strSrcFPath, strFPath, GetLastErrorMessage());
						else {
							DispWB2(nCodeLen, 0, m_WebBrowser24, strFPath);
							SetWMUserTimer(0, 31, NULL);
						}
					}

					m_Edit13.SetWindowText(pszEmpty);
				} else {
					if (nCodeLen)
						switch (nCheckedRadioButton1) {
						case IDC_RADIO10:
							strUrl1.Format(OBJ_KABU_CHART_L, m_sbQuickInfoUrl, strCode);
							break;
						default:
							strUrl1.Format(OBJ_KABU_DAYCHART_L, m_sbQuickInfoUrl, strCode);
						}
					else
						strUrl1 = "about:blank";

					m_pDispWB2Thread3 = new CDispWB2Thread;
					m_pDispWB2Thread3->m_nMode = nMode;
					m_pDispWB2Thread3->m_strDataDir = m_strDataDir;
					m_pDispWB2Thread3->m_strPreUrl = m_strDispWB2Url1;
					m_pDispWB2Thread3->m_strUrl = m_strDispWB2Url1 = strUrl1;
					m_pDispWB2Thread3->m_strFPath = strFPath;
					m_pDispWB2Thread3->m_bAutoDelete = FALSE;
					m_pDispWB2Thread3->CreateThread();

					nWaitThreadCount1 = 0;
					SetWMUserTimer(0, 8, NULL);
				}
			} else {
				if (WaitForSingleObject(m_pDispWB2Thread3->m_hThread, 0) == WAIT_TIMEOUT) {
//					if (nWaitThreadCount1 ++ < 400)
//						SetWMUserTimer(0, 8, NULL);
//					if (++ nWaitThreadCount1 < 37) {
					if (++ nWaitThreadCount1 < 74) {
						KillWMUserTimer(8);
						SetWMUserTimer(100, 8, NULL);
					} else {
						m_Edit13.SetWindowText("■");
						m_Edit19.SetWindowText(IToA(++ m_nDispStockAveThreadTimeoutCount));

						m_PaThreadTimeout.Add(m_pDispWB2Thread3);
						m_pDispWB2Thread3 = NULL;
						if (! m_bChkThreadTimerRun) {
							m_bChkThreadTimerRun = TRUE;
							SetWMUserTimer(1000, 21, NULL);
						}
					}
				} else {
					DispWB2(m_pDispWB2Thread3->m_strFPath.GetLength(), m_pDispWB2Thread3->m_nMode, m_WebBrowser24, m_pDispWB2Thread3->m_strUrl);
					SetWMUserTimer(0, 31, NULL);

					delete m_pDispWB2Thread3;
					m_pDispWB2Thread3 = NULL;

					m_Edit13.SetWindowText(pszEmpty);
				}
			}

			nSel = 0;
		}
	}
}

void CTradeHelperDlg::DispRanking(int nMode)
{
	static int nWaitThreadCount1;
	static int nWaitThreadCount2;

	int i;
	int imax;
	int nTopIndex;
	int nCurSel;
	CString strCurSel;
	void* pVoid;
	CString strCode;
	CString strName;
	CString strList;

	if (nMode == 0)
		if (m_pDispRankingThread0 == NULL) {
			nMode = GetCheckedRadioButton(IDC_RADIO12, IDC_RADIO20) - IDC_RADIO12;

			CString strDBFPath = m_strDBFPath;
			if (m_Check5.GetCheck() == 1) {
				SYSTEMTIME StDate;
				m_MonthCalCtrl1.GetCurSel(&StDate);
				CString strDBFPathA;
				strDBFPathA.Format("%s\\Data\\" MAIN_EXENAME "%04d%02d%02d.mdb", m_strDataDir, StDate.wYear, StDate.wMonth, StDate.wDay);
				if (CFile::GetStatus(strDBFPathA, m_FileStatus))
					strDBFPath = strDBFPathA;
			}

			m_pDispRankingThread0 = new CDispRankingThread;
			m_pDispRankingThread0->m_strDataDir = m_strDataDir;
			m_pDispRankingThread0->m_nMode = nMode;
			m_pDispRankingThread0->m_strDBFPath = strDBFPath;
			m_pDispRankingThread0->m_pMstiCodeInfo = &m_MstiCodeInfo;
			m_pDispRankingThread0->m_pMstpSelCode = &m_MstpSelCode;
			m_pDispRankingThread0->m_bAutoDelete = FALSE;
			m_pDispRankingThread0->CreateThread();

			SetWMUserTimer(0, 15, NULL);
		} else {
			if (WaitForSingleObject(m_pDispRankingThread0->m_hThread, 0) == WAIT_TIMEOUT)
				SetWMUserTimer(100, 15, NULL);
			else {
				long lTradeCount1000;
				long lCheckedTradeCount1000;
				long lDiffPrice;
				long lLowDiffPrice;
				CString strMainCode;
				long plPreTradeCount1000[5];
				long lPreDiffPrice;
				long lCheckedDiffPrice;
				RankingAttr RankingAttr;
				long lUpCount0;
				long lUpCount1;
				CString strUpCount;
				BOOL bCurUpCount;
				BOOL bUpCount = FALSE;
//				BOOL bNewUpCount = FALSE;
				CString strFPath;
				COleDateTime DtCur = GetCurrentTimeEx();
				int nDayOfWeek = DtCur.GetDayOfWeek();
				int nHour = DtCur.GetHour();
				int nMinute = DtCur.GetMinute();
				int nSecond = DtCur.GetSecond();
				CString strTime = DtCur.Format("%H:%M:%S ");
				BOOL bKehaiTime;
				BOOL bTradeTime;
				int nCheck7 = m_Check7.GetCheck();
				int nIndex;

				nTopIndex = m_List4.GetTopIndex();
				if ((nCurSel = m_List4.GetCurSel()) != LB_ERR) {
					m_List4.GetText(nCurSel, strCurSel);
					strCurSel = strCurSel.Left(strCurSel.Find(' '));
				}
				m_List4.ResetContent();

//				bKehaiTime = nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 8  &&  nHour < 9  ||  nHour == 12  &&  (nMinute >= 5  &&  nMinute < 30));
				bKehaiTime = nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour == 8  &&  nMinute == 59  ||  nHour == 12  &&  nMinute == 29)  &&  nSecond == 59;
//				bTradeTime = nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 9  &&  nHour < 11  ||  nHour == 11  &&  nMinute <= 1  ||  nHour == 12  &&  nMinute >= 30  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16);
				bTradeTime = nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 9  &&  nHour < 11  ||  nHour == 11  &&  nMinute <= 31  ||  nHour == 12  &&  nMinute >= 30  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16);

				CStdioFile StdioFile(m_strTempRankingFPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
				StdioFile.SeekToEnd();

				for (i = 0, imax = m_pDispRankingThread0->m_SaCode.GetSize(); i < imax; i ++) {
					strCode = m_pDispRankingThread0->m_SaCode[i];
					lTradeCount1000 = m_pDispRankingThread0->m_DwaTradeCount1000[i];
					lDiffPrice = m_pDispRankingThread0->m_DwaDiffPrice[i];
					lLowDiffPrice = m_pDispRankingThread0->m_DwaLowDiffPrice[i];
					if (! lTradeCount1000  &&  bTradeTime  ||  ! lDiffPrice  ||  ! m_MstpSelCode.Lookup(strCode, pVoid))
						continue;
					if (m_MstrCodeRankingAttr.Lookup(strCode, RankingAttr)) {
						CopyMemory(plPreTradeCount1000, RankingAttr.plTradeCount1000, sizeof(plPreTradeCount1000));
						lCheckedTradeCount1000 = RankingAttr.lCheckedTradeCount1000;
						lPreDiffPrice = RankingAttr.lDiffPrice;
						lCheckedDiffPrice = RankingAttr.lCheckedDiffPrice;
						if (lDiffPrice == lCheckedDiffPrice)
							strUpCount.Empty();
						else {
							lUpCount0 = lDiffPrice - lCheckedDiffPrice;
							if (lUpCount0 >= 100)
								lUpCount0 = 99;
							else if (lUpCount0 <= -10)
								lUpCount0 = -9;
							strUpCount = LToA(lUpCount0);
						}
						if (bCurUpCount =  (lDiffPrice / 5 > lCheckedDiffPrice / 5  ||  lCheckedDiffPrice - (lDiffPrice - lLowDiffPrice) <= 5)  &&  lDiffPrice >= lCheckedDiffPrice + 2  &&  lLowDiffPrice > 5)
							bUpCount = TRUE;
					} else {
						ZeroMemory(plPreTradeCount1000, sizeof(plPreTradeCount1000));
						lCheckedTradeCount1000 = lTradeCount1000;
						lPreDiffPrice = 0L;
						lCheckedDiffPrice = lDiffPrice;
						strUpCount = 'N';
						bCurUpCount = FALSE;
//						bNewUpCount = TRUE;
					}
					if (bTradeTime) {
						CopyMemory(&RankingAttr.plTradeCount1000[0], &plPreTradeCount1000[1], sizeof(plPreTradeCount1000) - sizeof(long));
						RankingAttr.plTradeCount1000[5 - 1] = lTradeCount1000;
						RankingAttr.lCheckedTradeCount1000 = lCheckedTradeCount1000;
						RankingAttr.lDiffPrice = lDiffPrice;
						RankingAttr.lCheckedDiffPrice = lCheckedDiffPrice;
						m_MstrCodeRankingAttr[strCode] = RankingAttr;
					}
					if ((lTradeCount1000 != plPreTradeCount1000[0]  ||  bCurUpCount  &&  ! nCheck7)  ||  ! bTradeTime) {
						strList = m_pDispRankingThread0->m_SaList[i];
						if (m_MstpNewsCode.Lookup(strCode, pVoid))
							strList.SetAt(4, '*');
						else if (m_MstpNewsCode2.Lookup(strCode, pVoid))
							strList.SetAt(4, '+');
//						lUpCount0 = lTradeCount1000 - lPreTradeCount1000;
//						lUpCount0 = lTradeCount1000 - lCheckedTradeCount1000;
//						if (lUpCount0 >= 1000)
//							lUpCount0 = 999;
//						lUpCount1 = lTradeCount1000 - lCheckedTradeCount1000;
						lUpCount1 = m_pDispRankingThread0->m_DwaLowDiffPrice[i];
						if (lUpCount1 >= 1000)
							lUpCount1 = 999;
						else if (lUpCount1 <= -100)
							lUpCount1 = -99;
//						strList +=  ("   " + strUpCount).Right(3) + ("   " + LToA(lUpCount0)).Right(4) + ("   " + LToA(lUpCount1)).Right(4);
						strList +=  ("   " + strUpCount).Right(3) + ("   " + LToA(lUpCount1)).Right(4);
						if ((nIndex = m_List4.AddString(strList)) != LB_ERR)
							m_List4.SetItemData(nIndex, bCurUpCount);

						if (bTradeTime  &&  lTradeCount1000 != plPreTradeCount1000[5 - 1]  ||  bKehaiTime)
							StdioFile.WriteString(strTime + strList + '\n');
					}
				}
				if (bUpCount  &&  bTradeTime  &&  ! m_Check8.GetCheck())
					MessageBeep(-1);
//				if (bNewUpCount && bTradeTime)
//					MessageBeep(MB_ICONHAND);

				StdioFile.Close();

				if (nTopIndex != LB_ERR)
					m_List4.SetTopIndex(nTopIndex);
				if (nCurSel != LB_ERR)
					m_List4.SelectString(-1, strCurSel);

				delete m_pDispRankingThread0;
				m_pDispRankingThread0 = NULL;
			}
		}
	else if (nMode == 1) {
//		if (! m_bMentenance0  ||  ! m_bMentenance1) {
		if (! m_bMentenance1) {
			if (m_pDispRankingThread1 == NULL) {
				m_Edit14.SetWindowText("○");

				nMode = 9 + GetCheckedRadioButton(IDC_RADIO12, IDC_RADIO20) - IDC_RADIO12;

				m_pDispRankingThread1 = new CDispRankingThread;
				m_pDispRankingThread1->m_bMentenance2 = m_bMentenance2;
				m_pDispRankingThread1->m_strDataDir = m_strDataDir;
				m_pDispRankingThread1->m_nMode = nMode;
				m_pDispRankingThread1->m_strDBFPath = m_strDBFPath;
				m_pDispRankingThread1->m_pSession = &m_SessionCosmo;
				m_pDispRankingThread1->m_sbQuickInfoUrl = m_sbQuickInfoUrl;
				m_pDispRankingThread1->m_sbCosmoQuoteUrl = m_sbCosmoQuoteUrl;
				m_pDispRankingThread1->m_pMstiCodeInfo = &m_MstiCodeInfo;
				m_pDispRankingThread1->m_bAutoDelete = FALSE;
				m_pDispRankingThread1->CreateThread();

				nWaitThreadCount1 = 0;
				SetWMUserTimer(0, 16, NULL);
			} else {
				if (WaitForSingleObject(m_pDispRankingThread1->m_hThread, 0) == WAIT_TIMEOUT) {
//					if (nWaitThreadCount1 ++ < 1000)
//						SetWMUserTimer(0, 16, NULL);
//					if (++ nWaitThreadCount1 < 47) {
//					if (++ nWaitThreadCount1 < 94) {
					if (++ nWaitThreadCount1 < 188) {
						KillWMUserTimer(16);
						SetWMUserTimer(100, 16, NULL);
					} else {
						m_Edit14.SetWindowText("●");
						m_Edit19.SetWindowText(IToA(++ m_nDispStockAveThreadTimeoutCount));

						m_PaThreadTimeout.Add(m_pDispRankingThread1);
						m_pDispRankingThread1 = NULL;
						if (! m_bChkThreadTimerRun) {
							m_bChkThreadTimerRun = TRUE;
							SetWMUserTimer(1000, 21, NULL);
						}
					}
				} else {
					long lTradeCount1000;
					long lCheckedTradeCount1000;
					long lDiffPrice;
					long lLowDiffPrice;
					CString strMainCode;
					short sUnit;
					long plPreTradeCount1000[5];
					long lPreDiffPrice;
					long lCheckedDiffPrice;
					RankingAttr RankingAttr;
					int nDiffPriceTick;
					long lUpCount0;
					long lUpCount1;
					CString strUpCount;
					BOOL bCurUpCount;
					BOOL bUpCount = FALSE;
//					BOOL bNewUpCount = FALSE;
					CString strFPath;
					COleDateTime DtCur = GetCurrentTimeEx();
					int nDayOfWeek = DtCur.GetDayOfWeek();
					int nHour = DtCur.GetHour();
					int nMinute = DtCur.GetMinute();
					CString strTime = DtCur.Format("%H:%M:%S ");
					BOOL bTradeTime;
					int nCheck7 = m_Check7.GetCheck();
					int nCheck9 = m_Check9.GetCheck();
					int nIndex;

					nTopIndex = m_List8.GetTopIndex();
					if ((nCurSel = m_List8.GetCurSel()) != LB_ERR) {
						m_List8.GetText(nCurSel, strCurSel);
						strCurSel = strCurSel.Left(strCurSel.Find(' '));
					}
					m_List8.ResetContent();

//					bTradeTime = nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 9  &&  nHour < 11  ||  nHour == 11  &&  nMinute <= 1  ||  nHour == 12  &&  nMinute >= 30  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16);
					bTradeTime = nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 9  &&  nHour < 11  ||  nHour == 11  &&  nMinute <= 31  ||  nHour == 12  &&  nMinute >= 30  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16);

					CStdioFile StdioFile(m_strTempRankingAllFPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
					StdioFile.SeekToEnd();

					for (i = 0, imax = m_pDispRankingThread1->m_SaCode.GetSize(); i < imax; i ++) {
						strCode = m_pDispRankingThread1->m_SaCode[i];
						lTradeCount1000 = m_pDispRankingThread1->m_DwaTradeCount1000[i];
						lDiffPrice = m_pDispRankingThread1->m_DwaDiffPrice[i];
						lLowDiffPrice = m_pDispRankingThread1->m_DwaLowDiffPrice[i];
						if (nCheck9 == 0  &&  m_MstpSelCode.Lookup(strCode, pVoid))
							continue;
						strMainCode = strCode.Left(4);
						CodeToName(strMainCode, strName, NULL, &sUnit);
						if (strCode != strMainCode)
							continue;
						if (m_MstrCodeRankingAttr2.Lookup(strCode, RankingAttr)) {
							CopyMemory(plPreTradeCount1000, RankingAttr.plTradeCount1000, sizeof(plPreTradeCount1000));
							lCheckedTradeCount1000 = RankingAttr.lCheckedTradeCount1000;
							lPreDiffPrice = RankingAttr.lDiffPrice;
							lCheckedDiffPrice = RankingAttr.lCheckedDiffPrice;
							nDiffPriceTick = GetTick(lCheckedDiffPrice, sUnit);
							if (lDiffPrice == lCheckedDiffPrice)
								strUpCount.Empty();
							else {
								lUpCount0 = (lDiffPrice - lCheckedDiffPrice) / nDiffPriceTick;
								if (lUpCount0 >= 100)
									lUpCount0 = 99;
								else if (lUpCount0 <= -10)
									lUpCount0 = -9;
								strUpCount = LToA(lUpCount0);
							}
							if (bCurUpCount =  (lDiffPrice / nDiffPriceTick / 5 > lCheckedDiffPrice / nDiffPriceTick / 5  ||  lCheckedDiffPrice / nDiffPriceTick - (lDiffPrice / nDiffPriceTick - lLowDiffPrice) <= 5)  &&  lDiffPrice / nDiffPriceTick >= lCheckedDiffPrice / nDiffPriceTick + 2  &&  lLowDiffPrice > 5)
								bUpCount = TRUE;
						} else {
							ZeroMemory(plPreTradeCount1000, sizeof(plPreTradeCount1000));
							lCheckedTradeCount1000 = lTradeCount1000;
							lPreDiffPrice = 0L;
							lCheckedDiffPrice = lDiffPrice;
							strUpCount = 'N';
							bCurUpCount = FALSE;
//							bNewUpCount = TRUE;
						}
						if (bTradeTime) {
							CopyMemory(&RankingAttr.plTradeCount1000[0], &plPreTradeCount1000[1], sizeof(plPreTradeCount1000) - sizeof(long));
							RankingAttr.plTradeCount1000[5 - 1] = lTradeCount1000;
							RankingAttr.lCheckedTradeCount1000 = lCheckedTradeCount1000;
							RankingAttr.lDiffPrice = lDiffPrice;
							RankingAttr.lCheckedDiffPrice = lCheckedDiffPrice;
							m_MstrCodeRankingAttr2[strCode] = RankingAttr;
						}
						if ((lTradeCount1000 != plPreTradeCount1000[5 - 1]  ||  bCurUpCount  &&  ! nCheck7)  ||  ! bTradeTime) {
							strList = m_pDispRankingThread1->m_SaList[i];
							if (m_MstpNewsCode.Lookup(strCode, pVoid))
								strList.SetAt(4, '*');
							else if (m_MstpNewsCode2.Lookup(strCode, pVoid))
								strList.SetAt(4, '+');
//							lUpCount0 = lTradeCount1000 - lPreTradeCount1000;
//							lUpCount0 = lTradeCount1000 - lCheckedTradeCount1000;
//							if (lUpCount0 >= 1000)
//								lUpCount0 = 999;
//							lUpCount1 = lTradeCount1000 - lCheckedTradeCount1000;
							lUpCount1 = m_pDispRankingThread1->m_DwaLowDiffPrice[i];
							if (lUpCount1 >= 1000)
								lUpCount1 = 999;
							else if (lUpCount1 <= -100)
								lUpCount1 = -99;
//							strList +=  ("   " + strUpCount).Right(3) + ("   " + LToA(lUpCount0)).Right(4) + ("   " + LToA(lUpCount1)).Right(4);
							strList +=  ("   " + strUpCount).Right(3) + ("   " + LToA(lUpCount1)).Right(4);
							if ((nIndex = m_List8.AddString(strList)) != LB_ERR)
								m_List8.SetItemData(nIndex, bCurUpCount);

							if (lTradeCount1000 != plPreTradeCount1000[5 - 1])
								StdioFile.WriteString(strTime + strList + '\n');
						}
					}
					if (bUpCount  &&  bTradeTime  &&  ! m_Check8.GetCheck())
						MessageBeep(-1);
//					if (bNewUpCount && bTradeTime)
//						MessageBeep(MB_ICONHAND);

					StdioFile.Close();

					if (nTopIndex != LB_ERR)
						m_List8.SetTopIndex(nTopIndex);
					if (nCurSel != LB_ERR)
						m_List8.SelectString(-1, strCurSel);

					delete m_pDispRankingThread1;
					m_pDispRankingThread1 = NULL;

					m_Edit14.SetWindowText(pszEmpty);
				}
			}
		}
	} else
		if (! m_bMentenance2) {
			if (m_pDispRankingThread2 == NULL) {
				m_Edit15.SetWindowText("○");

				m_pDispRankingThread2 = new CDispRankingThread;
				m_pDispRankingThread2->m_strDataDir = m_strDataDir;
				m_pDispRankingThread2->m_nMode = 18;
				m_pDispRankingThread2->m_pSession = &m_SessionCosmo;
				m_pDispRankingThread2->m_sbCosmoQuoteUrl = m_sbCosmoQuoteUrl;
				m_pDispRankingThread2->m_pMstiCodeInfo = &m_MstiCodeInfo;
				m_pDispRankingThread2->m_pMstpSelCode = &m_MstpSelCode;
				m_pDispRankingThread2->m_bAutoDelete = FALSE;
				m_pDispRankingThread2->CreateThread();

				nWaitThreadCount2 = 0;
				SetWMUserTimer(0, 17, NULL);
			} else {
				if (WaitForSingleObject(m_pDispRankingThread2->m_hThread, 0) == WAIT_TIMEOUT) {
//					if (nWaitThreadCount2 ++ < 1000)
//						SetWMUserTimer(0, 17, NULL);
//					if (++ nWaitThreadCount2 < 94) {
					if (++ nWaitThreadCount2 < 188) {
						KillWMUserTimer(17);
						SetWMUserTimer(100, 17, NULL);
					} else {
						m_Edit15.SetWindowText("●");
						m_Edit19.SetWindowText(IToA(++ m_nDispStockAveThreadTimeoutCount));

						m_PaThreadTimeout.Add(m_pDispRankingThread2);
						m_pDispRankingThread2 = NULL;
						if (! m_bChkThreadTimerRun) {
							m_bChkThreadTimerRun = TRUE;
							SetWMUserTimer(1000, 21, NULL);
						}
					}
				} else {
					char chSijoEx;
					CString strMainCode;

					nTopIndex = m_List5.GetTopIndex();
					if ((nCurSel = m_List5.GetCurSel()) != LB_ERR) {
						m_List5.GetText(nCurSel, strCurSel);
						strCurSel = strCurSel.Left(strCurSel.Find(' '));
					}
					m_List5.ResetContent();

					for (i = 0, imax = m_pDispRankingThread2->m_SaList.GetSize(); i < imax; i ++) {
						strList = m_pDispRankingThread2->m_SaList[i];
						strCode = strList.Left(strList.Find(' '));
						if (strCode.GetLength() == 7) {
							chSijoEx = strCode[6];
							if (chSijoEx == 'M'  ||  chSijoEx == '2')
								strCode.Delete(6);
						}
						strMainCode = strCode.Left(4);
						CodeToName(strMainCode, strName);
						if (strCode != strMainCode)
							continue;
						if (m_MstpNewsCode.Lookup(strCode, pVoid))
							strList.SetAt(4, '*');
						else if (m_MstpNewsCode2.Lookup(strCode, pVoid))
							strList.SetAt(4, '+');
//						if (m_MstpSelCode.Lookup(strCode, pVoid))
							m_List5.AddString(strList);
					}

					if (nTopIndex != LB_ERR)
						m_List5.SetTopIndex(nTopIndex);
					if (nCurSel != LB_ERR)
						m_List5.SelectString(-1, strCurSel);

					delete m_pDispRankingThread2;
					m_pDispRankingThread2 = NULL;

					m_Edit15.SetWindowText(pszEmpty);
				}
			}
		}
}

void CTradeHelperDlg::DispNews(int nMode)
{
	static int nWaitThreadCount0;
	static int nWaitThreadCount1;

	int i;
	CString strCode;
	CString strCodeEx;
	CString strName;
	void* pVoid;

	if (nMode == 0) {
		if (m_pDispNewsThread0 == NULL) {
			m_Edit16.SetWindowText("○");

			m_pDispNewsThread0 = new CDispNewsThread;
			m_pDispNewsThread0->m_nMode = nMode;
			m_pDispNewsThread0->m_strDataDir = m_strDataDir;
			m_pDispNewsThread0->m_DtPreDate = m_DtNewsPreDate;
			m_pDispNewsThread0->m_strCurNewsNo = m_SaNewsNo.GetSize() ? m_SaNewsNo[0] : pszEmpty;
			m_pDispNewsThread0->m_bAutoDelete = FALSE;
			m_pDispNewsThread0->CreateThread();

			nWaitThreadCount0 = 0;
			SetWMUserTimer(0, 19, NULL);
		} else {
			if (WaitForSingleObject(m_pDispNewsThread0->m_hThread, 0) == WAIT_TIMEOUT) {
//				if (nWaitThreadCount0 ++ < 12000)
//					SetWMUserTimer(0, 19, NULL);
//				if (++ nWaitThreadCount0 < 569) {
				if (++ nWaitThreadCount0 < 1138) {
					KillWMUserTimer(19);
					SetWMUserTimer(100, 19, NULL);
				} else {
					m_Edit16.SetWindowText("●");
					m_Edit19.SetWindowText(IToA(++ m_nDispStockAveThreadTimeoutCount));

					m_PaThreadTimeout.Add(m_pDispNewsThread0);
					m_pDispNewsThread0 = NULL;
					if (! m_bChkThreadTimerRun) {
						m_bChkThreadTimerRun = TRUE;
						SetWMUserTimer(1000, 21, NULL);
					}
				}
			} else {
				int nCurSel;
				CString strCurSel;
				CString strNewsNo;
				CWnd* pWnd;
				BOOL bNewNews = FALSE;
				BOOL bNewNewsCode = FALSE;

				if ((nCurSel = m_List6.GetCurSel()) != LB_ERR)
					m_List6.GetText(nCurSel, strCurSel);

				for (i = m_pDispNewsThread0->m_SaCode.GetUpperBound(); i >= 0; i --) {
					strCode = m_pDispNewsThread0->m_SaCode[i];
					strNewsNo = m_pDispNewsThread0->m_SaNewsNo[i];
					CodeToName(strCode, strName, NULL, NULL, NULL, NULL, NULL, NULL, &strCodeEx);
					if (strCode.GetLength() > 4  &&  ! m_MstpNewsNo.Lookup(strNewsNo, pVoid)) {
						m_MstpNewsNo[strNewsNo] = NULL;
						if (! m_MstpNewsCode.Lookup(strCode, pVoid)) {
							m_MstpNewsCode[strCode] = NULL;
							WritePrivateProfileString(PF_APP_GENERAL, PF_KEY_NEWSCODE + IToA(m_nNewsCount ++), strCode, m_strNewsIniFPath);
							bNewNewsCode = TRUE;
						}
						strCodeEx.SetAt(4, '/');
						m_List6.InsertString(0, (strCodeEx + ' ').Left(7) + ' ' + (StrConvHalfWidth(strName) + "     ").Left(6) + ' ' + (' ' + m_pDispNewsThread0->m_SaDateTime[i]).Right(5) + ' ' + m_pDispNewsThread0->m_SaTitle[i]);
						bNewNews = TRUE;
					} else {
						m_pDispNewsThread0->m_SaDateTime.RemoveAt(i);
						m_pDispNewsThread0->m_SaCode.RemoveAt(i);
						m_pDispNewsThread0->m_SaTitle.RemoveAt(i);
						m_pDispNewsThread0->m_SaNewsNo.RemoveAt(i);
						m_pDispNewsThread0->m_SaNewsUrl.RemoveAt(i);
					}
				}
				m_SaNewsDateTime.InsertAt(0, &m_pDispNewsThread0->m_SaDateTime);
				m_SaNewsCode.InsertAt(0, &m_pDispNewsThread0->m_SaCode);
				m_SaNewsTitle.InsertAt(0, &m_pDispNewsThread0->m_SaTitle);
				m_SaNewsNo.InsertAt(0, &m_pDispNewsThread0->m_SaNewsNo);
				m_SaNewsUrl.InsertAt(0, &m_pDispNewsThread0->m_SaNewsUrl);
				if (bNewNews) {
					if (bNewNewsCode) {
						SetCodeList();
						SetNewsList2();

						if (pWnd = CWnd::FindWindow(NULL, m_strChartViewerWndName))
							pWnd->PostMessage(WM_USER + 7, 0);
						if (pWnd = CWnd::FindWindow(NULL, m_strKehaiViewerWndName))
							pWnd->PostMessage(WM_USER + 7, 0);

						m_List6.SetTopIndex(0);
						if (nCurSel != LB_ERR)
							m_List6.SelectString(-1, strCurSel);
					}
					MessageBeep(MB_ICONHAND);
				}

				delete m_pDispNewsThread0;
				m_pDispNewsThread0 = NULL;

				m_Edit16.SetWindowText(pszEmpty);
			}
		}
	} else {
		if (m_pDispNewsThread1 == NULL) {
			m_Edit18.SetWindowText("○");

			m_pDispNewsThread1 = new CDispNewsThread;
			m_pDispNewsThread1->m_nMode = nMode;
			m_pDispNewsThread1->m_strDataDir = m_strDataDir;
			m_pDispNewsThread1->m_bAutoDelete = FALSE;
			m_pDispNewsThread1->CreateThread();

			nWaitThreadCount1 = 0;
			SetWMUserTimer(0, 20, NULL);
		} else {
			if (WaitForSingleObject(m_pDispNewsThread1->m_hThread, 0) == WAIT_TIMEOUT)
				SetWMUserTimer(100, 20, NULL);
			else {
				int imax;
				int nNewsCount2 = 0;

				for (i = 0, imax = m_pDispNewsThread1->m_SaCode.GetSize(); i < imax; i ++) {
					strCode = m_pDispNewsThread1->m_SaCode[i];
					CodeToName(strCode, strName, NULL, NULL, NULL, NULL, NULL, NULL, &strCodeEx);
					if (strCode.GetLength() > 4) {
						if (! m_MstpNewsCode2.Lookup(strCode, pVoid)) {
							m_MstpNewsCode2[strCode] = NULL;
							WritePrivateProfileString(PF_APP_GENERAL, PF_KEY_NEWSCODE2 + IToA(nNewsCount2 ++), strCode, m_strNewsIniFPath);
						}
						m_SaNewsCode2.Add(strCode);
						m_SaNewsDateTime2.Add(m_pDispNewsThread1->m_SaDateTime[i]);
					}
				}
				SetNewsList2();

				delete m_pDispNewsThread1;
				m_pDispNewsThread1 = NULL;

				m_Edit18.SetWindowText(pszEmpty);
			}
		}
	}
}

void CTradeHelperDlg::Disp()
{
	static CStringArray SaLineC;
	int i;
	int imax;
	long lSuryo;
	long lSoldSuryo;
	CStringArray SaLine;
	BOOL bDifferent = FALSE;

	for (i = 0, imax = m_UiaReceiptNo.GetSize(); i < imax; i ++) {
		switch (m_UiaState[i]) {
		case 3:
		case 4:
		case 12:
		case 15:
			lSuryo = m_DwaSellSuryo[i];
			lSoldSuryo = m_DwaSellSoldSuryo[i];
			break;
		default:
			lSuryo = m_DwaSuryo[i];
			lSoldSuryo = m_DwaBuySoldSuryo[i];
		}
		SaLine.Add(StrFormat("%s %s No.%d %ld円 %ld円 x%ld/%ld", m_SaCode[i], StrConvHalfWidth(m_SaName[i]).Left(20), m_UiaReceiptNo[i], m_DwaBuyPrice[i], m_DwaSellPrice[i], lSoldSuryo, lSuryo));
	}

	if (SaLine.GetSize() == SaLineC.GetSize()) {
		for (i = 0, imax = SaLine.GetSize(); i < imax; i ++)
			if (SaLine[i] != SaLineC[i]) {
				bDifferent = TRUE;
				break;
			}
	} else
		bDifferent = TRUE;

	if (bDifferent) {
		m_List3.ResetContent();

		for (i = 0, imax = SaLine.GetSize(); i < imax; i ++)
			m_List3.AddString(SaLine[i]);

		SaLineC.Copy(SaLine);

		m_bDisp = TRUE;
		if (m_List3.GetCount() == 0) {
			CString strEdit1;
			m_Edit1.GetWindowText(strEdit1);
			if (strEdit1.Find('/') == -1) {
				m_List2.SetCurSel(-1);
				OnSelchangeList2();
			}
		} else {
			m_List3.SetCurSel(0);
			OnSelchangeList3();
		}
		m_bDisp = FALSE;
	}
}

void CTradeHelperDlg::DispLog(LPCTSTR lpszFormat, ...)
{
	CStringBuffer sb;
	CStringBuffer sbC;

	va_list vl;
	va_start(vl, lpszFormat);
	sb.FormatV(lpszFormat, vl);
	va_end(vl);

	sbC = sb;
	sbC.TrimRight();
	m_List1.AddString(sbC);
	m_List1.SetTopIndex(m_List1.GetCount() - 1);

	CString strFPath;
#ifdef LOGNAME_THREADID
	strFPath.Format("%s\\Log\\" TRADEHELPER_EXENAME "%s%d.txt", m_strDataDir, COleDateTime::GetCurrentTime().Format("%Y%m%d"), AfxGetThread()->m_nThreadID);
#else
	strFPath.Format("%s\\Log\\" TRADEHELPER_EXENAME "%s.txt", m_strDataDir, COleDateTime::GetCurrentTime().Format("%Y%m%d"));
#endif
	CStdioFile StdioFile(strFPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	StdioFile.SeekToEnd();
	StdioFile.WriteString(sb);
	StdioFile.Close();

	PumpWaitingMessages();
}

void CTradeHelperDlg::DispErrorLog(LPCTSTR lpszFormat, ...)
{
	CStringBuffer sb;

	va_list vl;
	va_start(vl, lpszFormat);
	sb.FormatV(lpszFormat, vl);
	va_end(vl);

	sb = COleDateTime::GetCurrentTime().Format("%H:%M:%S ") + sb;

	DispLog(sb);

	CString strFPath;
	strFPath.Format("%s\\Log\\" TRADEHELPER_EXENAME "Error%s%d.txt", m_strDataDir, COleDateTime::GetCurrentTime().Format("%Y%m%d"), AfxGetThread()->m_nThreadID);
	CStdioFile StdioFile(strFPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	StdioFile.SeekToEnd();
	sb += StrFormat("m_strServerName = %s\n", m_strServerName);
	sb += StrFormat("m_strObject = %s\n", m_strObject);
	sb += StrFormat("m_strObjectC = %s\n", m_strObjectC);
	sb += StrFormat("m_sbOptional = %s\n", m_sbOptional);
	sb += StrFormat("m_nPort = %i\n", m_nPort);
	sb += StrFormat("m_sbHtml =\n%s", m_sbHtml);
	sb += '\n';
	StdioFile.WriteString(sb);
	StdioFile.Close();
}

void CTradeHelperDlg::SetCheckedDiffPrice()
{
	BOOL bShift = GetKeyState(VK_SHIFT) < 0;
	BOOL bCtrl = GetKeyState(VK_CONTROL) < 0;
	if (bShift || bCtrl) {
		int nMode = bShift && bCtrl ? 2 : bShift ? 0 : 1;
		CDaoDatabase Database;

		while (1) {
			try
			{
				COleDateTime DtCur = GetCurrentTimeEx();
				COleDateTime DtDate;
				POSITION pos;
				CString strCode;
				RankingAttr RankingAttr;
				COleVariant pKeyArray[2];
				COleVariant var;

				Database.Open(m_strDBFPath, FALSE, TRUE);

				CDaoRecordset RsHiashi(&Database);
				RsHiashi.Open(dbOpenTable, TBL_HIASHI);
				RsHiashi.SetCurrentIndex(pszPrimaryKey);

				DtDate.SetDate(DtCur.GetYear(), DtCur.GetMonth(), DtCur.GetDay());
				pKeyArray[0] = COleVariant(DtDate);

				pos = m_MstrCodeRankingAttr.GetStartPosition();
				while (pos) {
					m_MstrCodeRankingAttr.GetNextAssoc(pos, strCode, RankingAttr);
					if (strCode != "101") {
						pKeyArray[1] = COleVariant(strCode, VT_BSTRT);
						RsHiashi.Seek("=", pKeyArray, 2);
						if (! RsHiashi.IsEOF()) {
							RsHiashi.GetFieldValue(3 + nMode, var);
							RankingAttr.lCheckedDiffPrice = var.lVal / GetDiff(var.lVal + 1L);
							RankingAttr.lCheckedTradeCount1000 = RankingAttr.plTradeCount1000[5 - 1];
							m_MstrCodeRankingAttr[strCode] = RankingAttr;
						}
					}
				}
				if (nMode == 2) {
					pos = m_MstrCodeRankingAttr2.GetStartPosition();
					while (pos) {
						m_MstrCodeRankingAttr2.GetNextAssoc(pos, strCode, RankingAttr);
						RankingAttr.lCheckedDiffPrice = RankingAttr.lDiffPrice;
						RankingAttr.lCheckedTradeCount1000 = RankingAttr.plTradeCount1000[5 - 1];
						m_MstrCodeRankingAttr2[strCode] = RankingAttr;
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
				DispErrorLog(StrFormat("DAO 銘柄名取得エラー: %s\n", GetExceptionErrorMessage(pEx)));
				pEx->Delete();
			}
			catch (CException* pEx) {
				DispErrorLog("銘柄名取得エラー: %s\n", GetExceptionErrorMessage(pEx));
				pEx->Delete();
			}

			break;
		}
	}
}

void CTradeHelperDlg::SaveState()
{
	if (m_bInitDialog) {
		int i;
		int imax;
		CString strText;
		CString strCode;
		CString strName;
		CString strFPath;
		CStringBuffer sb;

		for (i = 0, imax = m_SaCode.GetSize(); i < imax; i ++)
			sb += StrFormat("\"%s\",\"%s\",%d,%d,%ld,%ld,%ld,%ld,%ld,%ld,%d,%hd,%d\n", m_SaCode[i], m_SaName[i], m_UiaReceiptNo[i], m_UiaState[i], m_DwaBuyPrice[i], m_DwaSellPrice[i], m_DwaSuryo[i], m_DwaBuySoldSuryo[i], m_DwaSellSuryo[i], m_DwaSellSoldSuryo[i], m_UiaTick[i], m_WaUnit[i], m_UiaSemiAuto[i]);

		strFPath = m_strDataDir + "\\" FNAME_ORDER;
		{
			CStdioFile StdioFile(strFPath, CFile::modeCreate | CFile::modeWrite);
			StdioFile.WriteString(sb);
			StdioFile.Close();
		}
	}
}

void CTradeHelperDlg::ClickStreamer(int nPX, int nPY)
{
	int nX = nPX * (65536 / 1920);
	int nY = nPY * (65536 / 1080);

	::mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
	::mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
	::mouse_event(MOUSEEVENTF_LEFTUP   | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
}

CString CTradeHelperDlg::CopyStreamer(int nPX, int nPY)
{
	HGLOBAL hMem;
	LPVOID lpMem;
	BOOL bOpenClipboard;
	char pszStk[5];

	int nX = nPX * (65536 / 1920);
	int nY = nPY * (65536 / 1080);

	bOpenClipboard = FALSE;
	do {
		if (! ::OpenClipboard(NULL)) {
			DispErrorLog("クリップボードオープンエラー: %s\n", GetLastErrorMessage());
			break;
		}
		bOpenClipboard = TRUE;
		// Remove the current Clipboard contents
		if(! EmptyClipboard()) {
			DispErrorLog("クリップボード削除エラー: %s\n", GetLastErrorMessage());
			break;
		}
	} while (0);
	if (bOpenClipboard  &&  ! CloseClipboard())
		DispErrorLog("コピー削除クリップボードクローズエラー: %s\n", GetLastErrorMessage());

	for (int i = 0; i < 2; i ++) {
		::mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
		::mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
		::mouse_event(MOUSEEVENTF_LEFTUP   | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
		::mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
		::mouse_event(MOUSEEVENTF_LEFTUP   | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
		Sleep(100);
		keybd_event( VK_CONTROL, 0, 0, 0 );
		keybd_event( 'C', 0, 0, 0 );
		keybd_event( 'C', 0, KEYEVENTF_KEYUP, 0);
		keybd_event( VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);

		bOpenClipboard = FALSE;
		*pszStk = '\0';
		do {
			if (! ::OpenClipboard(NULL)) {
				DispErrorLog("クリップボードオープンエラー: %s\n", GetLastErrorMessage());
				break;
			}
			bOpenClipboard = TRUE;
			if ((hMem = GetClipboardData(CF_TEXT)) == NULL) {
				DispErrorLog("クリップボードデータ取得エラー: %s\n", GetLastErrorMessage());
				break;
			}
			if ((lpMem = GlobalLock(hMem)) == NULL) {
				DispErrorLog("メモリロックエラー: %s\n", GetLastErrorMessage());
				break;
			}
			lstrcpy(pszStk, (LPTSTR)lpMem);
			if (! GlobalUnlock(hMem)  &&  GetLastError() != NO_ERROR) {
				DispErrorLog("メモリロック解除エラー: %s\n", GetLastErrorMessage());
				break;
			}
		} while (0);
		if (bOpenClipboard  &&  ! CloseClipboard())
			DispErrorLog("クリップボードクローズエラー: %s\n", GetLastErrorMessage());
		if (*pszStk)
			break;
	}

	return pszStk;
}

void CTradeHelperDlg::SelStreamer(int nIndex)
{
	CWnd* pWnd;

//	if (pWnd = FindWindow(pszStreamerClassName, pszStreamerWndName)) {
	if (pWnd = FindWindow(NULL, m_strTradeConsoleWndName)) {
		CRect Rect;
		::GetWindowRect(pWnd->m_hWnd, &Rect);
		if (Rect.left == 0  &&  Rect.top == 0  &&  Rect.right == 1003  &&  Rect.bottom == 516) {
			pWnd->SetForegroundWindow();

			CPoint Point;
			::GetCursorPos(&Point);

//			ClickStreamer(38, 122 + (454 - 94) / 9 * nIndex);
//			ClickStreamer(72, 122 + (454 - 94) / 9 * nIndex);
//			ClickStreamer(72, 120 + (444 - 93) / 9 * nIndex);
			ClickStreamer(123, 84 + (453 - 75) / 9 * nIndex);

			CString strEdit1;
			m_Edit1.GetWindowText(strEdit1);
			if (strEdit1.Find('/') != -1) {
				CString strStk = CopyStreamer(20, 84 + (453 - 75) / 9 * nIndex);
				if (strStk.GetLength() && strStk != strEdit1.Left(4)) {
					m_Edit1.SetFocus();
					m_Edit1.SetSel(0, -1);
					m_Edit1.Paste();
				}
			}

			::SetCursorPos(Point.x, Point.y);
			SetForegroundWindow();
		}
	}
}

void CTradeHelperDlg::DelStreamer(int nIndex)
{
	int nX;
	int nY;

//	nX = 83 * (65536 / 1280);
	nX = 81 * (65536 / 1920);
//	nY = (130 + (501 - 150) / 9 * nIndex) * (65536 / 1024);
//	nY = (102 + (501 - 150) / 9 * nIndex) * (65536 / 1024);
//	nY = (102 + (454 - 94) / 9 * nIndex) * (65536 / 1024);
//	nY = (102 + (444 - 93) / 9 * nIndex) * (65536 / 1024);
	nY = (84 + (453 - 75) / 9 * nIndex) * (65536 / 1080);
	::mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
	::mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
	::mouse_event(MOUSEEVENTF_LEFTUP   | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
	Sleep(100);
	keybd_event( VK_HOME, 0, 0, 0 );
	keybd_event( VK_HOME, 0, KEYEVENTF_KEYUP, 0);
	keybd_event( VK_TAB, 0, 0, 0 );
	keybd_event( VK_TAB, 0, KEYEVENTF_KEYUP, 0);
//	nX = 20 * (65536 / 1280);
//	nX = 18 * (65536 / 1280);
	nX = 20 * (65536 / 1920);
	::mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
	::mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
	::mouse_event(MOUSEEVENTF_LEFTUP   | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
	::mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
	::mouse_event(MOUSEEVENTF_LEFTUP   | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
	Sleep(100);
	keybd_event( VK_DELETE, 0, 0, 0 );
	keybd_event( VK_DELETE, 0, KEYEVENTF_KEYUP, 0);
	keybd_event( VK_RETURN, 0, 0, 0 );
	keybd_event( VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
}

void CTradeHelperDlg::SetStreamer(int nIndex, LPCTSTR lpszCode)
{
	int nX;
	int nY;

	nX = 20 * (65536 / 1920);
	nY = (84 + (453 - 75) / 9 * nIndex) * (65536 / 1080);

	DelStreamer(nIndex);
	Sleep(100);
	if (*lpszCode) {
		Sleep(100);
		::mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
		::mouse_event(MOUSEEVENTF_LEFTUP   | MOUSEEVENTF_ABSOLUTE, nX, nY, 0, NULL);
		Sleep(100);
		keybd_event( lpszCode[0], 0, 0, 0 );
		keybd_event( lpszCode[0], 0, KEYEVENTF_KEYUP, 0);
		keybd_event( lpszCode[1], 0, 0, 0 );
		keybd_event( lpszCode[1], 0, KEYEVENTF_KEYUP, 0);
		keybd_event( lpszCode[2], 0, 0, 0 );
		keybd_event( lpszCode[2], 0, KEYEVENTF_KEYUP, 0);
		keybd_event( lpszCode[3], 0, 0, 0 );
		keybd_event( lpszCode[3], 0, KEYEVENTF_KEYUP, 0);
		keybd_event( VK_RETURN, 0, 0, 0 );
		keybd_event( VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
	}
}

void CTradeHelperDlg::ReadInfo()
{
	CDaoDatabase Database;
	COleVariant pKeyArray[2];
	COleVariant var;
	CString strCode;
	Info InfoWork;

	while (1) {
		try {
			Database.Open(m_strDBFPath, FALSE, TRUE);

			CDaoRecordset RsHiashi(&Database);
			RsHiashi.Open(dbOpenTable, TBL_HIASHI);

			RsHiashi.SetCurrentIndex(pszSecondaryKey);
			pKeyArray[1] = COleVariant(m_DtPreDate);

			CDaoRecordset RsInfo(&Database);
			RsInfo.Open(dbOpenTable, TBL_INFO);
			RsInfo.SetCurrentIndex(pszPrimaryKey);

			m_MstiCodeInfo.RemoveAll();

			while (! RsInfo.IsEOF()) {
				RsInfo.GetFieldValue(0, var);
				strCode = V_BSTRT((LPVARIANT)var);

				RsInfo.GetFieldValue(1, var);
				InfoWork.strName = V_BSTRT((LPVARIANT)var);

				RsInfo.GetFieldValue(2, var);
				InfoWork.strSijo = V_BSTRT((LPVARIANT)var);

				RsInfo.GetFieldValue(4, var);
				InfoWork.sUnit = var.iVal;

				pKeyArray[0] = COleVariant(strCode, VT_BSTRT);
				if (RsHiashi.Seek("<=", pKeyArray, 2)) {
					RsHiashi.GetFieldValue(5, var);
					InfoWork.lPreEndPrice = var.lVal;

					RsHiashi.GetFieldValue(6, var);
					InfoWork.lPreEndTradeCount = var.lVal;
				} else
					InfoWork.lPreEndPrice = InfoWork.lPreEndTradeCount = 0L;

				m_MstiCodeInfo[strCode] = InfoWork;

				RsInfo.MoveNext();
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
			DispErrorLog(StrFormat("DAO 銘柄情報取得エラー: %s\n", GetExceptionErrorMessage(pEx)));
			pEx->Delete();
		}
		catch (CException* pEx) {
			DispErrorLog("銘柄情報取得エラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();
		}

		break;
	}
}

int CTradeHelperDlg::CodeToName(CString& strCode, CString& strName, CString* pstrSijoName, short* psUnit, long* plHighPrice, long* plLowPrice, long* plPreEndPrice, long* plTradeCount, CString* pstrCodeEx) 
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
			DispErrorLog(StrFormat("DAO 銘柄名取得エラー: %s\n", GetExceptionErrorMessage(pEx)));
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

void CTradeHelperDlg::ButtonF2() 
{
//	OnButton2();
	OnButton4();
}

void CTradeHelperDlg::ButtonF3() 
{
//	OnButton7();
	OnButton5();
}

void CTradeHelperDlg::ButtonF4() 
{
	OnButton3();
}

void CTradeHelperDlg::ButtonF5() 
{
	OnButton8();
}

void CTradeHelperDlg::ButtonF6() 
{
	OnButton6();
}

void CTradeHelperDlg::ButtonF7() 
{
	OnButton10();
}

void CTradeHelperDlg::ButtonF8() 
{
	OnButton11();
}

void CTradeHelperDlg::ButtonF9() 
{
	OnButton12();
}

void CTradeHelperDlg::ButtonF11() 
{
	OnButton13();
}

void CTradeHelperDlg::ButtonF12() 
{
	OnButton14();
}

int CTradeHelperDlg::CheckLicense()
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

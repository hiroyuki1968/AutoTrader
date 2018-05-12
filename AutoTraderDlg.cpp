// AutoTraderDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "AutoTrader.h"
#include "AutoTraderDlg.h"

#include <sys/timeb.h>
#include <WINIOCTL.H>
#include "License.h"
#include "Html.h"
#include "AutoTraderDef.h"
#include "DlHtmlThread.h"
#include "DlFileThread.h"
#include "RemitRegDlg.h"
#include "UpdateDetailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderDlg ダイアログ

CAutoTraderDlg::CAutoTraderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoTraderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAutoTraderDlg)
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hMapping = NULL;
	m_pMappingView = NULL;
	m_pMappingViewOffset = NULL;
	m_pMappingViewCell = NULL;
	for (int i = 0; i < sizeof(m_ppSession) / sizeof(CInternetSession*); i ++)
		m_ppSession[i] = NULL;
	m_ppSessionCosmo = NULL;
	m_pSetupDlg = NULL;
	m_nWMUserTimer = 100;
	m_bUserCall = FALSE;
	m_dwMaxConnectionsPerServer = 0;
}

void CAutoTraderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAutoTraderDlg)
	DDX_Control(pDX, IDC_BUTTON4, m_Btn4);
	DDX_Control(pDX, IDC_BUTTON5, m_Btn5);
	DDX_Control(pDX, IDC_CHECK1, m_Check1);
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
	DDX_Control(pDX, IDC_EDIT18, m_Edit18);
	DDX_Control(pDX, IDC_LIST1, m_List1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAutoTraderDlg, CDialog)
	//{{AFX_MSG_MAP(CAutoTraderDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_CHECK10, OnCheck10)
	ON_BN_CLICKED(IDC_CHECK11, OnCheck11)
	ON_BN_CLICKED(IDC_CHECK12, OnCheck12)
	ON_BN_CLICKED(IDC_CHECK13, OnCheck13)
	ON_BN_CLICKED(IDC_CHECK14, OnCheck14)
	ON_BN_CLICKED(IDC_CHECK15, OnCheck15)
	ON_BN_CLICKED(IDC_CHECK16, OnCheck16)
	ON_BN_CLICKED(IDC_CHECK17, OnCheck17)
	ON_BN_CLICKED(IDC_CHECK18, OnCheck18)
	ON_BN_CLICKED(IDC_CHECK19, OnCheck19)
	ON_EN_SETFOCUS(IDC_EDIT16, OnSetfocusEdit16)
	ON_EN_SETFOCUS(IDC_EDIT20, OnSetfocusEdit20)
	ON_EN_SETFOCUS(IDC_EDIT21, OnSetfocusEdit21)
	ON_EN_SETFOCUS(IDC_EDIT22, OnSetfocusEdit22)
	ON_EN_SETFOCUS(IDC_EDIT23, OnSetfocusEdit23)
	ON_EN_SETFOCUS(IDC_EDIT24, OnSetfocusEdit24)
	ON_EN_SETFOCUS(IDC_EDIT25, OnSetfocusEdit25)
	ON_EN_SETFOCUS(IDC_EDIT26, OnSetfocusEdit26)
	ON_EN_SETFOCUS(IDC_EDIT27, OnSetfocusEdit27)
	ON_EN_SETFOCUS(IDC_EDIT28, OnSetfocusEdit28)
	ON_EN_SETFOCUS(IDC_EDIT29, OnSetfocusEdit29)
	ON_EN_CHANGE(IDC_EDIT16, OnChangeEdit16)
	ON_EN_CHANGE(IDC_EDIT20, OnChangeEdit20)
	ON_EN_CHANGE(IDC_EDIT21, OnChangeEdit21)
	ON_EN_CHANGE(IDC_EDIT22, OnChangeEdit22)
	ON_EN_CHANGE(IDC_EDIT23, OnChangeEdit23)
	ON_EN_CHANGE(IDC_EDIT24, OnChangeEdit24)
	ON_EN_CHANGE(IDC_EDIT25, OnChangeEdit25)
	ON_EN_CHANGE(IDC_EDIT26, OnChangeEdit26)
	ON_EN_CHANGE(IDC_EDIT27, OnChangeEdit27)
	ON_EN_CHANGE(IDC_EDIT28, OnChangeEdit28)
	ON_EN_CHANGE(IDC_EDIT29, OnChangeEdit29)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER, OnUser)
	ON_MESSAGE(WM_USER + 1, OnUser1)
	ON_MESSAGE(WM_USER + 2, OnUser2)
	ON_MESSAGE(WM_USER + 3, OnUser3)
	ON_MESSAGE(WM_USER + 4, OnUser4)
	ON_MESSAGE(WM_USER + 5, OnUser5)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderDlg メッセージ ハンドラ

BOOL CAutoTraderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。

	m_bOnInitDialog = TRUE;
	BOOL bComplete = FALSE;

	SetWindowText(m_strMainExeWndName);

	ShowWindow(SW_SHOW);
	UpdateWindow();

	if (m_nExecMode == 2)
		DtsCurrentTime = COleDateTime::GetCurrentTime() - m_DtSimStart;

	int i;
	int j;
	int imax;
	COleDateTime DtCur = GetCurrentTimeEx();
	COleDateTime DtDate(DtCur.GetYear(), DtCur.GetMonth(), DtCur.GetDay(), 0, 0, 0);
	int nHour;
	int nMinute;
	HANDLE hFile;
	WORD wFlag;
	DWORD dwBytesReturned;
	CDaoDatabase Database;
	BOOL bCreateDB = FALSE;
	BOOL bData;
	CHtmlTokenizer HtmlTokenizer;
	CStringTokenizer StringTokenizer;
	CStringBuffer sbTag;
	CStringBuffer sbValue;
	int nPtr0;
	int nPtr1;
	int nSelCodeCount;
	int nMemMapHCount;
	DWORD dwMemMapInfoSize;
	int nMonth;
	int nDay;
	int nDayOfWeek;
	int nDayOfWeekWork;
	int nContractYear0;
	int nContractMonth0;
	CStringBuffer sbI;
	char pszBuf[MAX_PATH];
	long lNiceLockOn;
	CString strCode;
	void* pVoid;
	CStringArray SaHiashiCode;

	m_dwMaxConnectionsPerServer = GetMaxConnectionsPerServer();

	GetTempPath(MAX_PATH, m_strTempDir.GetBuffer(MAX_PATH));
	m_strTempDir.ReleaseBuffer();
//	m_strTempCompressDir = m_strTempDir + "Compress";

	m_pServer = NULL;
	m_sbCosmoLoginUrl = URL_LOGIN2;
	m_sbCosmoQuoteUrl = URL_COSMOQUOTE;
	m_strOrgMeigaraIniFPath = m_strDataDir + "\\" FNAME_MEIGARA;
	switch (m_nExecMode) {
	case 0:
		m_strMeigaraIniFPath = m_strOrgMeigaraIniFPath;
		break;
	case 1:
		m_strMeigaraIniFPath = m_strDataDir + "\\" FNAME_MEIGARASIM;
		break;
	default:
		m_strMeigaraIniFPath = m_strDataDir + "\\" FNAME_MEIGARARTS;
	}
	m_strLastStatusIniFPath = m_strDataDir + _T("\\") FNAME_LASTSTATUS;
	m_strOrgDBFPath = m_strDataDir + "\\" FNAME_DB;
	m_strRstDBFPath = m_strDataDir + "\\" FNAME_RTSDB;
	if (m_nExecMode == 2) {
		m_strHomeDBFPath = m_strRstDBFPath;
//		m_strDBFPath = m_strTempCompressDir + "\\" FNAME_RTSDB;
		m_strDBFPath = m_strTempDir + FNAME_RTSDB;
	} else {
		m_strHomeDBFPath = m_strOrgDBFPath;
//		m_strDBFPath = m_strTempCompressDir + "\\" FNAME_DB;
		m_strDBFPath = m_strTempDir + FNAME_DB;
	}
	m_strTempDBFPath = m_strDataDir + "\\" FNAME_TEMPDB;
	m_strAutoExecFPath = m_strDataDir + _T("\\") FNAME_AUTOEXECTXT;
	m_strUpdateTxtFName = FNAME_UPDATETXT;
	m_strUpdateTxtFPath = m_strDataDir + _T('\\') + m_strUpdateTxtFName;
	CString strFName;
#ifdef LOGNAME_THREADID
	strFName.Format(MAIN_EXENAME "%s%d.txt", COleDateTime::GetCurrentTime().Format("%Y%m%d"), AfxGetThread()->m_nThreadID);
#else
	strFName.Format(MAIN_EXENAME "%s.txt", COleDateTime::GetCurrentTime().Format("%Y%m%d"));
#endif
	m_strHomeLogFPath = m_strDataDir + "\\Log\\" + strFName;
	m_strLogFPath = m_strTempDir + strFName;
	m_lKabuSellPlusCount =
	m_lKabuSellPlus =
	m_lKabuSellZeroCount =
	m_lKabuSellMinusCount =
	m_lKabuSellMinus =
		0;
	m_bSetTimer2 =
	m_bTrade =
	m_bDispDebugLog =
	m_bSimStop =
	m_bLog =
	m_bTimeSim =
	m_bLicenseCanceled =
	m_bQuitReq =
		FALSE;
	m_bDispLog = TRUE;

	LoadLastStatus();

	if (CheckLicense()) {
		PostQuitMessage(0);
		return TRUE;
	}

	if (
//		m_strKazakaId0.IsEmpty()
//		|| m_strKazakaId1.IsEmpty()
//		|| m_strKazakaPasswd.IsEmpty()
		m_strTreasureId.IsEmpty()
		|| m_strTreasurePasswd.IsEmpty()
		|| m_strMatsuiId.IsEmpty()
		|| m_strMatsuiPasswd.IsEmpty()
		|| m_strCosmoId.IsEmpty()
		|| m_strCosmoPasswd.IsEmpty()
		|| m_strDataDir.IsEmpty()
	)
		OnButton7();

	BOOL bUpdateAutoTraderReq = m_bUpdateAutoTraderReq;
	if (m_bUpdateAutoTraderReq  &&  ! m_bUpdateCheck  &&  DtDate > m_DtAutoTraderUpdateDate) {
		UpdateAutoTrader1();
		if (m_bQuitReq) {
			PostQuitMessage(0);
			return FALSE;
		}
	}

	// アップデート時の自動実行
	BOOL bAutoExec;
	BOOL bSetup = FALSE;
	int nExeMode = 0;
	int nUpdateAutoExec = 0;
	if (bAutoExec = CFile::GetStatus(m_strAutoExecFPath, m_FileStatus)) {
		CStringBuffer strAutoExec;
		int nReStrFile = ReStrFile(m_strAutoExecFPath, strAutoExec);
		DeleteFile(m_strAutoExecFPath);
		if (nReStrFile) {
			PostQuitMessage(0);
			return FALSE;
		}
		/*
			nExeMode
				0x080 - Update by Setup
		*/
		nUpdateAutoExec = _stscanf(strAutoExec, _T("%d"), &nExeMode);
		switch (nUpdateAutoExec) {
		case 1:
			bSetup = nExeMode & 0x80;
			break;
		default:
			MessageBox(_T("自動実行パラメーター取得エラー"), NULL, MB_ICONSTOP);
			PostQuitMessage(0);
			return FALSE;
		}
	}
	if (m_bUpdateCheck  ||  ! bUpdateAutoTraderReq  &&  DtDate > m_DtAutoTraderUpdateDate) {
		int nAutoTraderUpdateType = m_nAutoTraderUpdateType;
		if (m_bUpdateCheck)
			if (m_nAutoTraderUpdateType == 6)
				m_nAutoTraderUpdateType = 0;
			else
				m_nAutoTraderUpdateType = m_nAutoTraderUpdateType / 2 * 2;
		switch (UpdateAutoTrader0()) {
		case 0:
			if (m_bUpdateCheck)
				MessageBox(_T("既に最新です"), NULL, MB_ICONINFORMATION);
			break;
		case 1:
			UpdateAutoTrader1();
		}
		if (m_bUpdateCheck)
			m_nAutoTraderUpdateType = nAutoTraderUpdateType;
		if (m_bUpdateCheck || m_bQuitReq) {
			PostQuitMessage(0);
			return FALSE;
		}
	} 
	if (bAutoExec)
		if (bSetup) {
			// 設定ダイアログ
			OnButton7();
		} else {
			if (! m_bUpdateAutoTraderReq)
				MessageBox(_T("AutoTrader のアップデートが完了しました"), NULL, MB_ICONINFORMATION);
		}

	CStringBuffer sbDPath = m_strDataDir + "\\Data";
	if (! CFile::GetStatus(sbDPath, m_FileStatus)) {
		if (ForceDir(sbDPath)) {
			MessageBox(StrFormat("%s 作成エラー: %s", sbDPath, GetLastErrorMessage()));
			PostQuitMessage(0);
			return TRUE;
		}

		if ((hFile = CreateFile(sbDPath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL)) != INVALID_HANDLE_VALUE) {
			wFlag = 1;
			DeviceIoControl(hFile, FSCTL_SET_COMPRESSION, &wFlag, sizeof(WORD), NULL, 0, &dwBytesReturned, NULL);
			CloseHandle(hFile);
		}
	}
	sbDPath = m_strDataDir + "\\Log";
	if (! CFile::GetStatus(sbDPath, m_FileStatus))
		if (ForceDir(sbDPath)) {
			MessageBox(StrFormat("%s 作成エラー: %s", sbDPath, GetLastErrorMessage()));
			PostQuitMessage(0);
			return TRUE;
		}
/*
	if (! CFile::GetStatus(m_strTempCompressDir, m_FileStatus)) {
		if (ForceDir(m_strTempCompressDir)) {
			MessageBox(StrFormat("%s 作成エラー: %s", m_strTempCompressDir, GetLastErrorMessage()));
			PostQuitMessage(0);
			return TRUE;
		}
	}
*/

#ifndef LOGNAME_THREADID
	CStdioFile StdioFile(m_strLogFPath, CFile::modeCreate | CFile::modeWrite);
	StdioFile.Close();
#endif

	DispLog("%s 履歴ファイル削除開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
	CFileFind Ff;
	CFileFind FfDir0;
	CFileFind FfDir1;
	BOOL bFfFound;
	BOOL bFfDir0Found;
	BOOL bFfDir1Found;
	CTime TFileDate;
	CTime TDelDate(CTime::GetCurrentTime() - CTimeSpan(72 * 7 / 5 + 7 + 6, 0, 0, 0));
	bFfFound = Ff.FindFile(m_strDataDir + "\\Log\\*.txt");
	while (bFfFound) {
		bFfFound = Ff.FindNextFile();
		if (Ff.GetLastWriteTime(TFileDate)  &&  TFileDate < TDelDate)
			if (! DeleteFile(Ff.GetFilePath()))
				DispErrorLog("%s 削除エラー: %s\n", Ff.GetFilePath(), GetLastErrorMessage());
	}
	Ff.Close();
	bFfFound = Ff.FindFile(m_strDataDir + "\\Data\\*.mdb");
	while (bFfFound) {
		bFfFound = Ff.FindNextFile();
		if (Ff.GetLastWriteTime(TFileDate)  &&  TFileDate < TDelDate)
			if (! DeleteFile(Ff.GetFilePath()))
				DispErrorLog("%s 削除エラー: %s\n", Ff.GetFilePath(), GetLastErrorMessage());
	}
	Ff.Close();
	bFfDir0Found = FfDir0.FindFile(m_strDataDir + "\\Chart\\0000 *");
	while (bFfDir0Found) {
		bFfDir0Found = FfDir0.FindNextFile();
		if (! FfDir0.IsDots()) {
			bFfFound = Ff.FindFile(FfDir0.GetFilePath() + "\\*.*");
			while (bFfFound) {
				bFfFound = Ff.FindNextFile();
				if (! Ff.IsDirectory()  &&  Ff.GetLastWriteTime(TFileDate)  &&  TFileDate < TDelDate)
					if (! DeleteFile(Ff.GetFilePath()))
						DispErrorLog("%s 削除エラー: %s\n", Ff.GetFilePath(), GetLastErrorMessage());
			}
			Ff.Close();
		}
	}
	FfDir0.Close();
	bFfDir0Found = FfDir0.FindFile(m_strDataDir + "\\Chart\\*");
	while (bFfDir0Found) {
		bFfDir0Found = FfDir0.FindNextFile();
		if (! FfDir0.IsDots()) {
			bFfDir1Found = FfDir1.FindFile(FfDir0.GetFilePath() + "\\*");
			while (bFfDir1Found) {
				bFfDir1Found = FfDir1.FindNextFile();
				if (! FfDir1.IsDots()) {
					bFfFound = Ff.FindFile(FfDir1.GetFilePath() + "\\*.gif");
					while (bFfFound) {
						bFfFound = Ff.FindNextFile();
						if (Ff.GetLastWriteTime(TFileDate)  &&  TFileDate < TDelDate)
							if (! DeleteFile(Ff.GetFilePath())  &&  ! DeleteFile(Ff.GetRoot() + '\\' + Ff.GetFileName()))
								DispErrorLog("%s 削除エラー: %s\n", Ff.GetFilePath(), GetLastErrorMessage());
					}
					Ff.Close();
					bFfFound = Ff.FindFile(FfDir1.GetFilePath() + "\\*.gif");
					Ff.Close();
					if (! bFfFound) {
						DeleteFile(FfDir1.GetFilePath() + "\\Thumbs.db");
						RemoveDirectory(FfDir1.GetFilePath());
					}
				}
			}
			FfDir1.Close();
			RemoveDirectory(FfDir0.GetFilePath());
		}
	}
	FfDir0.Close();
	DispLog("%s 履歴ファイル削除終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));

	if (! m_nExecMode) {
		nDayOfWeek = DtCur.GetDayOfWeek();
		nHour = DtCur.GetHour();
		nMinute = DtCur.GetMinute();
		if (nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour >= 6  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16)  &&  CFile::GetStatus(m_strHomeDBFPath, m_FileStatus)) {
			try {
				COleDateTime DtPreDate;
				COleDateTime DtMaxDate;
				COleVariant pKeyArray[2];
				COleVariant var;

				Database.Open(m_strHomeDBFPath, FALSE, TRUE);

				CDaoRecordset RsHiashi(&Database);
				RsHiashi.Open(dbOpenTable, TBL_HIASHI);

				RsHiashi.SetCurrentIndex(pszPrimaryKey);
				pKeyArray[0] = COleVariant(DtDate);
				if (RsHiashi.Seek("<", pKeyArray, 2)) {
					RsHiashi.GetFieldValue(0, var);
					DtPreDate = var.date;
				}
				pKeyArray[0] = COleVariant(COleDateTime(9999, 12, 31, 0, 0, 0));
				if (RsHiashi.Seek("<", pKeyArray, 2)) {
					RsHiashi.GetFieldValue(0, var);
					DtMaxDate = var.date;
				}

				Database.Close();

				if (DtMaxDate < DtDate) {
					CString strOldDBFName = DtPreDate.Format(MAIN_EXENAME "%Y%m%d.mdb");
					CString strOldDBFPath = m_strDataDir + "\\Data\\" + strOldDBFName;
					if (! CFile::GetStatus(strOldDBFPath, m_FileStatus)) {
						DispLog("%s DB リネーム移動 " FNAME_DB " -> Data\\%s\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), strOldDBFName);
						if (! MoveFile(m_strHomeDBFPath, strOldDBFPath))
							DispErrorLog("%s %s リネーム移動エラー: %s\n", m_strHomeDBFPath, strOldDBFPath, GetLastErrorMessage());
						else {
							DispLog("%s DB の圧縮開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
							if ((hFile = CreateFile(strOldDBFPath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL)) != INVALID_HANDLE_VALUE) {
								wFlag = 1;
								DeviceIoControl(hFile, FSCTL_SET_COMPRESSION, &wFlag, sizeof(WORD), NULL, 0, &dwBytesReturned, NULL);
								CloseHandle(hFile);
							}
							DispLog("%s DB の圧縮終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
						}
					}
				}
			}
			catch (CDaoException* pEx) {
				DispErrorLog(StrFormat("DAO 前営業日取得エラー: %s\n", GetExceptionErrorMessage(pEx)));
				pEx->Delete();
			}
			catch (CException* pEx) {
				DispErrorLog("前営業日取得、DB リネーム移動エラー: %s\n", GetExceptionErrorMessage(pEx));
				pEx->Delete();
			}
		}
	}

/*
	LONG lSize = 0L;
	if (CFile::GetStatus(m_strHomeDBFPath, m_FileStatus))
		lSize = m_FileStatus.m_size;
	wFlag = GetDiskFreeSpaceInt64(m_strTempCompressDir) - lSize < 512000000i64 ? 1 : 0;
	if ((hFile = CreateFile(m_strTempCompressDir, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL)) != INVALID_HANDLE_VALUE) {
		DeviceIoControl(hFile, FSCTL_SET_COMPRESSION, &wFlag, sizeof(WORD), NULL, 0, &dwBytesReturned, NULL);
		CloseHandle(hFile);
	}
*/

	if (CFile::GetStatus(m_strHomeDBFPath, m_FileStatus)) {
//		DispLog("%s DB 移動 Dataディレクトリ -> %s\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), m_strTempCompressDir);
		DispLog("%s DB 移動 Dataディレクトリ -> %s\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), m_strTempDir);
		if (! MoveFile(m_strHomeDBFPath, m_strDBFPath))
			DispErrorLog("%s %s 移動エラー: %s\n", m_strHomeDBFPath, m_strDBFPath, GetLastErrorMessage());
	}

	if (m_nExecMode) {
		CString strDBFPath = m_strDataDir + m_DtSimStart.Format("\\Data\\" MAIN_EXENAME "%Y%m%d.mdb");
		if (CFile::GetStatus(strDBFPath, m_FileStatus))
			if (m_nExecMode == 1)
				m_strDBFPath = strDBFPath;
			else
				m_strOrgDBFPath = strDBFPath;
	}

	if (! CFile::GetStatus(m_strDBFPath, m_FileStatus))
		switch (m_nExecMode) {
		case 0:
			if (CreateDB(Database))
				goto CleanUp;
			Database.Close();
			bCreateDB = TRUE;
			break;
		case 1:
			CreateDB(Database);
			goto CleanUp;
		default:
			if (! CFile::GetStatus(m_strOrgDBFPath, m_FileStatus))
				goto CleanUp;
			DispLog("%s DB コピー開始 %s -> %s\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), GetFNameFromFPath(m_strOrgDBFPath), GetFNameFromFPath(m_strDBFPath));
			if (! CopyFile(m_strOrgDBFPath, m_strDBFPath, TRUE))
				DispErrorLog("%s %s コピーエラー: %s\n", m_strOrgDBFPath, m_strDBFPath, GetLastErrorMessage());
			DispLog("%s DB コピー終了 %s -> %s\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), GetFNameFromFPath(m_strOrgDBFPath), GetFNameFromFPath(m_strDBFPath));
		}


	if (m_nExecMode == 2) {
//		BOOL bBeginTrans = FALSE;

		DispLog("%s ワークデータ削除開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));

		try
		{
			Database.Open(m_strDBFPath);

//			Database.m_pWorkspace->BeginTrans();
//			bBeginTrans = TRUE;

			Database.Execute(
				DtCur.Format(
					"DELETE FROM " TBL_HIASHI
					" WHERE "
						FLD_HI_DATE " >= #%Y/%m/%d#"
				),
				dbFailOnError
			);

			Database.Execute(
				DtCur.Format(
					"DELETE FROM " TBL_FUNASHI0
					" WHERE "
						FLD_FU_DATETIME " >= #%Y/%m/%d %H:%M:%S#"
				),
				dbFailOnError
			);

			Database.Execute(
				DtCur.Format(
					"DELETE FROM " TBL_FUNASHI1
					" WHERE "
						FLD_FU_DATETIME " >= #%Y/%m/%d %H:%M:%S#"
				),
				dbFailOnError
			);

			Database.Execute(
				DtCur.Format(
					"DELETE FROM " TBL_FUNASHI2
					" WHERE "
						FLD_FU_DATETIME " >= #%Y/%m/%d %H:%M:%S#"
				),
				dbFailOnError
			);

			Database.Execute(
				DtCur.Format(
					"DELETE FROM " TBL_FUNASHIDATETIME
					" WHERE "
						FLD_FD_DATETIME " >= #%Y/%m/%d %H:%M:%S#"
				),
				dbFailOnError
			);

//			Database.m_pWorkspace->CommitTrans();
//			bBeginTrans = FALSE;
			Database.Close();
		}
		catch (CException* pEx) {
			DispErrorLog("ワークデータ削除エラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();
//			if (bBeginTrans)
//				Database.m_pWorkspace->Rollback();
		}

		DispLog("%s ワークデータ削除終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
	}

	if (! m_nExecMode) {
		try
		{
			for (i = 0; ppszUrlLogin[i]; i ++) {
				if (i == 0) continue;
				if (m_bMentenance1  &&  i == 1) continue;

//				switch (i) {
//				default:
					DispLog("%s 初期化ダウンロード - 松井証券\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
//				}

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

//				if (ppszObjLogin[i])
					m_strObject = ppszObjLogin[i];
//				switch (i) {
//				default:
					m_sbOptional.Format(ppszOptLogin[i], m_strMatsuiId, m_strMatsuiPasswd);
//				}
				if (DlHtml(CHttpConnection::HTTP_VERB_POST, INTERNET_FLAG_SECURE, HEA_POST, m_sbOptional))
					goto CleanUp;

				bData = FALSE;
				switch (i) {
				case 0:
					if ((nPtr0 = m_sbHtml.Find("QUICK情報")) == -1)
						goto DataCleanUp1;
					HtmlTokenizer.SetHtml(m_sbHtml);
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					if (! HtmlTokenizer.HtmlReverseTok())
						goto DataCleanUp1;
					if (HtmlTokenizer.FindTagAttr("href", sbValue) != 2)
						goto DataCleanUp1;
					sbValue = StrQTrim(sbValue);
					if ((nPtr0 = StrReverseFindEx(sbValue, "/docs/")) == -1)
						goto DataCleanUp1;
					sbValue.Delete(nPtr0 + 1, sbValue.GetLength());
					m_psbQuickInfoUrl[i] = sbValue;
					if ((nPtr0 = m_sbHtml.Find("買い注文", HtmlTokenizer.m_nHtmlPtr)) == -1)
						goto DataCleanUp1;
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					if (! HtmlTokenizer.HtmlReverseTok())
						goto DataCleanUp1;
					if (HtmlTokenizer.FindTagAttr("href", sbValue) != 2)
						goto DataCleanUp1;
					m_sbKaiOdrHyjiObject = StrQTrim(sbValue);
					if ((nPtr0 = m_sbHtml.Find("売り注文", HtmlTokenizer.m_nHtmlPtr)) == -1)
						goto DataCleanUp1;
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					if (! HtmlTokenizer.HtmlReverseTok())
						goto DataCleanUp1;
					if (HtmlTokenizer.FindTagAttr("href", sbValue) != 2)
						goto DataCleanUp1;
					m_sbBaiObject = StrQTrim(sbValue);

					m_pServer->Close();
					delete m_pServer;
					m_pServer = NULL;

					if (! AfxParseURL(URL_TRADE0, m_dwServiceType, m_strServerName, m_strObject, m_nPort) || m_dwServiceType != AFX_INET_SERVICE_HTTPS) {
						DispErrorLog("URL 解析エラー: " URL_TRADE0 "\n");
						goto CleanUp;
					}
					m_pServer = m_ppSession[i]->GetHttpConnection(m_strServerName, m_nPort);

					m_strObject = m_sbKaiOdrHyjiObject;
					if (DlHtml(CHttpConnection::HTTP_VERB_GET, INTERNET_FLAG_SECURE))
						goto CleanUp;
					if ((nPtr0 = m_sbHtml.Find("お買付限度額")) == -1)
						goto DataCleanUp1;
					HtmlTokenizer.SetHtml(m_sbHtml);
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					if (! HtmlTokenizer.HtmlTok())
						goto DataCleanUp1;
					sbTag = HtmlTokenizer.m_strTag;
					sbTag.Replace("お買付限度額", pszEmpty);
					sbTag.Replace("&nbsp;", pszEmpty);
					sbTag.Replace(",", pszEmpty);
					sbTag.Replace("円", pszEmpty);
					m_lStartZan = m_lZan = m_lStartVZan = m_lVZan = m_lCashZan = atol(sbTag);
					if ((nPtr0 = StrFindNoCase(m_sbHtml, "<form ", HtmlTokenizer.m_nHtmlPtr)) == -1)
						goto DataCleanUp1;
					HtmlTokenizer.m_nHtmlPtr = nPtr0;
					if (! HtmlTokenizer.HtmlTok())
						goto DataCleanUp1;
					if (HtmlTokenizer.FindTagAttr("action", sbValue) != 2)
						goto DataCleanUp1;
					m_sbKaiOdrSijiObject = StrQTrim(sbValue);
					break;
				default:
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
					m_psbQuickInfoUrl[i] = sbValue;

					m_pServer->Close();
					delete m_pServer;
					m_pServer = NULL;

					if (! AfxParseURL(sbValue, m_dwServiceType, m_strServerName, m_strObject, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
						DispErrorLog("URL 解析エラー: %s\n", sbValue);
						goto CleanUp;
					}

					m_pServer = m_ppSession[i]->GetHttpConnection(m_strServerName, m_nPort);
					m_strObject.Format(OBJ_KABU_KAKAKU, m_strObject, "8628/T");
					if (DlHtml(CHttpConnection::HTTP_VERB_GET))
						goto CleanUp;
					if ((nPtr0 = m_sbHtml.Find("write_kabulink")) == -1)
						goto DataCleanUp1;
					StringTokenizer.SetStrSep(m_sbHtml, "(),");
					StringTokenizer.m_nStrPtr = nPtr0 + 14;
					for (j = 0; j < 11; j ++)
						if (! StringTokenizer.StrTok())
							goto DataCleanUp1;
					m_sbMatsuiQuoteUrl.Format(URL_MATSUIQUOTE "/%s/", StrQTrim(StringTokenizer.m_strTok));
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

			m_ppSessionCosmo = new CInternetSession*[max(min(m_dwMaxConnectionsPerServer, 16), 2)];
			ZeroMemory(m_ppSessionCosmo, sizeof(CInternetSession *) * (max(min(m_dwMaxConnectionsPerServer, 16), 2)));

			for (i = 0, imax = max(min(m_dwMaxConnectionsPerServer, 16), 2); i < imax; i ++) {
				if (m_bMentenance2)
					continue;

				DispLog("%s 初期化ダウンロード - コスモ証券%d\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), i);

				m_ppSessionCosmo[i] = new CInternetSession(_T("Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; Trident/4.0; GTB6.6; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.1; .NET4.0C)"));

				m_ppSessionCosmo[i]->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 10000);
				m_ppSessionCosmo[i]->SetOption(INTERNET_OPTION_CONTROL_SEND_TIMEOUT, 10000);
				m_ppSessionCosmo[i]->SetOption(INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT, 10000);
				m_ppSessionCosmo[i]->SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 10000);
				m_ppSessionCosmo[i]->SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 10000);
				m_ppSessionCosmo[i]->SetOption(INTERNET_OPTION_LISTEN_TIMEOUT, 10000);
				m_ppSessionCosmo[i]->SetOption(INTERNET_OPTION_DISCONNECTED_TIMEOUT, 10000);

				if (! AfxParseURL(m_sbCosmoLoginUrl, m_dwServiceType, m_strServerName, m_strObject, m_nPort) || m_dwServiceType != AFX_INET_SERVICE_HTTPS) {
					DispErrorLog("URL 解析エラー: %s\n", m_sbCosmoLoginUrl);
					goto CleanUp;
				}

				m_pServer = m_ppSessionCosmo[i]->GetHttpConnection(m_strServerName, m_nPort);

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

				m_pServer = m_ppSessionCosmo[i]->GetHttpConnection(m_strServerName, m_nPort);

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
//		if (m_bMentenance0)
//			m_psbQuickInfoUrl[0] = m_psbQuickInfoUrl[1];
	}

//	if (m_bMentenance0  ||  m_nExecMode)
		m_lStartZan = m_lZan = m_lStartVZan = m_lVZan = m_lCashZan = ZAN;

	Disp();

#ifndef GETALLHIASHI
	if (bCreateDB) {
#endif
		DispLog("%s 銘柄日足データダウンロード開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
		if (DlData1())
			goto CleanUp;
		DispLog("%s 銘柄日足データダウンロード終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
#ifndef GETALLHIASHI
	}
#endif

	if (! m_nExecMode)
		DispLog("%s 銘柄分足データ0ダウンロード開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
	if (DlData0(0x5))
		goto CleanUp;
	if (! m_nExecMode) {
		nDayOfWeek = DtCur.GetDayOfWeek();
		nHour = DtCur.GetHour();
		nMinute = DtCur.GetMinute();
//		if (nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour == 8  &&  nMinute >= 58  ||  nHour >= 9  &&  nHour < 11  ||  nHour == 12  &&  nMinute >= 30  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16)) {
		if (nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  (nHour == 8  &&  nMinute >= 58  ||  nHour >= 9  &&  nHour < 11  ||  nHour == 11  &&  nMinute < 30  ||  nHour == 12  &&  nMinute >= 30  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16)) {
			for (i = 0; ; i ++)
				if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_SELCODE + IToA(i), pszEmpty, pszBuf, MAX_PATH, m_strMeigaraIniFPath)) {
					if (! m_MstpSelCode.Lookup(pszBuf, pVoid)) {
						m_SaSelCode.Add(pszBuf);
						m_MstpSelCode[pszBuf] = NULL;
					}
				} else
					break;
		}
		DispLog("%s 銘柄分足データ0ダウンロード終了 セレクト銘柄数: %d\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), m_SaSelCode.GetSize());
	}

	if (bCreateDB)
		if (! CopyFile(m_strDBFPath, m_strRstDBFPath, FALSE))
			DispErrorLog("%s %s コピーエラー: %s\n", m_strDBFPath, m_strRstDBFPath, GetLastErrorMessage());

	nContractYear0 = m_DtDate.GetYear();
	nMonth = m_DtDate.GetMonth();
	nDay = m_DtDate.GetDay();
	nContractMonth0 = nMonth / 3 * 3;
	if (nMonth % 3  ||  nDay >= 14)
		nContractMonth0 += 3;
	else if (nDay >= 8) {
		nDayOfWeek = m_DtDate.GetDayOfWeek();
		nDayOfWeekWork = nDayOfWeek - (nDay - 8);
		if (nDayOfWeekWork <= 6  &&  nDayOfWeek >= 6  ||  nDayOfWeekWork <= -1)
			nContractMonth0 += 3;
	}
	if (nContractMonth0 > 12) {
		nContractYear0 ++;
		nContractMonth0 -= 12;
	}
	nContractYear0 %= 100;
	m_strContractMonth0.Format("%02d%02d", nContractYear0, nContractMonth0);

	if (! m_nExecMode)
		for (i = 0; ; i ++) {
			sbI = IToA(i);
			if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_CODE + sbI, pszX, pszBuf, MAX_PATH, m_strMeigaraIniFPath) == 1)
				break;
			else {
				GetDlgItem(IDC_EDIT20 + i)->SetWindowText(pszBuf);
				SetNiceCode(pszBuf);
			}
			if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_LOCKON + sbI, pszEmpty, pszBuf, MAX_PATH, m_strMeigaraIniFPath)) {
				lNiceLockOn = atol(pszBuf);
				((CButton *)GetDlgItem(IDC_CHECK10 + i))->SetCheck(lNiceLockOn ? 1 : 0);
				m_DwaNiceLockOn[i] = lNiceLockOn;
			}
		}
	else
		for (i = 0; ; i ++)
			if (GetPrivateProfileString(PF_APP_GENERAL, PF_KEY_SELCODE + IToA(i), pszEmpty, pszBuf, MAX_PATH, m_strOrgMeigaraIniFPath)) {
				m_SaSelCode.Add(pszBuf);
				m_MstpSelCode[pszBuf] = NULL;
			} else
				break;

	m_Check1.SetCheck(1);
	if (m_nExecMode) {
		m_Edit18.SetWindowText(m_DtSimStart.Format("%Y/%m/%d %H:%M:%S"));
		GetSimDateTime();
	}

	Disp();

	// CFunashi* (4 + (60 * 4 + 60 + 55 + 15 + 2) * 60 *   4) * 511 =  45624124 ( 43M)
	// CFunashi0      (60 * 4 + 60 + 55 + 15 + 2) * 60 * 112  *  11 =  27498240 ( 27M)
	// CFunashi1      (60 * 4 +      30 + 15 + 2) * 60 *  24  * 500 = 206640000 (197M)
	// CFunashi2      (         60 + 25         ) * 60 *  36  * 500 =  91800000 ( 87M)
	//                                                                           354M
	nSelCodeCount = m_SaSelCode.GetSize();
	nMemMapHCount = 1 + nSelCodeCount + NICECODE_MAXCOUNT;
//	m_nMemMapF0Count = (60 * 4 + 60 + 55 + 15 + 2) * 60 / TIMEUNIT * (1 + NICECODE_MAXCOUNT);
//	m_nMemMapF1Count = (60 * 4 +      30 + 15 + 2) * 60 / TIMEUNIT * nSelCodeCount;
//	m_nMemMapF2Count = (         60 + 25         ) * 60 / TIMEUNIT * nSelCodeCount;
	m_nMemMapF0Count = (60 * 4 + 60 + 30 + 55 + 15 + 2) * 60 / TIMEUNIT * (1 + NICECODE_MAXCOUNT);
	m_nMemMapF1Count = (60 * 4 +      30 + 30 + 15 + 2) * 60 / TIMEUNIT * nSelCodeCount;
	m_nMemMapF2Count = (         60      + 25         ) * 60 / TIMEUNIT * nSelCodeCount;
	dwMemMapInfoSize = GetAllocationSize(sizeof(DWORD) * 2);
	m_dwMemMapAllPaSize = GetAllocationSize(MEMMAPPASIZE * nMemMapHCount);
	m_dwMemMapCellSize =
		GetAllocationSize(
			m_nMemMapF0Count * sizeof(CFunashi0)
			+ m_nMemMapF1Count * sizeof(CFunashi1)
			+ m_nMemMapF2Count * sizeof(CFunashi2)
		);
	m_dwMemMapSize =
		dwMemMapInfoSize
		+ m_dwMemMapAllPaSize
		+ m_dwMemMapCellSize;

	// メモリマップドファイルの生成
	m_hMapping = ::CreateFileMapping(
		(HANDLE)0xffffffff,	// 共有メモリの場合は0xffffffffを指定
		NULL,				// セキュリティ属性。NULLでよい
		PAGE_READWRITE,		// プロテクト属性を読み書き可能に指定
		0,					// ファイルサイズの上位32ビット
		m_dwMemMapSize,		// ファイルサイズの下位32ビット
		StrFormat("Funashi_SharedMemory_%06d", m_nThisVer) + m_strUlCmdLine + m_strUlExeMode);	// メモリマップドファイルの名前
	if (! m_hMapping) {
		DispErrorLog("共有メモリ作成エラー: %s\n", GetLastErrorMessage());
		goto CleanUp;
	}

	// プロセス内のアドレス空間にファイルのビューをマップ
	m_pMappingView = (char *)::MapViewOfFile(m_hMapping, FILE_MAP_ALL_ACCESS, 0, 0, dwMemMapInfoSize);
	if (! m_pMappingView) {
		DispErrorLog("共有メモリマップエラー: %d %s\n", GetLastError(), GetLastErrorMessage());
		goto CleanUp;
	}
	*((DWORD *)m_pMappingView) = m_dwMemMapSize;
	*((DWORD *)m_pMappingView + 1) = m_dwMemMapAllPaSize;
	::UnmapViewOfFile(m_pMappingView);
	m_pMappingView = NULL;

	m_pMappingViewOffset = (char *)::MapViewOfFile(m_hMapping, FILE_MAP_ALL_ACCESS, 0, dwMemMapInfoSize, m_dwMemMapAllPaSize);
	if (! m_pMappingViewOffset) {
		DispErrorLog("オフセット共有メモリマップエラー: %d %s\n", GetLastError(), GetLastErrorMessage());
		goto CleanUp;
	}

	m_pMappingViewCell = (char *)::MapViewOfFile(m_hMapping, FILE_MAP_ALL_ACCESS, 0, dwMemMapInfoSize + m_dwMemMapAllPaSize, 0);
	if (! m_pMappingViewCell) {
		DispErrorLog("セル共有メモリマップエラー: %d %s\n", GetLastError(), GetLastErrorMessage());
		goto CleanUp;
	}

	if (m_nExecMode == 1) {
		m_SaSelCode.RemoveAll();
		m_MstpSelCode.RemoveAll();
	}

	if (m_nExecMode)
		SetMeigara();
	else {
		DispLog("%s 銘柄日足データ分析開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
		if (HiashiAnalyze(m_nExecMode == 1 ? &m_DtSim0 : NULL))
			goto CleanUp;
		for (i = 0, imax = m_SaNiceCode.GetSize(); i < imax; i ++) {
			strCode = m_SaNiceCode[i];
			if (strCode.GetLength()  &&  ! m_MstpHiashiCode.Lookup(strCode, pVoid))
				if (HiashiAnalyze(NULL, strCode, 1))
					goto CleanUp;
		}
		DispLog("%s 銘柄日足データ分析終了 日足銘柄数: %d,  Funashi: %ld/%ld, %ld/%ld, %ld/%ld\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), m_SaHiashiCode.GetSize(), m_lFunashi0Count, m_nMemMapF0Count, m_lFunashi1Count, m_nMemMapF1Count, m_lFunashi2Count, m_nMemMapF2Count);

		SaveSelCode();
		SaveHiashiCode();
	}

#ifdef GETHIASHI
	DispLog("%s 銘柄分足データ1ダウンロード開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
	if (DlData2(1))
		goto CleanUp;
	DispLog("%s 銘柄分足データ1ダウンロード終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
#endif

#ifdef GETCHART
	DispLog("%s 銘柄チャートダウンロード開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
	DlChart();
	DispLog("%s 銘柄チャートダウンロード終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
#endif

#ifdef PRICELIST
	DispLog("%s 株価リスト生成開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
	CreatePriceList();
	DispLog("%s 株価リスト生成終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
#endif

#ifdef NICELIST
	DispLog("%s Nice リスト生成開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
	CreateNiceList();
	DispLog("%s Nice リスト生成終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
#endif

#ifdef COMPACTDB
	DispLog("%s DB の最適化/修復開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
	CompactDB();
	DispLog("%s DB の最適化/修復終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
#endif

	DispLog("%s 起動完了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
	bComplete = TRUE;

CleanUp:
	if (m_pServer) {
		m_pServer->Close();
		delete m_pServer;
	}

	if (bComplete  &&  m_nExecMode != 1) {
		if (m_nExecMode == 2)
			DtsCurrentTime = COleDateTime::GetCurrentTime() - m_DtSimStart;

		SetWMUserTimer((TIMEUNIT - GetCurrentTimeEx().GetSecond() % TIMEUNIT) * 1000, 2, NULL);
		m_bSetTimer2 = TRUE;
	}

	m_bOnInitDialog = FALSE;
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CAutoTraderDlg::OnPaint() 
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
HCURSOR CAutoTraderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

LRESULT CAutoTraderDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
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

void CAutoTraderDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください

	KillWMUserTimer(2);

	SaveLastStatus();

	if (m_nExecMode == 1  &&  m_bTimeSim  &&  m_bDispDebugLog)
		m_SfDump.Close();

//	DispLog("%s DB 移動 %s -> Dataディレクトリ\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), m_strTempCompressDir);
	DispLog("%s DB 移動 %s -> Dataディレクトリ\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), m_strTempDir);
	if (! MoveFile(m_strDBFPath, m_strHomeDBFPath))
		DispErrorLog("%s %s 移動エラー: %s\n", m_strDBFPath, m_strHomeDBFPath, GetLastErrorMessage());

	DispLog("%s Log 移動 %s -> Dataディレクトリ\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), m_strTempDir);
	if (! MoveFile(m_strLogFPath, m_strHomeLogFPath))
		DispErrorLog("%s %s 移動エラー: %s\n", m_strLogFPath, m_strHomeLogFPath, GetLastErrorMessage());

	// ★ファイルのビューをアンマップし、マップのハンドルをクローズ
	if (m_pMappingViewCell)
		::UnmapViewOfFile(m_pMappingViewCell);
	if (m_pMappingViewOffset)
		::UnmapViewOfFile(m_pMappingViewOffset);
	if (m_pMappingView)
		::UnmapViewOfFile(m_pMappingView);
	if (m_hMapping)
		::CloseHandle(m_hMapping);

	int i;
	if (m_ppSessionCosmo) {
		int imax;
		for (i = 0, imax = max(min(m_dwMaxConnectionsPerServer, 16), 2); i < imax; i ++)
			if (m_ppSessionCosmo[i])
				delete m_ppSessionCosmo[i];
		delete [] m_ppSessionCosmo;
	}
	for (i = 0; i < sizeof(m_ppSession) / sizeof(CInternetSession*); i ++)
		if (m_ppSession[i])
			delete m_ppSession[i];
}

void CAutoTraderDlg::OnTimer(UINT nIDEvent) 
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

void CAutoTraderDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
//	CDialog::OnOK();
}

void CAutoTraderDlg::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	KillWMUserTimer(2);
	
	CDialog::OnCancel();
}

void CAutoTraderDlg::OnButton1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	SetWMUserTimer(0, 3, NULL);
}

void CAutoTraderDlg::OnButton2() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if (! CheckLicense()) {
		DispLog("%s 銘柄分足データ1ダウンロード開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
		DlData2(1);
		DispLog("%s 銘柄分足データ1ダウンロード終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
	}
	DispLog("%s 株価リスト生成開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
	CreatePriceList();
	DispLog("%s 株価リスト生成終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
	DispLog("%s DB の最適化/修復開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
	CompactDB();
	DispLog("%s DB の最適化/修復終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
/*
	struct _timeb timebuffer;
	_ftime( &timebuffer );
	COleDateTime DtCur(timebuffer.time);
	DtCur -= DtsCurrentTime;
	int nHour = DtCur.GetHour();
	if (nHour == 11) {
		CFile::GetStatus(m_strDBFPath, m_FileStatus);
		WORD wFlag = GetDiskFreeSpaceInt64(m_strTempCompressDir) - m_FileStatus.m_size < 512000000i64 ? 1 : 0;
		if (wFlag) {
			DispLog("%s DB の圧縮開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
			HANDLE hFile;
			if ((hFile = CreateFile(m_strTempCompressDir, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL)) != INVALID_HANDLE_VALUE) {
				DWORD dwBytesReturned;
				DeviceIoControl(hFile, FSCTL_SET_COMPRESSION, &wFlag, sizeof(WORD), NULL, 0, &dwBytesReturned, NULL);
				CloseHandle(hFile);
			}
			DispLog("%s DB の圧縮終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
		}
	}
*/
}

void CAutoTraderDlg::OnButton3() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if (! CheckLicense()) {
		DispLog("%s 銘柄チャートダウンロード開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
		DlChart();
		DispLog("%s 銘柄チャートダウンロード終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
	}
	struct _timeb timebuffer;
	_ftime( &timebuffer );
	COleDateTime DtCur(timebuffer.time);
	DtCur -= DtsCurrentTime;
	COleDateTime DtDate(DtCur.GetYear(), DtCur.GetMonth(), DtCur.GetDay(), 0, 0, 0);
	if (m_DtAutoTraderUpdateDate < DtDate) {
		if (UpdateAutoTrader0() == 1)
			UpdateAutoTrader1();
		if (m_bQuitReq)
			PostQuitMessage(0);
	}
}

void CAutoTraderDlg::OnButton4() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_Btn4.EnableWindow(FALSE);
	m_Btn5.EnableWindow();
	if (m_nExecMode == 1) {
		int i;
		int j;
		int imax;
		CStringArray SaNiceCodeC;
		CDWordArray DwaNiceLockOn;
		CString strCode;
		CString strName;
		CString strDPath;
		CString strFPath;
		COleDateTime DtSim0C = m_DtSim0;
		COleDateTime Dt;
		COleDateTime DtSim0;
		COleDateTime DtSim1;
		COleDateTimeSpan Dts2Min(0, 0, 2, 0);
		CStringArray SaCode;
		CDWordArray DwaCount;
		COleDateTimeArray DtaSim0;
		COleDateTimeArray DtaSim1;
		CMapStringToPtr MstpCode;
		void* pVoid;
		POSITION pos;
		CDaoDatabase Database;

		SaNiceCodeC.Copy(m_SaNiceCode);
		DwaNiceLockOn.Copy(m_DwaNiceLockOn);

		GetSimDateTime();

		DispLog("%s ダンプ開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));

		try
		{
			COleVariant var;
			COleVariant pKeyArray[2];

			Database.Open(m_strDBFPath, FALSE, TRUE);

			CDaoRecordset RsFunashi(&Database);

			RsFunashi.Open(dbOpenTable, TBL_FUNASHI0);

			m_Edit16.GetWindowText(strCode);
			if (strCode.GetLength())
				SaCode.Add(strCode);
			else {
				DispLog("%s ダンプ銘柄検索開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
				RsFunashi.SetCurrentIndex(pszPrimaryKey);
				pKeyArray[0] = COleVariant(m_DtSim0);
				if (RsFunashi.Seek(">", pKeyArray, 2)) {
					MstpCode["101"] = NULL;
					do {
						RsFunashi.GetFieldValue(0, var);
						if (var.date > m_DtSim1)
							break;

						RsFunashi.GetFieldValue(1, var);
						strCode = V_BSTRT((LPVARIANT)var);
						if (! MstpCode.Lookup(strCode, pVoid)) {
							MstpCode[strCode] = NULL;
							DispLog("%s ダンプ銘柄コード: %s\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), strCode);
						}

						RsFunashi.MoveNext();
					} while (! RsFunashi.IsEOF());

					pos = MstpCode.GetStartPosition();
					while (pos) {
						MstpCode.GetNextAssoc(pos, strCode, pVoid);
						if (strCode != "101")
							SaCode.Add(strCode);
					}
				}
				DispLog("%s ダンプ銘柄検索終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
			}

			DispLog("%s ダンプ開始終了時刻検索開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
			RsFunashi.SetCurrentIndex(pszSecondaryKey);
			for (i = 0, imax = SaCode.GetSize(); i < imax; i ++) {
				strCode = SaCode[i];

				pKeyArray[0] = COleVariant(strCode, VT_BSTRT);
				pKeyArray[1] = COleVariant(m_DtSim0);
				if (RsFunashi.Seek(">=", pKeyArray, 2))
					for (j = 0; ! RsFunashi.IsEOF(); j ++) {
						RsFunashi.GetFieldValue(1, var);
						if (V_BSTRT((LPVARIANT)var) != strCode)
							break;

						RsFunashi.GetFieldValue(0, var);
						Dt = var.date;
						if (Dt > m_DtSim1)
							break;
						DtSim0 = DtSim1 = Dt;

						RsFunashi.MoveNext();

						while (! RsFunashi.IsEOF()) {
							RsFunashi.GetFieldValue(1, var);
							if (V_BSTRT((LPVARIANT)var) != strCode)
								break;

							RsFunashi.GetFieldValue(0, var);
							Dt = var.date;
							if (Dt > m_DtSim1  ||  Dt >= FixDateTime(DtSim1 + Dts2Min))
								break;
							DtSim1 = Dt;

							RsFunashi.MoveNext();
						}

						if (j) {
							i ++;
							imax ++;
							SaCode.InsertAt(i, strCode);
						}
						DwaCount.Add(j);
						DtaSim0.Add(DtSim0);
						DtaSim1.Add(DtSim1);
						DispLog("%s ダンプ開始終了時刻: %s %s %s\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), strCode, DtSim0.Format("%Y/%m/%d %H:%M:%S"), DtSim1.Format("%Y/%m/%d %H:%M:%S"));
					}
			}
			DispLog("%s ダンプ開始終了時刻検索終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
		}
		catch (CException* pEx) {
			DispErrorLog("ダンプエラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();
		}

		for (i = 0, imax = SaCode.GetSize(); i < imax; i ++) {
			if (! m_bLicenseCanceled  &&  ! (m_bLicenseCanceled = CheckLicense())) {
				m_DtSim0 = DtaSim0[i];
				m_DtSim1 = DtaSim1[i];

				if (DwaCount[i] == 0UL) {
					if (i)
						m_SfDump.Close();

					strCode = m_strLogCode = SaCode[i];
					CodeToName(strCode, strName);

					DispLog("%s 銘柄 %s %s\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), strCode, strName);

					m_Edit16.SetWindowText(strCode);

					RemoveAllNiceCode();
					SetNiceCode(strCode);

					DispLog("%s 銘柄日足データ分析開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
					HiashiAnalyze(&m_DtSim0, strCode);
					DispLog("%s 銘柄日足データ分析終了 日足銘柄数: %d,  Funashi: %ld/%ld, %ld/%ld, %ld/%ld\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), m_SaHiashiCode.GetSize(), m_lFunashi0Count, m_nMemMapF0Count, m_lFunashi1Count, m_nMemMapF1Count, m_lFunashi2Count, m_nMemMapF2Count);
			
					strFPath.Format("%s\\Log\\%s %s %s %s.txt", m_strDataDir, COleDateTime::GetCurrentTime().Format("%Y%m%d"), strCode.Left(4), strCode.Mid(5), strName);
					m_SfDump.Open(strFPath, CFile::modeCreate | CFile::modeWrite);
				}

				TimeSim();
				if (m_bSimStop)
					break;
			}
		}
		if (i  ||  m_bSimStop)
			m_SfDump.Close();

		m_Edit16.SetWindowText(pszEmpty);
		m_Edit18.SetWindowText(DtSim0C.Format("%Y/%m/%d %H:%M:%S"));

		DispLog("%s ダンプ終了\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));

		RemoveAllNiceCode();
		for (i = 0, imax = SaNiceCodeC.GetSize(); i < imax; i ++)
			SetNiceCode(SaNiceCodeC[i]);
		m_DwaNiceLockOn.Copy(DwaNiceLockOn);

		m_Btn4.EnableWindow();
		m_Btn5.EnableWindow(FALSE);
	} else
		Start();
}

void CAutoTraderDlg::OnButton5() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if (m_nExecMode == 1)
		m_bSimStop = TRUE;
	else
		End();
}

void CAutoTraderDlg::OnButton6() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	SetWMUserTimer(0, 4, NULL);
}

void CAutoTraderDlg::OnButton7() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CSetupDlg SetupDlg;
	m_pSetupDlg = &SetupDlg;
//	SetupDlg.m_strKazakaId0 = m_strKazakaId0;
//	SetupDlg.m_strKazakaId1 = m_strKazakaId1;
//	SetupDlg.m_strKazakaPasswd = m_strKazakaPasswd;
	SetupDlg.m_strTreasureId = m_strTreasureId;
	SetupDlg.m_strTreasurePasswd = m_strTreasurePasswd;
	SetupDlg.m_strMatsuiId = m_strMatsuiId;
	SetupDlg.m_strMatsuiPasswd = m_strMatsuiPasswd;
	SetupDlg.m_strCosmoId = m_strCosmoId;
	SetupDlg.m_strCosmoPasswd = m_strCosmoPasswd;
	SetupDlg.m_nAutoTraderUpdateType = m_nAutoTraderUpdateType;
	SetupDlg.m_strDir = m_strDir;
	SetupDlg.m_strDefaultDataDir = m_strDefaultDataDir;
	SetupDlg.m_strDataDir = m_strDataDir;
	if (SetupDlg.DoModal() == IDOK) {
//		m_strKazakaId0 = SetupDlg.m_strKazakaId0;
//		m_strKazakaId1 = SetupDlg.m_strKazakaId1;
//		m_strKazakaPasswd = SetupDlg.m_strKazakaPasswd;
		m_strTreasureId = SetupDlg.m_strTreasureId;
		m_strTreasurePasswd = SetupDlg.m_strTreasurePasswd;
		m_strMatsuiId = SetupDlg.m_strMatsuiId;
		m_strMatsuiPasswd = SetupDlg.m_strMatsuiPasswd;
		m_strCosmoId = SetupDlg.m_strCosmoId;
		m_strCosmoPasswd = SetupDlg.m_strCosmoPasswd;
		m_nAutoTraderUpdateType = SetupDlg.m_nAutoTraderUpdateType;
		m_strDir = SetupDlg.m_strDir;
		m_strDataDir = SetupDlg.m_strDataDir;

		SaveLastStatus();
	}
	m_pSetupDlg = NULL;
	if (SetupDlg.m_bAutoTraderUpdated)
		PostQuitMessage(0);
}

void CAutoTraderDlg::OnChangeEdit16() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ChangeEditCode(IDC_EDIT16, IDC_EDIT17);
}

void CAutoTraderDlg::OnChangeEdit20() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ChangeEditCode(IDC_EDIT20, IDC_EDIT30);
}

void CAutoTraderDlg::OnChangeEdit21() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ChangeEditCode(IDC_EDIT21, IDC_EDIT31);
}

void CAutoTraderDlg::OnChangeEdit22() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ChangeEditCode(IDC_EDIT22, IDC_EDIT32);
}

void CAutoTraderDlg::OnChangeEdit23() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ChangeEditCode(IDC_EDIT23, IDC_EDIT33);
}

void CAutoTraderDlg::OnChangeEdit24() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ChangeEditCode(IDC_EDIT24, IDC_EDIT34);
}

void CAutoTraderDlg::OnChangeEdit25() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ChangeEditCode(IDC_EDIT25, IDC_EDIT35);
}

void CAutoTraderDlg::OnChangeEdit26() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ChangeEditCode(IDC_EDIT26, IDC_EDIT36);
}

void CAutoTraderDlg::OnChangeEdit27() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ChangeEditCode(IDC_EDIT27, IDC_EDIT37);
}

void CAutoTraderDlg::OnChangeEdit28() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ChangeEditCode(IDC_EDIT28, IDC_EDIT38);
}

void CAutoTraderDlg::OnChangeEdit29() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ChangeEditCode(IDC_EDIT29, IDC_EDIT39);
}

void CAutoTraderDlg::OnSetfocusEdit16() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_Edit16.SetWindowText(pszEmpty);
}

void CAutoTraderDlg::OnSetfocusEdit20() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CWnd* pWnd = GetFocus();
	CString strCode;
	pWnd->GetWindowText(strCode);
	m_Edit16.SetWindowText(strCode);
	SetWMUserTimer(0, 6, pWnd->GetDlgCtrlID());
}

void CAutoTraderDlg::OnSetfocusEdit21() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnSetfocusEdit20();
}

void CAutoTraderDlg::OnSetfocusEdit22() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnSetfocusEdit20();
}

void CAutoTraderDlg::OnSetfocusEdit23() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnSetfocusEdit20();
}

void CAutoTraderDlg::OnSetfocusEdit24() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnSetfocusEdit20();
}

void CAutoTraderDlg::OnSetfocusEdit25() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnSetfocusEdit20();
}

void CAutoTraderDlg::OnSetfocusEdit26() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnSetfocusEdit20();
}

void CAutoTraderDlg::OnSetfocusEdit27() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnSetfocusEdit20();
}

void CAutoTraderDlg::OnSetfocusEdit28() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnSetfocusEdit20();
}

void CAutoTraderDlg::OnSetfocusEdit29() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnSetfocusEdit20();
}

void CAutoTraderDlg::OnCheck10() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	Check10(0);
}

void CAutoTraderDlg::OnCheck11() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	Check10(1);
}

void CAutoTraderDlg::OnCheck12() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	Check10(2);
}

void CAutoTraderDlg::OnCheck13() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	Check10(3);
}

void CAutoTraderDlg::OnCheck14() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	Check10(4);
}

void CAutoTraderDlg::OnCheck15() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	Check10(5);
}

void CAutoTraderDlg::OnCheck16() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	Check10(6);
}

void CAutoTraderDlg::OnCheck17() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	Check10(7);
}

void CAutoTraderDlg::OnCheck18() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	Check10(8);
}

void CAutoTraderDlg::OnCheck19() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	Check10(9);
}

LRESULT CAutoTraderDlg::OnUser(WPARAM wParam, LPARAM lParam)
{
	if (! PreUser(wParam, lParam))
		return 0;
	nPumpWaitingMessages ++;
	switch (wParam) {
/*
	case 1:
		DestroyWindow();
		break;
*/
	case 2:
		{
			m_bDispLog = m_Check1.GetCheck() == 1;
			struct _timeb timebuffer;
			_ftime( &timebuffer );
			COleDateTime DtCur(timebuffer.time);
			DtCur -= DtsCurrentTime;
			int nDayOfWeek = DtCur.GetDayOfWeek();
			int nHour = DtCur.GetHour();
			int nMinute = DtCur.GetMinute();
			int nSecond = DtCur.GetSecond();
			int nMilliSecond = DtCur.GetSecond() * 1000 + timebuffer.millitm;
			int nMilliSecond0 = nMilliSecond / (TIMEUNIT * 1000) * (TIMEUNIT * 1000);
			int nElapseOffset = 0;
			if (nDayOfWeek >= 2  &&  nDayOfWeek <= 6)
//				if (nHour >= 8  &&  nHour < 11  ||  nHour == 11  &&  nMinute < 1  ||  nHour == 12  &&  nMinute >= 5  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16) {
				if (nHour >= 8  &&  nHour < 11  ||  nHour == 11  &&  nMinute < 31  ||  nHour == 12  &&  nMinute >= 5  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 16) {
					static int nPreMinute = 0;
					if (! m_bLicenseCanceled  &&  (nMinute % 5  ||  nMinute == nPreMinute  ||  (nPreMinute = nMinute, ! (m_bLicenseCanceled = CheckLicense())))) {
						_ftime( &timebuffer );
						DispLog("%s.%03d 銘柄分足データ0ダウンロード開始 ターゲット銘柄数: %d / %d\n", COleDateTime(timebuffer.time).Format("%H:%M:%S"), timebuffer.millitm, m_SaSelCode.GetSize(), m_SaHiashiCode.GetSize());
						if (m_nExecMode == 2)
							DlData3(0);
						else
							DlData2(0);
						_ftime( &timebuffer );
						DispLog("%s.%03d 銘柄分足データ0ダウンロード終了 Funashi: %ld/%ld, %ld/%ld, %ld/%ld\n", COleDateTime(timebuffer.time).Format("%H:%M:%S"), timebuffer.millitm, m_lFunashi0Count, m_nMemMapF0Count, m_lFunashi1Count, m_nMemMapF1Count, m_lFunashi2Count, m_nMemMapF2Count);
						if (m_nExecMode != 2)
							GetStockAve0();
						CWnd* pWnd;
						WPARAM wParam = m_nExecMode == 2 ? DtsCurrentTime.GetDays() : 0;
						LPARAM lParam = m_nExecMode == 2 ? DtsCurrentTime.GetHours() * 60 * 60 + DtsCurrentTime.GetMinutes() * 60 + DtsCurrentTime.GetSeconds() : 0;
						if (pWnd = FindWindow(NULL, m_strChartViewerWndName))
							pWnd->PostMessage(WM_USER + 1, wParam, lParam);
						if (pWnd = FindWindow(NULL, m_strKehaiViewerWndName))
							pWnd->PostMessage(WM_USER + 1, wParam, lParam);
						if (pWnd = FindWindow(NULL, m_strTradeHelperWndName))
							pWnd->PostMessage(WM_USER + 7, wParam, lParam);
						if (m_bTrade) {
							FunashiAnalyze(0);
							if (m_nExecMode == 2)
								GetState();
							SellJudge();
//							if (m_bSimStop)
//								SellAll();
							Sell();
							if (! m_bSimStop) {
//								if (! (nHour < 9  ||  nHour == 12  &&  nMinute >= 5  &&  nMinute < 30  ||  nHour == 9  &&  nMinute == 0  &&  nSecond < TIMEUNIT * PATERN_PRICE_COUNT  ||  nHour == 12  &&  nMinute == 30  &&  nSecond < TIMEUNIT * PATERN_PRICE_COUNT  ||  nHour == BUY_END_HOUR  &&  nMinute >= BUY_END_MINUTE)) {
//								if (! (nHour < 9  ||  nHour == 12  &&  nMinute >= 5  &&  nMinute < 30  ||  nHour == 9  &&  nMinute == 0  &&  nSecond < TIMEUNIT * FUNASHI_LONG_COUNT  ||  nHour == 12  &&  nMinute == 30  &&  nSecond < TIMEUNIT * FUNASHI_LONG_COUNT  ||  nHour == BUY_END_HOUR  &&  nMinute >= BUY_END_MINUTE)) {
								if (! (nHour < 9  ||  nHour == 12  &&  nMinute >= 5  &&  nMinute < 30  ||  nHour == BUY_END_HOUR  &&  nMinute >= BUY_END_MINUTE)) {
									BuyJudge();
									Buy();
								}
							}
//							if (nHour == 14  &&  nMinute == 59  ||  m_lVZan - m_lStartVZan < - m_lStartVZan / LOSS_STOP)
//							if (nHour == 15  &&  nMinute == 14  ||  m_lVZan - m_lStartVZan < - m_lStartVZan / LOSS_STOP)
//								m_bSimStop = TRUE;
						}
						Disp();
						if (nHour == 8  &&  nMinute == 58  &&  nSecond <= 5) {
							OnButton1();
							nElapseOffset = 1000;
						}
					}
//				} else if ((nHour == 11  &&  nMinute == 1  ||  nHour == 15  &&  nMinute == 31)  &&  nSecond <= 5)
				} else if ((nHour == 11  &&  nMinute == 31  ||  nHour == 15  &&  nMinute == 31)  &&  nSecond <= 5)
					OnButton2();
				else if (nHour == 17  &&  nMinute == 0  &&  nSecond <= 5)
					OnButton3();
			_ftime( &timebuffer );
			DtCur = timebuffer.time;
			DtCur -= DtsCurrentTime;
			nSecond = DtCur.GetSecond();
			nMilliSecond = nSecond * 1000 + timebuffer.millitm;
			int nMilliSecond1 = nMilliSecond / (TIMEUNIT * 1000) * (TIMEUNIT * 1000);
			SetWMUserTimer((DtCur.GetMinute() == nMinute  &&  nMilliSecond1 == nMilliSecond0  ? (TIMEUNIT * 1000) - nMilliSecond % (TIMEUNIT * 1000) : 0) + nElapseOffset, wParam, NULL);
			m_bSetTimer2 = FALSE;
		}
		break;
	case 3:
		if (! CheckLicense()) {
			DispLog("%s 銘柄分足データ0ダウンロード開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
			DlData0(0);
			DispLog("%s 銘柄分足データ0ダウンロード終了 セレクト銘柄数: %d\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), m_SaSelCode.GetSize());
			CWnd* pWnd;
			if (pWnd = FindWindow(NULL, m_strTradeHelperWndName))
				pWnd->PostMessage(WM_USER + 6);
			if (pWnd = FindWindow(NULL, m_strChartViewerWndName))
				pWnd->PostMessage(WM_USER + 8);
			if (pWnd = FindWindow(NULL, m_strKehaiViewerWndName))
				pWnd->PostMessage(WM_USER + 8);
		}
		break;
	case 4:
		SetMeigara();
		break;
	default:
		((CEdit *)GetDlgItem(lParam))->SetSel(0, -1);
	}
	nPumpWaitingMessages --;
	return 0;
}

LRESULT CAutoTraderDlg::OnUser1(WPARAM wParam, LPARAM lParam)
{
	int i;
	int imax;

	for (i = 0, imax = m_SaNiceCode.GetSize(); i < imax; i ++)
		if (atoi(m_SaNiceCode[i].Left(4)) == (int)wParam) {
			((CButton *)GetDlgItem(IDC_CHECK10 + i))->SetCheck(lParam);
			Check10(i);
			break;
		}

	return 0;
}

LRESULT CAutoTraderDlg::OnUser2(WPARAM wParam, LPARAM lParam)
{
	int i;
	int j;
	int k;
	int imax;
	int nReceiptNo = -1;
	CKehai0 KehaiWork;
	long lKehaiSellPrice;
	long lKehaiBuyPrice;
	long lSoldPrice = lParam;
	short sUnit;
	long lUnitCount = 1L;

	long l0;

	CString strCode;

	for (i = 0, imax = m_UiaKabuHiashiIndex.GetSize(); i < imax; i ++) {
		j = m_UiaKabuHiashiIndex[i];
		if (atoi(m_SaHiashiCode[j].Left(4)) == (int)wParam) {
			lUnitCount = m_DwaKabuUnitCount[i];

			strCode = m_SaHiashiCode[j];
			sUnit = m_WaHiashiUnit[j];
			k = m_UiaFunashiPaIndex[j];

			KehaiWork = GetFunashi(j, k).m_Kehai;
			lKehaiSellPrice = KehaiWork.m_plKehaiPrice[4];
			lKehaiBuyPrice = KehaiWork.m_plKehaiPrice[5];

			if (lSoldPrice != (long)m_DwaKabuBuyPrice0[i]) {
				l0 = (m_DwaKabuBuyPrice0[i] - lSoldPrice) * sUnit * lUnitCount;
				m_lCashZan += l0;
				m_DwaHiashiBuyTotalPrice[j] -= l0;
				m_DwaKabuBuyPrice0[i] = lSoldPrice;
				m_DwaKabuBuyPrice1[i] = lKehaiSellPrice  &&  lKehaiBuyPrice  &&  lKehaiSellPrice == lSoldPrice ? lKehaiBuyPrice : lSoldPrice - GetDiff(lSoldPrice);
			}

			DispLog(
				"%s %ld 買済 %d %s %s %ld円 単%d x%d 変%ld円\n",
				GetCurrentTimeEx().Format("%H:%M:%S"),
				m_lVZan, nReceiptNo, strCode, m_SaHiashiName[j], lSoldPrice, sUnit, lUnitCount, m_DwaKabuDiff[i]
			);

			m_UiaKabuState[i] = 2;

			break;
		}
	}

	return 0;
}

LRESULT CAutoTraderDlg::OnUser3(WPARAM wParam, LPARAM lParam)
{
	int i;
	int j;
	int k;
	int imax;
	int nReceiptNo = -1;
	CKehai0 KehaiWork;
	long lKehaiSellPrice;
	long lKehaiBuyPrice;
	long lBuyPrice;
	long lSoldPrice = lParam;
	short sUnit;
	long lUnitCount = 1L;
	long lSetPrice;
	long lProfit;

//	int m;
//	int mmax;

	CString strCode;

	for (i = 0, imax = m_UiaKabuHiashiIndex.GetSize(); i < imax; i ++) {
		j = m_UiaKabuHiashiIndex[i];
		if (atoi(m_SaHiashiCode[j].Left(4)) == (int)wParam) {
			lBuyPrice = m_DwaKabuBuyPrice0[i];
			lUnitCount = m_DwaKabuUnitCount[i];

			strCode = m_SaHiashiCode[j];
			sUnit = m_WaHiashiUnit[j];
			k = m_UiaFunashiPaIndex[j];

			KehaiWork = GetFunashi(j, k).m_Kehai;
			lKehaiSellPrice = KehaiWork.m_plKehaiPrice[4];
			lKehaiBuyPrice = KehaiWork.m_plKehaiPrice[5];

			lSetPrice = lSoldPrice * sUnit * lUnitCount;
			lProfit = (lSoldPrice - lBuyPrice) * sUnit * lUnitCount;
			m_lZan += lProfit;
			m_lCashZan += lSetPrice;
			m_DwaHiashiBuyUnitCount[j] -= lUnitCount;
			if (lProfit > 0) {
				m_lKabuSellPlusCount ++;
				m_lKabuSellPlus += lProfit;
			} else if (lProfit == 0)
				m_lKabuSellZeroCount ++;
			else {
				m_lKabuSellMinusCount ++;
				m_lKabuSellMinus += - lProfit;
			}

			DispLog(
				"%s %ld 売済 %d %s %s %ld円 単%d x%d 変%ld円 利%ld円\n",
				GetCurrentTimeEx().Format("%H:%M:%S"),
				m_lVZan, nReceiptNo, strCode, m_SaHiashiName[j], lSoldPrice, sUnit, lUnitCount, m_DwaKabuDiff[i], lProfit
			);

			m_UiaKabuHiashiIndex.RemoveAt(i);
			m_UiaKabuReceiptNo.RemoveAt(i);
			m_UiaKabuState.RemoveAt(i);
			m_UiaKabuStateMinutes.RemoveAt(i);
			m_UiaKabuTseiKaisu.RemoveAt(i);
			m_DtaKabuFunashiPaDateTime.RemoveAt(i);
			m_DwaKabuBuyPrice0.RemoveAt(i);
			m_DwaKabuBuyPrice1.RemoveAt(i);
			m_DwaKabuSellPrice.RemoveAt(i);
			m_DwaKabuHighPrice.RemoveAt(i);
			m_DwaKabuLowPrice.RemoveAt(i);
			m_DwaKabuUnitCount.RemoveAt(i);
			m_DwaKabuDiff.RemoveAt(i);
			m_UiaKabuUp.RemoveAt(i);
			m_UiaKabuDown.RemoveAt(i);
			m_UiaKabuSell.RemoveAt(i);

/*
			for (m = 0, mmax = m_SaNiceCode.GetSize(); m < mmax; m ++)
				if (m_SaNiceCode[m] == strCode) {
					((CButton *)GetDlgItem(IDC_CHECK10 + m))->SetCheck(0);
					Check10(m);
					break;
				}
*/

			break;
		}
	}

	return 0;
}

LRESULT CAutoTraderDlg::OnUser4(WPARAM wParam, LPARAM lParam)
{
	if (! PreUser(wParam, lParam, OnUser4))
		return 0;
	nPumpWaitingMessages ++;

	int nIndex = wParam - 1;
	CString strToCode;
	CString strName;

	((CButton *)GetDlgItem(IDC_CHECK10 + nIndex))->SetCheck(0);
	if (lParam)
		strToCode = IToA(lParam);
	GetDlgItem(IDC_EDIT20 + nIndex)->SetWindowText(strToCode);
	if (lParam)
		CodeToName(strToCode, strName);
	SetMeigara(nIndex, lParam ? (LPCTSTR)strToCode : NULL);

	CWnd* pWnd;
	if ((pWnd = FindWindow(NULL, m_strTradeHelperWndName)))
		pWnd->PostMessage(WM_USER + 1, 0, nIndex + 1);

	nPumpWaitingMessages --;

	return 0;
}

LRESULT CAutoTraderDlg::OnUser5(WPARAM wParam, LPARAM lParam)
{
	SetWMUserTimer(0, 4, NULL);

	return 0;
}

BOOL CAutoTraderDlg::PreUser(WPARAM wParam, LPARAM lParam, USERPROC lpUserFunc)
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

BOOL CAutoTraderDlg::SetWMUserParam(UINT nIDEvent, WPARAM wParam, LPARAM lParam, USERPROC lpUserFunc)
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

void CAutoTraderDlg::SetWMUserTimer(UINT nElapse, WPARAM wParam, LPARAM lParam, USERPROC lpUserFunc)
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

void CAutoTraderDlg::KillWMUserTimer(WPARAM wParam)
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

int CAutoTraderDlg::CreateDB(CDaoDatabase& Database)
{
	int i;

	CDaoTableDef TableDef(&Database);
	CDaoIndexInfo IndexInfo;
	CDaoIndexFieldInfo pIndexFieldInfo[2];

	for (i = 0; i < 2; i ++)
		pIndexFieldInfo[i].m_bDescending = FALSE;

	IndexInfo.m_pFieldInfos = pIndexFieldInfo;
	IndexInfo.m_bClustered = FALSE;
	IndexInfo.m_bIgnoreNulls = FALSE;
	IndexInfo.m_bRequired = TRUE;
	IndexInfo.m_bForeign = FALSE;

	try {
		Database.Create(m_nExecMode == 1 ? m_strTempDBFPath : m_strDBFPath);

		TableDef.Create(TBL_INFO);
		TableDef.CreateField(FLD_IN_CODE, dbText, 255, dbVariableField | dbUpdatableField);
		TableDef.CreateField(FLD_IN_NAME, dbText, 255, dbVariableField | dbUpdatableField);
		TableDef.CreateField(FLD_IN_SIJO, dbText, 255, dbVariableField | dbUpdatableField);
		TableDef.CreateField(FLD_IN_TYPE, dbText, 255, dbVariableField | dbUpdatableField);
		TableDef.CreateField(FLD_IN_UNIT, dbInteger, 0, dbFixedField | dbUpdatableField);

		pIndexFieldInfo[0].m_strName = FLD_IN_CODE;
		IndexInfo.m_nFields = 1;
		IndexInfo.m_strName = pszPrimaryKey;
		IndexInfo.m_bPrimary = TRUE;
		IndexInfo.m_bUnique = TRUE;
		TableDef.CreateIndex(IndexInfo);

		TableDef.Append();
		TableDef.Close();

		TableDef.Create(TBL_HIASHI);
		TableDef.CreateField(FLD_HI_DATE, dbDate, 0, dbFixedField | dbUpdatableField);
		TableDef.CreateField(FLD_HI_CODE, dbText, 255, dbVariableField | dbUpdatableField);
		TableDef.CreateField(FLD_HI_STARTPRICE, dbLong, 0, dbFixedField | dbUpdatableField);
		TableDef.CreateField(FLD_HI_HIGHPRICE, dbLong, 0, dbFixedField | dbUpdatableField);
		TableDef.CreateField(FLD_HI_LOWPRICE, dbLong, 0, dbFixedField | dbUpdatableField);
		TableDef.CreateField(FLD_HI_PRICE, dbLong, 0, dbFixedField | dbUpdatableField);
		TableDef.CreateField(FLD_HI_TRADECOUNT, dbLong, 0, dbFixedField | dbUpdatableField);

		pIndexFieldInfo[0].m_strName = FLD_HI_DATE;
		pIndexFieldInfo[1].m_strName = FLD_HI_CODE;
		IndexInfo.m_nFields = 2;
		IndexInfo.m_strName = pszPrimaryKey;
		IndexInfo.m_bPrimary = TRUE;
		IndexInfo.m_bUnique = TRUE;
		TableDef.CreateIndex(IndexInfo);

		pIndexFieldInfo[0].m_strName = FLD_HI_CODE;
		pIndexFieldInfo[1].m_strName = FLD_HI_DATE;
		IndexInfo.m_strName = pszSecondaryKey;
		IndexInfo.m_bPrimary = FALSE;
		TableDef.CreateIndex(IndexInfo);

		pIndexFieldInfo[0].m_strName = FLD_HI_CODE;
		IndexInfo.m_nFields = 1;
		IndexInfo.m_strName = FLD_HI_CODE;
		IndexInfo.m_bUnique = FALSE;
		TableDef.CreateIndex(IndexInfo);

		TableDef.Append();
		TableDef.Close();

		TableDef.Create(TBL_FUNASHI0);
		TableDef.CreateField(FLD_FU_DATETIME, dbDate, 0, dbFixedField | dbUpdatableField);
		TableDef.CreateField(FLD_FU_CODE, dbText, 255, dbVariableField | dbUpdatableField);
		TableDef.CreateField(FLD_FU_PRICE, dbLong, 0, dbFixedField | dbUpdatableField);
		TableDef.CreateField(FLD_FU_TRADECOUNT, dbLong, 0, dbFixedField | dbUpdatableField);
		TableDef.CreateField(FLD_FU_VWAP, dbDouble, 0, dbFixedField | dbUpdatableField);
		for (i = 0; i < 10; i ++)
			TableDef.CreateField(FLD_FU_KEHAIPRICE + IToA(i), dbLong, 0, dbFixedField | dbUpdatableField);
		for (i = 0; i < 10; i ++)
			TableDef.CreateField(FLD_FU_KEHAICOUNT + IToA(i), dbLong, 0, dbFixedField | dbUpdatableField);

		pIndexFieldInfo[0].m_strName = FLD_FU_DATETIME;
		pIndexFieldInfo[1].m_strName = FLD_FU_CODE;
		IndexInfo.m_nFields = 2;
		IndexInfo.m_strName = pszPrimaryKey;
		IndexInfo.m_bPrimary = TRUE;
		IndexInfo.m_bUnique = TRUE;
		TableDef.CreateIndex(IndexInfo);

		pIndexFieldInfo[0].m_strName = FLD_FU_CODE;
		pIndexFieldInfo[1].m_strName = FLD_FU_DATETIME;
		IndexInfo.m_strName = pszSecondaryKey;
		IndexInfo.m_bPrimary = FALSE;
		TableDef.CreateIndex(IndexInfo);

		TableDef.Append();
		TableDef.Close();

		TableDef.Create(TBL_FUNASHI1);
		TableDef.CreateField(FLD_FU_DATETIME, dbDate, 0, dbFixedField | dbUpdatableField);
		TableDef.CreateField(FLD_FU_CODE, dbText, 255, dbVariableField | dbUpdatableField);
		TableDef.CreateField(FLD_FU_PRICE, dbLong, 0, dbFixedField | dbUpdatableField);
		TableDef.CreateField(FLD_FU_TRADECOUNT, dbLong, 0, dbFixedField | dbUpdatableField);

		pIndexFieldInfo[0].m_strName = FLD_FU_DATETIME;
		pIndexFieldInfo[1].m_strName = FLD_FU_CODE;
		IndexInfo.m_nFields = 2;
		IndexInfo.m_strName = pszPrimaryKey;
		IndexInfo.m_bPrimary = TRUE;
		IndexInfo.m_bUnique = TRUE;
		TableDef.CreateIndex(IndexInfo);

		pIndexFieldInfo[0].m_strName = FLD_FU_CODE;
		pIndexFieldInfo[1].m_strName = FLD_FU_DATETIME;
		IndexInfo.m_strName = pszSecondaryKey;
		IndexInfo.m_bPrimary = FALSE;
		TableDef.CreateIndex(IndexInfo);

		TableDef.Append();
		TableDef.Close();

		TableDef.Create(TBL_FUNASHI2);
		TableDef.CreateField(FLD_FU_DATETIME, dbDate, 0, dbFixedField | dbUpdatableField);
		TableDef.CreateField(FLD_FU_CODE, dbText, 255, dbVariableField | dbUpdatableField);
		TableDef.CreateField(FLD_FU_PRICE, dbLong, 0, dbFixedField | dbUpdatableField);
		for (i = 0; i < 2; i ++)
			TableDef.CreateField(FLD_FU_KEHAIPRICE + IToA(i), dbLong, 0, dbFixedField | dbUpdatableField);
		for (i = 0; i < 2; i ++)
			TableDef.CreateField(FLD_FU_KEHAICOUNT + IToA(i), dbLong, 0, dbFixedField | dbUpdatableField);

		pIndexFieldInfo[0].m_strName = FLD_FU_DATETIME;
		pIndexFieldInfo[1].m_strName = FLD_FU_CODE;
		IndexInfo.m_nFields = 2;
		IndexInfo.m_strName = pszPrimaryKey;
		IndexInfo.m_bPrimary = TRUE;
		IndexInfo.m_bUnique = TRUE;
		TableDef.CreateIndex(IndexInfo);

		pIndexFieldInfo[0].m_strName = FLD_FU_CODE;
		pIndexFieldInfo[1].m_strName = FLD_FU_DATETIME;
		IndexInfo.m_strName = pszSecondaryKey;
		IndexInfo.m_bPrimary = FALSE;
		TableDef.CreateIndex(IndexInfo);

		TableDef.Append();
		TableDef.Close();

		TableDef.Create(TBL_FUNASHIDATETIME);
		TableDef.CreateField(FLD_FD_DATETIME, dbDate, 0, dbFixedField | dbUpdatableField);

		pIndexFieldInfo[0].m_strName = FLD_FD_DATETIME;
		IndexInfo.m_nFields = 1;
		IndexInfo.m_strName = pszPrimaryKey;
		IndexInfo.m_bPrimary = TRUE;
		IndexInfo.m_bUnique = TRUE;
		TableDef.CreateIndex(IndexInfo);

		TableDef.Append();
		TableDef.Close();
	}
	catch (CException* pEx) {
		DispErrorLog("データベース生成エラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
		return -1;
	}

	return 0;
}

int CAutoTraderDlg::DlHtml(int nVerb, DWORD dwFlags, LPCTSTR lpszHeaders, LPCTSTR lpszOptional)
{
	int nRv = -1;

	int i;
	BOOL bReload = FALSE;
	DWORD dwStatusCode;
	char sz[DL_BUFLEN + 1];
	int nRdLen;
	CStringBuffer sbHtml;

	srand( (unsigned)time( NULL ) );
	sbHtml = IToA(rand());

	m_pFile = NULL;
	m_dwErr = 0;

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
			m_dwErr = pEx->m_dwError;
			DispErrorLog("ダウンロードエラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();

			if (
				m_dwErr == ERROR_INTERNET_TIMEOUT
				||  m_dwErr == ERROR_INTERNET_NAME_NOT_RESOLVED
				||  m_dwErr == ERROR_INTERNET_CANNOT_CONNECT
//				||  m_dwErr == ERROR_INTERNET_CONNECTION_RESET
				||  m_dwErr == ERROR_HTTP_INVALID_SERVER_RESPONSE
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

int CAutoTraderDlg::DlFile(const CString& strFPath, int nVerb, DWORD dwFlags, LPCTSTR lpszHeaders, LPCTSTR lpszOptional)
{
	int nRv = -1;

	BOOL bReload = FALSE;
	DWORD dwStatusCode;
	char sz[DL_BUFLEN + 1];
	int nRdLen;
	int nErrCount = 0;
	CFile* pF = NULL;
	_TCHAR pszTempDPath[MAX_PATH];
	_TCHAR pszTempFPath[MAX_PATH];

	m_pFile = NULL;
	m_dwErr = 0;

	while (1) {
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
				goto CleanUp;
			}

			if (dwStatusCode != HTTP_STATUS_OK) {
				DispErrorLog("HttpStatus Error: %s\n", GetHttpStatusText(dwStatusCode));

				switch (dwStatusCode) {
				case HTTP_STATUS_FORBIDDEN:
				case HTTP_STATUS_SERVER_ERROR:
				case HTTP_STATUS_BAD_GATEWAY:
					if (nErrCount ++ < 80) {
						Sleep(250);
						bReload = TRUE;
						continue;
					}
				}

				goto CleanUp;
			}

			*pszTempFPath = _T('\0');
			while (nRdLen = m_pFile->Read(sz, DL_BUFLEN)) {
				if (pF == NULL)
					if (nRdLen < DL_BUFLEN)
						pF = new CFile(strFPath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
					else {
						if (GetTempPath(MAX_PATH, pszTempDPath) == 0) {
							DispErrorLog("ダウンロードエラー: %s\n", GetLastErrorMessage());
							goto CleanUp;
						}
						if (GetTempFileName(pszTempDPath, _T("atb"), 0, pszTempFPath) == 0) {
							DispErrorLog("ダウンロードエラー: %s\n", GetLastErrorMessage());
							goto CleanUp;
						}
						pF = new CFile(pszTempFPath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
					}
				pF->Write(sz, nRdLen);
			}
			if (nRv == -2)
				goto CleanUp;

			pF->Close();
			delete pF;
			pF = NULL;

			if (*pszTempFPath != _T('\0')) {
				CFileStatus FileStatus;
				if (CFile::GetStatus(strFPath, FileStatus))
					if (! DeleteFile(strFPath)) {
						DispErrorLog("ダウンロードエラー: %s\n", GetLastErrorMessage());
						goto CleanUp;
					}
				if (! MoveFile(pszTempFPath, strFPath)) {
					DispErrorLog("ダウンロードエラー: %s\n", GetLastErrorMessage());
					goto CleanUp;
				}
			}
		}
		catch (CInternetException* pEx) {
			m_dwErr = pEx->m_dwError;
			DispErrorLog("ダウンロードエラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();

			if (
				m_dwErr == ERROR_INTERNET_TIMEOUT
				||  m_dwErr == ERROR_INTERNET_NAME_NOT_RESOLVED
				||  m_dwErr == ERROR_INTERNET_CANNOT_CONNECT
//				||  m_dwErr == ERROR_INTERNET_CONNECTION_RESET
				||  m_dwErr == ERROR_HTTP_INVALID_SERVER_RESPONSE
			) {
				if (nErrCount ++ < 80) {
					Sleep(250);
					bReload = TRUE;
					continue;
				}
			}

			goto CleanUp;
		}
		catch (CException* pEx) {
			DispErrorLog("ダウンロードエラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();
			goto CleanUp;
		}

		break;
	}

	nRv = 0;

CleanUp:
	if (pF) {
		pF->Close();
		delete pF;
	}
	if (m_pFile) {
		m_pFile->Close();
		delete m_pFile;
	}

	return nRv;
}

DWORD CAutoTraderDlg::GetMaxConnectionsPerServer()
{
	DWORD dwMaxConnectionsPerServer = 2;
	DWORD cbMaxConnectionsPerServer = sizeof(dwMaxConnectionsPerServer);
	HKEY hKey;
	LONG nRegFunc;
	DWORD cbVersion;
	_TCHAR* pchVersion;
	int nVersion;
	if ((nRegFunc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Internet Explorer"), 0, KEY_ALL_ACCESS, &hKey)) != ERROR_SUCCESS) {
		DispErrorLog(_T("RegOpenKeyEx Error: %s\n"), GetLastErrorMessage(nRegFunc));
		goto CleanUp;
	}
	if ((nRegFunc = RegQueryValueEx(hKey, _T("Version"), NULL, NULL, NULL, &cbVersion)) != ERROR_SUCCESS) {
		DispErrorLog(_T("RegOpenKeyEx Error: %s\n"), GetLastErrorMessage(nRegFunc));
		goto CleanUp;
	}
	pchVersion = new _TCHAR[cbVersion];
	if ((nRegFunc = RegQueryValueEx(hKey, _T("Version"), NULL, NULL, (LPBYTE)pchVersion, &cbVersion)) != ERROR_SUCCESS) {
		DispErrorLog(_T("RegQueryValueEx Error: %s\n"), GetLastErrorMessage(nRegFunc));
		goto CleanUp;
		delete [] pchVersion;
	}
	nVersion = _ttoi(pchVersion);
	delete [] pchVersion;
	if (nVersion >= 8) {
		if (
			(
				nRegFunc =
					RegOpenKeyEx(
						HKEY_LOCAL_MACHINE,
						_T("Software\\Wow6432Node\\Policies\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_MAXCONNECTIONSPERSERVER"),
						0,
						KEY_ALL_ACCESS,
						&hKey
					)
			) == ERROR_SUCCESS
			|| (
				nRegFunc =
					RegOpenKeyEx(
						HKEY_LOCAL_MACHINE,
						_T("Software\\Wow6432Node\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_MAXCONNECTIONSPERSERVER"),
						0,
						KEY_ALL_ACCESS,
						&hKey
					)
			) == ERROR_SUCCESS
			|| (
				nRegFunc =
					RegOpenKeyEx(
						HKEY_CURRENT_USER,
						_T("Software\\Wow6432Node\\Policies\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_MAXCONNECTIONSPERSERVER"),
						0,
						KEY_ALL_ACCESS,
						&hKey
					)
			) == ERROR_SUCCESS
			|| (
				nRegFunc =
					RegOpenKeyEx(
						HKEY_CURRENT_USER,
						_T("Software\\Wow6432Node\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_MAXCONNECTIONSPERSERVER"),
						0,
						KEY_ALL_ACCESS,
						&hKey
					)
			) == ERROR_SUCCESS
			|| (
				nRegFunc =
					RegOpenKeyEx(
						HKEY_LOCAL_MACHINE,
						_T("Software\\Policies\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_MAXCONNECTIONSPERSERVER"),
						0,
						KEY_ALL_ACCESS,
						&hKey
					)
			) == ERROR_SUCCESS
			|| (
				nRegFunc =
					RegOpenKeyEx(
						HKEY_LOCAL_MACHINE,
						_T("Software\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_MAXCONNECTIONSPERSERVER"),
						0,
						KEY_ALL_ACCESS,
						&hKey
					)
			) == ERROR_SUCCESS
			|| (
				nRegFunc =
					RegOpenKeyEx(
						HKEY_CURRENT_USER,
						_T("Software\\Policies\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_MAXCONNECTIONSPERSERVER"),
						0,
						KEY_ALL_ACCESS,
						&hKey
					)
			) == ERROR_SUCCESS
			|| (
				nRegFunc =
					RegOpenKeyEx(
						HKEY_CURRENT_USER,
						_T("Software\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_MAXCONNECTIONSPERSERVER"),
						0,
						KEY_ALL_ACCESS,
						&hKey
					)
			) == ERROR_SUCCESS
		) {
			DWORD cbMaxConnectionsPerServer = sizeof(dwMaxConnectionsPerServer);
			if (
				RegQueryValueEx(
					hKey,
					_T("AutoTrader.exe"),
					NULL,
					NULL,
					(LPBYTE)&dwMaxConnectionsPerServer,
					&cbMaxConnectionsPerServer
				) != ERROR_SUCCESS
			)
				dwMaxConnectionsPerServer = 6;
			RegCloseKey(hKey);
		} else
			dwMaxConnectionsPerServer = 6;
	} else {
		if (
			(
				nRegFunc = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings", 0, KEY_ALL_ACCESS, &hKey)
			) != ERROR_SUCCESS
		) {
			DispErrorLog("RegOpenKeyEx Error: %s\n", GetLastErrorMessage(nRegFunc));
			goto CleanUp;
		}
		RegQueryValueEx(
			hKey,
			"MaxConnectionsPerServer",
			NULL,
			NULL,
			(LPBYTE)&dwMaxConnectionsPerServer,
			&cbMaxConnectionsPerServer
		);
		RegCloseKey(hKey);
	}

CleanUp:

	return dwMaxConnectionsPerServer;
}

int CAutoTraderDlg::DlData0(int nMode)
{
	int nRv = -1;

	int i;
	int j;
	int imax;
	int jmax;
#ifdef GETFUNASHI
	int k;
#endif
	CDaoDatabase Database;
	CDaoDatabase DatabaseOrg;
	BOOL bBeginTrans = FALSE;

	if (nMode & 0x1) {
		m_SaDlCode.RemoveAll();
		m_UiaDlHiashiIndex.RemoveAll();
//		m_UiaDlSel.RemoveAll();
		m_SaSelCode.RemoveAll();
		m_MstpSelCode.RemoveAll();
	}

	DWORD dwMaxConnectionsPerServer = max(min(m_dwMaxConnectionsPerServer, 16), 2);
	CDlHtmlThread** ppDlHtmlThread = (CDlHtmlThread **)new LPVOID[dwMaxConnectionsPerServer];
	CDlHtmlThread* pDlHtmlThread;
	ZeroMemory(ppDlHtmlThread, sizeof(CDlHtmlThread **) * dwMaxConnectionsPerServer);

	m_pServer = NULL;

//	if (! m_nExecMode  &&  ! m_bMentenance0)
	if (! m_nExecMode  &&  ! m_bMentenance1)
//		if (! AfxParseURL(m_psbQuickInfoUrl[0], m_dwServiceType, m_strServerName, m_strObjectC, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
		if (! AfxParseURL(m_psbQuickInfoUrl[1], m_dwServiceType, m_strServerName, m_strObjectC, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
//			DispErrorLog("URL 解析エラー: %s\n", m_psbQuickInfoUrl[0]);
			DispErrorLog("URL 解析エラー: %s\n", m_psbQuickInfoUrl[1]);
			goto CleanUp;
		}

	try
	{
		int nDlHtmlThreadIndex;
		DWORD dwThreadExitCode;
		BOOL bEnd = FALSE;
		BOOL bData;
		int nPtr0;
		int nPtr1;
		CHtmlTokenizer HtmlTokenizer0;
		CHtmlTokenizer HtmlTokenizer1;
		CStringBuffer sbValue;
		CStringBuffer sbTag;
		char chTag;
		CStringArray SaDlCode0;
		CStringArray SaDlCode1;
		CStringArray SaPrice0;
		CStringArray SaPrice1;
#ifdef GETFUNASHI
		CStringArray SaTime0;
		CStringArray SaTime1;
#endif
		CStringArray SaSijoName;
		CWordArray WaUnit;
//		CDWordArray DwaMaxHighPrice;
//		CDWordArray DwaMaxLowPrice;
//		CDWordArray DwaMaxPreEndPrice;
//		CDWordArray DwaMaxTradeCount;
		CString strStk0;
		CString strStk1;
		CString strStk2;
		CString strCode;
		CString strSijo;
		CString strName;
		CString strSijoName;
		CString strPrice;
		long lPrice;
		CString strDiff;
#ifdef GETFUNASHI
		CString strTime;
#endif
		COleDateTime DtCur;
		COleDateTime DtCurMinute;
		COleDateTime DtStart;
		COleDateTime DtEnd;
		COleDateTime DtTradeStart0;
		COleDateTime DtTradeStart1;
		COleDateTime DtTradeEnd0;
		COleDateTime DtTradeEnd1;
		BOOL bPreDateReq = FALSE;
		int nYear;
		int nMonth;
		int nDay;
		int nCurYear;
		int nCurMonth;
		int nCurDay;
		COleDateTime DtTime;
		COleDateTime DtDateTime;
		COleDateTime DtEmpty;
		long lDiff;
		long lPreEndPrice;
#ifdef GETFUNASHI
		CFunashi1 Funashi1;
#endif
		COleVariant pKeyArray[2];
		COleVariant var;
		short sUnit;
//		long lMaxHighPrice;
//		long lMaxLowPrice;
//		long lMaxPreEndPrice;
//		long lTicks;
//		long lMaxTradeCount;
//		long lMaxTradeCount1000;
		BOOL bSel;
		BOOL bAttr;
		CString strAttr;

		Database.Open(m_strDBFPath);
		if (m_nExecMode == 2)
			DatabaseOrg.Open(m_strOrgDBFPath, FALSE, TRUE);

		Database.m_pWorkspace->BeginTrans();
		bBeginTrans = TRUE;

		CDaoRecordset RsInfo(&Database);
		RsInfo.Open(dbOpenTable, TBL_INFO);
		RsInfo.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsHiashi(&Database);
		RsHiashi.Open(dbOpenTable, TBL_HIASHI);
		RsHiashi.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsFunashi(&Database);
		RsFunashi.Open(dbOpenTable, TBL_FUNASHI1);
		RsFunashi.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsFunashiDateTime(&Database);
		RsFunashiDateTime.Open(dbOpenTable, TBL_FUNASHIDATETIME);
		RsFunashiDateTime.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsHiashiPreDate(&(m_nExecMode == 2 ? DatabaseOrg : Database));
		RsHiashiPreDate.Open(dbOpenTable, TBL_HIASHI);
		RsHiashiPreDate.SetCurrentIndex(pszPrimaryKey);

		DtCur = GetCurrentTimeEx();
		nCurYear = DtCur.GetYear();
		nCurMonth = DtCur.GetMonth();
		nCurDay = DtCur.GetDay();
		DtCurMinute.SetDateTime(nCurYear, nCurMonth, nCurDay, DtCur.GetHour(), DtCur.GetMinute(), DtCur.GetSecond() / TIMEUNIT * TIMEUNIT);
		DtStart.SetDateTime(nCurYear, nCurMonth, nCurDay, 9, 0, 0);
//		DtEnd.SetDateTime(nCurYear, nCurMonth, nCurDay, 2, 0, 0);
		DtEnd.SetDateTime(nCurYear, nCurMonth, nCurDay, 7, 0, 0);

//		if (m_nExecMode || m_bMentenance0) {
		if (m_nExecMode || m_bMentenance1) {
			if (m_DtSim0 == DtEmpty) {
				pKeyArray[0] = COleVariant(DtCur);
				if (RsHiashiPreDate.Seek("<", pKeyArray, 2)) {
					RsHiashiPreDate.GetFieldValue(0, var);
					m_DtDate = var.date;
				}
			} else
				m_DtDate.SetDate(m_DtSim0.GetYear(), m_DtSim0.GetMonth(), m_DtSim0.GetDay());

			pKeyArray[0] = COleVariant(m_DtDate);
			if (RsHiashiPreDate.Seek("<", pKeyArray, 2)) {
				RsHiashiPreDate.GetFieldValue(0, var);
				m_DtPreDate = var.date;
			}
			pKeyArray[0] = COleVariant(m_DtPreDate);
			if (RsHiashiPreDate.Seek("<", pKeyArray, 2)) {
				RsHiashiPreDate.GetFieldValue(0, var);
				m_DtPrePreDate = var.date;
			}
			goto Finally;
		} else
			if (m_DtPreDate == DtEmpty  ||  m_DtPreDateGet < DtStart  &&  DtCur >= DtStart)
				bPreDateReq = TRUE;

		nYear = m_DtDate.GetYear();
		nMonth = m_DtDate.GetMonth();
		nDay = m_DtDate.GetDay();

		DtTradeStart0.SetDateTime(nYear, nMonth, nDay, 8, 0, 0);
//		DtTradeEnd0.SetDateTime(nYear, nMonth, nDay, 11, 1, 0);
		DtTradeEnd0.SetDateTime(nYear, nMonth, nDay, 11, 31, 0);
		DtTradeStart1.SetDateTime(nYear, nMonth, nDay, 12, 5, 0);
		DtTradeEnd1.SetDateTime(nYear, nMonth, nDay, 15, 16, 0);

		for (i = 0; ; i ++) {
			nDlHtmlThreadIndex = i % dwMaxConnectionsPerServer;

			if (i >= (int)dwMaxConnectionsPerServer)
				if (pDlHtmlThread = ppDlHtmlThread[nDlHtmlThreadIndex]) {
					if (WaitForSingleObject(pDlHtmlThread->m_hThread, INFINITE) == WAIT_FAILED) {
						DispErrorLog("WaitForSingleObject Error: %s\n", GetLastErrorMessage());
						ppDlHtmlThread[nDlHtmlThreadIndex] = NULL;
						goto CleanUp;
					}
					m_strObjectT = pDlHtmlThread->m_strObject;
					m_sbHtmlT = pDlHtmlThread->m_sbHtml;
					if (! GetExitCodeThread(pDlHtmlThread->m_hThread, &dwThreadExitCode)) {
						DispErrorLog("GetExitCodeThread Error: %s\n", GetLastErrorMessage());
						goto CleanUp;
					}
					if (dwThreadExitCode)
						DispErrorLog("DlHtmlThread Error\n");
					delete pDlHtmlThread;
					ppDlHtmlThread[nDlHtmlThreadIndex] = NULL;
				} else
					break;

			if (! bEnd) {
				pDlHtmlThread = new CDlHtmlThread;
				pDlHtmlThread->m_strDataDir = m_strDataDir;
				pDlHtmlThread->m_strServerName = m_strServerName;
				pDlHtmlThread->m_strObject.Format(OBJ_KABU_ICHIRAN, m_strObjectC, i * 10);
				pDlHtmlThread->m_nPort = m_nPort;
				pDlHtmlThread->m_nVerb = CHttpConnection::HTTP_VERB_GET;
				pDlHtmlThread->m_bAutoDelete = FALSE;
				if (! pDlHtmlThread->CreateThread()) {
					DispErrorLog("CreateThread Error\n");
					delete pDlHtmlThread;
					goto CleanUp;
				}
				ppDlHtmlThread[nDlHtmlThreadIndex] = pDlHtmlThread;
			}

			if (i >= (int)dwMaxConnectionsPerServer  &&  dwThreadExitCode == 0UL) {
				if ((nPtr0 = m_sbHtmlT.Find("リンク")) != -1) {
					HtmlTokenizer0.SetHtml(m_sbHtmlT);
					while (1) {
						if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<tr ", nPtr0 + 3)) == -1)
							break;
						if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<a ", nPtr0 + 3)) != -1) {
							bData = FALSE;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							if (HtmlTokenizer0.HtmlTok() == 0)
								goto DataCleanUp0;
							if (HtmlTokenizer0.FindTagAttr("href", sbValue) != 2)
								goto DataCleanUp0;
							sbValue = StrQTrim(sbValue);
							if ((nPtr1 = StrFindNoCase(sbValue, "&QCODE=")) == -1)
								goto DataCleanUp0;
							strCode = sbValue.Mid(nPtr1 + 7);
							if (strCode[4] != '/')
								continue;
							strSijo = strCode.Mid(5);
							if (strSijo == "FK"  ||  strSijo == "S")
								continue;
							for (j = 0; j < 18; j ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp0;
							strPrice = HtmlTokenizer0.m_strTag;
							lPrice = atol(strPrice);
							for (j = 0; j < 4; j ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp0;
#ifdef GETFUNASHI
							strTime = HtmlTokenizer0.m_strTag.Mid(1, 5);
#endif
							bAttr = FALSE;
							for (j = 0, jmax = 4; j < jmax; j ++) {
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp0;
								if (j == jmax - 1) {
									strDiff = HtmlTokenizer0.m_strTag;
									if (j == 3) {
										strAttr = strDiff.Left(2);
										if (strAttr == "配"  ||  strAttr == "他")
											bAttr = TRUE;
									}
									chTag = strDiff.Right(1)[0];
									if (! isdigit(chTag)  &&  chTag != '-')
										jmax ++;;
								}
							}
							strDiff.Replace("配", pszEmpty);
							strDiff.Replace("他", pszEmpty);
							lDiff = atol(strDiff);
							SaDlCode0.Add(strCode);
							SaPrice0.Add(strPrice);
#ifdef GETFUNASHI
							SaTime0.Add(strTime);
#endif
							if (bPreDateReq) {
//								m_pServer = m_ppSession[0]->GetHttpConnection(m_strServerName, m_nPort);
								m_pServer = m_ppSession[1]->GetHttpConnection(m_strServerName, m_nPort);
								m_strObject.Format(OBJ_KABU_KAKAKU, m_strObjectC, strCode);
								if (DlHtml(CHttpConnection::HTTP_VERB_GET))
									goto CleanUp;
								if ((nPtr1 = m_sbHtml.Find("日付：")) == -1)
									goto DataCleanUp0;
								if (DtCurMinute >= DtEnd  &&  DtCurMinute <= DtStart)
									m_DtDate.SetDate(nCurYear, nCurMonth, nCurDay);
								else
									if (! m_DtDate.ParseDateTime(m_sbHtml.Mid(nPtr1 + 6, 10)))
										goto DataCleanUp0;
								pKeyArray[0] = COleVariant(m_DtDate);
								pKeyArray[1] = COleVariant();
								if (RsHiashiPreDate.Seek("<", pKeyArray, 2)) {
									RsHiashiPreDate.GetFieldValue(0, var);
									m_DtPreDate = var.date;
								}
								pKeyArray[0] = COleVariant(m_DtPreDate);
								if (RsHiashiPreDate.Seek("<", pKeyArray, 2)) {
									RsHiashiPreDate.GetFieldValue(0, var);
									m_DtPrePreDate = var.date;
								}
								m_DtPreDateGet = GetCurrentTimeEx();
								if (nMode & 0x2) {
									nRv = 0;
									goto CleanUp;
								}
								nYear = m_DtDate.GetYear();
								nMonth = m_DtDate.GetMonth();
								nDay = m_DtDate.GetDay();
								DtTradeStart0.SetDateTime(nYear, nMonth, nDay, 8, 0, 0);
//								DtTradeEnd0.SetDateTime(nYear, nMonth, nDay, 11, 1, 0);
								DtTradeEnd0.SetDateTime(nYear, nMonth, nDay, 11, 31, 0);
								DtTradeStart1.SetDateTime(nYear, nMonth, nDay, 12, 5, 0);
								DtTradeEnd1.SetDateTime(nYear, nMonth, nDay, 15, 16, 0);
								bPreDateReq = FALSE;
							}
							pKeyArray[0] = COleVariant(strCode, VT_BSTRT);
							if (RsInfo.Seek("=", pKeyArray, 1)) {
								RsInfo.GetFieldValue(1, var);
								strName = V_BSTRT((LPVARIANT)var);
								if (! bAttr  &&  strName[0] == '!'  ||  bAttr  &&  strName[0] != '!') {
									if (bAttr)
										strName = '!' + strName;
									else
										strName.Delete(0);
									RsInfo.Edit();
									RsInfo.SetFieldValue(1, COleVariant(strName, VT_BSTRT));
									RsInfo.Update();
								}
							}
							while (strDiff != "----") {
								lPreEndPrice = lPrice - lDiff;
								pKeyArray[0] = COleVariant(DtCurMinute < DtStart ? m_DtPrePreDate : m_DtPreDate);
								pKeyArray[1] = COleVariant(strCode, VT_BSTRT);
								if (RsHiashi.Seek("=", pKeyArray, 2)) {
									RsHiashi.GetFieldValue(5, var);
									if (var.lVal == lPreEndPrice)
										break;
									RsHiashi.Edit();
								} else {
									RsHiashi.AddNew();
									for (j = 0; j < 2; j ++)
										RsHiashi.SetFieldValue(j, pKeyArray[j]);
								}
								RsHiashi.SetFieldValue(5, COleVariant(lPreEndPrice));
								RsHiashi.Update();

								break;
							}
							bData = TRUE;
DataCleanUp0:
							if (! bData)
								DispErrorLog("銘柄分足データ取得エラー\n");
						}
					}
				}

				if (m_sbHtmlT.Find("↓次ページ") == -1)
					bEnd = TRUE;
			}
		}

		for (i = 0, imax = SaDlCode0.GetSize(); i < imax; i ++) {
			strStk0 = i - 1 >= 0 ? SaDlCode0[i - 1].Left(4) : pszEmpty;
			strStk1 = SaDlCode0[i].Left(4);
			strStk2 = i + 1 < imax ? SaDlCode0[i + 1].Left(4) : pszEmpty;

			if (strStk1 != strStk0) {
//				if (strStk1 == strStk2) {
					strCode = strStk1;
//					CodeToName(strCode, strName);
//					CodeToName(strCode, strName, &strSijoName, &sUnit, &lMaxHighPrice, &lMaxLowPrice, &lMaxPreEndPrice, &lMaxTradeCount);
//					CodeToName(strCode, strName, &strSijoName, &sUnit, &lMaxHighPrice, NULL, &lMaxPreEndPrice, &lMaxTradeCount);
//					CodeToName(strCode, strName, NULL, &sUnit);
					CodeToName(strCode, strName, &strSijoName, &sUnit);
//				} else
//					strCode = SaDlCode0[i];

				if (strCode.GetLength() > 4) {
					SaDlCode1.Add(strCode);
					SaSijoName.Add(strSijoName);
					WaUnit.Add(sUnit);
//					DwaMaxHighPrice.Add(lMaxHighPrice);
//					DwaMaxLowPrice.Add(lMaxLowPrice);
//					DwaMaxPreEndPrice.Add(lMaxPreEndPrice);
//					DwaMaxTradeCount.Add(lMaxTradeCount);
				}
			}
		}

		for (i = j = 0, imax = SaDlCode0.GetSize(), jmax = SaDlCode1.GetSize(); i < imax  &&  j < jmax; i ++)
			if (SaDlCode0[i] == SaDlCode1[j]) {
				SaPrice1.Add(SaPrice0[i]);
#ifdef GETFUNASHI
				SaTime1.Add(SaTime0[i]);
#endif
				j ++;
			}

#ifdef GETFUNASHI
		for (i = 0, imax = SaDlCode1.GetSize(); i < imax; i ++) {
			strCode = SaDlCode1[i];
			bData = FALSE;
			lPrice = atol(SaPrice1[i]);
			if (lPrice == 0)
				continue;
			if (! DtTime.ParseDateTime(SaTime1[i]))
				goto DataCleanUp2;
			DtDateTime.SetDateTime(nYear, nMonth, nDay, DtTime.GetHour(), DtTime.GetMinute(), 0);
			pKeyArray[0] = COleVariant(DtDateTime);
			pKeyArray[1] = COleVariant(strCode, VT_BSTRT);
			if (! RsFunashi.Seek("=", pKeyArray, 2)) {
				RsFunashi.AddNew();
				for (j = 0; j < 2; j ++)
					RsFunashi.SetFieldValue(j, pKeyArray[j]);
				RsFunashi.SetFieldValue(2, COleVariant(lPrice));
				RsFunashi.Update();
				if ((nMode & 0x1) == 0) {
					k = m_UiaDlHiashiIndex[i];
					if (k >= 0) {
						Funashi1.Empty();
						Funashi1.DtDateTime = DtDateTime;
						Funashi1.lPrice = lPrice;
						AddFunashi1(k, Funashi1);
					}
				}
			}
			if (DtCurMinute >= DtTradeStart0  &&  DtCurMinute <= DtTradeEnd0  ||  DtCurMinute >= DtTradeStart1  &&  DtCurMinute <= DtTradeEnd1) {
				pKeyArray[0] = COleVariant(DtCurMinute);
				if (! RsFunashiDateTime.Seek("=", pKeyArray, 1)) {
					RsFunashiDateTime.AddNew();
					RsFunashiDateTime.SetFieldValue(0, pKeyArray[0]);
					RsFunashiDateTime.Update();
				}
			}
			bData = TRUE;
DataCleanUp2:
			if (! bData)
				DispErrorLog("銘柄分足データ取得エラー\n");
		}
#endif
		if (nMode & 0x1) {
			m_SaDlCode.Append(SaDlCode1);

			for (i = 0, imax = m_SaDlCode.GetSize(); i < imax; i ++) {
				strSijoName = SaSijoName[i];
				lPrice = atol(SaPrice1[i]);
//				lDiff = GetDiff(lPrice);
//				lMaxPreEndPrice = DwaMaxPreEndPrice[i];
//				lTicks = (DwaMaxHighPrice[i] - DwaMaxLowPrice[i]) / GetDiff(lMaxPreEndPrice);
//				lTicks = (DwaMaxHighPrice[i] - lMaxPreEndPrice) / GetDiff(lMaxPreEndPrice);
//				lMaxTradeCount1000 = DwaMaxTradeCount[i] * lDiff / 1000;
				if (
					bSel =
//						(lPrice  &&  lPrice < 200  &&  WaUnit[i] >= 1000)
//						(lPrice  &&  lPrice < 300  &&  WaUnit[i] == 100)
						(lPrice  &&  lPrice < 100  &&  WaUnit[i] == 100)
/*
						&&  lMaxTradeCount1000 > 3000
						&&  (
							(lMaxPreEndPrice >= 50  &&  lMaxPreEndPrice < 100  &&  lTicks >= 24)
							|| (lMaxPreEndPrice >= 100  &&  lMaxPreEndPrice < 200  &&  lTicks >= 40)
							|| (lMaxPreEndPrice >= 100000  &&  lMaxPreEndPrice < 150000  &&  lTicks >= 16)
							|| (lMaxPreEndPrice >= 150000  &&  lMaxPreEndPrice < 200000  &&  lTicks >= 24)
						)
						&&  (
							strSijoName == "ＨＣｽﾀﾝﾀﾞｰﾄﾞ"
							||  strSijoName == "ＨＣｸﾞﾛｰｽ"
							||  strSijoName == "東証ﾏｻﾞｰｽﾞ"
							||  strSijoName == "ＪＱ"
							||  strSijoName == "ＪＱＮＥＯ"
							||  strSijoName == "大証２部"
							||  strSijoName == "東証２部"
						)
*/
						&&  (
							strSijoName == "ＪＱ"
							||  strSijoName == "ＪＱｽﾀﾝﾀﾞｰﾄﾞ"
							||  strSijoName == "ＪＱｸﾞﾛｰｽ"
						)
				) {
					strCode = m_SaDlCode[i];
					m_MstpSelCode[strCode] = NULL;
					m_SaSelCode.Add(strCode);
				}
//				m_UiaDlSel.Add(bSel);
			}

			m_SaDlCode.InsertAt(0, "101");
//			m_UiaDlSel.InsertAt(0, (UINT)FALSE);
		}

Finally:
		Database.m_pWorkspace->CommitTrans();
		bBeginTrans = FALSE;
	}
	catch (CException* pEx) {
		DispErrorLog("銘柄分足データダウンロードエラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
		goto CleanUp;
	}

	nRv = 0;

CleanUp:
	if (bBeginTrans)
		Database.m_pWorkspace->Rollback();
	if (m_pServer) {
		m_pServer->Close();
		delete m_pServer;
		m_pServer = NULL;
	}
	for (i = 0; i < (int)dwMaxConnectionsPerServer; i ++)
		if (pDlHtmlThread = ppDlHtmlThread[i]) {
			WaitForSingleObject(pDlHtmlThread->m_hThread, INFINITE);
			delete pDlHtmlThread;
		}
	delete [] ppDlHtmlThread;

	return nRv;
}

int CAutoTraderDlg::DlData1()
{
	int nRv = -1;

	int i;
	int j;
	int k;
	int l;
	int imax;
	CDaoDatabase Database;
	BOOL bBeginTrans = FALSE;

	DWORD dwMaxConnectionsPerServer = max(min(m_dwMaxConnectionsPerServer, 16), 2);
	CDlHtmlThread** ppDlHtmlThread = (CDlHtmlThread **)new LPVOID[dwMaxConnectionsPerServer];
	CDlHtmlThread* pDlHtmlThread;
	ZeroMemory(ppDlHtmlThread, sizeof(CDlHtmlThread **) * dwMaxConnectionsPerServer);

	HANDLE* phThread = new HANDLE[dwMaxConnectionsPerServer];
	int* pCodeIndex = new int[dwMaxConnectionsPerServer];

	m_pServer = NULL;

	if (! AfxParseURL(m_psbQuickInfoUrl[1], m_dwServiceType, m_strServerName, m_strObjectC, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
		DispErrorLog("URL 解析エラー: %s\n", m_psbQuickInfoUrl[1]);
		goto CleanUp;
	}

	try
	{
		int nDlHtmlThreadIndex;
		DWORD dwRv;
		DWORD dwThreadExitCode;
		BOOL bEnd = FALSE;
		BOOL bData;
		int nPtr0;
		int nPtr1;
		int nPtr2;
		CHtmlTokenizer HtmlTokenizer0;
		CHtmlTokenizer HtmlTokenizer1;
		CStringBuffer sbValue;
		CStringArray SaDlCode;
		CString strStk0;
		CString strStk1;
		CString strStk2;
		int nCodeCount;
		CStringBuffer sbTag;
		CString strCode;
		CString strSijo;
		CStringTokenizer StringTokenizer0;
		CStringTokenizer StringTokenizer1;
		CString strName;
		CString strType;
		COleDateTime DtDate;
		long lStartPrice;
		long lHighPrice;
		long lLowPrice;
		long lPrice;
		long lTradeCount;
		short sUnit;
		COleVariant pKeyArray[2];
		COleVariant var;

		Database.Open(m_strDBFPath);

		Database.m_pWorkspace->BeginTrans();
		bBeginTrans = TRUE;

		CDaoRecordset RsInfo(&Database);
		RsInfo.Open(dbOpenTable, TBL_INFO);
		RsInfo.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsHiashi(&Database);
		RsHiashi.Open(dbOpenTable, TBL_HIASHI);
		RsHiashi.SetCurrentIndex(pszPrimaryKey);

		for (i = 0; ; i ++) {
			nDlHtmlThreadIndex = i % dwMaxConnectionsPerServer;

			if (i >= (int)dwMaxConnectionsPerServer)
				if (pDlHtmlThread = ppDlHtmlThread[nDlHtmlThreadIndex]) {
					if (WaitForSingleObject(pDlHtmlThread->m_hThread, INFINITE) == WAIT_FAILED) {
						DispErrorLog("WaitForSingleObject Error: %s\n", GetLastErrorMessage());
						ppDlHtmlThread[nDlHtmlThreadIndex] = NULL;
						goto CleanUp;
					}
					m_strObjectT = pDlHtmlThread->m_strObject;
					m_sbHtmlT = pDlHtmlThread->m_sbHtml;
					if (! GetExitCodeThread(pDlHtmlThread->m_hThread, &dwThreadExitCode)) {
						DispErrorLog("GetExitCodeThread Error: %s\n", GetLastErrorMessage());
						goto CleanUp;
					}
					if (dwThreadExitCode)
						DispErrorLog("DlHtmlThread Error\n");
					delete pDlHtmlThread;
					ppDlHtmlThread[nDlHtmlThreadIndex] = NULL;
				} else
					break;

			if (! bEnd) {
				pDlHtmlThread = new CDlHtmlThread;
				pDlHtmlThread->m_strDataDir = m_strDataDir;
				pDlHtmlThread->m_strServerName = m_strServerName;
				pDlHtmlThread->m_strObject.Format(OBJ_QSEARCH, m_strObjectC, i * 20);
				pDlHtmlThread->m_nPort = m_nPort;
				pDlHtmlThread->m_nVerb = CHttpConnection::HTTP_VERB_GET;
				pDlHtmlThread->m_bAutoDelete = FALSE;
				if (! pDlHtmlThread->CreateThread()) {
					DispErrorLog("CreateThread Error\n");
					delete pDlHtmlThread;
					goto CleanUp;
				}
				ppDlHtmlThread[nDlHtmlThreadIndex] = pDlHtmlThread;
			}

			if (i >= (int)dwMaxConnectionsPerServer  &&  dwThreadExitCode == 0UL) {
				if ((nPtr0 = m_sbHtmlT.Find("市場")) != -1) {
					HtmlTokenizer0.SetHtml(m_sbHtmlT);
					while (1) {
						if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<a ", nPtr0 + 3)) == -1)
							break;
						HtmlTokenizer0.m_nHtmlPtr = nPtr0;
						if (HtmlTokenizer0.HtmlTok())
							if (HtmlTokenizer0.FindTagAttr("href", sbValue) == 2) {
								sbValue = StrQTrim(sbValue);
								if ((nPtr1 = StrFindNoCase(sbValue, "&QCODE=")) == -1)
									break;
								strCode = sbValue.Mid(nPtr1 + 7);
								if (strCode[4] != '/')
									continue;
								strSijo = strCode.Mid(5);
								if (strSijo == "FK"  ||  strSijo == "S")
									continue;
								SaDlCode.Add(strCode);
							}
					}
				}

				if (m_sbHtmlT.Find("↓次ページ") == -1)
					bEnd = TRUE;
			}
		}

		nCodeCount = SaDlCode.GetSize();
		for (i = 0, imax = nCodeCount + dwMaxConnectionsPerServer; i < imax; i++) {
			nDlHtmlThreadIndex = i % dwMaxConnectionsPerServer;

			if (i >= (int)dwMaxConnectionsPerServer) {
				for (k = 0; k < (int)dwMaxConnectionsPerServer; k ++)
					if (ppDlHtmlThread[k] == NULL)
						break;
				if (k == 0)
					break;
				if ((dwRv = WaitForMultipleObjects(k, phThread, FALSE, INFINITE)) == WAIT_FAILED) {
					DispErrorLog("WaitForMultipleObjects Error: %s\n", GetLastErrorMessage());
					for (l = 0; l < k; l ++)
						ppDlHtmlThread[l] = NULL;
					goto CleanUp;
				}
				nDlHtmlThreadIndex = dwRv - WAIT_OBJECT_0;
				pDlHtmlThread = ppDlHtmlThread[nDlHtmlThreadIndex];
				j = pCodeIndex[nDlHtmlThreadIndex];
				m_strObjectT = pDlHtmlThread->m_strObject;
				m_sbHtmlT = pDlHtmlThread->m_sbHtml;
				if (! GetExitCodeThread(pDlHtmlThread->m_hThread, &dwThreadExitCode)) {
					DispErrorLog("GetExitCodeThread Error: %s\n", GetLastErrorMessage());
					goto CleanUp;
				}
				if (dwThreadExitCode)
					DispErrorLog("DlHtmlThread Error\n");
				delete pDlHtmlThread;
				ppDlHtmlThread[nDlHtmlThreadIndex] = NULL;
			}

			if (i < nCodeCount) {
				pDlHtmlThread = new CDlHtmlThread;
				pDlHtmlThread->m_strDataDir = m_strDataDir;
				pDlHtmlThread->m_strServerName = m_strServerName;
				pDlHtmlThread->m_strObject.Format(OBJ_KABU_HIASHI, m_strObjectC, SaDlCode[i]);
				pDlHtmlThread->m_nPort = m_nPort;
				pDlHtmlThread->m_nVerb = CHttpConnection::HTTP_VERB_GET;
				pDlHtmlThread->m_bAutoDelete = FALSE;
				if (! pDlHtmlThread->CreateThread()) {
					DispErrorLog("CreateThread Error\n");
					delete pDlHtmlThread;
					goto CleanUp;
				}
				ppDlHtmlThread[nDlHtmlThreadIndex] = pDlHtmlThread;
				phThread[nDlHtmlThreadIndex] = pDlHtmlThread->m_hThread;
				pCodeIndex[nDlHtmlThreadIndex] = i;
			} else
				if (i >= (int)dwMaxConnectionsPerServer  &&  nDlHtmlThreadIndex < k - 1) {
					ppDlHtmlThread[nDlHtmlThreadIndex] = ppDlHtmlThread[k - 1];
					phThread[nDlHtmlThreadIndex] = phThread[k - 1];
					pCodeIndex[nDlHtmlThreadIndex] = pCodeIndex[k - 1];
					ppDlHtmlThread[k - 1] = NULL;
				}

			if (i >= (int)dwMaxConnectionsPerServer  &&  dwThreadExitCode == 0UL) {
				bData = FALSE;
				if ((nPtr0 = m_sbHtmlT.Find("<!--見出し　ここから-->")) == -1  ||  (nPtr0 = m_sbHtmlT.Find("　", nPtr0 + 23)) == -1  ||  (nPtr1 = m_sbHtmlT.Find("<", nPtr0 + 2)) == -1)
					goto DataCleanUp0;
				strName = m_sbHtmlT.Mid(nPtr0 + 2, nPtr1 - (nPtr0 + 2));
				if ((nPtr0 = m_sbHtmlT.Find('[', nPtr1 + 1)) == -1)
					goto DataCleanUp0;
				if ((nPtr1 = StrReverseFindEx(m_sbHtmlT, ">", nPtr0)) == -1)
					goto DataCleanUp0;
				strSijo = m_sbHtmlT.Mid(nPtr1 + 1, nPtr0 - (nPtr1 + 1));
				if ((nPtr0 = m_sbHtmlT.Find("売買単位：", nPtr0 + 1)) == -1)
					goto DataCleanUp0;
				if ((nPtr1 = StrReverseFindEx(m_sbHtmlT, " &nbsp;", nPtr0)) == -1)
					goto DataCleanUp0;
				if ((nPtr2 = StrReverseFindEx(m_sbHtmlT, "&nbsp;", nPtr1)) == -1)
					goto DataCleanUp0;
				strType = m_sbHtmlT.Mid(nPtr2 + 6, nPtr1 - (nPtr2 + 6));
				if ((nPtr1 = m_sbHtmlT.Find("株", nPtr0 + 10)) == -1)
					goto DataCleanUp0;
				sUnit = atoi(m_sbHtmlT.Mid(nPtr0 + 10, nPtr1 - (nPtr0 + 10)));
				if ((nPtr0 = m_sbHtmlT.Find("<!--<form name=\"chart\">-->")) == -1)
					goto DataCleanUp0;
				HtmlTokenizer1.SetHtml(m_sbHtmlT);
				HtmlTokenizer1.m_nHtmlPtr = nPtr0;
				for (k = 0; k < 3; k ++)
					if (HtmlTokenizer1.HtmlTok() == 0)
						goto DataCleanUp0;
				if (HtmlTokenizer1.FindTagAttr("Value", sbValue) != 2)
					goto DataCleanUp0;
				sbValue = StrQTrim(sbValue);
				strCode = SaDlCode[j];
				StringTokenizer0.SetStrSep(sbValue, "\r\n");
				while (StringTokenizer0.StrTok()) {
					if (StringTokenizer0.m_strTok.IsEmpty()  ||  StringTokenizer0.m_strTok.Find(",,") != -1)
						continue;
					StringTokenizer1.SetStrSep(StringTokenizer0.m_strTok, ",");
					if (StringTokenizer1.StrTok() == 0)
						goto DataCleanUp0;
					if (DtDate.ParseDateTime(StringTokenizer1.m_strTok) == 0)
						goto DataCleanUp0;
					if (StringTokenizer1.StrTok() == 0)
						goto DataCleanUp0;
					lStartPrice = atol(StringTokenizer1.m_strTok);
					if (StringTokenizer1.StrTok() == 0)
						goto DataCleanUp0;
					lHighPrice = atol(StringTokenizer1.m_strTok);
					if (StringTokenizer1.StrTok() == 0)
						goto DataCleanUp0;
					lLowPrice = atol(StringTokenizer1.m_strTok);
					if (StringTokenizer1.StrTok() == 0)
						goto DataCleanUp0;
					lPrice = atol(StringTokenizer1.m_strTok);
					if (StringTokenizer1.StrTok() == 0)
						goto DataCleanUp0;
					lTradeCount = atol(StringTokenizer1.m_strTok);
					while (1) {
						pKeyArray[0] = COleVariant(DtDate);
						pKeyArray[1] = COleVariant(strCode, VT_BSTRT);
						if (RsHiashi.Seek("=", pKeyArray, 2)) {
							RsHiashi.GetFieldValue(6, var);
							if (var.lVal == lTradeCount) {
								RsHiashi.GetFieldValue(5, var);
								if (var.lVal == lPrice) {
									RsHiashi.GetFieldValue(4, var);
									if (var.lVal == lLowPrice) {
										RsHiashi.GetFieldValue(3, var);
										if (var.lVal == lHighPrice) {
											RsHiashi.GetFieldValue(2, var);
											if (var.lVal == lStartPrice)
												break;
										}
									}
								}
							}
							RsHiashi.Edit();
						} else {
							RsHiashi.AddNew();
							for (k = 0; k < 2; k ++)
								RsHiashi.SetFieldValue(k, pKeyArray[k]);
						}
						RsHiashi.SetFieldValue(2, COleVariant(lStartPrice));
						RsHiashi.SetFieldValue(3, COleVariant(lHighPrice));
						RsHiashi.SetFieldValue(4, COleVariant(lLowPrice));
						RsHiashi.SetFieldValue(5, COleVariant(lPrice));
						RsHiashi.SetFieldValue(6, COleVariant(lTradeCount));
						RsHiashi.Update();

						break;
					}
				}
				while (1) {
					pKeyArray[0] = COleVariant(strCode, VT_BSTRT);
					if (RsInfo.Seek("=", pKeyArray, 1)) {
						RsInfo.GetFieldValue(4, var);
						if (sUnit == var.iVal)
							break;
						RsInfo.Edit();
					} else {
						RsInfo.AddNew();
						RsInfo.SetFieldValue(0, pKeyArray[0]);
						RsInfo.SetFieldValue(1, COleVariant(strName, VT_BSTRT));
						RsInfo.SetFieldValue(2, COleVariant(strSijo, VT_BSTRT));
						RsInfo.SetFieldValue(3, COleVariant(strType, VT_BSTRT));
					}
					RsInfo.SetFieldValue(4, COleVariant(sUnit));
					RsInfo.Update();

					break;
				}
				bData = TRUE;
DataCleanUp0:
				if (! bData)
					DispErrorLog("銘柄データ取得エラー\n");
			}
		}

		Database.m_pWorkspace->CommitTrans();
		bBeginTrans = FALSE;
	}
	catch (CException* pEx) {
		DispErrorLog("銘柄データダウンロードエラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
		goto CleanUp;
	}

	nRv = 0;

CleanUp:
	if (bBeginTrans)
		Database.m_pWorkspace->Rollback();
	if (m_pServer) {
		m_pServer->Close();
		delete m_pServer;
		m_pServer = NULL;
	}
	delete [] pCodeIndex;
	delete [] phThread;
	for (i = 0; i < (int)dwMaxConnectionsPerServer; i ++)
		if (pDlHtmlThread = ppDlHtmlThread[i]) {
			WaitForSingleObject(pDlHtmlThread->m_hThread, INFINITE);
			delete pDlHtmlThread;
		}
	delete [] ppDlHtmlThread;

	return nRv;
}

/* コスモ証券 */
int CAutoTraderDlg::DlData2(int nMode)
{
	int nRv = -1;

	int i;
	int j;
	int k;
	int l;
	int m;
	int imax;
	int kmax;
	CDaoDatabase Database;
	BOOL bBeginTrans = FALSE;

	DWORD dwMaxConnectionsPerServer = max(min(m_dwMaxConnectionsPerServer, 16), 2);

	CDlHtmlThread** ppDlHtmlThread = (CDlHtmlThread **)new LPVOID[dwMaxConnectionsPerServer];
	CDlHtmlThread* pDlHtmlThread;
	ZeroMemory(ppDlHtmlThread, sizeof(CDlHtmlThread **) * dwMaxConnectionsPerServer);

	HANDLE* phThread = new HANDLE[dwMaxConnectionsPerServer];
	int* pCodeIndex = new int[dwMaxConnectionsPerServer];
	int* pDlMode = new int[dwMaxConnectionsPerServer];

	m_pServer = NULL;

	try
	{
		CString strServerName;
		INTERNET_PORT nPort;
		int nDlHtmlThreadIndex;
		DWORD dwRv;
		DWORD dwThreadExitCode;
		BOOL bEnd = FALSE;
		BOOL bData;
		int nPtr0;
		int nPtr1;
		CHtmlTokenizer HtmlTokenizer0;
		int nCodeCount;
		CStringBuffer sbTag;
		CString strCode;
		CString strStk;
		CString strSijo;
//		short sUnit;
		long lPrice;
		long lTradeCount;
		double dVwap;
		long lStartPrice;
		long lHighPrice;
		long lLowPrice;
//		CStringBuffer sbPreEndPrice;
//		long lPreEndPrice;
		COleDateTime DtCur;
		COleDateTime DtCurMinute;
		COleDateTime DtStart;
//		COleDateTime DtEnd;
		COleDateTime DtTradeStart0;
//		COleDateTime DtTradeStart0t;
		COleDateTime DtTradeStart1;
		COleDateTime DtTradeStart2;
		COleDateTime DtTradeStart3;
		COleDateTime DtTradeEnd0;
		COleDateTime DtTradeEnd1;
		COleDateTime DtTradeEnd1t;
		COleDateTime DtTradeEnd1o;
		COleDateTime DtTradeEnd2;
		COleDateTime DtTradeEnd3;
		BOOL bTradeTime;
		BOOL bPreDateReq = FALSE;
		int nYear;
		int nMonth;
		int nDay;
		int nCurYear;
		int nCurMonth;
		int nCurDay;
		COleDateTime DtTime;
		COleDateTime DtStartTime;
		COleDateTime DtDateTime;
//		long lKehaiPrice;
//		long lKehaiSellCount;
//		long lKehaiBuyCount;
		long lKehaiSpecial;
//		long plKehaiPrice[10];
//		long plKehaiCount[10];
//		int nKehaiSellIndex;
//		int nKehaiBuyIndex;
		CKehai0 Kehai0;
		CKehai1 Kehai1;
		CFunashi0 Funashi0;
		CFunashi1 Funashi1;
		CFunashi2 Funashi2;
		CFunashi0* pFunashi0;
		CFunashi1* pFunashi1;
		CFunashi2* pFunashi2;
		BOOL bSame;
		COleVariant pKeyArray[2];
		COleVariant var;
		void* pVoid;
		CStringArray SaSelCode;
		int nDlMode0;
		int nDlMode1;
		CString strReqCode;
		CString strObject;
		int nCodeIndex;
		BOOL bDBFunashiAdd;
		CStringArray SaCodeC;

		Database.Open(m_strDBFPath);

		Database.m_pWorkspace->BeginTrans();
		bBeginTrans = TRUE;

//		CDaoRecordset RsInfo(&Database);
//		RsInfo.Open(dbOpenTable, TBL_INFO);
//		RsInfo.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsHiashi(&Database);
		RsHiashi.Open(dbOpenTable, TBL_HIASHI);
		RsHiashi.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsFunashi0(&Database);
		RsFunashi0.Open(dbOpenTable, TBL_FUNASHI0);
		RsFunashi0.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsFunashi1(&Database);
		RsFunashi1.Open(dbOpenTable, TBL_FUNASHI1);
		RsFunashi1.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsFunashi2(&Database);
		RsFunashi2.Open(dbOpenTable, TBL_FUNASHI2);
		RsFunashi2.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsFunashiDateTime(&Database);
		RsFunashiDateTime.Open(dbOpenTable, TBL_FUNASHIDATETIME);
		RsFunashiDateTime.SetCurrentIndex(pszPrimaryKey);

		DtCur = GetCurrentTimeEx();
		nCurYear = DtCur.GetYear();
		nCurMonth = DtCur.GetMonth();
		nCurDay = DtCur.GetDay();
		DtCurMinute.SetDateTime(nCurYear, nCurMonth, nCurDay, DtCur.GetHour(), DtCur.GetMinute(), DtCur.GetSecond() / TIMEUNIT * TIMEUNIT);
		DtStart.SetDateTime(nCurYear, nCurMonth, nCurDay, 9, 0, 0);
//		DtEnd.SetDateTime(nCurYear, nCurMonth, nCurDay, 2, 0, 0);

		nYear = m_DtDate.GetYear();
		nMonth = m_DtDate.GetMonth();
		nDay = m_DtDate.GetDay();

		DtTradeStart0.SetDateTime(nYear, nMonth, nDay, 8, 0, 0);
//		DtTradeStart0t.SetDateTime(nYear, nMonth, nDay, 8, 20, 0);
//		DtTradeEnd0.SetDateTime(nYear, nMonth, nDay, 11, 1, 0);
		DtTradeEnd0.SetDateTime(nYear, nMonth, nDay, 11, 31, 0);
		DtTradeStart1.SetDateTime(nYear, nMonth, nDay, 12, 5, 0);
		DtTradeEnd1.SetDateTime(nYear, nMonth, nDay, 15, 16, 0);
		DtTradeEnd1t.SetDateTime(nYear, nMonth, nDay, 15, 1, 0);
		DtTradeEnd1o.SetDateTime(nYear, nMonth, nDay, 15, 11, 0);
		DtTradeStart2.SetDateTime(nYear, nMonth, nDay, 9, 0, 0);
//		DtTradeEnd2.SetDateTime(nYear, nMonth, nDay, 11, 1, 0);
		DtTradeEnd2.SetDateTime(nYear, nMonth, nDay, 11, 31, 0);
		DtTradeStart3.SetDateTime(nYear, nMonth, nDay, 12, 30, 0);
		DtTradeEnd3.SetDateTime(nYear, nMonth, nDay, 15, 16, 0);

		bTradeTime = DtCurMinute >= DtTradeStart0  &&  DtCurMinute < DtTradeEnd0  ||  DtCurMinute >= DtTradeStart1  &&  DtCurMinute < DtTradeEnd1;

		if (! AfxParseURL(m_sbCosmoQuoteUrl, m_dwServiceType, strServerName, m_strObjectC, nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
			DispErrorLog("URL 解析エラー: %s\n", m_sbCosmoQuoteUrl);
			goto CleanUp;
		}

		CStringArray& SaCode = (nMode & 0x1) == 0 ? m_SaHiashiCode : m_SaDlCode;
		for (i = 1, imax = SaCode.GetSize(); i < imax; i ++) {
			strCode = SaCode[i];
			strSijo = strCode.Mid(5);
			if (
//				strSijo == "T"  &&  (DtCurMinute >= DtTradeStart0  &&  DtCurMinute < DtTradeStart0t  ||  DtCurMinute > DtTradeEnd1t  &&  DtCurMinute <= DtTradeEnd1)
				strSijo == "T"  &&  (DtCurMinute > DtTradeEnd1t  &&  DtCurMinute <= DtTradeEnd1)
//				||  strSijo == "M"  &&  (DtCurMinute >= DtTradeStart0  &&  DtCurMinute < DtTradeStart0t)
				||  (strSijo == "O"  ||  strSijo == "NG"  ||  strSijo == "JQ")  &&  (DtCurMinute > DtTradeEnd1o  &&  DtCurMinute <= DtTradeEnd1)
/*
				||  strSijo == "JQ"
				&&  (
					(nDlMode0 =  nMode & 0x1  ||  m_MstpNiceCode.Lookup(strCode, pVoid))
					&&  (DtCurMinute > DtTradeEnd1t  &&  DtCurMinute <= DtTradeEnd1)
					||  ! nDlMode0
					&&  (
						DtCurMinute >= DtTradeStart0  &&  DtCurMinute < DtTradeStart2
						||  DtCurMinute >= DtTradeStart1  &&  DtCurMinute < DtTradeStart3
						||  DtCurMinute > DtTradeEnd1t  &&  DtCurMinute <= DtTradeEnd1
					)
				)
*/
			)
				continue;
			SaCodeC.Add(strCode);
		}
		nCodeCount = SaCodeC.GetSize();

		for (i = 0, nCodeIndex = 0; ; i ++, nCodeIndex ++) {
			nDlHtmlThreadIndex = i % dwMaxConnectionsPerServer;

			if (i >= (int)dwMaxConnectionsPerServer) {
				for (k = 0; k < (int)dwMaxConnectionsPerServer; k ++)
					if (ppDlHtmlThread[k] == NULL)
						break;
				if (k == 0)
					break;
				if ((dwRv = WaitForMultipleObjects(k, phThread, FALSE, INFINITE)) == WAIT_FAILED) {
					DispErrorLog("WaitForMultipleObjects Error: %s\n", GetLastErrorMessage());
					for (l = 0; l < k; l ++)
						ppDlHtmlThread[l] = NULL;
					goto CleanUp;
				}
				nDlHtmlThreadIndex = dwRv - WAIT_OBJECT_0;
				pDlHtmlThread = ppDlHtmlThread[nDlHtmlThreadIndex];
				j = pCodeIndex[nDlHtmlThreadIndex];
				nDlMode1 = pDlMode[nDlHtmlThreadIndex];
				m_strObjectT = pDlHtmlThread->m_strObject;
				m_sbHtmlT = pDlHtmlThread->m_sbHtml;
				if (! GetExitCodeThread(pDlHtmlThread->m_hThread, &dwThreadExitCode)) {
					DispErrorLog("GetExitCodeThread Error: %s\n", GetLastErrorMessage());
					goto CleanUp;
				}
				m_sbHtmlT.Replace("\r", pszEmpty);
				if (dwThreadExitCode)
					DispErrorLog("DlHtmlThread Error\n");
				delete pDlHtmlThread;
				ppDlHtmlThread[nDlHtmlThreadIndex] = NULL;
			}

			if (nCodeIndex < nCodeCount  ||  SaSelCode.GetSize()) {
				for (; ; nCodeIndex ++) {
					if (nCodeIndex < nCodeCount) {
						strCode = SaCodeC[nCodeIndex];
						if (nMode & 0x1  ||  m_MstpNiceCode.Lookup(strCode, pVoid)) {
							nDlMode0 = 0;
							break;
						}
						SaSelCode.Add(strCode);
					}
					if (SaSelCode.GetSize() == 20  ||  nCodeIndex >= nCodeCount - 1) {
						nDlMode0 =  DtCurMinute >= DtTradeStart2  &&  DtCurMinute < DtTradeEnd2  ||  DtCurMinute >= DtTradeStart3  &&  DtCurMinute < DtTradeEnd3  ? 1 : 2;
						break;
					}
				}
				if (nDlMode0) {
					strReqCode.Empty();
					for (k = 0, kmax = SaSelCode.GetSize(); k < kmax; k ++) {
						strCode = SaSelCode[k];
						strSijo = strCode.Mid(5);
						if (strSijo == "JQ")
							strSijo = "J";
						else if (strSijo == "NG")
							strSijo = "NJ";
						if (k)
							strReqCode += '*';
						strReqCode += strCode.Left(4) + "%23" + strSijo + "%241";
					}
					SaSelCode.RemoveAll();
					strObject.Format(nDlMode0 == 1 ? OBJ_COSMOQUOTE1 : OBJ_COSMOQUOTE2, strReqCode);
				} else {
					strStk = strCode.Left(4);
					strSijo = strCode.Mid(5);
					if (strSijo == "JQ")
						strSijo = "J";
					else if (strSijo == "NG")
						strSijo = "NJ";
					strObject.Format(OBJ_COSMOQUOTE0, strStk, strSijo);
				}
				pDlHtmlThread = new CDlHtmlThread;
				pDlHtmlThread->m_strDataDir = m_strDataDir;
				pDlHtmlThread->m_strServerName = strServerName;
				pDlHtmlThread->m_strObject = strObject;
				pDlHtmlThread->m_nPort = nPort;
				pDlHtmlThread->m_nVerb = CHttpConnection::HTTP_VERB_GET;
				pDlHtmlThread->m_pSession = m_ppSessionCosmo[nDlHtmlThreadIndex];
				pDlHtmlThread->m_bAutoDelete = FALSE;
				if (! pDlHtmlThread->CreateThread()) {
					DispErrorLog("CreateThread Error\n");
					delete pDlHtmlThread;
					goto CleanUp;
				}
				ppDlHtmlThread[nDlHtmlThreadIndex] = pDlHtmlThread;
				phThread[nDlHtmlThreadIndex] = pDlHtmlThread->m_hThread;
				pCodeIndex[nDlHtmlThreadIndex] = nCodeIndex;
				pDlMode[nDlHtmlThreadIndex] = nDlMode0;
			} else
				if (i >= (int)dwMaxConnectionsPerServer  &&  nDlHtmlThreadIndex < k - 1) {
					ppDlHtmlThread[nDlHtmlThreadIndex] = ppDlHtmlThread[k - 1];
					phThread[nDlHtmlThreadIndex] = phThread[k - 1];
					pCodeIndex[nDlHtmlThreadIndex] = pCodeIndex[k - 1];
					pDlMode[nDlHtmlThreadIndex] = pDlMode[k - 1];
					ppDlHtmlThread[k - 1] = NULL;
				}

			if (i >= (int)dwMaxConnectionsPerServer  &&  dwThreadExitCode == 0UL) {
				bData = FALSE;
				bDBFunashiAdd = FALSE;
				if (nDlMode1) {
					if ((nPtr0 = m_sbHtmlT.Find("騰落率")) == -1)
						goto DataCleanUp1;
					HtmlTokenizer0.SetHtml(m_sbHtmlT);
					HtmlTokenizer0.m_nHtmlPtr = nPtr0;
					for (k = 0; ; k ++) {
//						sbPreEndPrice.Empty();
//						lPreEndPrice = lStartPrice = lHighPrice = lLowPrice = lTradeCount = 0L;
						lStartPrice = lHighPrice = lLowPrice = lTradeCount = 0L;
						Kehai1.Empty();
						if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<tr>", nPtr0 + 1)) == -1)
							break;
						if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 4)) == -1)
							goto DataCleanUp1;
						HtmlTokenizer0.m_nHtmlPtr = nPtr0;
						for (l = 0; l < 3; l ++)
							if (HtmlTokenizer0.HtmlTok() == 0)
								goto DataCleanUp1;
						strCode = HtmlTokenizer0.m_strTag;
						nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
						if (strCode.IsEmpty())
							continue;
						for (l = 0; l < 2; l ++)
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
						HtmlTokenizer0.m_nHtmlPtr = nPtr0;
						for (l = 0; l < 2; l ++)
							if (HtmlTokenizer0.HtmlTok() == 0)
								goto DataCleanUp1;
						strSijo = HtmlTokenizer0.m_strTag;
						if (strSijo == "東証")
							strSijo = 'T';
						else if (strSijo == "大証")
							strSijo = 'O';
						else if (strSijo == "ＨＣ")
							strSijo = "NG";
						else if (strSijo == "ＪＱ")
							strSijo = "JQ";
						else if (strSijo == "名証")
							strSijo = 'M';
						strCode += '/' + strSijo;
						if ((nMode & 0x1) == 0) {
							if (! m_MstpHiashiCode.Lookup(strCode, pVoid))
								goto DataCleanUp1;
							j = (int)pVoid;
						}
						nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
						if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
							goto DataCleanUp1;
						HtmlTokenizer0.m_nHtmlPtr = nPtr0;
						for (l = 0; l < 2; l ++)
							if (HtmlTokenizer0.HtmlTok() == 0)
								goto DataCleanUp1;
						sbTag = HtmlTokenizer0.m_strTag;
						sbTag.Replace(",", pszEmpty);
						lPrice = atol(sbTag);
						nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
						if (lPrice) {
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbTag = HtmlTokenizer0.m_strTag;
							if (! DtTime.ParseDateTime(HtmlTokenizer0.m_strTag))
								goto DataCleanUp1;
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
/*
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbPreEndPrice = HtmlTokenizer0.m_strTag;
							sbPreEndPrice.Replace(",", pszEmpty);
							lPreEndPrice = lPrice - atol(sbPreEndPrice);
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
*/
							if (nDlMode1 == 1) {
								for (l = 0; l < 2; l ++)
									if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
										goto DataCleanUp1;
								HtmlTokenizer0.m_nHtmlPtr = nPtr0;
								for (l = 0; l < 2; l ++)
									if (HtmlTokenizer0.HtmlTok() == 0)
										goto DataCleanUp1;
								sbTag = HtmlTokenizer0.m_strTag;
								sbTag.Replace(",", pszEmpty);
								lStartPrice = atol(sbTag);
								nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
								if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
									goto DataCleanUp1;
								HtmlTokenizer0.m_nHtmlPtr = nPtr0;
								for (l = 0; l < 2; l ++)
									if (HtmlTokenizer0.HtmlTok() == 0)
										goto DataCleanUp1;
								sbTag = HtmlTokenizer0.m_strTag;
								sbTag.Replace(",", pszEmpty);
								lHighPrice = atol(sbTag);
								nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
								if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
									goto DataCleanUp1;
								HtmlTokenizer0.m_nHtmlPtr = nPtr0;
								for (l = 0; l < 2; l ++)
									if (HtmlTokenizer0.HtmlTok() == 0)
										goto DataCleanUp1;
								sbTag = HtmlTokenizer0.m_strTag;
								sbTag.Replace(",", pszEmpty);
								lLowPrice = atol(sbTag);
								nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
								if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
									goto DataCleanUp1;
								HtmlTokenizer0.m_nHtmlPtr = nPtr0;
								for (l = 0; l < 2; l ++)
									if (HtmlTokenizer0.HtmlTok() == 0)
										goto DataCleanUp1;
								sbTag = HtmlTokenizer0.m_strTag;
								sbTag.Replace(",", pszEmpty);
								lTradeCount = atol(sbTag);
								nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
							}
						} else {
							for (l = 0; l < 2; l ++)
								if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
									goto DataCleanUp1;
						}
						if (nDlMode1 == 2) {
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
							for (m = 0; m < 2; m ++) {
								if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
									goto DataCleanUp1;
								HtmlTokenizer0.m_nHtmlPtr = nPtr0;
								for (l = 0; l < 2; l ++)
									if (HtmlTokenizer0.HtmlTok() == 0)
										goto DataCleanUp1;
								sbTag = HtmlTokenizer0.m_strTag;
								sbTag.Replace(",", pszEmpty);
								Kehai1.m_plKehaiPrice[m] = atol(sbTag);
								nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
								if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
									goto DataCleanUp1;
								HtmlTokenizer0.m_nHtmlPtr = nPtr0;
								for (l = 0; l < 2; l ++)
									if (HtmlTokenizer0.HtmlTok() == 0)
										goto DataCleanUp1;
								sbTag = HtmlTokenizer0.m_strTag;
								sbTag.Replace(",", pszEmpty);
								Kehai1.m_plKehaiCount[m] = atol(sbTag);
								nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
							}
						}
						if (lPrice) {
/*
							while (sbPreEndPrice != "- ") {
								pKeyArray[0] = COleVariant(DtCurMinute < DtStart ? m_DtPrePreDate : m_DtPreDate);
								pKeyArray[1] = COleVariant(strCode, VT_BSTRT);
								if (RsHiashi.Seek("=", pKeyArray, 2)) {
									RsHiashi.GetFieldValue(5, var);
									if (var.lVal == lPreEndPrice)
										break;
									RsHiashi.Edit();
								} else {
									RsHiashi.AddNew();
									for (k = 0; k < 2; k ++)
										RsHiashi.SetFieldValue(k, pKeyArray[k]);
								}
								RsHiashi.SetFieldValue(5, COleVariant(lPreEndPrice));
								RsHiashi.Update();

								break;
							}
*/
							if (nDlMode1 == 1) {
								while (1) {
									pKeyArray[0] = COleVariant(m_DtDate);
									pKeyArray[1] = COleVariant(strCode, VT_BSTRT);
									if (RsHiashi.Seek("=", pKeyArray, 2)) {
										RsHiashi.GetFieldValue(6, var);
										if (var.lVal == lTradeCount) {
											RsHiashi.GetFieldValue(5, var);
											if (var.lVal == lPrice) {
												RsHiashi.GetFieldValue(4, var);
												if (var.lVal == lLowPrice) {
													RsHiashi.GetFieldValue(3, var);
													if (var.lVal == lHighPrice) {
														RsHiashi.GetFieldValue(2, var);
														if (var.lVal == lStartPrice)
															break;
													}
												}
											}
										}
										RsHiashi.Edit();
									} else {
										RsHiashi.AddNew();
										for (k = 0; k < 2; k ++)
											RsHiashi.SetFieldValue(k, pKeyArray[k]);
									}
									RsHiashi.SetFieldValue(2, COleVariant(lStartPrice));
									RsHiashi.SetFieldValue(3, COleVariant(lHighPrice));
									RsHiashi.SetFieldValue(4, COleVariant(lLowPrice));
									RsHiashi.SetFieldValue(5, COleVariant(lPrice));
									RsHiashi.SetFieldValue(6, COleVariant(lTradeCount));
									RsHiashi.Update();
									if ((nMode & 0x1) == 0) {
										m_DwaHiashiStartPrice[j] = lStartPrice;
										if (m_DwaHiashiPreEndPrice[j] == 0L)
											m_DwaHiashiStopDiff[j] = GetStopDiff(lStartPrice);
									}

									break;
								}
							}
						}
						if (bTradeTime)
							DtDateTime = DtCurMinute;
						else {
//							if (lPrice == 0L)
//								continue;
//							DtDateTime.SetDateTime(nYear, nMonth, nDay, DtTime.GetHour(), DtTime.GetMinute(), 0);
							continue;
						}
						bSame = TRUE;
						if (m_Mstf0Last.Lookup(strCode, Funashi0)) {
							if (nDlMode1 == 1) {
								if (
									Funashi0.m_nType != 1
									||  Funashi0.m_lPrice != lPrice
									||  Funashi0.m_lTradeCount != lTradeCount
								)
									bSame = FALSE;
							} else {
								if (
									Funashi0.m_nType != 2
									||  Funashi0.m_lPrice != lPrice
								)
									bSame = FALSE;
								else
									for (k = 0; k < 2; k ++)
										if (
											Funashi0.m_Kehai.m_plKehaiPrice[4 + k] != Kehai1.m_plKehaiPrice[k]
											||  Funashi0.m_Kehai.m_plKehaiCount[4 + k] != Kehai1.m_plKehaiCount[k]
										) {
											bSame = FALSE;
											break;
										}
							}
						} else
							bSame = FALSE;
						if (! bSame) {
							pKeyArray[0] = COleVariant(DtDateTime);
							pKeyArray[1] = COleVariant(strCode, VT_BSTRT);
							if (nDlMode1 == 1) {
								if (RsFunashi1.Seek("=", pKeyArray, 2)) {
//									if (! bTradeTime)
//										continue;
									RsFunashi1.Edit();
									if ((nMode & 0x1) == 0) {
										k = ((long *)m_PaFunashi[j])[-1] - 1;
										pFunashi1 = (CFunashi1 *)(m_pMappingViewCell + ((long *)m_PaFunashi[j])[k]);
										pFunashi1->m_lPrice = lPrice;
										pFunashi1->m_lTradeCount = lTradeCount;
									}
								} else {
									RsFunashi1.AddNew();
									for (k = 0; k < 2; k ++)
										RsFunashi1.SetFieldValue(k, pKeyArray[k]);
									if ((nMode & 0x1) == 0) {
										Funashi1.m_DtDateTime = DtDateTime;
										Funashi1.m_lPrice = lPrice;
										Funashi1.m_lTradeCount = lTradeCount;
										AddFunashi1(j, Funashi1);
									}
									bDBFunashiAdd = TRUE;
								}
								if (lPrice) {
									RsFunashi1.SetFieldValue(2, COleVariant(lPrice));
									RsFunashi1.SetFieldValue(3, COleVariant(lTradeCount));
								}
								RsFunashi1.Update();
							} else {
								if (RsFunashi2.Seek("=", pKeyArray, 2)) {
//									if (! bTradeTime)
//										continue;
									RsFunashi2.Edit();
									if ((nMode & 0x1) == 0) {
										k = ((long *)m_PaFunashi[j])[-1] - 1;
										pFunashi2 = (CFunashi2 *)(m_pMappingViewCell + ((long *)m_PaFunashi[j])[k]);
										pFunashi2->m_lPrice = lPrice;
										pFunashi2->m_Kehai = Kehai1;
									}
								} else {
									RsFunashi2.AddNew();
									for (k = 0; k < 2; k ++)
										RsFunashi2.SetFieldValue(k, pKeyArray[k]);
									if ((nMode & 0x1) == 0) {
										Funashi2.m_DtDateTime = DtDateTime;
										Funashi2.m_lPrice = lPrice;
										Funashi2.m_Kehai = Kehai1;
										AddFunashi2(j, Funashi2);
									}
									bDBFunashiAdd = TRUE;
								}
								if (lPrice)
									RsFunashi2.SetFieldValue(2, COleVariant(lPrice));
//								if (bTradeTime)
									for (k = 0; k < 2; k ++) {
										RsFunashi2.SetFieldValue(3 + k, COleVariant(Kehai1.m_plKehaiPrice[k]));
										RsFunashi2.SetFieldValue(5 + k, COleVariant(Kehai1.m_plKehaiCount[k]));
									}
								RsFunashi2.Update();
							}
							if ((nMode & 0x1) == 0)
								m_Mstf0Last[strCode] = GetFunashi(j, ((long *)m_PaFunashi[j])[-1] - 1);
							else {
								if (nDlMode1 == 1) {
									Funashi0.m_nType = 1;
									Funashi0.m_lTradeCount = lTradeCount;
								} else {
									Funashi0.m_nType = 2;
									Funashi0.m_Kehai.m_plKehaiPrice[4] = Kehai1.m_plKehaiPrice[0];
									Funashi0.m_Kehai.m_plKehaiPrice[5] = Kehai1.m_plKehaiPrice[1];
									Funashi0.m_Kehai.m_plKehaiCount[4] = Kehai1.m_plKehaiCount[0];
									Funashi0.m_Kehai.m_plKehaiCount[5] = Kehai1.m_plKehaiCount[1];
								}
								Funashi0.m_lPrice = lPrice;
								m_Mstf0Last[strCode] = Funashi0;
							}
						}
					}
					if (bDBFunashiAdd) {
//						if (bTradeTime) {
							pKeyArray[0] = COleVariant(DtCurMinute);
							if (! RsFunashiDateTime.Seek("=", pKeyArray, 1)) {
								RsFunashiDateTime.AddNew();
								RsFunashiDateTime.SetFieldValue(0, pKeyArray[0]);
								RsFunashiDateTime.Update();
							}
//						}
					}
				} else {
					lStartPrice = lHighPrice = lLowPrice = lTradeCount = 0L;
					dVwap = 0.0;
					strCode = SaCodeC[j];
					if ((nMode & 0x1) == 0) {
						if (! m_MstpHiashiCode.Lookup(strCode, pVoid))
							goto DataCleanUp1;
						j = (int)pVoid;
					}
					if (m_sbHtmlT.Find("指定エラー") != -1)
						continue;
/*
					if ((nPtr0 = m_sbHtmlT.Find("単元株数：")) == -1)
						goto DataCleanUp1;
					HtmlTokenizer0.SetHtml(m_sbHtmlT);
					HtmlTokenizer0.m_nHtmlPtr = nPtr0;
					if (HtmlTokenizer0.HtmlTok() == 0)
						goto DataCleanUp1;
					sbTag = HtmlTokenizer0.m_strTag.Mid(10);
					sbTag.Replace(",", pszEmpty);
					sbTag.Replace("株", pszEmpty);
					sUnit = atoi(sbTag);
					nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
*/
//					if ((nPtr0 = m_sbHtmlT.Find("現値エリア START", nPtr0)) == -1)
					if ((nPtr0 = m_sbHtmlT.Find("現値エリア START")) == -1)
						goto DataCleanUp1;
					HtmlTokenizer0.SetHtml(m_sbHtmlT);
					HtmlTokenizer0.m_nHtmlPtr = nPtr0;
					for (k = 0; k < 2; k ++)
						if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
							goto DataCleanUp1;
					HtmlTokenizer0.m_nHtmlPtr = nPtr0;
					for (k = 0; k < 2; k ++)
						if (HtmlTokenizer0.HtmlTok() == 0)
							goto DataCleanUp1;
					sbTag = HtmlTokenizer0.m_strTag;
					sbTag.Replace(",", pszEmpty);
					lPrice = atol(sbTag);
					nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
					if (lPrice) {
						for (k = 0; k < 2; k ++)
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
						HtmlTokenizer0.m_nHtmlPtr = nPtr0;
						for (k = 0; k < 2; k ++)
							if (HtmlTokenizer0.HtmlTok() == 0)
								goto DataCleanUp1;
						if (! DtTime.ParseDateTime(HtmlTokenizer0.m_strTag.Mid(1, 5)))
							goto DataCleanUp1;
						nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
						if ((nPtr0 = m_sbHtmlT.Find("出来高", nPtr0)) == -1)
							goto DataCleanUp1;
						for (k = 0; k < 2; k ++)
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
						HtmlTokenizer0.m_nHtmlPtr = nPtr0;
						for (k = 0; k < 2; k ++)
							if (HtmlTokenizer0.HtmlTok() == 0)
								goto DataCleanUp1;
						sbTag = HtmlTokenizer0.m_strTag;
						sbTag.Replace(",", pszEmpty);
						lTradeCount = atol(sbTag);
						nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
/*
						if ((nPtr0 = m_sbHtmlT.Find("前日終値", nPtr0)) == -1)
							goto DataCleanUp1;
						if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 8)) == -1)
							goto DataCleanUp1;
						HtmlTokenizer0.m_nHtmlPtr = nPtr0;
						for (k = 0; k < 2; k ++)
							if (HtmlTokenizer0.HtmlTok() == 0)
								goto DataCleanUp1;
						sbPreEndPrice = HtmlTokenizer0.m_strTag;
						sbPreEndPrice.Replace(",", pszEmpty);
						lPreEndPrice = atol(sbPreEndPrice);
*/
					}
/*
					if ((nPtr0 = m_sbHtmlT.Find("買い気配")) != -1) {
						// MM銘柄
						for (k = 0; k < 5; k ++) {
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<tr>", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
							for (l = 0; l < 2; l ++)
								if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 4)) == -1)
									goto DataCleanUp1;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbTag = HtmlTokenizer0.m_strTag;
							sbTag.Replace(",", pszEmpty);
							KehaiWork.m_plKehaiPrice[4 - k] = atol(sbTag);
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbTag = HtmlTokenizer0.m_strTag;
							sbTag.Replace(",", pszEmpty);
							KehaiWork.m_plKehaiCount[4 - k] = atol(sbTag);
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
							for (l = 0; l < 2; l ++)
								if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
									goto DataCleanUp1;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbTag = HtmlTokenizer0.m_strTag;
							sbTag.Replace(",", pszEmpty);
							KehaiWork.m_plKehaiPrice[5 + k] = atol(sbTag);
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbTag = HtmlTokenizer0.m_strTag;
							sbTag.Replace(",", pszEmpty);
							KehaiWork.m_plKehaiCount[5 + k] = atol(sbTag);
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
						}
					} else
*/
/*
					if ((nPtr0 = m_sbHtmlT.Find("件数")) != -1) {
						// JASDAQ
						nKehaiSellIndex = 0;
						nKehaiBuyIndex = 5;
						Kehai0.Empty();
						if ((nPtr0 = m_sbHtmlT.Find("成行", nPtr0 + 4)) == -1)
							goto DataCleanUp1;
						for (k = 0; k < 9; k ++) {
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<tr>", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 4)) == -1)
								goto DataCleanUp1;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbTag = HtmlTokenizer0.m_strTag;
							lKehaiSpecial = sbTag == "特"  ||  sbTag == "注"  ||  sbTag == "前"  ||  sbTag == "引"  ? -1 : 1;
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
							for (l = 0; l < 2; l ++)
								if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
									goto DataCleanUp1;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbTag = HtmlTokenizer0.m_strTag;
							sbTag.Replace(",", pszEmpty);
							lKehaiSellCount = atol(sbTag) * lKehaiSpecial;
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbTag = HtmlTokenizer0.m_strTag;
							sbTag.Replace(",", pszEmpty);
							lKehaiPrice = atol(sbTag);
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbTag = HtmlTokenizer0.m_strTag;
							sbTag.Replace(",", pszEmpty);
							lKehaiBuyCount = atol(sbTag);
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
							for (l = 0; l < 2; l ++)
								if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
									goto DataCleanUp1;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbTag = HtmlTokenizer0.m_strTag;
							lKehaiSpecial = sbTag == "特"  ||  sbTag == "注"  ||  sbTag == "前"  ||  sbTag == "引"  ? -1 : 1;
							lKehaiBuyCount *= lKehaiSpecial;
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
							if (lKehaiSellCount) {
								plKehaiPrice[nKehaiSellIndex] = lKehaiPrice;
								plKehaiCount[nKehaiSellIndex] = lKehaiSellCount;
								nKehaiSellIndex ++;
							}
							if (lKehaiBuyCount  &&  nKehaiBuyIndex < 10) {
								Kehai0.m_plKehaiPrice[nKehaiBuyIndex] = lKehaiPrice;
								Kehai0.m_plKehaiCount[nKehaiBuyIndex] = lKehaiBuyCount;
								nKehaiBuyIndex ++;
							}
						}
						for (k = 0; k < 5; k ++) {
							l = nKehaiSellIndex - 1 - k;
							if (l < 0)
								break;
							m = 4 - k;
							Kehai0.m_plKehaiPrice[m] = plKehaiPrice[l];
							Kehai0.m_plKehaiCount[m] = plKehaiCount[l];
						}
					} else {
*/
						// 東証、名証、大証、ヘラクレス
						if ((nPtr0 = m_sbHtmlT.Find("買数量")) == -1)
							goto DataCleanUp1;
						if ((nPtr1 = m_sbHtmlT.Find("最良指値", nPtr0 + 6)) != -1)
							nPtr0 = nPtr1;
						for (k = 0; k < 5; k ++) {
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<tr>", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 4)) == -1)
								goto DataCleanUp1;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbTag = HtmlTokenizer0.m_strTag;
							lKehaiSpecial = sbTag == "特"  ||  sbTag == "連"  ||  sbTag == "注"  ||  sbTag == "前"  ||  sbTag == "引"  ||  sbTag == "停"  ||  sbTag == "レ"  ? -1 : 1;
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbTag = HtmlTokenizer0.m_strTag;
							sbTag.Replace(",", pszEmpty);
							Kehai0.m_plKehaiCount[k] = atol(sbTag) * lKehaiSpecial;
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbTag = HtmlTokenizer0.m_strTag;
							sbTag.Replace(",", pszEmpty);
							Kehai0.m_plKehaiPrice[k] = atol(sbTag);
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
						}
						for (k = 5; k < 10; k ++) {
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<tr>", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
							for (l = 0; l < 3; l ++)
								if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 4)) == -1)
									goto DataCleanUp1;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbTag = HtmlTokenizer0.m_strTag;
							sbTag.Replace(",", pszEmpty);
							Kehai0.m_plKehaiPrice[k] = atol(sbTag);
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbTag = HtmlTokenizer0.m_strTag;
							sbTag.Replace(",", pszEmpty);
							Kehai0.m_plKehaiCount[k] = atol(sbTag);
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
							HtmlTokenizer0.m_nHtmlPtr = nPtr0;
							for (l = 0; l < 2; l ++)
								if (HtmlTokenizer0.HtmlTok() == 0)
									goto DataCleanUp1;
							sbTag = HtmlTokenizer0.m_strTag;
							lKehaiSpecial = sbTag == "特"  ||  sbTag == "連"  ||  sbTag == "注"  ||  sbTag == "前"  ||  sbTag == "引"  ||  sbTag == "停"  ||  sbTag == "レ"  ? -1 : 1;
							Kehai0.m_plKehaiCount[k] *= lKehaiSpecial;
							nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
						}
//					}
					if (lPrice) {
						if ((nPtr0 = m_sbHtmlT.Find("始値", nPtr0)) == -1)
							goto DataCleanUp1;
						for (k = 0; k < 2; k ++)
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
						HtmlTokenizer0.m_nHtmlPtr = nPtr0;
						for (k = 0; k < 2; k ++)
							if (HtmlTokenizer0.HtmlTok() == 0)
								goto DataCleanUp1;
						sbTag = HtmlTokenizer0.m_strTag;
						sbTag.Replace(",", pszEmpty);
						lStartPrice = atol(sbTag);
						if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", HtmlTokenizer0.m_nHtmlPtr)) == -1)
							goto DataCleanUp1;
						HtmlTokenizer0.m_nHtmlPtr = nPtr0;
						for (k = 0; k < 2; k ++)
							if (HtmlTokenizer0.HtmlTok() == 0)
								goto DataCleanUp1;
						if (! DtStartTime.ParseDateTime(HtmlTokenizer0.m_strTag.Mid(1, 5)))
							goto DataCleanUp1;
						if ((nPtr0 = m_sbHtmlT.Find("高値", HtmlTokenizer0.m_nHtmlPtr)) == -1)
							goto DataCleanUp1;
						for (k = 0; k < 2; k ++)
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
						HtmlTokenizer0.m_nHtmlPtr = nPtr0;
						for (k = 0; k < 2; k ++)
							if (HtmlTokenizer0.HtmlTok() == 0)
								goto DataCleanUp1;
						sbTag = HtmlTokenizer0.m_strTag;
						sbTag.Replace(",", pszEmpty);
						lHighPrice = atol(sbTag);
						if ((nPtr0 = m_sbHtmlT.Find("安値", HtmlTokenizer0.m_nHtmlPtr)) == -1)
							goto DataCleanUp1;
						for (k = 0; k < 2; k ++)
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
						HtmlTokenizer0.m_nHtmlPtr = nPtr0;
						for (k = 0; k < 2; k ++)
							if (HtmlTokenizer0.HtmlTok() == 0)
								goto DataCleanUp1;
						sbTag = HtmlTokenizer0.m_strTag;
						sbTag.Replace(",", pszEmpty);
						lLowPrice = atol(sbTag);
						if ((nPtr0 = m_sbHtmlT.Find(">VWAP", HtmlTokenizer0.m_nHtmlPtr)) == -1)
							goto DataCleanUp1;
						for (k = 0; k < 2; k ++)
							if ((nPtr0 = StrFindNoCase(m_sbHtmlT, "<td ", nPtr0 + 1)) == -1)
								goto DataCleanUp1;
						HtmlTokenizer0.m_nHtmlPtr = nPtr0;
						for (k = 0; k < 2; k ++)
							if (HtmlTokenizer0.HtmlTok() == 0)
								goto DataCleanUp1;
						sbTag = HtmlTokenizer0.m_strTag;
						sbTag.Replace(",", pszEmpty);
						dVwap = atof(sbTag);
/*
						if (m_bSetTimer2) {
							pKeyArray[0] = COleVariant(strCode, VT_BSTRT);
							if (RsInfo.Seek("=", pKeyArray, 1)) {
								RsInfo.GetFieldValue(4, var);
								if (sUnit != var.iVal) {
									RsInfo.Edit();
									RsInfo.SetFieldValue(4, COleVariant(sUnit));
									RsInfo.Update();
									if ((nMode & 0x1) == 0)
										m_WaHiashiUnit[j] = sUnit;
								}
							}
						}
						while (sbPreEndPrice != "-") {
							pKeyArray[0] = COleVariant(DtCurMinute < DtStart ? m_DtPrePreDate : m_DtPreDate);
							pKeyArray[1] = COleVariant(strCode, VT_BSTRT);
							if (RsHiashi.Seek("=", pKeyArray, 2)) {
								RsHiashi.GetFieldValue(5, var);
								if (var.lVal == lPreEndPrice)
									break;
								RsHiashi.Edit();
							} else {
								RsHiashi.AddNew();
								for (k = 0; k < 2; k ++)
									RsHiashi.SetFieldValue(k, pKeyArray[k]);
							}
							RsHiashi.SetFieldValue(5, COleVariant(lPreEndPrice));
							RsHiashi.Update();

							break;
						}
*/
						while (1) {
							pKeyArray[0] = COleVariant(m_DtDate);
							pKeyArray[1] = COleVariant(strCode, VT_BSTRT);
							if (RsHiashi.Seek("=", pKeyArray, 2)) {
								RsHiashi.GetFieldValue(6, var);
								if (var.lVal == lTradeCount) {
									RsHiashi.GetFieldValue(5, var);
									if (var.lVal == lPrice) {
										RsHiashi.GetFieldValue(4, var);
										if (var.lVal == lLowPrice) {
											RsHiashi.GetFieldValue(3, var);
											if (var.lVal == lHighPrice) {
												RsHiashi.GetFieldValue(2, var);
												if (var.lVal == lStartPrice)
													break;
											}
										}
									}
								}
								RsHiashi.Edit();
							} else {
								RsHiashi.AddNew();
								for (k = 0; k < 2; k ++)
									RsHiashi.SetFieldValue(k, pKeyArray[k]);
							}
							RsHiashi.SetFieldValue(2, COleVariant(lStartPrice));
							RsHiashi.SetFieldValue(3, COleVariant(lHighPrice));
							RsHiashi.SetFieldValue(4, COleVariant(lLowPrice));
							RsHiashi.SetFieldValue(5, COleVariant(lPrice));
							RsHiashi.SetFieldValue(6, COleVariant(lTradeCount));
							RsHiashi.Update();
							if ((nMode & 0x1) == 0) {
								m_DwaHiashiStartPrice[j] = lStartPrice;
								if (m_DwaHiashiPreEndPrice[j] == 0L)
									m_DwaHiashiStopDiff[j] = GetStopDiff(lStartPrice);
							}

							break;
						}
					}
					if (bTradeTime)
						DtDateTime = DtCurMinute;
					else {
//						if (lPrice == 0L)
//							continue;
//						DtDateTime.SetDateTime(nYear, nMonth, nDay, DtTime.GetHour(), DtTime.GetMinute(), 0);
						continue;
					}
					bSame = TRUE;
					if (m_Mstf0Last.Lookup(strCode, Funashi0)) {
						if (
							Funashi0.m_nType != 0
							||  Funashi0.m_lPrice != lPrice
							||  Funashi0.m_lTradeCount != lTradeCount
							||  Funashi0.m_dVwap != dVwap
						)
							bSame = FALSE;
						else
							for (k = 0; k < 10; k ++)
								if (
									Funashi0.m_Kehai.m_plKehaiPrice[k] != Kehai0.m_plKehaiPrice[k]
									||  Funashi0.m_Kehai.m_plKehaiCount[k] != Kehai0.m_plKehaiCount[k]
								) {
									bSame = FALSE;
									break;
								}
					} else
						bSame = FALSE;
					if (! bSame) {
						pKeyArray[0] = COleVariant(DtDateTime);
						pKeyArray[1] = COleVariant(strCode, VT_BSTRT);
						if (RsFunashi0.Seek("=", pKeyArray, 2)) {
//							if (! bTradeTime)
//								continue;
							RsFunashi0.Edit();
							if ((nMode & 0x1) == 0) {
								k = ((long *)m_PaFunashi[j])[-1] - 1;
								pFunashi0 = (CFunashi0 *)(m_pMappingViewCell + ((long *)m_PaFunashi[j])[k]);
								pFunashi0->m_lPrice = lPrice;
								pFunashi0->m_lTradeCount = lTradeCount;
								pFunashi0->m_dVwap = dVwap;
								pFunashi0->m_Kehai = Kehai0;
							}
						} else {
							RsFunashi0.AddNew();
							for (k = 0; k < 2; k ++)
								RsFunashi0.SetFieldValue(k, pKeyArray[k]);
							if ((nMode & 0x1) == 0) {
								Funashi0.m_nType = 0;
								Funashi0.m_DtDateTime = DtDateTime;
								Funashi0.m_lPrice = lPrice;
								Funashi0.m_lTradeCount = lTradeCount;
								Funashi0.m_dVwap = dVwap;
								Funashi0.m_Kehai = Kehai0;
								AddFunashi0(j, Funashi0);
							}
							bDBFunashiAdd = TRUE;
						}
						if (lPrice) {
							RsFunashi0.SetFieldValue(2, COleVariant(lPrice));
							RsFunashi0.SetFieldValue(3, COleVariant(lTradeCount));
							RsFunashi0.SetFieldValue(4, COleVariant(dVwap));
						}
//						if (bTradeTime)
							for (k = 0; k < 10; k ++) {
								RsFunashi0.SetFieldValue(5 + k, COleVariant(Kehai0.m_plKehaiPrice[k]));
								RsFunashi0.SetFieldValue(15 + k, COleVariant(Kehai0.m_plKehaiCount[k]));
							}
						RsFunashi0.Update();
						if ((nMode & 0x1) == 0)
							m_Mstf0Last[strCode] = GetFunashi(j, ((long *)m_PaFunashi[j])[-1] - 1);
						else {
							Funashi0.m_nType = 0;
							Funashi0.m_lPrice = lPrice;
							Funashi0.m_lTradeCount = lTradeCount;
							Funashi0.m_dVwap = dVwap;
							Funashi0.m_Kehai = Kehai0;
							m_Mstf0Last[strCode] = Funashi0;
						}
					}
					if (bDBFunashiAdd) {
//						if (bTradeTime) {
							pKeyArray[0] = COleVariant(DtCurMinute);
							if (! RsFunashiDateTime.Seek("=", pKeyArray, 1)) {
								RsFunashiDateTime.AddNew();
								RsFunashiDateTime.SetFieldValue(0, pKeyArray[0]);
								RsFunashiDateTime.Update();
							}
//						}
					}
				}
				bData = TRUE;

DataCleanUp1:
				if (! bData)
					DispErrorLog("銘柄分足データ取得エラー\n");
			}
		}

		Database.m_pWorkspace->CommitTrans();
		bBeginTrans = FALSE;
	}
	catch (CException* pEx) {
		DispErrorLog("銘柄分足データダウンロードエラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
		goto CleanUp;
	}

	nRv = 0;

CleanUp:
	if (bBeginTrans)
		Database.m_pWorkspace->Rollback();
	if (m_pServer) {
		m_pServer->Close();
		delete m_pServer;
		m_pServer = NULL;
	}
	delete [] pDlMode;
	delete [] pCodeIndex;
	delete [] phThread;
	for (i = 0; i < (int)dwMaxConnectionsPerServer; i ++)
		if (pDlHtmlThread = ppDlHtmlThread[i]) {
			WaitForSingleObject(pDlHtmlThread->m_hThread, INFINITE);
			delete pDlHtmlThread;
		}
	delete [] ppDlHtmlThread;

	return nRv;
}

/* リアルタイムシミュレーション */
int CAutoTraderDlg::DlData3(int nMode)
{
	int nRv = -1;

	int i;
	int j;
	int k;
	int imax;
	CDaoDatabase Database;
	CDaoDatabase DatabaseOrg;
	BOOL bBeginTrans = FALSE;

	DWORD dwMaxConnectionsPerServer = max(min(m_dwMaxConnectionsPerServer, 16), 2);
	CDlHtmlThread** ppDlHtmlThread = (CDlHtmlThread **)new LPVOID[dwMaxConnectionsPerServer];
	CDlHtmlThread* pDlHtmlThread;
	ZeroMemory(ppDlHtmlThread, sizeof(CDlHtmlThread **) * dwMaxConnectionsPerServer);

	try
	{
		int nDlHtmlThreadIndex;
		DWORD dwThreadExitCode;
		int nCodeCount;
		CString strCode;
		long lPrice;
		long lStartPrice;
		long lHighPrice;
		long lLowPrice;
		long lTradeCount;
		double dVwap;
		COleDateTime DtCur;
		COleDateTime DtCurMinute;
		COleDateTime DtStart;
		COleDateTime DtEnd;
		COleDateTime DtTradeStart0;
		COleDateTime DtTradeStart1;
		COleDateTime DtTradeEnd0;
		COleDateTime DtTradeEnd1;
		BOOL bPreDateReq = FALSE;
		int nYear;
		int nMonth;
		int nDay;
		int nCurYear;
		int nCurMonth;
		int nCurDay;
		COleDateTime DtDateTime;
		COleDateTime DtEmpty;
		CKehai0 Kehai0Work;
		CKehai1 Kehai1Work;
		CFunashi0 Funashi0;
		CFunashi1 Funashi1;
		CFunashi2 Funashi2;
		CFunashi0* pFunashi0;
		CFunashi1* pFunashi1;
		CFunashi2* pFunashi2;
		COleVariant pKeyArray[2];
		COleVariant var;
		BOOL bEdit;

		Database.Open(m_strDBFPath);
		DatabaseOrg.Open(m_strOrgDBFPath, FALSE, TRUE);

		Database.m_pWorkspace->BeginTrans();
		bBeginTrans = TRUE;

		CDaoRecordset RsFunashi0(&Database);
		RsFunashi0.Open(dbOpenTable, TBL_FUNASHI0);
		RsFunashi0.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsFunashi1(&Database);
		RsFunashi1.Open(dbOpenTable, TBL_FUNASHI1);
		RsFunashi1.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsFunashi2(&Database);
		RsFunashi2.Open(dbOpenTable, TBL_FUNASHI2);
		RsFunashi2.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsFunashi0Org(&DatabaseOrg);
		RsFunashi0Org.Open(dbOpenTable, TBL_FUNASHI0);
		RsFunashi0Org.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsFunashi1Org(&DatabaseOrg);
		RsFunashi1Org.Open(dbOpenTable, TBL_FUNASHI1);
		RsFunashi1Org.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsFunashi2Org(&DatabaseOrg);
		RsFunashi2Org.Open(dbOpenTable, TBL_FUNASHI2);
		RsFunashi2Org.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsFunashiDateTime(&Database);
		RsFunashiDateTime.Open(dbOpenTable, TBL_FUNASHIDATETIME);
		RsFunashiDateTime.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsHiashi(&Database);
		RsHiashi.Open(dbOpenTable, TBL_HIASHI);
		RsHiashi.SetCurrentIndex(pszPrimaryKey);

		CDaoRecordset RsHiashiPreDate(&DatabaseOrg);
		RsHiashiPreDate.Open(dbOpenTable, TBL_HIASHI);
		RsHiashiPreDate.SetCurrentIndex(pszPrimaryKey);

		DtCur = GetCurrentTimeEx();
		nCurYear = DtCur.GetYear();
		nCurMonth = DtCur.GetMonth();
		nCurDay = DtCur.GetDay();
		DtCurMinute.SetDateTime(nCurYear, nCurMonth, nCurDay, DtCur.GetHour(), DtCur.GetMinute(), DtCur.GetSecond() / TIMEUNIT * TIMEUNIT);
		DtStart.SetDateTime(nCurYear, nCurMonth, nCurDay, 8, 0, 0);
		DtEnd.SetDateTime(nCurYear, nCurMonth, nCurDay, 2, 0, 0);

		if (m_DtSim0 == DtEmpty) {
			pKeyArray[0] = COleVariant(DtCur);
			if (RsHiashiPreDate.Seek("<", pKeyArray, 2)) {
				RsHiashiPreDate.GetFieldValue(0, var);
				m_DtDate = var.date;
			}
		} else
			m_DtDate.SetDate(m_DtSim0.GetYear(), m_DtSim0.GetMonth(), m_DtSim0.GetDay());

		pKeyArray[0] = COleVariant(m_DtDate);
		if (RsHiashiPreDate.Seek("<", pKeyArray, 2)) {
			RsHiashiPreDate.GetFieldValue(0, var);
			m_DtPreDate = var.date;
		}
		pKeyArray[0] = COleVariant(m_DtPreDate);
		if (RsHiashiPreDate.Seek("<", pKeyArray, 2)) {
			RsHiashiPreDate.GetFieldValue(0, var);
			m_DtPrePreDate = var.date;
		}

		nYear = m_DtDate.GetYear();
		nMonth = m_DtDate.GetMonth();
		nDay = m_DtDate.GetDay();

		DtTradeStart0.SetDateTime(nYear, nMonth, nDay, 8, 0, 0);
//		DtTradeEnd0.SetDateTime(nYear, nMonth, nDay, 11, 1, 0);
		DtTradeEnd0.SetDateTime(nYear, nMonth, nDay, 11, 31, 0);
		DtTradeStart1.SetDateTime(nYear, nMonth, nDay, 12, 5, 0);
		DtTradeEnd1.SetDateTime(nYear, nMonth, nDay, 15, 16, 0);

		CStringArray& SaCode = (nMode & 0x1) == 0 ? m_SaHiashiCode : m_SaDlCode;
		nCodeCount = SaCode.GetSize();

		for (i = 0, imax = nCodeCount + dwMaxConnectionsPerServer; i < imax; i ++) {
			nDlHtmlThreadIndex = i % dwMaxConnectionsPerServer;

			if (i >= (int)dwMaxConnectionsPerServer)
				if (pDlHtmlThread = ppDlHtmlThread[nDlHtmlThreadIndex]) {
					dwThreadExitCode = 0UL;
					delete pDlHtmlThread;
					ppDlHtmlThread[nDlHtmlThreadIndex] = NULL;
				} else
					break;

			if (i < nCodeCount) {
				pDlHtmlThread = new CDlHtmlThread;
				ppDlHtmlThread[nDlHtmlThreadIndex] = pDlHtmlThread;
			}

			if (i >= (int)dwMaxConnectionsPerServer  &&  dwThreadExitCode == 0UL) {
				lTradeCount = 0L;
				j = i - dwMaxConnectionsPerServer;
				strCode = SaCode[j];
				DtDateTime = DtCurMinute;
				pKeyArray[0] = COleVariant(DtDateTime);
				pKeyArray[1] = COleVariant(strCode, VT_BSTRT);
				if (RsFunashi0Org.Seek("=", pKeyArray, 2)) {
					dVwap = 0.0;
					Kehai0Work.Empty();
					RsFunashi0Org.GetFieldValue(2, var);
					lPrice = var.vt == VT_NULL ? 0L : var.lVal;
					RsFunashi0Org.GetFieldValue(3, var);
					lTradeCount = var.vt == VT_NULL ? 0L : var.lVal;
					RsFunashi0Org.GetFieldValue(4, var);
					dVwap = var.vt == VT_NULL ? 0.0 : var.dblVal;
					for (k = 0; k < 10; k ++) {
						RsFunashi0Org.GetFieldValue(5 + k, var);
						if (var.vt != VT_NULL)
							Kehai0Work.m_plKehaiPrice[k] = var.lVal;

						RsFunashi0Org.GetFieldValue(15 + k, var);
						if (var.vt != VT_NULL)
							Kehai0Work.m_plKehaiCount[k] = var.lVal;
					}
					if (RsFunashi0.Seek("=", pKeyArray, 2)) {
						RsFunashi0.Edit();
						if ((nMode & 0x1) == 0) {
							k = ((long *)m_PaFunashi[j])[-1] - 1;
							pFunashi0 = (CFunashi0 *)(m_pMappingViewCell + ((long *)m_PaFunashi[j])[k]);
							pFunashi0->m_lPrice = lPrice;
							pFunashi0->m_lTradeCount = lTradeCount;
							pFunashi0->m_dVwap = dVwap;
							pFunashi0->m_Kehai = Kehai0Work;
						}
					} else {
						RsFunashi0.AddNew();
						for (k = 0; k < 2; k ++)
							RsFunashi0.SetFieldValue(k, pKeyArray[k]);
						if ((nMode & 0x1) == 0) {
							Funashi0.m_DtDateTime = DtDateTime;
							Funashi0.m_lPrice = lPrice;
							Funashi0.m_lTradeCount = lTradeCount;
							Funashi0.m_dVwap = dVwap;
							Funashi0.m_Kehai = Kehai0Work;
							AddFunashi0(j, Funashi0);
						}
					}
					if (lPrice) {
						RsFunashi0.SetFieldValue(2, COleVariant(lPrice));
						if (lTradeCount)
							RsFunashi0.SetFieldValue(3, COleVariant(lTradeCount));
						if (dVwap > 0.0)
							RsFunashi0.SetFieldValue(4, COleVariant(dVwap));
					}
					for (k = 0; k < 10; k ++) {
						RsFunashi0.SetFieldValue(5 + k, COleVariant(Kehai0Work.m_plKehaiPrice[k]));
						RsFunashi0.SetFieldValue(15 + k, COleVariant(Kehai0Work.m_plKehaiCount[k]));
					}
					RsFunashi0.Update();
				} else if (RsFunashi1Org.Seek("=", pKeyArray, 2)) {
					RsFunashi1Org.GetFieldValue(2, var);
					lPrice = var.vt == VT_NULL ? 0L : var.lVal;
					RsFunashi1Org.GetFieldValue(3, var);
					lTradeCount = var.vt == VT_NULL ? 0L : var.lVal;
					if (RsFunashi1.Seek("=", pKeyArray, 2)) {
						RsFunashi1.Edit();
						if ((nMode & 0x1) == 0) {
							k = ((long *)m_PaFunashi[j])[-1] - 1;
							pFunashi1 = (CFunashi1 *)(m_pMappingViewCell + ((long *)m_PaFunashi[j])[k]);
							pFunashi1->m_lPrice = lPrice;
							pFunashi1->m_lTradeCount = lTradeCount;
						}
					} else {
						RsFunashi1.AddNew();
						for (k = 0; k < 2; k ++)
							RsFunashi1.SetFieldValue(k, pKeyArray[k]);
						if ((nMode & 0x1) == 0) {
							Funashi1.m_DtDateTime = DtDateTime;
							Funashi1.m_lPrice = lPrice;
							Funashi1.m_lTradeCount = lTradeCount;
							AddFunashi1(j, Funashi1);
						}
					}
					if (lPrice) {
						RsFunashi1.SetFieldValue(2, COleVariant(lPrice));
						if (lTradeCount)
							RsFunashi1.SetFieldValue(3, COleVariant(lTradeCount));
					}
					RsFunashi1.Update();
				} else if (RsFunashi2Org.Seek("=", pKeyArray, 2)) {
					Kehai1Work.Empty();
					RsFunashi2Org.GetFieldValue(2, var);
					lPrice = var.vt == VT_NULL ? 0L : var.lVal;
					for (k = 0; k < 2; k ++) {
						RsFunashi2Org.GetFieldValue(3 + k, var);
						if (var.vt != VT_NULL)
							Kehai1Work.m_plKehaiPrice[k] = var.lVal;

						RsFunashi2Org.GetFieldValue(5 + k, var);
						if (var.vt != VT_NULL)
							Kehai1Work.m_plKehaiCount[k] = var.lVal;
					}
					if (RsFunashi2.Seek("=", pKeyArray, 2)) {
						RsFunashi2.Edit();
						if ((nMode & 0x1) == 0) {
							k = ((long *)m_PaFunashi[j])[-1] - 1;
							pFunashi2 = (CFunashi2 *)(m_pMappingViewCell + ((long *)m_PaFunashi[j])[k]);
							pFunashi2->m_lPrice = lPrice;
							pFunashi2->m_Kehai = Kehai1Work;
						}
					} else {
						RsFunashi2.AddNew();
						for (k = 0; k < 2; k ++)
							RsFunashi2.SetFieldValue(k, pKeyArray[k]);
						if ((nMode & 0x1) == 0) {
							Funashi2.m_DtDateTime = DtDateTime;
							Funashi2.m_lPrice = lPrice;
							Funashi2.m_Kehai = Kehai1Work;
							AddFunashi2(j, Funashi2);
						}
					}
					if (lPrice)
						RsFunashi2.SetFieldValue(2, COleVariant(lPrice));
					for (k = 0; k < 2; k ++) {
						RsFunashi2.SetFieldValue(3 + k, COleVariant(Kehai1Work.m_plKehaiPrice[k]));
						RsFunashi2.SetFieldValue(5 + k, COleVariant(Kehai1Work.m_plKehaiCount[k]));
					}
					RsFunashi2.Update();
				} else
					continue;
//				if (DtCurMinute >= DtTradeStart0  &&  DtCurMinute <= DtTradeEnd0  ||  DtCurMinute >= DtTradeStart1  &&  DtCurMinute <= DtTradeEnd1) {
					pKeyArray[0] = COleVariant(DtCurMinute);
					if (! RsFunashiDateTime.Seek("=", pKeyArray, 1)) {
						RsFunashiDateTime.AddNew();
						RsFunashiDateTime.SetFieldValue(0, pKeyArray[0]);
						RsFunashiDateTime.Update();
					}
//				}
				if (lPrice)
					do {
						pKeyArray[0] = COleVariant(m_DtDate);
						if (RsHiashi.Seek("=", pKeyArray, 2)) {
							RsHiashi.GetFieldValue(2, var);
							lStartPrice = var.lVal;
							RsHiashi.GetFieldValue(3, var);
							lHighPrice = var.lVal;
							if (lHighPrice < lPrice)
								bEdit = lHighPrice = lPrice;
							RsHiashi.GetFieldValue(4, var);
							lLowPrice = var.lVal;
							if (lLowPrice > lPrice)
								bEdit = lLowPrice = lPrice;
							RsHiashi.GetFieldValue(5, var);
							if (var.lVal != lPrice)
								bEdit = TRUE;
							RsHiashi.GetFieldValue(6, var);
							if (var.lVal != lTradeCount)
								bEdit = TRUE;
							if (! bEdit)
								break;
							RsHiashi.Edit();
						} else {
							RsHiashi.AddNew();
							for (k = 0; k < 2; k ++)
								RsHiashi.SetFieldValue(k, pKeyArray[k]);
							lStartPrice = lHighPrice = lLowPrice = lPrice;
						}
						RsHiashi.SetFieldValue(2, COleVariant(lStartPrice));
						RsHiashi.SetFieldValue(3, COleVariant(lHighPrice));
						RsHiashi.SetFieldValue(4, COleVariant(lLowPrice));
						RsHiashi.SetFieldValue(5, COleVariant(lPrice));
						if (lTradeCount)
							RsHiashi.SetFieldValue(6, COleVariant(lTradeCount));
						RsHiashi.Update();
					} while (0);
			}
		}

		Database.m_pWorkspace->CommitTrans();
		bBeginTrans = FALSE;
	}
	catch (CException* pEx) {
		DispErrorLog("銘柄分足データダウンロードエラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
		goto CleanUp;
	}

	nRv = 0;

CleanUp:
	if (bBeginTrans)
		Database.m_pWorkspace->Rollback();
	for (i = 0; i < (int)dwMaxConnectionsPerServer; i ++)
		if (pDlHtmlThread = ppDlHtmlThread[i]) {
			delete pDlHtmlThread;
		}
	delete [] ppDlHtmlThread;

	return nRv;
}

int CAutoTraderDlg::DlChart()
{
	int nRv = -1;

	int i;
	int j;
	CInternetSession Session;

	DWORD dwMaxConnectionsPerServer = m_dwMaxConnectionsPerServer;

	CDlHtmlThread** ppDlHtmlThread = (CDlHtmlThread **)new LPVOID[dwMaxConnectionsPerServer];
	CDlHtmlThread* pDlHtmlThread;
	ZeroMemory(ppDlHtmlThread, sizeof(CDlHtmlThread **) * dwMaxConnectionsPerServer);

	CDlFileThread** ppDlFileThread = (CDlFileThread **)new LPVOID[dwMaxConnectionsPerServer];
	CDlFileThread* pDlFileThread;
	ZeroMemory(ppDlFileThread, sizeof(CDlFileThread **) * dwMaxConnectionsPerServer);

	int* pCodeIndex = new int[dwMaxConnectionsPerServer];

	m_pServer = NULL;

	try
	{
		int nDlFileThreadIndex;
		DWORD dwThreadExitCode;
		BOOL bEnd = FALSE;
		CHtmlTokenizer HtmlTokenizer0;
		CStringBuffer sbValue;
		int nCodeCount;
		CStringBuffer sbTag;
		CStringArray SaDlCode;
		CString strStk0;
		CString strStk1;
		CString strStk2;
		CString strCode;
		CString strStk;
		CString strSijo;
		CString strName;
		CString strSijoName;
		COleDateTime DtCur;
		BOOL bPreDateReq = FALSE;
		int nYear;
		int nMonth;
		int nDay;
		COleDateTime DtStartTime;
		COleDateTime DtEmpty;
		COleVariant pKeyArray[1];
		COleVariant var;
		CString strFName0;
		CString strFName1;
		CString strFPath0;
		CString strFPath1;
		CString strFPath2;
		CStringBuffer sbFilesDir0;
		CStringBuffer sbFilesDir1;
		CStringBuffer sbFilesDir2;
		CStringBuffer sbFilesDir1a;
		CStringBuffer sbFilesDir2a;
		CStringBuffer sbFilesDir3a;
		CStringBuffer sbFilesDir4a;
		_TCHAR pszFromFPath[MAX_PATH + 1];
		SHFILEOPSTRUCT fileop;
		BOOL bName;
		BOOL bDlFileThread;
		CString strUrl;
		int nDlIndex;
		int nCodeIndex;

		nYear = m_DtDate.GetYear();
		nMonth = m_DtDate.GetMonth();
		nDay = m_DtDate.GetDay();

		fileop.hwnd = NULL;
		fileop.wFunc = FO_DELETE;
		fileop.pFrom = pszFromFPath;
		fileop.pTo = NULL;
		fileop.fFlags = FOF_NOCONFIRMATION | FOF_SILENT;

		if (! AfxParseURL(m_psbQuickInfoUrl[1], m_dwServiceType, m_strServerName, m_strObjectC, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
			DispErrorLog("URL 解析エラー: %s\n", m_psbQuickInfoUrl[1]);
			goto CleanUp;
		}

//		sbFilesDir1.Format(m_strDataDir + "\\Chart\\0000 Date\\%4d%02d%02d", nYear, nMonth, nDay);
		sbFilesDir1 = m_strDataDir + "\\Chart\\0000 Today MinuteChart";

		if (CFile::GetStatus(sbFilesDir1, m_FileStatus)) {
			_tcscpy(pszFromFPath, sbFilesDir1);
			_tcscat(pszFromFPath, _T("\\*"));
			pszFromFPath[_tcslen(pszFromFPath) + 1] = _T('\0');
			if (SHFileOperation(&fileop)) {
				DispErrorLog("銘柄チャートダウンロードフォルダファイル削除エラー: %s\n", pszFromFPath);
				goto CleanUp;
			}
		} else {
			if (ForceDir(sbFilesDir1)) {
				DispErrorLog("銘柄チャートダウンロードフォルダ作成エラー: %s: %s\n", sbFilesDir1, GetLastErrorMessage());
				goto CleanUp;
			}
		}

		sbFilesDir2.Format(m_strDataDir + "\\Chart\\0000 Today DayChart");

		if (CFile::GetStatus(sbFilesDir2, m_FileStatus)) {
			_tcscpy(pszFromFPath, sbFilesDir2);
			_tcscat(pszFromFPath, _T("\\*"));
			pszFromFPath[_tcslen(pszFromFPath) + 1] = _T('\0');
			if (SHFileOperation(&fileop)) {
				DispErrorLog("銘柄チャートダウンロードフォルダファイル削除エラー: %s\n", pszFromFPath);
				goto CleanUp;
			}
		} else {
			if (ForceDir(sbFilesDir2)) {
				DispErrorLog("銘柄チャートダウンロードフォルダ作成エラー: %s: %s\n", sbFilesDir2, GetLastErrorMessage());
				goto CleanUp;
			}
		}

		nCodeCount = m_SaDlCode.GetSize() * 2;

		for (i = 0, nCodeIndex = 2; ; i ++, nCodeIndex ++) {
			nDlFileThreadIndex = i % dwMaxConnectionsPerServer;
			bDlFileThread = FALSE;

			if (i >= (int)dwMaxConnectionsPerServer)
				if (pDlFileThread = ppDlFileThread[nDlFileThreadIndex]) {
					if (WaitForSingleObject(pDlFileThread->m_hThread, INFINITE) == WAIT_FAILED) {
						DispErrorLog("WaitForSingleObject Error: %s\n", GetLastErrorMessage());
						ppDlFileThread[nDlFileThreadIndex] = NULL;
						goto CleanUp;
					}
					j = pCodeIndex[nDlFileThreadIndex];
					m_strObjectT = pDlFileThread->m_strObject;
					m_strFPath = pDlFileThread->m_strFPath;
					m_strFPathC0 = pDlFileThread->m_strFPathC0;
					m_strFPathC1 = pDlFileThread->m_strFPathC1;
					if (! GetExitCodeThread(pDlFileThread->m_hThread, &dwThreadExitCode)) {
						DispErrorLog("GetExitCodeThread Error: %s\n", GetLastErrorMessage());
						goto CleanUp;
					}
					if (dwThreadExitCode)
						DispErrorLog("DlFileThread Error\n");
					delete pDlFileThread;
					ppDlFileThread[nDlFileThreadIndex] = NULL;
					bDlFileThread = TRUE;
				} else
					break;

			if (nCodeIndex < nCodeCount) {
				if ((nCodeIndex & 0x1) == 0) {
					nDlIndex = nCodeIndex >> 1;
					strCode = m_SaDlCode[nDlIndex];
					strStk = strCode.Left(4);
					strSijo = strCode.Mid(5);
					strCode = strStk;
					bName = ! CodeToName(strCode, strName, &strSijoName);

					if (bName) {
						if (strName[0] == '!')
							strName.Delete(0);
						strName.Replace("/", "／");

						sbFilesDir0.Format(m_strDataDir + "\\Chart\\%s\\%s %s %s", strSijoName, strStk, strSijo, strName);
						sbFilesDir1a = sbFilesDir1 + '\\' + strSijoName;
						sbFilesDir2a = sbFilesDir2 + '\\' + strSijoName;

						if (! CFile::GetStatus(sbFilesDir0, m_FileStatus)) {
							if (ForceDir(sbFilesDir0)) {
								DispErrorLog("銘柄チャートダウンロードフォルダ作成エラー: %s: %s\n", sbFilesDir0, GetLastErrorMessage());
								goto CleanUp;
							}
						}
						if (! CFile::GetStatus(sbFilesDir1a, m_FileStatus)) {
							if (ForceDir(sbFilesDir1a)) {
								DispErrorLog("銘柄チャートダウンロードフォルダ作成エラー: %s: %s\n", sbFilesDir1a, GetLastErrorMessage());
								goto CleanUp;
							}
						}
						if (! CFile::GetStatus(sbFilesDir2a, m_FileStatus)) {
							if (ForceDir(sbFilesDir2a)) {
								DispErrorLog("銘柄チャートダウンロードフォルダ作成エラー: %s: %s\n", sbFilesDir2a, GetLastErrorMessage());
								goto CleanUp;
							}
						}

						strFName0.Format("%4d%02d%02d.gif", nYear, nMonth, nDay);
						strFName1.Format("%s %s %s.gif", strStk, strSijo, strName);

						strFPath0 = sbFilesDir0 + '\\' + strFName0;
						strFPath1 = sbFilesDir1a + '\\' + strFName1;
						strFPath2 = sbFilesDir2a + '\\' + strFName1;
					}
				}

				if (bName) {
					pDlFileThread = new CDlFileThread;
					pDlFileThread->m_strDataDir = m_strDataDir;
					pDlFileThread->m_strServerName = m_strServerName;
					if ((nCodeIndex & 0x1) == 0) {
						pDlFileThread->m_strObject.Format(OBJ_KABU_CHART_L, m_strObjectC, strCode);
						pDlFileThread->m_strFPath = strFPath0;
						pDlFileThread->m_strFPathC0 = strFPath1;
					} else {
						pDlFileThread->m_strObject.Format(OBJ_KABU_DAYCHART_L, m_strObjectC, strCode);
						pDlFileThread->m_strFPath = strFPath2;
					}
					pDlFileThread->m_nPort = m_nPort;
					pDlFileThread->m_nVerb = CHttpConnection::HTTP_VERB_GET;
					pDlFileThread->m_bAutoDelete = FALSE;
					if (! pDlFileThread->CreateThread()) {
						DispErrorLog("CreateThread Error\n");
						delete pDlFileThread;
						goto CleanUp;
					}
				} else
					pDlFileThread = NULL;
				ppDlFileThread[nDlFileThreadIndex] = pDlFileThread;
				pCodeIndex[nDlFileThreadIndex] = nCodeIndex;
			}

			if (i >= (int)dwMaxConnectionsPerServer  &&  bDlFileThread  &&  dwThreadExitCode == 0UL) {
				if ((j & 0x1) == 0) {
					if (! CopyFile(m_strFPath, m_strFPathC0, FALSE)) {
						DispErrorLog("銘柄チャートダウンロードファイルコピーエラー: %s: %s: %s\n", m_strFPath, m_strFPathC0, GetLastErrorMessage());
						goto CleanUp;
					}
				}
			}
		}

		if (m_pServer == NULL)
			m_pServer = Session.GetHttpConnection(m_strServerName, m_nPort);

		sbFilesDir0 = m_strDataDir + "\\Chart\\0000 FX MinuteChart";

		if (! CFile::GetStatus(sbFilesDir0, m_FileStatus)) {
			if (ForceDir(sbFilesDir0)) {
				DispErrorLog("銘柄チャートダウンロードフォルダ作成エラー: %s: %s\n", sbFilesDir0, GetLastErrorMessage());
				goto CleanUp;
			}
		}

		m_strObject.Format(OBJ_INDEX_CHART_L, m_strObjectC, "101." + m_strContractMonth0);
		strFPath0.Format("%s\\%4d%02d%02d.gif", sbFilesDir0, nYear, nMonth, nDay);
		if (DlFile(strFPath0, CHttpConnection::HTTP_VERB_GET))
			goto CleanUp;

		sbFilesDir0 = m_strDataDir + "\\Chart\\0000 TM MinuteChart";

		if (! CFile::GetStatus(sbFilesDir0, m_FileStatus)) {
			if (ForceDir(sbFilesDir0)) {
				DispErrorLog("銘柄チャートダウンロードフォルダ作成エラー: %s: %s\n", sbFilesDir0, GetLastErrorMessage());
				goto CleanUp;
			}
		}

		m_strObject.Format(OBJ_INDEX_CHART_L, m_strObjectC, "154");
		strFPath0.Format("%s\\%4d%02d%02d.gif", sbFilesDir0, nYear, nMonth, nDay);
		if (DlFile(strFPath0, CHttpConnection::HTTP_VERB_GET))
			goto CleanUp;

		sbFilesDir0 = m_strDataDir + "\\Chart\\0000 JQ MinuteChart";

		if (! CFile::GetStatus(sbFilesDir0, m_FileStatus)) {
			if (ForceDir(sbFilesDir0)) {
				DispErrorLog("銘柄チャートダウンロードフォルダ作成エラー: %s: %s\n", sbFilesDir0, GetLastErrorMessage());
				goto CleanUp;
			}
		}

		m_strObject.Format(OBJ_INDEX_CHART_L, m_strObjectC, "191");
		strFPath0.Format("%s\\%4d%02d%02d.gif", sbFilesDir0, nYear, nMonth, nDay);
		if (DlFile(strFPath0, CHttpConnection::HTTP_VERB_GET))
			goto CleanUp;

		sbFilesDir0 = m_strDataDir + "\\Chart\\0000 Ranking";

		if (! CFile::GetStatus(sbFilesDir0, m_FileStatus)) {
			if (ForceDir(sbFilesDir0)) {
				DispErrorLog("銘柄チャートダウンロードフォルダ作成エラー: %s: %s\n", sbFilesDir0, GetLastErrorMessage());
				goto CleanUp;
			}
		}

		m_strObject.Format(OBJ_RANK_TOP0, m_strObjectC);
		strFPath0.Format("%s\\%4d%02d%02d top0.html", sbFilesDir0, nYear, nMonth, nDay);
		if (DlFile(strFPath0, CHttpConnection::HTTP_VERB_GET))
			goto CleanUp;

		m_strObject.Format(OBJ_RANK_TOP1, m_strObjectC);
		strFPath0.Format("%s\\%4d%02d%02d top1.html", sbFilesDir0, nYear, nMonth, nDay);
		if (DlFile(strFPath0, CHttpConnection::HTTP_VERB_GET))
			goto CleanUp;

		m_strObject.Format(OBJ_RANK_BOTTOM0, m_strObjectC);
		strFPath0.Format("%s\\%4d%02d%02d bottom0.html", sbFilesDir0, nYear, nMonth, nDay);
		if (DlFile(strFPath0, CHttpConnection::HTTP_VERB_GET))
			goto CleanUp;

		m_strObject.Format(OBJ_RANK_BOTTOM1, m_strObjectC);
		strFPath0.Format("%s\\%4d%02d%02d bottom1.html", sbFilesDir0, nYear, nMonth, nDay);
		if (DlFile(strFPath0, CHttpConnection::HTTP_VERB_GET))
			goto CleanUp;

		m_strObject.Format(OBJ_RANK_KYUZOU0, m_strObjectC);
		strFPath0.Format("%s\\%4d%02d%02d kyuzou0.html", sbFilesDir0, nYear, nMonth, nDay);
		if (DlFile(strFPath0, CHttpConnection::HTTP_VERB_GET))
			goto CleanUp;

		m_strObject.Format(OBJ_RANK_KYUZOU1, m_strObjectC);
		strFPath0.Format("%s\\%4d%02d%02d kyuzou1.html", sbFilesDir0, nYear, nMonth, nDay);
		if (DlFile(strFPath0, CHttpConnection::HTTP_VERB_GET))
			goto CleanUp;

		m_pServer->Close();
		delete m_pServer;
		m_pServer = NULL;

		sbFilesDir0 = m_strDataDir + "\\Chart\\0000 N225 DayChart";

		if (! CFile::GetStatus(sbFilesDir0, m_FileStatus)) {
			if (ForceDir(sbFilesDir0)) {
				DispErrorLog("銘柄チャートダウンロードフォルダ作成エラー: %s: %s\n", sbFilesDir0, GetLastErrorMessage());
				goto CleanUp;
			}
		}

		strUrl = "http://ichart.finance.yahoo.com/z?s=%5EN225&t=5d&q=l&l=on&z=l&p=s&a=v&p=s";
		if (! AfxParseURL(strUrl, m_dwServiceType, m_strServerName, m_strObject, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
			DispErrorLog("URL 解析エラー: %s\n", strUrl);
			goto CleanUp;
		}

		m_pServer = Session.GetHttpConnection(m_strServerName, m_nPort);

		strFPath0.Format("%s\\%4d%02d%02d.png", sbFilesDir0, nYear, nMonth, nDay);
		if (DlFile(strFPath0, CHttpConnection::HTTP_VERB_GET))
			goto CleanUp;

		m_pServer->Close();
		delete m_pServer;
		m_pServer = NULL;

		sbFilesDir0 = m_strDataDir + "\\Chart\\0000 StopPrice";

		if (! CFile::GetStatus(sbFilesDir0, m_FileStatus)) {
			if (ForceDir(sbFilesDir0)) {
				DispErrorLog("銘柄チャートダウンロードフォルダ作成エラー: %s: %s\n", sbFilesDir0, GetLastErrorMessage());
				goto CleanUp;
			}
		}

		strUrl = "http://www.traders.co.jp/domestic_stocks/domestic_market/stop_price/stop_price.asp";
		if (! AfxParseURL(strUrl, m_dwServiceType, m_strServerName, m_strObject, m_nPort) || m_dwServiceType != INTERNET_SERVICE_HTTP) {
			DispErrorLog("URL 解析エラー: %s\n", strUrl);
			goto CleanUp;
		}

		m_pServer = Session.GetHttpConnection(m_strServerName, m_nPort);

		strFPath0.Format("%s\\%4d%02d%02d.html", sbFilesDir0, nYear, nMonth, nDay);
		if (DlFile(strFPath0, CHttpConnection::HTTP_VERB_GET))
			goto CleanUp;
	}
	catch (CException* pEx) {
		DispErrorLog("銘柄チャートダウンロードエラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
		goto CleanUp;
	}

	nRv = 0;

CleanUp:
	if (m_pServer) {
		m_pServer->Close();
		delete m_pServer;
		m_pServer = NULL;
	}
	delete [] pCodeIndex;
	for (i = 0; i < (int)dwMaxConnectionsPerServer; i ++) {
		if (pDlHtmlThread = ppDlHtmlThread[i]) {
			WaitForSingleObject(pDlHtmlThread->m_hThread, INFINITE);
			delete pDlHtmlThread;
		}
		if (pDlFileThread = ppDlFileThread[i]) {
			WaitForSingleObject(pDlFileThread->m_hThread, INFINITE);
			delete pDlFileThread;
		}
	}
	delete [] ppDlHtmlThread;
	delete [] ppDlFileThread;

	return nRv;
}

long CAutoTraderDlg::GetStockAve0()
{
	int nRv = -1;

	int k;
	int l;
	int m;
	int mmax;
	CDaoDatabase Database;
	BOOL bBeginTrans = FALSE;

	try {
		CString strFPath;
		CString strLine;
		CStringBuffer sbHtml;
		BOOL bData;
		int nPtr0;
		CHtmlTokenizer HtmlTokenizer0;
		CStringBuffer sbTag;
		COleDateTime DtCur;
		COleDateTime DtCurMinute;
		COleDateTime DtTradeStart0;
		COleDateTime DtTradeStart1;
		COleDateTime DtTradeEnd0;
		COleDateTime DtTradeEnd1o;
		int nYear;
		int nMonth;
		int nDay;
		int nCurYear;
		int nCurMonth;
		int nCurDay;
		long lPrice225;
		long lTradeCount255;
		double dPrice;
		long lKehaiSpecial;
		CKehai0 KehaiWork;
		CFunashi0 Funashi0;
		CFunashi0* pFunashi0;
		BOOL bSame;
		COleVariant pKeyArray[2];
		COleVariant var;

		DtCur = GetCurrentTimeEx();
		nCurYear = DtCur.GetYear();
		nCurMonth = DtCur.GetMonth();
		nCurDay = DtCur.GetDay();
		DtCurMinute.SetDateTime(nCurYear, nCurMonth, nCurDay, DtCur.GetHour(), DtCur.GetMinute(), DtCur.GetSecond() / TIMEUNIT * TIMEUNIT);

		nYear = m_DtDate.GetYear();
		nMonth = m_DtDate.GetMonth();
		nDay = m_DtDate.GetDay();

		DtTradeStart0.SetDateTime(nYear, nMonth, nDay, 8, 0, 0);
//		DtTradeEnd0.SetDateTime(nYear, nMonth, nDay, 11, 1, 0);
		DtTradeEnd0.SetDateTime(nYear, nMonth, nDay, 11, 31, 0);
		DtTradeStart1.SetDateTime(nYear, nMonth, nDay, 12, 5, 0);
		DtTradeEnd1o.SetDateTime(nYear, nMonth, nDay, 15, 11, 0);

		if (DtCurMinute >= DtTradeStart0  &&  DtCurMinute <= DtTradeEnd0  ||  DtCurMinute >= DtTradeStart1  &&  DtCurMinute <= DtTradeEnd1o) {
			Database.Open(m_strDBFPath);

			Database.m_pWorkspace->BeginTrans();
			bBeginTrans = TRUE;

			CDaoRecordset RsFunashi(&Database);
			RsFunashi.Open(dbOpenTable, TBL_FUNASHI0);
			RsFunashi.SetCurrentIndex(pszPrimaryKey);

			strFPath = m_strTempDir + FNAME_STOCKAVE;
			{
				CStdioFile StdioFile(strFPath, CFile::modeRead | CFile::shareDenyNone);
				while (StdioFile.ReadString(strLine))
					sbHtml += strLine + '\n';
				StdioFile.Close();
			}

			bData = FALSE;
			HtmlTokenizer0.SetHtml(sbHtml);
			if ((nPtr0 = sbHtml.Find("日")) == -1)
				goto DataCleanUp0;
			if ((nPtr0 = StrFindNoCase(sbHtml, "<table ", nPtr0 + 2)) == -1)
				goto DataCleanUp0;
			if ((nPtr0 = StrFindNoCase(sbHtml, "<td ", nPtr0 + 7)) == -1)
				goto DataCleanUp0;
			HtmlTokenizer0.m_nHtmlPtr = nPtr0;
			for (l = 0; l < 2; l ++)
				if (! HtmlTokenizer0.HtmlTok())
					goto DataCleanUp0;
			dPrice = atof(HtmlTokenizer0.m_strTag);
			nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
			if ((nPtr0 = sbHtml.Find("先", nPtr0)) == -1)
				goto DataCleanUp0;
			if ((nPtr0 = StrFindNoCase(sbHtml, "<table ", nPtr0 + 2)) == -1)
				goto DataCleanUp0;
			if ((nPtr0 = StrFindNoCase(sbHtml, "<td ", nPtr0 + 7)) == -1)
				goto DataCleanUp0;
			HtmlTokenizer0.m_nHtmlPtr = nPtr0;
			for (l = 0; l < 2; l ++)
				if (! HtmlTokenizer0.HtmlTok())
					goto DataCleanUp0;
			lPrice225 = atol(HtmlTokenizer0.m_strTag);
			bData = TRUE;

DataCleanUp0:
			if (! bData) {
				DispErrorLog("日経平均取得エラー\n");
				goto CleanUp;
			}

			sbHtml.Empty();

			strFPath = m_strTempDir + FNAME_QUOTE0;
			{
				CStdioFile StdioFile(strFPath, CFile::modeRead | CFile::shareDenyNone);
				while (StdioFile.ReadString(strLine))
					sbHtml += strLine + '\n';
				StdioFile.Close();
			}

			bData = FALSE;
			if ((nPtr0 = sbHtml.Find("数量")) == -1)
				goto DataCleanUp1;
			for (l = 0; l < 3; l ++)
				if ((nPtr0 = StrFindNoCase(sbHtml, "<tr ", nPtr0 + 1)) == -1)
					goto DataCleanUp1;
			HtmlTokenizer0.SetHtml(sbHtml);
			for (l = 0; l < 5; l ++) {
				if ((nPtr0 = StrFindNoCase(sbHtml, "<tr ", nPtr0 + 1)) == -1)
					goto DataCleanUp1;
				for (m = 0; m < 2; m ++)
					if ((nPtr0 = StrFindNoCase(sbHtml, "<td ", nPtr0 + 4)) == -1)
						goto DataCleanUp1;
				HtmlTokenizer0.m_nHtmlPtr = nPtr0;
				for (m = 0; m < 2; m ++)
					if (HtmlTokenizer0.HtmlTok() == 0)
						goto DataCleanUp1;
				KehaiWork.m_plKehaiCount[l] = atol(HtmlTokenizer0.m_strTag);
				nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
				if ((nPtr0 = StrFindNoCase(sbHtml, "<td ", nPtr0 + 1)) == -1)
					goto DataCleanUp1;
				HtmlTokenizer0.m_nHtmlPtr = nPtr0;
				for (m = 0, mmax = 2; m < mmax; m ++) {
					if (HtmlTokenizer0.HtmlTok() == 0)
						goto DataCleanUp1;
					if (m == 1  &&  HtmlTokenizer0.m_strTag[0] == '<')
						mmax = 4;
				}
				sbTag = HtmlTokenizer0.m_strTag;
				if (sbTag == "特"  ||  sbTag == "注"  ||  sbTag == "前"  ||  sbTag == "引")
					KehaiWork.m_plKehaiCount[l] = - KehaiWork.m_plKehaiCount[l];
				nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
				if ((nPtr0 = StrFindNoCase(sbHtml, "<td ", nPtr0 + 1)) == -1)
					goto DataCleanUp1;
				HtmlTokenizer0.m_nHtmlPtr = nPtr0;
				for (m = 0; m < 2; m ++)
					if (HtmlTokenizer0.HtmlTok() == 0)
						goto DataCleanUp1;
				KehaiWork.m_plKehaiPrice[l] = atol(HtmlTokenizer0.m_strTag);
				nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
			}
			for (l = 5; l < 10; l ++) {
				if ((nPtr0 = StrFindNoCase(sbHtml, "<tr ", nPtr0 + 1)) == -1)
					goto DataCleanUp1;
				for (m = 0; m < 4; m ++)
					if ((nPtr0 = StrFindNoCase(sbHtml, "<td ", nPtr0 + 4)) == -1)
						goto DataCleanUp1;
				HtmlTokenizer0.m_nHtmlPtr = nPtr0;
				for (m = 0; m < 2; m ++)
					if (HtmlTokenizer0.HtmlTok() == 0)
						goto DataCleanUp1;
				KehaiWork.m_plKehaiPrice[l] = atol(HtmlTokenizer0.m_strTag);
				nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
				if ((nPtr0 = StrFindNoCase(sbHtml, "<td ", nPtr0 + 1)) == -1)
					goto DataCleanUp1;
				HtmlTokenizer0.m_nHtmlPtr = nPtr0;
				for (m = 0, mmax = 2; m < mmax; m ++) {
					if (HtmlTokenizer0.HtmlTok() == 0)
						goto DataCleanUp1;
					if (m == 1  &&  HtmlTokenizer0.m_strTag[0] == '<')
						mmax = 4;
				}
				sbTag = HtmlTokenizer0.m_strTag;
				lKehaiSpecial = sbTag == "特"  ||  sbTag == "注"  ||  sbTag == "前"  ||  sbTag == "引"  ? -1 : 1;
				nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
				if ((nPtr0 = StrFindNoCase(sbHtml, "<td ", nPtr0 + 1)) == -1)
					goto DataCleanUp1;
				HtmlTokenizer0.m_nHtmlPtr = nPtr0;
				for (m = 0; m < 2; m ++)
					if (HtmlTokenizer0.HtmlTok() == 0)
						goto DataCleanUp1;
				KehaiWork.m_plKehaiCount[l] = atol(HtmlTokenizer0.m_strTag) * lKehaiSpecial;
				nPtr0 = HtmlTokenizer0.m_nHtmlPtr;
			}
			if ((nPtr0 = StrFindNoCase(sbHtml, "売買高", nPtr0 + 1)) == -1)
				goto DataCleanUp1;
			if ((nPtr0 = StrFindNoCase(sbHtml, "<td>", nPtr0 + 6)) == -1)
				goto DataCleanUp1;
			HtmlTokenizer0.m_nHtmlPtr = nPtr0;
			for (l = 0; l < 2; l ++)
				if (HtmlTokenizer0.HtmlTok() == 0)
					goto DataCleanUp1;
			lTradeCount255 = atol(HtmlTokenizer0.m_strTag);
			bData = TRUE;

DataCleanUp1:
			if (! bData) {
				DispErrorLog("日経平均気配値取得エラー\n");
				goto CleanUp;
			}

			bSame = TRUE;
			if (m_Mstf0Last.Lookup("101", Funashi0)) {
				if (
					Funashi0.m_lPrice != lPrice225
					||  Funashi0.m_lTradeCount != lTradeCount255
					||  Funashi0.m_dVwap != dPrice
				)
					bSame = FALSE;
				else
					for (k = 0; k < 10; k ++)
						if (
							Funashi0.m_Kehai.m_plKehaiPrice[k] != KehaiWork.m_plKehaiPrice[k]
							||  Funashi0.m_Kehai.m_plKehaiCount[k] != KehaiWork.m_plKehaiCount[k]
						) {
							bSame = FALSE;
							break;
						}
			} else
				bSame = FALSE;
			if (! bSame) {
				pKeyArray[0] = COleVariant(DtCurMinute);
				pKeyArray[1] = COleVariant("101", VT_BSTRT);
				if (RsFunashi.Seek("=", pKeyArray, 2)) {
					RsFunashi.Edit();

					k = ((long *)m_PaFunashi[0])[-1] - 1;
					pFunashi0 = (CFunashi0 *)(m_pMappingViewCell + ((long *)m_PaFunashi[0])[k]);
					pFunashi0->m_lPrice = lPrice225;
					pFunashi0->m_lTradeCount = lTradeCount255;
					pFunashi0->m_dVwap = dPrice;
					pFunashi0->m_Kehai = KehaiWork;
				} else {
					RsFunashi.AddNew();
					for (l = 0; l < 2; l ++)
						RsFunashi.SetFieldValue(l, pKeyArray[l]);

					Funashi0.m_DtDateTime = DtCurMinute;
					Funashi0.m_lPrice = lPrice225;
					Funashi0.m_lTradeCount = lTradeCount255;
					Funashi0.m_dVwap = dPrice;
					Funashi0.m_Kehai = KehaiWork;
					AddFunashi0(0, Funashi0);
				}
				RsFunashi.SetFieldValue(2, COleVariant(lPrice225));
				RsFunashi.SetFieldValue(3, COleVariant(lTradeCount255));
				RsFunashi.SetFieldValue(4, COleVariant(dPrice));
				for (l = 0; l < 10; l ++) {
					RsFunashi.SetFieldValue(5 + l, COleVariant(KehaiWork.m_plKehaiPrice[l]));
					RsFunashi.SetFieldValue(15 + l, COleVariant(KehaiWork.m_plKehaiCount[l]));
				}
				RsFunashi.Update();
				m_Mstf0Last["101"] = GetFunashi(0, ((long *)m_PaFunashi[0])[-1] - 1);
			}

			Database.m_pWorkspace->CommitTrans();
			bBeginTrans = FALSE;
		}
	}
	catch (CFileException* pEx) {
		if (pEx->m_cause != CFileException::sharingViolation)
			DispErrorLog("日経平均取得エラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
		goto CleanUp;
	}
	catch (CException* pEx) {
		DispErrorLog("日経平均取得エラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
		goto CleanUp;
	}

	nRv = 0;

CleanUp:
	if (bBeginTrans)
		Database.m_pWorkspace->Rollback();

	return nRv;
}

void CAutoTraderDlg::AddFunashi0(long* plFunashi, const CFunashi0& Funashi0)
{
	long& lFunashiCount = plFunashi[-1];
	long& lFunashi = plFunashi[lFunashiCount];
	if (lFunashi)
		*(CFunashi0 *)(m_pMappingViewCell + lFunashi) = Funashi0;
	else {
		*(CFunashi0 *)m_pMappingViewNextCell = Funashi0;
		lFunashi = m_pMappingViewNextCell - m_pMappingViewCell;
		m_pMappingViewNextCell += sizeof(CFunashi0);
	}
	lFunashiCount ++;
	m_lFunashi0Count ++;
}

void CAutoTraderDlg::AddFunashi1(long* plFunashi, const CFunashi1& Funashi1)
{
	*(CFunashi1 *)m_pMappingViewNextCell = Funashi1;
	plFunashi[plFunashi[-1] ++] = m_pMappingViewNextCell - m_pMappingViewCell;
	m_pMappingViewNextCell += sizeof(CFunashi1);
	m_lFunashi1Count ++;
}

void CAutoTraderDlg::AddFunashi2(long* plFunashi, const CFunashi2& Funashi2)
{
	*(CFunashi2 *)m_pMappingViewNextCell = Funashi2;
	plFunashi[plFunashi[-1] ++] = m_pMappingViewNextCell - m_pMappingViewCell;
	m_pMappingViewNextCell += sizeof(CFunashi2);
	m_lFunashi2Count ++;
}

void CAutoTraderDlg::AddFunashi0(int nIndex, const CFunashi0& Funashi0)
{
	AddFunashi0((long *)m_PaFunashi[nIndex], Funashi0);
}

void CAutoTraderDlg::AddFunashi1(int nIndex, const CFunashi1& Funashi1)
{
	AddFunashi1((long *)m_PaFunashi[nIndex], Funashi1);
}

void CAutoTraderDlg::AddFunashi2(int nIndex, const CFunashi2& Funashi2)
{
	AddFunashi2((long *)m_PaFunashi[nIndex], Funashi2);
}

CFunashi0 CAutoTraderDlg::GetFunashi(long* plFunashi, int nIndex)
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

CFunashi0 CAutoTraderDlg::GetFunashi(int nIndex0, int nIndex1)
{
	return GetFunashi((long *)m_PaFunashi[nIndex0], nIndex1);
}

/*
int CAutoTraderDlg::GetHiashiNice(int nHiashiIndex, const long plPrice[], const long plTradeCount[])
{
	int nRv = 0;

	return nRv;
}
*/

int CAutoTraderDlg::GetFunashiNice(int nHiashiIndex, const long plPrice[], const long plPrice255[], const long plTradeCount[], const double pdVwap[], const CKehai0 pKehai[], const CKehai0 pKehai255[], const long plKehaiPrice[], int nCurDateStartIndex, const COleDateTime* pDtCur)
{
	static int nRv = 0;

	static CString strCode;
	static short sUnit;
	static long lPrice0;
	static long lPrice2550;
	static long lTradeCount0;
	static long lTradeCount1;
	static long lTradeCount01;
	static double dVwap0;
	static double dVwap1;
	const CKehai0& Kehai0 = pKehai[0];
	const CKehai0& Kehai1 = pKehai[1];
	static long lDiff;
	static int i;
	static int j;
//	static int k;
//	static int imax;
	static long l0;
	static long l1;
	static long l2;
	static long l3;
	static long l4;
//	static double d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13;
	static double d0, d1, d13;
	static long d2, d3;
//	static BOOL b0;
//	static BOOL b1;
	static CString strSijo;
	static COleDateTime dt;
	static int nHour;
	static int nMinute;
	static BOOL bSijoJQ;
	static int nPreI;
	static int nPreI2;
	static void* pVoid;

	nRv = 0;

	strCode = m_SaHiashiCode[nHiashiIndex];
	sUnit = m_WaHiashiUnit[nHiashiIndex];
	lPrice0 = plPrice[0];
	lPrice2550 = plPrice255[0];
	lTradeCount0 = plTradeCount[0];
	lTradeCount1 = plTradeCount[1];
	lTradeCount01 = lTradeCount0 - lTradeCount1;
	dVwap0 = pdVwap[0];
	dVwap1 = pdVwap[1];
	lDiff = GetDiff(lPrice0 ? lPrice0 : Kehai0.m_plKehaiPrice[5]);
	l0 = l1 = l2 = l3 = l4 = -1L;
//	b0 = b1 = FALSE;
	strSijo = strCode.Mid(5);
	bSijoJQ = strSijo == "JQ";

	if (bSijoJQ) {
		for (j = 1; j < 5; j ++)
			if (
				Kehai0.m_plKehaiPrice[4] != pKehai[j].m_plKehaiPrice[4]
				||  Kehai0.m_plKehaiPrice[5] != pKehai[j].m_plKehaiPrice[5]
				||  Kehai0.m_plKehaiCount[4] != pKehai[j].m_plKehaiCount[4]
				||  Kehai0.m_plKehaiCount[5] != pKehai[j].m_plKehaiCount[5]
			)
				break;
		nPreI = (j == 5 ? 1 : j);
		for (j = 1; j < 5; j ++)
			if (
				pKehai[nPreI].m_plKehaiPrice[4] != pKehai[nPreI + j].m_plKehaiPrice[4]
				||  pKehai[nPreI].m_plKehaiPrice[5] != pKehai[nPreI + j].m_plKehaiPrice[5]
				||  pKehai[nPreI].m_plKehaiCount[4] != pKehai[nPreI + j].m_plKehaiCount[4]
				||  pKehai[nPreI].m_plKehaiCount[5] != pKehai[nPreI + j].m_plKehaiCount[5]
			)
				break;
		nPreI2 = nPreI + (j == 5 ? 1 : j);
		if (
			pKehai[nPreI].m_plKehaiPrice[4] >= pKehai[nPreI2].m_plKehaiPrice[4] + GetDiff(pKehai[nPreI2].m_plKehaiPrice[4] + 1L) * 2
			&&  pKehai[nPreI2].m_plKehaiPrice[3] == pKehai[nPreI2].m_plKehaiPrice[4] + GetDiff(pKehai[nPreI2].m_plKehaiPrice[4] + 1L)
			||  pKehai[nPreI].m_plKehaiPrice[5] <= pKehai[nPreI2].m_plKehaiPrice[5] - GetDiff(pKehai[nPreI2].m_plKehaiPrice[5]) * 2
			&&  pKehai[nPreI2].m_plKehaiPrice[6] == pKehai[nPreI2].m_plKehaiPrice[5] - GetDiff(pKehai[nPreI2].m_plKehaiPrice[5])
		)
			nPreI = nPreI2;
	} else
		nPreI = 1;

	const CKehai0& Kehai1a = pKehai[nPreI];

//	d0 = d1 = d6 = d7 = d8 = d9 = d10 = d11 = d12 = 0.0;
	d0 = d1 = 0.0;
	if (pDtCur)
		dt = *pDtCur;
	else
		dt = GetCurrentTimeEx();
	nHour = dt.GetHour();
	nMinute = dt.GetMinute();
	dt.SetDateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay(), nHour, nMinute, dt.GetSecond() / TIMEUNIT * TIMEUNIT);
	if (lPrice0)
		l0 = lPrice0 / lDiff;
	if (lPrice2550)
		l2 = lPrice2550 / 10L;
//	if (lTradeCount1 && lTradeCount0)
	if (lTradeCount0)
		l1 = lTradeCount01 / sUnit;
	if (pKehai255[0].m_plKehaiPrice[4])
		l3 = pKehai255[0].m_plKehaiPrice[4] / 10L;
	if (pKehai255[0].m_plKehaiPrice[5])
		l4 = pKehai255[0].m_plKehaiPrice[5] / 10L;
	if (lTradeCount1  &&  lTradeCount0  &&  lTradeCount1 != lTradeCount0  &&  dVwap1 > 0.0  &&  dVwap0 > 0.0)
		d0 = ((dVwap0 * lTradeCount0 - dVwap1 * lTradeCount1) / lTradeCount01) / lDiff;
//	if (plTradeCount[0 + 1]  &&  plTradeCount[0]  &&  plTradeCount[0 + 1] != plTradeCount[0]  &&  pdVwap[0 + 1] > 0.0  &&  pdVwap[0] > 0.0  &&  pKehai[0 + 1].m_plKehaiPrice[4]  &&  pKehai[0 + 1].m_plKehaiPrice[5])
//		d1 = ((pdVwap[0] * plTradeCount[0] - pdVwap[0 + 1] * plTradeCount[0 + 1]) / (plTradeCount[0] - plTradeCount[0 + 1]) - (double)(pKehai[0 + 1].m_plKehaiPrice[4] + pKehai[0 + 1].m_plKehaiPrice[5]) / 2) / lDiff;
	if (lTradeCount1  &&  lTradeCount0  &&  lTradeCount1 != lTradeCount0  &&  dVwap1 > 0.0  &&  dVwap0 > 0.0  &&  Kehai1a.m_plKehaiPrice[4]  &&  Kehai1a.m_plKehaiPrice[5])
		d1 = ((dVwap0 * lTradeCount0 - dVwap1 * lTradeCount1) / lTradeCount01 - (double)(Kehai1a.m_plKehaiPrice[4] + Kehai1a.m_plKehaiPrice[5]) / 2) / lDiff;
	d13 = dVwap0 / lDiff;
	for (i = 1 - 1; i >= 0; i --) {
//	for (i = nCurDateStartIndex; i >= 0; i --) {
//		d2 = d3 = d4 = d5 = 0.0;
		d2 = d3 = 0;
		if (bSijoJQ) {
			for (j = 1; j < 5; j ++)
				if (
					pKehai[i].m_plKehaiPrice[4] != pKehai[i + j].m_plKehaiPrice[4]
					||  pKehai[i].m_plKehaiPrice[5] != pKehai[i + j].m_plKehaiPrice[5]
					||  pKehai[i].m_plKehaiCount[4] != pKehai[i + j].m_plKehaiCount[4]
					||  pKehai[i].m_plKehaiCount[5] != pKehai[i + j].m_plKehaiCount[5]
				)
					break;
			nPreI = i + (j == 5 ? 1 : j);
			for (j = 1; j < 5; j ++)
				if (
					pKehai[nPreI].m_plKehaiPrice[4] != pKehai[nPreI + j].m_plKehaiPrice[4]
					||  pKehai[nPreI].m_plKehaiPrice[5] != pKehai[nPreI + j].m_plKehaiPrice[5]
					||  pKehai[nPreI].m_plKehaiCount[4] != pKehai[nPreI + j].m_plKehaiCount[4]
					||  pKehai[nPreI].m_plKehaiCount[5] != pKehai[nPreI + j].m_plKehaiCount[5]
				)
					break;
			nPreI2 = nPreI + (j == 5 ? 1 : j);
			if (
				pKehai[nPreI].m_plKehaiPrice[4] >= pKehai[nPreI2].m_plKehaiPrice[4] + GetDiff(pKehai[nPreI2].m_plKehaiPrice[4] + 1L) * 2
				&&  pKehai[nPreI2].m_plKehaiPrice[3] == pKehai[nPreI2].m_plKehaiPrice[4] + GetDiff(pKehai[nPreI2].m_plKehaiPrice[4] + 1L)
				||  pKehai[nPreI].m_plKehaiPrice[5] <= pKehai[nPreI2].m_plKehaiPrice[5] - GetDiff(pKehai[nPreI2].m_plKehaiPrice[5]) * 2
				&&  pKehai[nPreI2].m_plKehaiPrice[6] == pKehai[nPreI2].m_plKehaiPrice[5] - GetDiff(pKehai[nPreI2].m_plKehaiPrice[5])
			)
				nPreI = nPreI2;
		} else
			nPreI = i + 1;
		if (
			pKehai[nPreI].m_plKehaiPrice[4]
			&&  pKehai[nPreI].m_plKehaiPrice[5]
			&&  pdVwap[i + 1] > 0.0
			&&  pdVwap[i] > 0.0
			&&  plTradeCount[i + 1]
			&&  plTradeCount[i]
			&&  pKehai[nPreI].m_plKehaiPrice[4] != pKehai[nPreI].m_plKehaiPrice[5]
		) {
			lTradeCount01 = plTradeCount[i] - plTradeCount[i + 1];
			d2 = (long)(((pdVwap[i] * plTradeCount[i] - pdVwap[i + 1] * plTradeCount[i + 1]) - pKehai[nPreI].m_plKehaiPrice[5] * (double)lTradeCount01) / (pKehai[nPreI].m_plKehaiPrice[4] - pKehai[nPreI].m_plKehaiPrice[5]));
			d2 = (d2 + sUnit / 2) / sUnit;
			lTradeCount01 /= sUnit;
			if (d2 < 0)
				d2 = 0;
			else if (d2 > lTradeCount01)
				d2 = lTradeCount01;
			d3 = lTradeCount01 - d2;
/*
			if (pKehai[i].m_plKehaiPrice[4]) {
				k = -1;
				for (j = 0; j < 5; j ++)
					if (pKehai[i + 1].m_plKehaiPrice[j] == pKehai[i].m_plKehaiPrice[4]) {
						k = j;
						break;
					}
				d4 = (double)labs(pKehai[i].m_plKehaiCount[4]);
				if (k != -1)
					d4 -= (double)labs(pKehai[i + 1].m_plKehaiCount[k]);
				switch (k) {
				case 4:
					d4 += d2;
					break;
				case 5:
					d4 += d3;
				}
				d4 /= sUnit;
			} else
				b0 = TRUE;
			if (pKehai[i].m_plKehaiPrice[5]) {
				k = -1;
				for (j = 5; j < 10; j ++)
					if (pKehai[i + 1].m_plKehaiPrice[j] == pKehai[i].m_plKehaiPrice[5]) {
						k = j;
						break;
					}
				d5 = (double)labs(pKehai[i].m_plKehaiCount[5]);
				if (k != -1)
					d5 -= (double)labs(pKehai[i + 1].m_plKehaiCount[k]);
				switch (k) {
				case 4:
					d5 += d2;
					break;
				case 5:
					d5 += d3;
				}
				d5 /= sUnit;
			} else
				b1 = TRUE;
			d2 /= sUnit;
			d3 /= sUnit;
			d6 += d2;
			d7 += d3;
			d8 += d4;
			d9 += d5;
		} else {
			d6 = d7 = d8 = d9 = 0.0;
			break;
*/
		}
	}
/*
	if (b0)
		d8 = 0.0;
	if (b1)
		d9 = 0.0;
	d6 /= 5;
	d7 /= 5;
	d8 /= 5;
	d9 /= 5;
	d10 = d2 - d4;
	d11 = d3 - d5;
	d12 = d10 - d11;
*/

	static long lNiceLockOn;
	lNiceLockOn = 0L;
//	if (nHour >= 9  &&  nHour < 11  ||  nHour == 12  &&  nMinute >= 30  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 15) {
	if (nHour >= 9  &&  nHour < 11  ||  nHour == 11  &&  nMinute < 30  ||  nHour == 12  &&  nMinute >= 30  ||  nHour >= 13  &&  nHour < 15  ||  nHour == 15  &&  nMinute < 15) {
		if (m_nExecMode == 1)
			lNiceLockOn = 1L;
//		else {
/**
			for (i = 0, imax = m_UiaKabuHiashiIndex.GetSize(); i < imax; i ++) {
				j = m_UiaKabuHiashiIndex[i];
				if (m_SaHiashiCode[j] == strCode)
					break;
			}
			if (i == imax)
				for (i = 0, imax = m_SaNiceCode.GetSize(); i < imax; i ++)
					if (m_SaNiceCode[i] == strCode) {
						lNiceLockOn = m_DwaNiceLockOn[i];
*/
/*
						long lNiceLockOffH = lNiceLockOn;
						long lNiceLockOffL = lNiceLockOn;

						for (j = 0; j < LOCKOFF_H_DIFF; j ++)
							lNiceLockOffH += GetDiff(lNiceLockOffH + 1L);

						for (j = 0; j < LOCKOFF_L_DIFF; j ++)
							lNiceLockOffL -= GetDiff(lNiceLockOffL);

						if (Kehai0.m_plKehaiPrice[5] >= lNiceLockOffH  ||  Kehai0.m_plKehaiPrice[5] <= lNiceLockOffL) {
							((CButton *)GetDlgItem(IDC_CHECK10 + i))->SetCheck(0);
							Check10(i);
							lNiceLockOn = 0L;
						}
*/
/*
						break;
					}
**/
/*
			if (m_MstpSelCode.Lookup(strCode, pVoid))
				lNiceLockOn = 1L;
		}
*/
	}

	static long nRvC;
	static long lCurKehaiPrice;
	static long lKehaiPower;
	static long lKehaiCountAve1;
	static BOOL pbCurKehaiPriceHold[2];
	nRvC = 0;
	lCurKehaiPrice = lKehaiPower = lKehaiCountAve1 = 0L;
	if (lNiceLockOn) {
		static long lCurKehaiPriceH;
		static long lCurKehaiPriceL;
		static long lCurKehaiPriceHL;
		static long lCurKehaiPriceC;
		for (i = 2; i >= 1; i --) {
			lCurKehaiPriceHL = 0L;
			pbCurKehaiPriceHold[i - 1] = TRUE;
//			lCurKehaiPrice = plKehaiPrice[i];
			lCurKehaiPrice = plKehaiPrice[20 / TIMEUNIT + i];
			lCurKehaiPriceH = lCurKehaiPrice + GetDiff(lCurKehaiPrice + 1L);
			lCurKehaiPriceL = lCurKehaiPrice - GetDiff(lCurKehaiPrice);
//			for (j = i + 1; j < FUNASHI_LONG_COUNT; j ++) {
			for (j = 20 / TIMEUNIT + i + 1; j < FUNASHI_LONG_COUNT; j ++) {
				if (pKehai[j].m_plKehaiPrice[4] == pKehai[j].m_plKehaiPrice[5] + GetDiff(pKehai[j].m_plKehaiPrice[5] + 1L))
					if (labs(pKehai[j].m_plKehaiCount[4]) < labs(pKehai[j].m_plKehaiCount[5]))
						lCurKehaiPriceC = pKehai[j].m_plKehaiPrice[4];
					else
						lCurKehaiPriceC = pKehai[j].m_plKehaiPrice[5];
				else
					lCurKehaiPriceC = pKehai[j].m_plKehaiPrice[5] + GetDiff(pKehai[j].m_plKehaiPrice[5] + 1L);
				if (lCurKehaiPriceHL == 0L  &&  lCurKehaiPriceC != lCurKehaiPrice  &&  lCurKehaiPriceC <= lCurKehaiPriceH  &&  lCurKehaiPriceC >= lCurKehaiPriceL)
					lCurKehaiPriceHL = lCurKehaiPriceC;
				if (lCurKehaiPriceC != lCurKehaiPrice  &&  lCurKehaiPriceC != lCurKehaiPriceHL) {
					pbCurKehaiPriceHold[i - 1] = FALSE;
					break;
				}
			}
		}

		if (m_nExecMode == 1) {
			static long lMaxKehaiPrice;
			static long lMinKehaiPrice;
			static long lKehaiPriceRange;
			static long lSellKehaiPriceRange;
			static long lBuyKehaiPriceRange;
			static long lSumSellKehaiCount;
			static long lSumBuyKehaiCount;
			static long lKehaiPowerCount;

			lMaxKehaiPrice = lMinKehaiPrice = 0L;
			for (i = 0; i < 5; i ++)
				if (lMaxKehaiPrice = Kehai0.m_plKehaiPrice[i])
					break;
			for (i = 9; i >= 5; i --)
				if (lMinKehaiPrice = Kehai0.m_plKehaiPrice[i])
					break;

			if (lMaxKehaiPrice && lMinKehaiPrice) {
				lKehaiPriceRange = __min(lMaxKehaiPrice - Kehai0.m_plKehaiPrice[4], Kehai0.m_plKehaiPrice[5] - lMinKehaiPrice);
				lSellKehaiPriceRange = Kehai0.m_plKehaiPrice[4] + lKehaiPriceRange;
				lBuyKehaiPriceRange = Kehai0.m_plKehaiPrice[5] - lKehaiPriceRange;
				lSumSellKehaiCount = lSumBuyKehaiCount = 0L;
				for (i = 0; i < 5; i ++)
					if (Kehai0.m_plKehaiPrice[i] <= lSellKehaiPriceRange)
						lSumSellKehaiCount += labs(Kehai0.m_plKehaiCount[i]);
				for (i = 5; i < 10; i ++)
					if (Kehai0.m_plKehaiPrice[i] >= lBuyKehaiPriceRange)
						lSumBuyKehaiCount += labs(Kehai0.m_plKehaiCount[i]);
				lKehaiPowerCount = lSumBuyKehaiCount - lSumSellKehaiCount;
				if (lKehaiPowerCount <= 0) {
					lKehaiPower = lSumSellKehaiCount == 0 ? 0 : 64 * lKehaiPowerCount / lSumSellKehaiCount;
				} else {
					lKehaiPower = lSumBuyKehaiCount == 0 ? 0 : 64 * lKehaiPowerCount / lSumBuyKehaiCount;
				}
				lKehaiPowerCount /= sUnit;
			}
		}

		j = 0;
		for (i = 5; i < 10; i ++)
			if (Kehai1.m_plKehaiCount[i]) {
				lKehaiCountAve1 += labs(Kehai1.m_plKehaiCount[i]);
				j ++;
			}
		if (j)
			lKehaiCountAve1 /= j;

		if (pbCurKehaiPriceHold[0] || pbCurKehaiPriceHold[1]) {
			long lKehaiCountAve2 = 0L;
			if (pbCurKehaiPriceHold[1]) {
				j = 0;
				for (i = 5; i < 10; i ++)
					if (pKehai[2].m_plKehaiCount[i]) {
						lKehaiCountAve2 += labs(pKehai[2].m_plKehaiCount[i]);
						j ++;
					}
				if (j)
					lKehaiCountAve2 /= j;
			}

#if 0
//			long lKehai0Price5Up;
			if (
/*
				Kehai0.m_plKehaiPrice[4]
				&&  Kehai0.m_plKehaiPrice[5] == Kehai0.m_plKehaiPrice[6] + GetDiff(Kehai0.m_plKehaiPrice[6] + 1L)
				&&  Kehai0.m_plKehaiCount[4] / sUnit >= m_lCashZan / Kehai0.m_plKehaiPrice[4]
				&&  (
					Kehai0.m_plKehaiPrice[4] == (lKehai0Price5Up = Kehai0.m_plKehaiPrice[5] + GetDiff(Kehai0.m_plKehaiPrice[5] + 1L))
					&&  Kehai0.m_plKehaiCount[4] < Kehai0.m_plKehaiCount[5]
					&&  (
						pbCurKehaiPriceHold[0]
//						&&  Kehai0.m_plKehaiCount[0] + Kehai0.m_plKehaiCount[1] + Kehai0.m_plKehaiCount[2] < lKehaiCountAve1 * 9
						&& (
							Kehai0.m_plKehaiCount[5] >= lKehaiCountAve1 * 3
							&&  Kehai0.m_plKehaiCount[5] >= labs(Kehai1.m_plKehaiCount[5]) * 2
							&&  Kehai0.m_plKehaiPrice[5] >= Kehai1.m_plKehaiPrice[5]
							||  Kehai0.m_plKehaiCount[5] >= lKehaiCountAve1 * 3 / 2
							&&  (
								Kehai0.m_plKehaiCount[6] >= lKehaiCountAve1
								||  Kehai0.m_plKehaiPrice[6] == Kehai0.m_plKehaiPrice[7] + GetDiff(Kehai0.m_plKehaiPrice[7] + 1L)
								&&  Kehai0.m_plKehaiCount[6] >= lKehaiCountAve1 / 2
								&&  Kehai0.m_plKehaiCount[7] >= lKehaiCountAve1
							)
							&&  (
								Kehai0.m_plKehaiPrice[5] == Kehai1.m_plKehaiPrice[5]
								&&  Kehai0.m_plKehaiCount[5] >= labs(Kehai1.m_plKehaiCount[5]) * 2
								||  Kehai0.m_plKehaiPrice[5] > Kehai1.m_plKehaiPrice[5]
							)
						)
						|| pbCurKehaiPriceHold[1]
//						&&  Kehai0.m_plKehaiCount[0] + Kehai0.m_plKehaiCount[1] + Kehai0.m_plKehaiCount[2] < lKehaiCountAve2 * 9
						&& (
							Kehai0.m_plKehaiCount[5] >= lKehaiCountAve2 * 3
							&&  Kehai0.m_plKehaiCount[5] >= labs(pKehai[2].m_plKehaiCount[5]) * 2
							&&  Kehai0.m_plKehaiPrice[5] >= pKehai[2].m_plKehaiPrice[5]
							||  Kehai0.m_plKehaiCount[5] >= lKehaiCountAve2 * 3 / 2
							&&  (
								Kehai0.m_plKehaiCount[6] >= lKehaiCountAve2
								||  Kehai0.m_plKehaiPrice[6] == Kehai0.m_plKehaiPrice[7] + GetDiff(Kehai0.m_plKehaiPrice[7] + 1L)
								&&  Kehai0.m_plKehaiCount[6] >= lKehaiCountAve2 / 2
								&&  Kehai0.m_plKehaiCount[7] >= lKehaiCountAve2
							)
							&&  (
								Kehai0.m_plKehaiPrice[5] == pKehai[2].m_plKehaiPrice[5]
								&&  Kehai0.m_plKehaiCount[5] >= labs(pKehai[2].m_plKehaiCount[5]) * 2
								||  Kehai0.m_plKehaiPrice[5] > pKehai[2].m_plKehaiPrice[5]
							)
						)
					)
					||  (
						Kehai0.m_plKehaiPrice[4] == lKehai0Price5Up
						||  Kehai0.m_plKehaiPrice[4] == lKehai0Price5Up + GetDiff(lKehai0Price5Up + 1L)
					)
//					&&  Kehai0.m_plKehaiCount[0] + Kehai0.m_plKehaiCount[1] + Kehai0.m_plKehaiCount[2] < lKehaiCountAve1 * 9
//					&&  Kehai0.m_plKehaiCount[3] < lKehaiCountAve1 * 3
					&&  Kehai0.m_plKehaiCount[4] >= 0
					&&  Kehai0.m_plKehaiCount[5] >= 0
					&&  pbCurKehaiPriceHold[0]
					&&  (long)d2 >= lKehaiCountAve1 * 2
					&&  (long)d3 <= 0L
				)
*/
				plKehaiPrice[0]
				&&  plKehaiPrice[1]
				&&  plKehaiPrice[20 / TIMEUNIT - 1]
				&&  plKehaiPrice[0] > plKehaiPrice[1]
				&&  plKehaiPrice[0] >= plKehaiPrice[20 / TIMEUNIT - 1] + GetDiff(plKehaiPrice[20 / TIMEUNIT - 1] + 1L) * 2
				&&  GetDiff(plKehaiPrice[20 / TIMEUNIT - 1] + 1L) == GetDiff(m_DwaHiashiPreEndPrice[nHiashiIndex])
			) {
/*
				CDWordArray* pDwaPlice = (CDWordArray *)m_PaFunashiPrice[nHiashiIndex];
				CKehaiArray* pKaKehai = (CKehaiArray *)m_PaFunashiKehai[nHiashiIndex];
				int nFunashiPaIndex = m_UiaFunashiPaIndex[nHiashiIndex];
				long lPrice;
				long lHighPrice = 0L;
				long lLowPrice = 0L;
				int nHighIndex;
				int nLowIndex;
				long lDiff;
*/
				long lDiff5;
/*
				CUIntArray UiaPeakIndex;
				CDWordArray DwaHighPrice;
				CDWordArray DwaLowPrice;
//				int nPeakCount = 0;
				int nUpDown = 0;
				for (i = imax = 0; i <= nFunashiPaIndex; i ++)
					if (pDwaPlice->GetAt(i)) {
						imax = i;
						break;
					}
//				for (i = nFunashiPaIndex; i >= imax  &&  nPeakCount < 6; i --) {
				for (i = nFunashiPaIndex; i >= imax; i --) {
//					lPrice = pDwaPlice->GetAt(i);
					if (pKaKehai->GetAt(i).m_plKehaiPrice[4] == pKaKehai->GetAt(i).m_plKehaiPrice[5] + GetDiff(pKaKehai->GetAt(i).m_plKehaiPrice[5] + 1L))
						if (labs(pKaKehai->GetAt(i).m_plKehaiCount[4]) < labs(pKaKehai->GetAt(i).m_plKehaiCount[5]))
							lPrice = pKaKehai->GetAt(i).m_plKehaiPrice[4];
						else
							lPrice = pKaKehai->GetAt(i).m_plKehaiPrice[5];
					else
						lPrice = pKaKehai->GetAt(i).m_plKehaiPrice[5] + GetDiff(pKaKehai->GetAt(i).m_plKehaiPrice[5] + 1L);
					if (lHighPrice == 0L) {
						lHighPrice = lLowPrice = lPrice;
						lDiff = GetDiff(lPrice);
						lDiff5 = lDiff * 5;
					}
					if (lPrice > lHighPrice) {
						lHighPrice = lPrice;
						nHighIndex = i;
					} else if (lPrice < lLowPrice) {
						lLowPrice = lPrice;
						nLowIndex = i;
					}
					if (lHighPrice >= lLowPrice + lDiff5) {
						if (nUpDown <= 0  &&  lPrice == lHighPrice) {
							UiaPeakIndex.Add(- nLowIndex);
							DwaLowPrice.Add(lLowPrice);
//							nPeakCount ++;
						} else if (nUpDown >= 0  &&  lPrice == lLowPrice) {
							UiaPeakIndex.Add(nHighIndex);
							DwaHighPrice.Add(lHighPrice);
//							nPeakCount ++;
						}
						if (lPrice == lHighPrice) {
							lLowPrice = lPrice;
							nUpDown = 1;
						} else {
							lHighPrice = lPrice;
							nUpDown = -1;
						}
					}
				}
//				if (i < imax  &&  UiaPeakIndex.GetSize())
				if (UiaPeakIndex.GetSize())
					if ((long)UiaPeakIndex[UiaPeakIndex.GetUpperBound()] > 0) {
						UiaPeakIndex.Add(- imax);
						DwaLowPrice.Add(lPrice);
					} else {
						UiaPeakIndex.Add(imax);
						DwaHighPrice.Add(lPrice);
					}
				if (m_nExecMode == 1) {
					for (i = UiaPeakIndex.GetUpperBound(); i >= 0; i --)
						TRACE("%d ", UiaPeakIndex[i]);
					TRACE("\n");
					if (UiaPeakIndex[0] < 0)
						TRACE("  ");
					for (i = DwaHighPrice.GetUpperBound(); i >= 0; i --)
						TRACE("%3ld ", DwaHighPrice[i] / lDiff);
					TRACE("\n");
					if (UiaPeakIndex[0] > 0)
						TRACE("  ");
					for (i = DwaLowPrice.GetUpperBound(); i >= 0; i --)
						TRACE("%3ld ", DwaLowPrice[i] / lDiff);
					TRACE("\n");
				}
*/
					if (
//					(
/*
						DwaLowPrice.GetSize() >= 2  &&  DwaLowPrice[1] < DwaLowPrice[0]
						||  UiaPeakIndex.GetSize() >= 1  &&  DwaHighPrice.GetSize() >= 3  &&  DwaLowPrice.GetSize() >= 3
						&&  (
							UiaPeakIndex[0] > 0  &&  (DwaHighPrice[2] < DwaHighPrice[0]  ||  DwaHighPrice[1] < DwaHighPrice[0])  &&  DwaLowPrice[2] < DwaLowPrice[0]
							||  UiaPeakIndex[0] < 0  &&  (DwaHighPrice[2] < DwaHighPrice[1]  ||  DwaHighPrice[2] < DwaHighPrice[0])  &&  DwaLowPrice[2] < DwaLowPrice[0]
						)
*/
//					)
//					&&  Kehai0.m_plKehaiPrice[4] <= (long)DwaLowPrice[0] / lDiff5 * lDiff5 + lDiff * 10
//					UiaPeakIndex.GetSize() >= 1  &&  UiaPeakIndex[0] < 0  &&  DwaLowPrice.GetSize() >= 2  &&  DwaLowPrice[1] < DwaLowPrice[0]
					1
				) {
					long lPreEndPrice;
					long lStopHighPrice;
					lPreEndPrice = m_DwaHiashiPreEndPrice[nHiashiIndex];
					if (lPreEndPrice == 0L)
						lPreEndPrice = m_DwaHiashiStartPrice[nHiashiIndex];
					lStopHighPrice = lPreEndPrice + m_DwaHiashiStopDiff[nHiashiIndex];
					lDiff5 = GetDiff(lStopHighPrice) * 5;
					if (Kehai0.m_plKehaiPrice[4] < lStopHighPrice / lDiff5 * lDiff5)
						nRvC |= 0x10;
				}
			}
#endif
		}
	}

//	if (m_bLog && (nHour == 8  &&  nMinute >= 20  ||  nHour >= 9  ||  strSijo != "T") && (nHour < 15  ||  (strSijo == "T"  ||  strSijo == "JQ")  &&  nMinute < 1  ||  (strSijo == "NG"  ||  strSijo == "O")  &&  nMinute < 11  ||  strSijo == "M")) {
//	if (m_bLog && (nHour == 8  &&  nMinute >= 20  ||  nHour >= 9  ||  strSijo != "T") && (nHour < 15  ||  (strSijo == "T")  &&  nMinute < 1  ||  (strSijo == "NG"  ||  strSijo == "O"  ||  strSijo == "JQ")  &&  nMinute < 11  ||  strSijo == "M")) {
	if (m_bLog && (nHour < 15  ||  (strSijo == "T")  &&  nMinute < 1  ||  (strSijo == "NG"  ||  strSijo == "O"  ||  strSijo == "JQ")  &&  nMinute < 11  ||  strSijo == "M")) {
		m_bDispDebugLog = TRUE;

		CStringBuffer sb =
			StrFormat(
//				"%s %4ld %4ld %4ld %4ld %4ld %6.1f %5.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f  ",
//				dt.Format("%H:%M:%S"), l2, l3, l4, l0, l1, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9
//				"%s %4ld %4ld %4ld %4ld %4ld %6.1f %5.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f  ",
//				dt.Format("%H:%M:%S"), l2, l3, l4, l0, l1, d0, d1, d2, d3, d4, d5, d10, d11, d12
//				"%s %4ld %4ld %4ld %4ld %4ld %6.1f %5.1f %6.1f %6.1f %6.1f %6.1f %6.1f  ",
//				dt.Format("%H:%M:%S"), l2, l3, l4, l0, l1, d0, d1, d2, d3, d4, d5, d12
				"%s %4ld %4ld %4ld %6.1f %4ld %4ld %6.1f %5.1f %4ld %4ld  ",
				dt.Format("%H:%M:%S"), l2, l3, l4, d13, l0, l1, d0, d1, d2, d3
			);
//		for (i = 3; i < 7; i ++) {
		for (i = 0; i < 10; i ++) {
			if (i == 5) {
				l0 = 0L;
				if (Kehai1.m_plKehaiPrice[i]  &&  Kehai0.m_plKehaiPrice[i])
					l0 = (Kehai0.m_plKehaiPrice[i] - Kehai1.m_plKehaiPrice[i]) / lDiff;
				sb += StrFormat("%3ld ", l0);
			}
			sb += StrFormat("%4ld ", Kehai0.m_plKehaiPrice[i] / lDiff);
			if (i == 4) {
				l0 = 0L;
				if (Kehai1.m_plKehaiPrice[i]  &&  Kehai0.m_plKehaiPrice[i])
					l0 = (Kehai0.m_plKehaiPrice[i] - Kehai1.m_plKehaiPrice[i]) / lDiff;
				sb += StrFormat("%3ld ", l0);
				l0 = 0L;
				if (Kehai0.m_plKehaiPrice[i]  &&  Kehai0.m_plKehaiPrice[i + 1])
					l0 = (Kehai0.m_plKehaiPrice[i] - Kehai0.m_plKehaiPrice[i + 1]) / lDiff;
				sb += StrFormat("%2ld ", l0);
			}
		}
		sb += " ";
//		for (i = 3; i < 7; i ++) {
		for (i = 0; i < 10; i ++) {
			if (i == 4  ||  i == 5)
				sb += StrFormat("%5ld ", Kehai0.m_plKehaiCount[i] / sUnit);
			else
				sb += StrFormat("%4ld ", Kehai0.m_plKehaiCount[i] / sUnit);
			if (i == 4)
				sb += "| ";
		}
		sb.TrimRight();
		sb += StrFormat(" : %3ld %3ld %3ld", plKehaiPrice[0] / lDiff, lKehaiCountAve1 / sUnit, lKehaiPower);
//		if (nRvC)
//			sb += " ◆";
		DispLog(sb + '\n');

		m_bDispDebugLog = FALSE;
	}
	if (m_nExecMode != 1)
		nRv = nRvC;

	return nRv;
}

int CAutoTraderDlg::HiashiAnalyze(const COleDateTime* pDtCur, LPCTSTR lpszCode, int nMode, int nIndex)
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
	COleDateTime DtPreDate;
	CDaoDatabase Database;
	BOOL bBeginTrans = FALSE;
#ifndef SKIP_FUNASHIANALYZE
	int nHour;
	int nDayOfWeek;
#endif

	m_pServer = NULL;

	DtCur = pDtCur ? *pDtCur : GetCurrentTimeEx();
	DtDate.SetDate(DtCur.GetYear(), DtCur.GetMonth(), DtCur.GetDay());
//	DtStartDate = DtDate - COleDateTimeSpan(60, 0, 0, 0);
	DtStartDate = DtDate - COleDateTimeSpan(4, 0, 0, 0);

	if (! nMode) {
		ZeroMemory(m_pMappingViewOffset, m_dwMemMapAllPaSize);
		ZeroMemory(m_pMappingViewCell, m_dwMemMapCellSize);
		m_PaFunashi.RemoveAll();
		m_pMappingViewNextCell = m_pMappingViewCell;
		m_lFunashi0Count = m_lFunashi1Count = m_lFunashi2Count = 0L;

		m_SaHiashiCode.RemoveAll();
		m_SaHiashiName.RemoveAll();
		m_SaHiashiType.RemoveAll();
		m_WaHiashiUnit.RemoveAll();
		m_UiaHiashiNice.RemoveAll();
		m_DwaHiashiPreEndPrice.RemoveAll();
		m_DwaHiashiPreEndTradeCount.RemoveAll();
		m_DwaHiashiPriceDiffAve.RemoveAll();
		m_DwaHiashiStartPrice.RemoveAll();
		m_DwaHiashiStopDiff.RemoveAll();
		m_DwaHiashiBuyTotalPrice.RemoveAll();
		m_DwaHiashiBuyUnitCount.RemoveAll();
	} else if (nMode == 2) {
		long* plFunashi = (long *)m_PaFunashi[nIndex];
		m_lFunashi0Count -= plFunashi[-1];
		plFunashi[-1] = 0;

		m_MstpHiashiCode.RemoveKey(m_SaHiashiCode[nIndex]);
	}

	try
	{
		CString strCode;
		CString strCurCode;
		CStringBuffer sbSql;
		COleVariant pKeyArray[2];
		COleVariant var;
		long lHighPrice;
		long lLowPrice;
		long plPrice[HIASHI_LONG_COUNT + HIASHI_SHORT_COUNT];
		long plTradeCount[HIASHI_LONG_COUNT + HIASHI_SHORT_COUNT];
		long lPreEndPrice;
		long lPreEndTradeCount;
		long lHiashiStartPrice;
		long lPriceDiffSum;

		Database.Open(m_strDBFPath);

		Database.m_pWorkspace->BeginTrans();
		bBeginTrans = TRUE;

		CDaoRecordset RsInfo(&Database);

		if (m_nExecMode) {
			CDaoRecordset RsHiashiPreDate(&Database);
			RsHiashiPreDate.Open(dbOpenTable, TBL_HIASHI);
			RsHiashiPreDate.SetCurrentIndex(pszPrimaryKey);

			pKeyArray[0] = COleVariant(DtDate);
			if (RsHiashiPreDate.Seek("<", pKeyArray, 2)) {
				RsHiashiPreDate.GetFieldValue(0, var);
				DtPreDate = var.date;
			}
		}

		if (lpszCode)
			sbSql = StrFormat(" WHERE " FLD_IN_CODE " = '%s'", lpszCode);
		else
			if (imax = m_SaSelCode.GetSize()) {
				sbSql = " WHERE " FLD_IN_CODE " IN (";
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
					"%s"
					" ORDER BY " FLD_IN_CODE,
					sbSql
				),
				dbForwardOnly
			);

		if (! nMode) {
			m_SaHiashiCode.Add("101");
			m_SaHiashiName.Add("日経平均225先物");
			m_SaHiashiType.Add(pszEmpty);
			m_WaHiashiUnit.Add(1);
		}

		if (sbSql.GetLength()) {
			while (! RsInfo.IsEOF()) {
				if (nMode == 2) {
					RsInfo.GetFieldValue(0, var);
					m_SaHiashiCode[nIndex] = V_BSTRT((LPVARIANT)var);

					RsInfo.GetFieldValue(1, var);
					m_SaHiashiName[nIndex] = V_BSTRT((LPVARIANT)var);

					RsInfo.GetFieldValue(3, var);
					m_SaHiashiType[nIndex] = V_BSTRT((LPVARIANT)var);

					RsInfo.GetFieldValue(4, var);
					m_WaHiashiUnit[nIndex] = var.iVal;
				} else {
					RsInfo.GetFieldValue(0, var);
					m_SaHiashiCode.Add(V_BSTRT((LPVARIANT)var));

					RsInfo.GetFieldValue(1, var);
					m_SaHiashiName.Add(V_BSTRT((LPVARIANT)var));

					RsInfo.GetFieldValue(3, var);
					m_SaHiashiType.Add(V_BSTRT((LPVARIANT)var));

					RsInfo.GetFieldValue(4, var);
					m_WaHiashiUnit.Add(var.iVal);
				}

				RsInfo.MoveNext();
			}

			RsInfo.Close();
		}

		jmax = m_SaHiashiCode.GetSize();

		if (nMode != 2) {
			m_UiaHiashiNice.SetSize(jmax);
			m_DwaHiashiPreEndPrice.SetSize(jmax);
			m_DwaHiashiPreEndTradeCount.SetSize(jmax);
			m_DwaHiashiPriceDiffAve.SetSize(jmax);
			m_DwaHiashiStartPrice.SetSize(jmax);
			m_DwaHiashiStopDiff.SetSize(jmax);
			m_DwaHiashiBuyTotalPrice.SetSize(jmax);
			m_DwaHiashiBuyUnitCount.SetSize(jmax);

			for (i = nMode ? jmax - 1 : 0; i < jmax; i ++)
				m_PaFunashi.Add(m_pMappingViewOffset + MEMMAPPASIZE * i + sizeof(long));
		}

//		if (m_nExecMode != 1)
//			m_Edit16.GetWindowText(m_strLogCode);

		CDaoRecordset RsHiashi(&Database);
		if (lpszCode)
			sbSql = StrFormat(" AND " FLD_HI_CODE " = '%s'", lpszCode);
		else
			if (imax = m_SaSelCode.GetSize()) {
				sbSql = " AND " FLD_HI_CODE " IN (";
				for (i = 0, imax = m_SaSelCode.GetSize(); i < imax; i ++) {
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
					"SELECT *"
					" FROM " TBL_HIASHI
					" WHERE "
						FLD_HI_DATE " >= #%s#"
						" AND " FLD_HI_DATE " <= #%s#"
						"%s"
					" ORDER BY "
						FLD_HI_CODE ", "
						FLD_HI_DATE " DESC",
					DtStartDate.Format("%Y/%m/%d"), DtDate.Format("%Y/%m/%d"),
					sbSql
				),
				dbForwardOnly
			);

			switch (nMode) {
			case 0:
				i = 0;
				break;
			case 1:
				i = jmax - 1;
				break;
			default:
				i = nIndex;
				jmax = nIndex + 1;
			}
			for (; i < jmax; i ++) {
				strCode = m_SaHiashiCode[i];

//				m_bLog = strCode == m_strLogCode;
//if (m_nExecMode == 1  &&  m_strLogCode.GetLength()  &&  ! m_bLog) continue;

				lHiashiStartPrice = lPriceDiffSum = 0L;

				for (j = k = 0; j < HIASHI_LONG_COUNT + HIASHI_SHORT_COUNT; ) {
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
							lHighPrice = var.lVal;

							RsHiashi.GetFieldValue(4, var);
							lLowPrice = var.lVal;

							RsHiashi.GetFieldValue(5, var);
							plPrice[j] = var.lVal;

							RsHiashi.GetFieldValue(6, var);
							plTradeCount[j] = var.lVal;

							if (j < HIASHI_LONG_COUNT) {
//							if (j < HIASHI_SHORT_COUNT) {
								lPriceDiffSum += (lHighPrice - lLowPrice) / GetDiff(lHighPrice);
								k ++;
							}

							j ++;
						}
					}

					RsHiashi.MoveNext();
				}

// 				m_UiaHiashiNice[i] = j == HIASHI_LONG_COUNT + HIASHI_SHORT_COUNT ? GetHiashiNice(i, plPrice, plTradeCount, HIASHI_LONG_COUNT, HIASHI_SHORT_COUNT) : 0;
				m_UiaHiashiNice[i] = 0;

				if (j) {
					lPreEndPrice = plPrice[0];
					lPreEndTradeCount = plTradeCount[0];

					m_DwaHiashiPriceDiffAve[i] = lPriceDiffSum / k;
				} else
					lPreEndPrice = lPreEndTradeCount = 0L;
				m_DwaHiashiPreEndPrice[i] = lPreEndPrice;
				m_DwaHiashiPreEndTradeCount[i] = lPreEndTradeCount;
				m_DwaHiashiStartPrice[i] = lHiashiStartPrice;
				m_DwaHiashiStopDiff[i] = GetStopDiff(lPreEndPrice);
			}
		}

		Database.m_pWorkspace->CommitTrans();
		bBeginTrans = FALSE;
	}
	catch (CException* pEx) {
		DispErrorLog("銘柄日足データ分析エラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
		goto CleanUp;
	}

	switch (nMode) {
	case 0:
		m_MstpHiashiCode.RemoveAll();
		for (i = 0, imax = m_SaHiashiCode.GetSize(); i < imax; i ++)
			m_MstpHiashiCode[m_SaHiashiCode[i]] = (void *)i;
		break;
	case 1:
		m_MstpHiashiCode[lpszCode] = (void *)m_SaHiashiCode.GetUpperBound();
		break;
	default:
		m_MstpHiashiCode[lpszCode] = (void *)nIndex;
	}

#ifndef SKIP_FUNASHIANALYZE
	if (! m_nExecMode) {
		DtCur = GetCurrentTimeEx();
		nHour = DtCur.GetHour();
		nDayOfWeek = DtCur.GetDayOfWeek();
		if (nDayOfWeek >= 2  &&  nDayOfWeek <= 6  &&  nHour >= 2  &&  nHour < 8) {
			DtDate = m_DtPreDate;
			DtPreDate = m_DtPrePreDate;
		} else {
			DtDate = m_DtDate;
			DtPreDate = m_DtPreDate;
		}
	}
	if (m_nExecMode == 1) {
		if (! m_bOnInitDialog) {
			if (! nMode)
				if (FunashiAnalyze(1, &DtDate, &DtPreDate, "101"))
					goto CleanUp;
			if (FunashiAnalyze(1, &DtDate, &DtPreDate, lpszCode))
				goto CleanUp;
		}
	} else
		if (FunashiAnalyze(1, &DtDate, &DtPreDate, lpszCode))
			goto CleanUp;
#endif

	jmax = m_SaDlCode.GetSize();

	m_UiaDlHiashiIndex.RemoveAll();
	m_UiaDlHiashiIndex.SetSize(jmax);

	for (i = 0, imax = m_SaHiashiCode.GetSize(); i < imax; i ++) {
		for (j = 0; j < jmax; j ++)
			if (m_SaDlCode[j] == m_SaHiashiCode[i]) {
				m_UiaDlHiashiIndex[j] = i;
				break;
			}
	}

	nRv = 0;

CleanUp:
	if (bBeginTrans)
		Database.m_pWorkspace->Rollback();
	if (m_pServer) {
		m_pServer->Close();
		delete m_pServer;
		m_pServer = NULL;
	}

	return nRv;
}

void CAutoTraderDlg::HiashiDel(int nIndex)
{
	int i;
	int j;
	long* plFunashi = (long *)m_PaFunashi[nIndex];
	char pchWork[MEMMAPPASIZE];
	int nHiashiSize = m_SaHiashiCode.GetSize();
	int nDlSize = m_SaDlCode.GetSize();

	m_lFunashi0Count -= plFunashi[-1];
	plFunashi[-1] = 0;
	CopyMemory(pchWork, m_pMappingViewOffset + MEMMAPPASIZE * nIndex, MEMMAPPASIZE);
	MoveMemory(m_pMappingViewOffset + MEMMAPPASIZE * nIndex, m_pMappingViewOffset + MEMMAPPASIZE * (nIndex + 1), MEMMAPPASIZE * (nHiashiSize - (nIndex + 1)));
	CopyMemory(m_pMappingViewOffset + MEMMAPPASIZE * (nHiashiSize - 1), pchWork, MEMMAPPASIZE);

	m_MstpHiashiCode.RemoveKey(m_SaHiashiCode[nIndex]);

	m_SaHiashiCode.RemoveAt(nIndex);
	m_SaHiashiName.RemoveAt(nIndex);
	m_SaHiashiType.RemoveAt(nIndex);
	m_WaHiashiUnit.RemoveAt(nIndex);
	m_UiaHiashiNice.RemoveAt(nIndex);
	m_DwaHiashiPreEndPrice.RemoveAt(nIndex);
	m_DwaHiashiPreEndTradeCount.RemoveAt(nIndex);
	m_DwaHiashiPriceDiffAve.RemoveAt(nIndex);
	m_DwaHiashiStartPrice.RemoveAt(nIndex);
	m_DwaHiashiStopDiff.RemoveAt(nIndex);
	m_DwaHiashiBuyTotalPrice.RemoveAt(nIndex);
	m_DwaHiashiBuyUnitCount.RemoveAt(nIndex);
	m_PaFunashi.RemoveAt(nIndex);

	nHiashiSize --;

	for (i = nIndex; i < nHiashiSize; i ++)
		m_PaFunashi[i] = m_pMappingViewOffset + MEMMAPPASIZE * i + sizeof(long);

	for (i = nIndex; i < nHiashiSize; i ++)
		m_MstpHiashiCode[m_SaHiashiCode[i]] = (void *)i;

	m_UiaFunashiPaIndex.RemoveAll();
	m_DwaFunashiPrice.RemoveAll();
	m_UiaFunashiNice.RemoveAll();

	for (i = nIndex; i < nHiashiSize; i ++) {
		for (j = 0; j < nDlSize; j ++)
			if (m_SaDlCode[j] == m_SaHiashiCode[i]) {
				m_UiaDlHiashiIndex[j] = i;
				break;
			}
	}
}

int CAutoTraderDlg::FunashiAnalyze(int nMode, const COleDateTime* pDtCur, const COleDateTime* pDtPrev, LPCTSTR lpszCode)
{
	static int nRv;

	static int i;
	static int j;
	static COleDateTime DtCur;
	static COleDateTime DtPrev;
	static COleDateTime DtCurMinute;
	static int nCurYear;
	static int nCurMonth;
	static int nCurDay;
	static CString strCode;
	static long* plFunashi;
	static long lPrice;
	static long lTradeCount;
	static double dVwap;
	static COleVariant var;
	static COleVariant pKeyArray[2];

	nRv = -1;

	if (pDtCur)
		DtCur = *pDtCur;
	else
		DtCur = GetCurrentTimeEx();

	nCurYear = DtCur.GetYear();
	nCurMonth = DtCur.GetMonth();
	nCurDay = DtCur.GetDay();

	DtCurMinute.SetDateTime(nCurYear, nCurMonth, nCurDay, DtCur.GetHour(), DtCur.GetMinute(), DtCur.GetSecond() / TIMEUNIT * TIMEUNIT);

	try
	{
		CDaoDatabase Database;
		Database.Open(m_strDBFPath, FALSE, TRUE);

		if (pDtPrev)
			DtPrev = *pDtPrev;
		else {
			CDaoRecordset RsHiashiPreDate(&Database);
			RsHiashiPreDate.Open(dbOpenTable, TBL_HIASHI);
			RsHiashiPreDate.SetCurrentIndex(pszPrimaryKey);

			pKeyArray[0] = COleVariant(COleDateTime(nCurYear, nCurMonth, nCurDay, 0, 0, 0));
			if (RsHiashiPreDate.Seek("<", pKeyArray, 2)) {
				RsHiashiPreDate.GetFieldValue(0, var);
				DtPrev = var.date;
			}
		}

		if (nMode) {
//			COleDateTime DtStart(DtPrev.GetYear(), DtPrev.GetMonth(), DtPrev.GetDay(), 8, 0, 0);
			COleDateTime DtStart(nCurYear, nCurMonth, nCurDay, 8, 0, 0);
			COleDateTime DtEnd(nCurYear, nCurMonth, nCurDay, 15, 30, 0);
			COleDateTime DtMax(9999, 12, 31, 23, 59, 59);
			BOOL bEOF0;
			BOOL bEOF1;
			BOOL bEOF2;
			int nType = -1;
			COleDateTime DtDateTime0;
			COleDateTime DtDateTime1;
			COleDateTime DtDateTime2;
			CString strCode0;
			CString strCode1;
			CString strCode2;
			COleDateTime DtDateTime;
			CKehai0 Kehai0Work;
			CKehai1 Kehai1Work;
			CFunashi0 Funashi0;
			CFunashi1 Funashi1;
			CFunashi2 Funashi2;
			void* pVoid;

			m_UiaFunashiPaIndex.RemoveAll();
			m_DwaFunashiPrice.RemoveAll();
//			m_DwaFunashiPriceRiseRatio.RemoveAll();
//			m_UiaFunashiPriceMinutes.RemoveAll();
			m_UiaFunashiNice.RemoveAll();

			CDaoRecordset RsFunashi0(&Database);
			CDaoRecordset RsFunashi1(&Database);
			CDaoRecordset RsFunashi2(&Database);
			RsFunashi0.Open(dbOpenTable, TBL_FUNASHI0);
			RsFunashi1.Open(dbOpenTable, TBL_FUNASHI1);
			RsFunashi2.Open(dbOpenTable, TBL_FUNASHI2);
			if (lpszCode) {
				RsFunashi0.SetCurrentIndex(pszSecondaryKey);
				RsFunashi1.SetCurrentIndex(pszSecondaryKey);
				RsFunashi2.SetCurrentIndex(pszSecondaryKey);
			} else {
				RsFunashi0.SetCurrentIndex(pszPrimaryKey);
				RsFunashi1.SetCurrentIndex(pszPrimaryKey);
				RsFunashi2.SetCurrentIndex(pszPrimaryKey);
			}

			if (lpszCode) {
				pKeyArray[0] = COleVariant(lpszCode, VT_BSTRT);
				pKeyArray[1] = COleVariant(DtStart);
			} else {
				pKeyArray[0] = COleVariant(DtStart);
				pKeyArray[1] = COleVariant();
			}
			bEOF0 = ! RsFunashi0.Seek(">=", pKeyArray, 2);
			bEOF1 = ! RsFunashi1.Seek(">=", pKeyArray, 2);
			bEOF2 = ! RsFunashi2.Seek(">=", pKeyArray, 2);
			if (! bEOF0  ||  ! bEOF1  ||  ! bEOF2) {
				if (bEOF0)
					DtDateTime0 = DtMax;
				else {
					RsFunashi0.GetFieldValue(0, var);
					DtDateTime0 = var.date;

					RsFunashi0.GetFieldValue(1, var);
					strCode0 = V_BSTRT((LPVARIANT)var);

					if (lpszCode  &&  strCode0 != lpszCode) {
						bEOF0 = TRUE;
						DtDateTime0 = DtMax;
					}
				}
				if (bEOF1)
					DtDateTime1 = DtMax;
				else {
					RsFunashi1.GetFieldValue(0, var);
					DtDateTime1 = var.date;

					RsFunashi1.GetFieldValue(1, var);
					strCode1 = V_BSTRT((LPVARIANT)var);

					if (lpszCode  &&  strCode1 != lpszCode) {
						bEOF1 = TRUE;
						DtDateTime1 = DtMax;
					}
				}
				if (bEOF2)
					DtDateTime2 = DtMax;
				else {
					RsFunashi2.GetFieldValue(0, var);
					DtDateTime2 = var.date;

					RsFunashi2.GetFieldValue(1, var);
					strCode2 = V_BSTRT((LPVARIANT)var);

					if (lpszCode  &&  strCode2 != lpszCode) {
						bEOF2 = TRUE;
						DtDateTime2 = DtMax;
					}
				}
				do {
					switch (nType) {
					case 0:
						RsFunashi0.GetFieldValue(0, var);
						DtDateTime0 = var.date;

						RsFunashi0.GetFieldValue(1, var);
						strCode0 = V_BSTRT((LPVARIANT)var);

						if (lpszCode  &&  strCode0 != lpszCode) {
							bEOF0 = TRUE;
							DtDateTime0 = DtMax;
						}
						break;
					case 1:
						RsFunashi1.GetFieldValue(0, var);
						DtDateTime1 = var.date;

						RsFunashi1.GetFieldValue(1, var);
						strCode1 = V_BSTRT((LPVARIANT)var);

						if (lpszCode  &&  strCode1 != lpszCode) {
							bEOF1 = TRUE;
							DtDateTime1 = DtMax;
						}
						break;
					case 2:
						RsFunashi2.GetFieldValue(0, var);
						DtDateTime2 = var.date;

						RsFunashi2.GetFieldValue(1, var);
						strCode2 = V_BSTRT((LPVARIANT)var);

						if (lpszCode  &&  strCode2 != lpszCode) {
							bEOF2 = TRUE;
							DtDateTime2 = DtMax;
						}
					}
					if (DtDateTime0 <= DtDateTime1  &&  DtDateTime0 <= DtDateTime2) {
						DtDateTime = DtDateTime0;
						strCode = strCode0;
						nType = 0;
					} else if (DtDateTime1 <= DtDateTime0  &&  DtDateTime1 <= DtDateTime2) {
						DtDateTime = DtDateTime1;
						strCode = strCode1;
						nType = 1;
					} else {
						DtDateTime = DtDateTime2;
						strCode = strCode2;
						nType = 2;
					}
					if (DtDateTime > DtEnd)
						break;

					CDaoRecordset& RsFunashi = ! nType ? RsFunashi0 : nType == 1 ? RsFunashi1 : RsFunashi2;

					if (m_MstpHiashiCode.Lookup(strCode, pVoid)) {
						plFunashi = (long *)m_PaFunashi[(int)pVoid];

						RsFunashi.GetFieldValue(2, var);
						lPrice = var.vt == VT_NULL ? 0L : var.lVal;

						switch (nType) {
						case 0:
							RsFunashi0.GetFieldValue(3, var);
							lTradeCount = var.vt == VT_NULL ? 0L : var.lVal;

							RsFunashi0.GetFieldValue(4, var);
							dVwap = var.vt == VT_NULL ? 0.0 : var.dblVal;

							Kehai0Work.Empty();

							for (j = 0; j < 10; j ++) {
								RsFunashi0.GetFieldValue(5 + j, var);
								if (var.vt != VT_NULL)
									Kehai0Work.m_plKehaiPrice[j] = var.lVal;

								RsFunashi0.GetFieldValue(15 + j, var);
								if (var.vt != VT_NULL)
									Kehai0Work.m_plKehaiCount[j] = var.lVal;
							}

							Funashi0.m_DtDateTime = DtDateTime;
							Funashi0.m_lPrice = lPrice;
							Funashi0.m_lTradeCount = lTradeCount;
							Funashi0.m_dVwap = dVwap;
							Funashi0.m_Kehai = Kehai0Work;
							AddFunashi0(plFunashi, Funashi0);
							break;
						case 1:
							RsFunashi1.GetFieldValue(3, var);
							lTradeCount = var.vt == VT_NULL ? 0L : var.lVal;

							Funashi1.m_DtDateTime = DtDateTime;
							Funashi1.m_lPrice = lPrice;
							Funashi1.m_lTradeCount = lTradeCount;
							AddFunashi1(plFunashi, Funashi1);
							break;
						default:
							Kehai1Work.Empty();

							for (j = 0; j < 2; j ++) {
								RsFunashi2.GetFieldValue(3 + j, var);
								if (var.vt != VT_NULL)
									Kehai1Work.m_plKehaiPrice[j] = var.lVal;

								RsFunashi2.GetFieldValue(5 + j, var);
								if (var.vt != VT_NULL)
									Kehai1Work.m_plKehaiCount[j] = var.lVal;
							}

							Funashi2.m_DtDateTime = DtDateTime;
							Funashi2.m_lPrice = lPrice;
							Funashi2.m_Kehai = Kehai1Work;
							AddFunashi2(plFunashi, Funashi2);
						}
					}

					RsFunashi.MoveNext();
					switch (nType) {
					case 0:
						if (bEOF0 = RsFunashi0.IsEOF()) {
							DtDateTime0 = DtMax;
							nType = -1;
						}
						break;
					case 1:
						if (bEOF1 = RsFunashi1.IsEOF()) {
							DtDateTime1 = DtMax;
							nType = -1;
						}
						break;
					default:
						if (bEOF2 = RsFunashi2.IsEOF()) {
							DtDateTime2 = DtMax;
							nType = -1;
						}
					}
				} while (! bEOF0  ||  ! bEOF1  ||  ! bEOF2);
			}
		} else {
			static int k;
			static int l;
			static int nSize;
			static COleDateTime Dt;
			static COleDateTime DtDateTime;
			static COleDateTime DtDate;
			static COleDateTime DtTime;
			static int nPreDay;
			static int nDay;
			static int nDay0;
			static int nHour;
			static long* plFunashi255;
			static long lPrice255;
			static CKehai0 KehaiWork255;
			static CFunashi0 FunashiWork;
			static long lKehaiPrice;
			static int nCurDateStartIndex;
			static int nFunashiPaIndex;
			static int nFunashi255Index;
/*
			static long plPrice[(60 * 4 + 60 + 55 + 15 + 2) * (60 / TIMEUNIT) * 2];
			static long plPrice255[(60 * 4 + 60 + 55 + 15 + 2) * (60 / TIMEUNIT) * 2];
			static long plTradeCount[(60 * 4 + 60 + 55 + 15 + 2) * (60 / TIMEUNIT) * 2];
			static double pdVwap[(60 * 4 + 60 + 55 + 15 + 2) * (60 / TIMEUNIT) * 2];
			static CKehai0 pKehai[(60 * 4 + 60 + 55 + 15 + 2) * (60 / TIMEUNIT) * 2];
			static CKehai0 pKehai255[(60 * 4 + 60 + 55 + 15 + 2) * (60 / TIMEUNIT) * 2];
			static long plKehaiPrice[(60 * 4 + 60 + 55 + 15 + 2) * (60 / TIMEUNIT) * 2];
*/
/*
			static long plPrice[(60 * 4 + 60 + 55 + 15 + 2) * (60 / TIMEUNIT)];
			static long plPrice255[(60 * 4 + 60 + 55 + 15 + 2) * (60 / TIMEUNIT)];
			static long plTradeCount[(60 * 4 + 60 + 55 + 15 + 2) * (60 / TIMEUNIT)];
			static double pdVwap[(60 * 4 + 60 + 55 + 15 + 2) * (60 / TIMEUNIT)];
			static CKehai0 pKehai[(60 * 4 + 60 + 55 + 15 + 2) * (60 / TIMEUNIT)];
			static CKehai0 pKehai255[(60 * 4 + 60 + 55 + 15 + 2) * (60 / TIMEUNIT)];
			static long plKehaiPrice[(60 * 4 + 60 + 55 + 15 + 2) * (60 / TIMEUNIT)];
*/
			static long plPrice[(60 * 4 + 60 + 30 + 55 + 15 + 2) * (60 / TIMEUNIT)];
			static long plPrice255[(60 * 4 + 60 + 30 + 55 + 15 + 2) * (60 / TIMEUNIT)];
			static long plTradeCount[(60 * 4 + 60 + 30 + 55 + 15 + 2) * (60 / TIMEUNIT)];
			static double pdVwap[(60 * 4 + 60 + 30 + 55 + 15 + 2) * (60 / TIMEUNIT)];
			static CKehai0 pKehai[(60 * 4 + 60 + 30 + 55 + 15 + 2) * (60 / TIMEUNIT)];
			static CKehai0 pKehai255[(60 * 4 + 60 + 30 + 55 + 15 + 2) * (60 / TIMEUNIT)];
			static long plKehaiPrice[(60 * 4 + 60 + 30 + 55 + 15 + 2) * (60 / TIMEUNIT)];
//			static int nSamePrice;
//			static int nSamePriceCount;
//			static BOOL bSamePrice;
			static int nNice;
			static COleDateTime Dt0859(1899, 12, 30, 7, 59, 60 - TIMEUNIT);
//			static COleDateTime Dt1059(1899, 12, 30, 11, 0, 60 - TIMEUNIT);
			static COleDateTime Dt1059(1899, 12, 30, 11, 30, 60 - TIMEUNIT);
//			static COleDateTime Dt1130(1899, 12, 30, 11, 30, 0);
			static COleDateTime Dt1130(1899, 12, 30, 12, 0, 0);
			static COleDateTime Dt1230(1899, 12, 30, 12, 5, 0);
			static COleDateTime Dt1459(1899, 12, 30, 15, 15, 60 - TIMEUNIT);
			static COleDateTime Dt1530(1899, 12, 30, 15, 30, 0);

			nSize = m_SaHiashiCode.GetSize();

			m_UiaFunashiPaIndex.SetSize(nSize);
			m_DwaFunashiPrice.SetSize(nSize);
//			m_DwaFunashiPriceRiseRatio.SetSize(nSize);
//			m_UiaFunashiPriceMinutes.SetSize(nSize);
			m_UiaFunashiNice.SetSize(nSize);

			nPreDay = DtPrev.GetDay();

			if (m_nExecMode != 1)
				m_Edit16.GetWindowText(m_strLogCode);

			CDaoRecordset RsHiashiPreDate(&Database);
			RsHiashiPreDate.Open(dbOpenTable, TBL_HIASHI);
			RsHiashiPreDate.SetCurrentIndex(pszPrimaryKey);

			plFunashi255 = (long *)m_PaFunashi[0];

			for (i = 1; i < nSize; i ++) {
				strCode = m_SaHiashiCode[i];

				m_bLog = strCode == m_strLogCode;
if (m_nExecMode == 1  &&  m_strLogCode.GetLength()  &&  ! m_bLog) continue;

				plFunashi = (long *)m_PaFunashi[i];

				for (j = plFunashi[-1] - 1; j >= 0; j --)
					if (((CFunashi0 *)(m_pMappingViewCell + plFunashi[j]))->m_DtDateTime <= DtCurMinute)
						break;
				nFunashiPaIndex = j;

				k = 0;
				nCurDateStartIndex = -2;
				Dt = DtCurMinute;
				nDay0 = nCurDay;
//				nSamePrice = nSamePriceCount = 0;
//				bSamePrice = FALSE;
				for (; j >= 0  &&  k < FUNASHI_LONG_COUNT + FUNASHI_SHORT_COUNT * 2; j --) {
					FunashiWork = GetFunashi(plFunashi, j);
					DtDateTime = FunashiWork.m_DtDateTime;

					nDay = DtDateTime.GetDay();
					if (nDay != nDay0) {
						if (nCurDateStartIndex == -2)
							nCurDateStartIndex = k - 1;
						nHour = DtDateTime.GetHour();
						if (m_nExecMode != 1  &&  PRE_HOUR == 10  ||  m_nExecMode == 1  &&  TIMESIM_PRE_HOUR == 10)
//							if (nDay == nPreDay  &&  (nHour == 10  &&  DtDateTime.GetMinute() >= 50  ||  nHour == 11)) {
							if (nDay == nPreDay  &&  (nHour == 11  &&  DtDateTime.GetMinute() >= 20)) {
								DtTime = Dt1130;
								DtDate.SetDate(Dt.GetYear(), Dt.GetMonth(), Dt.GetDay());
								if (DtDate == m_DtDate)
									DtDate = m_DtPreDate;
								else {
									pKeyArray[0] = COleVariant(DtDate);
									if (RsHiashiPreDate.Seek("<", pKeyArray, 2)) {
										RsHiashiPreDate.GetFieldValue(0, var);
										DtDate = var.date;
									}
								}
								Dt.SetDateTime(DtDate.GetYear(), DtDate.GetMonth(), DtDate.GetDay(), DtTime.GetHour(), DtTime.GetMinute(), DtTime.GetSecond());
							} else
								break;
						else
							if (nDay == nPreDay  &&  (nHour == 14  &&  DtDateTime.GetMinute() >= 50  ||  nHour == 15)) {
								DtTime = Dt1530;
								DtDate.SetDate(Dt.GetYear(), Dt.GetMonth(), Dt.GetDay());
								if (DtDate == m_DtDate)
									DtDate = m_DtPreDate;
								else {
									pKeyArray[0] = COleVariant(DtDate);
									if (RsHiashiPreDate.Seek("<", pKeyArray, 2)) {
										RsHiashiPreDate.GetFieldValue(0, var);
										DtDate = var.date;
									}
								}
								Dt.SetDateTime(DtDate.GetYear(), DtDate.GetMonth(), DtDate.GetDay(), DtTime.GetHour(), DtTime.GetMinute(), DtTime.GetSecond());
							} else
								break;
					}
					nDay0 = nDay;

					lPrice = FunashiWork.m_lPrice;
					lTradeCount = FunashiWork.m_lTradeCount;
					dVwap = FunashiWork.m_dVwap;
					CKehai0& KehaiWork = FunashiWork.m_Kehai;

					for (l = plFunashi255[-1] - 1; l >= 0; l --)
						if (((CFunashi0 *)(m_pMappingViewCell + plFunashi255[l]))->m_DtDateTime <= DtDateTime)
							break;
					nFunashi255Index = l;

					if (nFunashi255Index == -1) {
						lPrice255 = 0L;
						KehaiWork255.Empty();
					} else {
						lPrice255 = ((CFunashi0 *)(m_pMappingViewCell + plFunashi255[nFunashi255Index]))->m_lPrice;
						KehaiWork255 = ((CFunashi0 *)(m_pMappingViewCell + plFunashi255[nFunashi255Index]))->m_Kehai;
					}

					if (KehaiWork.m_plKehaiPrice[4] == KehaiWork.m_plKehaiPrice[5] + GetDiff(KehaiWork.m_plKehaiPrice[5] + 1L))
						if (labs(KehaiWork.m_plKehaiCount[4]) < labs(KehaiWork.m_plKehaiCount[5]))
							lKehaiPrice = KehaiWork.m_plKehaiPrice[4];
						else
							lKehaiPrice = KehaiWork.m_plKehaiPrice[5];
					else
						lKehaiPrice = KehaiWork.m_plKehaiPrice[5] + GetDiff(KehaiWork.m_plKehaiPrice[5] + 1L);

					while (Dt >= DtDateTime) {
						plPrice[k] = lPrice;
						plPrice255[k] = lPrice255;
						plTradeCount[k] = lTradeCount;
						pdVwap[k] = dVwap;
						pKehai[k] = KehaiWork;
						pKehai255[k] = KehaiWork255;
						plKehaiPrice[k] = lKehaiPrice;

//if (m_bLog)
//	TRACE("%s %d %d %s %s %s\n", strCode, j, k, DtCurMinute.Format("%Y/%m/%d %H:%M:%S"), Dt.Format("%Y/%m/%d %H:%M:%S"), DtDateTime.Format("%Y/%m/%d %H:%M:%S"));

						k ++;
						Dt = FixDateTime(Dt - COleDateTimeSpan(0, 0, 0, TIMEUNIT));
						DtDate.SetDate(Dt.GetYear(), Dt.GetMonth(), Dt.GetDay());
						DtTime.SetTime(Dt.GetHour(), Dt.GetMinute(), Dt.GetSecond());
						if (DtTime == Dt0859) {
							if (DtDate == m_DtDate)
								DtDate = m_DtPreDate;
							else {
								pKeyArray[0] = COleVariant(DtDate);
								if (RsHiashiPreDate.Seek("<", pKeyArray, 2)) {
									RsHiashiPreDate.GetFieldValue(0, var);
									DtDate = var.date;
								}
							}
							DtTime = Dt1530;
						} else if (DtTime > Dt1059  &&  DtTime < Dt1130)
							DtTime = Dt1059;
						else if (DtTime > Dt1130  &&  DtTime < Dt1230)
							DtTime = Dt1130;
						else if (DtTime > Dt1459  &&  DtTime < Dt1530)
							DtTime = Dt1459;
						Dt.SetDateTime(DtDate.GetYear(), DtDate.GetMonth(), DtDate.GetDay(), DtTime.GetHour(), DtTime.GetMinute(), DtTime.GetSecond());
					}

/*
					if (! bSamePrice) {
						if (nSamePrice == 0)
							nSamePrice = lPrice;
						if (nSamePrice == lPrice)
							nSamePriceCount = k;
						else
							bSamePrice = TRUE;
					}
*/
					}

				if (k >= FUNASHI_LONG_COUNT + FUNASHI_SHORT_COUNT * 2) {
					lPrice = plPrice[0];
					m_UiaFunashiPaIndex[i] = nFunashiPaIndex;
					m_DwaFunashiPrice[i] = lPrice;
//					m_DwaFunashiPriceRiseRatio[i] = m_DwaHiashiPreEndPrice[i] ? lPrice * 10000L / m_DwaHiashiPreEndPrice[i] - 10000L : 0L;
//					m_UiaFunashiPriceMinutes[i] = nSamePriceCount;
					if (nCurDateStartIndex == -2)
						nCurDateStartIndex = k - 1;
					if (nCurDateStartIndex >= 0)
						nNice = GetFunashiNice(i, plPrice, plPrice255, plTradeCount, pdVwap, pKehai, pKehai255, plKehaiPrice, nCurDateStartIndex, pDtCur);
					else
						nNice = 0;
					nNice |= m_UiaHiashiNice[i];
					m_UiaFunashiNice[i] = nNice;
				}
			}
		}
	}
	catch (CException* pEx) {
		DispErrorLog("銘柄分足データ分析エラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
		goto CleanUp;
	}

	nRv = 0;

CleanUp:

	return nRv;
}

void CAutoTraderDlg::Disp()
{
	m_Edit1.SetWindowText(IToA(m_lZan));
	m_Edit2.SetWindowText(IToA(m_lZan - m_lStartZan));

	m_Edit3.SetWindowText(IToA(m_lVZan));
	m_Edit4.SetWindowText(IToA(m_lVZan - m_lStartVZan));

	m_Edit5.SetWindowText(IToA(m_lCashZan));

	m_Edit6.SetWindowText(IToA(m_UiaKabuHiashiIndex.GetSize()));
	m_Edit7.SetWindowText(IToA(m_lZan - m_lCashZan));

	m_Edit8.SetWindowText(IToA(m_lKabuSellPlusCount));
	m_Edit9.SetWindowText(IToA(m_lKabuSellPlus));

	m_Edit10.SetWindowText(IToA(m_lKabuSellZeroCount));

	m_Edit11.SetWindowText(IToA(m_lKabuSellMinusCount));
	m_Edit12.SetWindowText(IToA(- m_lKabuSellMinus));

	m_Edit13.SetWindowText(m_DtPrePreDate.Format("%Y/%m/%d"));
	m_Edit14.SetWindowText(m_DtPreDate.Format("%Y/%m/%d"));
	m_Edit15.SetWindowText(m_DtDate.Format("%Y/%m/%d"));

	PumpWaitingMessages();
}

void CAutoTraderDlg::DispLog(LPCTSTR lpszFormat, ...)
{
	if (m_bDispLog || m_bDispDebugLog) {
		CStringBuffer sb;
		CStringBuffer sbC;

		va_list vl;
		va_start(vl, lpszFormat);
		sb.FormatV(lpszFormat, vl);
		va_end(vl);

		if (m_nExecMode != 1  ||  ! (m_bTimeSim && m_bDispDebugLog)) {
			sbC = sb;
			sbC.TrimRight();
			m_List1.AddString(sbC);
			m_List1.SetTopIndex(m_List1.GetCount() - 1);
		}

		if (m_nExecMode == 1  &&  m_bTimeSim  &&  m_bDispDebugLog)
			m_SfDump.WriteString(sb);
		else {
			CStdioFile StdioFile(m_strLogFPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
			StdioFile.SeekToEnd();
			StdioFile.WriteString(sb);
			StdioFile.Close();
		}
	}
	PumpWaitingMessages();
}

void CAutoTraderDlg::DispErrorLog(LPCTSTR lpszFormat, ...)
{
	CStringBuffer sb;

	va_list vl;
	va_start(vl, lpszFormat);
	sb.FormatV(lpszFormat, vl);
	va_end(vl);

	sb = COleDateTime::GetCurrentTime().Format("%H:%M:%S ") + sb;

	DispLog(sb);

	CString strFPath;
	strFPath.Format("%s\\Log\\" MAIN_EXENAME "Error%s%d.txt", m_strDataDir, COleDateTime::GetCurrentTime().Format("%Y%m%d"), AfxGetThread()->m_nThreadID);
	CStdioFile StdioFile(strFPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	StdioFile.SeekToEnd();
	sb += StrFormat("m_strServerName = %s\n", m_strServerName);
	sb += StrFormat("m_strObject = %s\n", m_strObject);
	sb += StrFormat("m_strObjectC = %s\n", m_strObjectC);
	sb += StrFormat("m_strObjectT = %s\n", m_strObjectT);
	sb += StrFormat("m_sbOptional = %s\n", m_sbOptional);
	sb += StrFormat("m_nPort = %i\n", m_nPort);
	sb += StrFormat("m_sbHtml =\n%s", m_sbHtml);
	sb += StrFormat("m_sbHtmlT =\n%s", m_sbHtmlT);
	sb += StrFormat("m_strFPath =\n%s", m_strFPath);
	sb += StrFormat("m_strFPathC0 =\n%s", m_strFPathC0);
	sb += StrFormat("m_strFPathC1 =\n%s", m_strFPathC1);
	sb += '\n';
	StdioFile.WriteString(sb);
	StdioFile.Close();
}

void CAutoTraderDlg::InsertNiceBuyHiashiIndex(int nNiceBuyLeftIndex, int nNiceBuyRightIndex, int nIndex, int nNice, int nMask)
{
	if (nNiceBuyRightIndex == -1)
		m_UiaNiceBuyHiashiIndex.Add(nIndex);
	else {
		int nNiceBuyCenterIndex = (nNiceBuyLeftIndex + nNiceBuyRightIndex + 1) / 2;
		int nCenterNice = m_UiaFunashiNice[m_UiaNiceBuyHiashiIndex[nNiceBuyCenterIndex]] & nMask;

		if (nNiceBuyLeftIndex == nNiceBuyRightIndex)
			if (nNice > nCenterNice)
				m_UiaNiceBuyHiashiIndex.InsertAt(nNiceBuyLeftIndex, nIndex);
			else
				m_UiaNiceBuyHiashiIndex.InsertAt(nNiceBuyLeftIndex + 1, nIndex);
		else
			if (nNice > nCenterNice)
				InsertNiceBuyHiashiIndex(nNiceBuyLeftIndex, nNiceBuyCenterIndex - 1, nIndex, nNice, nMask);
			else
				InsertNiceBuyHiashiIndex(nNiceBuyCenterIndex, nNiceBuyRightIndex, nIndex, nNice, nMask);
	}
}

void CAutoTraderDlg::GetState()
{
	int i;
	int j;
	int k;
	int nState;
	int nReceiptNo = -1;
	long lKehaiSellPrice;
	long lKehaiBuyPrice;
	long lKehaiSellPriceC;
	long lKehaiBuyPriceC;
	long lSellPrice;
	long lBuyPrice;
	long lPrice;
	long lSoldPrice;
	short sUnit;
	long lUnitCount = 1L;
	long lSetPrice;
	long lProfit;
	BOOL bSold;
	BOOL bCanceled;
	BOOL bChanged;
	BOOL bCancelReq;
	BOOL bRemoved;

	int l;
	int m;
	int mmax;
	int nKabuIndex;
	long* plFunashi;
	CFunashi0 Funashi0;
	CFunashi0 FunashiWork;
	COleDateTime DtDateTime;
	long lPriceH;
	long lPriceL;
	long lPrice0H;
	long lPrice0L;
	long lPrice1H;
	long lPrice1L;
	double dVwap0;
	double dVwap1;
	long lTradeCount0;
	long lTradeCount1;
	long l0;
	long l1;
	double d0;
	double d1;

	CString strCode;

	nKabuIndex = 0;

	while (m_UiaKabuReceiptNo.GetSize()) {
		bSold =
		bCanceled =
		bChanged =
		bCancelReq =
		bRemoved =
			FALSE;

		i = nKabuIndex;
		if (i >= m_UiaKabuReceiptNo.GetSize())
			break;

		nReceiptNo = m_UiaKabuReceiptNo[i];

		nKabuIndex = i + 1;

		j = m_UiaKabuHiashiIndex[i];

		nState = m_UiaKabuState[i];
		lBuyPrice = m_DwaKabuBuyPrice0[i];
		lSellPrice = m_DwaKabuSellPrice[i];
		lUnitCount = m_DwaKabuUnitCount[i];

		strCode = m_SaHiashiCode[j];
		sUnit = m_WaHiashiUnit[j];
		k = m_UiaFunashiPaIndex[j];

		if (nState == 5)
			bCanceled = TRUE;

		plFunashi = (long *)m_PaFunashi[j];
		Funashi0 = GetFunashi(plFunashi, k);

		CKehai0& KehaiWork = Funashi0.m_Kehai;
		lKehaiSellPrice = KehaiWork.m_plKehaiPrice[4];
		lKehaiBuyPrice = KehaiWork.m_plKehaiPrice[5];
		lPrice = Funashi0.m_lPrice;
		lKehaiSellPriceC = lKehaiSellPrice ? lKehaiSellPrice : lPrice;
		lKehaiBuyPriceC = lKehaiBuyPrice ? lKehaiBuyPrice : lPrice - GetDiff(lPrice);

		DtDateTime = m_DtaKabuFunashiPaDateTime[i];

		for (l = plFunashi[-1] - 1; l >= 0; l --)
			if (((CFunashi0 *)(m_pMappingViewCell + plFunashi[l]))->m_DtDateTime == DtDateTime)
				break;

		if (nState == 1  ||  nState == 3) {
			mmax = k + 1;
			lSoldPrice = nState == 1 ? lBuyPrice : lSellPrice;

			switch (nState) {
			case 1:
				for (m = l + 1; m < mmax; m ++) {
					l0 = GetFunashi(plFunashi, m).m_Kehai.m_plKehaiPrice[4];
					if (m == l + 1  &&  l0 < lBuyPrice  ||  m > l + 1  &&  l0 <= lBuyPrice) {
						bSold = TRUE;
						lSoldPrice = l0;
						break;
					}
				}
				if (! bSold  &&  lKehaiBuyPriceC > lBuyPrice)
					bCancelReq = TRUE;
				break;
			case 3:
				for (m = l + 1; m < mmax; m ++) {
					l0 = GetFunashi(plFunashi, m).m_Kehai.m_plKehaiPrice[5];
					if (m == l + 1  &&  l0 > lSellPrice  ||  m > l + 1  &&  l0 >= lSellPrice) {
						bSold = TRUE;
						lSoldPrice = l0;
						break;
					}
				}
				if (! bSold  &&  lKehaiSellPriceC < lSellPrice)
					bCancelReq = TRUE;
			}

			if (! bSold  &&  ! bCancelReq) {
				d0 = d1 = 0.0;
				FunashiWork = GetFunashi(plFunashi, l);
				lPriceH = FunashiWork.m_Kehai.m_plKehaiPrice[4];
				lPriceL = FunashiWork.m_Kehai.m_plKehaiPrice[5];
				for (m = l + 2; m < mmax; m ++) {
					FunashiWork = GetFunashi(plFunashi, m);
					lPrice0H = FunashiWork.m_Kehai.m_plKehaiPrice[4];
					lPrice0L = FunashiWork.m_Kehai.m_plKehaiPrice[5];
					dVwap0 = FunashiWork.m_dVwap;
					lTradeCount0 = FunashiWork.m_lTradeCount;
					FunashiWork = GetFunashi(plFunashi, m - 1);
					lPrice1H = FunashiWork.m_Kehai.m_plKehaiPrice[4];
					lPrice1L = FunashiWork.m_Kehai.m_plKehaiPrice[5];
					dVwap1 = FunashiWork.m_dVwap;
					lTradeCount1 = FunashiWork.m_lTradeCount;
					if (lPrice1H  &&  lPrice1L  &&  dVwap1 > 0.0  &&  dVwap0 > 0.0  &&  lTradeCount1  &&  lTradeCount0  &&  lPrice1H != lPrice1L) {
						d0 += ((dVwap0 * lTradeCount0 - dVwap1 * lTradeCount1) - lPrice1L * (double)(lTradeCount0 - lTradeCount1)) / (lPrice1H - lPrice1L);
						d1 += lTradeCount0 - lTradeCount1 - d0;
					}
				}

				l0 = l1 = 0L;
				FunashiWork = GetFunashi(plFunashi, l + 1);
				if (FunashiWork.m_Kehai.m_plKehaiPrice[5] == lBuyPrice)
					l0 = FunashiWork.m_Kehai.m_plKehaiCount[5];
				if (FunashiWork.m_Kehai.m_plKehaiPrice[4] == lSellPrice)
					l1 = FunashiWork.m_Kehai.m_plKehaiCount[4];

				if (nState == 1  &&  d1 > l0  ||  nState == 3  &&  d0 > l1)
					bSold = TRUE;
			}
		}

		/*
			1 - 買待
			2 - 買済
			3 - 売待
			4 - 売済
			5 - 消待（買）
		*/
		switch (nState) {
		case 1:
			if (bSold) {
				if (lSoldPrice != (long)m_DwaKabuBuyPrice0[i]) {
					l0 = (m_DwaKabuBuyPrice0[i] - lSoldPrice) * sUnit * lUnitCount;
					m_lCashZan += l0;
					m_DwaHiashiBuyTotalPrice[j] -= l0;
					m_DwaKabuBuyPrice0[i] = lSoldPrice;
					m_DwaKabuBuyPrice1[i] = lKehaiSellPrice  &&  lKehaiBuyPrice  &&  lKehaiSellPrice == lSoldPrice ? lKehaiBuyPrice : lSoldPrice - GetDiff(lSoldPrice);
				}

				DispLog(
					"%s %ld 買済 %d %s %s %ld円 単%d x%d 変%ld円\n",
					(m_nExecMode == 1 ? m_DtSim : GetCurrentTimeEx()).Format("%H:%M:%S"),
					m_lVZan, nReceiptNo, strCode, m_SaHiashiName[j], lSoldPrice, sUnit, lUnitCount, m_DwaKabuDiff[i]
				);
			} else if (bCancelReq)
				DispLog(
					"%s %ld 買消 %d %s %s\n",
					(m_nExecMode == 1 ? m_DtSim : GetCurrentTimeEx()).Format("%H:%M:%S"),
					m_lVZan, nReceiptNo, strCode, m_SaHiashiName[j]
				);
			break;
		case 3:
			if (bSold) {
				lSetPrice = lSoldPrice * sUnit * lUnitCount;
				lProfit = (lSoldPrice - lBuyPrice) * sUnit * lUnitCount;
				m_lZan += lProfit;
				m_lCashZan += lSetPrice;
				m_DwaHiashiBuyUnitCount[j] -= lUnitCount;
				if (lProfit > 0) {
					m_lKabuSellPlusCount ++;
					m_lKabuSellPlus += lProfit;
				} else if (lProfit == 0)
					m_lKabuSellZeroCount ++;
				else {
					m_lKabuSellMinusCount ++;
					m_lKabuSellMinus += - lProfit;
				}

				DispLog(
					"%s %ld 売済 %d %s %s %ld円 単%d x%d 変%ld円 利%ld円\n",
					(m_nExecMode == 1 ? m_DtSim : GetCurrentTimeEx()).Format("%H:%M:%S"),
					m_lVZan, nReceiptNo, strCode, m_SaHiashiName[j], lSoldPrice, sUnit, lUnitCount, m_DwaKabuDiff[i], lProfit
				);

				m_UiaKabuHiashiIndex.RemoveAt(i);
				m_UiaKabuReceiptNo.RemoveAt(i);
				m_UiaKabuState.RemoveAt(i);
				m_UiaKabuStateMinutes.RemoveAt(i);
				m_UiaKabuTseiKaisu.RemoveAt(i);
				m_DtaKabuFunashiPaDateTime.RemoveAt(i);
				m_DwaKabuBuyPrice0.RemoveAt(i);
				m_DwaKabuBuyPrice1.RemoveAt(i);
				m_DwaKabuSellPrice.RemoveAt(i);
				m_DwaKabuHighPrice.RemoveAt(i);
				m_DwaKabuLowPrice.RemoveAt(i);
				m_DwaKabuUnitCount.RemoveAt(i);
				m_DwaKabuDiff.RemoveAt(i);
				m_UiaKabuUp.RemoveAt(i);
				m_UiaKabuDown.RemoveAt(i);
				m_UiaKabuSell.RemoveAt(i);
				bRemoved = TRUE;

/*
				for (m = 0, mmax = m_SaNiceCode.GetSize(); m < mmax; m ++)
					if (m_SaNiceCode[m] == strCode) {
						((CButton *)GetDlgItem(IDC_CHECK10 + m))->SetCheck(0);
						Check10(m);
						break;
					}
*/
			} else if (bCancelReq) {
				m_DtaKabuFunashiPaDateTime[i] = Funashi0.m_DtDateTime;
				m_DwaKabuSellPrice[i] = lKehaiSellPriceC;

				DispLog(
					"%s %ld 売訂 %d %s %s %ld円 → %ld円\n",
					(m_nExecMode == 1 ? m_DtSim : GetCurrentTimeEx()).Format("%H:%M:%S"),
					m_lVZan, nReceiptNo, strCode, m_SaHiashiName[j], lSellPrice, lKehaiSellPriceC
				);
			} else if (bChanged) {
				m_UiaKabuTseiKaisu[i] ++;

				DispLog(
					"%s %ld 売訂済 %d %s %s %ld円\n",
					(m_nExecMode == 1 ? m_DtSim : GetCurrentTimeEx()).Format("%H:%M:%S"),
					m_lVZan, nReceiptNo, strCode, m_SaHiashiName[j], lSellPrice
				);
			}
			break;
		case 5:
			if (bCanceled) {
				lSetPrice = lBuyPrice * sUnit * lUnitCount;
				m_lCashZan += lSetPrice;

				DispLog(
					"%s %ld 買消済 %d %s %s\n",
					(m_nExecMode == 1 ? m_DtSim : GetCurrentTimeEx()).Format("%H:%M:%S"),
					m_lVZan, nReceiptNo, strCode, m_SaHiashiName[j]
				);

				m_UiaKabuHiashiIndex.RemoveAt(i);
				m_UiaKabuReceiptNo.RemoveAt(i);
				m_UiaKabuState.RemoveAt(i);
				m_UiaKabuStateMinutes.RemoveAt(i);
				m_UiaKabuTseiKaisu.RemoveAt(i);
				m_DtaKabuFunashiPaDateTime.RemoveAt(i);
				m_DwaKabuBuyPrice0.RemoveAt(i);
				m_DwaKabuBuyPrice1.RemoveAt(i);
				m_DwaKabuSellPrice.RemoveAt(i);
				m_DwaKabuHighPrice.RemoveAt(i);
				m_DwaKabuLowPrice.RemoveAt(i);
				m_DwaKabuUnitCount.RemoveAt(i);
				m_DwaKabuDiff.RemoveAt(i);
				m_UiaKabuUp.RemoveAt(i);
				m_UiaKabuDown.RemoveAt(i);
				m_UiaKabuSell.RemoveAt(i);
				bRemoved = TRUE;
			}
		}

		switch (nState) {
		case 1:
			if (bSold)
				nState = 2;
			else if (bCancelReq)
				nState = 5;
			break;
		case 3:
			if (bSold)
				nState = 4;
			break;
		case 5:
			if (bSold)
				nState = 2;
		}

		if (bRemoved)
			nKabuIndex --;
		else {
			if (nState == (int)m_UiaKabuState[i])
				m_UiaKabuStateMinutes[i] ++;
			else {
				m_UiaKabuStateMinutes[i] = 0U;
				m_UiaKabuState[i] = nState;
			}
		}
	}
}

void CAutoTraderDlg::BuyJudge()
{
	int i;
	int imax;

	m_UiaNiceBuyHiashiIndex.RemoveAll();

	for (i = 0, imax = m_SaHiashiCode.GetSize(); i < imax; i ++)
//		if (m_UiaFunashiNice[i] & 0x10  &&  (m_UiaFunashiNice[i] & 0x01) == 0  &&  m_DwaHiashiBuyUnitCount[i] == 0)
		if (m_UiaFunashiNice[i] & 0x10  &&  m_DwaHiashiBuyUnitCount[i] == 0)
			InsertNiceBuyHiashiIndex(0, m_UiaNiceBuyHiashiIndex.GetUpperBound(), i, m_UiaFunashiNice[i] & 0x03f0f0f0, 0x03f0f0f0);
}

void CAutoTraderDlg::SellJudge()
{
	int i;
	int j;
//	int k;
	int imax;
//	int kmax;
	CKehai0 KehaiWork;
	long lKehaiBuyPrice;
	long lPrice;
	int nNice;
	long lBuyPrice0;
	long lSellPrice;
	long lHighPrice;
	long lDiff;
	long lPreEndPrice;
	long lStopHighPrice;
	UINT nUp;
//	UINT nDown;
	long lLossCut;
//	CString strCode;
//	long lHazard;
//	BOOL bProfit;
//	BOOL bAveDownEq;
//	BOOL bHighHazard;
//	BOOL bLowHazard;
	int nSell;

	m_lVZan = m_lCashZan;

	for (i = 0, imax = m_UiaKabuHiashiIndex.GetSize(); i < imax; i ++) {
		j = m_UiaKabuHiashiIndex[i];
		KehaiWork = GetFunashi(j, m_UiaFunashiPaIndex[j]).m_Kehai;
		lKehaiBuyPrice = KehaiWork.m_plKehaiPrice[5];
		lPrice = lKehaiBuyPrice ? lKehaiBuyPrice : m_DwaFunashiPrice[j];
		lDiff = m_DwaKabuDiff[i] = GetDiff(lPrice);
		if (m_UiaKabuState[i] == 2) {
			nNice = m_UiaFunashiNice[j];
			lPreEndPrice = m_DwaHiashiPreEndPrice[j];
			if (lPreEndPrice == 0L)
				lPreEndPrice = m_DwaHiashiStartPrice[j];
			lStopHighPrice = lPreEndPrice + m_DwaHiashiStopDiff[j];
			lBuyPrice0 = m_DwaKabuBuyPrice0[i];
			nUp = m_UiaKabuUp[i];
//			nDown = m_UiaKabuDown[i];
			lSellPrice = lKehaiBuyPrice ? lBuyPrice0 : lBuyPrice0 + lDiff;
//			lLossCut = lSellPrice - lDiff * LOSS_CUT_DIFF;
			lLossCut = m_DwaKabuBuyPrice1[i];
//			strCode = m_SaHiashiCode[j];
//			for (k = 0, kmax = m_SaNiceCode.GetSize(); k < kmax; k ++)
//				if (m_SaNiceCode[k] == strCode) {
//					if ((long)m_DwaNiceLockOn[k] < lLossCut)
//						lLossCut = m_DwaNiceLockOn[k];
//					break;
//				}
//			lHazard = lSellPrice - lDiff * HAZARD_DIFF;
//			bProfit = lPrice >= lSellPrice;
//			bAveDownEq = (nNice & 0x80000000) == 0;
//			bHighHazard = nNice & 0x20000000;
//			bLowHazard = nNice & 0x10000000;

			if (lPrice > (long)m_DwaKabuHighPrice[i])
				m_DwaKabuHighPrice[i] = lPrice;
			if (lPrice < (long)m_DwaKabuLowPrice[i])
				m_DwaKabuLowPrice[i] = lPrice;
			lHighPrice = m_DwaKabuHighPrice[i];

//			if (nDown >= 2  &&  bProfit)
//				nDown = m_UiaKabuDown[i] = 0;

			nSell = 0;
//			if ((nNice & 0x10) == 0) {
//				if (bProfit  &&  bHighHazard)
//					nSell |= 0x100;
//				if (nNice & 0x01)
//					nSell |= 0x0;
//				if (bProfit  &&  nNice & 0x01)
//					nSell |= 0x80;
				if (lPrice >= lStopHighPrice)
					nSell |= 0x40;
//				if (lPrice < lHighPrice  &&  lPrice >= lSellPrice  &&  lPrice <= lBuyPrice0 + (lHighPrice - lBuyPrice0) * AVEUP_PROFIT_CUT_A / AVEUP_PROFIT_CUT_B)
//					nSell |= 0x20;
//				if (bAveDownEq  &&  lPrice < lHighPrice  &&  lPrice >= lSellPrice  &&  lPrice <= lBuyPrice0 + (lHighPrice - lBuyPrice0) * PROFIT_CUT_A / PROFIT_CUT_B)
				if (lHighPrice >= lBuyPrice0 + lDiff * 3  &&  lPrice <= lBuyPrice0 + (lHighPrice - lBuyPrice0) * PROFIT_CUT_A / PROFIT_CUT_B)
					nSell |= 0x10;
//				if (bAveDownEq  &&  nDown < 2  &&  lPrice <= lLossCut  &&  lPrice > lHazard)
//				if (bAveDownEq  &&  lPrice <= lLossCut  &&  lPrice > lHazard)
//				if (lPrice <= lLossCut  &&  lPrice > lHazard)
				if (lPrice < lLossCut)
					nSell |= 0x08;
				if (nUp  &&  lPrice <= lSellPrice)
//					nSell |= 0x0;
					nSell |= 0x04;
//				if (bAveDownEq  &&  nDown == 1  &&  bProfit)
//				if (bAveDownEq && nDown && bProfit)
//				if (nDown && bProfit)
//					nSell |= 0x04;
//				if (nDown >= 2  &&  lPrice > lHazard)
//					nSell |= 0x04;
//				if (lPrice > lSellPrice)
//					nSell |= 0x0;
//				if (bAveDownEq  &&  bProfit  &&  m_UiaFunashiPriceMinutes[j] >= SELL_PRICE_MINUTE)
//					nSell |= 0x02;
//				if (bAveDownEq  &&  nDown >= 1 + SELL_HAZARD_MINUTE)
//					nSell |= 0x01;
//			}
			m_UiaKabuSell[i] = nSell;
//			if (nSell)
//				m_UiaFunashiNice[j] &= 0xffffffef;

//			if (lPrice >= lSellPrice)
			if (lPrice > lSellPrice)
				m_UiaKabuUp[i] = 1;
//			if (lPrice < (m_UiaKabuUp[i] ? lSellPrice : (long)m_DwaKabuBuyPrice1[i]))
//				if (lPrice <= lHazard)
//					if (nDown < 2)
//						m_UiaKabuDown[i] = 2;
//					else
//						m_UiaKabuDown[i] ++;
//				else
//					if (nDown < 1)
//						m_UiaKabuDown[i] = 1;

		}
		m_lVZan += (lKehaiBuyPrice ? lKehaiBuyPrice : lPrice - lDiff) * m_WaHiashiUnit[j] * m_DwaKabuUnitCount[i];
	}
}

void CAutoTraderDlg::Buy()
{
	int i;
	int j;
	int k;
	int l;
	int imax;
	CString strCode;
	short sUnit;
	long lUnitCount = 1L;
	long lDiff;
	CKehai0 KehaiWork;
	long lKehaiSellPrice;
	long lKehaiBuyPrice;
	long lPrice;
	long lBuyPrice;
	long lSetPrice;
	long lPreEndPrice;
	long lStopHighPrice;
	long lBuyTotalPrice;
//	int nState;
	int nReceiptNo = -1;
	CWnd* pWnd;
	int nStk;

	for (i = 0, imax = m_UiaNiceBuyHiashiIndex.GetSize(); i < imax; i ++) {
		j = m_UiaNiceBuyHiashiIndex[i];
		k = m_UiaFunashiPaIndex[j];
		KehaiWork = GetFunashi(j, k).m_Kehai;
		lKehaiSellPrice = KehaiWork.m_plKehaiPrice[4];
		lKehaiBuyPrice = KehaiWork.m_plKehaiPrice[5];
		lDiff = GetDiff(lKehaiBuyPrice + 1L);
		lPrice = lBuyPrice = lKehaiBuyPrice ? lKehaiBuyPrice + lDiff : m_DwaFunashiPrice[j];
		for (l = 0; l < BUY_DIFF; l ++)
			lBuyPrice += GetDiff(lBuyPrice + 1L);
		lPreEndPrice = m_DwaHiashiPreEndPrice[j];
		if (lPreEndPrice == 0L)
			lPreEndPrice = m_DwaHiashiStartPrice[j];
		lStopHighPrice = lPreEndPrice + m_DwaHiashiStopDiff[j];
		sUnit = m_WaHiashiUnit[j];
		lBuyTotalPrice = m_DwaHiashiBuyTotalPrice[j];
		lUnitCount = (m_lCashZan - lBuyTotalPrice - ZAN_OUTPUT) / (lBuyPrice * sUnit) * sUnit;
		lSetPrice = lBuyPrice * sUnit * lUnitCount;
		if (lBuyPrice < lStopHighPrice  &&  m_lCashZan - lBuyTotalPrice >= lSetPrice) {
			strCode = m_SaHiashiCode[j];

/*
			nState = 1;

			if (lKehaiSellPrice == 0L)
				m_lVZan -= lDiff * sUnit * lUnitCount;
			m_lCashZan -= lSetPrice;
			m_DwaHiashiBuyTotalPrice[j] += lSetPrice;
			m_DwaHiashiBuyUnitCount[j] += lUnitCount;
			m_UiaKabuHiashiIndex.Add(j);
			m_UiaKabuReceiptNo.Add(nReceiptNo);
			m_UiaKabuState.Add(nState);
			m_UiaKabuStateMinutes.Add(0U);
			m_UiaKabuTseiKaisu.Add(0U);
			m_DtaKabuFunashiPaDateTime.Add(((COleDateTimeArray *)m_PaFunashiDateTime[j])->GetAt(k));
			m_DwaKabuBuyPrice0.Add(lBuyPrice);
			m_DwaKabuBuyPrice1.Add(lKehaiBuyPrice ? lKehaiBuyPrice : lPrice);
			m_DwaKabuSellPrice.Add(0UL);
			m_DwaKabuHighPrice.Add(lPrice);
			m_DwaKabuLowPrice.Add(lPrice);
			m_DwaKabuUnitCount.Add(lUnitCount);
			m_DwaKabuDiff.Add(lDiff);
			m_UiaKabuUp.Add(0U);
			m_UiaKabuDown.Add(0U);
			m_UiaKabuSell.Add(0U);
*/

			if (! m_nExecMode) {
				nStk = atoi(strCode.Left(4));
				if ((pWnd = FindWindow(NULL, m_strTradeHelperWndName)))
					pWnd->PostMessage(WM_USER + 3, nStk, lBuyPrice);
				if ((pWnd = FindWindow(NULL, m_strChartViewerWndName)))
					pWnd->PostMessage(WM_USER + 4, nStk, lBuyPrice);
				if ((pWnd = FindWindow(NULL, m_strKehaiViewerWndName)))
					pWnd->PostMessage(WM_USER + 4, nStk, lBuyPrice);
			}

			DispLog(
				"%s %ld 買 %s %s %ld円 単%d x%d 変%ld円 優%08x\n",
				(m_nExecMode == 1 ? m_DtSim : GetCurrentTimeEx()).Format("%H:%M:%S"),
				m_lVZan, strCode, m_SaHiashiName[j], lBuyPrice, sUnit, lUnitCount, lDiff, m_UiaFunashiNice[j]
			);
		}
	}
}

void CAutoTraderDlg::Sell()
{
	int i;
	int j;
	int k;
	int l;
	int imax;
	CFunashi0 FunashiWork;
	long lKehaiSellPrice;
	long lKehaiBuyPrice;
	long lPrice;
	long lDiff;
	long lBuyPrice;
	long lSellPrice;
	short sUnit;
	long lUnitCount = 1L;
	long lSetPrice;
	long lCurDiff;
	long lHighDiff;
	long lLowDiff;
	long lProfit;
	int nState;
	int nReceiptNo = -1;

	BOOL bGetUrlList = FALSE;
	CString strCode;

	for (i = 0, imax = m_UiaKabuHiashiIndex.GetSize(); i < imax; i ++)
		if (m_UiaKabuState[i] == 2  &&  m_UiaKabuSell[i]) {
			j = m_UiaKabuHiashiIndex[i];
			k = m_UiaFunashiPaIndex[j];
			FunashiWork = GetFunashi(j, k);
			CKehai0& KehaiWork = FunashiWork.m_Kehai;
			lKehaiSellPrice = KehaiWork.m_plKehaiPrice[4];
			lKehaiBuyPrice = KehaiWork.m_plKehaiPrice[5];
			lPrice = lKehaiBuyPrice ? lKehaiBuyPrice : m_DwaFunashiPrice[j];
			lDiff = m_DwaKabuDiff[i];
			lBuyPrice = m_DwaKabuBuyPrice0[i];
			lSellPrice = lKehaiSellPrice ? lKehaiSellPrice : lPrice;
			for (l = 0; l < BUY_DIFF + 1; l ++)
				lSellPrice -= GetDiff(lSellPrice);
			sUnit = m_WaHiashiUnit[j];
			lUnitCount = m_DwaKabuUnitCount[i];
			lSetPrice = lSellPrice * sUnit * lUnitCount;
			lCurDiff = (lPrice - lBuyPrice) / lDiff;
			lHighDiff = ((long)m_DwaKabuHighPrice[i] - lBuyPrice) / lDiff;
			lLowDiff = ((long)m_DwaKabuLowPrice[i] - lBuyPrice) / lDiff;
			lProfit = (lSellPrice - lBuyPrice) * sUnit * lUnitCount;

			strCode = m_SaHiashiCode[j];

			nState = 3;

			m_UiaKabuReceiptNo[i] = nReceiptNo;
			m_UiaKabuState[i] = nState;
			m_UiaKabuStateMinutes[i] = 0U;
			m_DtaKabuFunashiPaDateTime[i] = FunashiWork.m_DtDateTime;
			m_DwaKabuSellPrice[i] = lSellPrice;

			if (! m_nExecMode) {
				CWnd* pWnd;
				if ((pWnd = FindWindow(NULL, m_strTradeHelperWndName)))
					pWnd->PostMessage(WM_USER + 4, atoi(strCode.Left(4)), lSellPrice);
			}

			DispLog(
				"%s %ld 売 %s %s %ld円 単%d x%d 変%ld円 優%08x 判%03x 現%ld 高%ld 低%ld 利%ld円\n",
				(m_nExecMode == 1 ? m_DtSim : GetCurrentTimeEx()).Format("%H:%M:%S"),
				m_lVZan, strCode, m_SaHiashiName[j], lSellPrice, sUnit, lUnitCount, lDiff, m_UiaFunashiNice[j], m_UiaKabuSell[i], lCurDiff, lHighDiff, lLowDiff, lProfit
			);
		}
}

void CAutoTraderDlg::SellAll()
{
	int i;
	int imax;

	for (i = 0, imax = m_UiaKabuHiashiIndex.GetSize(); i < imax; i ++)
		switch (m_UiaKabuState[i]) {
		case 1:
			m_UiaKabuState[i] = 5;
			break;
		case 2:
			m_UiaKabuSell[i] |= 0x800;
		}
}

void CAutoTraderDlg::Start()
{
	m_bTrade = TRUE;
	m_bSimStop = FALSE;
	DispLog(
		"%s %ld 開始\n",
		(m_nExecMode == 1 ? m_DtSim : GetCurrentTimeEx()).Format("%H:%M:%S"),
		m_lVZan
	);
}

void CAutoTraderDlg::End()
{
	m_bTrade = FALSE;
	Disp();
	DispLog(
		"%s %ld 終了\n",
		(m_nExecMode == 1 ? m_DtSim : GetCurrentTimeEx()).Format("%H:%M:%S"),
		m_lVZan
	);
}

void CAutoTraderDlg::CreatePriceList()
{
	try
	{
		COleVariant var;
		CString strCode;
		CString strSijo;
		CString strCodeEx;
		CString strName;
		CString strSijoName;
		short sUnit;
		long lStartPrice;
		long lHighPrice;
		long lLowPrice;
		long lPrice;
		long lTradeCount;
		long lPreEndPrice;
		long lStopDiff;
		long lStopHighPrice;
		long lStopLowPrice;
		long lDiff;
		CMapStringToPtr MstsPrice;
		void* pValue;
		CStringBuffer sb;

		CDaoDatabase Database;
		Database.Open(m_strDBFPath, FALSE, TRUE);

		CDaoRecordset RsHiashi(&Database);

		RsHiashi.Open(
			dbOpenSnapshot,
			StrFormat(
				"SELECT "
					TBL_HIASHI "." FLD_HI_CODE ", "
					TBL_HIASHI "." FLD_HI_PRICE
				" FROM " TBL_HIASHI
				" WHERE "
					TBL_HIASHI "." FLD_HI_DATE " = #%s#",
				m_DtPreDate.Format("%Y/%m/%d")
			),
			dbForwardOnly
		);
		while (! RsHiashi.IsEOF()) {
			RsHiashi.GetFieldValue(0, var);
			strCode = V_BSTRT((LPVARIANT)var);
			RsHiashi.GetFieldValue(1, var);
			lPrice = var.lVal;

			MstsPrice[strCode] = (void *)lPrice;

			RsHiashi.MoveNext();
		}
		RsHiashi.Close();

		RsHiashi.Open(
			dbOpenSnapshot,
			StrFormat(
				"SELECT "
					TBL_INFO "." FLD_IN_CODE ", "
					TBL_INFO "." FLD_IN_NAME ", "
					TBL_INFO "." FLD_IN_SIJO ", "
					TBL_INFO "." FLD_IN_UNIT ", "
					TBL_HIASHI "." FLD_HI_STARTPRICE ", "
					TBL_HIASHI "." FLD_HI_HIGHPRICE ", "
					TBL_HIASHI "." FLD_HI_LOWPRICE ", "
					TBL_HIASHI "." FLD_HI_PRICE ", "
					TBL_HIASHI "." FLD_FU_TRADECOUNT
				" FROM " TBL_INFO ", " TBL_HIASHI
				" WHERE "
					TBL_INFO "." FLD_IN_CODE " = " TBL_HIASHI "." FLD_HI_CODE
					" AND " TBL_HIASHI "." FLD_HI_DATE " = #%s#",
				m_DtDate.Format("%Y/%m/%d")
			),
			dbForwardOnly
		);
		while (! RsHiashi.IsEOF()) {
			RsHiashi.GetFieldValue(0, var);
			strCode = strCodeEx = V_BSTRT((LPVARIANT)var);
			RsHiashi.GetFieldValue(1, var);
			strName = V_BSTRT((LPVARIANT)var);
			RsHiashi.GetFieldValue(2, var);
			strSijoName = V_BSTRT((LPVARIANT)var);
			RsHiashi.GetFieldValue(3, var);
			sUnit = var.iVal;
			RsHiashi.GetFieldValue(4, var);
			lStartPrice = var.lVal;
			RsHiashi.GetFieldValue(5, var);
			lHighPrice = var.lVal;
			RsHiashi.GetFieldValue(6, var);
			lLowPrice = var.lVal;
			RsHiashi.GetFieldValue(7, var);
			lPrice = var.lVal;
			RsHiashi.GetFieldValue(8, var);
			lTradeCount = var.lVal;

			strSijo = strCode.Mid(5);
			if (strSijo == "T") {
				if (strSijoName == "東証ﾏｻﾞｰｽﾞ")
					strCodeEx += 'M';
				else if (strSijoName == "東証２部")
					strCodeEx += '2';
			} else if (strSijo == "O")
				if (strSijoName == "大証２部")
					strCodeEx += '2';

			if (MstsPrice.Lookup(strCode, pValue))
				lPreEndPrice = (long)pValue;
			else
				lPreEndPrice = 0L;
			if (lPreEndPrice == 0L)
				lPreEndPrice = lStartPrice;

			lStopDiff = GetStopDiff(lPreEndPrice);

			lStopHighPrice = lPreEndPrice + lStopDiff;
			lDiff = GetDiff(lStopHighPrice);
			lStopHighPrice = lStopHighPrice / lDiff * lDiff + (lStopHighPrice % lDiff ? lDiff : 0L);

			lStopLowPrice = lPreEndPrice - lStopDiff;
			lDiff = GetDiff(lStopLowPrice);
			lStopLowPrice = lStopLowPrice / lDiff * lDiff;

			if (lPrice) {
				lDiff = GetDiff(lPrice);

				sb +=
					StrFormat(
						"%s,%s,%s,%ld,%s,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%s,%ld,%s\n",
						strCode.Left(4),
						strCodeEx.Mid(5),
						strName,
						lPrice,
						lPrice == lStopHighPrice ? "S高" :  lPrice == lStopLowPrice ? "S安" : pszEmpty,
						lTradeCount * lDiff / 1000,
						sUnit * lDiff,
						lPrice * sUnit,
						(lPrice - lLowPrice) / lDiff,
						(lPrice - lPreEndPrice) * 100 / lStopDiff,
						lPreEndPrice,
						lStartPrice,
						lHighPrice,
						lHighPrice == lStopHighPrice ? "S高" : pszEmpty,
						lLowPrice,
						lLowPrice == lStopLowPrice ? "S安" : pszEmpty
					);
			}

			RsHiashi.MoveNext();
		}

		CString strFPath;
		strFPath.Format("%s\\PriceList.csv", m_strDataDir);
		CStdioFile StdioFile(strFPath, CFile::modeCreate | CFile::modeWrite);
		StdioFile.WriteString(sb);
		StdioFile.Close();
	}
	catch (CException* pEx) {
		DispErrorLog("株価リスト生成エラー: %s\n", GetExceptionErrorMessage(pEx));
		pEx->Delete();
	}
}

void CAutoTraderDlg::CreateNiceList()
{
	int i;
	int imax;
	CStringBuffer sb;

	if (m_nExecMode == 1  &&  FunashiAnalyze(0, &m_DtSim1)  ||  m_nExecMode != 1  &&  FunashiAnalyze(0))
		for (i = 0, imax = m_SaHiashiCode.GetSize(); i < imax; i ++)
			sb += StrFormat("%s,%s,%d,%08x,%ld,%ld,%d,%ld,%ld,%ld,%ld\n", m_SaHiashiCode[i], m_SaHiashiName[i], m_DwaHiashiPreEndTradeCount[i] / m_WaHiashiUnit[i], m_UiaFunashiNice[i], m_DwaFunashiPrice[i], m_DwaHiashiPreEndPrice[i], m_WaHiashiUnit[i], m_DwaHiashiPreEndPrice[i] * m_WaHiashiUnit[i], GetDiff(m_DwaHiashiPreEndPrice[i]) * m_WaHiashiUnit[i], m_DwaHiashiPriceDiffAve[i], m_DwaHiashiPriceDiffAve[i] * GetDiff(m_DwaHiashiPreEndPrice[i]) * 100 / m_DwaHiashiPreEndPrice[i]);

	CString strFPath;
	strFPath.Format("%s\\NiceList.csv", m_strDataDir);
	CStdioFile StdioFile(strFPath, CFile::modeCreate | CFile::modeWrite);
	StdioFile.WriteString(sb);
	StdioFile.Close();
}

int CAutoTraderDlg::CodeToName(CString& strCode, CString& strName, CString* pstrSijoName, short* psUnit, long* plHighPrice, long* plLowPrice, long* plPreEndPrice, long* plTradeCount, CString* pstrCodeEx) 
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
						CString strSijo;

						*pstrCodeEx = strMainCode;
						strSijo = strMainCode.Mid(5);
						if (strSijo == "T") {
							if (strSijoName == "東証ﾏｻﾞｰｽﾞ")
								*pstrCodeEx += 'M';
							else if (strSijoName == "東証２部")
								*pstrCodeEx += '2';
						} else if (strSijo == "O")
							if (strSijoName == "大証２部")
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

void CAutoTraderDlg::ChangeEditCode(int nID0, int nID1) 
{
	CString strCode;
	CString strName;
	CWnd* pWnd = GetDlgItem(nID0);
	pWnd->GetWindowText(strCode);
	if (strCode.GetLength() >= 4) {
		CodeToName(strCode, strName);
		pWnd->SetWindowText(strCode);
	}
	GetDlgItem(nID1)->SetWindowText(strName);
}

void CAutoTraderDlg::Check10(int nIndex)
{
	int i;
	int imax;
	CString strCode = m_SaNiceCode[nIndex];
	long* plFunashi;
	CKehai0 KehaiWork;
	long lKehaiBuyPrice;
	long lKehaiCurPrice = 0L;

	for (i = 0, imax = m_SaHiashiCode.GetSize(); i < imax; i ++)
		if (m_SaHiashiCode[i] == strCode)
			break;
	if (((CButton *)GetDlgItem(IDC_CHECK10 + nIndex))->GetCheck() == 1) {
		plFunashi = (long *)m_PaFunashi[i];
		KehaiWork = GetFunashi(plFunashi, m_UiaFunashiPaIndex.GetSize() ? m_UiaFunashiPaIndex[i] : plFunashi[-1] - 1).m_Kehai;
		lKehaiBuyPrice = KehaiWork.m_plKehaiPrice[5];
		if (KehaiWork.m_plKehaiCount[4] < KehaiWork.m_plKehaiCount[5])
			lKehaiCurPrice = lKehaiBuyPrice;
		else
			lKehaiCurPrice = lKehaiBuyPrice - GetDiff(lKehaiBuyPrice);
	}
	m_DwaNiceLockOn[nIndex] = lKehaiCurPrice;
	WritePrivateProfileString(PF_APP_GENERAL, PF_KEY_LOCKON + IToA(nIndex), LToA(lKehaiCurPrice), m_strMeigaraIniFPath);
	CWnd* pWnd;
	if (pWnd = FindWindow(NULL, m_strChartViewerWndName))
		pWnd->PostMessage(WM_USER + 3);

	if (lKehaiCurPrice)
		DispLog(
			"%s %ld ロックオン %s %s %ld円\n",
			GetCurrentTimeEx().Format("%H:%M:%S"),
			m_lVZan, strCode, m_SaHiashiName[i], lKehaiCurPrice
		);
	else
		DispLog(
			"%s %ld ロックオフ %s %s\n",
			GetCurrentTimeEx().Format("%H:%M:%S"),
			m_lVZan, strCode, m_SaHiashiName[i]
		);
}

void CAutoTraderDlg::SetMeigara(int nFromIndex, LPCTSTR lpszToCode) 
{
	int i;
	int imax;
	CString strFromCode;
	int nNiceSize = m_SaNiceCode.GetSize();
	CString strCode;
	CString strName;
	CDaoDatabase Database;
	CWnd* pWnd;
	void* pVoid;

	if (m_bSetTimer2  &&  m_nExecMode != 1)
		KillWMUserTimer(2);

	if (nFromIndex != -1  &&  nFromIndex < m_SaNiceCode.GetSize())
		strFromCode = m_SaNiceCode[nFromIndex];

	m_Edit16.SetWindowText(pszEmpty);
	if (m_nExecMode)
		for (i = 0; i < 10; i ++) {
			GetDlgItem(IDC_EDIT20 + i)->SetWindowText(pszEmpty);
			((CButton *)GetDlgItem(IDC_CHECK10 + i))->SetCheck(0);
		}

	if (m_nExecMode) {
		RemoveAllNiceCode();

		try
		{
			COleDateTime DtStart;
//			COleDateTime DtEnd;
			CMapStringToPtr MstpCode;
			COleVariant pKeyArray[2];
			COleVariant var;

			if (m_nExecMode == 2) {
				Database.Open(m_strOrgDBFPath, FALSE, TRUE);

				DtStart = GetCurrentTimeEx();
			} else {
				Database.Open(m_strDBFPath, FALSE, TRUE);

				GetSimDateTime();
				DtStart = m_DtSim0;
//				if (DtStart.GetHour() == 8  &&  DtStart.GetMinute() == 0)
//					DtStart.SetDateTime(DtStart.GetYear(), DtStart.GetMonth(), DtStart.GetDay(), 8, 20, 0);
			}
//			DtEnd = FixDateTime(DtStart + COleDateTimeSpan(0, 0, 0, 2));

			CDaoRecordset RsFunashi(&Database);

			RsFunashi.Open(dbOpenTable, TBL_FUNASHI0);
			RsFunashi.SetCurrentIndex(pszPrimaryKey);
			pKeyArray[0] = COleVariant(DtStart);
			if (RsFunashi.Seek(">", pKeyArray, 2)) {
				MstpCode["101"] = NULL;
				i = 0;
				do {
//					RsFunashi.GetFieldValue(0, var);
//					if (var.date > DtEnd)
//						break;

					RsFunashi.GetFieldValue(1, var);
					strCode = V_BSTRT((LPVARIANT)var);
					if (! MstpCode.Lookup(strCode, pVoid)) {
						GetDlgItem(IDC_EDIT20 + i)->SetWindowText(strCode);
						SetNiceCode(strCode);
						MstpCode[strCode] = NULL;
						DispLog("%s 登録銘柄コード: %s\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), strCode);
						if (++ i >= 10)
							break;
					}

					RsFunashi.MoveNext();
				} while (! RsFunashi.IsEOF());
			}
		}
		catch (CException* pEx) {
			DispErrorLog("銘柄登録エラー: %s\n", GetExceptionErrorMessage(pEx));
			pEx->Delete();
		}
	} else {
		if (nFromIndex == -1) {
			CEdit* pEdit;

			RemoveAllNiceCode();
			for (i = 0; i < 10; i ++) {
				pEdit = (CEdit *)GetDlgItem(IDC_EDIT20 + i);
				pEdit->GetWindowText(strCode);
				if (strCode.GetLength()) {
					CodeToName(strCode, strName);
					pEdit->SetWindowText(strCode);
				}
				SetNiceCode(strCode);
			}
		} else
			SetNiceCode(lpszToCode, nFromIndex);
	}

	if (m_nExecMode != 1) {
		if (nNiceSize || m_SaNiceCode.GetSize()) {
			DispLog("%s 銘柄日足データ分析開始\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"));
			if (m_nExecMode  ||  nFromIndex == -1  &&  ! lpszToCode) {
				if (HiashiAnalyze(m_nExecMode ? &m_DtSim0 : NULL))
					goto CleanUp;
				for (i = 0, imax = m_SaNiceCode.GetSize(); i < imax; i ++) {
					strCode = m_SaNiceCode[i];
					if (strCode.GetLength()  &&  ! m_MstpHiashiCode.Lookup(strCode, pVoid))
						if (HiashiAnalyze(m_nExecMode ? &m_DtSim0 : NULL, strCode, 1))
							goto CleanUp;
				}
			} else if (! lpszToCode  ||  ! *lpszToCode  ||  m_MstpHiashiCode.Lookup(lpszToCode, pVoid)) {
				if (strFromCode.GetLength()  &&  ! m_MstpSelCode.Lookup(strFromCode, pVoid)  &&  ! m_MstpNiceCode.Lookup(strFromCode, pVoid)) {
					m_MstpHiashiCode.Lookup(strFromCode, pVoid);
					HiashiDel((int)pVoid);
				}
			} else {
				if (nFromIndex == -1  ||  strFromCode.IsEmpty()  ||  m_MstpSelCode.Lookup(strFromCode, pVoid)  ||  m_MstpNiceCode.Lookup(strFromCode, pVoid)) {
					if (HiashiAnalyze(NULL, lpszToCode, 1))
						goto CleanUp;
				} else {
					m_MstpHiashiCode.Lookup(strFromCode, pVoid);
					if (HiashiAnalyze(NULL, lpszToCode, 2, (int)pVoid))
						goto CleanUp;
				}
			}
			DispLog("%s 銘柄日足データ分析終了 日足銘柄数: %d,  Funashi: %ld/%ld, %ld/%ld, %ld/%ld\n", COleDateTime::GetCurrentTime().Format("%H:%M:%S"), m_SaHiashiCode.GetSize(), m_lFunashi0Count, m_nMemMapF0Count, m_lFunashi1Count, m_nMemMapF1Count, m_lFunashi2Count, m_nMemMapF2Count);

			if (m_bSetTimer2)
				SetWMUserTimer((TIMEUNIT - GetCurrentTimeEx().GetSecond() % TIMEUNIT) * 1000, 2, NULL);
		}

		SaveNiceCode();
		SaveSelCode();
		SaveHiashiCode();

		if (pWnd = FindWindow(NULL, m_strTradeHelperWndName))
			pWnd->PostMessage(WM_USER + 2);
		if (pWnd = FindWindow(NULL, m_strChartViewerWndName))
			pWnd->PostMessage(WM_USER + 2);
		if (pWnd = FindWindow(NULL, m_strKehaiViewerWndName))
			pWnd->PostMessage(WM_USER + 2);
	}

CleanUp:
	;
}

void CAutoTraderDlg::SaveNiceCode()
{
	int i;
	int imax;
	CStringBuffer sbI;

	for (i = 0, imax = m_SaNiceCode.GetSize(); i < 10; i ++) {
		sbI = IToA(i);
		if (i < imax) {
			WritePrivateProfileString(PF_APP_GENERAL, PF_KEY_CODE + sbI, m_SaNiceCode[i], m_strMeigaraIniFPath);
			WritePrivateProfileString(PF_APP_GENERAL, PF_KEY_LOCKON + sbI, LToA(m_DwaNiceLockOn[i]), m_strMeigaraIniFPath);
		} else {
			WritePrivateProfileString(PF_APP_GENERAL, PF_KEY_CODE + sbI, NULL, m_strMeigaraIniFPath);
			WritePrivateProfileString(PF_APP_GENERAL, PF_KEY_LOCKON + sbI, NULL, m_strMeigaraIniFPath);
		}
	}
}

void CAutoTraderDlg::SaveSelCode()
{
	int i;
	int imax;
	CStringBuffer sbI;

	for (i = 0, imax = m_SaSelCode.GetSize(); i < 1000; i ++) {
		sbI = IToA(i);
		if (i < imax)
			WritePrivateProfileString(PF_APP_GENERAL, PF_KEY_SELCODE + sbI, m_SaSelCode[i], m_strMeigaraIniFPath);
		else
			WritePrivateProfileString(PF_APP_GENERAL, PF_KEY_SELCODE + sbI, NULL, m_strMeigaraIniFPath);
	}
}

void CAutoTraderDlg::SaveHiashiCode()
{
	int i;
	int j;
	int imax;
	CString strCode;
	void* pVoid;

	for (i = 0; i < 10; i ++)
		WritePrivateProfileString(PF_APP_GENERAL, PF_KEY_HIASHICODE + IToA(i), NULL, m_strMeigaraIniFPath);
	for (i = 1, j = 0, imax = m_SaHiashiCode.GetSize(); i < imax; i ++) {
		strCode = m_SaHiashiCode[i];
		if (! m_MstpSelCode.Lookup(strCode, pVoid))
			WritePrivateProfileString(PF_APP_GENERAL, PF_KEY_HIASHICODE + IToA(j ++), strCode, m_strMeigaraIniFPath);
	}
}

void CAutoTraderDlg::LoadLastStatus()
{
	int i;
	char pszBuf[MAX_PATH];

	CString strIniDate(COleDateTime().Format("%Y/%m/%d"));
	CString strAutoTraderUpdateDate;
	int pnPfDefault[] = {
		0,
		0
	};
	CString* ppstrPfDefault[] = {
		NULL,
		&strIniDate
	};
	int* ppnPfValue[] = {
		&m_nAutoTraderUpdateType,
		NULL
	};
	CString* ppstrPfValue[] = {
		NULL,
		&strAutoTraderUpdateDate
	};
	BOOL* ppbPfValue[] = {
		NULL,
		NULL
	};
	for (i = 0; ppszPfKey[i]; i ++) {
		if (ppstrPfDefault[i]) {
			GetPrivateProfileString(PF_APP_GENERAL, ppszPfKey[i], *ppstrPfDefault[i], pszBuf, MAX_PATH, m_strLastStatusIniFPath);
			if (ppstrPfValue[i])
				*ppstrPfValue[i] = pszBuf;
			else
				*ppbPfValue[i] = stricmp(pszBuf, "True") == 0;
		} else
			*ppnPfValue[i] = GetPrivateProfileInt(PF_APP_GENERAL, ppszPfKey[i], pnPfDefault[i], m_strLastStatusIniFPath);
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
}

void CAutoTraderDlg::SaveLastStatus()
{
	// 変数宣言
	int i;
	// AutoTrader のアップデートチェック日付
	CString strAutoTraderUpdateDate = m_DtAutoTraderUpdateDate.Format("%Y/%m/%d");
	// LastStatus
	int pnPfValue[] = {
		m_nAutoTraderUpdateType,
		NULL
	};
	CString* ppstrPfValue[] = {
		NULL,
		&strAutoTraderUpdateDate
	};
	BOOL* ppbPfValue[] = {
		NULL,
		NULL
	};
	CString strPfValue;
	for (i = 0; ppszPfKey[i]; i ++) {
		if (ppstrPfValue[i])
			strPfValue = *ppstrPfValue[i];
		else if (ppbPfValue[i])
			strPfValue = *ppbPfValue[i] ? "True" : "False";
		else
			strPfValue = IToA(pnPfValue[i]);
		WritePrivateProfileString(PF_APP_GENERAL, ppszPfKey[i], strPfValue, m_strLastStatusIniFPath);
	}
	HKEY hKey = NULL;
	do {
		if (RegCreateKeyAutoTrader(hKey))
			break;
		CStringBuffer strData;
		LONG nRegFunc;
		strData = EncodeSecretString(m_strTreasureId);
		if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_TREASUREID, NULL, REG_SZ, (BYTE *)(LPCTSTR)strData, strData.GetLength())) != ERROR_SUCCESS) {
			MessageBox(_T("レジストリ設定エラー６: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
			break;
		}
		strData = EncodeSecretString(m_strTreasurePasswd);
		if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_TREASUREPWD, NULL, REG_SZ, (BYTE *)(LPCTSTR)strData, strData.GetLength())) != ERROR_SUCCESS) {
			MessageBox(_T("レジストリ設定エラー８: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
			break;
		}
		strData = EncodeSecretString(m_strMatsuiId);
		if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_MATSUIID, NULL, REG_SZ, (BYTE *)(LPCTSTR)strData, strData.GetLength())) != ERROR_SUCCESS) {
			MessageBox(_T("レジストリ設定エラー９: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
			break;
		}
		strData = EncodeSecretString(m_strMatsuiPasswd);
		if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_MATSUIPWD, NULL, REG_SZ, (BYTE *)(LPCTSTR)strData, strData.GetLength())) != ERROR_SUCCESS) {
			MessageBox(_T("レジストリ設定エラー１０: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
			break;
		}
		strData = EncodeSecretString(m_strCosmoId);
		if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_COSMOID, NULL, REG_SZ, (BYTE *)(LPCTSTR)strData, strData.GetLength())) != ERROR_SUCCESS) {
			MessageBox(_T("レジストリ設定エラー１１: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
			break;
		}
		strData = EncodeSecretString(m_strCosmoPasswd);
		if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_COSMOPWD, NULL, REG_SZ, (BYTE *)(LPCTSTR)strData, strData.GetLength())) != ERROR_SUCCESS) {
			MessageBox(_T("レジストリ設定エラー１２: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
			break;
		}
		strData = m_strDataDir;
		if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_DATAFOLDER, NULL, REG_SZ, (BYTE *)(LPCTSTR)strData, strData.GetLength())) != ERROR_SUCCESS) {
			MessageBox(_T("レジストリ設定エラー１３: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
			break;
		}
	} while (0);
	RegCloseKeyAutoTrader(hKey);
}

void CAutoTraderDlg::CompactDB()
{
	try {
		if (CFile::GetStatus(m_strTempDBFPath, m_FileStatus))
			if (! DeleteFile(m_strTempDBFPath)) {
				DispErrorLog("%s 削除エラー: %s\n", m_strTempDBFPath, GetLastErrorMessage());
				AfxThrowUserException();
			}

		try {
			CDaoWorkspace::CompactDatabase(m_strDBFPath, m_strTempDBFPath);
		}
		catch (CException* pEx) {
			DispErrorLog("DB の最適化/修復エラー: %s\n", GetExceptionErrorMessage);
			pEx->Delete();
			AfxThrowUserException();
		}

		if (! CopyFile(m_strTempDBFPath, m_strDBFPath, FALSE)) {
			DispErrorLog("%s %s コピーエラー: %s\n", m_strTempDBFPath, m_strDBFPath, GetLastErrorMessage());
			AfxThrowUserException();
		}
		if (! DeleteFile(m_strTempDBFPath)) {
			DispErrorLog("%s 削除エラー: %s\n", m_strTempDBFPath, GetLastErrorMessage());
			AfxThrowUserException();
		}
	}
	catch (CUserException* pEx) {
		pEx->Delete();
	}
}

void CAutoTraderDlg::SetNiceCode(LPCTSTR lpszAddCode, int nDelIndex)
{
	if (nDelIndex != -1) {
		CString strCode = m_SaNiceCode[nDelIndex];
		if (strCode.GetLength()) {
			BOOL bFound = FALSE;
			for (int i = 0, imax = m_SaNiceCode.GetSize(); i < imax; i ++)
				if (i != nDelIndex  &&  m_SaNiceCode[i] == strCode) {
					bFound = TRUE;
					break;
				}
			if (! bFound)
				m_MstpNiceCode.RemoveKey(strCode);
		}
	}
	if (lpszAddCode  &&  nDelIndex != -1) {
		m_SaNiceCode[nDelIndex] = lpszAddCode;
		m_DwaNiceLockOn[nDelIndex] = 0L;
		if (*lpszAddCode)
			m_MstpNiceCode[lpszAddCode] = NULL;
	} else if (lpszAddCode) {
		m_SaNiceCode.Add(lpszAddCode);
		m_DwaNiceLockOn.Add(0L);
		if (*lpszAddCode)
			m_MstpNiceCode[lpszAddCode] = NULL;
	} else if (nDelIndex != -1) {
		m_SaNiceCode[nDelIndex] = pszEmpty;
		m_DwaNiceLockOn[nDelIndex] = 0L;
	}
}

void CAutoTraderDlg::RemoveAllNiceCode()
{
	m_SaNiceCode.RemoveAll();
	m_DwaNiceLockOn.RemoveAll();
	m_MstpNiceCode.RemoveAll();
}

void CAutoTraderDlg::GetSimDateTime()
{
	CString strDateTime;
	m_Edit18.GetWindowText(strDateTime);
	m_DtSim0.ParseDateTime(strDateTime);
	COleDateTime DtCur = COleDateTime::GetCurrentTime();
	int nHour = DtCur.GetHour();
	int nMinute = DtCur.GetMinute();
	if (m_DtSim0.GetYear() == DtCur.GetYear()  &&  m_DtSim0.GetMonth() == DtCur.GetMonth()  &&  m_DtSim0.GetDay() ==  DtCur.GetDay()  &&  nHour >= 8  &&  (nHour < 15  ||  nHour == 15  &&  nMinute < 16))
//		m_DtSim1.SetDateTime(m_DtSim0.GetYear(), m_DtSim0.GetMonth(), m_DtSim0.GetDay(), 11, 1, 0);
		m_DtSim1.SetDateTime(m_DtSim0.GetYear(), m_DtSim0.GetMonth(), m_DtSim0.GetDay(), nHour, nMinute, 0);
	else
		m_DtSim1.SetDateTime(m_DtSim0.GetYear(), m_DtSim0.GetMonth(), m_DtSim0.GetDay(), 15, 16, 0);
}

void CAutoTraderDlg::TimeSim() 
{
	m_bTimeSim = TRUE;

	int nSize = m_SaHiashiCode.GetSize();
	m_DwaHiashiBuyTotalPrice.RemoveAll();
	m_DwaHiashiBuyUnitCount.RemoveAll();
	m_DwaHiashiBuyTotalPrice.SetSize(nSize);
	m_DwaHiashiBuyUnitCount.SetSize(nSize);
	m_UiaKabuHiashiIndex.RemoveAll();
	m_UiaKabuReceiptNo.RemoveAll();
	m_UiaKabuState.RemoveAll();
	m_UiaKabuStateMinutes.RemoveAll();
	m_UiaKabuTseiKaisu.RemoveAll();
	m_DtaKabuFunashiPaDateTime.RemoveAll();
	m_DwaKabuBuyPrice0.RemoveAll();
	m_DwaKabuBuyPrice1.RemoveAll();
	m_DwaKabuSellPrice.RemoveAll();
	m_DwaKabuHighPrice.RemoveAll();
	m_DwaKabuLowPrice.RemoveAll();
	m_DwaKabuUnitCount.RemoveAll();
	m_DwaKabuDiff.RemoveAll();
	m_UiaKabuUp.RemoveAll();
	m_UiaKabuDown.RemoveAll();
	m_UiaKabuSell.RemoveAll();
	m_lStartZan = m_lZan = m_lStartVZan = m_lVZan = m_lCashZan = ZAN;
	m_lKabuSellPlusCount =
	m_lKabuSellPlus =
	m_lKabuSellZeroCount =
	m_lKabuSellMinusCount =
	m_lKabuSellMinus =
		0;

	COleDateTimeSpan DtsSim(0, 0, 0, TIMEUNIT);
/*
	int nHour;
	int nMinute;
	int nSecond;
*/

	m_DtSim = m_DtSim0;
	Start();
	m_bDispLog = m_Check1.GetCheck() == 1;
	for (; m_DtSim <= m_DtSim1; m_DtSim = FixDateTime(m_DtSim + DtsSim)) {
		m_Edit18.SetWindowText(m_DtSim.Format("%Y/%m/%d %H:%M:%S"));
/*
		m_bDispLog = m_Check1.GetCheck() == 1;
		nHour = m_DtSim.GetHour();
		nMinute = m_DtSim.GetMinute();
		nSecond = m_DtSim.GetSecond();
		if (nHour >= 8  &&  nHour < 11  ||  nHour == 11  &&  nMinute < 1  ||  (nHour == 12  &&  nMinute >= 5  ||  nHour > 12)  &&  (nHour < 15  ||  nHour == 15  &&  (nMinute < 16  ||  nMinute == 16  &&  nSecond == 0))) {
*/
			FunashiAnalyze(0, &m_DtSim);
//			GetState();
//			SellJudge();
			if (m_bSimStop) {
//				if (m_UiaKabuReceiptNo.GetSize() == 0)
					break;
//				SellAll();
			}
/*
			Sell();
//			if (! m_bSimStop  &&  ! (nHour < 9  ||  nHour == 9  &&  nMinute == 0  &&  nSecond < TIMEUNIT * PATERN_PRICE_COUNT  ||  nHour == 12  &&  nMinute == 5  &&  nSecond < TIMEUNIT * PATERN_PRICE_COUNT  ||  nHour == TIMESIM_BUY_END_HOUR  &&  nMinute >= TIMESIM_BUY_END_MINUTE)) {
//			if (! m_bSimStop  &&  ! (nHour < 9  ||  nHour == 9  &&  nMinute == 0  &&  nSecond < TIMEUNIT * FUNASHI_LONG_COUNT  ||  nHour == 12  &&  nMinute == 5  &&  nSecond < TIMEUNIT * FUNASHI_LONG_COUNT  ||  nHour == TIMESIM_BUY_END_HOUR  &&  nMinute >= TIMESIM_BUY_END_MINUTE)) {
			if (! m_bSimStop  &&  ! (nHour < 9  ||  nHour == TIMESIM_BUY_END_HOUR  &&  nMinute >= TIMESIM_BUY_END_MINUTE)) {
				BuyJudge();
				Buy();
			}
//			if (nHour == 15  &&  nMinute == 0  ||  m_lVZan - m_lStartVZan < - m_lStartVZan / LOSS_STOP)
//			if (nHour == 15  &&  nMinute == 15  ||  m_lVZan - m_lStartVZan < - m_lStartVZan / LOSS_STOP)
//				m_bSimStop = TRUE;
			Disp();
		}
*/
	}
	m_Edit18.SetWindowText(m_DtSim0.Format("%Y/%m/%d %H:%M:%S"));
	End();

	m_bTimeSim = FALSE;
}

int CAutoTraderDlg::CheckLicense()
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

int CAutoTraderDlg::UpdateAutoTrader0()
{
	int nRv = 0;

	static const _TCHAR* ppszUpdateUrl[] = {URL_UPDATE0, URL_UPDATE0_BETA, URL_UPDATE0_ALPHA, URL_UPDATE1};
	static const _TCHAR* ppszUpdateTestUrl[] = {TESTURL_UPDATE0, TESTURL_UPDATE0_BETA, TESTURL_UPDATE0_ALPHA, URL_UPDATE1};

	if (m_nAutoTraderUpdateType == 6)
		nRv = 2;
	else {
		int i;
		CStringBuffer strUpdateTxt;
		int nPreVer0 = -1;
		int nPreVer1 = -1;
		int nVer0;
		int nVer1;
		CStringBuffer strUpdateUrl2;
		int nScanf;
		CStringBuffer strUpdateFNameFmt0(MAIN_EXENAME _T("%06d.EXE"));
		CStringBuffer strUpdateFNameFmt1(MAIN_EXENAME _T("%06da.EXE"));
		CStringBuffer strUpdateFPathFmt0(m_strDataDir + _T('\\') + strUpdateFNameFmt0);
		CStringBuffer strUpdateFPathFmt1(m_strDataDir + _T('\\') + strUpdateFNameFmt1);
		BOOL bFull;
		CStringBuffer strUpdateUrl;
		CStringBuffer strUpdateFName;
		CString strServerName;
		CString strObject;
		CPtrArray PaDlThread;
		CInternetSession Session;

		BOOL bTestUrl = FALSE;
		HKEY hKey;
		TCHAR szValueName[_MAX_PATH + 1] = _T("");
		_TCHAR lpRegData[MAX_PATH];
		DWORD cbRegDataSize;
		if (RegOpenKeyEx(HKEY_CURRENT_USER, REG_SUBKEY_TVCAT, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
			cbRegDataSize = MAX_PATH;
			bTestUrl = RegQueryValueEx(hKey, REG_KEY_TESTURL, NULL, NULL, (LPBYTE)lpRegData, &cbRegDataSize) == ERROR_SUCCESS;
			RegCloseKey(hKey);
		}

		m_pServer = NULL;

		for (i = 0; i < 3; i ++) {
			if (i == 0  &&  CFile::GetStatus(m_strUpdateTxtFPath, m_FileStatus)  ||  i == 2) {
				if (ReStrFile(m_strUpdateTxtFPath, strUpdateTxt)) {
					nRv = -1;
					break;
				}
				nScanf = _stscanf(strUpdateTxt, _T("%d %d %s"), &nVer0, &nVer1, strUpdateUrl2.GetBuffer(MAX_PATH));
				strUpdateUrl2.ReleaseBuffer();
				if (nScanf != 3) {
					DispErrorLog(_T("アップデートバージョン取得エラー\n"));
					nRv = -1;
					break;
				}
				if (i == 0) {
					nPreVer0 = nVer0;
					nPreVer1 = nVer1;
				} else {
					if (nPreVer0 > m_nThisVer) {
						if (nPreVer0 != nVer0)
							DeleteFile(StrFormat(strUpdateFPathFmt0, nPreVer0));
					} else if (nPreVer1 > m_nThisVer)
						if (nPreVer1 != nVer1)
							DeleteFile(StrFormat(strUpdateFPathFmt1, nPreVer1));
					if (nVer1 <= m_nThisVer)
						break;
					if (m_nAutoTraderUpdateType % 2) {
						nRv = 1;
						break;
					}
					bFull = nVer0 > m_nThisVer;
				}
			}

			if (i < 2)
				strUpdateFName = m_strUpdateTxtFName;
			else
				strUpdateFName = StrFormat(bFull ? strUpdateFNameFmt0 : strUpdateFNameFmt1, nVer1);

			if (i < 2)
				strUpdateUrl = (bTestUrl ? ppszUpdateTestUrl : ppszUpdateUrl)[i == 0 ? m_nAutoTraderUpdateType / 2 : 3];
			else
				strUpdateUrl = strUpdateUrl2;
			strUpdateUrl += strUpdateFName;

			if (! AfxParseURL(strUpdateUrl, m_dwServiceType, m_strServerName, m_strObject, m_nPort)) {
				DispErrorLog(_T("AutoTrader アップデート URL 解析エラー\n"));
				nRv = -1;
				break;
			}

			m_pServer = Session.GetHttpConnection(m_strServerName, m_nPort);

			if (
				DlFile(m_strDataDir + '\\' + strUpdateFName, CHttpConnection::HTTP_VERB_GET)
				&&  ! (i == 0  &&  (m_dwErr == 0xffffffff  ||  m_dwErr == ERROR_INTERNET_NAME_NOT_RESOLVED))
			) {
				nRv = -1;
				break;
			}
			if (i == 0  &&  (m_dwErr != 0xffffffff  &&  m_dwErr != ERROR_INTERNET_NAME_NOT_RESOLVED))
				i ++;
			if (i == 2)
				nRv = 1;
		}
		if (nRv < 0) {
			DeleteFile(m_strUpdateTxtFPath);
			DeleteFile(m_strDataDir + _T('\\') + strUpdateFName);
		} else {
			COleDateTime DtCur = COleDateTime::GetCurrentTime();
			m_DtAutoTraderUpdateDate.SetDate(DtCur.GetYear(), DtCur.GetMonth(), DtCur.GetDay());
		}
	}

	return nRv;
}

int CAutoTraderDlg::UpdateAutoTrader1()
{
	int nRv = 0;

	CStringBuffer strUpdateTxt;
	int nVer0;
	int nVer1;
	CStringBuffer strUpdateFNameFmt0(MAIN_EXENAME _T("%06d.EXE"));
	CStringBuffer strUpdateFNameFmt1(MAIN_EXENAME _T("%06da.EXE"));
	BOOL bFull;
	CStringBuffer strUpdateFName;

	while (CFile::GetStatus(m_strUpdateTxtFPath, m_FileStatus)) {
		if (ReStrFile(m_strUpdateTxtFPath, strUpdateTxt)) {
			nRv = -1;
			break;
		}
		if (_stscanf(strUpdateTxt, _T("%d %d"), &nVer0, &nVer1) != 2) {
			DispErrorLog(_T("アップデートバージョン取得エラー\n"));
			nRv = -1;
			break;
		}
		if (nVer1 <= m_nThisVer)
			break;
		bFull = nVer0 > m_nThisVer;
		strUpdateFName = StrFormat(bFull ? strUpdateFNameFmt0 : strUpdateFNameFmt1, nVer1);

		STARTUPINFO sInfo;
		PROCESS_INFORMATION pInfo;

		ZeroMemory(&sInfo, sizeof(sInfo));
		sInfo.cb = sizeof(sInfo);

		CStringBuffer strDocument;
		if (m_nAutoTraderUpdateType % 2)
			strDocument = _T("新しいバージョンの AutoTrader がリリースされてます");
		else {
			strDocument = _T("AutoTrader をアップデートできます。今すぐアップデートしますか？");
			if (m_OSVI.dwPlatformId == VER_PLATFORM_WIN32_NT)
				strDocument += _T("\n\nアップデートする場合、他のすべてのユーザーをログオフさせてください");
			if (! bFull)
				strDocument += _T("\n\nアップデートのウィザードで、「修復」、「削除」のラジオボタンは、「修復」を選択してください");
		}

		int i;
		int j;
		int imax;
		int jmax;
		int nIndex0 = 0;
		int nIndex1;
		CStringBuffer strLine;
		BOOL bDate;
		BOOL bVer;
		CStringArray SaDate;
		CStringArray SaVer;
		CStringArray SaDetail;
		i = -1;
		while ((nIndex1 = strUpdateTxt.Find(_T('\n'), nIndex0)) != -1) {
			strLine = strUpdateTxt.Mid(nIndex0, nIndex1 - nIndex0);
			if (strLine.IsEmpty()) {
				bDate = FALSE;
				bVer = FALSE;
				i ++;
			} else
				if (i >= 0)
					if (! bDate) {
						bDate = TRUE;
						SaDate.Add(strLine);
					} else if (! bVer) {
						bVer = TRUE;
						SaVer.Add(strLine);
						SaDetail.Add("");
					} else {
						if (SaDetail[i].GetLength())
							SaDetail[i] += "\n";
						SaDetail[i] += strLine;
					}
			nIndex0 = nIndex1 + 1;
		}
		CStringBuffer strUpdateDetail;
		CStringBuffer strDate;
		CStringBuffer strVer;
		CStringBuffer strDetail;
		int nVer;
		int nRev;
		int nThisRev = m_nThisVer % 100;
		BOOL bThisVerAlpha = nThisRev  &&  nThisRev < 51;
		BOOL bThisVer = FALSE;
		for (i = 0, imax = SaVer.GetSize(); i < imax; i ++) {
			strVer = SaVer[i];
			nVer = _ttoi(strVer);
			if (nVer == m_nThisVer)
				bThisVer = TRUE;
			if (nVer > m_nThisVer  &&  nVer <= nVer1  ||  ! bThisVer  &&  bThisVerAlpha) {
				nRev = _ttoi(strVer.Mid(4));

				strDate = SaDate[i];
				strDate.Insert(4, _T("/"));
				strDate.Insert(7, _T("/"));

				strVer = ConvVer(strVer);

				strDetail = SaDetail[i];
				if (strDetail.IsEmpty())
					if (nRev == 0) {
						for (j = i + 1, jmax = SaVer.GetSize(); j < jmax; j ++)
							if (_ttoi(SaVer[j].Mid(4)) >= 51)
								break;
						strDetail = _T("AutoTrader Ver.") + ConvVer(SaVer[j]) + _T(" を安定版としてリリース。");
					} else if (nRev >= 51) {
						for (j = i + 1, jmax = SaVer.GetSize(); j < jmax; j ++) {
							nRev = _ttoi(SaVer[j].Mid(4));
							if (nRev  &&  nRev < 51)
								break;
						}
						strDetail = _T("AutoTrader Ver.") + ConvVer(SaVer[j]) + _T(" をβ版としてリリース。");
					} else {
						for (j = i + 1, jmax = SaVer.GetSize(); j < jmax; j ++)
							if (_ttoi(SaVer[j].Mid(4)) >= 51)
								break;
						strDetail = _T("AutoTrader Ver.") + ConvVer(SaVer[j]) + _T(" のアップデート内容を適用。");
					}
				else
					strDetail.Replace(_T("\n"), _T("\r\n・"));
				strDetail = _T("・") + strDetail + _T("\r\n");

				if (strUpdateDetail.GetLength())
					strUpdateDetail += _T("\r\n");
				strUpdateDetail += strDate + _T(' ') + strVer + _T("\r\n") + strDetail;
			}
		}

		CUpdateDetailDlg UpdateDetailDlg;
		UpdateDetailDlg.m_lpszDocument = strDocument;
		UpdateDetailDlg.m_lpszUpdateDetail = strUpdateDetail;
		UpdateDetailDlg.m_uType = m_nAutoTraderUpdateType % 2 ? MB_OK : MB_OKCANCEL;
		if (UpdateDetailDlg.DoModal() != IDOK  ||  m_nAutoTraderUpdateType % 2) {
			m_bUpdateAutoTraderReq = FALSE;
			break;
		}

		if (m_OSVI.dwPlatformId == VER_PLATFORM_WIN32_NT) {
			CStringBuffer strNewDir(m_strDataDir + _T("\\") MAIN_EXENAME _T("999999b"));
			if (! CreateDirectory(strNewDir, NULL)) {
				DispErrorLog(_T("AutoTrader コピーフォルダ作成エラー: %s\n"), GetLastErrorMessage());
				nRv = -1;
				break;
			}
			CStringBuffer strSepUpdateManagerFName = _T("\\") FNAME_UPDATEMANAGEREXE;
			CStringBuffer strUpdateManagerFPath = m_strDir + strSepUpdateManagerFName;
			CStringBuffer strUpdateManagerFPathC = strNewDir + strSepUpdateManagerFName;
			if (! CopyFile(strUpdateManagerFPath, strUpdateManagerFPathC, FALSE)) {
				DispErrorLog(_T("%s %s コピーエラー: %s\n"), strUpdateManagerFPath, strUpdateManagerFPathC, GetLastErrorMessage());
				nRv = -1;
				break;
			}
			if (! CreateProcess(NULL, (LPTSTR)(LPCTSTR)StrQ(strUpdateManagerFPathC), NULL, NULL, FALSE, 0, NULL, strNewDir, &sInfo, &pInfo)) {
				DispErrorLog(_T("AutoTraderUpdateManager コピー実行エラー: %s\n"), GetLastErrorMessage());
				nRv = -1;
				break;
			}
		}
		HINSTANCE hShellExecute;
		if ((int)(hShellExecute = ShellExecute(m_hWnd, _T("open"), strUpdateFName, pszEmpty, m_strDataDir, SW_SHOWNORMAL)) <= 32) {
			DispErrorLog(_T("AutoTrader アップデートインストーラー実行エラー: %s\n"), GetShellExecuteErrorText(hShellExecute));
			nRv = -1;
			break;
		}
		nRv = 2;
		m_bUpdateAutoTraderReq = FALSE;

		break;
	}
	if (nRv < 0) {
		DeleteFile(m_strUpdateTxtFPath);
		DeleteFile(m_strDataDir + _T('\\') + strUpdateFName);
	}
	if (nRv == 2) {
		if (m_pSetupDlg == NULL) {
			m_bQuitReq = TRUE;
		}
	}

	return nRv;
}

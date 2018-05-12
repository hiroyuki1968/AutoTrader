// RemitRegDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "tradehelper.h"
#include "RemitRegDlg.h"

#include "../AutoTraderVer.h"
#include "../AutoTraderDef.h"
#include "../Common.h"
#include "../License.h"
#include "../AutoTraderProc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRemitRegDlg ダイアログ


CRemitRegDlg::CRemitRegDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRemitRegDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRemitRegDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CRemitRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRemitRegDlg)
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_MonthCalCtrl1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRemitRegDlg, CDialog)
	//{{AFX_MSG_MAP(CRemitRegDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemitRegDlg メッセージ ハンドラ

void CRemitRegDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	// メールアドレス取得
	CString strMailAddr;
	m_Edit1.GetWindowText(strMailAddr);
	if (strMailAddr.IsEmpty()) {
		MessageBox(_T("登録メールアドレスを入力してください"), NULL, MB_ICONSTOP);
		return;
	}
	// ライセンス開始日取得
	SYSTEMTIME StDate;
	m_MonthCalCtrl1.GetCurSel(&StDate);
	COleDateTime DtDate(StDate.wYear, StDate.wMonth, StDate.wDay, 0, 0, 0);
	strMailAddr += DtDate.Format("%Y%m%d");
	// ライセンスキー取得
	CString strLicenseKey;
	m_Edit2.GetWindowText(strLicenseKey);
	if (strLicenseKey.IsEmpty()) {
		MessageBox(_T("ライセンスキーを入力してください"), NULL, MB_ICONSTOP);
		return;
	}
	strLicenseKey.MakeUpper();
	// ライセンスキーチェック
	if (! CheckLicenseKey(SECRET_KEY, strMailAddr, strLicenseKey)) {
		MessageBox(_T("登録メールアドレスまたはライセンス開始日またはライセンスキーが正しくありません"), NULL, MB_ICONSTOP);
		return;
	}
	// ライセンス開始日チェック
	COleDateTime DtCur = COleDateTime::GetCurrentTime();
	if (DtCur < DtDate) {
		MessageBox(_T("ライセンスキーの開始日前です。"), NULL, MB_ICONSTOP);
		return;
	}
	if (DtCur >= DtDate + COleDateTimeSpan(30, 0, 0, 0)) {
		MessageBox(_T("ライセンスキーの有効期限が切れています。"), NULL, MB_ICONSTOP);
		return;
	}
	// エンコード
	strMailAddr = EncodeSecretString(strMailAddr);
	strLicenseKey = EncodeSecretString(strLicenseKey);
	// レジストリサブキー作成
	HKEY hKey;
	if (RegCreateKeyAutoTrader(hKey))
		return;
	LONG nRegFunc;
	// 登録メールアドレス設定
	if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_MADDR, NULL, REG_SZ, (BYTE *)(LPCTSTR)strMailAddr, strMailAddr.GetLength())) != ERROR_SUCCESS) {
		MessageBox(_T("レジストリ設定エラー０: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
		RegCloseKey(hKey);
		return;
	}
	// ライセンスキー設定
	if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_LKEY, NULL, REG_SZ, (BYTE *)(LPCTSTR)strLicenseKey, strLicenseKey.GetLength())) != ERROR_SUCCESS) {
		MessageBox(_T("レジストリ設定エラー１: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
		RegCloseKey(hKey);
		return;
	}
	// レジストリクローズ
	if (RegCloseKeyAutoTrader(hKey))
		return;
	// 受付メッセージ
	MessageBox(_T("ご送金ありがとうございます"), NULL, MB_ICONINFORMATION);
	
	CDialog::OnOK();
}

void CRemitRegDlg::OnButton1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	// 現在日
	CTime TCur = CTime::GetCurrentTime();
	if (m_bIDate  &&  m_bIVer  &&  m_dwIVer >= THIS_VER) {
		// 試用期間チェック
		CTimeSpan Ts(7, 0, 0, 0);
		if (TCur > m_TIDate + Ts) {
			MessageBox(_T("試用期間が終了しています。送金登録してください。"), NULL, MB_ICONSTOP);
			return;
		}
		if (TCur < m_TIDate) {
			MessageBox(_T("初回起動日エラー。送金登録してください。"), NULL, MB_ICONSTOP);
			return;
		}
	} else {
		// レジストリサブキー作成
		HKEY hKey;
		if (RegCreateKeyAutoTrader(hKey))
			return;
		LONG nRegFunc;
		// 初回起動日付
		DWORD dwIYear = TCur.GetYear();
		DWORD dwIMon = TCur.GetMonth();
		DWORD dwIDay = TCur.GetDay();
		DWORD dwIVer = THIS_VER;
		// エンコード
		dwIYear = EncodeSecretDWord(dwIYear);
		dwIMon = EncodeSecretDWord(dwIMon);
		dwIDay = EncodeSecretDWord(dwIDay);
		dwIVer = EncodeSecretDWord(dwIVer);
		// 年設定
		if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_IYEAR, NULL, REG_DWORD, (BYTE*)&dwIYear, sizeof(dwIYear))) != ERROR_SUCCESS) {
			MessageBox(_T("レジストリ設定エラー０: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
			RegCloseKey(hKey);
			return;
		}
		// 月設定
		if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_IMON, NULL, REG_DWORD, (BYTE*)&dwIMon, sizeof(dwIMon))) != ERROR_SUCCESS) {
			MessageBox(_T("レジストリ設定エラー１: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
			RegCloseKey(hKey);
			return;
		}
		// 日設定
		if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_IDAY, NULL, REG_DWORD, (BYTE*)&dwIDay, sizeof(dwIDay))) != ERROR_SUCCESS) {
			MessageBox(_T("レジストリ設定エラー２: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
			RegCloseKey(hKey);
			return;
		}
		// バージョン設定
		if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_IVER, NULL, REG_DWORD, (BYTE*)&dwIVer, sizeof(dwIVer))) != ERROR_SUCCESS) {
			MessageBox(_T("レジストリ設定エラー３: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
			RegCloseKey(hKey);
			return;
		}
		// レジストリクローズ
		if (RegCloseKeyAutoTrader(hKey))
			return;
	}
	EndDialog(IDOK);
}

// RandChart.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "RandChart.h"
#include "RandChartDlg.h"

#include <shfolder.h>
#include <htmlhelp.h>

#include "../Common.h"
#include "../AutoTraderVer.h"
#include "../AutoTraderDef.h"
#include "RandChartDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRandChartApp

BEGIN_MESSAGE_MAP(CRandChartApp, CWinApp)
	//{{AFX_MSG_MAP(CRandChartApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRandChartApp クラスの構築

CRandChartApp::CRandChartApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
	m_hExeCheckMutex = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CRandChartApp オブジェクト

CRandChartApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRandChartApp クラスの初期化

BOOL CRandChartApp::InitInstance()
{
	AfxEnableControlContainer();

	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。

#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL 内で MFC を使う場合はここをコールしてください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクする場合はここをコールしてください。
#endif

	AfxGetModuleState()->m_dwVersion = 0x0601;

	if (m_hExeCheckMutex) {
		DWORD flOldProtect;
		VirtualProtect((LPVOID)0x00401000, 1, PAGE_READONLY, &flOldProtect);
	}

	// Exe フォルダ
	m_strDir = GetDPathFromFPath(m_pszHelpFilePath);

	// デフォルトデータフォルダ
	CStringBuffer strAppDataDir = GetLongPath(GetShFolderPath(CSIDL_APPDATA | CSIDL_FLAG_CREATE));
	if (strAppDataDir.IsEmpty()) {
		AfxMessageBox(_T("アプリケーションデータフォルダパス名取得エラー"), MB_ICONSTOP);
		return FALSE;
	}
	if (strAppDataDir.Right(1) == _T("\\"))
		strAppDataDir = strAppDataDir.Left(strAppDataDir.GetLength() - 1);
	CStringBuffer strDefaultDataDir = strAppDataDir + _T("\\") DNAME_AUTOTRADER;

	HKEY hKey;
	_TCHAR lpRegData[MAX_PATH];
	DWORD cbRegDataSize;

	// BaseStatus
	CStringBuffer strDataDir;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, REG_SUBKEY_AUTOTRADER, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
		// データフォルダ
		cbRegDataSize = MAX_PATH;
		if (RegQueryValueEx(hKey, REG_KEY_DATAFOLDER, NULL, NULL, (LPBYTE)lpRegData, &cbRegDataSize) == ERROR_SUCCESS  &&  cbRegDataSize > 1)
			strDataDir = lpRegData;
		RegCloseKey(hKey);
	}
	if (strDataDir.IsEmpty())
		strDataDir = strDefaultDataDir;

	// ウィンドウ名
#if THIS_VER % 100
	CStringBuffer strVer = StrFormat(_T(" Ver.%d.%d.%d%s"), THIS_VER / 10000, THIS_VER % 10000 / 100, THIS_VER % 100, THIS_VER % 100 < 51 ? _T("α") : _T("β"));
#else
	CStringBuffer strVer = StrFormat(_T(" Ver.%d.%d"), THIS_VER / 10000, THIS_VER % 10000 / 100);
#endif
	CStringBuffer strRandChartWndName = RANDCHART_EXENAME + strVer;

	CRandChartDlg dlg;
	dlg.m_nThisVer = THIS_VER;
	dlg.m_strDir = m_strDir;
	dlg.m_strDataDir = strDataDir;
	dlg.m_strRandChartWndName = strRandChartWndName;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//       記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <ｷｬﾝｾﾙ> で消された時のコードを
		//       記述してください。
	}

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

void CRandChartApp::WinHelp(DWORD dwData, UINT nCmd) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	//ここでOS等のチェックを行うとよい
	//OSVERSIONINFO os_info;
	//os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	//GetVersionEx(&os_info);

	//これは作成したHtmlHelpにより異なる
	//dwDataを変換するコードも必要
	_TCHAR* szFileName = FNAME_HELP_HTM;

	CString strHelpPath = m_pszHelpFilePath;
	strHelpPath = strHelpPath.Left(strHelpPath.ReverseFind(_T('\\')) + 1) + FNAME_HELP_CHM;

	HtmlHelp(NULL, strHelpPath, HH_DISPLAY_TOPIC, (DWORD)szFileName);
	
// 基本クラスのメンバ関数は呼ばない
//	CWinApp::WinHelp(dwData, nCmd);
}

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CRandChartDlg* pRandChartDlg = (CRandChartDlg *)theApp.m_pMainWnd;

	LPMSG lpMsg = (LPMSG) lParam;

	if ( nCode >= 0 && PM_REMOVE == wParam )
	{
		if (
			lpMsg->message == WM_KEYDOWN
		)
		{
			BOOL bNull = FALSE;

			switch (lpMsg->wParam) {
			case VK_SPACE:
				pRandChartDlg->SetParam();
				pRandChartDlg->Disp();
				bNull = TRUE;
				break;
			case VK_INSERT:
				pRandChartDlg->m_nMode = 0;
				pRandChartDlg->Disp();
				bNull = TRUE;
				break;
			case VK_DELETE:
				pRandChartDlg->m_nMode = 1;
				pRandChartDlg->Disp();
				bNull = TRUE;
				break;
			case VK_LEFT:
				if (pRandChartDlg->m_nIndex)
					pRandChartDlg->m_nIndex --;
				pRandChartDlg->Disp();
				bNull = TRUE;
				break;
			case VK_UP:
				pRandChartDlg->m_nIndex = pRandChartDlg->m_Pa.GetUpperBound();
				pRandChartDlg->Disp();
				bNull = TRUE;
				break;
			case VK_RIGHT:
				if (pRandChartDlg->m_nIndex < pRandChartDlg->m_Pa.GetUpperBound())
					pRandChartDlg->m_nIndex ++;
				pRandChartDlg->Disp();
				bNull = TRUE;
				break;
			case VK_DOWN:
				pRandChartDlg->m_nIndex = 0;
				pRandChartDlg->Disp();
				bNull = TRUE;
			}

			if (bNull) {
				lpMsg->message = WM_NULL;
				lpMsg->lParam  = 0;
				lpMsg->wParam  = 0;
			}
		}
	}

	return CallNextHookEx(pRandChartDlg->m_hHook, nCode, wParam, lParam);
}

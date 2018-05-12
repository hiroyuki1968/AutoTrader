// AutoTraderUpdateManagerWnd.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "AutoTraderUpdateManager.h"
#include "AutoTraderUpdateManagerWnd.h"

#include "../AutoTraderVer.h"
#include "../AutoTraderDef.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderUpdateManagerWnd

CAutoTraderUpdateManagerWnd::CAutoTraderUpdateManagerWnd()
{
}

CAutoTraderUpdateManagerWnd::~CAutoTraderUpdateManagerWnd()
{
}


BEGIN_MESSAGE_MAP(CAutoTraderUpdateManagerWnd, CWnd)
	//{{AFX_MSG_MAP(CAutoTraderUpdateManagerWnd)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USERNAME, OnUserName)
	ON_MESSAGE(WM_PRODUCTCODE, OnProductCode)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAutoTraderUpdateManagerWnd メッセージ ハンドラ

void CAutoTraderUpdateManagerWnd::OnTimer(UINT nIDEvent) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	KillTimer(nIDEvent);
	DestroyWindow();
	
	CWnd::OnTimer(nIDEvent);
}

LRESULT CAutoTraderUpdateManagerWnd::OnUserName(WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 0;

	if (wParam) {
		lResult = THIS_VER;
		m_strUserName += (TCHAR)wParam;
	} else {
		do {
			TCHAR lpUserName[UNLEN + 1];
			DWORD dwUserNameSize = UNLEN + 1;
			if (! GetUserName(lpUserName, &dwUserNameSize)) {
				MessageBox(_T("ユーザー名取得エラー: ") + GetLastErrorMessage(), NULL, MB_ICONSTOP);
				break;
			}

			if (m_strUserName.CompareNoCase(lpUserName)) {
				lResult = 1;

				CString strInstallDir;
				HKEY hKey;
				_TCHAR lpRegData[MAX_PATH];
				DWORD cbRegDataSize;
				if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_SUBKEY_UNINSTALL _T("\\") + m_strProductCode, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
					// インストールフォルダ
					cbRegDataSize = MAX_PATH;
					if (RegQueryValueEx(hKey, REG_KEY_INSTALLLOCATION, NULL, NULL, (LPBYTE)lpRegData, &cbRegDataSize) == ERROR_SUCCESS  &&  cbRegDataSize > 1)
						strInstallDir = lpRegData;
					RegCloseKey(hKey);
				}

				CString strExeFPath = strInstallDir + FNAME_MAINEXE;

				STARTUPINFO sInfo;
				PROCESS_INFORMATION pInfo;

				ZeroMemory(&sInfo, sizeof(sInfo));
				sInfo.cb = sizeof(sInfo);

				if (! CreateProcess(NULL, (LPTSTR)(LPCTSTR)StrQ(strExeFPath), NULL, NULL, FALSE, 0, NULL, strInstallDir, &sInfo, &pInfo)) {
					MessageBox(_T("AutoTrader 実行エラー: ") + GetLastErrorMessage(), NULL, MB_ICONSTOP);
					break;
				}
			}
		} while (0);
		SetTimer(1, 0, NULL);
	}

	return lResult;
}

LRESULT CAutoTraderUpdateManagerWnd::OnProductCode(WPARAM wParam, LPARAM lParam)
{
	m_strProductCode += (TCHAR)wParam;
	return 0;
}

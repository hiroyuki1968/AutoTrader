// AutoTraderUpdateManager.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "AutoTraderUpdateManager.h"
//#include "AutoTraderUpdateManagerDlg.h"

#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderUpdateManagerApp

BEGIN_MESSAGE_MAP(CAutoTraderUpdateManagerApp, CWinApp)
	//{{AFX_MSG_MAP(CAutoTraderUpdateManagerApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderUpdateManagerApp クラスの構築

CAutoTraderUpdateManagerApp::CAutoTraderUpdateManagerApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CAutoTraderUpdateManagerApp オブジェクト

CAutoTraderUpdateManagerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderUpdateManagerApp クラスの初期化

BOOL CAutoTraderUpdateManagerApp::InitInstance()
{
	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。

/*
	CAutoTraderUpdateManagerDlg dlg;
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
*/
	m_pMainWnd = &m_AutoTraderUpdateManagerWnd;
	CString strDefaultWndClassName(AfxRegisterWndClass(NULL));
	if (! m_AutoTraderUpdateManagerWnd.CreateEx(WS_EX_TOOLWINDOW, strDefaultWndClassName, _T("AutoTraderUpdateManager"), NULL, 0, 0, 1, 1, GetDesktopWindow(), NULL)) {
		AfxMessageBox(_T("ウィンドウ作成エラー: ") + GetLastErrorMessage(), MB_ICONSTOP);
		return FALSE;
	}

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
//	return FALSE;
	return TRUE;
}

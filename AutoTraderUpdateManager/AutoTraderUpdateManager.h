// AutoTraderUpdateManager.h : AUTOTRADERUPDATEMANAGER アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_AUTOTRADERUPDATEMANAGER_H__57F3CE8F_15EB_4A16_B0C5_9753057C1656__INCLUDED_)
#define AFX_AUTOTRADERUPDATEMANAGER_H__57F3CE8F_15EB_4A16_B0C5_9753057C1656__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

#include "AutoTraderUpdateManagerWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderUpdateManagerApp:
// このクラスの動作の定義に関しては AutoTraderUpdateManager.cpp ファイルを参照してください。
//

class CAutoTraderUpdateManagerApp : public CWinApp
{
public:
	CAutoTraderUpdateManagerApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAutoTraderUpdateManagerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
	CAutoTraderUpdateManagerWnd m_AutoTraderUpdateManagerWnd;

	//{{AFX_MSG(CAutoTraderUpdateManagerApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_AUTOTRADERUPDATEMANAGER_H__57F3CE8F_15EB_4A16_B0C5_9753057C1656__INCLUDED_)

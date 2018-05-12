// TradeHelper.h : TRADEHELPER アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_TRADEHELPER_H__A39D3FCA_33B0_4E79_BB44_4441A49BDB7D__INCLUDED_)
#define AFX_TRADEHELPER_H__A39D3FCA_33B0_4E79_BB44_4441A49BDB7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

#include "../StringBuffer.h"

/////////////////////////////////////////////////////////////////////////////
// CTradeHelperApp:
// このクラスの動作の定義に関しては TradeHelper.cpp ファイルを参照してください。
//

class CTradeHelperApp : public CWinApp
{
public:
	CTradeHelperApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CTradeHelperApp)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	CStringBuffer m_strDir;
	HANDLE m_hExeCheckMutex;

	//{{AFX_MSG(CTradeHelperApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_TRADEHELPER_H__A39D3FCA_33B0_4E79_BB44_4441A49BDB7D__INCLUDED_)

// AutoTrader.h : AUTOTRADER アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_AUTOTRADER_H__C9B5B68B_7F9C_49D8_8D1F_E81125B4F0B0__INCLUDED_)
#define AFX_AUTOTRADER_H__C9B5B68B_7F9C_49D8_8D1F_E81125B4F0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

#include "StringBuffer.h"

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderApp:
// このクラスの動作の定義に関しては AutoTrader.cpp ファイルを参照してください。
//

class CAutoTraderApp : public CWinApp
{
public:
	CAutoTraderApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAutoTraderApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	int ReadProductCode(CStringBuffer& strProductCode);
	void DelWorkFile(int nMode, const CStringBuffer& strDataDir, BOOL bEqDataDir);
	OSVERSIONINFO m_OSVI;
	CFileStatus m_FileStatus;
	CStringBuffer m_strDir;
	HANDLE m_hExeCheckMutex;

	//{{AFX_MSG(CAutoTraderApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_AUTOTRADER_H__C9B5B68B_7F9C_49D8_8D1F_E81125B4F0B0__INCLUDED_)

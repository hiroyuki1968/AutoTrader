// ChartViewer.h : CHARTVIEWER アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_CHARTVIEWER_H__F1E9AA2B_BEF1_46F5_9F5B_C97681391620__INCLUDED_)
#define AFX_CHARTVIEWER_H__F1E9AA2B_BEF1_46F5_9F5B_C97681391620__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

#include "../StringBuffer.h"

/////////////////////////////////////////////////////////////////////////////
// CChartViewerApp:
// このクラスの動作の定義に関しては ChartViewer.cpp ファイルを参照してください。
//

class CChartViewerApp : public CWinApp
{
public:
	CChartViewerApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CChartViewerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	CStringBuffer m_strDir;
	HANDLE m_hExeCheckMutex;

	//{{AFX_MSG(CChartViewerApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CHARTVIEWER_H__F1E9AA2B_BEF1_46F5_9F5B_C97681391620__INCLUDED_)

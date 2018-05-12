#if !defined(AFX_AUTOTRADERUPDATEMANAGERWND_H__8FC9D8F3_B5ED_4691_9285_5A159CCD2A98__INCLUDED_)
#define AFX_AUTOTRADERUPDATEMANAGERWND_H__8FC9D8F3_B5ED_4691_9285_5A159CCD2A98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AutoTraderUpdateManagerWnd.h : ヘッダー ファイル
//

#include <Lmcons.h>

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderUpdateManagerWnd ウィンドウ

class CAutoTraderUpdateManagerWnd : public CWnd
{
// コンストラクション
public:
	CAutoTraderUpdateManagerWnd();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CAutoTraderUpdateManagerWnd)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CAutoTraderUpdateManagerWnd();
protected:
	CString m_strUserName;
	CString m_strProductCode;

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CAutoTraderUpdateManagerWnd)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnUserName(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnProductCode(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_AUTOTRADERUPDATEMANAGERWND_H__8FC9D8F3_B5ED_4691_9285_5A159CCD2A98__INCLUDED_)

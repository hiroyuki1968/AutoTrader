#if !defined(AFX_DLHTMLTHREAD_H__DF5B7972_5E54_46E8_86D4_368B41B105D7__INCLUDED_)
#define AFX_DLHTMLTHREAD_H__DF5B7972_5E54_46E8_86D4_368B41B105D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlHtmlThread.h : ヘッダー ファイル
//

#include <afxinet.h>
#include "StringBuffer.h"



/////////////////////////////////////////////////////////////////////////////
// CDlHtmlThread スレッド

class CDlHtmlThread : public CWinThread
{
	DECLARE_DYNCREATE(CDlHtmlThread)
public:
	CDlHtmlThread();           // 動的生成に使用されるプロテクト コンストラクタ
protected:
//	CDlHtmlThread();           // 動的生成に使用されるプロテクト コンストラクタ

// アトリビュート
public:
	CString m_strDataDir;
	CInternetSession* m_pSession;
	CString m_strServerName;
	CString m_strObject;
	INTERNET_PORT m_nPort;
	int m_nVerb;
	DWORD m_dwFlags;
	LPCTSTR m_lpszHeaders;
	LPCTSTR m_lpszOptional;
	CStringBuffer m_sbHtml;

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlHtmlThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CDlHtmlThread();
protected:
//	virtual ~CDlHtmlThread();
	void DispErrorLog(LPCTSTR lpszFormat, ...);

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlHtmlThread)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLHTMLTHREAD_H__DF5B7972_5E54_46E8_86D4_368B41B105D7__INCLUDED_)

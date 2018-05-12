#if !defined(AFX_DLFILETHREAD_H__AD0365E0_8621_43AB_B071_5DB21589331E__INCLUDED_)
#define AFX_DLFILETHREAD_H__AD0365E0_8621_43AB_B071_5DB21589331E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlFileThread.h : ヘッダー ファイル
//

#include <afxinet.h>
#include "StringBuffer.h"



/////////////////////////////////////////////////////////////////////////////
// CDlFileThread スレッド

class CDlFileThread : public CWinThread
{
	DECLARE_DYNCREATE(CDlFileThread)
public:
	CDlFileThread();           // 動的生成に使用されるプロテクト コンストラクタ
protected:
//	CDlFileThread();           // 動的生成に使用されるプロテクト コンストラクタ

// アトリビュート
public:
	CString m_strDataDir;
	CString m_strServerName;
	CString m_strObject;
	INTERNET_PORT m_nPort;
	int m_nVerb;
	DWORD m_dwFlags;
	LPCTSTR m_lpszHeaders;
	LPCTSTR m_lpszOptional;
	CString m_strFPath;
	CString m_strFPathC0;
	CString m_strFPathC1;

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlFileThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CDlFileThread();
protected:
//	virtual ~CDlFileThread();
	void DispErrorLog(LPCTSTR lpszFormat, ...);

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlFileThread)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLFILETHREAD_H__AD0365E0_8621_43AB_B071_5DB21589331E__INCLUDED_)

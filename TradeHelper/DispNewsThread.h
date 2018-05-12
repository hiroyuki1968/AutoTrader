#if !defined(AFX_DISPNEWSTHREAD_H__E64CCE72_5C62_4DE1_83C5_9EFC22F4F1C7__INCLUDED_)
#define AFX_DISPNEWSTHREAD_H__E64CCE72_5C62_4DE1_83C5_9EFC22F4F1C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DispNewsThread.h : ヘッダー ファイル
//

#include <afxinet.h>
#include "../StringBuffer.h"



/////////////////////////////////////////////////////////////////////////////
// CDispNewsThread スレッド

class CDispNewsThread : public CWinThread
{
	DECLARE_DYNCREATE(CDispNewsThread)
public:
	CDispNewsThread();           // 動的生成に使用されるプロテクト コンストラクタ
protected:
//	CDispNewsThread();           // 動的生成に使用されるプロテクト コンストラクタ

// アトリビュート
public:
	int m_nMode;
	CString m_strDataDir;
	COleDateTime m_DtPreDate;
	CString m_strCurNewsNo;
	CStringArray m_SaDateTime;
	CStringArray m_SaCode;
	CStringArray m_SaTitle;
	CStringArray m_SaNewsNo;
	CStringArray m_SaNewsUrl;

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDispNewsThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CDispNewsThread();
protected:
//	virtual ~CDispNewsThread();
	int DlHtml(int nVerb, DWORD dwFlags = INTERNET_FLAG_EXISTING_CONNECT, LPCTSTR lpszHeaders = NULL, LPCTSTR lpszOptional = NULL);
	void DispErrorLog(LPCTSTR lpszFormat, ...);
	CHttpConnection* m_pServer;
	CHttpFile* m_pFile;
	DWORD m_dwServiceType;
	CString m_strServerName;
	CString m_strObject;
	CString m_strObjectC;
	INTERNET_PORT m_nPort;
	CStringBuffer m_sbHtml;
	CStringBuffer m_sbOptional;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDispNewsThread)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DISPNEWSTHREAD_H__E64CCE72_5C62_4DE1_83C5_9EFC22F4F1C7__INCLUDED_)

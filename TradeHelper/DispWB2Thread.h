#if !defined(AFX_DISPWB2THREAD_H__0DB963DA_4E57_4597_BDA5_DAD930C0BA01__INCLUDED_)
#define AFX_DISPWB2THREAD_H__0DB963DA_4E57_4597_BDA5_DAD930C0BA01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DispWB2Thread.h : ヘッダー ファイル
//



#include "webbrowser2.h"

#include <afxinet.h>
#include "../StringBuffer.h"

/////////////////////////////////////////////////////////////////////////////
// CDispWB2Thread スレッド

class CDispWB2Thread : public CWinThread
{
	DECLARE_DYNCREATE(CDispWB2Thread)
//protected:
public:
	CDispWB2Thread();           // 動的生成に使用されるプロテクト コンストラクタ

// アトリビュート
public:

// オペレーション
public:
	int m_nMode;
	CString m_strDataDir;
	CString m_strPreUrl;
	CString m_strUrl;
	CString m_strFPath;

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDispWB2Thread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
//protected:
public:
	virtual ~CDispWB2Thread();
protected:
	int DlFile(const CString& strFPath, int nVerb, DWORD dwFlags = INTERNET_FLAG_EXISTING_CONNECT, LPCTSTR lpszHeaders = NULL, LPCTSTR lpszOptional = NULL);
	void DispErrorLog(LPCTSTR lpszFormat, ...);
	CHttpConnection* m_pServer;
	CHttpFile* m_pFile;
	DWORD m_dwServiceType;
	CString m_strServerName;
	CString m_strObject;
	CString m_strObjectC;
	INTERNET_PORT m_nPort;
	CStringBuffer m_sbOptional;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDispWB2Thread)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DISPWB2THREAD_H__0DB963DA_4E57_4597_BDA5_DAD930C0BA01__INCLUDED_)

#if !defined(AFX_DISPRANKINGTHREAD_H__D58AF973_BD6B_448B_94CE_E00254DC0A4C__INCLUDED_)
#define AFX_DISPRANKINGTHREAD_H__D58AF973_BD6B_448B_94CE_E00254DC0A4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DispRankingThread.h : ヘッダー ファイル
//

#include <afxinet.h>
#include "../StringBuffer.h"
#include "../AutoTraderProc.h"
#include "TradeHelperProc.h"



/////////////////////////////////////////////////////////////////////////////
// CDispRankingThread スレッド

class CDispRankingThread : public CWinThread
{
	DECLARE_DYNCREATE(CDispRankingThread)
public:
	CDispRankingThread();           // 動的生成に使用されるプロテクト コンストラクタ
protected:
//	CDispRankingThread();           // 動的生成に使用されるプロテクト コンストラクタ

// アトリビュート
public:
	BOOL m_bMentenance2;
	CString m_strDataDir;
	int m_nMode;
	CString m_strDBFPath;
	CInternetSession* m_pSession;
	CStringBuffer m_sbQuickInfoUrl;
	CStringBuffer m_sbCosmoQuoteUrl;
	CStringToInfoMap* m_pMstiCodeInfo;
	CMapStringToPtr* m_pMstpSelCode;
	CStringArray m_SaList;
	CStringArray m_SaCode;
	CDWordArray m_DwaTradeCount1000;
	CDWordArray m_DwaDiffPrice;
	CDWordArray m_DwaLowDiffPrice;

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDispRankingThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CDispRankingThread();
protected:
//	virtual ~CDispRankingThread();
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
	//{{AFX_MSG(CDispRankingThread)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DISPRANKINGTHREAD_H__D58AF973_BD6B_448B_94CE_E00254DC0A4C__INCLUDED_)

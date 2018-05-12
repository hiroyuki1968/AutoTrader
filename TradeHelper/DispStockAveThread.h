#if !defined(AFX_DISPSTOCKAVETHREAD_H__64E7399C_328D_4674_8A4A_2F12E3627465__INCLUDED_)
#define AFX_DISPSTOCKAVETHREAD_H__64E7399C_328D_4674_8A4A_2F12E3627465__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DispStockAveThread.h : ヘッダー ファイル
//

#include <afxinet.h>
#include "../StringBuffer.h"
#include "DispWB2Thread.h"



/////////////////////////////////////////////////////////////////////////////
// CDispStockAveThread スレッド

class CDispStockAveThread : public CWinThread
{
	DECLARE_DYNCREATE(CDispStockAveThread)
public:
	CDispStockAveThread();           // 動的生成に使用されるプロテクト コンストラクタ
protected:
//	CDispStockAveThread();           // 動的生成に使用されるプロテクト コンストラクタ

// アトリビュート
public:
	BOOL m_bMentenance1;
	BOOL m_bMentenance2;
	CString m_strDataDir;
	CInternetSession* m_pSession;
	CStringBuffer m_sbQuickInfoUrl;
	CStringBuffer m_sbCosmoQuoteUrl;
	CString m_strContractMonth0;
//	CString m_strContractMonth1;
	CString m_strContractMonth0S;
	long m_lDiff255;
	double m_dPrice;
	double m_dPrePrice;
	long m_lPrePrice255[60];
	double m_dDiff;
	CString m_strTime;
	CString m_strCode;
	CString m_strName;
	short m_sUnit;
	long m_lMaxTradeCount;
	CString m_strCodeEx;
	CString m_strFPath0;
	CString m_strFPath1;
	CString m_strFPath2;
	CStringBuffer m_sbKehaiHtml;
//	COleDateTime m_DtCur;
//	BOOL m_bStockAveThread;

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDispStockAveThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CDispStockAveThread();
protected:
//	virtual ~CDispStockAveThread();
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
	//{{AFX_MSG(CDispStockAveThread)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DISPSTOCKAVETHREAD_H__64E7399C_328D_4674_8A4A_2F12E3627465__INCLUDED_)

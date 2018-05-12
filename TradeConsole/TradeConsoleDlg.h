// TradeConsoleDlg.h : ヘッダー ファイル
//
//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES

#if !defined(AFX_TRADECONSOLEDLG_H__154D1869_94F4_4D15_9A64_165B4E2E05BE__INCLUDED_)
#define AFX_TRADECONSOLEDLG_H__154D1869_94F4_4D15_9A64_165B4E2E05BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <COMDEF.H>
#include <atlbase.h>
#include <mshtml.h>
#include <afxinet.h>
#include "../StringBuffer.h"
#include "../AutoTraderDef.h"
#include "TradeConsoleDef.h"
#include "../AutoTraderProc.h"

class CTradeConsoleDlg;

typedef LRESULT (CTradeConsoleDlg::* USERPROC)(WPARAM, LPARAM);

typedef struct {
	WPARAM wParam;
	LPARAM lParam;
	USERPROC lpUserFunc;
} WMParam;

/////////////////////////////////////////////////////////////////////////////
// CWMParamArray : WMParam 配列クラス

typedef CArray<WMParam, const WMParam&> CWMParamArray;

/////////////////////////////////////////////////////////////////////////////
// CLongToWMParamMap : long WMParam マップクラス

typedef CMap<UINT, UINT, WMParam, const WMParam&> CMapLongToWMParam;

/////////////////////////////////////////////////////////////////////////////
// CTradeConsoleDlg ダイアログ

class CTradeConsoleDlg : public CDialog
{
// 構築
public:
	CTradeConsoleDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CTradeConsoleDlg)
	enum { IDD = IDD_TRADECONSOLE_DIALOG };
	CTabCtrl	m_TabCtrl1;
	CWebBrowser2	m_WebBrowser21;
	CWebBrowser2	m_WebBrowser22;
	CWebBrowser2	m_WebBrowser23;
	CWebBrowser2	m_WebBrowser24;
	CWebBrowser2	m_WebBrowser25;
	CWebBrowser2	m_WebBrowser26;
	CWebBrowser2	m_WebBrowser27;
	CWebBrowser2	m_WebBrowser28;
	CWebBrowser2	m_WebBrowser29;
	CWebBrowser2	m_WebBrowser210;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CTradeConsoleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	BOOL SetWMUserParam(UINT nIDEvent, WPARAM wParam = 0, LPARAM lParam = 0, USERPROC lpUserFunc = OnUser);
	void SetWMUserTimer(UINT nElapse, WPARAM wParam = 0, LPARAM lParam = 0, USERPROC lpUserFunc = OnUser);
	void SelchangeTab1();
	HHOOK m_hHook;
	CString m_strTradeHelperWndName;
	CString m_strTradeConsoleWndName;
	BOOL m_bMentenance0;
	BOOL m_bMentenance1;
	BOOL m_bMentenance2;
protected:
	HICON m_hIcon;
	BOOL PreUser(WPARAM wParam = 0, LPARAM lParam = 0, USERPROC lpUserFunc = OnUser);
	void DispErrorLog(LPCTSTR lpszFormat, ...);
	int CheckLicense();
	void UpdateStreamer();
	void WaitWebBrowser2Ready(CWebBrowser2& WebBrowser2);
	CComQIPtr<IHTMLDocument2> GetWebBrowser2Document(CWebBrowser2& WebBrowser2, LPCTSTR lpszFrameName0, LPCTSTR lpszFrameName1);
	CComQIPtr<IHTMLElement> GetWebBrowser2Element(CWebBrowser2& WebBrowser2, LPCTSTR lpszFrameName0, LPCTSTR lpszFrameName1, LPCTSTR lpszAttributeName, LPCTSTR lpszName, int nIndex);
	void SetWebBrowser2(CWebBrowser2& WebBrowser2, LPCTSTR lpszFrameName0, LPCTSTR lpszFrameName1, LPCTSTR lpszAttributeName0, LPCTSTR lpszName, int nIndex, LPCTSTR lpszAttributeName1, LPCTSTR lpszValue);
	CString GetWebBrowser2(CWebBrowser2& WebBrowser2, LPCTSTR lpszFrameName0, LPCTSTR lpszFrameName1, LPCTSTR lpszAttributeName0, LPCTSTR lpszName, int nIndex, LPCTSTR lpszAttributeName1);
	BOOL ClickWebBrowser2(CWebBrowser2& WebBrowser2, LPCTSTR lpszFrameName0, LPCTSTR lpszFrameName1, LPCTSTR lpszAttributeName, LPCTSTR lpszName, int nIndex);
	void GoBackWebBrowser2(CWebBrowser2& WebBrowser2);
	CString GetBodyHtmlWebBrowser2(CWebBrowser2& WebBrowser2, LPCTSTR lpszFrameName0, LPCTSTR lpszFrameName1);
	void Buy();
	BOOL GetState(int nMode);
	int GetChkItem(long lReceiptNo);
	void DelOdr(long lReceiptNo);
	void ChangeOdr(int nMode, int nStatus);
	CRect m_RectDlg;
	CRect m_RectWB2;
	CMapLongToWMParam m_MltwmpWMUserTimer;
	CWMParamArray m_WmpaUser;
	BOOL m_bUserCall;
	UINT m_nWMUserTimer;
	CString m_strTreasureId;
	CString m_strTreasurePasswd;
	CString m_strMatsuiId;
	CString m_strMatsuiPasswd;
	CString m_strCosmoId;
	CString m_strCosmoPasswd;
	CInternetSession m_pSession[2];
	CInternetSession m_SessionCosmo;
	CHttpConnection* m_pServer;
	CHttpFile* m_pFile;
	DWORD m_dwServiceType;
	CString m_strServerName;
	CString m_strObject;
	CString m_strObjectC;
	INTERNET_PORT m_nPort;
	CStringBuffer m_sbHtml;
	CStringBuffer m_sbCosmoLoginUrl;
	CStringBuffer m_sbOptional;
	INT m_nOnNewWindow2Explorer2;
	BOOL m_bStreamerWide;
	BOOL m_bStreamerSel;
	CDWordArray m_DwaBuyReceiptNo;
	CDWordArray m_DwaBuySuryo;
	CDWordArray m_DwaBuyKakaku;
	CStringArray m_SaGetStateOrderList;
	CStringArray m_SaGetStateSoldList;
	CDWordArray m_DwaGetStateReceiptNo;
	int m_nChkItem;
	CDWordArray m_DwaChangeOdrReceiptNo;
	CDWordArray m_DwaChangeOdrSuryo;
	CDWordArray m_DwaChangeOdrKakaku;
	BOOL m_bWebBrowser21;
	BOOL m_bWebBrowser21MenuClickInterval;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CTradeConsoleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnDocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT FAR* URL);
	afx_msg void OnDocumentCompleteExplorer2(LPDISPATCH pDisp, VARIANT FAR* URL);
	afx_msg void OnDocumentCompleteExplorer3(LPDISPATCH pDisp, VARIANT FAR* URL);
	afx_msg void OnDocumentCompleteExplorer5(LPDISPATCH pDisp, VARIANT FAR* URL);
	afx_msg void OnNavigateComplete2Explorer3(LPDISPATCH pDisp, VARIANT FAR* URL);
	afx_msg void OnNavigateComplete2Explorer6(LPDISPATCH pDisp, VARIANT FAR* URL);
	afx_msg void OnNavigateComplete2Explorer7(LPDISPATCH pDisp, VARIANT FAR* URL);
	afx_msg void OnNewWindow2Explorer2(LPDISPATCH FAR* ppDisp, BOOL FAR* Cancel);
	afx_msg void OnNewWindow2Explorer5(LPDISPATCH FAR* ppDisp, BOOL FAR* Cancel);
	afx_msg void OnNewWindow2Explorer6(LPDISPATCH FAR* ppDisp, BOOL FAR* Cancel);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg LRESULT OnUser(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser1(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser2(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser3(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser4(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser5(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser6(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_TRADECONSOLEDLG_H__154D1869_94F4_4D15_9A64_165B4E2E05BE__INCLUDED_)

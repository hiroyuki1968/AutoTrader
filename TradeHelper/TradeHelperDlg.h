// TradeHelperDlg.h : ヘッダー ファイル
//
//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES

#if !defined(AFX_TRADEHELPERDLG_H__7E288863_0AE2_4039_9D2A_151498FD973C__INCLUDED_)
#define AFX_TRADEHELPERDLG_H__7E288863_0AE2_4039_9D2A_151498FD973C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxinet.h>
#include "../StringBuffer.h"
#include "TradeHelperDef.h"
#include "../AutoTraderProc.h"
#include "TradeHelperProc.h"
#include "DispWB2Thread.h"
#include "DispStockAveThread.h"
#include "DispRankingThread.h"
#include "DispNewsThread.h"

class CTradeHelperDlg;

typedef LRESULT (CTradeHelperDlg::* USERPROC)(WPARAM, LPARAM);

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
// CTradeHelperDlg ダイアログ

class CTradeHelperDlg : public CDialog
{
// 構築
public:
	CTradeHelperDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CTradeHelperDlg)
	enum { IDD = IDD_TRADEHELPER_DIALOG };
	CButton	m_Btn15;
	CButton	m_Check1;
	CButton	m_Check2;
	CButton	m_Check3;
	CButton	m_Check4;
	CButton	m_Check5;
	CButton	m_Check6;
	CButton	m_Check7;
	CButton	m_Check8;
	CButton	m_Check9;
	CEdit	m_Edit1;
	CEdit	m_Edit2;
	CEdit	m_Edit3;
	CEdit	m_Edit4;
	CEdit	m_Edit5;
	CEdit	m_Edit6;
	CEdit	m_Edit7;
	CEdit	m_Edit8;
	CEdit	m_Edit9;
	CEdit	m_Edit10;
	CEdit	m_Edit11;
	CEdit	m_Edit12;
	CEdit	m_Edit13;
	CEdit	m_Edit14;
	CEdit	m_Edit15;
	CEdit	m_Edit16;
	CEdit	m_Edit17;
	CEdit	m_Edit18;
	CEdit	m_Edit19;
	CListBox	m_List1;
	CListBox	m_List2;
	CListBox	m_List3;
	CListBox	m_List4;
	CListBox	m_List5;
	CListBox	m_List6;
	CListBox	m_List7;
	CListBox	m_List8;
	CWebBrowser2	m_WebBrowser21;
	CWebBrowser2	m_WebBrowser22;
	CWebBrowser2	m_WebBrowser23;
	CWebBrowser2	m_WebBrowser24;
	CWebBrowser2	m_WebBrowser25;
	CMonthCalCtrl	m_MonthCalCtrl1;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CTradeHelperDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	BOOL SetWMUserParam(UINT nIDEvent, WPARAM wParam = 0, LPARAM lParam = 0, USERPROC lpUserFunc = OnUser);
	void SetWMUserTimer(UINT nElapse, WPARAM wParam = 0, LPARAM lParam = 0, USERPROC lpUserFunc = OnUser);
	void KillWMUserTimer(WPARAM wParam);
	void ButtonF2();
	void ButtonF3();
	void ButtonF4();
	void ButtonF5();
	void ButtonF6();
	void ButtonF7();
	void ButtonF8();
	void ButtonF9();
	void ButtonF11();
	void ButtonF12();
	HHOOK m_hHook;
	int m_nThisVer;
	CString m_strDir;
	CString m_strDataDir;
	CString m_strMainExeWndName;
	CString m_strChartViewerWndName;
	CString m_strKehaiViewerWndName;
	CString m_strTradeHelperWndName;
	CString m_strTradeConsoleWndName;
	CString m_strUlExeMode;
	int m_nExecMode;
	BOOL m_bMentenance0;
	BOOL m_bMentenance1;
	BOOL m_bMentenance2;
protected:
	HICON m_hIcon;
	BOOL PreUser(WPARAM wParam = 0, LPARAM lParam = 0, USERPROC lpUserFunc = OnUser);
	void AddOdr(int nMode);
	void ChangeOdr(int nIndex, long lNewPrice, long lNewSuryo);
	void ChangeOdrBack(WPARAM wParam, LPARAM lParam);
	void DelOdr();
	void DelOdrBack(WPARAM wParam, LPARAM lParam);
	void SetCodeList();
	void SetNewsList1();
	void SetNewsList2();
	void EntryStk();
	int DlHtml(int nVerb, DWORD dwFlags = INTERNET_FLAG_EXISTING_CONNECT, LPCTSTR lpszHeaders = NULL, LPCTSTR lpszOptional = NULL);
	int GetState(int nMode = 0);
	int GetStateBack(WPARAM wParam, LPARAM lParam);
	void Sell();
	void SellBack(WPARAM wParam, LPARAM lParam);
	void Buy();
	void BuyBack(WPARAM wParam, LPARAM lParam);
	void DispWB2(BOOL bFile, int nMode, CWebBrowser2& WebBrowser2, const CString& strUrl);
	void DispStockAve();
	void DispChart(int nMode = -1);
	void DispRanking(int nMode);
	void DispNews(int nMode = 0);
	void Disp();
	void DispLog(LPCTSTR lpszFormat, ...);
	void DispErrorLog(LPCTSTR lpszFormat, ...);
	void SetCheckedDiffPrice();
	void SaveState();
	void ClickStreamer(int nPX, int nPY);
	CString CopyStreamer(int nPX, int nPY);
	void SelStreamer(int nIndex);
	void DelStreamer(int nIndex);
	void SetStreamer(int nIndex, LPCTSTR lpszCode);
	void ReadInfo();
	int CodeToName(CString& strCode, CString& strName, CString* pstrSijoName = NULL, short* psUnit = NULL, long* plPreEndPrice = NULL, long* plHighPrice = NULL, long* plLowPrice = NULL, long* plTradeCount = NULL, CString* pstrCodeEx = NULL);
	int CheckLicense();
	CFileStatus m_FileStatus;
	CFont m_FontListBox;
	CMapLongToWMParam m_MltwmpWMUserTimer;
	CWMParamArray m_WmpaUser;
	BOOL m_bUserCall;
	UINT m_nWMUserTimer;
	HANDLE m_hStockAveBeepThread;
	CDispWB2Thread* m_pDispWB2Thread2;
	CDispWB2Thread* m_pDispWB2Thread3;
	CDispStockAveThread* m_pDispStockAveThread;
	CDispRankingThread* m_pDispRankingThread0;
	CDispRankingThread* m_pDispRankingThread1;
	CDispRankingThread* m_pDispRankingThread2;
	CDispNewsThread* m_pDispNewsThread0;
	CDispNewsThread* m_pDispNewsThread1;
	CPtrArray m_PaThreadTimeout;
	BOOL m_bChkThreadTimerRun;
	BOOL m_bInitDialog;
	BOOL m_bUser3;
//	BOOL m_bStockAveThread;
	CString m_strTempDir;
//	CString m_strTempCompressDir;
	CString m_strMeigaraIniFPath;
	CString m_strNewsIniFPath;
	CString m_strDBFPath;
	CString m_strRankingFPath;
	CString m_strTempRankingFPath;
	CString m_strRankingAllFPath;
	CString m_strTempRankingAllFPath;
	BOOL m_bShift;
	BOOL m_bCtrl;
	int m_nList2CurSel;
	int m_nList3CurSel;
	int m_nList2PreCurSel;
	BOOL m_bSelchangeList3;
	CString m_strDispWB2Url0;
	CString m_strDispWB2Url1;
	CString m_strTreasureId;
	CString m_strTreasurePasswd;
	CString m_strMatsuiId;
	CString m_strMatsuiPasswd;
	CString m_strCosmoId;
	CString m_strCosmoPasswd;
	CInternetSession* m_ppSession[3];
	CInternetSession m_SessionCosmo;
	CHttpConnection* m_pServer;
	CHttpFile* m_pFile;
	DWORD m_dwServiceType;
	CString m_strServerName;
	CString m_strObject;
	CString m_strObjectC;
	INTERNET_PORT m_nPort;
	CStringBuffer m_sbHtml;
	CStringBuffer m_sbQuickInfoUrl;
	CStringBuffer m_sbKaiOdrHyjiObject;
	CStringBuffer m_sbKaiOdrSijiObject;
	CStringBuffer m_sbBaiObject;
	CStringBuffer m_sbTreasureServerId;
	CStringBuffer m_sbTreasureSsnid;
	CStringBuffer m_sbOptional;
	CStringBuffer m_sbCosmoLoginUrl;
	CStringBuffer m_sbCosmoQuoteUrl;
	CStringArray m_SaCode;
	CStringArray m_SaName;
	CUIntArray m_UiaReceiptNo;
	CUIntArray m_UiaState;
	CDWordArray m_DwaBuyPrice;
	CDWordArray m_DwaSellPrice;
	CDWordArray m_DwaSuryo;
	CDWordArray m_DwaBuySoldSuryo;
	CDWordArray m_DwaSellSuryo;
	CDWordArray m_DwaSellSoldSuryo;
	CUIntArray m_UiaTick;
	CWordArray m_WaUnit;
	CUIntArray m_UiaSemiAuto;
	int m_nDummyReceiptNo;
	CStringToInfoMap m_MstiCodeInfo;
	CMapStringToMainCodeName m_MstmCodeMainCodeName;
	CStringToRankingAttrMap m_MstrCodeRankingAttr;
	CStringToRankingAttrMap m_MstrCodeRankingAttr2;
	int m_nDispStockAveThreadTimeoutCount;
	long m_lZan;
	BOOL m_bDisp;
	CString m_strEntryStk;
	BOOL m_bSetFocusEdit1;
	COleDateTime m_DtDate;
	COleDateTime m_DtPreDate;
	CString m_strContractMonth0;
	CString m_strContractMonth1;
	CString m_strContractMonth0S;
	CStringArray m_SaNewsDateTime;
	CStringArray m_SaNewsCode;
	CStringArray m_SaNewsTitle;
	CStringArray m_SaNewsNo;
	CStringArray m_SaNewsUrl;
	COleDateTime m_DtNewsPreDate;
	CMapStringToPtr m_MstpNewsNo;
	CMapStringToPtr m_MstpNewsCode;
	CStringArray m_SaNewsCode2;
	CStringArray m_SaNewsDateTime2;
	CMapStringToPtr m_MstpNewsCode2;
	int m_nNewsCount;
	CStringArray m_SaNiceCode;
	CMapStringToPtr m_MstpNiceCode;
	CStringArray m_SaSelCode;
	CMapStringToPtr m_MstpSelCode;
	CString m_strKehaiCode;
	CStringBuffer m_sbKehaiHtml;
	BOOL m_bLicenseCanceled;
	CDWordArray m_DwaGetStateWParam;
	CDWordArray m_DwaGetStateLParam;
	CDWordArray m_DwaGetStateReceiptNo;
	CUIntArray m_UiaGetStateStatus;
	CDWordArray m_DwaGetStateSuryo;
	CDWordArray m_DwaGetStatePrice;
	CDWordArray m_DwaGetStateSoldSuryo;
	CDWordArray m_DwaGetStateSoldPrice;
	long m_lChangeOdrWParam;
	long m_lChangeOdrLParam;
	int m_nSetStreamer;
	int m_nSelStreamer;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CTradeHelperDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton10();
	afx_msg void OnButton11();
	afx_msg void OnButton12();
	afx_msg void OnButton13();
	afx_msg void OnButton14();
	afx_msg void OnButton15();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnChangeEdit1();
	afx_msg void OnSetfocusEdit1();
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnSelchangeList2();
	afx_msg void OnSelchangeList3();
	afx_msg void OnSelchangeList4();
	afx_msg void OnSelchangeList5();
	afx_msg void OnSelchangeList6();
	afx_msg void OnSelchangeList7();
	afx_msg void OnSelchangeList8();
	afx_msg void OnDblclkList6();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnRadio8();
	afx_msg void OnRadio9();
	afx_msg void OnRadio10();
	afx_msg void OnRadio11();
	afx_msg void OnRadio12();
	afx_msg void OnRadio13();
	afx_msg void OnRadio14();
	afx_msg void OnRadio15();
	afx_msg void OnRadio16();
	afx_msg void OnRadio17();
	afx_msg void OnRadio18();
	afx_msg void OnRadio19();
	afx_msg void OnRadio20();
	afx_msg void OnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg LRESULT OnUser(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser1(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser2(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser3(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser4(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser5(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser6(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser7(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser8(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser9(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser10(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser11(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser12(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser13(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser14(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser15(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_TRADEHELPERDLG_H__7E288863_0AE2_4039_9D2A_151498FD973C__INCLUDED_)

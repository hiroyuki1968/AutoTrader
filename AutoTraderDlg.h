// AutoTraderDlg.h : ヘッダー ファイル
//

#if !defined(AFX_AUTOTRADERDLG_H__CE91A720_5092_4F24_88AA_6384AAE889E0__INCLUDED_)
#define AFX_AUTOTRADERDLG_H__CE91A720_5092_4F24_88AA_6384AAE889E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxmt.h>
#include <afxinet.h>
#include <afxdao.h>
#include "Common.h"
#include "StringBuffer.h"
#include "AutoTraderProc.h"
#include "SetupDlg.h"

class CAutoTraderDlg;

typedef LRESULT (CAutoTraderDlg::* USERPROC)(WPARAM, LPARAM);

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
// CAutoTraderDlg ダイアログ

class CAutoTraderDlg : public CDialog
{
// 構築
public:
	CAutoTraderDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CAutoTraderDlg)
	enum { IDD = IDD_AUTOTRADER_DIALOG };
	CButton	m_Btn4;
	CButton	m_Btn5;
	CButton	m_Check1;
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
	CEdit	m_Edit18;
	CListBox	m_List1;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAutoTraderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	int UpdateAutoTrader0();
	int UpdateAutoTrader1();
	BOOL SetWMUserParam(UINT nIDEvent, WPARAM wParam = 0, LPARAM lParam = 0, USERPROC lpUserFunc = OnUser);
	void SetWMUserTimer(UINT nElapse, WPARAM wParam = 0, LPARAM lParam = 0, USERPROC lpUserFunc = OnUser);
	void KillWMUserTimer(WPARAM wParam);
	OSVERSIONINFO m_OSVI;
	int m_nThisVer;
	CString m_strDir;
	CString m_strDefaultDataDir;
	CString m_strDataDir;
	BOOL m_bUpdateCheck;
	CString m_strMainExeWndName;
	CString m_strChartViewerWndName;
	CString m_strKehaiViewerWndName;
	CString m_strTradeHelperWndName;
	CString m_strUlCmdLine;
	CString m_strUlExeMode;
	BOOL m_bUpdateAutoTraderReq;
	int m_nExecMode;
	BOOL m_bMentenance0;
	BOOL m_bMentenance1;
	BOOL m_bMentenance2;
	COleDateTime m_DtSimStart;
	int m_nAutoTraderUpdateType;
	COleDateTime m_DtAutoTraderUpdateDate;
	CString m_strAutoExecFPath;
	CString m_strUpdateTxtFName;
	CString m_strUpdateTxtFPath;
protected:
	HICON m_hIcon;
	BOOL PreUser(WPARAM wParam = 0, LPARAM lParam = 0, USERPROC lpUserFunc = OnUser);
	int CreateDB(CDaoDatabase& Database);
	DWORD GetMaxConnectionsPerServer();
	int DlHtml(int nVerb, DWORD dwFlags = INTERNET_FLAG_EXISTING_CONNECT, LPCTSTR lpszHeaders = NULL, LPCTSTR lpszOptional = NULL);
	int DlFile(const CString& strFPath, int nVerb, DWORD dwFlags = INTERNET_FLAG_EXISTING_CONNECT, LPCTSTR lpszHeaders = NULL, LPCTSTR lpszOptional = NULL);
	int DlData0(int nMode);
	int DlData1();
	int DlData2(int nMode);
	int DlData3(int nMode);
	int DlChart();
	long GetStockAve0();
	void AddFunashi0(long* plFunashi, const CFunashi0& Funashi0);
	void AddFunashi1(long* plFunashi, const CFunashi1& Funashi1);
	void AddFunashi2(long* plFunashi, const CFunashi2& Funashi2);
	void AddFunashi0(int nIndex, const CFunashi0& Funashi0);
	void AddFunashi1(int nIndex, const CFunashi1& Funashi1);
	void AddFunashi2(int nIndex, const CFunashi2& Funashi2);
	CFunashi0 GetFunashi(long* plFunashi, int nIndex);
	CFunashi0 GetFunashi(int nIndex0, int nIndex1);
//	int GetHiashiNice(int nHiashiIndex, const long plPrice[], const long plTradeCount[]);
	int GetFunashiNice(int nHiashiIndex, const long plPrice[], const long plPrice255[], const long plTradeCount[], const double pdVwap[], const CKehai0 pKehai[], const CKehai0 pKehai255[], const long plKehaiPrice[], int nCurDateStartIndex, const COleDateTime* pDtCur);
	int HiashiAnalyze(const COleDateTime* pDtCur = NULL, LPCTSTR lpszCode = NULL, int nMode = 0, int nIndex = -1);
	void HiashiDel(int nIndex);
	int FunashiAnalyze(int nMode, const COleDateTime* pDtCur = NULL, const COleDateTime* pDtPrev = NULL, LPCTSTR lpszCode = NULL);
	void Disp();
	void DispLog(LPCTSTR lpszFormat, ...);
	void DispErrorLog(LPCTSTR lpszFormat, ...);
	void InsertNiceBuyHiashiIndex(int nBuyLeftIndex, int nBuyRightIndex, int nIndex, int nNice, int nMask);
	void GetState();
	void BuyJudge();
	void SellJudge();
	void Buy();
	void Sell();
	void SellAll();
	void Start();
	void End();
	void CreatePriceList();
	void CreateNiceList();
	int CodeToName(CString& strCode, CString& strName, CString* pstrSijoName = NULL, short* psUnit = NULL, long* plPreEndPrice = NULL, long* plHighPrice = NULL, long* plLowPrice = NULL, long* plTradeCount = NULL, CString* pstrCodeEx = NULL);
	void ChangeEditCode(int nID0, int nID1);
	void Check10(int nIndex);
	void SetMeigara(int nFromIndex = -1, LPCTSTR lpszToCode = NULL);
	void SaveNiceCode();
	void SaveSelCode();
	void SaveHiashiCode();
	void LoadLastStatus();
	void SaveLastStatus();
	void CompactDB();
	void SetNiceCode(LPCTSTR lpszAddCode = NULL, int nDelIndex = -1);
	void RemoveAllNiceCode();
	void GetSimDateTime();
	void TimeSim();
	int CheckLicense();
	CFileStatus m_FileStatus;
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
	int m_dwMaxConnectionsPerServer;
	CInternetSession* m_ppSession[3];
	CInternetSession** m_ppSessionCosmo;
	CHttpConnection* m_pServer;
	CHttpFile* m_pFile;
	DWORD m_dwServiceType;
	CString m_strServerName;
	CString m_strObject;
	CString m_strObjectC;
	CString m_strObjectT;
	INTERNET_PORT m_nPort;
	CStringBuffer m_sbHtml;
	CStringBuffer m_sbHtmlT;
	DWORD m_dwErr;
	CString m_strFPath;
	CString m_strFPathC0;
	CString m_strFPathC1;
	CStringBuffer m_psbQuickInfoUrl[3];
	CStringBuffer m_sbKaiOdrHyjiObject;
	CStringBuffer m_sbKaiOdrSijiObject;
	CStringBuffer m_sbBaiObject;
	CStringBuffer m_sbOptional;
	CStringBuffer m_sbMatsuiQuoteUrl;
	CStringBuffer m_sbCosmoLoginUrl;
	CStringBuffer m_sbCosmoQuoteUrl;
	CString m_strTempDir;
//	CString m_strTempCompressDir;
	CString m_strMeigaraIniFPath;
	CString m_strOrgMeigaraIniFPath;
	CString m_strLastStatusIniFPath;
	CString m_strDBFPath;
	CString m_strHomeDBFPath;
	CString m_strTempDBFPath;
	CString m_strRstDBFPath;
	CString m_strOrgDBFPath;
	CString m_strLogFPath;
	CString m_strHomeLogFPath;
	COleDateTime m_DtDate;
	COleDateTime m_DtPreDate;
	COleDateTime m_DtPrePreDate;
	COleDateTime m_DtPreDateGet;
	CString m_strContractMonth0;
	CString m_strContractMonth1;
	CString m_strContractMonth0S;
	CStringArray m_SaNiceCode;
	CMapStringToPtr m_MstpNiceCode;
	CDWordArray m_DwaNiceLockOn;
	CUIntArray m_UiaNiceSel;
	CStringArray m_SaSelCode;
	CMapStringToPtr m_MstpSelCode;
	CStringArray m_SaDlCode;
	CUIntArray m_UiaDlHiashiIndex;
	CUIntArray m_UiaDlSel;
	CStringArray m_SaHiashiCode;
	CMapStringToPtr m_MstpHiashiCode;
	CStringArray m_SaHiashiName;
	CStringArray m_SaHiashiType;
	CWordArray m_WaHiashiUnit;
	CUIntArray m_UiaHiashiNice;
	CDWordArray m_DwaHiashiPreEndPrice;
	CDWordArray m_DwaHiashiPreEndTradeCount;
	CDWordArray m_DwaHiashiPriceDiffAve;
	CDWordArray m_DwaHiashiStartPrice;
	CDWordArray m_DwaHiashiStopDiff;
	CDWordArray m_DwaHiashiBuyTotalPrice;
	CDWordArray m_DwaHiashiBuyUnitCount;
	CPtrArray m_PaFunashi;
	CUIntArray m_UiaFunashiPaIndex;
	CDWordArray m_DwaFunashiPrice;
//	CDWordArray m_DwaFunashiPriceRiseRatio;
//	CUIntArray m_UiaFunashiPriceMinutes;
	CUIntArray m_UiaFunashiNice;
	CUIntArray m_UiaNiceBuyHiashiIndex;
	long m_lZan;
	long m_lStartZan;
	long m_lVZan;
	long m_lStartVZan;
	long m_lCashZan;
	CUIntArray m_UiaKabuHiashiIndex;
	CUIntArray m_UiaKabuReceiptNo;
	CUIntArray m_UiaKabuState;
	CUIntArray m_UiaKabuStateMinutes;
	CUIntArray m_UiaKabuTseiKaisu;
	COleDateTimeArray m_DtaKabuFunashiPaDateTime;
	CDWordArray m_DwaKabuBuyPrice0;
	CDWordArray m_DwaKabuBuyPrice1;
	CDWordArray m_DwaKabuSellPrice;
	CDWordArray m_DwaKabuHighPrice;
	CDWordArray m_DwaKabuLowPrice;
	CDWordArray m_DwaKabuUnitCount;
	CDWordArray m_DwaKabuDiff;
	CUIntArray m_UiaKabuUp;
	CUIntArray m_UiaKabuDown;
	CUIntArray m_UiaKabuSell;
	long m_lKabuSellPlusCount;
	long m_lKabuSellPlus;
	long m_lKabuSellZeroCount;
	long m_lKabuSellMinusCount;
	long m_lKabuSellMinus;
	BOOL m_bOnInitDialog;
	BOOL m_bSetTimer2;
	BOOL m_bTrade;
	BOOL m_bDispLog;
	BOOL m_bDispDebugLog;
	BOOL m_bSimStop;
	BOOL m_bLog;
	CString m_strLogCode;
	CMapStringToMainCodeName m_MstmCodeMainCodeName;
	CMapStringToPtr m_MstpNewsCode;
	CMapStringToPtr m_MstpNewsCode2;
	int m_nMemMapF0Count;
	int m_nMemMapF1Count;
	int m_nMemMapF2Count;
	DWORD m_dwMemMapAllPaSize;
	DWORD m_dwMemMapCellSize;
	DWORD m_dwMemMapSize;
	HANDLE m_hMapping;		// メモリマップドファイルのハンドル
	char *m_pMappingView;	// ファイルのビューへのポインタ
	char *m_pMappingViewOffset;
	char *m_pMappingViewCell;
	char *m_pMappingViewNextCell;
	long m_lFunashi0Count;
	long m_lFunashi1Count;
	long m_lFunashi2Count;
	COleDateTime m_DtSim;
	COleDateTime m_DtSim0;
	COleDateTime m_DtSim1;
	BOOL m_bTimeSim;
	CStdioFile m_SfDump;
	BOOL m_bLicenseCanceled;
	CSetupDlg* m_pSetupDlg;
	BOOL m_bQuitReq;
	CMapStringToCFunashi0 m_Mstf0Last;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAutoTraderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnCheck10();
	afx_msg void OnCheck11();
	afx_msg void OnCheck12();
	afx_msg void OnCheck13();
	afx_msg void OnCheck14();
	afx_msg void OnCheck15();
	afx_msg void OnCheck16();
	afx_msg void OnCheck17();
	afx_msg void OnCheck18();
	afx_msg void OnCheck19();
	afx_msg void OnSetfocusEdit16();
	afx_msg void OnSetfocusEdit20();
	afx_msg void OnSetfocusEdit21();
	afx_msg void OnSetfocusEdit22();
	afx_msg void OnSetfocusEdit23();
	afx_msg void OnSetfocusEdit24();
	afx_msg void OnSetfocusEdit25();
	afx_msg void OnSetfocusEdit26();
	afx_msg void OnSetfocusEdit27();
	afx_msg void OnSetfocusEdit28();
	afx_msg void OnSetfocusEdit29();
	afx_msg void OnChangeEdit16();
	afx_msg void OnChangeEdit20();
	afx_msg void OnChangeEdit21();
	afx_msg void OnChangeEdit22();
	afx_msg void OnChangeEdit23();
	afx_msg void OnChangeEdit24();
	afx_msg void OnChangeEdit25();
	afx_msg void OnChangeEdit26();
	afx_msg void OnChangeEdit27();
	afx_msg void OnChangeEdit28();
	afx_msg void OnChangeEdit29();
	//}}AFX_MSG
	afx_msg LRESULT OnUser(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser1(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser2(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser3(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser4(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser5(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_AUTOTRADERDLG_H__CE91A720_5092_4F24_88AA_6384AAE889E0__INCLUDED_)

// KehaiViewerDlg.h : ヘッダー ファイル
//

#if !defined(AFX_KEHAIVIEWERDLG_H__971D8E50_1222_4ECC_84F1_53CCDDD455C3__INCLUDED_)
#define AFX_KEHAIVIEWERDLG_H__971D8E50_1222_4ECC_84F1_53CCDDD455C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../AutoTraderProc.h"

class CKehaiViewerDlg;

typedef LRESULT (CKehaiViewerDlg::* USERPROC)(WPARAM, LPARAM);

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
// CKehaiViewerDlg ダイアログ

class CKehaiViewerDlg : public CDialog
{
// 構築
public:
	CKehaiViewerDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CKehaiViewerDlg)
	enum { IDD = IDD_KEHAIVIEWER_DIALOG };
		// メモ: この位置に ClassWizard によってデータ メンバが追加されます。
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CKehaiViewerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	BOOL SetWMUserParam(UINT nIDEvent, WPARAM wParam = 0, LPARAM lParam = 0, USERPROC lpUserFunc = OnUser);
	void SetWMUserTimer(UINT nElapse, WPARAM wParam = 0, LPARAM lParam = 0, USERPROC lpUserFunc = OnUser);
	void KillWMUserTimer(WPARAM wParam);
	void DispKehai();
	void EraseDisp();
	HHOOK m_hHook;
	int m_nThisVer;
	CString m_strDir;
	CString m_strDataDir;
	CString m_strMainExeWndName;
	CString m_strChartViewerWndName;
	CString m_strKehaiViewerWndName;
	CString m_strTradeHelperWndName;
	CString m_strUlExeMode;
	int m_nExecMode;
	int m_nPage;
	CStringArray m_SaSelCode;
protected:
	HICON m_hIcon;
	BOOL PreUser(WPARAM wParam = 0, LPARAM lParam = 0, USERPROC lpUserFunc = OnUser);
	int DlData0();
	int HiashiAnalyze(LPCTSTR lpszCode = NULL);
	CFunashi0 GetFunashi(long* plFunashi, int nIndex);
	CFunashi0 GetFunashi(int nIndex0, int nIndex1);
	void DispErrorLog(LPCTSTR lpszFormat, ...);
	int CodeToName(CString& strCode, CString& strName, CString* pstrSijoName = NULL, short* psUnit = NULL, long* plPreEndPrice = NULL, long* plHighPrice = NULL, long* plLowPrice = NULL, long* plTradeCount = NULL, CString* pstrCodeEx = NULL);
	void User1();
	void User2();
	void User4(WPARAM wParam);
	void User5(WPARAM wParam);
	void User6(WPARAM wParam);
	void User7();
	void User8();
	int CheckLicense();
	CMapLongToWMParam m_MltwmpWMUserTimer;
	CWMParamArray m_WmpaUser;
	BOOL m_bUserCall;
	UINT m_nWMUserTimer;
	CString m_strTempDir;
//	CString m_strTempCompressDir;
	CString m_strMeigaraIniFPath;
	CString m_strNewsIniFPath;
	CString m_strDBFPath;
	COleDateTime m_DtDate;
	COleDateTime m_DtPreDate;
	CStringArray m_SaNiceCode;
	CMapStringToPtr m_MstpSelCode;
	CStringArray m_SaHiashiCode;
	CMapStringToPtr m_MstpHiashiCode;
	CStringArray m_SaHiashiName;
	CStringArray m_SaHiashiType;
	CWordArray m_WaHiashiUnit;
	CDWordArray m_DwaHiashiPreEndPrice;
	CDWordArray m_DwaHiashiPreEndTradeCount;
	CDWordArray m_DwaHiashiStartPrice;
	CDWordArray m_DwaHiashiPriceAve25;
	CPtrArray m_PaFunashi;
	long m_plPrice[11];
	long m_plTradeCount[11];
	int m_pnPriceDirec[11];
	long m_pplKehaiPrice[11][10];
	long m_pplKehaiCount[11][10];
	COLORREF m_pcrPriceTextColor[11];
	COLORREF m_pcrPriceDirecTextColor[11];
	COLORREF m_ppcrKehaiPriceBkColor[11][10];
	COLORREF m_ppcrKehaiCountBkColor[11][10];
	CString m_strReqStk;
	CRect m_rc;
	int m_x0;
	int m_y0;
	int m_x1;
	int m_y1;
	int m_w;
	int m_h;
	CFont m_Font;
	CDC m_MemoryDC;
	CBitmap m_Bitmap;
	CBitmap* m_pOldBitmap;
	CFont* m_pOldFont;
	TEXTMETRIC m_Metrics;
	CSize m_Size;
	CMapStringToMainCodeName m_MstmCodeMainCodeName;
	CMapStringToPtr m_MstpNewsCode;
	CMapStringToPtr m_MstpNewsCode2;
	HANDLE m_hMapping;		// メモリマップドファイルのハンドル
	char *m_pMappingView;	// ファイルのビューへのポインタ
	char *m_pMappingViewOffset;
	char *m_pMappingViewCell;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CKehaiViewerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	afx_msg LRESULT OnUser(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser1(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser2(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser4(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser5(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser6(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser7(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser8(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_KEHAIVIEWERDLG_H__971D8E50_1222_4ECC_84F1_53CCDDD455C3__INCLUDED_)

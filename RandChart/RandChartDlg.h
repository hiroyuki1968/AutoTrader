// RandChartDlg.h : ヘッダー ファイル
//
//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES

#if !defined(AFX_RANDCHARTDLG_H__3CAFFC94_4976_4AAE_8A19_B850518272CB__INCLUDED_)
#define AFX_RANDCHARTDLG_H__3CAFFC94_4976_4AAE_8A19_B850518272CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../AutoTraderProc.h"
#include "RandChartProc.h"

/////////////////////////////////////////////////////////////////////////////
// CRandChartDlg ダイアログ

class CRandChartDlg : public CDialog
{
// 構築
public:
	CRandChartDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CRandChartDlg)
	enum { IDD = IDD_RANDCHART_DIALOG };
	CButton	m_Check1;
	CWebBrowser2	m_WebBrowser21;
	CStatic	m_Text1;
	CStatic	m_Text2;
	CStatic	m_Text3;
	CStatic	m_Text4;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CRandChartDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	void SetParam();
	void Disp();
	HHOOK m_hHook;
	int m_nThisVer;
	CString m_strDir;
	CString m_strDataDir;
	CString m_strRandChartWndName;
	int m_nMode;
	int m_nIndex;
	CParmArray m_Pa;
protected:
	int HiashiAnalyze();
	int CodeToName(CString& strCode, CString& strName, CString* pstrSijoName = NULL, short* psUnit = NULL, long* plPreEndPrice = NULL, long* plHighPrice = NULL, long* plLowPrice = NULL, long* plTradeCount = NULL, CString* pstrCodeEx = NULL);
	int CheckLicense();
	HICON m_hIcon;
	CFileStatus m_FileStatus;
	CString m_strTempDir;
//	CString m_strTempCompressDir;
	CString m_strMeigaraIniFPath;
	CString m_strDBFPath;
	CStringArray m_SaSelCode;
	CStringArray m_SaHiashiCode;
	CMapStringToMainCodeName m_MstmCodeMainCodeName;
	CMapStringToPtr m_MstpNewsCode;
	CMapStringToPtr m_MstpNewsCode2;
	CString m_strDstFPath;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CRandChartDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_RANDCHARTDLG_H__3CAFFC94_4976_4AAE_8A19_B850518272CB__INCLUDED_)

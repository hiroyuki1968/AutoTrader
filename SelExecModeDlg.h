#if !defined(AFX_SELEXECMODEDLG_H__B90FFCCB_C771_408B_90E0_BE8253F4853F__INCLUDED_)
#define AFX_SELEXECMODEDLG_H__B90FFCCB_C771_408B_90E0_BE8253F4853F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelExecModeDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSelExecModeDlg ダイアログ

class CSelExecModeDlg : public CDialog
{
// コンストラクション
public:
	CSelExecModeDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSelExecModeDlg)
	enum { IDD = IDD_SELEXECMODE_DIALOG };
	CButton	m_Check1;
	CButton	m_Check2;
	CButton	m_Check3;
	CDateTimeCtrl	m_DateTimeCtrl1;
	CButton	m_Group2;
	CButton	m_Group3;
	CMonthCalCtrl	m_MonthCalCtrl1;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSelExecModeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	int m_nExecMode;
	BOOL m_bMentenance0;
	BOOL m_bMentenance1;
	BOOL m_bMentenance2;
	COleDateTime m_DtSimStart;
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSelExecModeDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SELEXECMODEDLG_H__B90FFCCB_C771_408B_90E0_BE8253F4853F__INCLUDED_)

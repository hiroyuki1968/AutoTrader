#if !defined(AFX_SETUPDLG_H__3B354A08_2A8B_4F17_B472_53EB9EF77FE6__INCLUDED_)
#define AFX_SETUPDLG_H__3B354A08_2A8B_4F17_B472_53EB9EF77FE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupDlg.h : ヘッダー ファイル
//

class CAutoTraderDlg;

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg ダイアログ

class CSetupDlg : public CDialog
{
// コンストラクション
public:
	CSetupDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSetupDlg)
	enum { IDD = IDD_SETUP_DIALOG };
	CEdit	m_Edit1;
	CEdit	m_Edit2;
	CEdit	m_Edit3;
	CEdit	m_Edit4;
	CEdit	m_Edit5;
	CEdit	m_Edit6;
	CEdit	m_Edit7;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	CAutoTraderDlg* m_pAutoTraderDlg;
	CString m_strTreasureId;
	CString m_strTreasurePasswd;
	CString m_strMatsuiId;
	CString m_strMatsuiPasswd;
	CString m_strCosmoId;
	CString m_strCosmoPasswd;
	CString m_strDir;
	CString m_strDefaultDataDir;
	int m_nAutoTraderUpdateType;
	BOOL m_bAutoTraderUpdated;
	CString m_strDataDir;
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSetupDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SETUPDLG_H__3B354A08_2A8B_4F17_B472_53EB9EF77FE6__INCLUDED_)

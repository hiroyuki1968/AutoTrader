#if !defined(AFX_REMITREGDLG_H__4596789B_1B60_4F41_8E42_F055F84A99FB__INCLUDED_)
#define AFX_REMITREGDLG_H__4596789B_1B60_4F41_8E42_F055F84A99FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RemitRegDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CRemitRegDlg ダイアログ

class CRemitRegDlg : public CDialog
{
// コンストラクション
public:
	CRemitRegDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CRemitRegDlg)
	enum { IDD = IDD_REMITREG_DIALOG };
	CEdit	m_Edit1;
	CEdit	m_Edit2;
	CMonthCalCtrl	m_MonthCalCtrl1;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CRemitRegDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	BOOL m_bIDate;
	CTime m_TIDate;
	BOOL m_bIVer;
	DWORD m_dwIVer;
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CRemitRegDlg)
	virtual void OnOK();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_REMITREGDLG_H__4596789B_1B60_4F41_8E42_F055F84A99FB__INCLUDED_)

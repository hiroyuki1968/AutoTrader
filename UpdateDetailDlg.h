#if !defined(AFX_UPDATEDETAILDLG_H__78CAD6E5_365F_4BBB_AFA2_9E59C2FFB23B__INCLUDED_)
#define AFX_UPDATEDETAILDLG_H__78CAD6E5_365F_4BBB_AFA2_9E59C2FFB23B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdateDetailDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CUpdateDetailDlg ダイアログ

class CUpdateDetailDlg : public CDialog
{
// コンストラクション
public:
	CUpdateDetailDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CUpdateDetailDlg)
	enum { IDD = IDD_UPDATEDETAIL_DIALOG };
	CButton	m_Cancel;
	CEdit	m_Edit1;
	CStatic	m_Text1;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CUpdateDetailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	UINT m_uType;
	LPCTSTR m_lpszDocument;
	LPCTSTR m_lpszUpdateDetail;
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CUpdateDetailDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_UPDATEDETAILDLG_H__78CAD6E5_365F_4BBB_AFA2_9E59C2FFB23B__INCLUDED_)

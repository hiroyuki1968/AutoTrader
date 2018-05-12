#if !defined(AFX_LOGINDLG_H__5981E5D7_BDBD_4EFE_B0F6_717A7470DDA7__INCLUDED_)
#define AFX_LOGINDLG_H__5981E5D7_BDBD_4EFE_B0F6_717A7470DDA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg ダイアログ

class CLoginDlg : public CDialog
{
// コンストラクション
public:
	CLoginDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_LOGIN_DIALOG };
	CEdit	m_Edit1;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	CString m_strPasswd;
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CLoginDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_LOGINDLG_H__5981E5D7_BDBD_4EFE_B0F6_717A7470DDA7__INCLUDED_)

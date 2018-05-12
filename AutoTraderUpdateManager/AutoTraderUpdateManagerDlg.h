// AutoTraderUpdateManagerDlg.h : ヘッダー ファイル
//

#if !defined(AFX_AUTOTRADERUPDATEMANAGERDLG_H__BE37CE3D_967C_4C84_8134_8C31DA3E4C3B__INCLUDED_)
#define AFX_AUTOTRADERUPDATEMANAGERDLG_H__BE37CE3D_967C_4C84_8134_8C31DA3E4C3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderUpdateManagerDlg ダイアログ

class CAutoTraderUpdateManagerDlg : public CDialog
{
// 構築
public:
	CAutoTraderUpdateManagerDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CAutoTraderUpdateManagerDlg)
	enum { IDD = IDD_AUTOTRADERUPDATEMANAGER_DIALOG };
		// メモ: この位置に ClassWizard によってデータ メンバが追加されます。
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAutoTraderUpdateManagerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAutoTraderUpdateManagerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_AUTOTRADERUPDATEMANAGERDLG_H__BE37CE3D_967C_4C84_8134_8C31DA3E4C3B__INCLUDED_)

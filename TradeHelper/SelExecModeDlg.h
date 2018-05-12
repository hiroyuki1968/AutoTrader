#if !defined(AFX_SELEXECMODEDLG_H__9944A218_B402_4FB2_9AB3_387F82310DF5__INCLUDED_)
#define AFX_SELEXECMODEDLG_H__9944A218_B402_4FB2_9AB3_387F82310DF5__INCLUDED_

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
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSelExecModeDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SELEXECMODEDLG_H__9944A218_B402_4FB2_9AB3_387F82310DF5__INCLUDED_)

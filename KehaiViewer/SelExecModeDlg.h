#if !defined(AFX_SELEXECMODEDLG_H__556E25F4_839C_417E_9109_5FC521638D83__INCLUDED_)
#define AFX_SELEXECMODEDLG_H__556E25F4_839C_417E_9109_5FC521638D83__INCLUDED_

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
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
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

#endif // !defined(AFX_SELEXECMODEDLG_H__556E25F4_839C_417E_9109_5FC521638D83__INCLUDED_)

// SelExecModeDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "tradehelper.h"
#include "SelExecModeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelExecModeDlg ダイアログ


CSelExecModeDlg::CSelExecModeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelExecModeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelExecModeDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CSelExecModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelExecModeDlg)
	DDX_Control(pDX, IDC_CHECK1, m_Check1);
	DDX_Control(pDX, IDC_CHECK2, m_Check2);
	DDX_Control(pDX, IDC_CHECK3, m_Check3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelExecModeDlg, CDialog)
	//{{AFX_MSG_MAP(CSelExecModeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelExecModeDlg メッセージ ハンドラ

BOOL CSelExecModeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CSelExecModeDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	m_nExecMode = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO3) - IDC_RADIO1;
	m_bMentenance0 = m_Check1.GetCheck();
	m_bMentenance1 = m_Check2.GetCheck();
	m_bMentenance2 = m_Check3.GetCheck();
	
	CDialog::OnOK();
}

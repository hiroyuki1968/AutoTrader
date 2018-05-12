// SelExecModeDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "tradeconsole.h"
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

void CSelExecModeDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	m_bMentenance0 = m_Check1.GetCheck();
	m_bMentenance1 = m_Check2.GetCheck();
	m_bMentenance2 = m_Check3.GetCheck();
	
	CDialog::OnOK();
}

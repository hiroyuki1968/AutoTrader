// NotesDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "tradehelper.h"
#include "NotesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotesDlg ダイアログ


CNotesDlg::CNotesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNotesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNotesDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CNotesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNotesDlg)
	DDX_Control(pDX, IDC_CHECK1, m_Check1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNotesDlg, CDialog)
	//{{AFX_MSG_MAP(CNotesDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotesDlg メッセージ ハンドラ

void CNotesDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	m_bExeNotes = m_Check1.GetCheck() == 1;
	
	CDialog::OnOK();
}

void CNotesDlg::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	if (GetKeyState(VK_ESCAPE) >= 0)
		CDialog::OnCancel();
	
//	CDialog::OnCancel();
}

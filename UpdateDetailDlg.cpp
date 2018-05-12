// UpdateDetailDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "autotrader.h"
#include "UpdateDetailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdateDetailDlg ダイアログ


CUpdateDetailDlg::CUpdateDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateDetailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpdateDetailDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CUpdateDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpdateDetailDlg)
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_TEXT1, m_Text1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUpdateDetailDlg, CDialog)
	//{{AFX_MSG_MAP(CUpdateDetailDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateDetailDlg メッセージ ハンドラ

BOOL CUpdateDetailDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	m_Text1.SetWindowText(m_lpszDocument);
	m_Edit1.SetWindowText(m_lpszUpdateDetail);
	if (m_uType == MB_OK)
		m_Cancel.ShowWindow(SW_HIDE);
	SetTimer(1, 0, NULL);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CUpdateDetailDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	KillTimer(1);
	m_Edit1.SetSel(0, 0);
	
	CDialog::OnTimer(nIDEvent);
}

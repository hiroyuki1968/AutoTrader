// SetupDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "autotrader.h"
#include "SetupDlg.h"

#include "Common.h"
#include "AutoTraderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg ダイアログ


CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupDlg)
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_EDIT3, m_Edit3);
	DDX_Control(pDX, IDC_EDIT4, m_Edit4);
	DDX_Control(pDX, IDC_EDIT5, m_Edit5);
	DDX_Control(pDX, IDC_EDIT6, m_Edit6);
	DDX_Control(pDX, IDC_EDIT7, m_Edit7);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg メッセージ ハンドラ

BOOL CSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	m_Edit1.SetWindowText(m_strTreasureId);
	m_Edit2.SetWindowText(m_strTreasurePasswd);
	m_Edit3.SetWindowText(m_strMatsuiId);
	m_Edit4.SetWindowText(m_strMatsuiPasswd);
	m_Edit5.SetWindowText(m_strCosmoId);
	m_Edit6.SetWindowText(m_strCosmoPasswd);
	m_Edit7.SetWindowText(m_strDataDir);
	CheckRadioButton(IDC_RADIO1, IDC_RADIO7, IDC_RADIO1 + m_nAutoTraderUpdateType);
	m_bAutoTraderUpdated = FALSE;
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CSetupDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	m_Edit1.GetWindowText(m_strTreasureId);
	m_Edit2.GetWindowText(m_strTreasurePasswd);
	m_Edit3.GetWindowText(m_strMatsuiId);
	m_Edit4.GetWindowText(m_strMatsuiPasswd);
	m_Edit5.GetWindowText(m_strCosmoId);
	m_Edit6.GetWindowText(m_strCosmoPasswd);
	m_Edit7.GetWindowText(m_strDataDir);
	m_nAutoTraderUpdateType = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO7) - IDC_RADIO1;
	
	CDialog::OnOK();
}

void CSetupDlg::OnButton1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	EnableWindow(FALSE);
	int nAutoTraderUpdateType = m_pAutoTraderDlg->m_nAutoTraderUpdateType;
	m_pAutoTraderDlg->m_nAutoTraderUpdateType = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO7) - IDC_RADIO1;
	if (m_pAutoTraderDlg->m_nAutoTraderUpdateType == 6)
		m_pAutoTraderDlg->m_nAutoTraderUpdateType = 0;
	else
		m_pAutoTraderDlg->m_nAutoTraderUpdateType = m_pAutoTraderDlg->m_nAutoTraderUpdateType / 2 * 2;
	switch (m_pAutoTraderDlg->UpdateAutoTrader0()) {
	case 0:
		MessageBox(_T("既に最新です"), NULL, MB_ICONINFORMATION);
		break;
	case 1:
		switch (m_pAutoTraderDlg->UpdateAutoTrader1()) {
		case 2:
			m_bAutoTraderUpdated = TRUE;
		}
	}
	m_pAutoTraderDlg->m_nAutoTraderUpdateType = nAutoTraderUpdateType;
	EnableWindow();
	if (m_bAutoTraderUpdated) {
		WrStrFile(m_pAutoTraderDlg->m_strAutoExecFPath, _T("128\n"));
		OnCancel();
	}
}

void CSetupDlg::OnButton2() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	SetCurrentDirectory(m_strDataDir);
	CString strDataDir = FolderDialog(m_hWnd);
	SetCurrentDirectory(m_strDir);
	if (strDataDir.GetLength())
		m_Edit7.SetWindowText(strDataDir);
}

void CSetupDlg::OnButton3() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_Edit7.SetWindowText(m_strDefaultDataDir);
}

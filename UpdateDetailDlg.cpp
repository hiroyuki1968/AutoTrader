// UpdateDetailDlg.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CUpdateDetailDlg �_�C�A���O


CUpdateDetailDlg::CUpdateDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateDetailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpdateDetailDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
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
// CUpdateDetailDlg ���b�Z�[�W �n���h��

BOOL CUpdateDetailDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	m_Text1.SetWindowText(m_lpszDocument);
	m_Edit1.SetWindowText(m_lpszUpdateDetail);
	if (m_uType == MB_OK)
		m_Cancel.ShowWindow(SW_HIDE);
	SetTimer(1, 0, NULL);
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CUpdateDetailDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	KillTimer(1);
	m_Edit1.SetSel(0, 0);
	
	CDialog::OnTimer(nIDEvent);
}

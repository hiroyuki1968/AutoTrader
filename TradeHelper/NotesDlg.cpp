// NotesDlg.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CNotesDlg �_�C�A���O


CNotesDlg::CNotesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNotesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNotesDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
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
// CNotesDlg ���b�Z�[�W �n���h��

void CNotesDlg::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	m_bExeNotes = m_Check1.GetCheck() == 1;
	
	CDialog::OnOK();
}

void CNotesDlg::OnCancel() 
{
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	if (GetKeyState(VK_ESCAPE) >= 0)
		CDialog::OnCancel();
	
//	CDialog::OnCancel();
}

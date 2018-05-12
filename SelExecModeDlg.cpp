// SelExecModeDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "autotrader.h"
#include "SelExecModeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelExecModeDlg �_�C�A���O


CSelExecModeDlg::CSelExecModeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelExecModeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelExecModeDlg)
	//}}AFX_DATA_INIT
}


void CSelExecModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelExecModeDlg)
	DDX_Control(pDX, IDC_CHECK1, m_Check1);
	DDX_Control(pDX, IDC_CHECK2, m_Check2);
	DDX_Control(pDX, IDC_CHECK3, m_Check3);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DateTimeCtrl1);
	DDX_Control(pDX, IDC_GROUP2, m_Group2);
	DDX_Control(pDX, IDC_GROUP3, m_Group3);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_MonthCalCtrl1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelExecModeDlg, CDialog)
	//{{AFX_MSG_MAP(CSelExecModeDlg)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelExecModeDlg ���b�Z�[�W �n���h��

BOOL CSelExecModeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������

	CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);

	SYSTEMTIME StDate;
	COleDateTime DtCur = COleDateTime::GetCurrentTime();
	COleDateTime DtDate = DtCur;
	COleDateTimeSpan Dts1Day(1, 0, 0, 0);
	int nCurYear = DtCur.GetYear();
	int nCurMonth = DtCur.GetMonth();
	int nCurDay = DtCur.GetDay();
	int nCurHour = DtCur.GetHour();
	int nDayOfWeek;
	while (
		(nDayOfWeek = DtDate.GetDayOfWeek()) == 1
		||  nDayOfWeek == 7
		||  nCurHour < 17  &&  DtDate.GetYear() == nCurYear  &&  DtDate.GetMonth() == nCurMonth  &&  DtDate.GetDay() == nCurDay
	)
		DtDate -= Dts1Day;
	DtDate.GetAsSystemTime(StDate);
	m_MonthCalCtrl1.SetCurSel(&StDate);

	DtDate.SetTime(9, 0, 0);
	DtDate.GetAsSystemTime(StDate);
	m_DateTimeCtrl1.SetTime(&StDate);
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CSelExecModeDlg::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������

	m_nExecMode = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO3) - IDC_RADIO1;
	m_bMentenance0 = m_Check1.GetCheck();
	m_bMentenance1 = m_Check2.GetCheck();
	m_bMentenance2 = m_Check3.GetCheck();

	SYSTEMTIME StDate0;
	SYSTEMTIME StDate1;
	m_MonthCalCtrl1.GetCurSel(&StDate0);
	m_DateTimeCtrl1.GetTime(&StDate1);
	m_DtSimStart.SetDateTime(StDate0.wYear, StDate0.wMonth, StDate0.wDay, StDate1.wHour, StDate1.wMinute, StDate1.wSecond);
	
	CDialog::OnOK();
}

void CSelExecModeDlg::OnRadio1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	BOOL bEnable = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO3) - IDC_RADIO1;
	m_MonthCalCtrl1.EnableWindow(bEnable);
	m_DateTimeCtrl1.EnableWindow(bEnable);
	m_Group3.EnableWindow(bEnable);
	bEnable = ! bEnable;
	m_Check1.EnableWindow(bEnable);
	m_Check2.EnableWindow(bEnable);
	m_Check3.EnableWindow(bEnable);
	m_Group2.EnableWindow(bEnable);
}

void CSelExecModeDlg::OnRadio2() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnRadio1();
}

void CSelExecModeDlg::OnRadio3() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnRadio1();
}

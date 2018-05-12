// RemitRegDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "tradehelper.h"
#include "RemitRegDlg.h"

#include "../AutoTraderVer.h"
#include "../AutoTraderDef.h"
#include "../Common.h"
#include "../License.h"
#include "../AutoTraderProc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRemitRegDlg �_�C�A���O


CRemitRegDlg::CRemitRegDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRemitRegDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRemitRegDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CRemitRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRemitRegDlg)
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_MonthCalCtrl1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRemitRegDlg, CDialog)
	//{{AFX_MSG_MAP(CRemitRegDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemitRegDlg ���b�Z�[�W �n���h��

void CRemitRegDlg::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	// ���[���A�h���X�擾
	CString strMailAddr;
	m_Edit1.GetWindowText(strMailAddr);
	if (strMailAddr.IsEmpty()) {
		MessageBox(_T("�o�^���[���A�h���X����͂��Ă�������"), NULL, MB_ICONSTOP);
		return;
	}
	// ���C�Z���X�J�n���擾
	SYSTEMTIME StDate;
	m_MonthCalCtrl1.GetCurSel(&StDate);
	COleDateTime DtDate(StDate.wYear, StDate.wMonth, StDate.wDay, 0, 0, 0);
	strMailAddr += DtDate.Format("%Y%m%d");
	// ���C�Z���X�L�[�擾
	CString strLicenseKey;
	m_Edit2.GetWindowText(strLicenseKey);
	if (strLicenseKey.IsEmpty()) {
		MessageBox(_T("���C�Z���X�L�[����͂��Ă�������"), NULL, MB_ICONSTOP);
		return;
	}
	strLicenseKey.MakeUpper();
	// ���C�Z���X�L�[�`�F�b�N
	if (! CheckLicenseKey(SECRET_KEY, strMailAddr, strLicenseKey)) {
		MessageBox(_T("�o�^���[���A�h���X�܂��̓��C�Z���X�J�n���܂��̓��C�Z���X�L�[������������܂���"), NULL, MB_ICONSTOP);
		return;
	}
	// ���C�Z���X�J�n���`�F�b�N
	COleDateTime DtCur = COleDateTime::GetCurrentTime();
	if (DtCur < DtDate) {
		MessageBox(_T("���C�Z���X�L�[�̊J�n���O�ł��B"), NULL, MB_ICONSTOP);
		return;
	}
	if (DtCur >= DtDate + COleDateTimeSpan(30, 0, 0, 0)) {
		MessageBox(_T("���C�Z���X�L�[�̗L���������؂�Ă��܂��B"), NULL, MB_ICONSTOP);
		return;
	}
	// �G���R�[�h
	strMailAddr = EncodeSecretString(strMailAddr);
	strLicenseKey = EncodeSecretString(strLicenseKey);
	// ���W�X�g���T�u�L�[�쐬
	HKEY hKey;
	if (RegCreateKeyAutoTrader(hKey))
		return;
	LONG nRegFunc;
	// �o�^���[���A�h���X�ݒ�
	if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_MADDR, NULL, REG_SZ, (BYTE *)(LPCTSTR)strMailAddr, strMailAddr.GetLength())) != ERROR_SUCCESS) {
		MessageBox(_T("���W�X�g���ݒ�G���[�O: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
		RegCloseKey(hKey);
		return;
	}
	// ���C�Z���X�L�[�ݒ�
	if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_LKEY, NULL, REG_SZ, (BYTE *)(LPCTSTR)strLicenseKey, strLicenseKey.GetLength())) != ERROR_SUCCESS) {
		MessageBox(_T("���W�X�g���ݒ�G���[�P: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
		RegCloseKey(hKey);
		return;
	}
	// ���W�X�g���N���[�Y
	if (RegCloseKeyAutoTrader(hKey))
		return;
	// ��t���b�Z�[�W
	MessageBox(_T("���������肪�Ƃ��������܂�"), NULL, MB_ICONINFORMATION);
	
	CDialog::OnOK();
}

void CRemitRegDlg::OnButton1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	// ���ݓ�
	CTime TCur = CTime::GetCurrentTime();
	if (m_bIDate  &&  m_bIVer  &&  m_dwIVer >= THIS_VER) {
		// ���p���ԃ`�F�b�N
		CTimeSpan Ts(7, 0, 0, 0);
		if (TCur > m_TIDate + Ts) {
			MessageBox(_T("���p���Ԃ��I�����Ă��܂��B�����o�^���Ă��������B"), NULL, MB_ICONSTOP);
			return;
		}
		if (TCur < m_TIDate) {
			MessageBox(_T("����N�����G���[�B�����o�^���Ă��������B"), NULL, MB_ICONSTOP);
			return;
		}
	} else {
		// ���W�X�g���T�u�L�[�쐬
		HKEY hKey;
		if (RegCreateKeyAutoTrader(hKey))
			return;
		LONG nRegFunc;
		// ����N�����t
		DWORD dwIYear = TCur.GetYear();
		DWORD dwIMon = TCur.GetMonth();
		DWORD dwIDay = TCur.GetDay();
		DWORD dwIVer = THIS_VER;
		// �G���R�[�h
		dwIYear = EncodeSecretDWord(dwIYear);
		dwIMon = EncodeSecretDWord(dwIMon);
		dwIDay = EncodeSecretDWord(dwIDay);
		dwIVer = EncodeSecretDWord(dwIVer);
		// �N�ݒ�
		if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_IYEAR, NULL, REG_DWORD, (BYTE*)&dwIYear, sizeof(dwIYear))) != ERROR_SUCCESS) {
			MessageBox(_T("���W�X�g���ݒ�G���[�O: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
			RegCloseKey(hKey);
			return;
		}
		// ���ݒ�
		if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_IMON, NULL, REG_DWORD, (BYTE*)&dwIMon, sizeof(dwIMon))) != ERROR_SUCCESS) {
			MessageBox(_T("���W�X�g���ݒ�G���[�P: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
			RegCloseKey(hKey);
			return;
		}
		// ���ݒ�
		if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_IDAY, NULL, REG_DWORD, (BYTE*)&dwIDay, sizeof(dwIDay))) != ERROR_SUCCESS) {
			MessageBox(_T("���W�X�g���ݒ�G���[�Q: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
			RegCloseKey(hKey);
			return;
		}
		// �o�[�W�����ݒ�
		if ((nRegFunc = RegSetValueEx(hKey, REG_KEY_IVER, NULL, REG_DWORD, (BYTE*)&dwIVer, sizeof(dwIVer))) != ERROR_SUCCESS) {
			MessageBox(_T("���W�X�g���ݒ�G���[�R: ") + GetLastErrorMessage(nRegFunc), NULL, MB_ICONSTOP);
			RegCloseKey(hKey);
			return;
		}
		// ���W�X�g���N���[�Y
		if (RegCloseKeyAutoTrader(hKey))
			return;
	}
	EndDialog(IDOK);
}

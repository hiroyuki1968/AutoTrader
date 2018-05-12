#if !defined(AFX_SETUPDLG_H__3B354A08_2A8B_4F17_B472_53EB9EF77FE6__INCLUDED_)
#define AFX_SETUPDLG_H__3B354A08_2A8B_4F17_B472_53EB9EF77FE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupDlg.h : �w�b�_�[ �t�@�C��
//

class CAutoTraderDlg;

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg �_�C�A���O

class CSetupDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CSetupDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSetupDlg)
	enum { IDD = IDD_SETUP_DIALOG };
	CEdit	m_Edit1;
	CEdit	m_Edit2;
	CEdit	m_Edit3;
	CEdit	m_Edit4;
	CEdit	m_Edit5;
	CEdit	m_Edit6;
	CEdit	m_Edit7;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	CAutoTraderDlg* m_pAutoTraderDlg;
	CString m_strTreasureId;
	CString m_strTreasurePasswd;
	CString m_strMatsuiId;
	CString m_strMatsuiPasswd;
	CString m_strCosmoId;
	CString m_strCosmoPasswd;
	CString m_strDir;
	CString m_strDefaultDataDir;
	int m_nAutoTraderUpdateType;
	BOOL m_bAutoTraderUpdated;
	CString m_strDataDir;
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSetupDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SETUPDLG_H__3B354A08_2A8B_4F17_B472_53EB9EF77FE6__INCLUDED_)

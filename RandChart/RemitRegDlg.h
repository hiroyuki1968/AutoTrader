#if !defined(AFX_REMITREGDLG_H__4596789B_1B60_4F41_8E42_F055F84A99FB__INCLUDED_)
#define AFX_REMITREGDLG_H__4596789B_1B60_4F41_8E42_F055F84A99FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RemitRegDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CRemitRegDlg �_�C�A���O

class CRemitRegDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CRemitRegDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CRemitRegDlg)
	enum { IDD = IDD_REMITREG_DIALOG };
	CEdit	m_Edit1;
	CEdit	m_Edit2;
	CMonthCalCtrl	m_MonthCalCtrl1;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CRemitRegDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	BOOL m_bIDate;
	CTime m_TIDate;
	BOOL m_bIVer;
	DWORD m_dwIVer;
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CRemitRegDlg)
	virtual void OnOK();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_REMITREGDLG_H__4596789B_1B60_4F41_8E42_F055F84A99FB__INCLUDED_)

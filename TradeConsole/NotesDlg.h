#if !defined(AFX_NOTESDLG_H__850F602F_F034_4B42_B8BC_5B60F49C2D3F__INCLUDED_)
#define AFX_NOTESDLG_H__850F602F_F034_4B42_B8BC_5B60F49C2D3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NotesDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CNotesDlg �_�C�A���O

class CNotesDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CNotesDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CNotesDlg)
	enum { IDD = IDD_NOTES_DIALOG };
	CButton	m_Check1;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CNotesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	BOOL m_bExeNotes;
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CNotesDlg)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_NOTESDLG_H__850F602F_F034_4B42_B8BC_5B60F49C2D3F__INCLUDED_)

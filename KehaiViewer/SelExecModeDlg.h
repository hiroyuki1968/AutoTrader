#if !defined(AFX_SELEXECMODEDLG_H__556E25F4_839C_417E_9109_5FC521638D83__INCLUDED_)
#define AFX_SELEXECMODEDLG_H__556E25F4_839C_417E_9109_5FC521638D83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelExecModeDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CSelExecModeDlg �_�C�A���O

class CSelExecModeDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CSelExecModeDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSelExecModeDlg)
	enum { IDD = IDD_SELEXECMODE_DIALOG };
		// ����: ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSelExecModeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	int m_nExecMode;
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSelExecModeDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SELEXECMODEDLG_H__556E25F4_839C_417E_9109_5FC521638D83__INCLUDED_)

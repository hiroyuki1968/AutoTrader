#if !defined(AFX_SELEXECMODEDLG_H__B90FFCCB_C771_408B_90E0_BE8253F4853F__INCLUDED_)
#define AFX_SELEXECMODEDLG_H__B90FFCCB_C771_408B_90E0_BE8253F4853F__INCLUDED_

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
	CButton	m_Check1;
	CButton	m_Check2;
	CButton	m_Check3;
	CDateTimeCtrl	m_DateTimeCtrl1;
	CButton	m_Group2;
	CButton	m_Group3;
	CMonthCalCtrl	m_MonthCalCtrl1;
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
	BOOL m_bMentenance0;
	BOOL m_bMentenance1;
	BOOL m_bMentenance2;
	COleDateTime m_DtSimStart;
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSelExecModeDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SELEXECMODEDLG_H__B90FFCCB_C771_408B_90E0_BE8253F4853F__INCLUDED_)

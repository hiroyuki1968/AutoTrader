#if !defined(AFX_UPDATEDETAILDLG_H__78CAD6E5_365F_4BBB_AFA2_9E59C2FFB23B__INCLUDED_)
#define AFX_UPDATEDETAILDLG_H__78CAD6E5_365F_4BBB_AFA2_9E59C2FFB23B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdateDetailDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CUpdateDetailDlg �_�C�A���O

class CUpdateDetailDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CUpdateDetailDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CUpdateDetailDlg)
	enum { IDD = IDD_UPDATEDETAIL_DIALOG };
	CButton	m_Cancel;
	CEdit	m_Edit1;
	CStatic	m_Text1;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CUpdateDetailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	UINT m_uType;
	LPCTSTR m_lpszDocument;
	LPCTSTR m_lpszUpdateDetail;
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CUpdateDetailDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_UPDATEDETAILDLG_H__78CAD6E5_365F_4BBB_AFA2_9E59C2FFB23B__INCLUDED_)

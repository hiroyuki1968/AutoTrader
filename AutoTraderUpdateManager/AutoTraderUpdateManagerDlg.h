// AutoTraderUpdateManagerDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_AUTOTRADERUPDATEMANAGERDLG_H__BE37CE3D_967C_4C84_8134_8C31DA3E4C3B__INCLUDED_)
#define AFX_AUTOTRADERUPDATEMANAGERDLG_H__BE37CE3D_967C_4C84_8134_8C31DA3E4C3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderUpdateManagerDlg �_�C�A���O

class CAutoTraderUpdateManagerDlg : public CDialog
{
// �\�z
public:
	CAutoTraderUpdateManagerDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAutoTraderUpdateManagerDlg)
	enum { IDD = IDD_AUTOTRADERUPDATEMANAGER_DIALOG };
		// ����: ���̈ʒu�� ClassWizard �ɂ���ăf�[�^ �����o���ǉ�����܂��B
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAutoTraderUpdateManagerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAutoTraderUpdateManagerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_AUTOTRADERUPDATEMANAGERDLG_H__BE37CE3D_967C_4C84_8134_8C31DA3E4C3B__INCLUDED_)

#if !defined(AFX_AUTOTRADERUPDATEMANAGERWND_H__8FC9D8F3_B5ED_4691_9285_5A159CCD2A98__INCLUDED_)
#define AFX_AUTOTRADERUPDATEMANAGERWND_H__8FC9D8F3_B5ED_4691_9285_5A159CCD2A98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AutoTraderUpdateManagerWnd.h : �w�b�_�[ �t�@�C��
//

#include <Lmcons.h>

/////////////////////////////////////////////////////////////////////////////
// CAutoTraderUpdateManagerWnd �E�B���h�E

class CAutoTraderUpdateManagerWnd : public CWnd
{
// �R���X�g���N�V����
public:
	CAutoTraderUpdateManagerWnd();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CAutoTraderUpdateManagerWnd)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CAutoTraderUpdateManagerWnd();
protected:
	CString m_strUserName;
	CString m_strProductCode;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CAutoTraderUpdateManagerWnd)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnUserName(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnProductCode(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_AUTOTRADERUPDATEMANAGERWND_H__8FC9D8F3_B5ED_4691_9285_5A159CCD2A98__INCLUDED_)

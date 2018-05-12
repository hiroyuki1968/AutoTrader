#if !defined(AFX_DLFILETHREAD_H__AD0365E0_8621_43AB_B071_5DB21589331E__INCLUDED_)
#define AFX_DLFILETHREAD_H__AD0365E0_8621_43AB_B071_5DB21589331E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlFileThread.h : �w�b�_�[ �t�@�C��
//

#include <afxinet.h>
#include "StringBuffer.h"



/////////////////////////////////////////////////////////////////////////////
// CDlFileThread �X���b�h

class CDlFileThread : public CWinThread
{
	DECLARE_DYNCREATE(CDlFileThread)
public:
	CDlFileThread();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
protected:
//	CDlFileThread();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^

// �A�g���r���[�g
public:
	CString m_strDataDir;
	CString m_strServerName;
	CString m_strObject;
	INTERNET_PORT m_nPort;
	int m_nVerb;
	DWORD m_dwFlags;
	LPCTSTR m_lpszHeaders;
	LPCTSTR m_lpszOptional;
	CString m_strFPath;
	CString m_strFPathC0;
	CString m_strFPathC1;

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlFileThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CDlFileThread();
protected:
//	virtual ~CDlFileThread();
	void DispErrorLog(LPCTSTR lpszFormat, ...);

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlFileThread)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLFILETHREAD_H__AD0365E0_8621_43AB_B071_5DB21589331E__INCLUDED_)

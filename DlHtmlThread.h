#if !defined(AFX_DLHTMLTHREAD_H__DF5B7972_5E54_46E8_86D4_368B41B105D7__INCLUDED_)
#define AFX_DLHTMLTHREAD_H__DF5B7972_5E54_46E8_86D4_368B41B105D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlHtmlThread.h : �w�b�_�[ �t�@�C��
//

#include <afxinet.h>
#include "StringBuffer.h"



/////////////////////////////////////////////////////////////////////////////
// CDlHtmlThread �X���b�h

class CDlHtmlThread : public CWinThread
{
	DECLARE_DYNCREATE(CDlHtmlThread)
public:
	CDlHtmlThread();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
protected:
//	CDlHtmlThread();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^

// �A�g���r���[�g
public:
	CString m_strDataDir;
	CInternetSession* m_pSession;
	CString m_strServerName;
	CString m_strObject;
	INTERNET_PORT m_nPort;
	int m_nVerb;
	DWORD m_dwFlags;
	LPCTSTR m_lpszHeaders;
	LPCTSTR m_lpszOptional;
	CStringBuffer m_sbHtml;

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlHtmlThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CDlHtmlThread();
protected:
//	virtual ~CDlHtmlThread();
	void DispErrorLog(LPCTSTR lpszFormat, ...);

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlHtmlThread)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLHTMLTHREAD_H__DF5B7972_5E54_46E8_86D4_368B41B105D7__INCLUDED_)

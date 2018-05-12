#if !defined(AFX_DISPWB2THREAD_H__0DB963DA_4E57_4597_BDA5_DAD930C0BA01__INCLUDED_)
#define AFX_DISPWB2THREAD_H__0DB963DA_4E57_4597_BDA5_DAD930C0BA01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DispWB2Thread.h : �w�b�_�[ �t�@�C��
//



#include "webbrowser2.h"

#include <afxinet.h>
#include "../StringBuffer.h"

/////////////////////////////////////////////////////////////////////////////
// CDispWB2Thread �X���b�h

class CDispWB2Thread : public CWinThread
{
	DECLARE_DYNCREATE(CDispWB2Thread)
//protected:
public:
	CDispWB2Thread();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^

// �A�g���r���[�g
public:

// �I�y���[�V����
public:
	int m_nMode;
	CString m_strDataDir;
	CString m_strPreUrl;
	CString m_strUrl;
	CString m_strFPath;

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDispWB2Thread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
//protected:
public:
	virtual ~CDispWB2Thread();
protected:
	int DlFile(const CString& strFPath, int nVerb, DWORD dwFlags = INTERNET_FLAG_EXISTING_CONNECT, LPCTSTR lpszHeaders = NULL, LPCTSTR lpszOptional = NULL);
	void DispErrorLog(LPCTSTR lpszFormat, ...);
	CHttpConnection* m_pServer;
	CHttpFile* m_pFile;
	DWORD m_dwServiceType;
	CString m_strServerName;
	CString m_strObject;
	CString m_strObjectC;
	INTERNET_PORT m_nPort;
	CStringBuffer m_sbOptional;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDispWB2Thread)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DISPWB2THREAD_H__0DB963DA_4E57_4597_BDA5_DAD930C0BA01__INCLUDED_)

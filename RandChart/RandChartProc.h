#if !defined(RANDCHARTRPROC_H__INCLUDED_)
#define RANDCHARTRPROC_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

typedef struct {
	CString strCode;
	CString strName;
	short sUnit;
	COleDateTime Dt;
	CString strSrcFPath0;
	CString strSrcFPath1;
} Parm;

/////////////////////////////////////////////////////////////////////////////
// CParmArray : Parm ”z—ñƒNƒ‰ƒX

typedef CArray<Parm, const Parm&> CParmArray;

#endif // !defined(RANDCHARTRPROC_H__INCLUDED_)

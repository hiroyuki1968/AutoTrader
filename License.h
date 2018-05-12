#if !defined(LICENSE_H__INCLUDED_)
#define LICENSE_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

int CheckLicenseKey(LPCTSTR lpszEncodedSecretKey, const CString& strMailAddr, const CString& strLicenseKey);

#endif // !defined(LICENSE_H__INCLUDED_)

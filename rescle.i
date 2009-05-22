%module rescle

%typemap(in) wchar_t const * {
	PyObject* tmp = $input;
	bool isUnicode = PyUnicode_Check( tmp );
	if ( isUnicode ) {
		// ok.
	} else if ( PyString_Check( tmp ) ) {
		// convert.
		tmp = PyUnicode_FromObject( tmp );
	} else {
	    SWIG_exception_fail(SWIG_ValueError, "Expected unicode string." ); 
	}
	
	Py_ssize_t len = PyUnicode_GetSize( tmp );
	wchar_t wcharBuf[1024]; memset( wcharBuf, 0, sizeof(wcharBuf) );
	Py_ssize_t i = PyUnicode_AsWideChar( (PyUnicodeObject*) tmp, wcharBuf, len );
	wcharBuf[i] = 0;
	$1 = wcharBuf;
}

%typemap(in) WORD {
	$1 = PyInt_AsLong($input);
}

%typemap(in) UINT {
	$1 = PyInt_AsLong($input);
}

%{
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "rescle.h"
%}


class ResourceUpdater {
public:
	ResourceUpdater();
	~ResourceUpdater();
public:
	bool Load( const wchar_t* filename );
	bool ChangeVersionString( const WORD languageId, const wchar_t* name, const wchar_t* value );
	bool ChangeString( WORD languageId, UINT id, const wchar_t* value );
	bool ChangeVersionProductVersion( const WORD languageId, const UINT id, const unsigned char& v1, const unsigned char& v2, const unsigned char& v3, const unsigned char& v4 );
	bool ChangeVersionFileVersion( const WORD languageId, const UINT id, const unsigned char& v1, const unsigned char& v2, const unsigned char& v3, const unsigned char& v4 );
	bool Commit();
public:
	static bool UpdateRaw( const wchar_t* filename, const WORD& languageId, const wchar_t* type, const UINT& id, const void* data, const size_t& dataSize, const bool& deleteOld );
	static bool GetResourcePointer( const HMODULE& hModule, const WORD& languageId, const int& id, const wchar_t* type, void*& data, size_t& dataSize );
};

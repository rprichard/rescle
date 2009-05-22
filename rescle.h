#ifndef VERSION_INFO_UPDATER
#define VERSION_INFO_UPDATER

#include <tchar.h>
#include <windows.h>
#include <string>
#include <vector>
#include <map>

#define RU_VS_COMMENTS          L"Comments"
#define RU_VS_COMPANY_NAME      L"CompanyName"
#define RU_VS_FILE_DESCRIPTION  L"FileDescription"
#define RU_VS_FILE_VERSION      L"FileVersion"
#define RU_VS_INTERNAL_NAME     L"InternalName"
#define RU_VS_LEGAL_COPYRIGHT   L"LegalCopyright"
#define RU_VS_LEGALLRADEMARKS   L"LegalTrademarks"
#define RU_VS_ORIGINAL_FILENAME L"OriginalFilename"
#define RU_VS_PRIVATE_BUILD     L"PrivateBuild"
#define RU_VS_PRODUCT_NAME      L"ProductName"
#define RU_VS_PRODUCT_VERSION   L"ProductVersion"
#define RU_VS_SPECIAL_BUILD     L"SpecialBuild"

class VersionStampValue {
public:
	unsigned short wOffset;
	unsigned short wLength;
	unsigned short wKeyLength;
	unsigned short wType;
	std::wstring szKey;
	std::vector<char> Data;
	unsigned short GetLength( const bool& rounding = true ) const;
};

class ResourceUpdater {
public:
	typedef std::basic_string<TCHAR> tstring;
	typedef std::vector<std::wstring> StringValues;
	typedef std::map<UINT,StringValues> StringTable;
	typedef std::map<WORD,StringTable> StringTableMap;

	typedef std::vector<VersionStampValue> VersionStampValues;
	typedef std::map<UINT,VersionStampValues> VersionStampTable;
	typedef std::map<WORD,VersionStampTable> VersionStampMap;
public:
	ResourceUpdater();
	~ResourceUpdater();
public:
	bool Load( const TCHAR* filename );
	bool ChangeVersionString( const WORD& languageId, const WCHAR* name, const WCHAR* value );
	bool ChangeVersionString( const WCHAR* name, const WCHAR* value );
	bool ChangeVersionProductVersion( const WORD& languageId, const UINT& id, const unsigned char& v1, const unsigned char& v2, const unsigned char& v3, const unsigned char& v4 );
	bool ChangeVersionFileVersion( const WORD& languageId, const UINT& id, const unsigned char& v1, const unsigned char& v2, const unsigned char& v3, const unsigned char& v4 );
	bool ChangeString( const WORD& languageId, const UINT& id, const WCHAR* value );
	bool ChangeString( const UINT& id, const WCHAR* value );
	bool Commit();
public:
	static bool UpdateRaw( const TCHAR* filename, const WORD& languageId, const TCHAR* type, const UINT& id, const void* data, const size_t& dataSize, const bool& deleteOld );
	static bool GetResourcePointer( const HMODULE& hModule, const WORD& languageId, const int& id, const TCHAR* type, void*& data, size_t& dataSize );
private:
	bool Deserialize( const void* data, const size_t& dataSize, VersionStampValues& values );
	bool SerializeVersionInfo( VersionStampValues& values, std::vector<char>& out );
	bool SerializeStringTable( const StringValues& values, const UINT& blockId, std::vector<char>& out );
private:
	// not thread-safe
	static BOOL CALLBACK OnEnumResourceName( HMODULE hModule, LPCTSTR lpszType, LPTSTR lpszName, LONG_PTR lParam );
	// not thread-safe
	static BOOL CALLBACK OnEnumResourceLanguage( HANDLE hModule, LPCTSTR lpszType, LPCTSTR lpszName, WORD wIDLanguage, LONG_PTR lParam );
private:
	HMODULE hModule;
	tstring filename;
	VersionStampMap versionStampMap;
	StringTableMap stringTableMap;
};

class ScopedResoueceUpdater {
public:
	ScopedResoueceUpdater( const TCHAR* filename, const bool& deleteOld );
	~ScopedResoueceUpdater();
public:
	HANDLE Get() const;
	bool Commit();
private:
	bool EndUpdate( const bool& doesCommit );
private:
	HANDLE handle;
	bool commited;
};

#endif // VERSION_INFO_UPDATER

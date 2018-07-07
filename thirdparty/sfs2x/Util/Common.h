// ===================================================================
//
// Description		
//		Contains common items shared with all other API files
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __Common__
#define __Common__

// -------------------------------------------------------------------
// Disable export/import unusefull warnings
// -------------------------------------------------------------------
#pragma warning( disable: 4251 )

// -------------------------------------------------------------------
// Define alias to mark exported/imported library items
// -------------------------------------------------------------------
#if defined WIN32
#if defined SMARTFOXCLIENTAPI_EXPORTS
    #define DLLImportExport __declspec(dllexport)
#else
    #define DLLImportExport __declspec(dllimport)
#endif
#else
#define DLLImportExport
#endif

// -------------------------------------------------------------------
// Define boost array deleter
// -------------------------------------------------------------------
template< typename T >
struct array_deleter
{
	void operator ()( T const * p)
	{ 
		delete[] p; 
	}
};

#endif



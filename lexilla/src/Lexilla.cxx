// Lexilla lexer library
/** @file Lexilla.cxx
 ** Lexer infrastructure.
 ** Provides entry points to shared library.
 **/
// Copyright 2019 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#include <cstring>

#include <vector>
#include <initializer_list>

#if defined(_WIN32)
#define EXPORT_FUNCTION __declspec(dllexport)
#define CALLING_CONVENTION __stdcall
#else
#define EXPORT_FUNCTION __attribute__((visibility("default")))
#define CALLING_CONVENTION
#endif

#include "ILexer.h"

#include "LexerModule.h"
#include "CatalogueModules.h"

using namespace Lexilla;

//++Autogenerated -- run lexilla/scripts/LexillaGen.py to regenerate
//**\(extern LexerModule \*;\n\)
extern LexerModule lmCPP;

//--Autogenerated -- end of automatically generated section

namespace {

CatalogueModules catalogueLexilla;

void AddEachLexer() {

	if (catalogueLexilla.Count() > 0) {
		return;
	}

	catalogueLexilla.AddLexerModules({
//++Autogenerated -- run scripts/LexillaGen.py to regenerate
//**\(\t\t&\*,\n\)
		&lmCPP,

//--Autogenerated -- end of automatically generated section
		});

}

}

extern "C" {

EXPORT_FUNCTION int CALLING_CONVENTION GetLexerCount() {
	AddEachLexer();
	return static_cast<int>(catalogueLexilla.Count());
}

EXPORT_FUNCTION void CALLING_CONVENTION GetLexerName(unsigned int index, char *name, int buflength) {
	AddEachLexer();
	*name = 0;
	const char *lexerName = catalogueLexilla.Name(index);
	if (static_cast<size_t>(buflength) > strlen(lexerName)) {
		strcpy(name, lexerName);
	}
}

EXPORT_FUNCTION LexerFactoryFunction CALLING_CONVENTION GetLexerFactory(unsigned int index) {
	AddEachLexer();
	return catalogueLexilla.Factory(index);
}

EXPORT_FUNCTION Scintilla::ILexer5 * CALLING_CONVENTION CreateLexer(const char *name) {
	AddEachLexer();
	for (size_t i = 0; i < catalogueLexilla.Count(); i++) {
		const char *lexerName = catalogueLexilla.Name(i);
		if (0 == strcmp(lexerName, name)) {
			return catalogueLexilla.Create(i);
		}
	}
	return nullptr;
}

EXPORT_FUNCTION const char * CALLING_CONVENTION LexerNameFromID(int identifier) {
	AddEachLexer();
	const LexerModule *pModule = catalogueLexilla.Find(identifier);
	if (pModule) {
		return pModule->languageName;
	}
	return nullptr;
}

EXPORT_FUNCTION const char * CALLING_CONVENTION GetLibraryPropertyNames() {
	return "";
}

EXPORT_FUNCTION void CALLING_CONVENTION SetLibraryProperty(const char *, const char *) {
	// Null implementation
}

EXPORT_FUNCTION const char * CALLING_CONVENTION GetNameSpace() {
	return "lexilla";
}

// Not exported from binary as LexerModule must be built exactly the same as
// modules listed above
void AddStaticLexerModule(LexerModule *plm) {
	AddEachLexer();
	catalogueLexilla.AddLexerModule(plm);
}

}

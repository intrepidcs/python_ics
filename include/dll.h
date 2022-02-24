#ifndef _DLL_H_
#define _DLL_H_

#ifdef _MSC_VER
#pragma warning( disable : 4290 )
#endif

#include "ice/ice_library.h"
#include "ice/ice_exception.h"
#include "ice/ice_function.h"

#ifdef _MSC_VER
#pragma warning( default : 4290 )
#endif

#ifdef _cplusplus
extern "C" {
#endif

bool dll_initialize(char* name=NULL);
bool dll_is_initialized(void);
void dll_uninitialize(void);
bool dll_reinitialize(char* name=NULL);
char* dll_get_error(char* error_msg);
ice::Library* dll_get_library(void);

#ifdef _cplusplus
}
#endif

#endif // _DLL_H_

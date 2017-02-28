#ifndef _DLL_H_
#define _DLL_H_



#pragma warning( disable : 4290 )
#include "ice/ice_library.h"
#include "ice/ice_exception.h"
#include "ice/ice_function.h"
#pragma warning( default : 4290 )

#ifdef _cplusplus
extern "C" {
#endif

bool dll_initialize(void);
bool dll_is_initialized(void);
void dll_uninitialize(void);
char* dll_get_error(char* error_msg);
ice::Library* dll_get_library(void);

#ifdef _cplusplus
}
#endif

#endif // _DLL_H_

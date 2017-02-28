#include "defines.h"

int setup_module_defines(PyObject* module)
{
    int result = 0;
    if (!module)
        return --result;

    result += PyModule_AddStringConstant(module, "BUILD_DATETIME", __DATE__ " " __TIME__);

    if (result == 0) {
        return 1;
    }
    return result;
}

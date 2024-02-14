#include "defines.h"

int setup_module_defines(PyObject* module)
{
    int result = 0;
    if (!module)
        return --result;

    result += PyModule_AddStringConstant(module, "BUILD_DATETIME", __DATE__ " " __TIME__);
    result += PyModule_AddObject(module, "MIN_BASE36_SERIAL", PyLong_FromUnsignedLong(MIN_BASE36_SERIAL));
    result += PyModule_AddObject(module, "MAX_SERIAL", PyLong_FromUnsignedLong(MAX_SERIAL));

    if (result == 0) {
        return 1;
    }
    return result;
}

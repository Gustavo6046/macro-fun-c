#include <stdio.h>
#include <stdlib.h>

#include "my_interface.h"


IDEFAULT_FUNC_BEGIN(MyInterface, char*, supplyMyString, char *myArg)
    char* res = malloc(strlen(myArg) + 1);
    strcpy(res, myArg);
    
    return res;
IDEFAULT_FUNC_END()

IDEFAULT_BEGIN(MyInterface)
    IDEFAULT_MEMBER(MyInterface, supplyMyString)
    IDEFAULT_NONE(MyInterface, setMyString)
    IDEFAULT_NONE(MyInterface, doStuff)
IDEFAULT_END()

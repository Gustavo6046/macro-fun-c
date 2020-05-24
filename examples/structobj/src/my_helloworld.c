#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "my_interface.h"



// First, the implementation members.
IMPL_FUNC_BEGIN(MyInterface, MyHelloWorld, void, setMyString, char* myNewString)
    self->myString = myNewString;
IMPL_FUNC_END()

IMPL_FUNC_BEGIN(MyInterface, MyHelloWorld, char*, supplyMyString, char* myArg)
    char *res = malloc(strlen(myArg) + 6);
    sprintf(res, "mr. %s", myArg);
    return res;
IMPL_FUNC_END()

IMPL_FUNC_BEGIN(MyInterface, MyHelloWorld, void, doStuff, char* myArg)
    self->myString = NULL;

    char *myStr = IMPLCALL(MyInterface, MyHelloWorld, supplyMyString, myArg);
    IMPLCALL(MyInterface, MyHelloWorld, setMyString, myStr);
    
    printf("Hello, World! My name is %s!\n", self->myString);
    
    free(self->myString);
IMPL_FUNC_END()

// Then, the implementation itself.

IMPL_BEGIN(MyInterface, MyHelloWorld)
    IMPL_MEMBER(MyInterface, MyHelloWorld, setMyString)
    IMPL_MEMBER(MyInterface, MyHelloWorld, supplyMyString)
    IMPL_MEMBER(MyInterface, MyHelloWorld, doStuff)
IMPL_END()
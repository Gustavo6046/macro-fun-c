#ifndef MYINTERFACE_HEADER
#define MYINTERFACE_HEADER

#include "structobj.h"
#include "string.h"

//------------------------

typedef struct MyHelloWorld_s {
    char* myString;
} MyHelloWorld;

// All interface members must also be declared outside
// the interface afer it and its defaults. Known limitation
// of using preprocessors here.
INTERFACE_BEGIN(MyInterface)
    INTERFACE_MEMBER(MyInterface, void, setMyString, char* myNewString)
    INTERFACE_MEMBER(MyInterface, char*, supplyMyString, char *myArg) // can transform myArg
    INTERFACE_MEMBER(MyInterface, void, doStuff, char *myArg)
INTERFACE_END(MyInterface)

IDEFAULT_FUNC_DECLARE(MyInterface, char*, supplyMyString, char *myArg);

//-- implementation declaration

IMPL_DECLARE(MyInterface, MyHelloWorld)

//------------------------

#endif

// All interface members must also be declared in the
// implementation, outside the header guard. Noticeable
// limitations of using preprocessors here.
INTERFACE_POST_MEMBER(MyInterface, void, setMyString, char* myNewString)
INTERFACE_POST_MEMBER(MyInterface, char*, supplyMyString, char *myArg)
INTERFACE_POST_MEMBER(MyInterface, void, doStuff, char* myNewString)

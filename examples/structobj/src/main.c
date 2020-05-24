#include "my_interface.h"




int main() {
    MyHelloWorld myHelloWorld;
    myHelloWorld.myString = NULL;

    IMPLCALLON(MyInterface, MyHelloWorld, &myHelloWorld, doStuff, "Bob");

    return 0;
}
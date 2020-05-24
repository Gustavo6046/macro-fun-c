#ifndef STRUCTOBJ_HEADER
#define STRUCTOBJ_HEADER
//---------------------- entering <structobj.h>

/*
 *----
 * structobj.
 * advanced c interfaces.
 *----
 *
 * (c)2020 Gustavo R. Rehermann.
 *         The MIT License.
 */

#include <stdio.h>
#include <stdlib.h>


// This defines an interface named I.
// Concrete 'self' pointers (ie to implementations of
// interfaces)
#define INTERFACE_BEGIN(I)                              typedef struct __intf_##I##_s {
#define INTERFACE_MEMBER(I, RTYPE, NAME, ...)               RTYPE (*__intf_##I##_func_##NAME)(struct __intf_##I##_s *__intfself, void *__implself, __VA_ARGS__);
#define INTERFACE_END(I)                                } __intf_##I; extern __intf_##I __intf_##I##_default;

#define INTERFACE_POST_MEMBER(I, RTYPE, NAME, ...)      typedef RTYPE (*__intf_##I##_func_##NAME##_t)(__intf_##I *__intfself, void *__implself, __VA_ARGS__);\
                                                        static inline __intf_##I##_func_##NAME##_t __intf_##I##_get_func_##NAME(__intf_##I *__intfself, const char *__implname) {\
                                                            if (__intfself->__intf_##I##_func_##NAME)\
                                                                return __intfself->__intf_##I##_func_##NAME;\
                                                            else if (__intf_##I##_default.__intf_##I##_func_##NAME)\
                                                                return __intf_##I##_default.__intf_##I##_func_##NAME;\
                                                            else {\
                                                                __intf_nul(__implname, #NAME, #I);\
                                                                return __intf_##I##_default.__intf_##I##_func_##NAME;\
                                                            }\
                                                        }

// Default member implementations; must be defined
// outside the main interface.
// Keep in mind you can't use the 'self' symbol in
// the interface, as there is no concrete 'self'
// known here. Use INTFCALL instead.
#define IDEFAULT_FUNC_DECLARE(I, RTYPE, NAME, ...)      RTYPE __intf_##I##_default_##NAME(struct __intf_##I##_s *__intfself, void *__implself, __VA_ARGS__);
#define IDEFAULT_FUNC_BEGIN(I, RTYPE, NAME, ...)        RTYPE __intf_##I##_default_##NAME(struct __intf_##I##_s *__intfself, void *__implself, __VA_ARGS__) {
#define IDEFAULT_FUNC_END()                             }

#define IDEFAULT_BEGIN(I)                               __intf_##I __intf_##I##_default = {
#define IDEFAULT_MEMBER(I, NAME)                            .__intf_##I##_func_##NAME = &__intf_##I##_default_##NAME,
#define IDEFAULT_NONE(I, NAME)                              .__intf_##I##_func_##NAME = NULL,
#define IDEFAULT_END()                                  };

// This precedes the arguments, when calling an
// interface function from another function of
// the interface itself. Can only be called from
// within an implementation of one of said 
// interface's members.
#define INTFCALL(I, FNAME, ...)                         (*__intfself->__intf_##I##_func_##FNAME)(__intfself, __implself, __VA_ARGS__)

// Each implementation of an interface's method must
// me defined with IMPL preprocessors.

#define IMPL_DECLARE(I, NAME)                           extern __intf_##I __intf_##I##_impl_##NAME;
#define IMPLOF(I, NAME)                                 &__intf_##I##_impl_##NAME

#define IMPL_BEGIN(I, NAME)                             __intf_##I __intf_##I##_impl_##NAME = {
#define IMPL_MEMBER(I, T, NAME)                             .__intf_##I##_func_##NAME = &__impl_##I##_##T##_func_##NAME,
#define IMPL_END()                                      };

// Implementations' functions must be declare outside
// the implementation itself.
#define IMPL_FUNC_BEGIN(I, T, RTYPE, NAME, ...)         RTYPE __impl_##I##_##T##_func_##NAME(struct __intf_##I##_s *__intfself, void *__implself, __VA_ARGS__) {\
                                                            T *self = (T*)__implself;
#define IMPL_FUNC_END()                                 }

// INTF calls can be used in implementation methods.
// However, only IMPL calls can be used to call an
// implementation method, whether it is from inside
// or outside said implementations.
void* (*__impl_curr_fptr)();

#define IMPLFPTR(I, T, IMPL, FNAME)                     (__intf_##I##_get_func_##FNAME##(IMPL, #T))
#define IMPLFPTRSET(I, T, IMPL, FNAME)                  (__impl_curr_fptr = __intf_##I##_get_func_##FNAME(IMPL, #T))

#define IMPLCALL(I, T, FNAME, ...)                      (IMPLFPTRSET(I, T, __intfself, FNAME), (*__impl_curr_fptr)(__intfself, self, __VA_ARGS__))
#define IMPLCALLON(I, T, IMPL, FNAME, ...)              (IMPLFPTRSET(I, T, &__intf_##I##_impl_##T, FNAME), (*__impl_curr_fptr)(&__intf_##I##_impl_##T, IMPL, __VA_ARGS__))

static inline void __intf_nul(const char *t, const char *fname, const char *i);

#endif // STRUCTOBJ_HEADER


// Internal implementations.
static inline void __intf_nul(const char *t, const char *fname, const char *i) {
    fprintf(stderr,"Struct-Obj %s does not implement %s of interface %s, nor is there a default! Aborted.", t, fname, i);
    abort();
}

//---------------------- exiting <structobj.h>

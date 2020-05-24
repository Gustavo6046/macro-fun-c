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
#define INTERFACE_BEGIN(I)                              typedef struct _intf_##I##_s {
#define INTERFACE_MEMBER(I, RTYPE, NAME, ...)               RTYPE (*_intf_##I##_func_##NAME)(struct _intf_##I##_s *_intfself, void *_implself, __VA_ARGS__);
#define INTERFACE_END(I)                                } _intf_##I; extern _intf_##I _intf_##I##_default;

#define INTERFACE_POST_MEMBER(I, RTYPE, NAME, ...)      typedef RTYPE (*_intf_##I##_func_##NAME##_t)(_intf_##I *_intfself, void *_implself, __VA_ARGS__);\
                                                        static inline _intf_##I##_func_##NAME##_t _intf_##I##_get_func_##NAME(_intf_##I *_intfself, const char *_implname) {\
                                                            if (_intfself->_intf_##I##_func_##NAME)\
                                                                return _intfself->_intf_##I##_func_##NAME;\
                                                            else if (_intf_##I##_default._intf_##I##_func_##NAME)\
                                                                return _intf_##I##_default._intf_##I##_func_##NAME;\
                                                            else {\
                                                                _intf_nul(_implname, #NAME, #I);\
                                                                return _intf_##I##_default._intf_##I##_func_##NAME;\
                                                            }\
                                                        }

// Default member implementations; must be defined
// outside the main interface.
// Keep in mind you can't use the 'self' symbol in
// the interface, as there is no concrete 'self'
// known here. Use INTFCALL instead.
#define IDEFAULT_FUNC_DECLARE(I, RTYPE, NAME, ...)      RTYPE _intf_##I##_default_##NAME(struct _intf_##I##_s *_intfself, void *_implself, __VA_ARGS__);
#define IDEFAULT_FUNC_BEGIN(I, RTYPE, NAME, ...)        RTYPE _intf_##I##_default_##NAME(struct _intf_##I##_s *_intfself, void *_implself, __VA_ARGS__) {
#define IDEFAULT_FUNC_END()                             }

#define IDEFAULT_BEGIN(I)                               _intf_##I _intf_##I##_default = {
#define IDEFAULT_MEMBER(I, NAME)                            ._intf_##I##_func_##NAME = &_intf_##I##_default_##NAME,
#define IDEFAULT_NONE(I, NAME)                              ._intf_##I##_func_##NAME = NULL,
#define IDEFAULT_END()                                  };

// This precedes the arguments, when calling an
// interface function from another function of
// the interface itself. Can only be called from
// within an implementation of one of said 
// interface's members.
#define INTFCALL(I, FNAME, ...)                         (*_intfself->_intf_##I##_func_##FNAME)(_intfself, _implself, __VA_ARGS__)

// Each implementation of an interface's method must
// me defined with IMPL preprocessors.

#define IMPL_DECLARE(I, NAME)                           extern _intf_##I _intf_##I##_impl_##NAME;
#define IMPLOF(I, NAME)                                 &_intf_##I##_impl_##NAME

#define IMPL_BEGIN(I, NAME)                             _intf_##I _intf_##I##_impl_##NAME = {
#define IMPL_MEMBER(I, T, NAME)                             ._intf_##I##_func_##NAME = &_impl_##I##_##T##_func_##NAME,
#define IMPL_END()                                      };

// Implementations' functions must be declare outside
// the implementation itself.
#define IMPL_FUNC_BEGIN(I, T, RTYPE, NAME, ...)         RTYPE _impl_##I##_##T##_func_##NAME(struct _intf_##I##_s *_intfself, void *_implself, __VA_ARGS__) {\
                                                            T *self = (T*)_implself;
#define IMPL_FUNC_END()                                 }

// INTF calls can be used in implementation methods.
// However, only IMPL calls can be used to call an
// implementation method, whether it is from inside
// or outside said implementations.
void* (*_impl_curr_fptr)();

#define IMPLFPTR(I, T, IMPL, FNAME)                     (_intf_##I##_get_func_##FNAME##(IMPL, #T))
#define IMPLFPTRSET(I, T, IMPL, FNAME)                  (_impl_curr_fptr = _intf_##I##_get_func_##FNAME(IMPL, #T))

#define IMPLCALL(I, T, FNAME, ...)                      (IMPLFPTRSET(I, T, _intfself, FNAME), (*_impl_curr_fptr)(_intfself, self, __VA_ARGS__))
#define IMPLCALLON(I, T, IMPL, FNAME, ...)              (IMPLFPTRSET(I, T, &_intf_##I##_impl_##T, FNAME), (*_impl_curr_fptr)(&_intf_##I##_impl_##T, IMPL, __VA_ARGS__))

static inline void _intf_nul(const char *t, const char *fname, const char *i);

//---------------------- exiting  <structobj.h>

#endif // STRUCTOBJ_HEADER

//---------------------- entering <structobj.h> impl mode
// Internal implementations.
static inline void _intf_nul(const char *t, const char *fname, const char *i) {
    fprintf(stderr,"Struct-Obj %s does not implement %s of interface %s, nor is there a default! Aborted.", t, fname, i);
    abort();
}
//---------------------- exiting  <structobj.h> impl mode

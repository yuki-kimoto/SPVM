#ifndef SPVM_VERSION_H
#define SPVM_VERSION_H

#define SPVM_NATIVE_VERSION_NUMBER 0.990051

#define SPVM_NATIVE_CREATE_VERSION_STRING_STRINGIFY(x) #x

#define SPVM_NATIVE_CREATE_VERSION_STRING(x) SPVM_NATIVE_CREATE_VERSION_STRING_STRINGIFY(x)

#define SPVM_NATIVE_VERSION_STRING SPVM_NATIVE_CREATE_VERSION_STRING(SPVM_NATIVE_VERSION_NUMBER)

#endif

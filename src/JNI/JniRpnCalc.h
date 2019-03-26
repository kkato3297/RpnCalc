//
// Created by Kazuki_Kato on 2019/03/24.
//

#ifndef CALCULATOR_JNIRPNCALC_H
#define CALCULATOR_JNIRPNCALC_H

#include <jni.h>
#include <In2Rpn/In2Rpn.h>
#include <Rpn/Rpn.h>

#pragma region "ExceptionUtility"

inline void throwRuntimeException(JNIEnv* env, const char* what)
{
    try {
        jclass classj = env->FindClass("java/lang/RuntimeException");
        if (classj == nullptr)
            return;

        env->ThrowNew(classj, what);
        env->DeleteLocalRef(classj);
    } catch (exception &e) {
        throw e;
    }
}

template <typename Func>
inline void convertException(JNIEnv* env, Func func) noexcept
{
    try {
        func();
    } catch (std::exception& e) {
        throwRuntimeException(env, e.what());
    } catch (...) {
        throwRuntimeException(env, "Unindentified exception thrown (not derived from std::exception)");
    }
}

#pragma endregion

extern "C" JNIEXPORT jstring JNICALL
Java_com_kksystems_calculator_CalculatorLib_in2Rpn(
        JNIEnv* env,
        jobject /* this */,
        jstring expr) {
    jboolean isCopy;
    jstring result = nullptr;
    std::string string(env->GetStringUTFChars(expr, &isCopy));

    try {
        In2Rpn in2rpn(string);
        result = env->NewStringUTF(in2rpn.toRpn().c_str());
    } catch (exception &e) {
        throwRuntimeException(env, e.what());
    }

    return result;
}

extern "C" JNIEXPORT jdouble JNICALL
Java_com_kksystems_calculator_CalculatorLib_rpnExec(
        JNIEnv* env,
        jobject /* this */,
        jstring expr) {
    jboolean isCopy;
    jdouble result = 0;

    try {
        std::string string(env->GetStringUTFChars(expr, &isCopy));
        Rpn rpn;
        result = rpn.exec(string);
    } catch (exception &e) {
        throwRuntimeException(env, e.what());
    }

    return result;
}

#endif //CALCULATOR_JNIRPNCALC_H

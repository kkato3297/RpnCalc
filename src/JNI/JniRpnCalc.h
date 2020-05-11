//
// Created by Kazuki_Kato on 2019/03/24.
//

#ifndef CALCULATOR_JNIRPNCALC_H
#define CALCULATOR_JNIRPNCALC_H

#include <jni.h>
#include <In2Rpn/In2Rpn.h>
#include <Rpn/Rpn.h>

static Rpn rpn;

extern "C" JNIEXPORT jstring JNICALL
Java_com_kksystems_calculator_CalculatorLib_in2Rpn(
        JNIEnv* env,
        jobject /* this */,
        jstring expr);

extern "C" JNIEXPORT jdouble JNICALL
Java_com_kksystems_calculator_CalculatorLib_rpnExec(
        JNIEnv* env,
        jobject /* this */,
        jstring expr);

#endif // CALCULATOR_JNIRPNCALC_H

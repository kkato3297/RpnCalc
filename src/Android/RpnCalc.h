//
// Created by KK Systems on 2019/03/24.
//

#ifndef ANDROID_RPNCALC_H
#define ANDROID_RPNCALC_H

#include <string>
#include <exception>

std::string convIn2Rpn(const std::string &expr);

std::string rpnExec(const std::string &expr);

#endif // ANDROID_RPNCALC_H

//
// Created by KK Systems on 2019/03/24.
//

#ifndef IOS_RPNCALC_H
#define IOS_RPNCALC_H

#include <string>
#include <exception>

std::string convIn2Rpn(const std::string &expr);

std::string rpnExec(const std::string &expr);

std::exception &getException(void);

#endif // IOS_RPNCALC_H

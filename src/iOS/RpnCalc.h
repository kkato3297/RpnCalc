//
// Created by KK Systems on 2019/03/24.
//

#ifndef IOS_RPNCALC_H
#define IOS_RPNCALC_H

#include <string>
#include <exception>
#include <map>

void setMemory(const std::map<std::string, std::string>& memory);

void getMemory(std::map<std::string, std::string>& memory);

std::string convIn2Rpn(const std::string &expr);

std::string rpnExec(const std::string &expr);

std::exception &getException(void);

#endif // IOS_RPNCALC_H

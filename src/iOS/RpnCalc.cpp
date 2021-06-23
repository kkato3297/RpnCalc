//
// Created by KK Systems on 2021/03/16.
//

#include "RpnCalc.h"
#include <In2Rpn/In2Rpn.h>
#include <Rpn/Rpn.h>
#include <Exception.h>
#include <MemoryRepository.h>

static Rpn rpn;

const std::map<std::string, MemoryKey> s_keyTable = {
	{ "MEMORY_M", MemoryKey::MEMORY_M },
	{ "MEMORY_A", MemoryKey::MEMORY_A },
	{ "MEMORY_B", MemoryKey::MEMORY_B },
	{ "MEMORY_C", MemoryKey::MEMORY_C },
	{ "MEMORY_D", MemoryKey::MEMORY_D },
	{ "MEMORY_X", MemoryKey::MEMORY_X },
	{ "MEMORY_Y", MemoryKey::MEMORY_Y },
	{ "MEMORY_ANS", MemoryKey::MEMORY_ANS },
};

bool convertKey(const std::string& key, MemoryKey& result)
{
	const bool status = s_keyTable.find(key) != s_keyTable.end();

	if (status) {
		result = s_keyTable.at(key);
	}

	return status;
}

void setMemory(const std::map<std::string, std::string>& memory)
{
	MemoryRepository& memoryRepository = MemoryRepository::getInstance();

	for (auto&& item : memory) {
		MemoryKey key;

		if (convertKey(item.first, key)) {
			memoryRepository.set(key, item.second);
		}
	}
}

void getMemory(std::map<std::string, std::string>& memory)
{
	MemoryRepository& memoryRepository = MemoryRepository::getInstance();

	for (auto&& item : s_keyTable) {
		memory[item.first] = memoryRepository.get(item.second);
	}
}

std::string convIn2Rpn(const std::string &expr)
{
	std::string result = "";
	std::string string = expr;

	In2Rpn in2rpn(string);
	result = in2rpn.toRpn();

	return result;
}

std::string rpnExec(const std::string &expr)
{
	Number result = 0;
	std::string string = expr;

	mpfr_float::default_precision(100);

	result = rpn.exec(string);

	std::stringstream ss;
	ss << std::setprecision(mpfr_float::default_precision()) << result;

	return ss.str();
}

std::exception &getException(void)
{
	return *ExceptionCollection::getInstance().getException();
}

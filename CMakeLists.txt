# CMakeList.txt : 最上位の CMake プロジェクト ファイル。グローバル構成を行います
# また、サブプロジェクトをここに含めます。
#
cmake_minimum_required (VERSION 3.10.2)

option(TARGET_PLATFORM	"Target platform")
option(TARGET_FORMAT	"Target format")

# デフォルト値の設定
if(${TARGET_PLATFORM} STREQUAL "PLATFORM_WINDOWS")
elseif(${TARGET_PLATFORM} STREQUAL "PLATFORM_ANDROID")
elseif(${TARGET_PLATFORM} STREQUAL "PLATFORM_LINUX")
elseif(${TARGET_PLATFORM} STREQUAL "PLATFORM_IOS")
else()
	set(TARGET_PLATFORM "PLATFORM_WINDOWS")
endif()

# デフォルト値の設定
if(${TARGET_FORMAT} STREQUAL "EXECUTABLE")
elseif(${TARGET_FORMAT} STREQUAL "SHARED_LIBRARY")
elseif(${TARGET_FORMAT} STREQUAL "STATIC_LIBRARY")
elseif(${TARGET_FORMAT} STREQUAL "UNITTEST")
else()
	if(${TARGET_PLATFORM} STREQUAL "PLATFORM_WINDOWS")
		set(TARGET_FORMAT "EXECUTABLE")
	elseif(${TARGET_PLATFORM} STREQUAL "PLATFORM_ANDROID")
		set(TARGET_FORMAT "SHARED_LIBRARY")
	endif()
endif()

set(CMAKE_CXX_STANDARD 17)
project ("RpnCalc" CXX)

message ("========================================")
message ("TARGET_PLATFORM: \"${TARGET_PLATFORM}\"")
message ("TARGET_FORMAT  : \"${TARGET_FORMAT}\"")
message ("========================================")

# サブプロジェクトを含めます。
if(${TARGET_FORMAT} STREQUAL "UNITTEST")
	add_subdirectory("test")
else()
	add_subdirectory("src")
endif()

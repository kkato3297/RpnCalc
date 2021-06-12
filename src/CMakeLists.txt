# CMakeList.txt : RpnCalc の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.10.2)

include_directories("include")
add_definitions("-DTARGET_PLATFORM=${TARGET_PLATFORM}")
add_definitions("-DTARGET_FORMAT=${TARGET_FORMAT}")

# ソースをこのプロジェクトの実行可能ファイルに追加します。
if(${TARGET_FORMAT} STREQUAL "EXECUTABLE")
	add_executable (RpnCalc "RpnCalc.cpp" "RpnCalc.h")
elseif(${TARGET_FORMAT} STREQUAL "SHARED_LIBRARY")
	add_library (RpnCalc SHARED "RpnCalcLib.cpp" "RpnCalc.h")
	set_target_properties(RpnCalc PROPERTIES OUTPUT_NAME "RpnCalcLib")
	if(${TARGET_PLATFORM} STREQUAL "PLATFORM_IOS")
		set_target_properties(RpnCalc PROPERTIES
			FRAMEWORK TRUE
			FRAMEWORK_VERSION A
			MACOSX_FRAMEWORK_IDENTIFIER net.kk_systems.rpnCalc
			PUBLIC_HEADER "iOS/RpnCalc.h"
			XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
			XCODE_ATTRIBUTE_INSTALL_PATH "@rpath"
		)
	endif()
elseif(${TARGET_FORMAT} STREQUAL "STATIC_LIBRARY")
	add_library (RpnCalc "RpnCalcLib.cpp" "RpnCalc.h")
endif()
target_compile_definitions(RpnCalc PUBLIC _UNICODE UNICODE)

# サブプロジェクトを含めます。
add_subdirectory ("Common")
add_subdirectory ("Rpn")
add_subdirectory ("In2Rpn")
if(${TARGET_PLATFORM} STREQUAL "PLATFORM_ANDROID")
	add_subdirectory ("Android")
elseif(${TARGET_PLATFORM} STREQUAL "PLATFORM_IOS")
	add_subdirectory ("iOS")
endif()

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。

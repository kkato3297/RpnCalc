# CMakeList.txt : RpnCalc の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.4.1)

include_directories("include")
add_definitions("-DTARGET_PLATFORM=${TARGET_PLATFORM}")
add_definitions("-DTARGET_FORMAT=${TARGET_FORMAT}")

# ソースをこのプロジェクトの実行可能ファイルに追加します。
if(${TARGET_FORMAT} STREQUAL "EXECUTABLE")
	add_executable (RpnCalc "RpnCalc.cpp" "RpnCalc.h")
elseif(${TARGET_FORMAT} STREQUAL "SHARED_LIBRARY")
	add_library (RpnCalc SHARED "RpnCalc.cpp" "RpnCalc.h")
elseif(${TARGET_FORMAT} STREQUAL "STATIC_LIBRARY")
	add_library (RpnCalc "RpnCalc.cpp" "RpnCalc.h")
endif()
target_compile_definitions(RpnCalc PUBLIC _UNICODE UNICODE)

# サブプロジェクトを含めます。
add_subdirectory ("Common")
add_subdirectory ("Rpn")
add_subdirectory ("In2Rpn")
if(${TARGET_PLATFORM} STREQUAL "ANDROID")
	add_subdirectory ("JNI")
endif()

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。

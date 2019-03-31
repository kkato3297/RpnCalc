# CMakeList.txt : RpnCalc の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.8)

include_directories("include" "../src/include")
if(${TARGET_PLATFORM} STREQUAL "PLATFORM_LINUX")
	add_definitions("-fprofile-arcs")
	add_definitions("-ftest-coverage")
	set(CMAKE_EXE_LINKER_FLAGS "--coverage")
endif()

# ソースをこのプロジェクトの実行可能ファイルに追加します。
add_executable (RpnCalcTest
	"RpnCalcTest.cpp"
	"In2RpnTest.cpp"
	"${CMAKE_SOURCE_DIR}/src/Common/Exception.cpp"
	"${CMAKE_SOURCE_DIR}/src/In2Rpn/In2Rpn.cpp")

if(${TARGET_PLATFORM} STREQUAL "PLATFORM_WINDOWS")
	target_link_libraries(RpnCalcTest "${CMAKE_SOURCE_DIR}/test/lib/cppunitd.lib")
elseif(${TARGET_PLATFORM} STREQUAL "PLATFORM_LINUX")
	target_link_libraries(RpnCalcTest cppunit)
endif()
target_compile_definitions(RpnCalcTest PUBLIC _UNICODE UNICODE)

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。

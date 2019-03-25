# CMakeList.txt : RpnCalc の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.8)

include_directories("include" "../src/include")

# ソースをこのプロジェクトの実行可能ファイルに追加します。
add_executable (RpnCalcTest "RpnCalcTest.cpp" "In2RpnTest.cpp")
target_sources (RpnCalcTest
	PUBLIC
		"${CMAKE_SOURCE_DIR}/src/Common/Stack.cpp"
		"${CMAKE_SOURCE_DIR}/src/In2Rpn/In2Rpn.cpp")

target_link_libraries(RpnCalcTest "${CMAKE_SOURCE_DIR}/test/lib/cppunitd.lib")
target_compile_definitions(RpnCalcTest PUBLIC _UNICODE UNICODE)

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。

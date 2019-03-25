# CMakeList.txt : RpnCalc の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.8)

include_directories("include")

# ソースをこのプロジェクトの実行可能ファイルに追加します。
add_executable (RpnCalc "RpnCalc.cpp" "RpnCalc.h")
target_compile_definitions(RpnCalc PUBLIC _UNICODE UNICODE)

# サブプロジェクトを含めます。
add_subdirectory ("Common")
add_subdirectory ("Rpn")
add_subdirectory ("In2Rpn")

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。

# CMakeList.txt : RpnCalc の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.4.1)

# ソースをこのプロジェクトの実行可能ファイルに追加します。
target_sources (RpnCalc
	PUBLIC
		"Common/Stack.cpp")

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。

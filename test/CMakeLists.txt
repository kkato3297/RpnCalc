# CMakeList.txt : RpnCalc の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.8)

include_directories("include" "../src/include")
if(${TARGET_PLATFORM} STREQUAL "PLATFORM_LINUX")
	add_definitions("-fprofile-arcs")
	add_definitions("-ftest-coverage")
	set(CMAKE_EXE_LINKER_FLAGS "--coverage")
elseif(${TARGET_PLATFORM} STREQUAL "PLATFORM_MACOS")
	include_directories("/usr/local/include")
	link_directories("/usr/local/opt/cppunit/lib")
	add_definitions("-fprofile-arcs")
	add_definitions("-ftest-coverage")
	set(CMAKE_EXE_LINKER_FLAGS "--coverage")
endif()

# ソースをこのプロジェクトの実行可能ファイルに追加します。
add_executable (RpnCalcTest
	"RpnCalcTest.cpp"
	"In2RpnTest.cpp"
	"${CMAKE_SOURCE_DIR}/src/Common/Exception.cpp"
	"${CMAKE_SOURCE_DIR}/src/Common/Utility.cpp"
	"${CMAKE_SOURCE_DIR}/src/In2Rpn/In2Rpn.cpp"
	"${CMAKE_SOURCE_DIR}/src/In2Rpn/Parser.cpp"
)

if(${TARGET_PLATFORM} STREQUAL "PLATFORM_WINDOWS")
	target_link_libraries(RpnCalcTest "${CMAKE_SOURCE_DIR}/test/lib/cppunitd.lib")
elseif(${TARGET_PLATFORM} STREQUAL "PLATFORM_LINUX")
	target_link_libraries(RpnCalcTest cppunit)
elseif(${TARGET_PLATFORM} STREQUAL "PLATFORM_MACOS")
	list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/src/.cmake)
	set(Boost_DIR "$ENV{HOME}/.local/boost/boost_1_76_0/lib/cmake/Boost-1.76.0")

	find_package(Boost REQUIRED)
	find_package(GMP REQUIRED)
	find_package(MPFR REQUIRED)

	target_include_directories(RpnCalcTest
		PRIVATE ${Boost_INCLUDE_DIRS}
		PRIVATE ${GMP_INCLUDE_DIR}
	)
	target_link_libraries(RpnCalcTest GMP::GMP MPFR::MPFR)
	target_link_libraries(RpnCalcTest cppunit)
endif()
target_compile_definitions(RpnCalcTest PUBLIC _UNICODE UNICODE)

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。

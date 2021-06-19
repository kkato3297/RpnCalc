# CMakeList.txt : RpnCalc の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.10.2)

include_directories("include")
add_definitions("-DTARGET_PLATFORM=${TARGET_PLATFORM}")
add_definitions("-DTARGET_FORMAT=${TARGET_FORMAT}")

# ソースをこのプロジェクトの実行可能ファイルに追加します。
if(${TARGET_FORMAT} STREQUAL "EXECUTABLE")
	list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/src/.cmake)

	set(Boost_DIR "$ENV{HOME}/.local/boost/boost_1_76_0/lib/cmake/Boost-1.76.0")

	find_package(Boost REQUIRED)
	find_package(GMP REQUIRED)
	find_package(MPFR REQUIRED)

	add_executable (RpnCalc "RpnCalc.cpp" "RpnCalc.h")
	target_include_directories(RpnCalc
		PRIVATE ${Boost_INCLUDE_DIRS}
		PRIVATE ${GMP_INCLUDE_DIR}
	)
	target_link_libraries(RpnCalc GMP::GMP MPFR::MPFR)
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
			XCODE_ATTRIBUTE_EXCLUDED_ARCHS[sdk=iphonesimulator*] "arm64"
		)
		set_target_properties(RpnCalc PROPERTIES
			XCODE_ATTRIBUTE_ENABLE_BITCODE "NO"
		)
		target_include_directories(RpnCalc
			PRIVATE ${CMAKE_SOURCE_DIR}/lib/dist/boost/${SDK_NAME}/include
			PRIVATE ${CMAKE_SOURCE_DIR}/lib/dist/gmp/${SDK_NAME}/include
			PRIVATE ${CMAKE_SOURCE_DIR}/lib/dist/mpfr/${SDK_NAME}/include
		)
		add_library(GMP::GMP STATIC IMPORTED)
		add_library(MPFR::MPFR STATIC IMPORTED)
		set_target_properties(GMP::GMP
			PROPERTIES
				IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/dist/gmp/${SDK_NAME}/lib/libgmp.a
		)
		set_target_properties(MPFR::MPFR
			PROPERTIES
				IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/dist/mpfr/${SDK_NAME}/lib/libmpfr.a
		)
		target_link_libraries(RpnCalc GMP::GMP MPFR::MPFR)
	endif()
elseif(${TARGET_FORMAT} STREQUAL "STATIC_LIBRARY")
	add_library (RpnCalc "RpnCalcLib.cpp" "RpnCalc.h")
	set_target_properties(RpnCalc PROPERTIES OUTPUT_NAME "RpnCalcLib")
	if(${TARGET_PLATFORM} STREQUAL "PLATFORM_ANDROID")
		target_include_directories(RpnCalc
			PRIVATE ${CMAKE_SOURCE_DIR}/lib/dist/boost/iphoneos/include
			PRIVATE ${CMAKE_SOURCE_DIR}/lib/dist/gmp/android-${ANDROID_ABI}/include
			PRIVATE ${CMAKE_SOURCE_DIR}/lib/dist/mpfr/android-${ANDROID_ABI}/include
		)
	endif()
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

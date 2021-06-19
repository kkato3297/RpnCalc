#!/bin/bash

function exec_ios_b2() {
    local CXX_ARCH=$1
    local B2_ARCH=$2
    local SDK_PATH=$3
    local DEVICE_NAME=$4
    local BUILD_MODE=$5

    ./b2 \
        --build-dir=./build/ios/${DEVICE_NAME} \
        --stagedir=./stage/ios/${DEVICE_NAME} \
        --prefix=./stage/include \
        toolset=clang cflags="${CXX_ARCH} -fvisibility=default -miphoneos-version-min=13.0 -isysroot \"${SDK_PATH}\"" \
        architecture=${B2_ARCH} \
        target-os=iphone \
        link=static \
        threading=multi \
        define=_LITTLE_ENDIAN \
        include="${SDK_PATH}/usr/include/" \
        ${BUILD_MODE}
}

function build_ios_boost() {
    pushd $(pwd)

    cd lib/source/boost

    local SDK_DEVICE_PATH=$(xcrun --sdk iphoneos --show-sdk-path)
    local SDK_SIMULATOR_PATH=$(xcrun --sdk iphonesimulator --show-sdk-path)

    # for iphoneos
    if [ ! -e stage/ios/iphoneos ]; then
        exec_ios_b2 "-arch arm64" "arm" "${SDK_DEVICE_PATH}" "iphoneos" "stage install"
    fi
    # for iphonesimulator
    if [ ! -e stage/ios/iphonesimulator ]; then
        exec_ios_b2 "-arch x86_64 -arch arm64" "arm" "${SDK_SIMULATOR_PATH}" "iphonesimulator" "stage"
    fi

    popd

    pushd $(pwd)

    if [ ! -e lib/dist/boost ]; then
        mkdir -p lib/dist/boost
    fi

    if [ ! -e lib/dist/boost/iphoneos ]; then
        mkdir -p lib/dist/boost/iphoneos
    fi

    if [ ! -e lib/dist/boost/iphonesimulator ]; then
        mkdir -p lib/dist/boost/iphonesimulator
    fi

    if [ ! -e lib/dist/boost/iphoneos/lib ]; then
        cp -R lib/source/boost/stage/ios/iphoneos/lib lib/dist/boost/iphoneos
    fi

    if [ ! -e lib/dist/boost/iphonesimulator/lib ]; then
        cp -R lib/source/boost/stage/ios/iphonesimulator/lib lib/dist/boost/iphonesimulator
    fi

    if [ ! -e lib/dist/boost/iphoneos/include ]; then
        cp -R lib/source/boost/stage/include/include lib/dist/boost/iphoneos
    fi

    if [ ! -e lib/dist/boost/iphonesimulator/include ]; then
        cp -R lib/source/boost/stage/include/include lib/dist/boost/iphonesimulator
    fi

    popd
}

function realpath() {
    [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

function build_ios_gmp() {
    pushd $(pwd)

    cd lib/source/gmp

    local SDK_DEVICE_PATH=$(xcrun --sdk iphoneos --show-sdk-path)
    local SDK_SIMULATOR_PATH=$(xcrun --sdk iphonesimulator --show-sdk-path)
    local CLANG=$(xcrun --sdk iphoneos --find clang)
    local BITCODE_FLAGS=" -disable-llvm-optzns -O3"

    # for iphoneos
    make clean
    make distclean

    local PREFIX=$(realpath "../../dist/gmp/iphoneos")
    local EXTRAS="-arch arm64 -miphoneos-version-min=13.0 -no-integrated-as -target aarch64-apple-darwin"
    local CFLAGS=" ${BITCODE_FLAGS} -isysroot ${SDK_DEVICE_PATH} -Wno-error -Wno-implicit-function-declaration ${EXTRAS} -fvisibility=hidden"
    if [ ! -e "${PREFIX}" ]; then
        mkdir -p "${PREFIX}"

        ./configure \
            --prefix="${PREFIX}" \
            CC="${CLANG} ${CFLAGS}" \
            LDFLAGS="${CFLAGS}" \
            CPP="${CLANG} -E" \
            CPPFLAGS="${CFLAGS}" \
            --host=x86_64-apple-darwin \
            --disable-assembly --enable-static --disable-shared --enable-cxx
        
        make
        make install
    fi

    # for iphonesimulator
    make clean
    make distclean

    local PREFIX=$(realpath "../../dist/gmp/iphonesimulator-arm64")
    local EXTRAS="-arch arm64 -miphoneos-version-min=13.0 -no-integrated-as -target aarch64-apple-darwin"
    local CFLAGS=" ${BITCODE_FLAGS} -isysroot ${SDK_SIMULATOR_PATH} -Wno-error -Wno-implicit-function-declaration ${EXTRAS} -fvisibility=hidden"
    if [[ ! -e "../../dist/gmp/iphonesimulator" && ! -e "${PREFIX}" ]]; then
        mkdir -p "${PREFIX}"

        ./configure \
            --prefix="${PREFIX}" \
            CC="${CLANG} ${CFLAGS}" \
            LDFLAGS="${CFLAGS}" \
            CPP="${CLANG} -E" \
            CPPFLAGS="${CFLAGS}" \
            --host=x86_64-apple-darwin \
            --disable-assembly --enable-static --disable-shared --enable-cxx
        
        make
        make install
    fi

    make clean
    make distclean

    local PREFIX=$(realpath "../../dist/gmp/iphonesimulator-x86_64")
    local EXTRAS="-arch x86_64 -miphoneos-version-min=13.0 -no-integrated-as -target x86_64-apple-darwin"
    local CFLAGS=" ${BITCODE_FLAGS} -isysroot ${SDK_SIMULATOR_PATH} -Wno-error -Wno-implicit-function-declaration ${EXTRAS} -fvisibility=hidden"
    if [[ ! -e "../../dist/gmp/iphonesimulator" && ! -e "${PREFIX}" ]]; then
        mkdir -p "${PREFIX}"

        ./configure \
            --prefix="${PREFIX}" \
            CC="${CLANG} ${CFLAGS}" \
            LDFLAGS="${CFLAGS}" \
            CPP="${CLANG} -E" \
            CPPFLAGS="${CFLAGS}" \
            --host=x86_64-apple-darwin \
            --disable-assembly --enable-static --disable-shared --enable-cxx
        
        make
        make install
    fi

    if [ ! -e "../../dist/gmp/iphonesimulator" ]; then
        local SIMULATOR_PATH="../../dist/gmp/iphonesimulator"
        mkdir -p ${SIMULATOR_PATH}/lib ${SIMULATOR_PATH}/include
        cp -R ${SIMULATOR_PATH}-arm64/include ${SIMULATOR_PATH}/
        lipo -create -output ${SIMULATOR_PATH}/lib/libgmp.a \
            -arch arm64 ${SIMULATOR_PATH}-arm64/lib/libgmp.a \
            -arch x86_64 ${SIMULATOR_PATH}-x86_64/lib/libgmp.a
        lipo -create -output ${SIMULATOR_PATH}/lib/libgmpxx.a \
            -arch arm64 ${SIMULATOR_PATH}-arm64/lib/libgmpxx.a \
            -arch x86_64 ${SIMULATOR_PATH}-x86_64/lib/libgmpxx.a
    fi

    popd
}

function build_ios_mpfr() {
    pushd $(pwd)

    cd lib/source/mpfr

    local SDK_DEVICE_PATH=$(xcrun --sdk iphoneos --show-sdk-path)
    local SDK_SIMULATOR_PATH=$(xcrun --sdk iphonesimulator --show-sdk-path)
    local CLANG=$(xcrun --sdk iphoneos --find clang)
    local BITCODE_FLAGS=" -disable-llvm-optzns -O3"

    # for iphoneos
    make clean
    make distclean

    local PREFIX=$(realpath "../../dist/mpfr/iphoneos")
    local EXTRAS="-arch arm64 -miphoneos-version-min=13.0 -no-integrated-as -target aarch64-apple-darwin"
    local CFLAGS=" ${BITCODE_FLAGS} -isysroot ${SDK_DEVICE_PATH} -Wno-error -Wno-implicit-function-declaration ${EXTRAS} -fvisibility=hidden"
    local GMP_LIB_PATH="../../dist/gmp/iphoneos"
    local GMP_PATH="../../dist/gmp/iphoneos"
    if [ ! -e "${PREFIX}" ]; then
        mkdir -p "${PREFIX}"

        ./configure \
            --prefix="${PREFIX}" \
            CC="${CLANG} ${CFLAGS}" \
            LDFLAGS="${CFLAGS}" \
            CPP="${CLANG} -E" \
            --with-gmp=${GMP_LIB_PATH} \
            --host=x86_64-apple-darwin \
            --disable-assembly --enable-static --disable-shared --enable-cxx
        
        make
        make install
    fi

    # for iphonesimulator
    make clean
    make distclean

    local PREFIX=$(realpath "../../dist/mpfr/iphonesimulator-arm64")
    local EXTRAS="-arch arm64 -miphoneos-version-min=13.0 -no-integrated-as -target aarch64-apple-darwin"
    local CFLAGS=" ${BITCODE_FLAGS} -isysroot ${SDK_SIMULATOR_PATH} -Wno-error -Wno-implicit-function-declaration ${EXTRAS} -fvisibility=hidden"
    local GMP_LIB_PATH="../../dist/gmp/iphonesimulator"
    local GMP_PATH="../../dist/gmp/iphonesimulator"
    if [[ ! -e "../../dist/mpfr/iphonesimulator" && ! -e "${PREFIX}" ]]; then
        mkdir -p "${PREFIX}"

        ./configure \
            --prefix="${PREFIX}" \
            CC="${CLANG} ${CFLAGS}" \
            LDFLAGS="${CFLAGS}" \
            CPP="${CLANG} -E" \
            --with-gmp=${GMP_LIB_PATH} \
            --host=x86_64-apple-darwin \
            --disable-assembly --enable-static --disable-shared --enable-cxx
        
        make
        make install
    fi

    make clean
    make distclean

    local PREFIX=$(realpath "../../dist/mpfr/iphonesimulator-x86_64")
    local EXTRAS="-arch x86_64 -miphoneos-version-min=13.0 -no-integrated-as -target x86_64-apple-darwin"
    local CFLAGS=" ${BITCODE_FLAGS} -isysroot ${SDK_SIMULATOR_PATH} -Wno-error -Wno-implicit-function-declaration ${EXTRAS} -fvisibility=hidden"
    local GMP_LIB_PATH="../../dist/gmp/iphonesimulator"
    local GMP_PATH="../../dist/gmp/iphonesimulator"
    if [[ ! -e "../../dist/mpfr/iphonesimulator" && ! -e "${PREFIX}" ]]; then
        mkdir -p "${PREFIX}"

        ./configure \
            --prefix="${PREFIX}" \
            CC="${CLANG} ${CFLAGS}" \
            LDFLAGS="${CFLAGS}" \
            CPP="${CLANG} -E" \
            --with-gmp=${GMP_LIB_PATH} \
            --host=x86_64-apple-darwin \
            --disable-assembly --enable-static --disable-shared --enable-cxx
        
        make
        make install
    fi

    if [ ! -e "../../dist/mpfr/iphonesimulator" ]; then
        local SIMULATOR_PATH="../../dist/mpfr/iphonesimulator"
        mkdir -p ${SIMULATOR_PATH}/lib ${SIMULATOR_PATH}/include
        cp -R ${SIMULATOR_PATH}-arm64/include ${SIMULATOR_PATH}/
        lipo -create -output ${SIMULATOR_PATH}/lib/libmpfr.a \
            -arch arm64 ${SIMULATOR_PATH}-arm64/lib/libmpfr.a \
            -arch x86_64 ${SIMULATOR_PATH}-x86_64/lib/libmpfr.a
    fi

    popd
}

function rpncalc_ios_build() {
    result=0

    build_ios_boost
    build_ios_gmp
    build_ios_mpfr
}

function rpncalc_ios_clean() {
    pushd $(pwd)

    cd lib/dist

    rm -rf ./*

    popd
}

#!/bin/bash

ANDROID_TARGET_ABI="armeabi-v7a arm64-v8a x86 x86_64"

function exec_android_b2() {
    local ABI_NAME=$1
    local SDK_PATH=$2
    local BUILD_MODE=$3

    local TOOLCHAIN=llvm
    local PlatformOS=darwin
    local TOOLPATH=${SDK_PATH}/toolchains/${TOOLCHAIN}/prebuilt/${PlatformOS}-x86_64

    case $ABI_NAME in
        armeabi-v7a)
            B2_ARCH="arm"
            local CXX_ARCH="-march=armv7-a -m32 -mfloat-abi=softfp -mfpu=vfpv3-d16 -mthumb"
            ABI_PREFIX="arm-linux-androideabi"
            ADDRESS_MODEL=32
            B2_ABI=aapcs
            ;;
        arm64-v8a)
            B2_ARCH="arm"
            local CXX_ARCH="-march=armv8-a -m64"
            ABI_PREFIX="aarch64-linux-android"
            ADDRESS_MODEL=64
            B2_ABI=aapcs
            ;;
        x86_64)
            B2_ARCH="x86"
            local CXX_ARCH="-march=x86-64 -m64 -msse4.2 -mpopcnt -mtune=intel"
            ABI_PREFIX="x86_64-linux-android"
            ADDRESS_MODEL=64
            B2_ABI=sysv
            ;;
        x86)
            B2_ARCH="x86"
            local CXX_ARCH="-march=i686 -m32 -mssse3 -mfpmath=sse -mtune=intel"
            ABI_PREFIX="i686-linux-android"
            ADDRESS_MODEL=32
            B2_ABI=sysv
            ;;
    esac

    ./b2 \
        -q \
        -d+2 \
        --ignore-site-config \
        --build-dir=./build/android/${ABI_NAME} \
        --stagedir=./stage/android/${ABI_NAME} \
        --prefix=../../dist/boost/android-${ABI_NAME} \
        --layout=system \
        --without-mpi \
        --without-graph_parallel \
        --without-locale \
        --without-regex \
        --without-filesystem \
        --without-log \
        --without-stacktrace \
        --without-nowide \
        --without-iostreams \
        toolset=clang-android \
        address-model=${ADDRESS_MODEL} \
        architecture=${B2_ARCH} \
        abi=${B2_ABI} \
        target-os=android \
        link=static \
        runtime-link=static \
        threading=multi \
        variant=release \
        binary-format=elf \
        ${BUILD_MODE}
}

function get_android_target() {
    local ARCH=$1
    local SDKVERSION=${MINSDKVERSION}

    case $ARCH in
        arm64-v8a|x86_64)
            if [ $SDKVERSION -lt 21 ]; then
                SDKVERSION=21
            fi
            ;;
    esac

    local TARGET
    case $ARCH in
        armeabi-v7a)
            TARGET="armv7-none-linux-androideabi${SDKVERSION}"
            ;;
        arm64-v8a)
            TARGET="aarch64-none-linux-android${SDKVERSION}"
            ;;
        x86_64)
            TARGET="x86_64-none-linux-android${SDKVERSION}"
            ;;
        x86)
            TARGET="i686-none-linux-android${SDKVERSION}"
            ;;
    esac

    echo "${TARGET}"
}

function get_android_compiler_prefix() {
    local ARCH=$1

    local ABI_PREFIX
    case $ARCH in
        armeabi-v7a)
            ABI_PREFIX="arm-linux-androideabi"
            ;;
        arm64-v8a)
            ABI_PREFIX="aarch64-linux-android"
            ;;
        x86_64)
            ABI_PREFIX="x86_64-linux-android"
            ;;
        x86)
            ABI_PREFIX="i686-linux-android"
            ;;
    esac

    echo "${ABI_PREFIX}"
}

function build_android_boost() {
    pushd $(pwd)

    cd lib/source/boost

    local LATEST_NDK_VERSION=$(ls $HOME/Library/Android/sdk/ndk/ | sort | tail -n 1)
    local NDK=$HOME/Library/Android/sdk/ndk/$LATEST_NDK_VERSION
    local MINSDKVERSION=16
    local TARGETSDKVERSION=30

    local TOOLCHAIN=llvm
    local PlatformOS=darwin
    local TOOLPATH=${NDK}/toolchains/${TOOLCHAIN}/prebuilt/${PlatformOS}-x86_64

    cd ./build
    rm -r ./android
    cd ..

    local user_config=tools/build/src/user-config.jam
    for ARCH in $(echo $ANDROID_TARGET_ABI); do
        rm -f $user_config

        case $ARCH in
            armeabi-v7a)
                ARCH_NAME="arm"
                ABI_PREFIX="arm-linux-androideabi"
                TARGET="armv7-none-linux-androideabi${MINSDKVERSION}"
                ADDRESS_MODEL=32
                ;;
            arm64-v8a)
                ARCH_NAME="arm"
                ABI_PREFIX="aarch64-linux-android"
                TARGET="aarch64-none-linux-android${TARGETSDKVERSION}"
                ADDRESS_MODEL=64
                ;;
            x86_64)
                ARCH_NAME="x86"
                ABI_PREFIX="x86_64-linux-android"
                TARGET="x86_64-none-linux-android${TARGETSDKVERSION}"
                ADDRESS_MODEL=64
                ;;
            x86)
                ARCH_NAME="x86"
                ABI_PREFIX="i686-linux-android"
                TARGET="i686-none-linux-android${MINSDKVERSION}"
                ADDRESS_MODEL=32
                ;;
        esac

        cat <<EOF > $user_config
import os ;

using clang : android
:
"${TOOLPATH}/bin/clang++"
:
<archiver>${TOOLPATH}/bin/${ABI_PREFIX}-ar
<ranlib>${TOOLPATH}/bin/${ABI_PREFIX}-ranlib
<compileflags>--target=${TARGET}
<compileflags>--gcc-toolchain=${TOOLPATH}
<compileflags>--sysroot=${TOOLPATH}/sysroot
<compileflags>-fexceptions
<compileflags>-frtti
<compileflags>-ffunction-sections
<compileflags>-funwind-tables
<compileflags>-fstack-protector-strong
<compileflags>-Wno-invalid-command-line-argument
<compileflags>-Wno-unused-command-line-argument
<compileflags>-no-canonical-prefixes
<compileflags>-I${TOOLPATH}/sysroot/usr/include/${ABI_PREFIX}
<compileflags>-I${TOOLPATH}/sysroot/usr/include
<compileflags>-I${NDK}/sources/android/support/include
<compileflags>-DANDROID
<compileflags>-D__ANDROID__
<compileflags>-Wa,--noexecstack
<compileflags>-Wformat
<compileflags>-Werror=format-security
<compileflags>-DNDEBUG
<compileflags>-O2
<compileflags>-fPIC
<compileflags>-fno-integrated-as
<compileflags>-isystem
<compileflags>${TOOLPATH}/sysroot/usr/include/${ABI_PREFIX}
<compileflags>-std=c++17
<architecture>${ARCH_NAME}
<address-model>${ADDRESS_MODEL}
<linkflags>--target=${TARGET}
<linkflags>-L${TOOLPATH}/sysroot/usr/lib/${ABI_PREFIX}/${TARGETSDKVERSION}
<library-path>${NDK}/sources/cxx-stl/llvm-libc++/libs/${ARCH}
;
EOF

# <compileflags>--target=${TARGET}
# <compileflags>--gcc-toolchain=${TOOLPATH}
# <compileflags>--sysroot=${TOOLPATH}/sysroot
# <compileflags>-fexceptions
# <compileflags>-frtti
# <compileflags>-ffunction-sections
# <compileflags>-funwind-tables
# <compileflags>-fstack-protector-strong
# <compileflags>-Wno-invalid-command-line-argument
# <compileflags>-Wno-unused-command-line-argument
# <compileflags>-no-canonical-prefixes
# <compileflags>-I${NDK}/sources/cxx-stl/llvm-libc++/include
# <compileflags>-I${NDK}/sources/cxx-stl/llvm-libc++abi/include
# <compileflags>-I${NDK}/sources/android/support/include
# <compileflags>-I${TOOLPATH}/sysroot/usr/include/${ABI_PREFIX}
# <compileflags>-I${TOOLPATH}/sysroot/usr/include
# <compileflags>-DANDROID
# <compileflags>-D__ANDROID__
# <compileflags>-Wa,--noexecstack
# <compileflags>-Wformat
# <compileflags>-Werror=format-security
# <compileflags>-DNDEBUG
# <compileflags>-O2
# <compileflags>-fPIC
# <compileflags>-fno-integrated-as
# <compileflags>-isystem
# <compileflags>${TOOLPATH}/sysroot/usr/include/${ABI_PREFIX}

        # ./bootstrap.sh

        # for android
        if [ ! -e stage/android/iphoneos ]; then
            exec_android_b2 "${ARCH}" "${NDK}" "--clean stage install"
        fi
    done

    popd

    # pushd $(pwd)

    # if [ ! -e lib/dist/boost ]; then
    #     mkdir -p lib/dist/boost
    # fi

    # for ARCH in $(echo $ANDROID_TARGET_ABI); do
    #     if [ ! -e lib/dist/boost/android-${ARCH} ]; then
    #         mkdir -p lib/dist/boost/android-${ARCH}
    #     fi

    #     if [ ! -e lib/dist/boost/android-${ARCH}/lib ]; then
    #         cp -R lib/source/boost/stage/android/${ARCH}/lib lib/dist/boost/android-${ARCH}
    #     fi

    #     if [ ! -e lib/dist/boost/android-${ARCH}/include ]; then
    #         cp -R lib/source/boost/stage/android/${ARCH}/include lib/dist/boost/android-${ARCH}
    #     fi
    # done

    # popd
}

function realpath() {
    [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

function build_android_gmp() {
    pushd $(pwd)

    cd lib/source/gmp

    local LATEST_NDK_VERSION=$(ls $HOME/Library/Android/sdk/ndk/ | sort | tail -n 1)
    local NDK=$HOME/Library/Android/sdk/ndk/$LATEST_NDK_VERSION
    local MINSDKVERSION=16
    local TARGETSDKVERSION=30

    local TOOLCHAIN=llvm
    local PlatformOS=darwin
    local TOOLPATH=${NDK}/toolchains/${TOOLCHAIN}/prebuilt/${PlatformOS}-x86_64

    # for iphoneos
    for ARCH in $(echo $ANDROID_TARGET_ABI); do
        if [ ! -e "./build/android/${ARCH}" ]; then
            mkdir -p "build/android/${ARCH}"
        fi

        pushd $(pwd)

        cd "build/android/${ARCH}"

        make clean
        make distclean

        local PREFIX=$(realpath "../../../../../dist/gmp/android-${ARCH}")
        local TARGET=$(get_android_target "${ARCH}")
        local EXTRAS="--target=${TARGET}"
        local CFLAGS="${EXTRAS} --gcc-toolchain=${TOOLPATH} --sysroot=${TOOLPATH}/sysroot -fPIC"

        if [ ! -e "${PREFIX}" ]; then
            mkdir -p "${PREFIX}"

            local AR=${TOOLPATH}/bin/$(get_android_compiler_prefix "${ARCH}")-ar
            local AS=${TOOLPATH}/bin/$(get_android_compiler_prefix "${ARCH}")-as
            local CC=${TOOLPATH}/bin/clang
            local CXX=${TOOLPATH}/bin/clang++
            local LD=${TOOLPATH}/bin/ld
            local RANLIB=${TOOLPATH}/bin/$(get_android_compiler_prefix "${ARCH}")-ranlib
            local STRIP=${TOOLPATH}/bin/$(get_android_compiler_prefix "${ARCH}")-strip

            ../../../configure \
                --prefix="${PREFIX}" \
                CC="${CC} ${CFLAGS}" \
                LDFLAGS="${CFLAGS}" \
                CPP="${CC} -E" \
                CXX="${CXX} ${CFLAGS}" \
                LD="${LD}" \
                AR="${AR}" \
                AS="${AS}" \
                RANLIB="${RANLIB}" \
                STRIP="${STRIP}" \
                CPPFLAGS="${CFLAGS}" \
                --host=x86_64-apple-darwin \
                --disable-assembly --enable-static --disable-shared --enable-cxx --with-pic
            
            make
            make install
        fi

        popd
    done

    popd
}

function build_android_mpfr() {
    pushd $(pwd)

    cd lib/source/mpfr

    local LATEST_NDK_VERSION=$(ls $HOME/Library/Android/sdk/ndk/ | sort | tail -n 1)
    local NDK=$HOME/Library/Android/sdk/ndk/$LATEST_NDK_VERSION
    local MINSDKVERSION=16
    local TARGETSDKVERSION=30

    local TOOLCHAIN=llvm
    local PlatformOS=darwin
    local TOOLPATH=${NDK}/toolchains/${TOOLCHAIN}/prebuilt/${PlatformOS}-x86_64

    # for iphoneos
    for ARCH in $(echo $ANDROID_TARGET_ABI); do
        if [ ! -e "./build/android/${ARCH}" ]; then
            mkdir -p "build/android/${ARCH}"
        fi

        pushd $(pwd)

        cd "build/android/${ARCH}"

        make clean
        make distclean

        local PREFIX=$(realpath "../../../../../dist/mpfr/android-${ARCH}")
        local TARGET=$(get_android_target "${ARCH}")
        local EXTRAS="--target=${TARGET}"
        local CFLAGS="${EXTRAS} --gcc-toolchain=${TOOLPATH} --sysroot=${TOOLPATH}/sysroot -fPIC"
        local GMP_LIB_PATH="../../../../../dist/gmp/android-${ARCH}"
        local GMP_PATH="../../../../../dist/gmp/android-${ARCH}"

        if [ ! -e "${PREFIX}" ]; then
            mkdir -p "${PREFIX}"

            local AR=${TOOLPATH}/bin/$(get_android_compiler_prefix "${ARCH}")-ar
            local AS=${TOOLPATH}/bin/$(get_android_compiler_prefix "${ARCH}")-as
            local CC=${TOOLPATH}/bin/clang
            local CXX=${TOOLPATH}/bin/clang++
            local LD=${TOOLPATH}/bin/ld
            local RANLIB=${TOOLPATH}/bin/$(get_android_compiler_prefix "${ARCH}")-ranlib
            local STRIP=${TOOLPATH}/bin/$(get_android_compiler_prefix "${ARCH}")-strip

            ../../../configure \
                --prefix="${PREFIX}" \
                CC="${CC} ${CFLAGS}" \
                LDFLAGS="${CFLAGS}" \
                CPP="${CC} -E" \
                CXX="${CXX} ${CFLAGS}" \
                LD="${LD}" \
                AR="${AR}" \
                AS="${AS}" \
                RANLIB="${RANLIB}" \
                STRIP="${STRIP}" \
                CPPFLAGS="${CFLAGS}" \
                --with-gmp=${GMP_LIB_PATH} \
                --host=x86_64-apple-darwin \
                --disable-assembly --enable-static --disable-shared --enable-cxx --with-pic
            
            make
            make install
        fi

        popd
    done

    popd
}

function rpncalc_android_build() {
    result=0

    # build_android_boost
    build_android_gmp
    build_android_mpfr
}

function rpncalc_android_clean() {
    pushd $(pwd)

    cd lib/dist

    for LIBRARY in $(ls); do
        pushd $(pwd)

        cd ${LIBRARY}

        for TARGET in $(ls | grep ^android); do
            rm -rf ./${TARGET}
        done

        popd
    done

    popd
}

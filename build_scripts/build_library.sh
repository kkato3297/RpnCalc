#!/bin/bash

. ./build_scripts/android_build_script.sh
. ./build_scripts/ios_build_script.sh
# . ./build_scripts/macos_build_script.sh

function download_and_extract_package() {
    local BOOST_PACKAGE="https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.7z"
    local GMP_PACKAGE="https://gmplib.org/download/gmp/gmp-6.2.1.tar.xz"
    local MPFR_PACKAGE="https://www.mpfr.org/mpfr-current/mpfr-4.1.0.tar.xz"

    local URLLIST=(${BOOST_PACKAGE} ${GMP_PACKAGE} ${MPFR_PACKAGE})

    pushd $(pwd)

    if [ ! -e lib/package ]; then
        mkdir -p lib/package
    fi

    if [ ! -e lib/source ]; then
        mkdir -p lib/source
    fi

    cd lib/package

    for URL in ${URLLIST[@]}; do
        if [ ! -e "./$(basename ${URL})" ]; then
            wget "${URL}"
        fi
    done

    cd ../source

    for URL in ${URLLIST[@]}; do
        local EXTENSION="${URL##*.}"
        local PACKAGENAME=$(basename "${URL}")
        local EXTRACTEDNAME=$(echo ${PACKAGENAME} | sed -E "s/\.(7z|tar\.xz)//")
        local SOURCEDIR=$(echo "${EXTRACTEDNAME}" | sed -E "s/^(boost|gmp|mpfr).+$/\1/g")

        if [ ! -e "./${SOURCEDIR}" ]; then
            if [ "a${EXTENSION}z" == "a7zz" ]; then
                unar "../package/${PACKAGENAME}"
            elif [ "a${EXTENSION}z" == "axzz" ]; then
                tar Jxfv "../package/${PACKAGENAME}"
            fi

            mv "./${EXTRACTEDNAME}" "./${SOURCEDIR}"
        fi
    done

    popd
}

function prepare_boost_environment() {
    pushd $(pwd)

    cd lib/source/boost

    if [ ! -e ./b2 ]; then
        ./bootstrap.sh
    fi

    popd
}

function main() {
    local args=("$@")
    echo ${args[@]}
    if [ "a${args[0]}z" == "aiosz" ]; then
        if [ "a${args[1]}z" == "abuildz" ]; then
            download_and_extract_package
            prepare_boost_environment
            rpncalc_ios_build
        elif [ "a${args[1]}z" == "acleanz" ]; then
            rpncalc_ios_clean
        fi
    # elif [ "a${args[0]}z" == "amacosz" ]; then
    #     if [ "a${args[1]}z" == "abuildz" ]; then
    #         macos_build
    #     elif [ "a${args[1]}z" == "atestz" ]; then
    #         macos_test
    #     elif [ "a${args[1]}z" == "acleanz" ]; then
    #         macos_clean
    #     fi
    elif [ "a${args[0]}z" == "aandroidz" ]; then
        if [ "a${args[1]}z" == "abuildz" ]; then
            download_and_extract_package
            prepare_boost_environment
            rpncalc_android_build
        elif [ "a${args[1]}z" == "acleanz" ]; then
            rpncalc_android_clean
        fi
    else
        echo "unknown target..."
    fi
}

main "$@"

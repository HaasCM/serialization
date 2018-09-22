#!/usr/bin/env bash

handle_help() {
    echo -e "Usage: build.sh [mode] \n"
    echo -e "build.sh - Build Script for the Serialization Library \n"
    echo "Positional Arguments:"
    echo -e "[mode] {deploy, develop}\tsets the build mode of the suite. \n"
    echo "Optional Arguments:"
    echo -e "-h, --help\t\t\t Displays this help menu."
    echo -e "-v, --version\t\t\t Displays the version"

    return $1
}

handle_error() {
    echo -e "\nUnhandled argument received\n"
    handle_help 1
}

handle_version() {
    echo -e "version 0.1"

    return 0
}

handle_deploy() {
    rm -rf build
    mkdir build
    cd build
    cmake3 ../ -DCMAKE_INSTALL_PREFIX=../deploy
    make -j ${nproc}
    make install
    cd ..
    return 0
}

handle_develop() {
    rm -rf build
    mkdir build
    cd build
    cmake3 ../
    make -j ${nproc}
    return 0
}


for var in "$@"
do
    if [ "$var" = "--help" -o "$var" = "-h" ]
    then
       handle_help 0
       exit 0
    fi;

    if [ "$var" = "--version" -o "$var" = "-v" ]
    then
        handle_version
        exit 0
    fi;

    if [ "$var" = "deploy" ]
    then
        handle_deploy
        exit 0
    fi;

    if [ "$var" = "develop" ]
    then
        handle_develop
        exit 0
    fi;

    handle_error
    exit 1
done


#!/bin/bash

if [[ "$1" == "clean" ]]; then
    rm -rf "build/" "rpmalloc/" "SFML/"
    exit
fi

if [[ -n "$(command -v wget)" ]]; then
    download_cmd="wget"
elif [[ -n "$(command -v curl)" ]]; then
    download_cmd="curl -O"
fi

if [[ ! -d "SFML/" ]]; then
    $download_cmd "https://www.sfml-dev.org/files/SFML-2.5.0-linux-gcc-64-bit.tar.gz"
    tar -xzf "SFML-2.5.0-linux-gcc-64-bit.tar.gz" -C .
    rm -rf "SFML/"
    mv "SFML-2.5.0/" "SFML/"
    rm "SFML-2.5.0-linux-gcc-64-bit.tar.gz"
else
    echo "Skip fetching of SFML library ..."
fi

if [[ ! -d "rpmalloc/" ]]; then
    git clone "https://github.com/rampantpixels/rpmalloc.git" "rpmalloc-temp/"
    rm -rf "rpmalloc/"
    mv "rpmalloc-temp/rpmalloc/" .
    rm -rf "rpmalloc-temp/"

    # There is an issue with RTLD_NEXT, Clang suggests compiling with RTLD_NOW (which works).
    sed -i 's/RTLD_NEXT/RTLD_NOW/g' "rpmalloc/malloc.c"
else
    echo "Skip fetching of rpmalloc ..."
fi

echo "Compiling RTMOBAS ..."
rm -rf "build/"
mkdir "build/"
cmake -Bbuild/ -H.

cd "build/" || exit
make

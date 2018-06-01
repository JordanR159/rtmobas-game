#!/bin/bash

if [[ "hash -v wget" -eq 0 ]]; then
    download_cmd="wget"
elif [[ "hash -v curl" -eq 0 ]]; then
    download_cmd="curl -O"
fi

$download_cmd "https://www.sfml-dev.org/files/SFML-2.5.0-linux-gcc-64-bit.tar.gz"
tar -xzf "SFML-2.5.0-linux-gcc-64-bit.tar.gz" -C .
mv "SFML-2.5.0" "SFML"

git clone "https://github.com/rampantpixels/rpmalloc.git" "./rpmalloc-temp/"
mv "rpmalloc-temp/rpmalloc" .
rm -rf "rpmalloc-temp"

# There is an issue with RTLD_NEXT, Clang suggests compiling with RTLD_NEW (which works).
sed -i 's/RTLD_NEXT/RTLD_NEW/g' "./rpmalloc/malloc.c"

mkdir build
cmake -B./build/ -H.

echo "You are ready to compile RTMOBAS. Follow these steps:"
echo "1. Enter ./build/"
echo "2. Execute make"

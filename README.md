# RTM
A game that can be played in RTS style or MOBA style

## Installation
For those who need some assistance on setting up this github repository on their local machine:

### Windows
1. Install MinGW x64 and create CLion Toolchain
2. Download SFML 2.5.0 - MinGW Version *(YOU MUST HAVE THIS VERSION)*
3. Place SFML 2.5.0 as the Folder "SFML" inside the local repository
4. Download RPMalloc and place the Folder "rpmalloc" inside the local repository
5. ------------- (Insert STB Download step once integrated)
6. Set MinGW/bin as a new environmental variable under advanced system settings
7. Either set SFML/bin as another environmental variable or move all the dll files inside SFML/bin into C:/Windows/System32/... Another choice is to have a global copy of SFML inside C:/Program Files/ and set that as a new environmental variable.
8. You are ready to go

### Linux
1. Install SFML, if possible (the bash script will grab a copy, but it's not optimal).
    - On Ubuntu or Debian: `sudo apt install libsfml-dev build-essential`
    - On Fedora: `sudo dnf install SFML-devel`
    - on openSUSE: `sudo zypper install sfml2-devel`
2. Execute: `./build.sh`

## Libraries

[Rampant Pixels Memory Allocator (rpmalloc)](https://github.com/rampantpixels/rpmalloc)
[Simple and Fast Multimedia Library (SFML)](https://github.com/SFML/SFML)

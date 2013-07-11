#!/bin/bash

# The purpose of this script is just to create a new tarball of the latest release files

TAR_NAME="snowman-apocalypse-for-linux-v$1.tar"

if [ "$1" != "" ] 
    then
    cd release
    if [ -f "$TAR_NAME" ] 
        then
        echo "Release already exists! Aborting."
    else
        # Get stuff ready
        mkdir bin
        cp -r ../bin/textures bin
        cp -r ../bin/audio bin
        cp -r ../bin/Release/snowman-apocalypse-linux bin

        # tar it up with version from cmd line
        tar -cvf $TAR_NAME bin 1>/dev/null

        # Cleanup
        rm -rf bin

        echo "Done"
    fi
else
    echo "You must specify a version number!"
fi
#!/bin/sh

# Run the Saucer CLI tool to embed the HMTL file structure
saucer embed "content"

targetFolder='/Users/Shared/Gig Performer/Extensions'

if ! test -d "$targetFolder"; then
   mkdir -p "$targetFolder"
fi


#Get rid of all the DLLs in there so we can do a clean test
#rm -rf "$targetFolder"/*


if ! test -d build; then
   mkdir build
fi
cd build
cmake ..
cmake --build . --config Release
mv *.dylib "$targetFolder"
::Run the Saucer CLI tool to embed the HMTL file structure
CALL saucer embed "content"

::Create a build directory if it's not already there
mkdir build

::Change to the build directory
cd build

::Create the configuration file using cmake
cmake ..

::For RELEASE mode please execute this instead
cmake --build . --config Release

::All going well, you should now have a DLL in the Release folder


::Go back to the starting folder
cd ..

rem
rem ********************************************
rem Extension built and stored in /build/Release
rem ********************************************


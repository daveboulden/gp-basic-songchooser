::All going well, you should now have a DLL in the Debug folder
::So now copy it to the location where GP can find it

mkdir "C:\Users\Public\Documents\Gig Performer\Extensions"
copy build\Debug\*.dll "%PUBLIC%\Documents\Gig Performer\Extensions"

::For RELEASE build please replace the "Debug" folder reference with "Release"

rem
rem ********************************************
rem Extension copied into "%PUBLIC%\Documents\Gig Performer\Extensions"
rem ********************************************


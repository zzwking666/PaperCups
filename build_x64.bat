@echo off
set "VSMSVC=C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231"
set "WINSDK=C:\Program Files (x86)\Windows Kits\10"
set "PATH=%VSMSVC%\bin\Hostx64\x64;%PATH%"
set "INCLUDE=%VSMSVC%\include;%VSMSVC%\ATLMFC\include;C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\VS\include;%WINSDK%\include\10.0.26100.0\ucrt;%WINSDK%\include\10.0.26100.0\um;%WINSDK%\include\10.0.26100.0\shared;%WINSDK%\include\10.0.26100.0\winrt"
set "LIB=%VSMSVC%\lib\x64;%VSMSVC%\ATLMFC\lib\x64;%WINSDK%\lib\10.0.26100.0\ucrt\x64;%WINSDK%\lib\10.0.26100.0\um\x64"
cd /d D:\Projects\PaperCups
cmake --preset user-ninja-debug-NoHardware && cmake --build --preset user-ninja-debug-NoHardware-build

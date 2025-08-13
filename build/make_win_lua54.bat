set MINGW64_PATH=D:\msys64\mingw64
:: set MINGW32_PATH=D:\msys64\mingw32

:: 检查MinGW路径是否存在
if not exist "%MINGW64_PATH%\bin\gcc.exe" (
    echo Error: MinGW64 not found at %MINGW64_PATH%
    pause
    exit /b 1
)
:: if not exist "%MINGW32_PATH%\bin\gcc.exe" (
::     echo Error: MinGW32 not found at %MINGW32_PATH%
::     pause
::     exit /b 1
:: )

:: 设置环境变量
set PATH=%MINGW64_PATH%\bin;%PATH%

:: 64位构建
mkdir build64_54
pushd build64_54
cmake -DLUA_VERSION=5.4.1 -DUSING_LX=ON -G "MinGW Makefiles" -DCMAKE_C_COMPILER=%MINGW64_PATH%/bin/gcc.exe -DCMAKE_CXX_COMPILER=%MINGW64_PATH%/bin/g++.exe ..
mingw32-make
popd

:: 创建目录并复制64位dll
md plugin_lua54\Plugins\x86_64
copy /Y build64_54\libxlua.dll plugin_lua54\Plugins\x86_64\xlua.dll

:: :: 设置环境变量为32位
:: set PATH=%MINGW32_PATH%\bin;%PATH%
::
:: :: 32位构建
:: mkdir build32_54
:: pushd build32_54
:: cmake -DLUA_VERSION=5.4.1 -DUSING_LX=ON -G "MinGW Makefiles" -DCMAKE_C_COMPILER=%MINGW32_PATH%/bin/gcc.exe -DCMAKE_CXX_COMPILER=%MINGW32_PATH%/bin/g++.exe ..
:: mingw32-make
:: popd
::
:: :: 创建目录并复制32位dll
:: md plugin_lua54\Plugins\x86
:: copy /Y build32_54\xlua.dll plugin_lua54\Plugins\x86\xlua.dll

pause
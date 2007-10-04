rem script to build Lua under "Visual Studio .NET Command Prompt".
rem do not run it from this directory, run it from the toplevel: etc\luavs.bat
rem it creates lua5.1.dll, lua5.1.lib, lua5.1.exe, and luac5.1.exe in src.

cd src
cl /MD /O2 /W3 /c /D_CRT_SECURE_NO_DEPRECATE /D_CRT_NONSTDC_NO_DEPRECATE /DLUA_BUILD_AS_DLL l*.c
del lua.obj luac.obj
link /DLL /out:lua5.1.dll l*.obj
cl /MD /O2 /W3 /c /D_CRT_SECURE_NO_DEPRECATE /D_CRT_NONSTDC_NO_DEPRECATE /DLUA_BUILD_AS_DLL lua.c
link /out:lua5.1.exe lua.obj lua5.1.lib
cl /MD /O2 /W3 /c /D_CRT_SECURE_NO_DEPRECATE /D_CRT_NONSTDC_NO_DEPRECATE l*.c print.c
del lua.obj linit.obj lbaselib.obj ldblib.obj liolib.obj lmathlib.obj loslib.obj ltablib.obj lstrlib.obj loadlib.obj
link /out:luac5.1.exe *.obj
del *.obj
cd ..

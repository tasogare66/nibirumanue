::x64 native tools command prompt ������Ȃ���,dumpbin /EXPORTS lib�m�F�Ŋ֐��̐擪�� _ ������(_lua_open)�����N�ł��Ȃ�����
if defined VCINSTALLDIR (
call "%VCINSTALLDIR%\vcvarsall.bat" x64)
cl /MD /O2 /c /DLUA_BUILD_AS_DLL *.c
ren lua.obj lua.o
ren luac.obj luac.o
link /DLL /IMPLIB:lua5.4.6.lib /OUT:lua5.4.6.dll *.obj 
link /OUT:lua.exe lua.o lua5.4.6.lib 
lib /OUT:lua5.4.6-static.lib *.obj
link /OUT:luac.exe luac.o lua5.4.6-static.lib
del *.obj *.o

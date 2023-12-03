cd /d %~dp0

set include_dirs=-I..\dependencies\collision_engine\include -I..\dependencies\sdl\include -I..\dependencies\sdl_image\include
set sources=src\*.cpp src\entities\*.cpp src\utils\*.cpp src\utils\tilemap\*.cpp
set libs=..\dependencies\collision_engine\lib\collision_engine.lib ..\dependencies\sdl\lib\x64\SDL2main.lib ..\dependencies\sdl\lib\x64\SDL2.lib ..\dependencies\sdl_image\lib\x64\SDL2_image.lib

g++ %include_dirs% %sources% %libs% -o bin\main.exe -std=gnu++20 

cd /d %~dp0\..
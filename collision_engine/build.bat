cd /d %~dp0

g++ -Iinclude -c src\collider.cpp -o bin\interms\collider.o -std=gnu++20
g++ -Iinclude -c src\collision_listener.cpp -o bin\interms\collision_listener.o -std=gnu++20
g++ -Iinclude -c src\shape.cpp -o bin\interms\shape.o -std=gnu++20

ar rcs bin\collision_engine.lib bin\interms\*.o
ar rcs ..\dependencies\collision_engine\lib\collision_engine.lib bin\interms\*.o

cd /d %~dp0\..
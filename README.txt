Программа читает данные из файла, заменяет вхождения одной последовательности байт на другую и записывает результат в другой файл.

--version Текущая версия.

--help Руководство использования.

Пример использования: CReplace input.txt output.txt "[BYTES TO REPLACE]" "[BYTES TO REPLACE WITH]"

Байты записываются в Hex формате (abc = 0x616263).

Настройка проекта для сборки в студии (выполняем команды в консоле в директории проекта):
> mkdir build
> cd build
> cmake -S .. -G "Visual Studio 17 2022" -A Win32

В каталоге build создаются нужные для сборки файлы. Можно открыть проект (.sln-файл) в Visual Studio и в ней собирать. Можно открыть в Visual Studio файл CMakeLists.txt. Можно собирать проект через cmake в консоле.

Сборка проекта:
> cmake --build . -C Release
> cmake --build . -C Debug


Запуск тестов:
> cmake --build . --target test_lib
> cmake --build . --target test_src
> cmake --build . --target test_all
> ctest -C Release
> ctest -C Debug
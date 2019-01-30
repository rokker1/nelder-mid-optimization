# Алгоритм оптимизации Нелдера-Мида

### Минимальное окружение
* `g++` (GNU C++ Compiler) с поддержкой стандарта С++11
* `gnuplot`  версии не ниже 4.6 ([gnuplot home page](http://www.gnuplot.info/))

### Компиляция и запуск
1. Через консоль (g++)

```sh
g++ -std=c++11 -lm point.cpp nma.cpp main.cpp -o nma;
./nma
```

2. Используя [JetBrains CLion](https://www.jetbrains.com/clion/) ([CMake](https://cmake.org/)) 

    a. Открыть проект из папки репозитория, используя СLion.
    
    b. Собрать проект и запустить

Для визуализации результатов

```sh
gnuplot plot.plt
```

### Описание алгоритма
См. папку `docs`

### Контроль точности при сходимости
Требуемое значение epsilon-константы задается в файле `nma.h`

```cpp
#define EPS 1e-4
```


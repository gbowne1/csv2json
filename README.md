# csv2json
This is convertcsv, a C++ program to convert CSV to JSON

To build and compile this use:

```shell
g++ -o convertcsv main.cpp convertcsv.cpp -Wall -Werror -Wextra -Wpedantic -Wshadow -Wfloat-equal -Wconversion -std=c++17
```

if you want everything just use

```shell
g++ -o convertcsv main.cpp convertcsv.cpp -Wall -Werror -Wextra -Wpedantic -Wshadow -Wfloat-equal -Wconversion -std=c++17 -O2 -g
```

this might work too

```shell
clang++ -o convertcsv main.cpp convertcsv.cpp -Wall -Werror -Wextra -Wpedantic -Wshadow -Wfloat-equal -Wconversion -std=c++17 -O2 -g
```

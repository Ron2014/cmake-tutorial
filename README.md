# Intro

Check these code from [cmake-3.16.1/Help/guide/tutorial/](https://cmake.org/download/).

For learning CMake, I will follow [official tutorial document](https://cmake.org/cmake/help/latest/guide/tutorial/index.html) and do changes in theses files.

More official repo, I search into these address:

[repo for CMake](https://gitlab.kitware.com/cmake/cmake/tree/master)

[repo for CMake Tutorial](https://gitlab.kitware.com/cmake/cmake/tree/master/Help/guide/tutorial)

Pay attention to the different between official document and repo.

## build in MinGW/MSYS

When I built in Msys2-MinGW64 I got this

```
System is unknown to cmake, create:
Platform/MINGW64_NT-10.0 to use this system, please send your config file to cmake@www.cmake.org so it can be added to cmake
```

Suggest to `pacman -S mingw-w64-x86_64-cmake` and then you can

`cmake .. -G "MinGW Makefiles"`

or

`cmake .. -G "MSYS Makefiles"`

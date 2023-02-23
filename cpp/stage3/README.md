# Stage3

複数ターゲット、複数パッケージ

```
cpp
└─stage3
    ├─ lib
    |   ├─ BUILD
    |   ├─ hello-time.cpp
    |   └─ hello-time.hpp
    ├─ main
    |   ├─ BUILD
    |   ├─ hello-world.cpp
    |   ├─ hello-greet.cpp
    |   └─ hello-greet.hpp
    └─ WORKSPACE
```

## ビルド

```sh
$ cd cpp/stage3

$ bazel build //main:hello-world
Starting local Bazel server and connecting to it...
INFO: Analyzed target //main:hello-world (37 packages loaded, 161 targets configured).
INFO: Found 1 target...
Target //main:hello-world up-to-date:
  bazel-bin/main/hello-world
INFO: Elapsed time: 3.813s, Critical Path: 0.32s
INFO: 8 processes: 4 internal, 4 linux-sandbox.
INFO: Build completed successfully, 8 total actions
```

ライブラリのビルド

```
$ bazel build //lib:hello-time 
INFO: Analyzed target //lib:hello-time (36 packages loaded, 155 targets configured).
INFO: Found 1 target...
Target //lib:hello-time up-to-date:
  bazel-bin/lib/libhello-time.a
  bazel-bin/lib/libhello-time.so
INFO: Elapsed time: 0.747s, Critical Path: 0.27s
INFO: 6 processes: 3 internal, 3 linux-sandbox.
INFO: Build completed successfully, 6 total actions

$ file bazel-bin/lib/libhello-time.a
bazel-bin/lib/libhello-time.a: current ar archive

$ file bazel-bin/lib/libhello-time.so
bazel-bin/lib/libhello-time.so: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, BuildID[sha1]=6b316cf0202a6894a36477b7fc94b47ddfd6819b, not stripped
```

## 実行

```sh
$ ./bazel-bin/main/hello-world
Hello world
Thu Feb 23 11:26:13 2023
```

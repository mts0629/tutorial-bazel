# Stage2

複数ターゲット、単一パッケージ

```
cpp
└─stage2
    ├─ main
    |   ├─ BUILD
    |   ├─ hello-world.cpp
    |   ├─ hello-greet.cpp
    |   └─ hello-greet.hpp
    └─ WORKSPACE
```

## ビルド

```sh
$ cd cpp/stage2

$ bazel build //main:hello-world
Starting local Bazel server and connecting to it...
INFO: Analyzed target //main:hello-world (36 packages loaded, 158 targets configured).
INFO: Found 1 target...
Target //main:hello-world up-to-date:
  bazel-bin/main/hello-world
INFO: Elapsed time: 4.047s, Critical Path: 0.29s
INFO: 7 processes: 4 internal, 3 linux-sandbox.
INFO: Build completed successfully, 7 total actions
```

ライブラリのビルド

```
$ bazel build //main:hello-greet
INFO: Analyzed target //main:hello-greet (0 packages loaded, 0 targets configured).
INFO: Found 1 target...
Target //main:hello-greet up-to-date:
  bazel-bin/main/libhello-greet.a
  bazel-bin/main/libhello-greet.so
INFO: Elapsed time: 0.243s, Critical Path: 0.08s
INFO: 5 processes: 3 internal, 2 linux-sandbox.
INFO: Build completed successfully, 5 total actions

$ file ./bazel-bin/main/libhello-greet.a
./bazel-bin/main/libhello-greet.a: current ar archive

$ file ./bazel-bin/main/libhello-greet.so
./bazel-bin/main/libhello-greet.so: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, BuildID[sha1]=69d6141a062428c11432051fecc71663c8d0aa51, not stripped
```

## 実行

```sh
$ bazel run //main:hello-world
INFO: Analyzed target //main:hello-world (1 packages loaded, 5 targets configured).
INFO: Found 1 target...
Target //main:hello-world up-to-date:
  bazel-bin/main/hello-world
INFO: Elapsed time: 0.189s, Critical Path: 0.01s
INFO: 1 process: 1 internal.
INFO: Build completed successfully, 1 total action
INFO: Running command line: bazel-bin/main/hello-world
Hello world
Thu Feb 23 02:46:40 2023
```

```sh
$ ./bazel-bin/main/hello-world
Hello world
Thu Feb 23 02:47:19 2023
```

# Stage1

単一ターゲット、単一パッケージ

```
cpp
└─stage1
    ├─ main
    |   ├─ BUILD
    |   └─ hello-world.cpp
    └─ WORKSPACE
```

## ビルド

`bazel build <package_name>:<target_name>`

```sh
$ cd cpp/stage1

$ bazel build //main:hello-world
INFO: Analyzed target //main:hello-world (36 packages loaded, 155 targets configured).
INFO: Found 1 target...
Target //main:hello-world up-to-date:
  bazel-bin/main/hello-world
INFO: Elapsed time: 0.614s, Critical Path: 0.26s
INFO: 6 processes: 4 internal, 2 linux-sandbox.
INFO: Build completed successfully, 6 total actions

$ ls
WORKSPACE  bazel-bin  bazel-out  bazel-stage1  bazel-testlogs  main
```

## 実行

`bazel run <package_name>:<target_name>`

```sh
$ bazel run //main:hello-world
INFO: Analyzed target //main:hello-world (0 packages loaded, 0 targets configured).
INFO: Found 1 target...
Target //main:hello-world up-to-date:
  bazel-bin/main/hello-world
INFO: Elapsed time: 0.126s, Critical Path: 0.00s
INFO: 1 process: 1 internal.
INFO: Build completed successfully, 1 total action
INFO: Running command line: bazel-bin/main/hello-world
Hello world
Wed Feb 22 02:31:49 2023
```

出力バイナリを直接指定して実行

```
$ ./bazel-bin/main/hello-world
Hello world
Wed Feb 22 02:32:21 2023
```

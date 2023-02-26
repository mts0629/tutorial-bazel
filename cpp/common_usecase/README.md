# Common C++ build usecase

```
cpp
└─ common_usecase
    ├─ lib
    |   ├─ BUILD
    |   ├─ hello-time.cpp
    |   └─ hello-time.hpp
    ├─ main
    |   ├─ BUILD
    |   ├─ const.hpp
    |   ├─ hello-world.cpp
    |   ├─ hello-greet.cpp
    |   └─ hello-greet.hpp
    ├─ test
    |   ├─ BUILD
    |   └─ hello-test.cpp
    └─ WORKSPACE
```

## 推移的なインクルード (transitive includes)

`deps` 属性では、直接的な依存関係のみが指定される。
例えば

`hello-world` <- `hello-greet` <- `constants`

という依存関係があるとき、 `hello-world` 側で指定される依存関係は `hello-greet` のみとなる。


```bazel
cc_library(
    name = "constants",
    hdrs = ["constants.hpp"],
    visibility = ["//test:__pkg__"],
)

cc_library(
    name = "hello-greet",
    srcs = ["hello-greet.cpp"],
    hdrs = ["hello-greet.hpp"],
    deps = ["//main:constants"],
    visibility = ["//test:__pkg__"],
)

cc_binary(
    name = "hello-world",
    srcs = ["hello-world.cpp"],
    deps = [
        "//main:hello-greet",
        "//lib:hello-time",
    ],
)
```

## 複数ファイルの指定

ターゲットに複数ファイルを指定する際、ヘルパー関数 `glob` でパッケージ内のファイルをパターンマッチングを使って取得できる。

```bazel
cc_library(
    name = "hello-time",
    srcs = glob(["*.cpp"]),
    hdrs = ["hello-time.hpp"],
    visibility = ["//main:__pkg__"],
)
```

## コンパイル済みライブラリの追加

`cc_library` ルールでプリコンパイル済み（またはヘッダオンリー）ライブラリを依存関係に追加できる。
  - .so ファイル等ライブラリ本体は `src` 属性として追加する。

```bazel
cc_library(
    name = "constants",
    hdrs = ["constants.hpp"],
    visibility = ["//test:__pkg__"],
)
```

## 外部ライブラリのインクルード（Google Testによるテスト）

ワークスペース外のライブラリとしてGoogle Testをインクルードし、Bazelでテストを実施する方法について。

[Quickstart: Building with Bazel](https://github.com/google/googletest/blob/main/docs/quickstart-bazel.md)

`WORKSPACE` ファイルに、 `http_archive` ルールでGoogle Testへの依存関係を追加する。
- `url` 属性として、Commit IDを指定してアーカイブをダウンロードしている（ここではv1.13.0の最新コミット）。
- コミットIDが上記アーカイブのディレクトリパスに付加されてしまうため、 `strip_prefix` 属性にプレフィックスと指定し、取り除いている。

```bazel
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_googletest",
    # Commit id: b796f7d44681514f58a683a3a71ff17c94edb0c1
    url = "https://github.com/google/googletest/archive/b796f7d44681514f58a683a3a71ff17c94edb0c1.zip",
    # Remove prefix from the files
    strip_prefix = "googletest-b796f7d44681514f58a683a3a71ff17c94edb0c1",
)
```

`get_greet()` 関数のテストを `//test:hello-test` として追加する。

- test/hello-test.cpp

  ```cpp
  #include "gtest/gtest.h"
  #include "main/hello-greet.hpp"

  TEST(HelloTest, GetGreet) {
      EXPECT_EQ(get_greet("Bazel"), "Hello Bazel");
  }
  ```

- test/BUILD

  `cc_test` ルールでテストを追加する。_
  - `deps` にテスト対象のターゲットおよび、外部ライブラリであるGoogle Testのターゲット `"@com_google_googletest/::gtest_main"` （テストプログラムのmain関数）を追加する。
  - `size` は、テストで使用するリソースの規模を指定する。単体テストは `"small"`、End-to-Endテストは `"large"` など。

  ```bazel
  load("@rules_cc//cc:defs.bzl", "cc_test")

  cc_test(
      name = "hello-test",
      # "Heaviness": required time/resources of the test target,
      # "small": 20MB / 1 CPU / 1 min.
      size = "small",
      srcs = ["hello-test.cpp"],
      deps = [
          "@com_google_googletest//:gtest_main",
          "//main:hello-greet",
      ],
  )
  ```

`bazel test <label>` でテストをビルド・実行する。
- C++14以上が要件であるため、オプション `--cxxopt` でバージョン (C++17) を指定している。
- `--test_output=all` でテスト時の全ログを出力している（デフォルト値は、ステータス概要のみ出力する `"summary"` ）。

```sh
$ bazel test //test:hello-test --cxxopt=-std=c++17 --test_output=all
INFO: Analyzed target //test:hello-test (49 packages loaded, 636 targets configured).
INFO: Found 1 test target...
INFO: From Testing //test:hello-test:
==================== Test output for //test:hello-test:
Running main() from gmock_main.cc
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from HelloTest
[ RUN      ] HelloTest.GetGreet
[       OK ] HelloTest.GetGreet (0 ms)
[----------] 1 test from HelloTest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
================================================================================
Target //test:hello-test up-to-date:
  bazel-bin/test/hello-test
INFO: Elapsed time: 5.892s, Critical Path: 4.01s
INFO: 32 processes: 10 internal, 22 linux-sandbox.
INFO: Build completed successfully, 32 total actions
//test:hello-test                                                        PASSED in 0.0s

Executed 1 out of 1 test: 1 test passes.
```

## オプション

Bazelの各種コマンドに対して、コマンドラインから実行時オプションを指定できる。

[Command-Line Reference](https://bazel.build/reference/command-line-reference?hl=en)

例えば、 `bazel build` に対するオプションには次のようなものがある。

### `--copt=<a string>` / `--cxxopt=<a string>`

gcc / g++ に渡す追加のオプション。

### `--verbose_vailures`

コマンドが失敗した場合、実行したコマンドラインの全体を表示する。

`--verbose_failures` オプション

### `--sandbox_debug`

通常ビルド後破棄される一時ディレクトリのsandboxを、ビルド後も保持する。
また、実行時に追加のデバッグ情報が付加される。

### `--subcommands`

ビルド中に実行されたサブコマンドを表示する。


各コマンドの実行時に指定するオプションを、`command:name` の形式で `.bazelrc` ファイルに記載できる。

例えば、デバッグビルド時のオプションを下記のように `.bazelrc` に記載して、

```bazel
build:debug --compilation_mode=dbg
build:debug --cxxopt="-g"
build:debug --strip=never
```

ビルド時のオプション `--config debug` で参照できる。

```sh
$ bazel build //main:hello-world --config debug
INFO: Analyzed target //main:hello-world (37 packages loaded, 163 targets configured).
INFO: Found 1 target...
Target //main:hello-world up-to-date:
  bazel-bin/main/hello-world
INFO: Elapsed time: 0.617s, Critical Path: 0.27s
INFO: 8 processes: 4 internal, 4 linux-sandbox.
INFO: Build completed successfully, 8 total actions

# デバッグ情報が付加されている
$ file ./bazel-bin/main/hello-world
./bazel-bin/main/hello-world: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=fa75f7d7b565deaf45391fdd0fe3f3b69750cb05, with debug_info, not stripped
```

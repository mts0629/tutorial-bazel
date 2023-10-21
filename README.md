# tutorial-bazel

ビルドツールBazelの学習

## インストール

APTによるインストール

- [Install](https://bazel.build/install)
- [Installing Bazel on Ubuntu](https://bazel.build/install/ubuntu)

```sh
$ sudo apt install apt-transport-https curl gnupg -y
curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor >bazel-archive-keyring.gpg
sudo mv bazel-archive-keyring.gpg /usr/share/keyrings
echo "deb [arch=amd64 signed-by=/usr/share/keyrings/bazel-archive-keyring.gpg] https://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list

$ sudo apt update && sudo apt install bazel

# Upgrade bazel
# $ sudo apt update && sudo apt full-upgrade
```

## ソースコード・著作権

本リポジトリに含まれるソースコードは、下記で公開されている内容を元に改変を加えたものです。

未改変部の著作権は、原著作者様に帰属します。

- [Bazel](https://github.com/bazelbuild/bazel)
- [Bazel Tutorial: Build a C++ Project](https://bazel.build/start/cpp)

### 改変点

- コーディングスタイルの調整
- コメントの追加
- プロジェクト・ファイル構成

## 基本

- Bazelはビルドの再現性を重視しており、ビルド時のすべての依存関係を明示的に記述する必要がある。

- ビルド時にSandboxと呼ばれる隔離環境を生成し、その中でビルドを実施する (sandboxing) 。

- キャッシュをリモート環境へ保存 / リモート環境から取得する機能が提供されている。

- Workspace

    ビルド入出力の対象物および、`BUILD` ファイルが配置されたディレクトリ。
    `WORKSPACE` ファイルの配置で定義される。

    - `WORKSPACE` ファイルには、Workspace外部の依存関係などが記述される。
    - `BUILD` (`BUILD.bazel`) ファイルには、ビルド出力物とその依存関係、ビルド方法 (Rule) が記述される。

- Package

    `BUILD` ファイルで定義される Targetのセット。
    Workspaceルートからの、`BUILD` ファイルの相対パスとして表される。

- Target

    `BUILD` ファイルで定義される、ユーザのビルド可能な単位。
    Labelによって識別される。

    - Labelは、`//` をWorkspaceルートとして `//path/to/package:target` の形式で記述される。

# bazel-tutorial

ビルドツール [bazel](https://github.com/bazelbuild/bazel) 入門

## インストール

[Ubuntu環境へのインストール](https://bazel.build/install/ubuntu)

APTによるインストール

```sh
$ sudo apt install apt-transport-https curl gnupg -y
curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor >bazel-archive-keyring.gpg
sudo mv bazel-archive-keyring.gpg /usr/share/keyrings
echo "deb [arch=amd64 signed-by=/usr/share/keyrings/bazel-archive-keyring.gpg] https://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list

$ sudo apt update && sudo apt install bazel

# Upgrade bazel
$ sudo apt update && sudo apt full-upgrade
```

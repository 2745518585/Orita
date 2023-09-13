zh-CN | [en-CN](./README_en-CN.md)

# Orita

[Orita](https://github.com/2745518585/Orita)

由 [赵悦岑](https://github.com/2745518585/) 开发的一款 OI 工具，包括评测、对拍、数据生成等，主要由 C++ 语言编写。

[vscode-Orita](https://github.com/2745518585/vscode-Orita)

Orita 的配套 VSCode 拓展。

## 安装

### 构建

在安装 Orita 前，需要保证环境为 Windows 或 Linux 环境，计算机上需要安装以下应用程序：

- [CMake](https://cmake.org/) (3.15+)

同时需要安装 GCC 11.4+ 或 MSVC 2022+。

Windows 计算机请前往官网下载并安装：

- [CMake](https://cmake.org/)
- [MinGW](https://www.mingw-w64.org/downloads/)
- [Visual Studio](https://visualstudio.microsoft.com/downloads/)

Linux 计算机执行以下命令安装 CMake 和 GCC：

```shell
$ sudo apt-get install cmake
$ sudo apt-get install g++
```

安装完成后，通过以下命令获取 Orita 源代码：

```shell
$ git clone https://github.com/2745518585/Orita
$ git submodule init
$ git submodule update
```

在 `Orita/` 目录下运行以下命令来编译源代码：

```shell
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

### 下载

可以在 [Github](https://github.com/2745518585/Orita/releases) 上查找最新的发行版，下载对应平台的已编译文件压缩包。

### 初始化

运行 `Orita/` 目录下的 `init.bat | init.sh` 编译得到入口文件，请保证 `Orita/bin/` 中的可执行文件能被全局调用，可以任意移动可执行文件位置。使用 CMake 生成时会自动输出源文件所在位置，如果移动源文件后请执行 `Orita/` 目录下的 `init.bat | init.sh`。

为了正常使用 Orita，请保证计算机上有支持 C++14 的 C++ 编译器 g++，并能在控制台中全局调用。

使用 `orita reset` 命令初始化并清空配置。

## 用法

### 参数系统

所有命令的参数格式均为 `/i arg ...` 或 `-i arg`，每个参数的范围为声明至下一个参数或结尾。

如参数中含空格需加引号，且参数中需要使用引号请使用 `\"`。

### 内置文件

Orita 内置了一些文件来方便使用，其初始化后位于配置文件目录中。

`0.cpp`：空，总是返回 $0$。

`1.cpp`：文件比较器，三个参数分别为 `in` `out` `ans` 文件，返回 `out` 和 `ans` 忽略行末空格和文末换行的比较结果。

### 文件名替换

形如 `%[0-999]` 将替换为 `file.json` 中对应编号的文件名，如 `%1` 表示编号为 $1$ 的文件名。

文件名中的 `%...%` 替换为环境变量 `...`。优先匹配项目环境变量 `{APPDATA_PATH}`、`{FILE_PATH}` 和 `{RUNNING_PATH}`，不匹配则返回系统环境变量 `...`。

文件名中的 `%%` 将替换为 `%`。

## 命令

### reset

`orita reset`

重置配置。

### clear

`orita clear`

删除配置文件。

### run

`run [/f <file>] [/c <chk_file>] [/t <time>]`

#### 描述

将给定的文件跑预定好的标准输入输出，并给出结果。所有文件编译时定义宏 `JUDGING`。

#### 参数列表

`/f <file>`    指定源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的源文件为准。

`/c <chk_file>`    指定 `checker` 文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的源文件为准。

`/t <time>`    修改默认运行时间限制（单位 ms）。

#### 数据及源代码输出

数据与源代码输出会在程序运行完成后存放至 `data/data.in` `data/data.out` `data/data.ans` `data/data.txt`。

### chdata

`chdata [/f <input_file> <output_file> | /s] [/t <time>]`

#### 描述

用于修改标准输入输出。

#### 参数列表

`/f <input_file> <output_file>`   指定输入输出文件。

`/s`    从 `stdin` 中读取，每个文件以 `EOF` 结束。此参数与 `/f` 冲突，优先级低于 `/f`。

`/t <time>`    修改默认运行时间限制（单位 ms）。

### check

`check [/n <sum>] [/f <in_file> <out_file> <ans_file> | [[/if <in_file>] [/of <out_file>] [/af <ans_file>]]] [/c <chk_file>] [/t <time>]`

#### 描述

给定数据生成器、标准代码和源代码，进行对拍。所有文件编译时定义宏 `JUDGING`。数据会存放在 `data/` 目录下。

#### 参数列表

`/n <sum>`    对拍次数。如无此参数不会开始对拍，仅视为设置参数。

`/f <in_file> <out_file> <ans_file>`    指定源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的源文件为准。

`/c <chk_file>`    指定 `checker` 的文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的源文件为准。

`/if <in_file>`    指定 `in` 文件（后缀不为 `.cpp `自动添加 `.cpp `后缀）。如无此参数则以上一次设置的 `in` 文件为准。此参数与 `/f` 冲突，优先级低于 `/f`。

`/of <out_file>`    指定 `out` 文件（后缀不为 `.cpp `自动添加 `.cpp `后缀）。如无此参数则以上一次设置的 `out` 文件为准。此参数与 `/f` 冲突，优先级低于 `/f`。

`/af <ans_file>`    指定 `ans` 文件（后缀不为 `.cpp `自动添加 `.cpp `后缀）。如无此参数则以上一次设置的 `ans` 文件为准。此参数与 `/f` 冲突，优先级低于 `/f`。

`/t <time>`    修改默认运行时间限制（单位 ms）。

### judge

`judge [/f <file>] [/c <chk_file>] [/d data...] [/is <infile_suf>] [/os <outfile_suf>] [/t <time>]`

#### 描述

给定数据文件和源代码，从数据文件中找到指定后缀名的输入输出文件并组成数据点，得到源代码的所有结果。所有文件编译时定义宏 `JUDGING`。数据会存放在 `data/` 目录下。

#### 参数列表

`/f <file>`    指定源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的源文件为准。

`/c <chk_file>`    指定 `checker` 的文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的源文件为准。

`/d data...`    指定数据点文件。如无此参数将不会开始评测，仅视为设置参数。

`/is <infile_suf>`    指定输入文件后缀名。

`/os <outfile_suf>`    指定输出文件后缀名。

`/t <time>`    修改默认运行时间限制（单位 ms）。

### compile

`compile [[/r <file>] | [/t <file>] | [/f file...]] [/o compile_arg] [/p run_arg]`

#### 描述

给定源文件和编译参数，编译源文件。

#### 参数列表

`/r <file>`    给定源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀），编译并运行。此参数与 `/f` 冲突，优先级高于 `/f`。添加此参数将没有输出。

`/t <file>`    给定源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀），运行该源文件对应生成的可执行文件。此参数与 `/f` 冲突，优先级高于 `/f`。添加此参数将没有输出。

`/f file...`    给定多个编译源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。

`/o compile_arg`    给定编译参数。

`/p run_arg`    给定运行参数。

### config

`config [[/s [key [value | %{RESET}%]]] | [/f [key [value | %{RESET}%]]]]`

#### 描述

查看、修改配置

#### 参数列表

`/s [key [value]]`    如未给出 `key`，输出 `settings.json` 文件。如给出 `key` 未给出 `value`，输出 `key` 的值。如 `key` 后追加 `%{RESET}%`，则将该项重置为默认值，默认值从 `%{FILE_PATH}%/files/settings.json` 中读取。如 `key` 后追加 `value`，则修改 `key` 的值为 `value`。`key` 中不同层的键值用 `/` 分隔。

`/f [num [value]]`    如未给出 `num`，输出 `file.json` 文件。如给出 `num` 未给出 `value`，输出编号为 `num` 的文件的值。如 `num` 后追加 `%{RESET}%`，则将该文件重置为默认值，默认值从 `%{FILE_PATH}%/files/file.json` 中读取。如 `num` 后追加 `value`，则将该文件设为 `value`。

## 卸载

使用 `orita clear` 删除所有配置文件，再删除 `Orita` 目录下的源文件即可。

如不再需要 CMake、GCC、MSVC 等请自行卸载。

## 依赖项

该项目使用了以下第三方库：

- [nlohmann/json](https://github.com/nlohmann/json)
- [gabime/spdlog](https://github.com/gabime/spdlog)
- [ikalnytskyi/termcolor](https://github.com/ikalnytskyi/termcolor)
- [pocoproject/poco](https://github.com/pocoproject/poco)

## 致谢

本项目由 [Sukwants](https://github.com/Sukwants) 及 [Pond Ink](https://pond.ink/) 团队提供技术支持。

[![0](https://avatars.githubusercontent.com/u/95968907?s=64&v=4)](https://github.com/Sukwants)
[<img src="https://pond.ink/images/avatar.png" height=64x width=64x alt>](https://pond.ink/)

相关项目：
- [vscode-Orita](https://github.com/2745518585/vscode-Orita) - VSCode extension for Orita
- [Atiro](https://github.com/Sukwants/Atiro) - Useless OI Tools
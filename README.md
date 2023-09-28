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

使用 `orita /r`(Windows) 或 `orita -r`(Linux) 命令初始化并清空配置。

## 用法

### 参数系统

Windows 系统下使用 DOS 风格命令行参数，Linux 下使用 Unix 风格命令行参数。以下示例中均使用 DOS 风格。

### 内置文件

Orita 内置了一些文件来方便使用，其初始化后位于配置文件目录中。

`0.cpp`：空，总是返回 $0$。

`1.cpp`：文件比较器，三个参数分别为 `in` `out` `ans` 文件，返回 `out` 和 `ans` 忽略行末空格和文末换行的比较结果。

### 文件名替换

形如 `%[0-999]` 将替换为 `file.json` 中对应编号的文件名，如 `%1` 表示编号为 $1$ 的文件名。

文件名中的 `%...%` 替换为环境变量 `...`。匹配环境变量：

- `APPDATA_PATH`: Windows 下为 `%APPDATA%/Orita`，Linux 下为 `%HOME%/.Orita`。
- `FILE_PATH`: 源代码所在目录。
- `RUNNING_PATH`: 运行目录。
- `OS_NAME`：操作系统名称，Windows 下为 `windows`，Linux 下为 `linux`。
- 否则返回系统环境变量 `...`。

文件名中的 `%%` 将替换为 `%`。

### 设置系统

设置文件名为 `settings.json`，分为三种：

1. 默认设置文件，位于 `%{FILE_PATH}%/files/%{OS_NAME}%/settings.json`。
2. 全局设置文件，位于 `%{APPDATA_PATH}%/settings.json`。
3. 局部设置文件，位于 `.orita/settings.json`。

从上到下优先级递增，单次运行有效局部设置文件为 `%{RUNNING_PATH%` 自身和祖先目录下的 `.orita/settings.json` 文件，目录层数由浅到深优先级递增。优先级从高到低匹配，如果当前设置值为 `null` 则查询优先级次于当前的文件。

凡是识别到当前目录下存在局部设置文件或通过命令修改了局部设置文件的目录，都会在程序结束时输出最新设置文件，没有设置文件且没有修改的目录则不会输出。

## 命令

### orita

`orita [/help] [/reset] [/clear]`

`/help`     帮助信息。

`/reset`    重置配置。

`/clear`    清空配置。

### run

`orita run [/help] [/file=file] [/checker=file] [/time=time]`

运行给定的文件并重定向输入，与输出数据比较。所有文件编译时定义宏 `JUDGING`。数据会存放在 `settings.data.data_dir/` 目录下。

`/help`             帮助信息。

`/file=file`        指定源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的源文件为准。

`/checker=file`     指定评测文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的源文件为准。

`/time=time`        修改默认运行时间限制（单位 ms）。

### chdata

`orita chdata [/help] [/ifile[=file]] [/ofile[=file]] [/time=time]`

用于修改 `run` 命令的输入输出数据。

`/help`             帮助信息。

`/ifile[=file]`     指定输入数据所在文件，未指定值从标准输入中读取。

`/ofile[=file]`     指定输出数据所在文件，未指定值从标准输入中读取。

`/t <time>`         修改默认运行时间限制（单位 ms）。

### check

`orita check [/help] [/ifile=file] [/ofile=file] [/afile=file] [/checker=file] [/num=num] [/time=time]`

给定数据生成器、标准代码和源代码，进行对拍。所有文件编译时定义宏 `JUDGING`。数据会存放在 `settings.data.data_dir/` 目录下。

`/help`             帮助信息。

`/ifile=file`       指定数据生成器（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的文件为准。

`/ofile=file`       指定标准代码（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的文件为准。

`/afile=file`       指定源代码（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的文件为准。

`/checker=file`     指定评测文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的源文件为准。

`/num=num`          对拍次数。如无此参数不会开始对拍，仅视为设置参数。

`/time=time`        修改默认运行时间限制（单位 ms）。

### judge

`orita judge [data] [/help] [/file=file] [/checker=file] [/time=time] [/isuf=suf] [/osuf=suf]`

给定数据文件和源代码，从数据文件中找到指定后缀名的输入输出文件并组成数据点，得到源代码的所有结果。所有文件编译时定义宏 `JUDGING`。数据会存放在 `data/` 目录下。

`data`              指定数据文件。如无此参数将不会开始评测，仅视为设置参数。

`/help`             帮助信息。

`/file=file`        指定源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的源文件为准。

`/checker=file`     指定评测文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的源文件为准。

`/time=time`        修改默认运行时间限制（单位 ms）。

`/isuf=suf`         指定输入文件后缀名，默认为 `.in`。

`/osuf=suf`         指定输出文件后缀名，默认为 `.out`。

### compile

`orita compile [file] /help [/run] [/trun] [/carg=args] [/arg=args]`

给定源文件和编译参数，编译源文件。

`file`              指定源文件。

`/help`             帮助信息。

`/r <file>`         指定源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀），编译并运行。此参数与 `/f` 冲突，优先级高于 `/f`。添加此参数将没有输出。

`/t <file>`         指定源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀），运行该源文件对应生成的可执行文件。此参数与 `/f` 冲突，优先级高于 `/f`。添加此参数将没有输出。

`/f file...`        指定多个编译源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。

`/carg=args`        指定编译参数。

`/arg=args`         指定运行参数。

### config

`config [key [value]] [/help] [/settings] [/files]`

#### 描述

查看、修改配置

#### 参数列表

`key`           指定键。

`value`         指定值。

`/help`         帮助信息。

`/settings`     如未给出 `key`，输出 `settings.json` 文件。如给出 `key` 未给出 `value`，输出 `key` 的值。如 `key` 后追加 `%{RESET}%`，则将该项重置为默认值，默认值从 `%{FILE_PATH}%/files/%{OS_NAME}%/settings.json` 中读取。如 `key` 后追加 `value`，则修改 `key` 的值为 `value`。`key` 中不同层的键值用 `/` 分隔。

`/files`        如未给出 `num`，输出 `file.json` 文件。如给出 `num` 未给出 `value`，输出编号为 `num` 的文件的值。如 `num` 后追加 `%{RESET}%`，则将该文件重置为默认值，默认值从 `%{FILE_PATH}%/files/%{OS_NAME}%/file.json` 中读取。如 `num` 后追加 `value`，则将该文件设为 `value`。

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

本项目由 [Sukwants](https://github.com/Sukwants)、[Pond Ink](https://pond.ink/) 团队和 [syysongyuyang](https://github.com/syysongyuyang) 提供技术支持。

[![0](https://avatars.githubusercontent.com/u/95968907?s=64&v=4)](https://github.com/Sukwants)
[<img src="https://pond.ink/images/avatar.png" height=64x width=64x alt>](https://pond.ink/)
[<img src="https://avatars.githubusercontent.com/u/123732645" height=64x width=64x alt>](https://github.com/syysongyuyang)

相关项目：
- [vscode-Orita](https://github.com/2745518585/vscode-Orita) - VSCode extension for Orita
- [Atiro](https://github.com/Sukwants/Atiro) - Useless OI Tools
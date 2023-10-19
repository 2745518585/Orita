zh-CN | [en-CN](./README_en-CN.md)

# Orita

[Orita](https://github.com/2745518585/Orita)

Orita 是一款由 [赵悦岑](https://github.com/2745518585/) 开发的 OI 工具，主要使用 C++ 编写，包含评测、压力测试、数据生成等功能。

[vscode-Orita](https://github.com/2745518585/vscode-Orita)

Orita 的配套 VSCode 扩展。

## 安装

### 构建

在安装 Orita 前，需要保证环境为 Windows 或 Linux 环境，计算机上需要安装以下应用程序：

- [CMake](https://cmake.org/) (3.15+)

同时需要安装 GCC 11.4+ 或 MSVC 2022+。

对于 Windows 计算机，请下载并安装以下应用程序：

- [CMake](https://cmake.org/)
- [MinGW](https://www.mingw-w64.org/downloads/)
- [Visual Studio](https://visualstudio.microsoft.com/downloads/)

对于 Linux 计算机，请运行以下命令安装 CMake 和 GCC：

```shell
$ sudo apt-get install cmake
$ sudo apt-get install g++
```

安装完成后，请使用以下命令获取 Orita 源代码：

```shell
$ git clone https://github.com/2745518585/Orita
$ git submodule init
$ git submodule update
```

在 `Orita/` 目录中使用以下命令编译源代码：

```shell
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

### 下载

可以在 [GitHub](https://github.com/2745518585/Orita/releases) 上查找最新的发行版，下载对应平台的已编译文件压缩包。

### 初始化

请确保可执行文件目录 `bin/bin/` 中的入口文件 `orita.exe` 或 `orita` 可以被全局调用，可以任意移动入口文件的位置，可以任意修改名称来修改入口命令名。

如果使用 CMake 生成，它会自动输出可执行文件的位置。如果移动可执行文件后，请执行可执行文件所在目录下的 `path.bat` 或 `path.sh`。

为了正常使用 Orita，请确保计算机上安装了支持 C++14 的 C++ 编译器 g++，并且可以在控制台中全局调用。

使用 `orita /r`(Windows) 或 `orita -r`(Linux) 命令来初始化并清空配置。

## 用法

### 参数系统

在 Windows 下使用 DOS 风格的命令行参数，在 Linux 下使用 Unix 风格的命令行参数。以下示例均使用 DOS 风格。

### 内置文件

Orita 预置了一些文件以方便使用，这些文件在初始化后位于配置文件目录中。

`0.cpp`: 空文件，总是返回 $0$。

`1.cpp`: 文件比较器，三个参数分别为 `in` `out` `ans` 文件，返回 `out` 和 `ans` 忽略行末空格和文末换行的比较结果。

### 环境变量替换

所有从命令行参数或配置文件读入的数据都将进行环境变量替换，从标准输入读入的数据则不会进行替换。


* 文件名中的 `%...%` 替换为环境变量 `...`。程序将依次匹配以下环境变量：
  - 形如 `%*[0-999]%` 的表达式，将会替换为 `file.json` 中对应编号的文件名，例如 `%*1%` 表示编号为 $1$ 的文件名。
  - 形如 `%....%` 的表达式，将会替换为设置系统中对应值，例如 `%.data.data_dir%` 表示设置中 `/data/data_dir` 的值。
  - `{APPDATA_PATH}`: Windows 下为 `%APPDATA%/Orita`，Linux 下为 `%HOME%/.Orita`。
  - `{FILE_PATH}`: 可执行文件所在目录。
  - `{RUNNING_PATH}`: 运行目录。
  - `{OS_NAME}`: 操作系统名称。
  - 否则返回系统环境变量 `...`。

- 文件名中的 `%%` 会被替换为 `%`。

### 设置系统

设置文件名为 `settings.json`，有三个层级：

1. 默认设置文件，位于 `%{FILE_PATH}%/files/%{OS_NAME}%/settings.json`。
2. 全局设置文件，位于 `%{APPDATA_PATH}%/settings.json`。
3. 局部设置文件，位于 `.orita/settings.json`。

这三个层级设置文件从上到下优先级递增。单次运行有效局部设置文件为 `%{RUNNING_PATH}%` 自身和祖先目录下的 `.orita/settings.json` 文件，目录层数由浅到深优先级递增。

查询和修改设置时默认优先级从高到低匹配，如果当前设置值为 `null` 则查询优先级次于当前的文件。

局部设置文件中的相对路径将在文件对应的目录下解析。凡是识别到当前目录下存在局部设置文件或通过命令修改了局部设置文件的目录，都会在程序结束时输出最新设置文件，没有设置文件且没有修改的目录则不会输出。

如需要用一个字符串表示设置中的一个对象，请使用 `.` 分隔不同层级的目录，如 `.data.data_dir`。下文中形如 `%.data.data_dir%` 即代表设置中对应的对象。

设置文件可以存储在全局设置文件的 `.~list` 位置，并且可以加载到当前目录的配置文件。

$\color{red}{\text{注意}}$：设置中的 `.max_process_num` 和 `.max_thread_num` 分别表示最大进程数和最大线程数的量级，请根据 CPU 并行性能、内存及磁盘读写速率调整参数，否则可能因为 CPU 占用过高导致系统崩溃，或磁盘读写延迟过高导致程序异常。

### 命令匹配

将以第一个参数为键于 `%.commands...%` 匹配命令，命令名称见命令列表，匹配列表默认为：
```json
{
  "c": "compile",
  "ch": "check",
  "chd": "chdata",
  "com": "command",
  "con": "config",
  "j": "judge",
  "r": "run"
}
```
匹配失败则以第一个参数作为命令，无参数或没有对应命令则进入入口命令。

## 命令

### orita

`orita [[/help] | [/reset] | [/clear]]`

命令行工具的入口命令。

`/help`: 显示帮助信息。

`/reset`: 重置配置。

`/clear`: 清空配置。

### run

`orita run [/help] [/file=file] [/checker=file] [/time=time]`

运行指定的文件并重定向输入，然后与输出数据进行比较。所有文件在编译时都会追加参数 `%.data.compile_argu%`。数据将存储在 `%.data.data_dir%/` 目录下。

`/help`: 显示帮助信息。

`/file=file`: 指定源文件（如果没有指定后缀为 `.cpp`，将自动添加 `.cpp` 后缀）。如果没有此参数，则将使用上一次设置的源文件。

`/checker=file`: 指定评测文件（如果没有指定后缀为 `.cpp`，将自动添加 `.cpp` 后缀）。如果没有此参数，则将使用上一次设置的评测文件。

`/time=time`: 修改默认的运行时间限制（单位：毫秒）。

### chdata

`orita chdata [/help] [/ifile[=file]] [/ofile[=file]] [/time=time]`

用于修改 `run` 命令的输入输出数据。

`/help`: 显示帮助信息。

`/ifile[=file]`: 指定输入数据的文件（如果没有指定将从标准输入读取）。

`/ofile[=file]`: 指定输出数据的文件（如果没有指定将从标准输入读取）。

`/time=time`: 修改默认的运行时间限制（单位：毫秒）。

### check

`orita check [/help] [/ifile=file] [/ofile=file] [/afile=file] [/checker=file] [/num=num] [/time=time] [/multithread]`

使用数据生成器、标准代码和源代码进行对拍。所有文件在编译时都会追加参数 `%.data.compile_argu%`。数据将存储在 `%.data.data_dir%/` 目录下。

`/help`: 显示帮助信息。

`/ifile=file`: 指定数据生成器（如果没有指定后缀为 `.cpp`，将自动添加 `.cpp` 后缀）。如果没有此参数，则将使用上一次设置的数据生成器。

`/ofile=file`: 指定标准代码（如果没有指定后缀为 `.cpp`，将自动添加 `.cpp` 后缀）。如果没有此参数，则将使用上一次设置的标准代码。

`/afile=file`: 指定源代码（如果没有指定后缀为 `.cpp`，将自动添加 `.cpp` 后缀）。如果没有此参数，则将使用上一次设置的源代码。

`/checker=file`: 指定评测文件（如果没有指定后缀为 `.cpp`，将自动添加 `.cpp` 后缀）。如果没有此参数，则将使用上一次设置的评测文件。

`/num=num`: 对拍次数。如果没有此参数，则不会开始对拍，仅作为设置参数。

`/time=time`: 修改默认的运行时间限制（单位：毫秒）。

`/multithread`: 启用多线程。启用多线程会导致单个测试得到的程序运行时间增加数倍，并和运行的进程数及计算机并行性能相关，因此得到的 `TLE` 结果不一定准确。

### judge

`orita judge [data] [/help] [/file=file] [/checker=file] [/time=time] [/isuf=suf] [/osuf=suf]`

对于给定的数据文件和源代码，从数据文件中找到具有指定后缀名的输入输出文件并生成数据点，然后获取源代码的所有结果。所有文件在编译时都会追加参数 `%.data.compile_argu%`。数据将存储在 `%.data.data_dir%/` 目录下。

`data`: 指定数据文件。如果没有此参数，将不会开始评测，仅作为设置参数。

`/help`: 显示帮助信息。

`/file=file`: 指定源文件（如果没有指定后缀为 `.cpp`，将自动添加 `.cpp` 后缀）。如果没有此参数，则将使用上一次设置的源文件。

`/checker=file`: 指定评测文件（如果没有指定后缀为 `.cpp`，将自动添加 `.cpp` 后缀）。如果没有此参数，则将使用上一次设置的评测文件。

`/time=time`: 修改默认的运行时间限制（单位：毫秒）。

`/isuf=suf`: 指定输入文件的后缀名，默认为 `.in`。

`/osuf=suf`: 指定输出文件的后缀名，默认为 `.out`。

### compile

`orita compile [file] /help [[/run] | [/trun]] [/carg=args] [/arg=args]`

编译指定的源文件和编译参数。

`file`: 指定源文件。

`/help`: 显示帮助信息。

`/run`: 指定源文件（如果没有指定后缀为 `.cpp`，将自动添加 `.cpp` 后缀），编译并运行，使用此参数将不会有编译信息输出。

`/trun`: 指定源文件（如果没有指定后缀为 `.cpp`，将自动添加 `.cpp` 后缀），运行与该源文件对应的可执行文件，使用此参数将不会有编译信息输出。

`/carg=args`: 指定编译参数。

`/arg=args`: 指定运行参数。

### config

`config [key [value]] [/help] [[/settings [/global] [/local] [[/add=key] | [/load=key] | [/merge=key]]] | [/files]]`

查看或修改配置。

`key`: 指定键。

`value`: 指定值。

`/help`: 显示帮助信息。

`/settings`: 如果未提供 `key`，则输出 `settings.json` 文件。如果提供 `key` 但未提供 `value`，则输出 `key` 的值。如果在 `key` 后追加 `%{RESET}%`，则将该项重置为默认值，默认值将从 `%{FILE_PATH}%/files/settings.json` 中读取。如果在 `key` 后追加 `value`，则将 `key` 的值修改为 `value`。

`/global`: 指定为全局设置。

`/local`: 指定为当前目录的局部设置。

`/add=key`: 上传设置至名为 `key` 的设置文件。

`/load=key`: 加载名为 `key` 的设置文件至当前目录的局部设置。

`/merge=key`: 将名为 `key` 的设置文件合并（覆盖不匹配）至当前目录的局部设置。

`/files`: 如果未提供 `num`，则输出 `file.json` 文件。如果提供 `num` 但未提供 `value`，则输出编号为 `num` 的文件的值。如果在 `num` 后追加 `%{RESET}%`，则将该文件重置为默认值，默认值将从 `%{FILE_PATH}%/files/%{OS_NAME}%/file.json` 中读取。如果在 `num` 后追加 `value`，则将该文件的值设置为 `value`。

### command

`command [commands]`

执行替换环境变量后的 commands。

`/help`: 显示帮助信息。

## 卸载

要卸载 Orita，请使用 `orita clear` 命令删除所有配置文件，然后删除 `Orita` 目录下的源文件即可。

如不再需要 CMake、GCC、MSVC 等请自行卸载。

## 依赖项

该项目使用了以下第三方库：

- Lohmann, N. (2022). JSON for Modern C++ (Version 3.11.2) [Computer software]. https://github.com/nlohmann
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
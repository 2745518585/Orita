zh-CN | [en-CN](./README_en-CN.md)

# Orita

[Orita](https://github.com/2745518585/Orita)

Orita 是一款由 [赵悦岑](https://github.com/2745518585/) 开发的 OI 工具，主要使用 C++ 编写，包含评测、对拍、数据生成等功能。

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
  - 形如 `%....%` 的表达式，将会替换为设置系统中对应值，例如 `%.data.data_dir%` 表示设置中 `/data/data_dir` 的值。如值为 `string` 类型则直接替换，否则序列化后替换。
  - 形如 `%#...%` 的表达式，将会替换为传入参数中对应值，例如 `%#file%` 表示参数中 `file` 的值。
  - `{APPDATA_PATH}`: Windows 下为 `%APPDATA%/Orita`，Linux 下为 `%HOME%/.Orita`。
  - `{FILE_PATH}`: 可执行文件所在目录。
  - `{RUNNING_PATH}`: 运行目录。
  - `{OS_NAME}`: 操作系统名称。
  - `{TERMINAL_WIDTH}`: 终端宽度。
  - 否则返回系统环境变量 `...`。

- 文件名中的 `%%` 会被替换为 `%`。

### 设置系统

设置文件名为 `settings.json`，有三个层级：

1. 默认设置文件，位于 `%{FILE_PATH}%/files/settings.json`。
2. 全局设置文件，位于 `%{APPDATA_PATH}%/settings.json`。
3. 局部设置文件，位于 `.orita/settings.json`。

这三个层级设置文件从上到下优先级递增。单次运行有效局部设置文件为 `%{RUNNING_PATH}%` 自身和祖先目录下的 `.orita/settings.json` 文件，目录层数由浅到深优先级递增。

查询和修改设置时默认优先级从高到低匹配，如果当前设置值为 `null` 或值不合法则查询优先级次于当前的文件。

设置中 `%{SETTINGS_PATH}%` 将优先替换为设置文件对应目录（先于环境变量替换）。凡是识别到当前目录下存在局部设置文件或通过命令修改了局部设置文件的目录，都会在程序结束时输出最新设置文件，没有设置文件且没有修改的目录则不会输出。

如需要用一个字符串表示设置中的一个对象，请使用 `.` 分隔不同层级的目录，如 `.data.data_dir`。下文中形如 `%.data.data_dir%` 即代表设置中对应的对象。

设置文件可以存储在全局设置文件的 `.~list` 位置，并且可以加载到当前目录的配置文件。

#### 设置信息

- `commands`: 命令匹配列表。
- `compiler`: 编译器相关。
  - `argu`: 编译选项。
  - `command`: 调用的编译器路径。
  - `skip_compiled`: 是否启用当源文件不比可执行文件更新时跳过编译。
  - `time_limit`: 编译时限。
  - `try_times`: 编译超时后重试次数。
- `data`: 评测相关。
  - `ans_args`: 传入 `ans` 的参数列表。提供参数 `infile`,`outfile`,`ansfile`,`chkfile` 分别为输入、输出、答案、比较信息文件路径。
  - `ansfile`: 默认答案数据文件。
  - `chk_args`: 传入 `checker` 的参数列表。提供参数 `infile`,`outfile`,`ansfile`,`chkfile` 分别为输入、输出、答案、比较信息文件路径。
  - `chk_exit_code`: `checker` 在遇到答案错误时的返回值，在十进制下使用正则表达式匹配。
  - `chk_outputs`: 值为 `"on"` 时启用 `%*1%` 默认比较器向控制台输出信息。
  - `chkfile`: 默认比较信息文件。
  - `compile_argu`: 评测编译选项。
  - `data_dir`: 数据文件存放目录。
  - `data_file`: 批量评测或对拍后输出数据文件位置，分别添加 `.in`、`.out`、`.ans`、`.txt` 后缀。提供参数 `testcase_name` 数据点名称、`result` 评测结果、`short_result` 评测结果缩写、`info` 测试点信息（解释见*程序评测*）、`runned_sum` 已评测数量、`outputed_sum` 已输出数量。
  - `in_args`: 传入 `data_maker` 的参数列表。提供参数 `infile`,`outfile`,`ansfile`,`chkfile` 分别为输入、输出、答案、比较信息文件路径，参数 `seed` 为该测试点随机数种子，参数 `testcase_name` 为测试点名称。
  - `infile`: 默认输入数据文件。
  - `info_pre`: 测试点信息前缀。
  - `out_args`: 传入 `std` 的参数列表。提供参数 `infile`,`outfile`,`ansfile`,`chkfile` 分别为输入、输出、答案、比较信息文件路径。
  - `outfile`: 默认输出数据文件。
  - `time`: 评测时间限制。
- `exefile`: 可执行文件路径。提供参数 `file` 为源文件路径去除后缀，`filename` 为源文件名去除后缀，`filepath` 为源文件所在目录。
- `max_process_num`: 最大进程数量级。
- `max_thread_num`: 最大线程数量级。
- `runtime_limit`: 子进程运行时间限制。
- `show_file_info`: 是否在评测时展示文件信息。
- `~list`: 设置列表。

### 子进程环境

所有子进程均包含主进程环境变量，并额外定义以下环境变量：

- 文件环境变量，键名形如 `file[0-999]`。
- 设置环境变量，键名形如 `....`。
- 内置环境变量。
- 批量评测且未启用多线程时，`runned_sum` 已评测数量，`outputed_sum` 已输出数量。

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

### 线程与进程管理

> [!WARNING]
> $\color{red}{\text{注意}}$：设置中的 `%.max_process_num%` 和 `%.max_thread_num%` 分别表示最大进程数和最大线程数的量级，请根据 CPU 并行性能、内存及磁盘读写速率调整参数，否则可能因为 CPU 占用过高导致系统崩溃，或磁盘读写延迟过高导致程序异常。

### 程序评测

评测时同时使用 `%.compiler.argu%` 和 `%.data.compile_argu%` 编译选项，默认含有宏 `JUDGING`。

评测时标准输入输出、标准错误输出（`stderr` 指向控制台）均需要 `flush` 操作才会进行推送，建议使用 `iostream` 或使用 `orita::auto_flush()` 自动推送输出，从文件读入自动在文件结束后关闭管道写入端，从控制台读入建议在结束时键入 `EOF`。如需在程序非正常退出时依然保留已有输出（包括输出到文件和控制台），也需要进行 `flush` 操作。

评测时任意程序可以向比较信息文件输出首行输出形如 `%.data.info_pre%{...}` 的字符串，评测结束后将会读取 `{...}` 中的内容作为测试点信息。

评测后得到的数据文件会存放至 `%.data.data_dir%` 下。

### 其他

所有命令在指定 C++ 源文件时默认后缀为 `cpp`，后缀不为 `cpp` 自动添加 `cpp` 后缀，得到的可执行文件为将源文件作为参数传入后 `%.exefile%` 的值。

## 命令

### orita

`orita [[/help] | [/reset] | [/clear] | [/path]]`

命令行工具的入口命令。

`/help`: 显示帮助信息。

`/reset`: 重置配置。

`/clear`: 清空配置。

`/path`: 获取文件路径。

### run

`orita run [/help] [/file=file] [/checker=file] [/time=time] [/dorecompile]`

运行指定的文件并重定向输入，然后与输出数据进行比较。

`/help`: 显示帮助信息。

`/file=file`: 指定源文件。如果没有此参数，则将使用上一次设置的源文件。

`/checker=file`: 指定评测文件。如果没有此参数，则将使用上一次设置的评测文件。

`/time=time`: 修改默认的运行时间限制（单位：毫秒）。

`/dorecompile`: 强制重新编译。

### chdata

`orita chdata [/help] [/ifile[=file]] [/ofile[=file]] [/time=time]`

用于修改 `run` 命令的输入输出数据。

`/help`: 显示帮助信息。

`/ifile[=file]`: 指定输入数据的文件（如果没有指定将从标准输入读取）。

`/ofile[=file]`: 指定输出数据的文件（如果没有指定将从标准输入读取）。

`/time=time`: 修改默认的运行时间限制（单位：毫秒）。

### check

`orita check [/help] [/ifile=file] [/ofile=file] [/afile=file] [/checker=file] [/num=num [/multithread]] [/time=time] [/dorecompile]`

使用数据生成器、标准代码和源代码进行对拍。测试点名称在一般情况下为编号，开启多线程后为空。

`/help`: 显示帮助信息。

`/ifile=file`: 指定数据生成器。如果没有此参数，则将使用上一次设置的数据生成器。

`/ofile=file`: 指定标准代码。如果没有此参数，则将使用上一次设置的标准代码。

`/afile=file`: 指定源代码。如果没有此参数，则将使用上一次设置的源代码。

`/checker=file`: 指定评测文件。如果没有此参数，则将使用上一次设置的评测文件。

`/num=num`: 对拍次数。如果没有此参数，则不会开始对拍，仅作为设置参数。

`/time=time`: 修改默认的运行时间限制（单位：毫秒）。

`/multithread`: 启用多线程。启用多线程会导致单个测试得到的程序运行时间增加数倍，并和运行的进程数及计算机并行性能相关，因此得到的 `TLE` 结果不一定准确。

`/dorecompile`: 强制重新编译。

### judge

`orita judge [data] [/help] [/file=file] [/checker=file] [/time=time] [/isuf=suf] [/osuf=suf] [/ofile=file] [/multithread] [/dorecompile]`

对于给定的数据文件和源代码，从数据文件中找到具有指定后缀名的输入输出文件并生成数据点，然后获取源代码的所有结果。测试点名称在一般情况下为输入输出文件名，开启多线程后为空。

`data`: 指定数据文件。如果没有此参数，将不会开始评测，仅作为设置参数。

`/help`: 显示帮助信息。

`/file=file`: 指定源文件。如果没有此参数，则将使用上一次设置的源文件。

`/checker=file`: 指定评测文件。如果没有此参数，则将使用上一次设置的评测文件。

`/time=time`: 修改默认的运行时间限制（单位：毫秒）。

`/isuf=suf`: 指定输入文件的后缀名，默认为 `.in`。

`/osuf=suf`: 指定输出文件的后缀名，默认为 `.out`。

`/ofile=file`: 指定标准输出文件，当未找到输出文件时使用此源文件输出为输出文件。

`/multithread`: 启用多线程。启用多线程会导致单个测试得到的程序运行时间增加数倍，并和运行的进程数及计算机并行性能相关，因此得到的 `TLE` 结果不一定准确。

`/dorecompile`: 强制重新编译。

### compile

`orita compile [file] [/help] [[/run] | [/trun]] [/carg=args] [/arg=args] [/dorecompile]`

编译指定的源文件和编译参数。

`file`: 指定源文件。

`/help`: 显示帮助信息。

`/run`: 指定源文件，编译并运行，使用此参数将不会有编译信息输出。

`/trun`: 指定源文件，运行与该源文件对应的可执行文件，使用此参数将不会有编译信息输出。

`/carg=args`: 指定编译参数。

`/arg=args`: 指定运行参数。

`/dorecompile`: 强制重新编译。

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

`/files`: 如果未提供 `num`，则输出 `file.json` 文件。如果提供 `num` 但未提供 `value`，则输出编号为 `num` 的文件的值。如果在 `num` 后追加 `%{RESET}%`，则将该文件重置为默认值，默认值将从 `%{FILE_PATH}%/files/file.json` 中读取。如果在 `num` 后追加 `value`，则将该文件的值设置为 `value`。

### command

`command [commands]`

执行替换环境变量后的 commands。

`/help`: 显示帮助信息。

## 头文件

头文件默认位于 `${FILE_PATH}%/orita.hpp`，此目录默认添加至编译选项包含路径中，可通过 `#include"orita.hpp"` 直接引用。需要 C++14 及以上标准才可通过编译。

所有函数、变量、类均位于 `namespace orita` 中。

#### `std::mt19937 rd`

`std::mt19937` 类型随机数生成器。

#### `void `register_rnd`(int argc, char **argv, unsigned int pos = 1U)`

用于注册随机数生成器的种子。

- **参数**: 
  - `argc`: 命令行参数的数量。
  - `argv`: 命令行参数的数组。
  - `pos`: 种子所在的参数位置。

#### `void register_rnd(unsigned seed)`

用于注册指定的随机数种子。

- **参数**: 
  - `seed`: 要注册的随机数种子。

#### `unsigned long long rnd()`

生成一个无符号长整型随机数。

- **返回值**: 生成的随机数。

#### `template<class Ty> std::enable_if<std::is_integral<Ty>::value, Ty>::type rnd(const Ty &lim)`

当传入参数类型为整数时，生成一个范围在 `[0, lim)` 之间的随机数。

- **参数**: 
  - `lim`: 随机数的上限。
- **返回值**: 生成的随机数。

#### `long long rnd(const long long &lim)`

生成一个范围在 `[0, lim)` 之间的长整型随机数。

- **参数**: 
  - `lim`: 随机数的上限。
- **返回值**: 生成的随机数。

#### `template<class Ty> std::enable_if<std::is_integral<Ty>::value, Ty>::type rnd(const Ty &llim,const Ty &ulim)`

当传入参数类型为整数时，生成一个范围在 `[llim, ulim]` 之间的随机数。

- **参数**: 
  - `llim`: 随机数的下限。
  - `ulim`: 随机数的上限。
- **返回值**: 生成的随机数。

#### `long long rnd(const long long &llim,const long long &ulim)`

生成一个范围在 `[llim, ulim]` 之间的长整型随机数。

- **参数**: 
  - `llim`: 随机数的下限。
  - `ulim`: 随机数的上限。
- **返回值**: 生成的随机数。

#### `template<class lTy, class uTy> class rdl<lTy, uTy>`

指定上限和下限，生成随机数。

注意，C++14 及以下无法推导类模板，需显式定义模板。

- **成员**
  - `lTy llim`: 随机数下限。
  - `uTy ulim`: 随机数上限。
  - `auto rdl<lTy, uTy>::operator()() const`: 返回 `rnd(llim,ulim)` 的结果。
- **构造函数**
  - `rdl()`: 默认构造函数。
  - `rdl<lTy, uTy>::rdl(const uTy &lim)`: 指定上限。
  - `rdl(const lTy &llim, const uTy &ulim)`: 指定下限和上限。

#### `template<class Ty1, class Ty2> class pr<Ty1, Ty2>`

带分隔符的键值对。

- **基类**: `std::pair<Ty1,Ty2>`。
- **成员**: 
  - `std::string sep`: 分隔符。
- **构造函数**: 
  - `pr(const Ty1 &first, const Ty2 &second, const std::string &_sep = " ")`: 用于初始化键值对和分隔符。
  - `pr(const std::pair<Ty1, Ty2> &_pair, const std::string &_sep = " ")`: 从现有键值对和分隔符初始化。

此类通过基类 `std::pair` 进行结构化绑定的解构。

#### `template<class Ty1, class Ty2> std::ostream &operator<<(std::ostream &out, const pr<Ty1, Ty2> &pr)`

输出键值对。

- **参数**: 
  - `out`: 输出流。
  - `pr`: 键值对。
- **返回值**: 生成的随机数。

#### `template<class Ty1, class Ty2> struct _NEQ<Ty1, Ty2>`
#### `template<class Ty1, class Ty2> struct _LES<Ty1, Ty2>`
#### `template<class Ty1, class Ty2> struct _GRE<Ty1, Ty2>`
#### `template<class Ty1, class Ty2> struct _LOE<Ty1, Ty2>`
#### `template<class Ty1, class Ty2> struct _GOE<Ty1, Ty2>`

- **成员**: 
  - `bool operator()(const Ty1 &s1,const Ty2 &s2) const `: 返回两数的比较结果，分别为不等于、小于、大于、小于等于、大于等于。

#### `rnd_pair(...,const std::string &seq)`

生成满足比较函数的随机数对。

比较函数可以是函数作为参数传入，也可以是类或结构体作为模板传入。传入的类或结构体需可以调用 `operator()` 并将两数作为参数传入，返类型为 `bool`。（C++14 及以下无法推导类模板，传入的类需可接受支持无模板、一个模板（两个数类型相同时）或两个模板（分别为两个数的类型））

对于生成随机数对的生成器，可以直接指定上限和下限，也可以指定一个或两个生成器。生成器为类或结构体的实例或 lambda 表达式，需可以无参数调用 `operator()`，返类型为 `bool`。当指定了两个参数时，依据能否调用 `operator()` 判断作为生成器还是作为随机数范围使用。

- **参数**: 
  - `seq`: 分隔符。
- **返回值**: 生成的随机数对。

**用法示例**: 
- `rnd_pair(1,10,[&](auto x1,auto x2){return x1<x2;});`
- `rnd_pair<_LES>(1,10);`
- `rnd_pair<std::less>(1,1e5);`
- `rnd_pair<std::less<int>>(1,1e5);`
- `rnd_pair<_LES>([&](){return rnd(1,10);});`
- `rnd_pair<_LES>(rdl<int,int>(1,10));`
- `rnd_pair<_LES>(rdl<int,int>(1,10),rdl<int,int>(1,1e5));`
- `rnd_pair<_LES>(rdl(1,10));` (C++17 及以上)
- `rnd_pair<_LES>(rdl(1,10),rdl(1,1e5));` (C++17 及以上)

#### `std::vector<unsigned int> rnd_range(unsigned int tot)`

生成随机排列。

- **参数**: 
  - `tot`: 排列长度。
- **返回值**: 随机排列。

#### `std::vector<std::pair<unsigned int, unsigned int>> rnd_tree(unsigned int tot)`

生成随机树。

- **参数**: 
  - `tot`: 树的大小。
- **返回值**: 随机树的边集。

#### `std::vector<std::pair<unsigned int, unsigned int>> rnd_ucgraph(unsigned int totp, unsigned int tote)`

生成随机无向连通图。

- **参数**: 
  - `tot`: 图的大小。
- **返回值**: 随机无向连通图的边集。

#### `void register_info(int argc, char **argv, unsigned int pos = 3U)`

用于注册测试点信息输出文件。

- **参数**: 
  - `argc`: 命令行参数的数量。
  - `argv`: 命令行参数的数组。
  - `pos`: 文件所在的参数位置。

#### `template<class Ty> void print_info(const Ty &info, const std::string &pre = default_pre)`

输出测试点信息。其中 `default_pre` 为从环境变量 `.data.info_pre` 的值，默认为 `***** info: `。

- **参数**: 
  - `info`: 需输出的测试点信息。
  - `pre`: 测试点信息前缀。

#### `void auto_flush()`

自动刷新标准输出、标准错误输出缓冲区。

#### `void register_all(int argc, char **argv)`

以默认参数位置注册所有需注册信息。

- **参数**: 
  - `argc`: 命令行参数的数量。
  - `argv`: 命令行参数的数组。

## 卸载

要卸载 Orita，请使用 `orita /clear` 命令删除所有配置文件，然后删除 `Orita` 目录下的源文件即可。

如不再需要 CMake、GCC、MSVC 等请自行卸载。

## 依赖项

该项目使用了以下第三方库：

- Lohmann, N. (2023). JSON for Modern C++ (Version 3.11.3) [Computer software]. https://github.com/nlohmann
- [gabime/spdlog](https://github.com/gabime/spdlog)
- [ikalnytskyi/termcolor](https://github.com/ikalnytskyi/termcolor)
- [pocoproject/poco](https://github.com/pocoproject/poco)

## 开源协议

[MIT](LICENSE) LICENSE

## 致谢

本项目由 [Sukwants](https://github.com/Sukwants)、[Pond Ink](https://github.com/Pond-Ink) 团队和 [syysongyuyang](https://github.com/syysongyuyang) 提供技术支持。

[![0](https://avatars.githubusercontent.com/u/95968907?s=64&v=4)](https://github.com/Sukwants)
[![0](https://avatars.githubusercontent.com/u/145256515?s=64&v=4)](https://github.com/Pond-Ink)
[<img src="https://avatars.githubusercontent.com/u/123732645" height=64x width=64x alt>](https://github.com/syysongyuyang)

相关项目：
- [vscode-Orita](https://github.com/2745518585/vscode-Orita) - VSCode extension for Orita
- [Atiro](https://github.com/Sukwants/Atiro) - Useless OI Tools
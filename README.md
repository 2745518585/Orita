# Orita

[Orita](https://github.com/2745518585/Orita)

由 [赵悦岑](https://github.com/2745518585/) 开发的一款 OI 工具，包括评测、对拍、数据生成等，主要由 C++ 语言编写。

[vscode-Orita](https://github.com/2745518585/vscode-Orita)

Orita 的配套 vscode 拓展。

## 安装

在安装 Orita 前，需要保证环境为 Windows 或 Linux 环境，计算机上需要安装以下应用程序：

- [CMake](https://cmake.org/)

通过以下命令获取 Orita 源代码：

```
$ git clone https://github.com/2745518585/Orita
```

在 `Orita/` 目录下运行以下命令来编译源代码：

```
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

请保证 `Orita/bin/` 中的程序能被全局调用。

为了正常使用 Orita，请保证计算机上有支持 C++14 的 C++ 编译器 g++，并能在控制台中全局调用。

使用 `orita reset` 命令初始化并清空配置。

## 用法

### 参数系统

所有命令的参数格式均为 `/i arg ...` 或 `-i arg`，每个参数的范围为声明至下一个参数或结尾。

如参数中含空格需加引号，且参数中需要使用引号请使用 `\"`。

### 全局变量替换

`%[0-999]` 将替换为槽位中的文件名，如 `%1` 表示存储在槽位 $1$ 的文件。

`%...%` 将替换为环境变量 `...`。

`%%` 将替换为 `%`。

### 内置文件

Orita 内置了一些文件来方便使用，其初始化后位于文件缓存的槽位中。如果自行修改下列槽位文件，部分命令可能会出现错误。

$0$ 槽位：空，总是返回 $0$。

$1$ 槽位：文件比较器，三个参数分别为 `in` `out` `ans` 文件，返回 `out` 和 `ans` 忽略行末空格和文末换行的比较结果。

## 命令

### reset

`orita reset`

重置配置。

### clear

`orita clear`

删除配置文件。

### run

`run [/f <file>] [/c [chk_file]] [/t <time>]`

#### 描述

将给定的文件跑预定好的标准输入输出，并给出结果。所有文件编译时定义宏 `JUDGING`。

#### 参数列表

`/f <file>`    指定源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的源文件为准。

`/c [chk_file]`    指定 `checker` 文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。未指定文件以上一次设置的源文件为准。无此参数使用使用 $1$ 槽位比较器。

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

`check [/n <sum>] [/f <in_file> <out_file> <ans_file> | [[/if <in_file>] [/of <out_file>] [/af <ans_file>]]] [/c [chk_file]] [/t <time>]`

#### 描述

给定数据生成器、标准代码和源代码，进行对拍。所有文件编译时定义宏 `JUDGING`。数据会存放在 `data/` 目录下。

#### 参数列表

`/n <sum>`    对拍次数。如无此参数不会开始对拍，仅视为设置参数。

`/f <in_file> <out_file> <ans_file>`    指定源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的源文件为准。

`/c <chk_file>`    指定 `checker` 的文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。未指定文件以上一次设置的源文件为准。无此参数使用使用 $1$ 槽位比较器。

`/if <in_file>`    指定 `in` 文件（后缀不为 `.cpp `自动添加 `.cpp `后缀）。如无此参数则以上一次设置的 `in` 文件为准。此参数与 `/f` 冲突，优先级低于 `/f`。

`/of <out_file>`    指定 `out` 文件（后缀不为 `.cpp `自动添加 `.cpp `后缀）。如无此参数则以上一次设置的 `out` 文件为准。此参数与 `/f` 冲突，优先级低于 `/f`。

`/af <ans_file>`    指定 `ans` 文件（后缀不为 `.cpp `自动添加 `.cpp `后缀）。如无此参数则以上一次设置的 `ans` 文件为准。此参数与 `/f` 冲突，优先级低于 `/f`。

`/t <time>`    修改默认运行时间限制（单位 ms）。

### judge

`judge [/f <file>] [/c [chk_file]] [/d data...] [/is <infile_suf>] [/os <outfile_suf>] [/t <time>]`

#### 描述

给定数据文件和源代码，从数据文件中找到指定后缀名的输入输出文件并组成数据点，得到源代码的所有结果。所有文件编译时定义宏 `JUDGING`。数据会存放在 `data/` 目录下。

#### 参数列表

`/f <file>`    指定源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的源文件为准。

`/c [chk_file]`    指定 `checker` 的文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。未指定文件以上一次设置的源文件为准。无此参数使用使用 $1$ 槽位比较器。

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

### cmp

`cmp </f <file1> <file2>>`

#### 描述

比较两个文件是否相同，忽略行末空格与文末换行。

#### 参数列表

`/f <file1> <file2>`    指定比较的两个文件。

### setfile

`setfile [/i <file>]`

#### 描述

修改指定文件槽位的文件。

#### 参数列表

`/i <file>`    将槽位 $i$ 的文件修改为 `file`。
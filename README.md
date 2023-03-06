# Orita

[Orita](https://github.com/2745518585/Orita)

由 [赵悦岑](https://github.com/2745518585/) 开发的一款 OI 工具，包括评测、对拍、数据生成等，主要由 C++ 语言编写。

## 初始化

使用前需要保证环境为 `Windows` 系统，电脑中有支持 `C++14` 的 `g++` 且已加入环境变量（即可以在控制台运行 `g++`）。

首先将 `Orita\` 目录加入环境变量。

然后运行 `init_Orita` 命令。

出现奇怪问题需要初始化也可以使用 `init_Orita` 清空配置。

## 全局逻辑

### 参数系统

所有命令的参数格式均为 `/i parameter ...`，每个参数的范围为声明至下一个参数或结尾。

如参数中含空格需加引号，如参数中含引号请使用 `\"`。

### 文件缓存

文件可以用 `:` 和 $1 \sim 100$ 的一个数字表示，如 `:1` 表示存储在位置 $1$ 的文件。

此逻辑不检查文件是否存在，将在命令执行前运行，即先替换文件名及地址再进行各命令的检查。

## 命令

### run

`run [/f file] [/c chk_file] [/t time]`

#### 描述

将给定的文件跑预定好的标准输入输出，并给出结果。

#### 参数列表

`/f file`    指定源文件名（后缀不为 `.cpp` 自动添加 `.cpp` 后缀），程序将从当前目录寻找名为 `file` 的文件作为源文件。如无此参数则以上一次设置的源文件为准。

`/c chk_file`    指定 `Special judge` 的 `checker` 文件名（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。程序将从当前目录下寻找名为 `chk_file` 的文件。默认比较器为内置比较器，添加此参数即可开启 `Special judge`。未指定文件名以上一次设置的源文件为准。

`/t time`    修改默认运行时间限制（单位 ms）。

#### 返回值说明

`ans:`    `file` 的信息。

`checker:`    `chk_file` 的信息。

`No Such File`    未找到源文件。

`Accepted`    答案正确。

`Wrong Answer`    答案错误。

`Runtime Error`    运行时错误。

`Time Limit Error, over ... ms`    超出时间限制（此时会强制杀死源代码进程）。

`Time Limit Error, Correct Answer`    超出时间限制，答案正确。

`Time Limit Error, Wrong Answer`    超出时间限制，答案错误。

`Compile Error`    编译错误。

`Dangerous syscalls`    危险的系统调用。

#### 数据及源代码输出

数据与源代码输出会在程序运行完成后存放至 `data\data.in` `data\data.out` `data\data.ans`。

#### 默认编译参数

`-std=c++14 -O2 -Wl,--stack=2147483647`。

### chdata

`chdata [/f input_file output_file] [/s] [/t time]`

#### 描述

用于修改标准输入输出。

#### 参数列表

`/f input_file output_file`   指定输入输出文件名（输入文件自动添加 `.in `后缀，输出文件自动添加 `.out `后缀）。程序将从当前目录下寻找名为 `input_file` 和 `output_file` 的文件。

`/s`    从 `stdin` 与 `stdout` 中读取，每个文件以 `EOF` 结束。此参数与 `/f` 冲突，优先级低于 `/f`。

`/t time`    修改默认运行时间限制（单位 ms）。

#### 返回值说明

`Success`    成功修改标准输入输出。

`No Such File`    未找到文件。

### check

`check [/n sum] [/f in_file out_file ans_file] [/c chk_file] [/e] [/if in_file] [/of out_file] [/af ans_file] [/t time]`

#### 描述

给定数据生成器、标准代码和源代码，进行对拍。

#### 参数列表

`/n sum`    对拍次数。如无此参数不会开始对拍，仅视为设置参数。

`/f in_file out_file ans_file`    指定源文件名（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。程序将从当前目录下寻找名为 `in_file`，`out_file`，`ans_file` 的文件。如无此参数则以上一次设置的源文件为准。

`/c chk_file`    指定 `Special judge` 的 `checker` 文件名（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。程序将从当前目录下寻找名为 `chk_file` 的文件。默认比较器为内置比较器，添加此参数即可开启 `Special judge`。未指定文件名以上一次设置的源文件为准。

`/e`    开启对 `in_file` 和 `out_file` 的检查。可能降低运行速度。

`/t time`    修改默认运行时间限制（单位 ms）。

`/if in_file`    指定 `in` 文件名（后缀不为 `.cpp `自动添加 `.cpp `后缀）。程序将从当前目录下寻找名为 `in_file` 的文件。如无此参数则以上一次设置的 `in` 文件为准。此参数与 `/f` 冲突，优先级低于 `/f`。

`/of out_file`    指定 `out` 文件名（后缀不为 `.cpp `自动添加 `.cpp `后缀）。程序将从当前目录下寻找名为 `out_file` 的文件。如无此参数则以上一次设置的 `out` 文件为准。此参数与 `/f` 冲突，优先级低于 `/f`。

`/af ans_file`    指定 `ans` 文件名（后缀不为 `.cpp `自动添加 `.cpp `后缀）。程序将从当前目录下寻找名为 `ans_file` 的文件。如无此参数则以上一次设置的 `ans` 文件为准。此参数与 `/f` 冲突，优先级低于 `/f`。

#### 返回值说明

`data_maker:`    `in_file` 的信息。

`std:`    `out_file` 的信息。

`ans:`    `ans_file` 的信息。

`checker:`    `chk_file` 的信息。

`No Such File`    未找到源文件。

`Compile Error`    编译错误。

`Dangerous syscalls`    危险的系统调用。

`#i--------------------------------------------------  (Unaccepted p)`    表示第 $i$ 个数据点的信息，当前已经有 $p$ 个数据点错误（没有此项则表示当前无错误）。

`Accepted`    答案正确。

`Wrong Answer`    答案错误。

`Runtime Error`    运行时错误。

`Time Limit Error, over ... ms`    超出时间限制（此时会强制杀死源代码进程）。

`Time Limit Error, Correct Answer`    超出时间限制，答案正确。

`Time Limit Error, Wrong Answer`    超出时间限制，答案错误。

`ac_sum / total_sum`    共 $total\_ sum$ 个测试点，正确 $ac\_ sum$ 个。

#### 数据及源代码输出

错误数据点的数据与源代码输出会在当前测试点运行完成后存放至 `data\i.in` `data\i.out` `data\i.ans`。

#### 默认编译参数

`-std=c++14 -O2 -Wl,--stack=2147483647`。

### judge

`judge [/f file] [/c checker] [/d data_pre sum] [/t time]`

#### 描述

给定多组数据和源代码，得到源代码的所有结果。

#### 参数列表

`/f file`    指定源文件名（后缀不为 `.cpp` 自动添加 `.cpp` 后缀），程序将从当前目录寻找名为 `file` 的文件作为源文件。如无此参数则以上一次设置的源文件为准。

`/c chk_file`    指定 `Special judge` 的 `checker` 文件名（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。程序将从当前目录下寻找名为 `chk_file` 的文件。默认比较器为内置比较器，添加此参数即可开启 `Special judge`。未指定文件名以上一次设置的源文件为准。

`/d data_pre sum`    指定数据点的前缀名和个数。程序将从当前目录下寻找名为 `data_pre` + $i$ + `.in` 的文件作为第 $i$ 组输入文件和 `data_pre` + $i$ + `.out` 作为第 $i$ 组输出文件。如无此参数将不会开始评测，仅视为设置参数。

`/t time`    修改默认运行时间限制（单位 ms）。

#### 返回值说明

`No Such File`    未找到源文件。

`Accepted`    答案正确。

`Wrong Answer`    答案错误。

`Runtime Error`    运行时错误。

`Time Limit Error, over ... ms`    超出时间限制（此时会强制杀死源代码进程）。

`Time Limit Error, Correct Answer`    超出时间限制，答案正确。

`Time Limit Error, Wrong Answer`    超出时间限制，答案错误。

`Compile Error`    编译错误。

`Dangerous syscalls`    危险的系统调用。

`ac_sum / total_sum`    共 $total\_ sum$ 个测试点，正确 $ac\_ sum$ 个。

最后结果会汇总到 `result.txt`。

### compile

`compile [/f file1 file2 ...] [/r file] [/o compile_parameter]`

#### 描述

给定源文件和编译参数，编译源文件。

#### 参数列表

`/f file1 file2 ...`    给定多个编译源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。程序将从当前目录下寻找名为 `file` 的文件。如无此参数则编译所在目录下的所有后缀为 `.cpp` 的文件（包括子目录）。

`/r file`    给定源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀），编译并运行。次参数与 `/f` 冲突，优先级低于 `/f`。添加此参数将没有输出。

`/o compile_parameter`    给定编译参数。此参数将跟在默认编译参数后，`g++` 会在冲突的参数中选择靠后的参数。

#### 返回值说明

`file`    正在编译 `file` 文件。

`Success`    编译成功。

`Compile Error`    编译错误。

#### 默认编译参数

`-std=c++14 -O2 -Wl,--stack=2147483647`。

### changna

`changna /f old_name new_name /i min_i max_i`

#### 描述

给定文件名表达式，批量重命名。

#### 参数列表

`/f old_name new_name`    指定旧文件名表达式和新文件名表达式。

`/i min_i max_i`    指定参数 $i$ 的值域。

#### 表达式规范

使用形如 `:x1:,format` 的表达式表示一个变量，`,format` 可以省略。$x1$ 表示参数 $i$，会以 `format` 的格式输出（即 C++ 格式化输出，默认为 `%d`）。

目前仅支持 `:x1:` 到 `:x9:`。

形如 `:s:` 的表达式表示当前文件编号，即已经成功重命名的文件个数 $+1$。

#### 返回值说明

`inst` 尝试执行 `inst`。

`Success` 成功。

`Fail` 失败，一般为未找到文件。

#### 注意事项

未指定标准输出和标准错误输出的命令全部定向到 `nul`，即在命令开头加上 `>nul 2>&1`。

### cmp

`cmp /f file1 file2`

#### 描述

比较两个文件是否相同。

#### 参数列表

`/f file1 file2`    指定比较的两个文件名。默认忽略行末空格与文末换行。

#### 返回值说明

`No such file`    找不到文件。

`Different Answer`    文件不相同。

`Same Answer`    文件相同。

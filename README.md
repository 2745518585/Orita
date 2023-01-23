# Orita

由 [赵悦岑](https://github.com/2745518585/) 开发的一款 OI 工具，包括评测、对拍、数据生成等，主要由 C++ 语言编写。

## 全局逻辑

### 参数系统

所有命令的参数格式均为 `/i parameter ...`，每个参数的范围为声明至下一个参数或结尾。

### 文件缓存

文件可以用 `:` 和 $1 \sim 100$ 的一个数字表示，如 `:1` 表示存储在位置 $1$ 的文件。

## 命令

### run

`run [/f file] [/t time]`

#### 描述

将给定的文件跑预定好的标准输入输出，并给出结果。

#### 参数列表

`/f file`    指定源文件名（后缀不为 `.cpp` 自动添加 `.cpp` 后缀），程序将从当前目录寻找名为 `file` 的文件作为源文件。如无此参数则以上一次设置的源文件为准。

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

#### 数据及源代码输出

数据与源代码输出会在程序运行完成后存放至 `data\data.in` `data\data.out` `data\data.ans`。

#### 默认编译参数

`-std=c++14 -O2 -Wl,--stack=2147483647`。

### change_data

`change_data [/f input_file output_file] [/s] [/t time]`

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

`check [/n num] [/f in_file out_file ans_file] [/if in_file] [/of out_file] [/af ans_file] [/t time]`

#### 描述

给定数据生成器、标准代码和源代码，进行对拍。

#### 参数列表

`/n`    对拍次数。如无此参数不会开始对拍，仅视为设置参数。

`/f in_file out_file ans_file`    指定源文件名（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。程序将从当前目录下寻找名为 `in_file`，`out_file`，`ans_file` 的文件。如无此参数则以上一次设置的源文件为准。

`/t time`    修改默认运行时间限制（单位 ms）。

`/if in_file`    指定 `in` 文件名（后缀不为 `.cpp `自动添加 `.cpp `后缀）。程序将从当前目录下寻找名为 `in_file` 的文件。如无此参数则以上一次设置的 `in` 文件为准。此参数与 `/f` 冲突，优先级低于 `/f`。

`/of out_file`    指定 `out` 文件名（后缀不为 `.cpp `自动添加 `.cpp `后缀）。程序将从当前目录下寻找名为 `out_file` 的文件。如无此参数则以上一次设置的 `out` 文件为准。此参数与 `/f` 冲突，优先级低于 `/f`。

`/af ans_file`    指定 `ans` 文件名（后缀不为 `.cpp `自动添加 `.cpp `后缀）。程序将从当前目录下寻找名为 `ans_file` 的文件。如无此参数则以上一次设置的 `ans` 文件为准。此参数与 `/f` 冲突，优先级低于 `/f`。

#### 返回值说明

`No Such File`    未找到源文件。

`Compile Error`    `ans_file` 编译错误。

`data_maker Compile Error`    `in_file` 编译错误。

`std Compile Error`    `out_file` 编译错误。

`Dangerous syscalls`    `ans_file` 危险的系统调用。

`data_maker Dangerous syscalls`    `in_file` 危险的系统调用。

`std Dangerous syscalls`    `out_file` 危险的系统调用。

`#i--------------------------------------------------  (Unaccepted p)`    表示第 $i$ 个数据点的信息，当前已经有 $p$ 个数据点错误（没有此项则表示当前无错误）。

`Accepted`    答案正确。

`Wrong Answer`    答案错误。

`Runtime Error`    运行时错误。

`Time Limit Error, over ... ms`    超出时间限制（此时会强制杀死源代码进程）。

`Time Limit Error, Correct Answer`    超出时间限制，答案正确。

`Time Limit Error, Wrong Answer`    超出时间限制，答案错误。

`ac_sum / total_sum`    共 $total\_sum$ 个测试点，正确 $ac\_sum$ 个。

#### 数据及源代码输出

错误数据点的数据与源代码输出会在当前测试点运行完成后存放至 `data\i.in` `data\i.out` `data\i.ans`。

#### 默认编译参数

`-std=c++14 -O2 -Wl,--stack=2147483647`。

### compile

`compile [/f file1 file2 ...] [/o compile_parameter]`

#### 描述

给定源文件和编译参数，编译源文件。

#### 参数列表

`/f file1 file2 ...`    给定多个编译源文件（后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。程序将从当前目录下寻找名为 `file` 的文件。如无此参数则编译所在目录下的所有后缀为 `.cpp` 的文件（包括子目录）。

`/o compile_parameter`    给定编译参数。此参数将跟在默认编译参数后，`g++` 会在冲突的参数中选择靠后的参数。

#### 返回值说明

`file`    正在编译 `file` 文件。

`Success`    编译成功。

`Compile Error`    编译错误。

#### 默认编译参数

`-std=c++14 -O2 -Wl,--stack=2147483647`。

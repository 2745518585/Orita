# Orita

由 [赵悦岑](https://github.com/2745518585/) 开发的一款 OI 工具，包括评测、对拍、数据生成等，主要由 C++ 语言编写。

## 命令

### run

`run [/f file] [/t time]`

#### 描述

将给定的文件跑预定好的标准输入输出，并给出结果。

#### 参数列表

`/f`    `file`    指定源文件名（如果无 `.cpp` 后缀或后缀不为 `.cpp` 自动添加 `.cpp` 后缀），程序将从当前目录寻找名为 `file` 的文件作为源文件。如无此参数则以上一次设置的源文件为准。

`/t`    `time`    修改默认运行时间限制（单位 ms）。

#### 返回值说明

`No Such File`    未找到源文件。

`Compile Error`    编译错误。

`Accepted`    答案正确。

`Wrong Answer`    答案错误。

`Runtime Error`    运行时错误。

`Time Limit Error, over ... ms`    超出时间限制（此时会强制杀死源代码进程）。

`Time Limit Error, Correct Answer`    超出时间限制，答案正确。

`Time Limit Error, Wrong Answer`    超出时间限制，答案错误。

#### 数据及源代码输出

数据与源代码输出会在程序运行完成后存放至 `data\data.in` `data\data.out` `data\data.ans`。

#### 编译参数

`-std=c++14 -O2 -Wl,--stack=2147483647`。

### change_data

`change_data [/f input_file output_file] [/s] [/t time]`

#### 描述

用于修改标准输入输出。

#### 参数列表

`/f`     `input_file`    `output_file`   指定输入输出文件名（输入文件自动添加 `.in `后缀，输出文件自动添加 `.out `后缀）。程序将从当前目录下寻找名为 `input_file` 和 `output_file` 的文件。此参数与  `/s `冲突，优先级高于 `/s`。

`/s`    从 `stdin` 与 `stdout` 中读取，每个文件以 `EOF` 结束。此参数与 `/f` 冲突，优先级低于 `/f`。

`/t`    `time`    修改默认运行时间限制（单位 ms）。

#### 返回值说明

`Success`    成功修改标准输入输出。

`No Such File`    未找到文件。

### check

`check [/n num] [/f data_maker_file std_file test_file] [/t time]`

#### 描述

给定数据生成器、标准代码和源代码，进行对拍。

#### 参数列表

`/n`    对拍次数。如无此参数不会开始对拍，仅视为设置参数。

`/f`    `data_maker_file`    `std_file`    `test_file`    指定源文件名（如果无 `.cpp` 后缀或后缀不为 `.cpp` 自动添加 `.cpp` 后缀）。程序将从当前目录下寻找名为 `data_maker_file`，`std_file`，`test_file` 的文件。如无此参数则以上一次设置的源文件为准。

`/t`    `time`    修改默认运行时间限制（单位 ms）。

#### 返回值说明

`No Such File`    未找到源文件。

`Compile Error`    `test_file` 编译错误。

`data_maker Compile Error`    `data_maker_file` 编译错误。

`std Compile Error`    `std_file` 编译错误。

`#i--------------------------------------------------  (Unaccepted p)`    表示第 $i$ 个数据点的信息，当前已经有 $p$ 个数据点错误（没有此项则表示当前无错误）。

`Accepted`    答案正确。

`Wrong Answer`    答案错误。

`Runtime Error`    运行时错误。

`Time Limit Error, over ... ms`    超出时间限制（此时会强制杀死源代码进程）。

`Time Limit Error, Correct Answer`    超出时间限制，答案正确。

`Time Limit Error, Wrong Answer`    超出时间限制，答案错误。

`s/n w pts`    共 $n$ 个测试点，正确 $s$ 个，得分 $w$。

#### 数据及源代码输出

错误数据点的数据与源代码输出会在当前测试点运行完成后存放至 `data\i.in` `data\i.out` `data\i.ans`。

#### 编译参数

`-std=c++14 -O2 -Wl,--stack=2147483647`。

#### 注意事项

程序仅保存上一次设置的源文件名，不保存路径，每次执行均在当前目录下寻找源文件。即不能在与源文件不同的目录下执行，即使是使用上一次的记录。

# run

由 [赵悦岑](https://github.com/2745518585/) 开发的一款对拍器，主要由 C++ 语言编写。

## 命令

### run

`run [/f file] [/t time]`

#### 描述

将给定的文件跑预定好的标准输入输出，并给出结果。

#### 参数列表

`/f`    `file`    指定源文件名（自动添加 `.cpp` 后缀）。如无此参数则以上一次设置的源文件名为准。

`/t`    `time`    修改默认运行时间限制（单位 ms）。

#### 返回值说明

`Accepted`    答案正确。

`Wrong Answer`    答案错误。

`Runtime Error`    运行时错误。

`Time Limit Error`    超出时间限制（此时会强制杀死源代码进程）。

`Time Limit Error, Correct Answer`    超出时间限制，答案正确。

`Time Limit Error, Wrong Answer`    超出时间限制，答案错误。

`No Such File`    未找到源文件。

#### 数据及源代码输出

数据与源代码输出会在程序运行完成后存放至 `data\data.in` `data\data.out` `data\run.out`。

#### 编译参数

`-std=c++14 -O2 -Wl,--stack=2147483647`。

#### 注意事项

程序仅保存上一次设置的源文件名，不保存路径，每次执行均在当前目录下寻找源文件。即不能在与源文件不同的目录下执行，即使是使用上一次的记录。

### change_data

`change_data [/f input_file output_file] [/s] [/t time]`

#### 描述

用于修改标准输入输出。

#### 参数列表

`/f`     `input_file`    `output_file `   指定输入输出文件名（输入文件自动添加 `.in `后缀，输出文件自动添加 `.out `后缀）。此参数与 `/s` 冲突，优先级高于 `/s`。

`/s`    从 `stdin `与 `stdout `中读取，每个文件以 `EOF` 结束。

`/t`    `time`    修改默认运行时间限制（单位 ms）。

#### 返回值说明

`Success`成功修改标准输入输出。

`No Such File`    未找到文件。

### check

`check /n num [/f data_maker_file std_file test_file] [/t time]`

#### 描述

给定数据生成器、标准代码和源代码，进行对拍。

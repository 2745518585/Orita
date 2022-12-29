# run

由 [赵悦岑](https://github.com/2745518585/) 开发的一款对拍器，主要由 C++ 语言编写。

## 命令

### run

`run [/f]`

#### 描述

使用该工具将给定的文件跑预定好的标准输入输出，并给出结果。

#### 参数列表

`/f`    `files`    指定源文件（自动添加 `.cpp` 后缀）。

#### 返回值说明

`Accepted`    答案正确。

`Wrong Answer`    答案错误。

`Runtime Error`    运行时错误。

`Time Limit Error`    超出时间限制。

`Time Limit Error, Correct Answer`    超出时间限制，答案正确。

`Time Limit Error, Wrong Answer`    超出时间限制，答案错误。

#### 编译参数

`-std=c++14 -O2 -Wl,--stack=2147483647`

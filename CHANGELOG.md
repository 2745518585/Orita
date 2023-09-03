# Orita CHANGELOG

## Dev 0.0

Orita 第一个正式版本。

### Dev 0.0.1

2023-01-23

发布第一个正式版本。

### Dev 0.0.2

2023-01-27

#### 修复

- `Time Limit Error, over ... ms` 错误的输出为 `over %dms`。
- `change_data` 命令从文件读入时无法正确修改输出文件。

### Dev 0.0.3

2023-01-30

#### 修复

- `data_maker Dangerous syscalls` 输出样式错误。

### Dev 0.0.4

2023-02-01

#### 代码

- 更换 json 库，支持 `Unicode`。
- 修改宏定义的命名。

#### 新增

- 文件地址支持 Unicode。
- `change_data` 命令支持全局文件替换逻辑。

### Dev 0.0.5

2023-02-02

#### 代码

- 修改宏定义的命名。

#### 新增

- 支持相对路径。
- 对部分输出增加所述文件的提示。
- 新增 `Special Judge` 功能。

### Dev 0.0.6

2023-02-03

#### 代码

- `judge.hpp` 输入输出答案的文件加入 `name` 系统，可修改文件。
- 修改 `print` 的逻辑。
- 换用 `nlohmann/json`，使用输入输出时 `GB2312` 和 `UTF-8` 相互转换的方式支持中文，停止支持 `Unicode`。

#### 新增

- `check` 命令可以判断 `data_maker` 与 `std` 是否 `TLE` 或 `RE`，自动跳过该数据点。
- `check` 对拍两个选手文件输出是否相同，将测试两个文件，不支持 `Special judge`。
- `judge` 命令，用于评测答案文件跑大量数据的结果。

#### 修复

- `check` 命令 `std` 文件地址部分情况下错误。
- 部分情况下无法支持中文。

### Dev 0.0.7

2023-02-10

#### 代码

- 修改宏定义名称。

#### 新增

- `cmp` 命令，用于比较两个文件，忽略行末空格和文末换行。
- `judge` 使用新的比较函数，忽略行末空格和文末换行。
- `changna`，用于批量修改文件名。
- 将 `init_Orita` 命令改为批处理脚本，直接运行即可初始化。
- 完善 `data_maker`。
- 支持带空格的文件，输入时加引号即可。
- 修改部分命令名。

#### 修复

- 修复了初始化过程的问题。
- `compile` 的中文显示问题。

### Dev 0.0.8

2023-02-17

#### 新增

- `run` 和 `check` 中找到的  `Dangerous syscalls` 仅作为 `warning` 输出，不阻止程序运行。
- `compile` `/r` 命令，编译并运行文件。
- 调用上次的文件名之前检查是否存在。

### Dev 0.0.9

2023-02-26

#### 代码

- 使用 `json` 储存参数。
- 从主要使用 `name` 传文件变为 `string` 传文件。
- 内部主要编码由 `UTF-8` 转为 `GB2312`。

#### 新增

- 对于错误参数报 `Invalid input`。
- 编译过程提示。
- `changna` 支持对任意 cmd 命令进行替换后执行，返回值为 $0$ 报 `Success`，否则报 `Fail`。

#### 修复

- `check` 文件名含空格出错。

### Dev 0.0.10

2023-03-07

#### 代码

- 修改处理文件的逻辑。
- 修改初始化逻辑。

#### 新增

- 更换标准配色。

### Dev 0.0.11

2023-03-18

#### 新增

- 在 `run`、`check`、`judge` 命令中编译的文件在编译时会加上 `JUDGING` 的宏定义。
- 记录 `checker` 的输出。
- 随机生成树。
- 添加 `orita` 命令。

### Dev 0.0.12

2023-04-17

#### 代码

- 去掉 `using namespace std;`
- 添加 `#pragma once`。

#### 新增

- 使用 CMake。

## Dev 0.1

### Dev 0.1.0

2023-04-24

#### 新增

- 支持 Linux 系统。

### Dev 0.1.1

2023-04-29

#### 代码

- `judge` 封装为 `class`。

#### 新增

- `Linux` 下可执行文件改为无后缀名。

#### 修复

- `.sh` 文件换行符为 `\r\n`。

### Dev 0.1.2

2023-05-11

#### 代码

- 封装 `result` 类型。

#### 新增

- 无输出编译使用多线程并行编译。
- 删除 `Dangerous Syscalls`。
- 修改输出格式。
- 文件名允许使用 `%...%`。 

### Dev 0.1.3

2023-05-23

#### Features

- Use [spdlog](https://github.com/gabime/spdlog) to output logs.
- Replace command `reset_Orita` with `orita reset`.
- Use default color in terminal.
- Command `orita judge` read data by wildcards.
- Delete command `orita changna`.
- Add data settings `dafault_checker`.
- Add some error while reading settings.
- Add `bin/`.

#### Fixs

- `orita compile /t` didn't work。
- Killing tasks cannot run successfully in Linux。

### Dev 0.1.4

#### Features

- `data_maker` can use custom function.
- Delete `orita cmp`.
- Replace `setfile` with `config`.
- Is able to change default data files in settings.

#### Changes

- Use `std::filesystem`.
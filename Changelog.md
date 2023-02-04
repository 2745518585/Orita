# Changelog

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

- 更换 json 库，支持 Unicode。
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
- 换用 `nlohmann/json`，修复支持中文，停止支持 Unicode。

#### 新增

- `check` 命令可以判断 `data_maker` 与 `std` 是否 `TLE` 或 `RE`，自动跳过该数据点。
- `check` 对拍两个选手文件输出是否相同，将测试两个文件，不支持 `Special judge`。
- `judge` 命令，用于评测答案文件跑大量数据的结果。

#### 修复

- `check` 命令 `std` 文件地址部分情况下错误。
- 部分情况下无法支持中文。

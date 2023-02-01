# Changelog

## Dev 0.0

Orita 第一个正式版本。

### Dev 0.0.1(2023-01-23)

发布第一个正式版本。

### Dev 0.0.2(2023-01-27)

#### 修复

- `Time Limit Error, over ... ms` 错误的输出为 `over %dms`。
- `change_data` 命令从文件读入时无法正确修改输出文件。

### Dev 0.0.3(2023-01-30)

#### 修复

- `data_maker Dangerous syscalls` 输出样式错误。

### Dev 0.0.4

#### 代码

- 更换 json 库，支持 Unicode。
- 修改宏定义的命名。

#### 新增

- 文件地址支持 Unicode。
- `change_data` 命令支持全局文件替换逻辑。

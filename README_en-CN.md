[zh-CN](./README.md) | en-CN

# Orita

[Orita](https://github.com/2745518585/Orita)

An OI (Olympiad in Informatics) tool developed by [赵悦岑](https://github.com/2745518585/). It includes features such as judging, stress testing, and data generation, and is primarily written in C++.

[vscode-Orita](https://github.com/2745518585/vscode-Orita)

The VSCode extension for Orita.

## Install

### Build

Before installing Orita, ensure that your environment is a Windows or Linux environment, and the following applications are installed on your computer:

- [CMake](https://cmake.org/) (3.15+)

You also need to install GCC 11.4+ or MSVC 2022+.

For Windows computers, please go to the official websites to download and install:

- [CMake](https://cmake.org/)
- [MinGW](https://www.mingw-w64.org/downloads/)
- [Visual Studio](https://visualstudio.microsoft.com/downloads/)

For Linux computers, execute the following commands to install CMake and GCC:

```shell
$ sudo apt-get install cmake
$ sudo apt-get install g++
```

After installation, use the following command to obtain the Orita source code:

```shell
$ git clone https://github.com/2745518585/Orita
```

To compile the source code, run the following commands in the `Orita/` directory:

```shell
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

### Download

You can find the latest release on [Github](https://github.com/2745518585/Orita/releases) and download the precompiled file package for your corresponding platform.

### Initialization

Run `init.bat | init.sh` in the `Orita/` directory to compile the entry file. Ensure that the executable files in the `Orita/bin/` directory can be globally accessed and can be moved to any location. When using CMake to generate, the location of the source files will be automatically output. If you move the source files, please run `init.bat | init.sh` in the `Orita/` directory.

To use Orita properly, make sure that your computer has a C++ compiler g++ that supports C++14 and can be globally accessed from the command line.

Use the `orita reset` command to initialize and clear the configuration.

## Usage

### Parameter System

The parameter format for all commands is `/i arg ...` or `-i arg`, and the scope of each parameter extends to the next parameter or the end.

If a parameter contains spaces, enclose it in quotes, and use `\"` to include quotes within the parameter.

### Built-in Files

Orita comes with some built-in files for convenience, and they are located in the configuration directory after initialization.

`0.cpp`: Empty, always returns 0.

`1.cpp`: File comparator, takes three parameters - `in`, `out`, and `ans` files, and returns the comparison result between `out` and `ans`, ignoring trailing spaces and line endings.

### File Name Replacement

File names in Orita can be replaced using specific patterns:

- `%[0-999]`: This will be replaced with the corresponding file name based on the `file.json` configuration. For example, `%1` represents the file name with the ID 1.

- `%...%`: In file names, this pattern is replaced with environment variables `...`. It first attempts to match project-specific environment variables like `{APPDATA_PATH}`, `{FILE_PATH}`, and `{RUNNING_PATH}`. If no match is found, it falls back to system environment variables `...`.

- `%%`: In file names, this pattern is replaced with `%`.

## Commands

### reset

`orita reset`

Reset the configuration.

### clear

`orita clear`

Delete the configuration files.

### run

`run [/f <file>] [/c <chk_file>] [/t <time>]`

#### Description

Run the given file with predefined standard input and output and provide the results. All files are compiled with the `JUDGING` macro defined.

#### Parameter List

`/f <file>`: Specify the source file (automatically adds a `.cpp` extension if not present). If this parameter is not provided, the last set source file is used.

`/c <chk_file>`: Specify the `checker` file (automatically adds a `.cpp` extension if not present). If this parameter is not provided, the last set source file is used.

`/t <time>`: Modify the default runtime limit (in milliseconds).

#### Data and Source Code Output

Data and source code output will be placed in `data/data.in`, `data/data.out`, `data/data.ans`, and `data/data.txt` after the program has completed.

### chdata

`chdata [/f <input_file> <output_file> | /s] [/t <time>]`

#### Description

Used to modify standard input and output.

#### Parameter List

`/f <input_file> <output_file>`: Specify the input and output files.

`/s`: Read from `stdin`, with each file ending at `EOF`. This parameter conflicts with `/f` and has lower priority than `/f`.

`/t <time>`: Modify the default runtime limit (in milliseconds).

### check

`check [/n <sum>] [/f <in_file> <out_file> <ans_file> | [[/if <in_file>] [/of <out_file>] [/af <ans_file>]]] [/c <chk_file>] [/t <time>]`

#### Description

Perform stress testing with a given data generator, standard code, and source code. All files are compiled with the `JUDGING` macro defined. Data will be stored in the `data/` directory.

#### Parameter List

`/n <sum>`: Number of stress testing iterations. If not provided, stress testing will not be performed and will be considered as parameter setting only.

`/f <in_file> <out_file> <ans_file>`: Specify the source file (automatically adds a `.cpp` extension if not present). If no file is specified, the last set source file is used.

`/c <chk_file>`: Specify the `checker` file (automatically adds a `.cpp` extension if not present). If this parameter is not provided, the last set source file is used.

`/if <in_file>`: Specify the `in` file (automatically adds a `.cpp` extension if not present). If no file is specified, the last set `in` file is used. This parameter conflicts with `/f` and has lower priority than `/f`.

`/of <out_file>`: Specify the `out` file (automatically adds a `.cpp` extension if not present). If no file is specified, the last set `out` file is used. This parameter conflicts with `/f` and has lower priority than `/f`.

`/af <ans_file>`: Specify the `ans` file (automatically adds a `.cpp` extension if not present). If no file is specified, the last set `ans` file is used. This parameter conflicts with `/f` and has lower priority than `/f`.

`/t <time>`: Modify the default runtime limit (in milliseconds).

### judge

`judge [/f <file>] [/c <chk_file>] [/d data...] [/is <infile_suf>] [/os <outfile_suf>] [/t <time>]`

#### Description

Given data files and source code, create data points by finding input and output files with specified extensions in the data files, and obtain all results of the source code. All files are compiled with the `JUDGING` macro defined. Data will be stored in the `data/` directory.

#### Parameter List

`/f <file>`: Specify the source file (automatically adds a `.cpp` extension if not present). If this parameter is not provided, the last set source file is used.

`/c <chk_file>`: Specify the `checker` file (automatically adds a `.cpp` extension if not present). If this parameter is not provided, the last set source file is used.

`/d data...`: Specify data point files. If this parameter is not provided, judging will not begin and will be considered as parameter setting only.

`/is <infile_suf>`: Specify the input file suffix.

`/os <outfile_suf>`: Specify the output file suffix.

`/t <time>`: Modify the default runtime limit (in milliseconds).

### compile

`compile [[/r <file>] | [/t <file>] | [/f file...]] [/o compile_arg] [/p run_arg]`

#### Description

Given source files and compilation parameters, compile the source files.

#### Parameter List

`/r <file>`: Specify the source file (automatically adds a `.cpp` extension if not present), compile and run it. This parameter conflicts with `/f` and takes precedence over `/f`. Using this parameter will have no output.

`/t <file>`: Specify the source file (automatically adds a `.cpp` extension if not present), run the executable file generated from it. This parameter conflicts with `/f` and takes precedence over `/f`. Using this parameter will have no output.

`/f file...`: Specify multiple source files to be compiled (automatically adds a `.cpp` extension if not present).

`/o compile_arg`: Specify compilation parameters.

`/p run_arg`: Specify runtime parameters.

### config

`config [[/s [key [value | %{RESET}%]]] | [/f [key [value | %{RESET}%]]]]`

#### Description

View and modify configurations.

#### Parameter List

`/s [key [value]]` If `key` is not given, output `settings.json` file. If `key` is given but `value` is not given, output the value of `key`. If `%{RESET}%` is appended after `key`, the item will be reset to the default value, which is read from `%{FILE_PATH}%/files/settings.json`. If `value` is appended after `key`, the value of `key` is changed to `value`. The key values of different layers in `key` are separated by `/`.

`/f [num [value]]` If `num` is not given, output `file.json` file. If `num` is given but `value` is not given, output the value of the file numbered `num`. If `%{RESET}%` is appended after `num`, the file will be reset to the default value, which is read from `%{FILE_PATH}%/files/file.json`. If `value` is appended after `num`, the file is set to `value`.

## Uninstall

To uninstall Orita, use `orita clear` to delete all configuration files, and then remove the source files under the `Orita` directory.

If you no longer need CMake, GCC, MSVC, or other components, please uninstall them manually.

## Dependencies

This project uses the following third-party libraries:

- [nlohmann/json](https://github.com/nlohmann/json)
- [gabime/spdlog](https://github.com/gabime/spdlog)
- [ikalnytskyi/termcolor](https://github.com/ikalnytskyi/termcolor)
- [pocoproject/poco](https://github.com/pocoproject/poco)

## Thanks

This project is supported by [Sukwants](https://github.com/Sukwants) and [Pond Ink](https://pond.ink/) teams.

[![0](https://avatars.githubusercontent.com/u/95968907?s=64&v=4)](https://github.com/Sukwants)
[<img src="https://pond.ink/images/avatar.png" height=64x width=64x alt>](https://pond.ink/)

Related projects:
- [vscode-Orita](https://github.com/2745518585/vscode-Orita) - VSCode extension for Orita
- [Atiro](https://github.com/Sukwants/Atiro) - Useless OI Tools
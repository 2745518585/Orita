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
$ git submodule init
$ git submodule update
```

To compile the source code, run the following commands in the `Orita/` directory:

```shell
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

### Download

You can find the latest releases on [GitHub](https://github.com/2745518585/Orita/releases) and download the compiled files for your platform.

### Initialization

Run `init.bat` (Windows) or `init.sh` (Linux) in the `Orita/` directory to compile and generate the entry file. Make sure that the executable files in `Orita/bin/` can be globally called, and you can move the executable files to any location. If you generate them with CMake, the source file location will be automatically output. If you move the source files, please execute `init.bat` (Windows) or `init.sh` (Linux) in the `Orita/` directory.

To use Orita properly, make sure that your computer has a C++ compiler g++ that supports C++14 and can be globally accessed from the command line.

Use the `orita /r` command (Windows) or `orita -r` command (Linux) to initialize and clear the configuration.

## Usage

### Parameter System

Use DOS-style command line parameters on Windows and Unix-style command line parameters on Linux. The following examples use DOS-style parameters.

### Built-in Files

Orita provides some built-in files for convenience, and these files are located in the configuration file directory after initialization.

`0.cpp`: Empty, always returns 0.

`1.cpp`: File comparator, takes three parameters - `in`, `out`, and `ans` files, and returns the comparison result between `out` and `ans`, ignoring trailing spaces and line endings.

### File Name Replacement

File names in Orita can be replaced using specific patterns:

- `%[0-999]`: This will be replaced with the corresponding file name based on the `file.json` configuration. For example, `%1` represents the file name with the ID 1.

* The `%...%` in the file name is replaced with environment variables `...`. The program will match the following environment variables in sequence:
  
  - `{APPDATA_PATH}`: `%APPDATA%/Orita` on Windows, `%HOME%/.Orita` on Linux.
  - `{FILE_PATH}`: The directory where the source code is located.
  - `{RUNNING_PATH}`: The running directory.
  - `{OS_NAME}`: The name of the operating system, `windows` on Windows, `linux` on Linux.
  - Otherwise, it returns the system environment variable `...`.

- `%%` in the file name is replaced with `%`.

### Configuration System

The configuration file is named `settings.json` and has three levels:

1. Default settings file located at `%{FILE_PATH}%/files/%{OS_NAME}%/settings.json`.
2. Global settings file located at `%{APPDATA_PATH}%/settings.json`.
3. Local settings file located at `.orita/settings.json`.

These three-level settings files have increasing priority from top to bottom. For a single run, the effective local settings file is the one in the `%{RUNNING_PATH}%` directory itself and its ancestor directories, with the priority increasing from shallow to deep.

When querying and modifying settings, the default priority is from high to low. If the current setting value is `null`, the query priority is lower than the current file.

Relative paths in local settings files will be resolved in the directory corresponding to the file. Whenever a local settings file is identified in the current directory or a directory with modified local settings through commands, the latest settings file will be output when the program ends. Directories without settings files and without modifications will not output anything.

## Commands

The command can be called through the true prefix of the full name of the command. For example, `orita run` can be abbreviated as `orita r`. The matching priority from high to low is:
- `compile`
- `config`
- `check`
- `chdata`
- `judge`
- `run`

### orita

`orita [/help] [/reset] [/clear]`

The entry command for the command-line tool.

`/help`: Display help information.

`/reset`: Reset the configuration.

`/clear`: Clear the configuration.

### run

`orita run [/help] [/file=file] [/checker=file] [/time=time]`

Run the given file and redirect input, and compare the output. Macros defined during file compilation include `JUDGING`. The data will be placed in the `settings.data.data_dir/` directory.

`/help`: Display help information.

`/file=file`: Specify the source file (automatically adds `.cpp` extension if not present). If this parameter is not present, the source file set in the previous step will be used.

`/checker=file`: Specify the judging file (automatically adds `.cpp` extension if not present). If this parameter is not present, the source file set in the previous step will be used.

`/time=time`: Modify the default runtime limit (in ms).

### chdata

`orita chdata [/help] [/ifile[=file]] [/ofile[=file]] [/time=time]`

Used to modify

 the input and output data for the `run` command.

`/help`: Display help information.

`/ifile[=file]`: Specify the input data file. If no value is specified, it will read from standard input.

`/ofile[=file]`: Specify the output data file. If no value is specified, it will read from standard input.

`/t <time>`: Modify the default runtime limit (in ms).

### check

`orita check [/help] [/ifile=file] [/ofile=file] [/afile=file] [/checker=file] [/num=num] [/time=time]`

Perform a data check with the given data generator, standard code, and source code. Macros defined during file compilation include `JUDGING`. The data will be placed in the `settings.data.data_dir/` directory.

`/help`: Display help information.

`/ifile=file`: Specify the data generator (automatically adds `.cpp` extension if not present). If this parameter is not present, the file set in the previous step will be used.

`/ofile=file`: Specify the standard code (automatically adds `.cpp` extension if not present). If this parameter is not present, the file set in the previous step will be used.

`/afile=file`: Specify the source code (automatically adds `.cpp` extension if not present). If this parameter is not present, the file set in the previous step will be used.

`/checker=file`: Specify the judging file (automatically adds `.cpp` extension if not present). If this parameter is not present, the source file set in the previous step will be used.

`/num=num`: Number of checks. If this parameter is not present, it will not start checking and will only be treated as setting parameters.

`/time=time`: Modify the default runtime limit (in ms).

### judge

`orita judge [data] [/help] [/file=file] [/checker=file] [/time=time] [/isuf=suf] [/osuf=suf]`

Given data files and source code, find the input and output files with the specified suffix in the data files and compose data points to obtain all results of the source code. Macros defined during file compilation include `JUDGING`. The data will be placed in the `data/` directory.

`data`: Specify the data file. If this parameter is not present, it will not start judging and will only be treated as setting parameters.

`/help`: Display help information.

`/file=file`: Specify the source file (automatically adds `.cpp` extension if not present). If this parameter is not present, the source file set in the previous step will be used.

`/checker=file`: Specify the judging file (automatically adds `.cpp` extension if not present). If this parameter is not present, the source file set in the previous step will be used.

`/time=time`: Modify the default runtime limit (in ms).

`/isuf=suf`: Specify the input file suffix, default is `.in`.

`/osuf=suf`: Specify the output file suffix, default is `.out`.

### compile

`orita compile [file] /help [/run] [/trun] [/carg=args] [/arg=args]`

Compile the source file with the given source file and compilation parameters.

`file`: Specify the source file.

`/help`: Display help information.

`/r <file>`: Specify the source file (automatically adds `.cpp` extension if not present) and compile and run it. This parameter conflicts with `/f` and takes precedence over `/f`. Adding this parameter will have no output.

`/t <file>`: Specify the source file (automatically adds `.cpp` extension if not present) and run the corresponding executable file generated by the source file. This parameter conflicts with `/f` and takes precedence over `/f`. Adding this parameter will have no output.

`/f file...`: Specify multiple source files to compile (automatically adds `.cpp` extension if not present).

`/carg=args`: Specify compilation parameters.

`/arg=args`: Specify runtime parameters.

### config

`config [key [value]] [/help] [/settings] [/files]`

#### Description

View or modify the configuration.

#### Parameter List

`key`: Specify the key.

`value`: Specify the value.

`/help`: Display help information.

`/settings`: If the `key` is not provided, output the `settings.json` file. If the `key` is provided but not the `value`, output the value of the `key`. If `%{RESET}%` is appended to the `key`, reset the item to its default value, which is read from `%{FILE_PATH}%/files/settings.json`. If `value` is appended to the `key`, modify the value of the `key`. Different layers of keys in `key` are separated by `/`.

`/global`: Specifies modifying global settings.

`/local`: Specifies modifying local settings for the current directory.

`/files`: If `num` is not provided, output the `file.json` file. If `num` is provided but not the `value`, output the value of the file with the number `num`. If `%{RESET}%` is appended to `num`, reset the file to its default value, which is read from `%{FILE_PATH}%/files/file.json`. If `value` is appended to `num`, set the file to `value`.

## Uninstallation

To uninstall Orita, use the `orita clear` command to delete all configuration files and then delete the source files in the `Orita` directory.

You can also uninstall CMake, GCC, MSVC, and other components if you no longer need them.

## Dependencies

This project uses the following third-party libraries:

- [nlohmann/json](https://github.com/nlohmann/json)
- [gabime/spdlog](https://github.com/gabime/spdlog)
- [ikalnytskyi/termcolor](https://github.com/ikalnytskyi/termcolor)
- [pocoproject/poco](https://github.com/pocoproject/poco)

## Thanks

This project is supported by [Sukwants](https://github.com/Sukwants), [Pond Ink](https://pond.ink/) teams and [syysongyuyang](https://github.com/syysongyuyang).

[![0](https://avatars.githubusercontent.com/u/95968907?s=64&v=4)](https://github.com/Sukwants)
[<img src="https://pond.ink/images/avatar.png" height=64x width=64x alt>](https://pond.ink/)
[<img src="https://avatars.githubusercontent.com/u/123732645" height=64x width=64x alt>](https://github.com/syysongyuyang)

Related projects:
- [vscode-Orita](https://github.com/2745518585/vscode-Orita) - VSCode extension for Orita
- [Atiro](https://github.com/Sukwants/Atiro) - Useless OI Tools
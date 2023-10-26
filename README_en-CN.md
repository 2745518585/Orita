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

Make sure the executable file `orita.exe` or `orita` in the `bin/bin/` directory is globally accessible. You can move the executable file to any location and change its name as needed.

If you used CMake to generate the executable, it should automatically output the location of the executable file. If you move the executable file, run the `path.bat` or `path.sh` in the directory where the executable file is located.

To use Orita properly, ensure that your computer has a C++ compiler (g++) that supports C++14, and it should be globally accessible from the command line.

Use the `orita /r` (Windows) or `orita -r` (Linux) command to initialize and clear the configuration.

## Usage

### Parameter System

Use DOS-style command line parameters on Windows and Unix-style command line parameters on Linux. The following examples use DOS-style parameters.

### Built-in Files

Orita comes with some pre-defined files for convenience, and these files are located in the configuration directory after initialization.

- `0.cpp`: An empty file that always returns $0$.

- `1.cpp`: The file comparator. It takes three arguments: `in`, `out`, and `ans` files, and returns the comparison result of `out` and `ans` after ignoring trailing spaces and end-of-line characters.

### Environment Variable Replacement

All data read from command line parameters or configuration files undergo environment variable replacement. Data read from standard input is not replaced.

- In file names, `%...%` is replaced with the environment variable `...`. The program will match the following environment variables in order:
  - Expressions like `%*[0-999]%` will be replaced with the file name corresponding to the number in `file.json`. For example, `%*1%` represents the file name corresponding to $1$.
  - Expressions like `%....%` are replaced with the values set in the system. For example, `%.data.data_dir%` represents the value of `/data/data_dir` in the settings.
  - `{APPDATA_PATH}`: `%APPDATA%/Orita` on Windows, `%HOME%/.Orita` on Linux.
  - `{FILE_PATH}`: The directory of the executable file.
  - `{RUNNING_PATH}`: The running directory.
  - `{OS_NAME}`: The name of the operating system.
  - Otherwise, it returns the system environment variable `...`.

- `%%` in file names will be replaced with `%`.

### Settings System

The settings file is named `settings.json` and has three levels:

1. Default settings file, located at `%{FILE_PATH}%/files/%{OS_NAME}%/settings.json`.
2. Global settings file, located at `%{APPDATA_PATH}%/settings.json`.
3. Local settings file, located at `.orita/settings.json`.

These three-level settings files have increasing priority from top to bottom. The effective local settings file for a single run is the one in `%{RUNNING_PATH}%` or in any ancestor directory with the file `.orita/settings.json`. The priority is determined by the directory level, with the shallowest directory taking precedence.

When querying and modifying settings, the default order is from high to low priority. If the current setting value is `null`, the query priority is lower than the current file.

Relative paths in settings are resolved within the directory of the file. If a local settings file is detected in the current directory or the directory is changed via a command to a directory with a modified local settings file, the latest settings file will be output at the end of the program. Directories without settings files or without modifications will not be output.

If you need to represent an object in the settings as a string, use `.` to separate different levels of directories, like `.data.data_dir`. In the following text, `%.data.data_dir%` represents the corresponding object in the settings.

Settings files can be stored in the `.~list` location of global settings and loaded into the local directory's configuration files.

#### Setting Information

- `commands`: List of matching commands.
- `compiler`: Compiler-related settings.
  - `argu`: Compilation options.
  - `command`: Path to the compiler to call.
  - `time_limit`: Compilation time limit.
- `data`: Evaluation-related settings.
  - `ansfile`: Default answer data file.
  - `chk_exit_code`: The return value of the `checker` when an answer is incorrect. Use regular expressions for decimal matching.
  - `chkfile`: Default comparison information file.
  - `compile_argu`: Evaluation compilation options.
  - `data_dir`: Directory for data files.
  - `infile`: Default input data file.
  - `outfile`: Default output data file.
  - `time`: Evaluation time limit.
- `exe_suf`: Executable file suffix.
- `max_process_num`: Maximum process number order.
- `max_thread_num`: Maximum thread number order.
- `runtime_limit`: Subprocess runtime time limit.
- `show_file_info`: Whether to display file information during evaluation.
- `~list`: List of settings.

### Command Matching

Use the first parameter as the key to match commands in `%.commands...%`. Command names are listed in the command list. The default matching list is:

```json
{
  "c": "compile",
  "ch": "check",
  "chd": "chdata",
  "com": "command",
  "con": "config",
  "j": "judge",
  "r": "run"
}
```

If matching fails, use the first parameter as the command. If there are no parameters or no corresponding command, enter the entry command.

## Notes

**Note**: The settings `.max_process_num` and `.max_thread_num` represent the magnitude of the maximum number of processes and threads. Adjust these parameters based on CPU parallelism, memory, and disk read/write performance; otherwise, high CPU usage might cause system crashes, or high disk read/write latency could lead to program exceptions.

The sum of the running time of all programs in a single run is not recommended to be less than $5$ ms. Otherwise, it might result in program exceptions.

## Commands

### orita

`orita [[/help] | [/reset] | [/clear]]`

The entry command for the command-line tool.

`/help`: Display help information.

`/reset`: Reset configurations.

`/clear`: Clear configurations.

### run

`orita run [/help] [/file=file] [/checker=file] [/time=time]`

Run the specified file and redirect input. Then, compare the output with the input. All files are appended with the `%.data.compile_argu%` parameter during compilation. Data will be stored in the `%.data.data_dir%/` directory.

`/help`: Display help information.

`/file=file`: Specify the source file (automatically adds `.cpp` as the extension if not specified). If this parameter is not present, the previous source file setting will be used.

`/checker=file`: Specify the evaluation file (automatically adds `.cpp` as the extension if not specified). If this parameter is not present, the previous evaluation file setting will be used.

`/time=time`: Modify the default run time limit (in milliseconds).

### chdata

`orita chdata [/help] [/ifile[=file]] [/ofile[=file]] [/time=time]`

Used to modify the input and output data of the `run` command.

`/help`: Display help information.

`/ifile[=file]`: Specify the input data file (reads from standard input if not specified).

`/ofile[=file]`: Specify the output data file (reads from standard input if not specified).

`/time=time`: Modify the default run time limit (in milliseconds).

### check

`orita check [/help] [/ifile=file] [/ofile=file] [/afile=file] [/checker=file] [/num=num [/multithread]] [/time=time]`

Use data generators, standard code, and source code for stress testing. All files are appended with the `%.data.compile_argu%` parameter during compilation. Data will be stored in the `%.data.data_dir%/` directory.

`/help`: Display help information.

`/ifile=file`: Specify the data generator (automatically adds `.cpp` as the extension if not specified). If this parameter is not present, the previous data generator setting will be used.

`/ofile=file`: Specify the standard code (automatically adds `.cpp` as the extension if not specified). If this parameter is not present, the previous standard code setting will be used.

`/afile=file`: Specify the source code (automatically adds `.cpp` as the extension if not specified). If this parameter is not present, the previous source code setting will be used.

`/checker=file`: Specify the evaluation file (automatically adds `.cpp` as the extension if not specified). If this parameter is not present, the previous evaluation file setting will be used.

`/num=num`: Number of stress tests. If this parameter is not present, stress testing will not be conducted; it is only for setting parameters.

`/time=time`: Modify the default run time limit (in milliseconds).

`/multithread`: Enable multithreading. Enabling multithreading will increase the runtime of a single test program by several times and is related to the number of running processes and the computer's parallel performance. Therefore, the `TLE` results may not be accurate.

### judge

`orita judge [data] [/help] [/file=file] [/checker=file] [/time=time] [/isuf=suf] [/osuf=suf] [/multithread]`

For a given data file and source code, generate data points from the data file with a specified suffix, and get all results from the source code. All files are appended with the `%.data.compile_argu%` parameter during compilation. Data will be stored in the `%.data.data_dir%/` directory.

`data`: Specify the data file. If this parameter is not present, evaluation will not be conducted; it is only for setting parameters.

`/help`: Display help information.

`/file=file`: Specify the source file (automatically adds `.cpp` as the extension if not specified). If this parameter is not present, the previous source file setting will be used.

`/checker=file`: Specify the evaluation file (automatically adds `.cpp` as the extension if not specified). If this parameter is not present, the previous evaluation file setting will be used.

`/time=time`: Modify the default run time limit (in milliseconds).

`/isuf=suf`: Specify the input file suffix (default is `.in`).

`/osuf=suf`: Specify the output file suffix (default is `.out`).

`/multithread`: Enable multithreading. Enabling multithreading will increase the runtime of a single test program by several times and is related to the number of running processes and the computer's parallel performance. Therefore, the `TLE` results may not be accurate.

### compile

`orita compile [file] /help [[/run] | [/trun]] [/carg=args] [/arg=args]`

Compile the specified source file and compile parameters.

`file`: Specify the source file.

`/help`: Display help information.

`/run`: Specify the source file (automatically adds `.cpp` as the extension if not specified), compile and run it. Using this parameter will not output compilation information.

`/trun`: Specify the source file (automatically adds `.cpp` as the extension if not specified), run the executable file corresponding to the source file. Using this parameter will not output compilation information.

`/carg=args`: Specify compilation parameters.

`/arg=args`: Specify run parameters.

### config

`config [key [value]] [/help] [[/settings [/global] [/local] [[/add=key] | [/load=key] | [/merge=key]]] | [/files]]`

View or modify configurations.

`key`: Specify the key.

`value`: Specify the value.

`/help`: Display help information.

`/settings`: If no `key` is provided, output the `settings.json` file. If `key` is provided but no `value`, output the value of `key`. If `key` is followed by `%{RESET}%`, reset that item to its default value, which is read from `%{FILE_PATH}%/files/settings.json`. If `key` is followed by `value`, modify the value of `key` to `value`.

`/global`: Specify as a global setting.

`/local`: Specify as a local setting in the current directory.

`/add=key`: Upload settings to a settings file named `key`.

`/load=key`: Load a settings file named `key` into the local settings in the current directory.

`/merge=key`: Merge a settings file named `key` (overwrite if there are conflicts) into the local settings in the current directory.

`/files`: If no `num` is provided, output the `file.json` file. If `num` is provided but no `value`, output the value of the file with the number `num`. If `num` is followed by `%{RESET}%`, reset that file to its default value, which is read from `%{FILE_PATH}%/files/%{OS_NAME}%/file.json`. If `num` is followed by `value`, set the value of that file to `value`.

### command

`command [commands]`

Execute commands after replacing environment variables.

`/help`: Display help information.

## Uninstallation

To uninstall Orita, use the `orita clear` command to delete all configuration files and then delete the source files in the `Orita` directory.

You can also uninstall CMake, GCC, MSVC, and other components if they are no longer needed.

## Dependencies

This project uses the following third-party libraries:

- Lohmann, N. (2022). JSON for Modern C++ (Version 3.11.2) [Computer software]. [https://github.com/nlohmann](https://github.com/nlohmann)
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
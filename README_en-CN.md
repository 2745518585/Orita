[zh-CN](./README.md) | en-CN

# Orita

[Orita](https://github.com/2745518585/Orita)

An OI (Olympiad in Informatics) tool developed by [赵悦岑](https://github.com/2745518585/). It includes features such as judging, stress testing, and data generation, and is primarily written in C++.

[vscode-Orita](https://github.com/2745518585/vscode-Orita)

The vscode extension for Orita.

## Installation

Before installing Orita, ensure that your environment is either Windows or Linux, and that the following applications are installed on your computer:

- [CMake](https://cmake.org/)

Obtain the Orita source code with the following command:

```
$ git clone https://github.com/2745518585/Orita
```

To compile the source code, run the following commands in the `Orita/` directory:

```
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

Run `init.bat | init.sh` in the `Orita/` directory to compile the entry file. Ensure that the executable files in the `Orita/bin/` directory can be globally accessed and can be moved to any location. When using CMake to generate, the location of the source files will be automatically output. If you move the source files, please run `init.bat | init.sh` in the `Orita/` directory.

To use Orita properly, make sure that your computer has a C++ compiler g++ that supports C++14 and can be globally accessed from the command line.

Use the `orita reset` command to initialize and clear the configuration.

## Usage

### Parameter System

The parameter format for all commands is `/i arg ...` or `-i arg`, and the scope of each parameter extends to the next parameter or the end.

If a parameter contains spaces, enclose it in quotes, and use `\"` to include quotes within the parameter.

### Built-in Files

Orita includes some built-in files for convenience, which are located in the file cache after initialization. If you manually modify the files in the following slots, some commands may produce errors.

Slot `$0$`: Empty, always returns `$0$`.

Slot `$1$`: File comparator, takes three parameters: `in`, `out`, and `ans` files, and returns the comparison result between `out` and `ans`, ignoring trailing spaces and line endings.

### File Name Replacement

Use `%[0-999]` to replace it with the file name in the slot, such as `%1`, which represents the file stored in slot `$1$`.

Use `%...%` in file names to replace it with environment variables `...`.

Use `%%` in file names to replace it with `%`.

## Commands

### reset

`orita reset`

Reset the configuration.

### clear

`orita clear`

Delete the configuration files.

### run

`run [/f <file>] [/c [chk_file]] [/t <time>]`

#### Description

Run the given file with predefined standard input and output and provide the results. All files are compiled with the `JUDGING` macro defined.

#### Parameter List

`/f <file>`: Specify the source file (automatically adds a `.cpp` extension if not present). If this parameter is not provided, the last set source file is used.

`/c [chk_file]`: Specify the `checker` file (automatically adds a `.cpp` extension if not present). If no file is specified, the last set source file is used. If this parameter is not used, the `settings: default_checker` file is used.

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

`check [/n <sum>] [/f <in_file> <out_file> <ans_file> | [[/if <in_file>] [/of <out_file>] [/af <ans_file>]]] [/c [chk_file]] [/t <time>]`

#### Description

Perform stress testing with a given data generator, standard code, and source code. All files are compiled with the `JUDGING` macro defined. Data will be stored in the `data/` directory.

#### Parameter List

`/n <sum>`: Number of stress testing iterations. If not provided, stress testing will not be performed and will be considered as parameter setting only.

`/f <in_file> <out_file> <ans_file>`: Specify the source file (automatically adds a `.cpp` extension if not present). If no file is specified, the last set source file is used.

`/c <chk_file>`: Specify the `checker` file (automatically adds a `.cpp` extension if not present). If no file is specified, the last set source file is used. If this parameter is not used, the `settings: default_checker` file is used.

`/if <in_file>`: Specify the `in` file (automatically adds a `.cpp` extension if not present). If no file is specified, the last set `in` file is used. This parameter conflicts with `/f` and has lower priority than `/f`.

`/of <out_file>`: Specify the `out` file (automatically adds a `.cpp` extension if not present). If no file is specified, the last set `out` file is used. This parameter conflicts with `/f` and has lower priority than `/f`.

`/af <ans_file>`: Specify the `ans` file (automatically adds a `.cpp` extension if not present). If no file is specified, the last set `ans` file is used. This parameter conflicts with `/f` and has lower priority than `/f`.

`/t <time>`: Modify the default runtime limit (in milliseconds).

### judge

`judge [/f <file>] [/c [chk_file]] [/d data...] [/is <infile_suf>] [/os <outfile_suf>] [/t <time>]`

#### Description

Given data files and source code, create data points by finding input and output files with specified extensions in the data files, and obtain all results of the source code. All files are compiled with the `JUDGING` macro defined. Data will be stored in the `data/` directory.

#### Parameter List

`/f <file>`: Specify the source file (automatically adds a `.cpp` extension if not present). If this parameter is not provided, the last set source file is used.

`/c [chk_file]`: Specify the `checker` file (autom

atically adds a `.cpp` extension if not present). If no file is specified, the last set source file is used. If this parameter is not used, the `settings: default_checker` file is used.

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

`config [[/s [key [value]]] | [/f [key [value]]]]`

#### Description

View and modify configurations.

#### Parameter List

`/s [key [value]]`: If `key` is not provided, output the `settings.json` file. If `key` is provided and `value` is not provided, output the value of `key`. If `value` is provided, modify the value of `key` to `value`. Different layers of keys in `key` are separated by `/`.

`/f [num [value]]`: If `num` is not provided, output the `file.json` file. If `num` is provided and `value` is not provided, output the value of the file with the number `num`. If `value` is provided, set the file with number `num` to `value`.
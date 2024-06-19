en-CN | [zh-CN](./README.md)

# Orita

[Orita](https://github.com/2745518585/Orita)

Orita is an OI tool developed by [Zhao Yuecen](https://github.com/2745518585/), mainly written in C++, including features such as evaluation, comparing outputs, data generation, and more.

## Installation

### Build

Before installing Orita, ensure the environment is either Windows or Linux, and that the following applications are installed on your computer:

- [CMake](https://cmake.org/) (3.15+)

Additionally, install GCC 11.4+ or MSVC 2022+.

For Windows computers, download and install the following applications:

- [CMake](https://cmake.org/)
- [MinGW](https://www.mingw-w64.org/downloads/)
- [Visual Studio](https://visualstudio.microsoft.com/downloads/)

For Linux computers, run the following commands to install CMake and GCC:

```shell
$ sudo apt-get install cmake
$ sudo apt-get install g++
```

After installation, use the following commands to obtain the Orita source code:

```shell
$ git clone https://github.com/2745518585/Orita
$ git submodule init
$ git submodule update
```

In the `Orita/` directory, use the following commands to compile the source code:

```shell
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

### Download

You can find the latest releases on [GitHub](https://github.com/2745518585/Orita/releases) and download the compiled file package for the corresponding platform.

### Initialization

Ensure that the entry file `orita.exe` or `orita` in the executable directory `bin/bin/` can be globally called. You can move the entry file to any location and modify its name to change the entry command name.

If using CMake to generate, it will automatically output the location of the executable file. If the executable file is moved, execute `path.bat` or `path.sh` in the directory where the executable file is located.

To use Orita normally, ensure a C++ compiler supporting C++14 (g++) is installed on the computer and can be globally called in the console.

Use the command `orita /r` (Windows) or `orita -r` (Linux) to initialize and clear the configuration.

## Usage

### Parameter System

In Windows, use DOS-style command-line parameters, and in Linux, use Unix-style command-line parameters. The following examples use DOS-style.

### Built-in Files

Orita pre-sets some files for convenience, located in the configuration file directory after initialization.

`0.cpp`: An empty file, always returns $0$.

`1.cpp`: A file comparator, with three parameters: `in`, `out`, `ans` files, returning the comparison result of `out` and `ans` ignoring trailing spaces and end-of-line characters.

### Environment Variable Substitution

All data read from command-line parameters or configuration files will undergo environment variable substitution. Data read from standard input will not be substituted.

* In filenames, `%...%` will be replaced by the environment variable `...`. The program will match the following environment variables in sequence:
  - Expressions like `%*[0-999]%` will be replaced with the corresponding file name in `file.json`, e.g., `%*1%` represents the file name numbered $1$.
  - Expressions like `%....%` will be replaced with the corresponding value in the settings system, e.g., `%.data.data_dir%` represents the value of `/data/data_dir` in the settings. If the value is a `string`, it will be directly substituted; otherwise, it will be serialized and then substituted.
  - Expressions like `%#...%` will be replaced with the corresponding value in the passed parameters, e.g., `%#file%` represents the value of the parameter `file`.
  - `{APPDATA_PATH}`: On Windows, it is `%APPDATA%/Orita`; on Linux, it is `%HOME%/.Orita`.
  - `{FILE_PATH}`: The directory of the executable file.
  - `{RUNNING_PATH}`: The running directory.
  - `{OS_NAME}`: The operating system name.
  - `{TERMINAL_WIDTH}`: The terminal width.
  - Otherwise, it returns the system environment variable `...`.

- In filenames, `%%` will be replaced by `%`.

### Settings System

The settings filename is `settings.json`, with three levels:

1. Default settings file, located at `%{FILE_PATH}%/files/settings.json`.
2. Global settings file, located at `%{APPDATA_PATH}%/settings.json`.
3. Local settings file, located at `.orita/settings.json`.

The priority of these settings files increases from top to bottom. The effective local settings file for a single run is the `.orita/settings.json` file in the current and ancestor directories of `%{RUNNING_PATH}%`, with priority increasing from shallow to deep directories.

When querying and modifying settings, the default priority matches from high to low. If the current setting value is `null` or invalid, it will query the file with the next highest priority.

In the settings, `%{SETTINGS_PATH}%` will be preferentially replaced by the corresponding directory of the settings file (prior to environment variable substitution). Whenever a local settings file is detected in the current directory or a command modifies the local settings file's directory, the latest settings file will be output when the program ends. Directories without settings files and without modifications will not output.

If you need to represent an object in the settings as a string, use `.` to separate different levels of directories, e.g., `.data.data_dir`. In the text below, expressions like `%.data.data_dir%` represent the corresponding object in the settings.

The settings file can store a list in the `.~list` location of the global settings file and can be loaded into the configuration file of the current directory.

#### Settings Information

- `commands`: Command matching list.
- `compiler`: Compiler-related settings.
  - `argu`: Compilation options.
  - `command`: Path to the compiler.
  - `skip_compiled`: Whether to skip compilation when the source file is not newer than the executable file.
  - `time_limit`: Compilation time limit.
  - `try_times`: Number of retries after compilation timeout.
- `data`: Evaluation-related settings.
  - `ans_args`: Parameter list passed to `ans`. Parameters `infile`, `outfile`, `ansfile`, `chkfile` are the paths to input, output, answer, and comparison information files, respectively.
  - `ansfile`: Default answer data file.
  - `chk_args`: Parameter list passed to `checker`. Parameters `infile`, `outfile`, `ansfile`, `chkfile` are the paths to input, output, answer, and comparison information files, respectively.
  - `chk_exit_code`: Return value of `checker` when encountering an answer error, matched using a regular expression in decimal.
  - `chk_outputs`: When set to `"on"`, the default comparator `%*1%` outputs information to the console.
  - `chkfile`: Default comparison information file.
  - `compile_argu`: Evaluation compilation options.
  - `data_dir`: Directory for storing data files.
  - `data_file`: Location for output data files after batch evaluation or comparing outputs, with `.in`, `.out`, `.ans`, `.txt` suffixes added. Parameters `testcase_name` (data point name), `result` (evaluation result), `short_result` (evaluation result abbreviation), `info` (test point information, see *Program Evaluation*), `runned_sum` (number of evaluations completed), `outputed_sum` (number of outputs completed) are provided.
  - `in_args`: Parameter list passed to `data_maker`. Parameters `infile`, `outfile`, `ansfile`, `chkfile` are the paths to input, output, answer, and comparison information files, respectively. Parameter `seed` is the random seed for the test point, and parameter `testcase_name` is the test point name.
  - `infile`: Default input data file.
  - `info_pre`: Test point information prefix.
  - `out_args`: Parameter list passed to `std`. Parameters `infile`, `outfile`, `ansfile`, `chkfile` are the paths to input, output, answer, and comparison information files, respectively.
  - `outfile`: Default output data file.
  - `time`: Evaluation time limit.
- `exefile`: Executable file path. Parameters `file` (source file path without suffix), `filename` (source file name without suffix), `filepath` (directory of the source file) are provided.
- `max_process_num`: Maximum number of processes.
- `max_thread_num`: Maximum number of threads.
- `runtime_limit`: Time limit for running child processes.
- `show_file_info`: Whether to display file information during evaluation.
- `~list`: Settings list.

### Child Process Environment

All child processes contain the main process environment variables and additionally define the following environment variables:

- File environment variables, with keys like `file[0-999]`.
- Settings environment variables, with keys like `....`.
- Built-in environment variables.
- During batch evaluation without multithreading, `runned_sum` (number of evaluations completed) and `outputed_sum` (number of outputs completed).

### Command Matching

Commands are matched with the first parameter against `%.commands...%`, where command names are listed in the command list. The default matching list is:

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

If no match is found, the first parameter itself is used as the command. If no parameters are provided or there is no corresponding command, it defaults to the entry command.

### Thread and Process Management

> [!WARNING]
> $\color{red}{\text{Attention}}$: The settings `%.max_process_num%` and `%.max_thread_num%` represent the scale of maximum processes and threads, respectively. Adjust these parameters based on CPU parallel performance, memory, and disk read/write speed to avoid system crashes due to excessive CPU usage or program anomalies caused by high disk read/write latency.

### Program Evaluation

During evaluation, both `%.compiler.argu%` and `%.data.compile_argu%` compile options are used by default, including the macro `JUDGING`.

For evaluation, standard input/output and standard error output (`stderr` to console) require `flush` operations to push data. It is recommended to use `iostream` or `orita::auto_flush()` for automatic output pushing. When reading from files, the pipeline write end is automatically closed after the file ends. For console input, entering `EOF` at the end is recommended. To preserve existing output (including output to files and the console) in case of abnormal program termination, `flush` operation is necessary.

During evaluation, any program can output a string to the comparison information file's first line in the form `%.data.info_pre%{...}`, and after evaluation, the content within `{...}` will be read as test point information.

The resulting data files from evaluation will be stored in `%.data.data_dir%`.

### Others

When specifying a C++ source file for all commands, the default suffix is `cpp`. If the suffix is not `cpp`, `.cpp` will be automatically appended, resulting in an executable file that is passed to `%.exefile%` after the source file.

## Commands

### orita

`orita [[/help] | [/reset] | [/clear] | [/path]]`

Entry command for the command-line tool.

`/help`: Display help information.

`/reset`: Reset configuration.

`/clear`: Clear configuration.

`/path`: Get file path.

### run

`orita run [/help] [/file=file] [/checker=file] [/time=time] [/dorecompile]`

Run specified file and redirect input, then compare with output data.

`/help`: Display help information.

`/file=file`: Specify source file. If absent, use the last set source file.

`/checker=file`: Specify evaluation file. If absent, use the last set evaluation file.

`/time=time`: Modify default runtime limit (milliseconds).

`/dorecompile`: Force recompilation.

### chdata

`orita chdata [/help] [/ifile[=file]] [/ofile[=file]] [/time=time]`

Modify input and output data for `run` command.

`/help`: Display help information.

`/ifile[=file]`: Specify input data file (read from standard input if absent).

`/ofile[=file]`: Specify output data file (read from standard input if absent).

`/time=time`: Modify default runtime limit (milliseconds).

### check

`orita check [/help] [/ifile=file] [/ofile=file] [/afile=file] [/checker=file] [/num=num [/multithread]] [/time=time] [/dorecompile]`

Use data generator, standard code, and source code for stress testing. Test point names are typically numbers unless multithreading is enabled.

`/help`: Display help information.

`/ifile=file`: Specify data generator. If absent, use the last set data generator.

`/ofile=file`: Specify standard code. If absent, use the last set standard code.

`/afile=file`: Specify source code. If absent, use the last set source code.

`/checker=file`: Specify evaluation file. If absent, use the last set evaluation file.

`/num=num`: Number of stress tests. If absent, no stress testing is performed; it's only a configuration parameter.

`/time=time`: Modify default runtime limit (milliseconds).

`/multithread`: Enable multithreading. Multithreading increases the runtime of individual tests several times and is related to the number of processes and computer parallel performance. Therefore, `TLE` results may not be accurate.

`/dorecompile`: Force recompilation.

### judge

`orita judge [data] [/help] [/file=file] [/checker=file] [/time=time] [/isuf=suf] [/osuf=suf] [/ofile=file] [/multithread] [/dorecompile]`

For given data files and source code, generate data points from input and output files with specified suffixes, then obtain all results from the source code. Test point names are typically the input and output file names unless multithreading is enabled.

`data`: Specify data file. If absent, no evaluation is performed; it's only a configuration parameter.

`/help`: Display help information.

`/file=file`: Specify source file. If absent, use the last set source file.

`/checker=file`: Specify evaluation file. If absent, use the last set evaluation file.

`/time=time`: Modify default runtime limit (milliseconds).

`/isuf=suf`: Specify input file suffix. Default is `.in`.

`/osuf=suf`: Specify output file suffix. Default is `.out`.

`/ofile=file`: Specify standard output file; use this source file output as the output file when no output file is found.

`/multithread`: Enable multithreading. Multithreading increases the runtime of individual tests several times and is related to the number of processes and computer parallel performance. Therefore, `TLE` results may not be accurate.

`/dorecompile`: Force recompilation.

### compile

`orita compile [file] [/help] [[/run] | [/trun]] [/carg=args] [/arg=args] [/dorecompile]`

Compile specified source file and compilation arguments.

`file`: Specify source file.

`/help`: Display help information.

`/run`: Specify source file, compile, and run. Using this parameter suppresses compilation information output.

`/trun`: Specify source file, run executable corresponding to this source file. Using this parameter suppresses compilation information output.

`/carg=args`: Specify compilation arguments.

`/arg=args`: Specify runtime arguments.

`/dorecompile`: Force recompilation.

### config

`config [key [value]] [/help] [[/settings [/global] [/local] [[/add=key] | [/load=key] | [/merge=key]]] | [/files]]`

View or modify configurations.

`key`: Specify key.

`value`: Specify value.

`/help`: Display help information.

`/settings`: If `key` is not provided, output `settings.json` file. If `key` is provided but `value` is not, output the value of `key`. If `%{RESET}%` is appended to `key`, reset the item to default value, which is read from `%{FILE_PATH}%/files/settings.json`. If `value` is appended to `key`, modify the value of `key`.

`/global`: Specify global settings.

`/local`: Specify local settings for the current directory.

`/add=key`: Upload settings to a file named `key`.

`/load=key`: Load settings from a file named `key` to the local directory.

`/merge=key`: Merge (overwrite non-matching) settings from a file named `key` to the local directory.

`/files`: If `num` is not provided, output `file.json` file. If `num` is provided but `value` is not, output the value of the file numbered `num`. If `%{RESET}%` is appended to `num`, reset the file to default value, which is read from `%{FILE_PATH}%/files/file.json`. If `value` is appended to `num`, set the value of the file to `value`.

### command

`command [commands]`

Execute commands after replacing environment variables.

`/help`: Display help information.

## Header Files

Header files are located by default in `${FILE_PATH}%/orita.hpp`, and this directory is automatically added to the include path in compilation options. They can be directly referenced by `#include"orita.hpp"`. Compilation requires C++14 or higher standard.

All functions, variables, and classes are within `namespace orita`.

#### `std::mt19937 rd`

Random number generator of type `std::mt19937`.

#### `void `register_rnd`(int argc, char **argv, unsigned int pos = 1U)`

Function to register seed for random number generator.

- **Parameters**: 
  - `argc`: Number of command-line arguments.
  - `argv`: Array of command-line arguments.
  - `pos`: Position of seed in parameters.

#### `void register_rnd(unsigned seed)`

Function to register specified random number seed.

- **Parameters**: 
  - `seed`: Random number seed to register.

#### `unsigned long long rnd()`

Function to generate unsigned long long random number.

- **Returns**: Generated random number.

### Translation

#### `template<class Ty> std::enable_if<std::is_integral<Ty>::value, Ty>::type rnd(const Ty &lim)`

Generates a random number within the range `[0, lim)` when the input parameter type is an integer.

- **Parameters**: 
  - `lim`: Upper limit of the random number.
- **Returns**: The generated random number.

#### `long long rnd(const long long &lim)`

Generates a long integer random number within the range `[0, lim)`.

- **Parameters**: 
  - `lim`: Upper limit of the random number.
- **Returns**: The generated random number.

#### `template<class Ty> std::enable_if<std::is_integral<Ty>::value, Ty>::type rnd(const Ty &llim,const Ty &ulim)`

Generates a random number within the range `[llim, ulim]` when the input parameter type is an integer.

- **Parameters**: 
  - `llim`: Lower limit of the random number.
  - `ulim`: Upper limit of the random number.
- **Returns**: The generated random number.

#### `long long rnd(const long long &llim,const long long &ulim)`

Generates a long integer random number within the range `[llim, ulim]`.

- **Parameters**: 
  - `llim`: Lower limit of the random number.
  - `ulim`: Upper limit of the random number.
- **Returns**: The generated random number.

#### `template<class lTy, class uTy> class rdl<lTy, uTy>`

Generates a random number within specified upper and lower limits.

Note: Class templates cannot be deduced in C++14 and below, explicit template definitions are required.

- **Members**
  - `lTy llim`: Lower limit of the random number.
  - `uTy ulim`: Upper limit of the random number.
  - `auto rdl<lTy, uTy>::operator()() const`: Returns the result of `rnd(llim,ulim)`.
- **Constructors**
  - `rdl()`: Default constructor.
  - `rdl<lTy, uTy>::rdl(const uTy &lim)`: Specifies the upper limit.
  - `rdl(const lTy &llim, const uTy &ulim)`: Specifies the lower and upper limits.

#### `template<class Ty1, class Ty2> class pr<Ty1, Ty2>`

Key-value pair with a separator.

- **Base**: `std::pair<Ty1,Ty2>`.
- **Members**: 
  - `std::string sep`: Separator.
- **Constructors**: 
  - `pr(const Ty1 &first, const Ty2 &second, const std::string &_sep = " ")`: Initializes the key-value pair and separator.
  - `pr(const std::pair<Ty1, Ty2> &_pair, const std::string &_sep = " ")`: Initializes from an existing key-value pair and separator.

This class facilitates structured binding via the base class `std::pair`.

#### `template<class Ty1, class Ty2> std::ostream &operator<<(std::ostream &out, const pr<Ty1, Ty2> &pr)`

Outputs a key-value pair.

- **Parameters**: 
  - `out`: Output stream.
  - `pr`: Key-value pair.
- **Returns**: The generated random number.

#### `template<class Ty1, class Ty2> struct _NEQ<Ty1, Ty2>`
#### `template<class Ty1, class Ty2> struct _LES<Ty1, Ty2>`
#### `template<class Ty1, class Ty2> struct _GRE<Ty1, Ty2>`
#### `template<class Ty1, class Ty2> struct _LOE<Ty1, Ty2>`
#### `template<class Ty1, class Ty2> struct _GOE<Ty1, Ty2>`

- **Members**: 
  - `bool operator()(const Ty1 &s1,const Ty2 &s2) const `: Returns the comparison result of two numbers, indicating not equal, less than, greater than, less than or equal to, and greater than or equal to.

#### `rnd_pair(...,const std::string &seq)`

Generates pairs of random numbers that satisfy a comparison function.

The comparison function can be passed as a function parameter, class, or structure as a template. The passed class or structure must be callable using `operator()` with two numbers as parameters, returning `bool`. (Class templates cannot be deduced in C++14 and below; the passed class must support no template, one template (same type for both numbers), or two templates (different types for each number)).

For the generator of pairs of random numbers, you can directly specify upper and lower limits, or specify one or two generators. Generators are instances of classes or structures or lambda expressions that can be called with no parameters using `operator()`, returning `bool`. When two parameters are specified, whether `operator()` can be called is used to determine whether it is used as a generator or as a range of random numbers.

- **Parameters**: 
  - `seq`: Separator.
- **Returns**: Generated pair of random numbers.

**Usage Examples**: 
- `rnd_pair(1,10,[&](auto x1,auto x2){return x1<x2;});`
- `rnd_pair<_LES>(1,10);`
- `rnd_pair<std::less>(1,1e5);`
- `rnd_pair<std::less<int>>(1,1e5);`
- `rnd_pair<_LES>([&](){return rnd(1,10);});`
- `rnd_pair<_LES>(rdl<int,int>(1,10));`
- `rnd_pair<_LES>(rdl<int,int>(1,10),rdl<int,int>(1,1e5));`
- `rnd_pair<_LES>(rdl(1,10));` (C++17 and above)
- `rnd_pair<_LES>(rdl(1,10),rdl(1,1e5));` (C++17 and above)

#### `std::vector<unsigned int> rnd_range(unsigned int tot)`

Generates a random permutation.

- **Parameters**: 
  - `tot`: Length of the permutation.
- **Returns**: Random permutation.

#### `std::vector<std::pair<unsigned int, unsigned int>> rnd_tree(unsigned int tot)`

Generates a random tree.

- **Parameters**: 
  - `tot`: Size of the tree.
- **Returns**: Edge set of the random tree.

#### `std::vector<std::pair<unsigned int, unsigned int>> rnd_ucgraph(unsigned int totp, unsigned int tote)`

Generates a random undirected connected graph.

- **Parameters**: 
  - `tot`: Size of the graph.
- **Returns**: Edge set of the random undirected connected graph.

#### `void register_info(int argc, char **argv, unsigned int pos = 3U)`

Registers the output file for test point information.

- **Parameters**: 
  - `argc`: Number of command-line arguments.
  - `argv`: Array of command-line arguments.
  - `pos`: Position of the file.

#### `template<class Ty> void print_info(const Ty &info, const std::string &pre = default_pre)`

Outputs test point information. `default_pre` is the value from the environment variable `.data.info_pre`, defaulting to `***** info: `.

- **Parameters**: 
  - `info`: Test point information to output.
  - `pre`: Prefix for test point information.

#### `void auto_flush()`

Automatically flushes standard output and standard error output buffers.

#### `void register_all(int argc, char **argv)`

Registers all required information with default parameters.

- **Parameters**: 
  - `argc`: Number of command-line arguments.
  - `argv`: Array of command-line arguments.

## Uninstallation

To uninstall Orita, use the command `orita /clear` to delete all configuration files, and then delete the source files under the `Orita` directory.

If CMake, GCC, MSVC, etc., are no longer needed, uninstall them as needed.

## Dependencies

This project uses the following third-party libraries:

- Lohmann, N. (2023). JSON for Modern C++ (Version 3.11.3) [Computer software]. https://github.com/nlohmann
- [gabime/spdlog](https://github.com/gabime/spdlog)
- [ikalnytskyi/termcolor](https://github.com/ikalnytskyi/termcolor)
- [pocoproject/poco](https://github.com/pocoproject/poco)

## Open Source License

[MIT](LICENSE) LICENSE

## Acknowledgments

This project is supported by technical contributions from the Sukwants, Pond Ink team, and syysongyuyang.

[![0](https://avatars.githubusercontent.com/u/95968907?s=64&v=4)](https://github.com/Sukwants)
[![0](https://avatars.githubusercontent.com/u/145256515?s=64&v=4)](https://github.com/Pond-Ink)
[<img src="https://avatars.githubusercontent.com/u/123732645" height=64x width=64x alt>](https://github.com/syysongyuyang)

Related projects:
- [vscode-Orita](https://github.com/2745518585/vscode-Orita) - VSCode extension for Orita
- [Atiro](https://github.com/Sukwants/Atiro) - Useless OI Tools
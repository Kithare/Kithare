![Kithare](assets/banner.png) <br/>
![State](https://img.shields.io/badge/state-unfinished-ff2222.svg)
![Version](https://img.shields.io/badge/version-0.0.0-00ffaa.svg)

# Kithare
 An open source general purpose statically-typed cross-platform interpreted Python and C like programming language.

## Community / Contact
- [Discord server](https://discord.gg/hXvY8CzS7A)

## Building
- Kithare uses a python helper script to make building easier. So in order to
build Kithare, you need Python 3.6 or above installed
- For advanced usage, you may checkout the "build.py" file, which contains instructions on how to
use the build script to achieve more things
- A basic HOWTO to building Kithare is given below

### Windows
#### MSVC / Visual Studio
- Make sure you have Visual Studio 2019 with C++ build tools and Windows 10 SDK installed.
- Run `python3 build.py --msvc-deps`. It'll download the dependencies such as SDL and create the build destination directory with the dependencies' DLLs copied.
- Open the solution `Kithare.sln`.
- See `Kithare` in the Solution Explorer. If the name's not bolded, right click and click "Set as Startup Project".
- You can now build it by clicking "Local Windows Debugger".

#### MinGW
- Make sure you have MinGW (aka MinGW-w64) installed, and its `bin` directory be put in 
the PATH.
- Run `python3 build.py`. It will automatically download the dependencies such as SDL and 
compile Kithare.

### Other platforms
- Make sure you have the GCC compiler.
- Install the development libraries for these: `SDL2`, `SDL2_mixer`, `SDL2_image`, `SDL2_ttf`, `SDL2_net`. You may use your disto's package manager to do this.
- A recommended way to do this on Mac is to use Homebrew. Just run
`brew install gcc sdl2 sdl2_image sdl2_mixer sdl2_net sdl2_ttf`
- Run `python3 build.py`.

## Contributing
- New Contributors are most welcome to come and help us in making Kithare better.
- If you want to contribute a major change, it's a good idea to discuss with us
first, either on our discord server, or on GitHub issues section.
- It is expected that contributors follow code formatting rules while contributing
to Kithare. If any *unclean* code is opened up in a PR, that PR will be waited for a cleaning commit.

### Naming convention
- `snake_case` for variable, namespace, file, and folder names.
- `SCREAMING_SNAKE_CASE` for constants, enum members, and macros (An exception for `khPrint` and `khPrintln` as they are intended to be like functions).
- `camelCase` (Or some call `lowerCamelCase`) for function, method, and label names.
- `PascalCase` for classes, structs, and enums.

### Coding style
```cpp
/* All kinds of comments should use multi-line comment */

/* Opening curly braces should be in the same line */
if (condition) {

}

/* Pointers and references should be placed to the side of the type */
int* var = nullptr;
int& reference_var = *var;

/* Always explicitly specify `const` for values that aren't meant to be changed in the function.
* For strings and vectors, use a `const` reference.
*/
void function(const std::string& str, const int value) {

}

/* NO */
using namespace std;
using namespace kh;
```

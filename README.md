<p align="center">
    <img
      src="https://github.com/NeoResearch/neoresearch.github.io/blob/master/assets/images/logo/Gemcut-butterfly/butterfly-banner.png"
       />
</p>

# neopt
## Portable Neo for all things

This project intends to provide easy access to [NEO blockchain](github.com/neo-project) for all things.


### Why chosing C/C++ language for that?
Existing frameworks use high-level languages that may not be suitable for very lightweight architectures,
such as microcontrollers with very limited computing capabilities.

C/C++ is interoperable with nearly all existing languages, so the idea is to provide modules that can be
reused on other projects (on other languages too).

#### C++ Standard
Currently, C++11 is adopted, in order to keep the best compatibility between conversors and compilers. However, it is recommended to migrate to C++17 as soon as possible, if this does not break compatibility with any existing modules and tools.

#### vscode IDE
If using vscode IDE, it is recommended to install the following extensions:
* C/C++ (currently 0.23.0-insiders2)
* C++ Intellisense (currently 0.2.2)
* GoogleTest Adapter (currently 1.8.3)

#### C++ Format Style
The currently adopted style for C++ is `Mozilla`, with indentation level set to 3.
Recommended configuration for vscode:
```json
{
    "[cpp]": {
        "editor.tabSize" : 3,
        "editor.detectIndentation": false
    },
    "C_Cpp.clang_format_fallbackStyle": "{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}"
}
```

#### Variable Naming Style
The naming style for variables and methods is based on `C#` language. 
So, CamelCase is used and `public` variables start with upper-case letters, while `private` and `local` variables start with lower-case.
The idea is to preseve maximum compatibility with reference project (which is on C#).

Anything that is beyond the scope of the reference project can use classic CamelCase `C++` naming (for example, starting variables with lower-case).

#### Ensuring code style
You can use `make lint` command to format files automatically (using `clang-format`) and also the linter to verify programming practices (using `clang-tidy`).

### Which are the main modules?

The repository is divided into three main parts, located on `src` folder: `neo2`, `neo` and `common`.

```
- src\
       common (neo2 and neo3 stuff)
       neo    (neo3 project)
       cli    (neo3 project)
       nvm    (neo3 project)
       neo2   (neo2 project)
       cli2   (neo2 project)
```

#### common
The `common` folder includes common data structures and cryptography technology for Neo blockchain, in all its versions.

#### neo (or neo3)

The `neo` (or `neo3`) project comprises three folders, related to Neo Blockchain version 3 and beyond: [cli](https://github.com/neo-project/neo-cli) (command-line interface), [neo](https://github.com/neo-project/neo) (blockchain stuff itself) and [nvm](https://github.com/neo-project/neo-vm) (NeoVM version 3). Note that `nvm` is now fully dettached from `neo`, as an independent project.


`neo` sub-project includes four interdependent modules:

* mempool: p2p protocol and networking
* smart: ApplicationEngine and SmartContract
* ledger: blockchain persistance
* consensus: dBFT consensus


#### neo2
The `neo2` project comprises two folders, related to Neo Blockchain version 2: `cli2` (command-line interface) and `neo2` (blockchain stuff itself). 
`neo2` subproject includes six interdependent modules:

* core: main stuff
* nvm: [neo-vm](https://github.com/neo-project/neo-vm/tree/master-2.x) 2.x implementation (depends on `core` only)
* smart: ApplicationEngine and SmartContract
* mempool: p2p protocol and networking
* ledger: blockchain persistance
* consensus: dBFT consensus


### How to build

#### Dependencies

First, install `openssl` and `gtest` dependencies. But don't be afraid, it is provided as a git submodule. Just type `make vendor` and be happy :)

#### On Linux

After that, type `make` (`make cli`) to build `neopt-cli` and put the binary on `bin` folder (tests will run automatically).

To run tests only, type `make test` to invoke all tests from `tests` folder.

#### On Windows (and others)
TODO

### Tests

Tests are very important! Just go to `tests` directory and type `make tests`.

* it is also important to install `lcov` (usually `apt install lcov`), so that you can also run `make coverage` and generate html coverage reports on `reports/` folder.

### Versioning

Project will follow semantic versioning ([semver](semver.org)).

**Important:** the first part of version numbers is proposed to be set according to the first two digits of [NEO reference](github.com/neo-project) implementation (currently on C#).
For example, version `ref2.9-v0.2.1` should be interpreted as `neopt 0.2.1 (semver) for Neo reference 2.9.x`.
Version `0.x` will be kept until a complete implementation of the specification is not ready (seen as `alpha`).
If another specification exists (example Neo 3.0), another branch will exist for this project, regarding the implementation of that specification.

### Project roadmap

The object is to build:
1. **core**
2. **vm** (and `vm-application` interop layer)
3. **ledger** (persistance, even if on volatile memory)
4. **mempool**
5. **consensus**

### How to accomplish that?
Ok, it's a lot of stuff to build, so we need to focus on:
1. Implement complete specification in a portable manner
2. Code optimization

So, it doesn't matter if it's not being built in the most efficient way,
as long as this job is done **as quickly as possible**, in a **portable** and **testable** manner.
If not fully efficient, at least it should be perfectly safe for use.

### License

MIT License (for now, perhaps migrate to Apache 2.0?)

NeoResearch Community (2019)

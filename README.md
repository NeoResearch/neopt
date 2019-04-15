# neopt
## Portable Neo for all things

This project intends to provide easy access to [Neo blockchain](github.com/neo-project) for all things.


### Why chosing C/C++ language for that?
Existing frameworks use high-level languages that may not be suitable for very lightweight architectures,
such as microcontrollers with very limited computing capabilities.

C/C++ is interoperable with nearly all existing languages, so the idea is to provide modules that can be
reused on other projects (on other languages too).

### Which are the main modules?

The project proposal is divided into modules:

* core: main module (should be fully independent from others)
* vm: neo vm implementation (should depend on **core** only)
* mempool: p2p protocol and networking
* ledger: blockchain persistance
* consensus: dBFT consensus

### Versioning

Project will follow semantic versioning ([semver](semver.org)).

**Important:** the first part of version numbers is proposed to be set according to the first two digits of [Neo reference](github.com/neo-project) implementation (currently on C#).
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

### License

MIT License (for now, perhaps migrate to Apache 2.0?)

NeoResearch Community (2019)

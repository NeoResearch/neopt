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

### Which are the main modules?

The project proposal is divided into modules:

* core: main module (should be fully independent from others)
* vm: [neo-vm](https://github.com/neo-project/neo-vm) implementation (should depend on **core** only)
* mempool: p2p protocol and networking
* ledger: blockchain persistance
* consensus: dBFT consensus

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

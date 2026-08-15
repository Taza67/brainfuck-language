<a id="readme-top"></a>

[![Contributors][contributors-shield]][contributors-url]
[![Issues][issues-shield]][issues-url]
[![License][license-shield]][license-url]
[![C][c-shield]][c-url]

<div align="center">

<h3 align="center">brainfuck-language</h3>

  <p align="center">
    Interpreter-compiler for the Brainfuck language, written in C. Lexical and syntactic analysis with Lex and Yacc, then interpretation, compilation to bytecode / Python / C, or execution of bytecode in a virtual machine.
    <br />
    <br />
    <a href="https://github.com/Taza67/brainfuck-language/issues/new?labels=bug">Report Bug</a>
    &middot;
    <a href="https://github.com/Taza67/brainfuck-language/issues/new?labels=enhancement">Request Feature</a>
  </p>
</div>

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

## About The Project

`brainfuck-language` is an interpreter-compiler for the **Brainfuck** language. The `brainfuck` program parses a source program or a bytecode file — using a lexical analyzer (`flex`) and a grammar (`bison`) — and builds an abstract syntax tree before:

* interpreting the source program,
* compiling it to **bytecode**, **Python** or **C**,
* executing **bytecode** in a virtual machine,
* decompiling **bytecode** back to Brainfuck.

### Built With

* [C](https://fr.wikipedia.org/wiki/C_(langage)) C11
* [Make](https://fr.wikipedia.org/wiki/Make)
* [Flex](https://fr.wikipedia.org/wiki/Flex_(analyseur_lexical))
* [Bison](https://fr.wikipedia.org/wiki/GNU_bison)

<p align="right"><a href="#readme-top" title="Back to top">↑</a></p>

## Getting Started

### Prerequisites

* `gcc`
* `make`
* `flex`
* `bison`

### Installation

```bash
git clone https://github.com/Taza67/brainfuck-language.git
cd brainfuck-language
make build
```

<p align="right"><a href="#readme-top" title="Back to top">↑</a></p>

## Usage

Display the help notice:

```sh
./brainfuck -h
```

Interpret a Brainfuck source program:

```sh
./brainfuck -i program.bf
```

Execute a bytecode file:

```sh
./brainfuck -ib program.bytecode
```

Compile a source program to bytecode, Python or C:

```sh
./brainfuck -c program.bf output bytecode
./brainfuck -c program.bf output python
./brainfuck -c program.bf output c
```

Compile a bytecode file to Python or C:

```sh
./brainfuck -cb program.bytecode output python
./brainfuck -cb program.bytecode output c
```

Decompile a bytecode file back to Brainfuck:

```sh
./brainfuck -d program.bytecode output
```

<p align="right"><a href="#readme-top" title="Back to top">↑</a></p>

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md). Please read [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) before participating.

<p align="right"><a href="#readme-top" title="Back to top">↑</a></p>

## License

Distributed under the MIT License. See [LICENSE](LICENSE) for more information.

<p align="right"><a href="#readme-top" title="Back to top">↑</a></p>

## Contact

Taza67 - [tazaakil67@gmail.com](mailto:tazaakil67@gmail.com)

Project link : [https://github.com/Taza67/brainfuck-language](https://github.com/Taza67/brainfuck-language)

<p align="right"><a href="#readme-top" title="Back to top">↑</a></p>

<!-- MARKDOWN LINKS & IMAGES -->
[contributors-shield]: https://img.shields.io/github/contributors/Taza67/brainfuck-language.svg
[contributors-url]: https://github.com/Taza67/brainfuck-language/graphs/contributors
[issues-shield]: https://img.shields.io/github/issues/Taza67/brainfuck-language.svg
[issues-url]: https://github.com/Taza67/brainfuck-language/issues
[license-shield]: https://img.shields.io/badge/License-MIT-blue.svg
[license-url]: https://github.com/Taza67/brainfuck-language/blob/main/LICENSE
[c-shield]: https://img.shields.io/badge/C11-00599C.svg?logo=c&logoColor=white
[c-url]: https://fr.wikipedia.org/wiki/C_(langage)

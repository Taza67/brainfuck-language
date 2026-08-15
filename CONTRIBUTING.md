# Contributing

Thank you for your interest in **brainfuck-language**. The project is an interpreter-compiler in C for the Brainfuck language, built with `make`, `flex` and `bison` (C11 standard).

## Before you start

- Search the [existing issues](https://github.com/Taza67/brainfuck-language/issues) to avoid duplicating work.
- For large or structural changes, open an issue first.

## Development environment

### Prerequisites

- `gcc` (see `Makefile`: options `-std=c11 -Wall -Wextra -g -pedantic -O3`)
- `make`
- `flex`
- `bison`

### Clone and build

```bash
git clone https://github.com/Taza67/brainfuck-language.git
cd brainfuck-language
make build
```

## Pull requests

1. Fork the repository and create a branch from `main`.
2. Make focused changes; keep the PRs easy to review.
3. Make sure `make build` compiles without error or warning.
4. Open a pull request with a clear description and link the related issues.

## Commit messages

Follow [Conventional Commits](https://www.conventionalcommits.org/).

- **Types:** `feat`, `fix`, `refactor`, `docs`, `test`, `chore`
- **Description:** imperative, lowercase, no trailing period
- **Body:** optional; blank line after the description, then `-` bullets — lowercase except proper nouns, imperative, no trailing period

## Code organization

| File | Role |
|------|------|
| `src/main.c` | Entry point, dispatch of the execution modes |
| `src/parser.c` | Execution of a lexer/parser on an input file |
| `src/compiler.c` | Compilation to bytecode, Python and C |
| `src/decompiler.c` | Decompilation of bytecode to Brainfuck |
| `src/vm.c` | Execution of a program in the virtual machine |
| `src/ast.c` | Abstract syntax tree |
| `src/tstack.c` | Generic array-based stack |
| `src/utilities.c` | Output and usage helper functions |
| `src/merror.c` | Error and warning messages |
| `par/ysrc/parser_ast.y` | Bison grammar of the bytecode format |
| `par/ysrc/parser_code.y` | Bison grammar of the source language |
| `par/lsrc/parser_ast.l` | Flex lexer of the bytecode format |
| `par/lsrc/parser_code.l` | Flex lexer of the source language |

## Code of conduct

This project follows the [Contributor Covenant](CODE_OF_CONDUCT.md). By participating, you agree to abide by it.

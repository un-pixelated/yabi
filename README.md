# yabi — yet another brainfuck interpreter

A fast, lightweight brainfuck interpreter written in C.

## Requirements

- C compiler (GCC or Clang)
- CMake 3.10+

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

```bash
./yabi file.bf
```

## Interpreter Spec

| Property               | Value                       |
| ---------------------- | --------------------------- |
| Cell array length      | 30,000                      |
| Cell value range       | 0–127 (7-bit, wraps around) |
| Cell array             | Wraps around at both ends   |
| Max loop nesting depth | 1024                        |

## How it works

yabi uses a two-pass approach:

- **Pass 1** — Scans the file and builds a bracket map, precomputing the matching position of every `[` and `]` so jumps are O(1) during execution.
- **Pass 2** — Executes the program using the bracket map for loop handling.

## Brainfuck Resources

- [Fireship video](https://www.youtube.com/watch?v=hdHjjBS4cs8) — great introduction to the language and its history
- [Learn X in Y Minutes](https://learnxinyminutes.com/bf/) — quick written reference

## Supported Commands

| Command | Description                                          |
| ------- | ---------------------------------------------------- |
| `>`     | Move to next cell (wraps around)                     |
| `<`     | Move to previous cell (wraps around)                 |
| `+`     | Increment current cell (wraps around)                |
| `-`     | Decrement current cell (wraps around)                |
| `.`     | Output current cell as ASCII                         |
| `,`     | Accept one byte of input                             |
| `[`     | Jump past matching `]` if current cell is 0          |
| `]`     | Jump back to matching `[` if current cell is nonzero |

Any other character is treated as a comment and ignored.

## Some cool bits

**Variadic `free_memory()` using a sentinel NULL**

Instead of passing a count, `free_memory()` walks through its arguments and stops when it hits a `NULL` sentinel — similar to how `execl` works. This keeps callsites clean:

```c
free_memory(bracket_map, validation_stack, cell_array, NULL);
```

**`extension_checker()` pointer walking**

Rather than using `strlen` or indexing, `extension_checker()` walks the filename character by character using pointer arithmetic. Short circuit evaluation on null terminator checks keeps it memory safe without any bounds checking overhead.

**Two-pass O(1) bracket jumping**

Most brainfuck interpreters scan forward or backward through the file at runtime to find matching brackets. yabi does a first pass to precompute a `bracket_map` so every `[` and `]` jump is O(1) during execution — no scanning at all.

## Why I made this

I started working on this to see whether I could write safe and clean C code and just learn a lot in general. I get this might not be the most complex of projects but I still learnt a lot about writing clean and structured code and I believe I am now ready to re-write this in C++ and learn OOP.

## License

This project is licensed under the [MIT License](LICENSE).

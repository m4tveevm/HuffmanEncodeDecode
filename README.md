# Huffman Code Decode

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Dependencies](#dependencies)
- [Build](#build)
- [Usage](#usage)
- [Example](#example)
- [Help](#help)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Introduction

This repository contains an implementation of the Huffman coding algorithm for file compression and decompression, offering an efficient way to reduce file size.

## Features

- Compress files to a Huffman-coded binary format.
- Decompress Huffman-coded files to their original state.
- Pure C++ implementation without third-party dependencies.

## Dependencies

- CMake (minimum version 3.28)
- C++17 compliant compiler (GCC, Clang, MSVC)

## Build

To build the Huffman Code Decode project:

1. Clone the repository:
   ```bash
   git clone https://github.com/m4tveevm/HuffmanEncodeDecode.git
   ```
2. Navigate to the repository directory:
   ```bash
   cd HuffmanCodeDecode
   ```
3. Generate the build system using CMake:
   ```bash
   cmake -S . -B build
   ```
4. Build the project:
   ```bash
   cmake --build build --config Release
   ```

## Usage

After building the project, you can:

- **Compress** a file:
  ```bash
  ./build/HuffmanCodeDecode -z <input_file> <compressed_file>
  ```
- **Decompress** a file:
  ```bash
  ./build/HuffmanCodeDecode -u <compressed_file> <decompressed_file>
  ```


## Help

If you encounter any issues, check the [Issues](https://github.com/m4tveevm/HuffmanEncodeDecode/issues) tab of this repository.

## License

This project is licensed under the [MIT License](LICENSE) - see the LICENSE file for details.

## Acknowledgments

Credit goes to the various resources and documentation that helped in the development of this project:

- [Huffman Coding Wikipedia](https://en.wikipedia.org/wiki/Huffman_coding)
- [Алгоритм Хаффмана на пальцах](https://habr.com/ru/articles/144200/)
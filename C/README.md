# Turkish Syllable Library - README

This README file provides a step-by-step guide on how to use the **Turkish Syllable** library. This library is designed to syllabify Turkish texts and is developed using Python and C. The library connects to a `syllable` library written in C using Python's `ctypes`. This guide explains both the installation and usage.

## Table of Contents
1. [Installation](#installation)
2. [Usage](#usage)
3. [Example Usage](#example-usage)
4. [Detailed Explanations](#detailed-explanations)
5. [Troubleshooting](#troubleshooting)

## Installation

### Requirements

- **Python 3.x** (Python 3.6 or above)
- **GCC** (to compile C files)
- **ctypes** library (to use C code with Python)

### Steps

1. **Download Source Code**
   
   Download or copy the source code into your project folder. The project structure should look like this:
   
   ```
   Turkish Syllable/
   |-- include/
   |   |-- syllable.h
   |-- src/
   |   |-- syllable.c
   |-- wrapper/
   |   |-- csyllable_tr.py
   |-- example_usage.py
   |-- Makefile
   ```

2. **Compile the Library**
   
   To compile the `syllable` library written in C, run the following command in the terminal:
   
   ```sh
   make all
   ```
   This command will compile `syllable.c` and create a shared library named `libsyllable.so`.

3. **Set Up Python Files**
   
   The `wrapper/csyllable_tr.py` file acts as a bridge between Python and the C library. The Python files do not require any additional libraries and can be used directly.

## Usage

The `example_usage.py` script can be used to run the syllabification process.

### Running from Command Line

The `example_usage.py` script is set up to work with input and output files. You can run it with the following command:

```sh
python3 example_usage.py -i <input_file> -o <output_file>
```

#### Parameters:
- `-i`, `--input`: Specifies the path to the input file containing the text to be syllabified.
- `-o`, `--output`: Specifies the path to the output file where the syllabified text will be written.

### Example Commands

1. **Running with an Input File**
   
   Suppose you have a file named `input.txt` with the following content:
   
   ```
   ahmet okula gittiginde
   ```

   You can run the script like this to syllabify the text:
   
   ```sh
   python3 example_usage.py -i input.txt -o output.txt
   ```
   
   After running this command, the `output.txt` file will contain the following output:
   
   ```
   ah-met o-ku-la git-ti-gin-de
   ```

2. **Running with User Input**
   
   If you do not specify an input file, the script will prompt you to enter the text:
   
   ```sh
   python3 example_usage.py
   ```
   
   You will see the following in the terminal:
   
   ```
   Enter the text to syllabify: ahmet okula gittiginde
   ah-met o-ku-la git-ti-gin-de
   ```

## Detailed Explanations

### File Structure
- **include/syllable.h**: Header file containing function prototypes for syllabification. 
- **src/syllable.c**: C file containing the syllabification algorithm. This file includes the functions needed to syllabify Turkish words.
- **wrapper/csyllable_tr.py**: Acts as a bridge between Python and C, making the syllabification functions usable in Python.
- **example_usage.py**: Python script demonstrating how to use the syllabification library.
- **Makefile**: Used to compile the C code and create the shared library (`libsyllable.so`).

### Makefile Commands
- **all**: Creates the shared library named `libsyllable.so`.
  ```sh
  make all
  ```
- **clean**: Deletes the compiled files and the library.
  ```sh
  make clean
  ```
- **test**: Compiles `syllable_processor.c` and runs it for testing purposes.
  ```sh
  make test
  ```

## Troubleshooting

1. **Library Load Error**
   - If you encounter an error while running the Python script stating that `libsyllable.so` cannot be loaded, ensure that the library has been created and is in the correct directory.
   - Try adding the current directory to the `LD_LIBRARY_PATH` environment variable:
     ```sh
     export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
     ```

2. **Incomplete or Incorrect Syllabified Text**
   - If only the last word is syllabified, make sure to handle memory resetting properly in the C code. The updated versions are included in this file.

3. **Incompatibility Between Python and C**
   - When accessing C libraries using `ctypes`, ensure that the data types and memory management are handled correctly. Verify that `argtypes` and `restype` definitions are correct.

This README file provides a detailed explanation of how to install and use the **Turkish Syllable** library. For more information or to contribute, please refer to the project's source code.

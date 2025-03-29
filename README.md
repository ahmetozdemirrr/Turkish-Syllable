# Turkish Syllable Splitter

`turkish-syllable` is a library for syllabification of Turkish text, written in C and accessible using Python connectors. It works quickly and efficiently, produces results that follow Turkish spelling rules, and offers optional inclusion of punctuation.

## Features
- **Turkish Spelling**: Works according to the spelling rules specific to the Turkish language (for example, “merhaba” → `['mer', 'ha', 'ba']`).
- **Punctuation Support**: Optionally adds punctuation marks and spaces to the syllable list (`with_punctuation` parameter).
- **Fast Performance**: C-based algorithm provides fast results even for large texts.
- **Platform Compatibility**: Works on Linux based systems (**manylinux** compatible).

## Installation

You can install it via PyPI:

```bash
pip install turkish-syllable
```

## Sample Usage

### Using with Python:

```Python
from turkish_syllable import syllabify

# with punctuation
result = syllabify("Merhaba, dünya!") # default value of with_punctuation is True
print(result)
# output: ['Mer', 'ha', 'ba', ',', ' ', 'dü', 'nya', '!']

# without punctuation
result = syllabify("Merhaba, dünya!", with_punctuation=False)
print(result)
# output: ['Mer', 'ha', 'ba', 'dü', 'nya']
```

### Using with command line:

```bash
# with punctuation (default)
python -m turkish_syllable -i input.txt -o output.txt -p
# or enter the text directly:
python -m turkish_syllable -p
# sample input: "Merhaba, dünya!"
# output: Mer ha ba ,   dü nya !

# without punctuation
python -m turkish_syllable -i input.txt -o output.txt --no-punctuation
# or:
python -m turkish_syllable --no-punctuation
# sample input: "Merhaba, dünya!"
# output: Mer ha ba dü nya
```

## Technical Details

* **Language:** The algorithm is written in C and linked to Python with **ctypes**.
* **Spelling Algorithm:** It follows the natural distinctions between vowels and consonants according to Turkish spelling rules. It is optimized for special cases (for example, words with 3 or 4 letters).
* **Dependencies:** No extra Python dependencies are required, only standard libraries are used.
* **File Structure:**
	- **syllable.c**: C source code containing the spelling logic.
	- **libsyllable.so**: Compiled shared library.
	- **csyllable_en.py**: Python linker.

## Requirements
* **Python 3.6** or higher
* Linux operating system (with **manylinux** compatible build)

## License
Distributed under this project (MIT).

## Contribution
If you want to contribute:

1. Fork the repository: [github](https://github.com/ahmetozdemirrr/Turkish-Syllable) 
1. Make your changes and send **pull request**.

## Contact
For questions or suggestions: ahmetozdemiir.ao@gmail.com

## Version History
* **0.1.1**: Added `with_punctuation` parameter, shortened function name to `syllabify`.
* **0.1.0**: Initial release.
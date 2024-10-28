# Turkish Syllabifier

A Python library for syllabifying Turkish words. This tool helps break down Turkish words into their individual syllables, following Turkish phonological rules.

## Installation

You can install this library by cloning the repository:

```sh
git clone <repository_url>
```

## Usage

To use the Turkish syllabifier, import the `TurkishSyllabifier` class from `turkish_syllable.py` and create an instance of it:

```python
from turkish_syllable import TurkishSyllabifier

syllabifier = TurkishSyllabifier()
```

### Syllabify a Single Word

You can syllabify a single word by using the `syllabify` method:

```python
word = "saatim"
syllables = syllabifier.syllabify(word)
print(syllables)
```

Output:

```
['sa', 'a', 'tim']
```

### Syllabify a Sentence

You can also syllabify an entire sentence, keeping punctuation intact:

```python
sentence = "Merhaba dünya!"
syllabified_sentence = syllabifier.syllabify_text(sentence)
print(syllabified_sentence)
```

Output:

```
Mer ha ba dün ya !
```

## Example

See the `usage_example.py` file for a full example of how to use the Turkish Syllabifier library.

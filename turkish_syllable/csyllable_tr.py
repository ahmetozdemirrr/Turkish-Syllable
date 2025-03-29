import ctypes
import os


# Load the shared library (C code compiled to a shared object file)
lib_path = os.path.join(os.path.dirname(__file__), 'libsyllable.so')
lib = ctypes.CDLL(lib_path)


# Define the SyllableList struct
class SyllableList(ctypes.Structure):
    _fields_ = [
        ("syllables", ctypes.POINTER(ctypes.c_wchar_p)),
        ("count", ctypes.c_int),
        ("capacity", ctypes.c_int)
    ]


# Define the function prototypes
lib.init_syllable_list.argtypes = [ctypes.POINTER(SyllableList)]
lib.init_syllable_list.restype = None
lib.syllabify_text_with_punctuation.argtypes = [ctypes.c_wchar_p, ctypes.POINTER(SyllableList), ctypes.c_bool]
lib.syllabify_text_with_punctuation.restype = None
lib.free_syllable_list.argtypes = [ctypes.POINTER(SyllableList)]
lib.free_syllable_list.restype = None


def syllabify(content, with_punctuation=True):
    """
    Separates Turkish text into syllables, including punctuation.

    Args:
        content (str): Text to be syllabified.

    Returns:
        list: Syllable list
    """

    # Create an instance of SyllableList
    syllable_list = SyllableList()
    
    # Initialize the syllable list
    lib.init_syllable_list(ctypes.byref(syllable_list))
    # Call the syllabify function
    lib.syllabify_text_with_punctuation(content, ctypes.byref(syllable_list), with_punctuation)
    
    # Retrieve the syllables
    syllables = [ctypes.wstring_at(syllable_list.syllables[i]) for i in range(syllable_list.count)]
    
    # Free the syllable list
    lib.free_syllable_list(ctypes.byref(syllable_list))
    
    return syllables


def process_input_output(input_file=None, output_file=None, with_punctuation=True):
    if input_file:
        with open(input_file, 'r', encoding='utf-8') as infile:
            content = infile.read()
    else:
        content = input("Enter the text to syllabify: ")

    syllabified_text = syllabify(content, with_punctuation)
    output = ' '.join(syllabified_text)

    if output_file:
        with open(output_file, 'w', encoding='utf-8') as outfile:
            outfile.write(output)
    else:
        print(output)


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description="Syllabify Turkish text using csyllable_tr library.")
    parser.add_argument('-i', '--input', help="Input file containing text to syllabify.")
    parser.add_argument('-o', '--output', help="Output file to write the syllabified text.")
    parser.add_argument('-p', '--punctuation', action='store_true', default=True, help="Include punctuation and spaces (default: True).")
    parser.add_argument('--no-punctuation', action='store_false', dest='punctuation', help="Exclude punctuation and spaces.")
    args = parser.parse_args()

    process_input_output(input_file=args.input, output_file=args.output, with_punctuation=args.punctuation)

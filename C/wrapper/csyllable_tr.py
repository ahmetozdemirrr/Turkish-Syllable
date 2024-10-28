import ctypes
import os


# Load the shared library (C code compiled to a shared object file)
lib_path = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'libsyllable.so')
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
lib.syllabify_text_with_punctuation.argtypes = [ctypes.c_wchar_p, ctypes.POINTER(SyllableList)]
lib.syllabify_text_with_punctuation.restype = None
lib.free_syllable_list.argtypes = [ctypes.POINTER(SyllableList)]
lib.free_syllable_list.restype = None


def syllabify_text_with_punctuation(content):
    # Create an instance of SyllableList
    syllable_list = SyllableList()
    
    # Initialize the syllable list
    lib.init_syllable_list(ctypes.byref(syllable_list))
    # Call the syllabify function
    lib.syllabify_text_with_punctuation(content, ctypes.byref(syllable_list))
    
    # Retrieve the syllables
    syllables = []

    for i in range(syllable_list.count):
        syllable_ptr = syllable_list.syllables[i]
        syllable = ctypes.wstring_at(syllable_ptr)
        syllables.append(syllable)
    
    # Free the syllable list
    lib.free_syllable_list(ctypes.byref(syllable_list))
    
    return syllables


def process_input_output(input_file=None, output_file=None):
    if input_file:
        with open(input_file, 'r', encoding='utf-8') as infile:
            content = infile.read()
    else:
        content = input("Enter the text to syllabify: ")

    syllabified_text = syllabify_text_with_punctuation(content)
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
    args = parser.parse_args()

    process_input_output(input_file=args.input, output_file=args.output)

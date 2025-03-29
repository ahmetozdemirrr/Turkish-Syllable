# test_file.py
from turkish_syllable.csyllable_tr import process_input_output

input_file = "input.txt"
output_file = "output.txt"

process_input_output(input_file=input_file, output_file=output_file, with_punctuation=True)

with open(output_file, "r", encoding="utf-8") as f:
    print("With punctuation:")
    print(f.read())

process_input_output(input_file=input_file, output_file=output_file, with_punctuation=False)

with open(output_file, "r", encoding="utf-8") as f:
    print("\nWithout punctuation:")
    print(f.read())
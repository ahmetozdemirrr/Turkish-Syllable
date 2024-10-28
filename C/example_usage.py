# example_usage.py
import os
import sys


# Add wrapper directory to sys.path if needed
wrapper_dir = os.path.join(os.path.dirname(__file__), 'wrapper')
sys.path.append(wrapper_dir)

import csyllable_tr

# Example 1: Syllabify content from an input file and write to an output file
input_file = 'input.txt'
output_file = 'output.txt'

# Create an input file with some sample text
test_content = "Merhaba, bu bir heceleme testidir."
with open(input_file, 'w', encoding='utf-8') as f:
    f.write(test_content)

# Run the syllabify function from the csyllable_tr library
csyllable_tr.process_input_output(input_file=input_file, output_file=output_file)

# Print the content of the output file
with open(output_file, 'r', encoding='utf-8') as f:
    print("Syllabified output:")
    print(f.read())

# Example 2: Syllabify content from user input and print to console
print("\nNow syllabifying user-provided text.")
csyllable_tr.process_input_output()

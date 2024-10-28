# usage_example.py

from turkish_syllable import TurkishSyllabifier


if __name__ == "__main__":
    # Create an instance of the TurkishSyllabifier class
    syllabifier = TurkishSyllabifier()
    
    # Example words to syllabify
    words = ["ata", "saatim", "maaş", "elektrokardiyografi"]
    for word in words:
        syllables = syllabifier.syllabify(word)
        print(f"{word}: {syllables}")
    
    # Example sentence to syllabify
    sentence = "Merhaba dünya!"
    syllabified_sentence = syllabifier.syllabify_text(sentence)
    print(f"{sentence}: {syllabified_sentence}")

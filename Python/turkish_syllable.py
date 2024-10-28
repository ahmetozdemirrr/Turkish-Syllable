import re

VOWELS = "aeıioöuü"


def is_vowel(char):
    return char in VOWELS


def syllabify(word):
    syllables = []
    current_syllable = ""
    
    i = 0
    while i < len(word):
        char = word[i]
        current_syllable += char
        
        if is_vowel(char):  # sesli - ...
            if (i + 1) < len(word) and not is_vowel(word[i + 1]):  # sesli - sessiz - ...
                if (i + 2) < len(word) and not is_vowel(word[i + 2]):  # sessiz - sessiz - sessiz - ...  # sesli - sessiz - sessiz - ...
                    if (i + 3) < len(word) and not is_vowel(word[i + 3]):  # sesli - sessiz - sessiz - sessiz - ...
                        current_syllable += word[i + 1] + word[i + 2]
                        syllables.append(current_syllable)
                        current_syllable = ""
                        i += 3
                        continue
                    else:
                        if len(word) == 3:  # üç harfliyse (tek hecele)
                            syllables.append(word)
                            break
                        current_syllable += word[i + 1]
                        syllables.append(current_syllable)
                        current_syllable = ""
                        i += 2
                        continue
                else:
                    syllables.append(current_syllable)
                    current_syllable = ""
                    i += 1
                    continue
            else:
                syllables.append(current_syllable)
                current_syllable = ""
                i += 1
                continue
        else:
            if (i + 1) < len(word) and is_vowel(word[i + 1]):  # sessiz - sesli - ...
                if (i + 2) < len(word) and is_vowel(word[i + 2]):  # sessiz - sesli - sesli - ...
                    if len(word) == 4:  # dört harfliyse (özel durum)
                        current_syllable += word[i + 1]
                        syllables.append(current_syllable)
                        current_syllable = ""
                        current_syllable += word[i + 2]
                        if (i + 3) < len(word):
                            current_syllable += word[i + 3]
                        syllables.append(current_syllable)
                        current_syllable = ""
                        break
                else:
                    if (i + 3) < len(word) and is_vowel(word[i + 3]):  # sessiz - sesli - sessiz - sesli - ...
                        current_syllable += word[i + 1]
                        syllables.append(current_syllable)
                        current_syllable = ""
                        i += 2
                        continue
                    elif (i + 3) < len(word) and not is_vowel(word[i + 3]) and (i + 4) < len(word) and not is_vowel(word[i + 4]):  # sessiz - sesli - sessiz - sessiz - sessiz - ...
                        current_syllable += word[i + 1] + word[i + 2] + word[i + 3]
                        syllables.append(current_syllable)
                        current_syllable = ""
                        i += 4
                        continue
                    elif (i + 2) < len(word):  # sessiz - sesli - sessiz - ...
                        current_syllable += word[i + 1] + word[i + 2]
                        syllables.append(current_syllable)
                        current_syllable = ""
                        i += 3
                        continue
            else:
                if (i + 2) < len(word) and not is_vowel(word[i + 2]):
                    current_syllable += word[i + 1] + word[i + 2]
                    syllables.append(current_syllable)
                    current_syllable = ""
                    i += 3
                    continue
        i += 1

    if current_syllable and len(word) != 3:
        syllables.append(current_syllable)
    
    return syllables


def syllabify_text_with_punctuation(content):
    words = re.findall(r'\w+|[^\w\s]', content, re.UNICODE)
    syllabified_words = [' '.join(syllabify(word)) if word.isalpha() else word for word in words]
    
    return ' '.join(syllabified_words)



class TurkishSyllabifier:
    def __init__(self):
        self.vowels = VOWELS

    def syllabify(self, word):
        return syllabify(word)

    def syllabify_text(self, text):
        return syllabify_text_with_punctuation(text)


if __name__ == "__main__":

    syllabifier = TurkishSyllabifier()
    words = ["ata", "saatim", "saat", "maaş", 
            "maaşımız", "kaan", "deniz", "çocukluk", 
            "sallık", "sallantı", "altlık", "korkmak", 
            "kontrol", "uçurtma", "antropoloji", "ant", 
            "psikosomatik", "nöroplastisite", 
            "triskaidekafobi", "zor", "kartopu", 
            "elektrokardiyografi"]
    
    for word in words:
        print(f"{word}: {syllabifier.syllabify(word)}")

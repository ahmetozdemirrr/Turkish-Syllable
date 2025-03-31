/* syllable.h */

#ifndef SYLLABLE_H
#define SYLLABLE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h> /* platform dependency !! look when you use */
#include <stdlib.h>

#define MAX_SYLLABLE_LENGTH 10
#define INITIAL_SYLLABLE_CAPACITY 1000

typedef struct 
{
    wchar_t ** syllables;
    int count;
    int capacity;
} 
SyllableList;

bool is_vowel(wchar_t c);
void syllabify(const wchar_t * word, SyllableList * syllable_list);
void syllabify_text_with_punctuation(const wchar_t * content, SyllableList * syllable_list, bool with_punctuation);

void init_syllable_list(SyllableList * list);
void append_syllable(SyllableList * list, const wchar_t * syllable);
void free_syllable_list(SyllableList * list);

#endif /* SYLLABLE_H */

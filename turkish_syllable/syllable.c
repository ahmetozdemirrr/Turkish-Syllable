/* syllable.c */

#include <syllable.h>

bool is_vowel(wchar_t c) 
{
    const wchar_t vowels[] = L"aeıioöuüAEIİOÖUÜ";

    for (int i = 0; vowels[i] != L'\0'; i++) {
        if (c == vowels[i]) {
            return true;
        }
    }
    return false;
}

void syllabify(const wchar_t * word, SyllableList * syllable_list)
{
    wchar_t current_syllable[50] = L"";
    int len = wcslen(word);
    int i = 0;

    /* Special case: Consonant-Vowel-Consonant-Consonant (CVCVC) structure */
    if (len == 4 && !is_vowel(word[0]) && is_vowel(word[1]) && 
        !is_vowel(word[2]) && !is_vowel(word[3])) {
        append_syllable(syllable_list, word);
        return; /* Exit the function, because it is one syllable */
    }
    
    while (i < len)
    {
        wchar_t c = word[i];
        size_t curr_len = wcslen(current_syllable);

        /* Ensure we don't overflow current_syllable */
        if (curr_len + 1 >= sizeof(current_syllable) / sizeof(wchar_t)) {
            fprintf(stderr, "Error: Syllable too long.\n");
            exit(EXIT_FAILURE);
        }

        /* Append current character to current_syllable */
        current_syllable[curr_len] = c;
        current_syllable[curr_len + 1] = L'\0';

        if (is_vowel(c)) /* Vowel - ... */ {
            if ((i + 1) < len && !is_vowel(word[i + 1])) /* Vowel - Consonant - ... */ {
                if ((i + 2) < len && !is_vowel(word[i + 2])) /* Vowel - Consonant - Consonant - ... */ {
                    if (len == 3) /* If word has 3 letters, consider as one syllable */ {
                        append_syllable(syllable_list, word);
                        break;
                    }

                    if ((i + 3) < len && !is_vowel(word[i + 3])) /* Vowel - Consonant - Consonant - Consonant - ... */ {
                        /* Append word[i + 1] and word[i + 2] to current_syllable */
                        if (curr_len + 2 >= sizeof(current_syllable) / sizeof(wchar_t)) {
                            fprintf(stderr, "Error: Syllable too long.\n");
                            exit(EXIT_FAILURE);
                        }
                        current_syllable[curr_len + 1] = word[i + 1];
                        current_syllable[curr_len + 2] = word[i + 2];
                        current_syllable[curr_len + 3] = L'\0';

                        append_syllable(syllable_list, current_syllable);
                        current_syllable[0] = L'\0';
                        i += 3;
                        continue;
                    }

                    else {
                        /* Append word[i + 1] to current_syllable */
                        if (curr_len + 1 >= sizeof(current_syllable) / sizeof(wchar_t)) {
                            fprintf(stderr, "Error: Syllable too long.\n");
                            exit(EXIT_FAILURE);
                        }
                        current_syllable[curr_len + 1] = word[i + 1];
                        current_syllable[curr_len + 2] = L'\0';

                        append_syllable(syllable_list, current_syllable);
                        current_syllable[0] = L'\0';
                        i += 2;
                        continue;
                    }
                }

                else {
                    append_syllable(syllable_list, current_syllable);
                    current_syllable[0] = L'\0';
                    i += 1;
                    continue;
                }
            }

            else {
                append_syllable(syllable_list, current_syllable);
                current_syllable[0] = L'\0';
                i += 1;
                continue;
            }
        }

        else /* Consonant - ... */ {
            if ((i + 1) < len && is_vowel(word[i + 1])) /* Consonant - Vowel - ... */ {
                if ((i + 2) < len && is_vowel(word[i + 2])) /* Consonant - Vowel - Vowel - ... */ {
                    if (len == 4) /* If word has 4 letters (special case) */ {
                        /* Append word[i + 1] to current_syllable */
                        if (curr_len + 1 >= sizeof(current_syllable) / sizeof(wchar_t)) {
                            fprintf(stderr, "Error: Syllable too long.\n");
                            exit(EXIT_FAILURE);
                        }
                        current_syllable[curr_len + 1] = word[i + 1];
                        current_syllable[curr_len + 2] = L'\0';

                        append_syllable(syllable_list, current_syllable);
                        current_syllable[0] = L'\0';

                        /* Start a new syllable with word[i + 2] */
                        current_syllable[0] = word[i + 2];
                        current_syllable[1] = L'\0';

                        if ((i + 3) < len) {
                            if (wcslen(current_syllable) + 1 >= sizeof(current_syllable) / sizeof(wchar_t)) {
                                fprintf(stderr, "Error: Syllable too long.\n");
                                exit(EXIT_FAILURE);
                            }
                            current_syllable[1] = word[i + 3];
                            current_syllable[2] = L'\0';
                        }

                        append_syllable(syllable_list, current_syllable);
                        current_syllable[0] = L'\0';
                        break;
                    }
                }

                else {
                    if ((i + 3) < len && is_vowel(word[i + 3])) /* Consonant - Vowel - Consonant - Vowel - ... */ {
                        /* Append word[i + 1] to current_syllable */
                        if (curr_len + 1 >= sizeof(current_syllable) / sizeof(wchar_t)) {
                            fprintf(stderr, "Error: Syllable too long.\n");
                            exit(EXIT_FAILURE);
                        }
                        current_syllable[curr_len + 1] = word[i + 1];
                        current_syllable[curr_len + 2] = L'\0';

                        append_syllable(syllable_list, current_syllable);
                        current_syllable[0] = L'\0';
                        i += 2;
                        continue;
                    }

                    else if ((i + 3) < len && !is_vowel(word[i + 3]) && (i + 4) < len && !is_vowel(word[i + 4])) /* Consonant - Vowel - Consonant - Consonant - Consonant - ... */ {
                        /* Append word[i + 1], word[i + 2], word[i + 3] to current_syllable */
                        if (curr_len + 3 >= sizeof(current_syllable) / sizeof(wchar_t)) {
                            fprintf(stderr, "Error: Syllable too long.\n");
                            exit(EXIT_FAILURE);
                        }
                        current_syllable[curr_len + 1] = word[i + 1];
                        current_syllable[curr_len + 2] = word[i + 2];
                        current_syllable[curr_len + 3] = word[i + 3];
                        current_syllable[curr_len + 4] = L'\0';

                        append_syllable(syllable_list, current_syllable);
                        current_syllable[0] = L'\0';
                        i += 4;
                        continue;
                    }

                    else if ((i + 2) < len) /* Consonant - Vowel - Consonant - ... */ {
                        /* Append word[i + 1], word[i + 2] to current_syllable */
                        if (curr_len + 2 >= sizeof(current_syllable) / sizeof(wchar_t)) {
                            fprintf(stderr, "Error: Syllable too long.\n");
                            exit(EXIT_FAILURE);
                        }
                        current_syllable[curr_len + 1] = word[i + 1];
                        current_syllable[curr_len + 2] = word[i + 2];
                        current_syllable[curr_len + 3] = L'\0';

                        append_syllable(syllable_list, current_syllable);
                        current_syllable[0] = L'\0';
                        i += 3;
                        continue;
                    }
                }
            }

            else {
                if ((i + 2) < len && !is_vowel(word[i + 2])) /* Consonant - Consonant - Consonant - ... */ {
                    /* Append word[i + 1], word[i + 2] to current_syllable */
                    if (curr_len + 2 >= sizeof(current_syllable) / sizeof(wchar_t)) {
                        fprintf(stderr, "Error: Syllable too long.\n");
                        exit(EXIT_FAILURE);
                    }
                    current_syllable[curr_len + 1] = word[i + 1];
                    current_syllable[curr_len + 2] = word[i + 2];
                    current_syllable[curr_len + 3] = L'\0';

                    append_syllable(syllable_list, current_syllable);
                    current_syllable[0] = L'\0';
                    i += 3;
                    continue;
                }
            }
        }
        i++;
    }

    if (current_syllable[0] != L'\0' && len != 3) {
        append_syllable(syllable_list, current_syllable);
    }
}

void syllabify_text_with_punctuation(const wchar_t * content, SyllableList * syllable_list, bool with_punctuation) 
{
    #ifdef _WIN32
        /* 
            Windows-specific code (future parallel processing)
            for ex.: parallel processing with CreateThread
        */
    #elif defined(__APPLE__)
        /*
            macOS-specific code (future parallel processing)
            for ex.: parallel processing with Grand Central Dispatch (GCD)
        */
    #else
        /*
            Linux/Unix-specific code (future parallel processing)
            for ex.: parallel procesing with POSIX threads (pthread)
        */
    #endif

    wchar_t word[100] = L"";
    size_t word_index = 0;
    bool is_number = true;
    int len = wcslen(content);

    for (int i = 0; i <= len; i++) {
        if (iswalpha(content[i])) {
            if (word_index + 1 >= sizeof(word) / sizeof(wchar_t)) {
                fprintf(stderr, "Error: Word too long.\n");
                exit(EXIT_FAILURE);
            }
            word[word_index++] = content[i];
            word[word_index] = L'\0';
            is_number = false;
        } 

        else if (iswdigit(content[i])) {
            if (word_index + 1 >= sizeof(word) / sizeof(wchar_t)) {
                fprintf(stderr, "Error: Word too long.\n");
                exit(EXIT_FAILURE);
            }
            word[word_index++] = content[i];
            word[word_index] = L'\0';
        }

        else {
            if (word_index > 0) {
                word[word_index] = L'\0';
                
                if (is_number) {
                    append_syllable(syllable_list, word);
                } 

                else {
                    syllabify(word, syllable_list);
                }
                word_index = 0;
                is_number = true;
            }

            if (with_punctuation && (iswpunct(content[i]) || iswspace(content[i]))) {
                wchar_t punctuation[2] = {content[i], L'\0'};
                append_syllable(syllable_list, punctuation);
            }
        }
    }

    if (word_index > 0) {
        word[word_index] = L'\0';
        if (is_number) {
            append_syllable(syllable_list, word);
        } 

        else {
            syllabify(word, syllable_list);
        }
    }
}

void init_syllable_list(SyllableList * list) 
{
    list->syllables = (wchar_t **)malloc(INITIAL_SYLLABLE_CAPACITY * sizeof(wchar_t *));

    if (!list->syllables) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    list->count = 0;
    list->capacity = INITIAL_SYLLABLE_CAPACITY;
}

void append_syllable(SyllableList * list, const wchar_t * syllable) 
{
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity * 2;
        wchar_t ** new_syllables = (wchar_t **)realloc(list->syllables, new_capacity * sizeof(wchar_t *));

        if (!new_syllables) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        list->syllables = new_syllables;
        list->capacity = new_capacity;
    }
    size_t len = wcslen(syllable) + 1;  /* +1 for the null terminator */
    wchar_t *syllable_copy = (wchar_t *)malloc(len * sizeof(wchar_t));

    if (!syllable_copy) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    wcscpy(syllable_copy, syllable);
    list->syllables[list->count++] = syllable_copy;
}

void free_syllable_list(SyllableList * list) 
{
    for (int i = 0; i < list->count; i++) {
        free(list->syllables[i]);
    }
    free(list->syllables);
    list->syllables = NULL;
    list->count = 0;
    list->capacity = 0;
}

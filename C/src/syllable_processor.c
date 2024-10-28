/* syllable_processor.c */

#include "syllable.h"

#define STANDALONE

int main(void) 
{
    setlocale(LC_ALL, "");

#ifdef STANDALONE 
    const wchar_t * text = L"arp arpa sarp ata saatim saat maas maasimiz kaan deniz cocukluk sallik sallanti altlik korkmak kontrol ucurtma antropoloji,ahmet ant psikosomatik noroplastisite triskaidekafobi zor kartopu elektrokardiyografi";

    /* Initialize the SyllableList */
    SyllableList syllable_list;
    init_syllable_list(&syllable_list);

    syllabify_text_with_punctuation(text, &syllable_list);

    wprintf(L"Text: %ls\n", text);
    wprintf(L"Syllabified:\n");
    for (int i = 0; i < syllable_list.count; i++) 
    {
        wprintf(L"%ls ", syllable_list.syllables[i]);
    }
    wprintf(L"\n");

    /* Free the allocated memory */
    free_syllable_list(&syllable_list);
#endif

    return 0;
}

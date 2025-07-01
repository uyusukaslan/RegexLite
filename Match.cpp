/*

    Poyraz Erdoðan, Created in 01.07.2025

*/

#include "Match.h"

bool Match::match(string pattern, const string text)
{
    int textIndex = 0;
    int patternIndex = 0;

    while (patternIndex < pattern.size())
    {

        if (patternIndex + 1 < pattern.size() && pattern[patternIndex + 1] == '*')
        {
            char current = pattern[patternIndex];

            int start = textIndex;

            // match with greedy
            while (textIndex < text.size() && (current == text[textIndex] || current == '.'))
            {
                textIndex++;
            }

            // backtrack
            for (int i = textIndex; i >= start; i--)
            {
                if (match(pattern.substr(patternIndex + 2), text.substr(i)))
                {
                    return true;
                }
                // unsigned wraparound
                if (i == 0) break;
            }
            return false;
        }

        // . or a
        if (textIndex < text.size() && (pattern[patternIndex] == text[textIndex] || pattern[patternIndex] == '.')) {
            patternIndex++;
            textIndex++;
        }
        else {
            return false;
        }

    }


    return text.size() == textIndex;
}

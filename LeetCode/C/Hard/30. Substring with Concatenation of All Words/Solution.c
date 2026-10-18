static uint64_t hashString(const char *s, int len) {
    uint64_t hash = 14695981039346656037ULL;

    for (int i = 0; i < len; i++) {
        hash ^= (unsigned char)s[i];
        hash *= 1099511628211ULL;
    }

    return hash;
}

static int findWord(
    const char *s,
    int len,
    char **words,
    int *table,
    int capacity,
    int wordLen
) {
    int slot = (int)(hashString(s, len) & (capacity - 1));

    while (table[slot] != -1) {
        if (strncmp(s, words[table[slot]], wordLen) == 0) {
            return slot;
        }

        slot = (slot + 1) & (capacity - 1);
    }

    return -1;
}

int* findSubstring(
    char* s,
    char** words,
    int wordsSize,
    int* returnSize
) {
    *returnSize = 0;

    int sLen = strlen(s);
    int wordLen = strlen(words[0]);
    int totalLen = wordLen * wordsSize;

    int* result = malloc(sizeof(int) * (sLen + 1));

    if (sLen < totalLen) {
        return result;
    }

    // Hash table capacity: power of 2
    int capacity = 1;

    while (capacity < wordsSize * 2) {
        capacity *= 2;
    }

    int* table = malloc(sizeof(int) * capacity);
    int* required = calloc(capacity, sizeof(int));
    int* seen = calloc(capacity, sizeof(int));

    for (int i = 0; i < capacity; i++) {
        table[i] = -1;
    }

    // Build the word-frequency table
    for (int i = 0; i < wordsSize; i++) {
        int slot = (int)(
            hashString(words[i], wordLen) & (capacity - 1)
        );

        while (table[slot] != -1 &&
               strncmp(words[i], words[table[slot]], wordLen) != 0) {
            slot = (slot + 1) & (capacity - 1);
        }

        if (table[slot] == -1) {
            table[slot] = i;
        }

        required[slot]++;
    }

    // Try each possible alignment of word-sized chunks
    for (int offset = 0; offset < wordLen; offset++) {
        memset(seen, 0, sizeof(int) * capacity);

        int left = offset;
        int count = 0;

        for (int right = offset;
             right + wordLen <= sLen;
             right += wordLen) {

            int slot = findWord(
                s + right, wordLen, words,
                table, capacity, wordLen
            );

            // Unknown word: reset the current window
            if (slot == -1) {
                memset(seen, 0, sizeof(int) * capacity);
                count = 0;
                left = right + wordLen;
                continue;
            }

            seen[slot]++;
            count++;

            // Too many copies of this word
            while (seen[slot] > required[slot]) {
                int leftSlot = findWord(
                    s + left, wordLen, words,
                    table, capacity, wordLen
                );

                seen[leftSlot]--;
                count--;
                left += wordLen;
            }

            // Found all required words
            if (count == wordsSize) {
                result[(*returnSize)++] = left;

                // Move left to search for overlapping matches
                int leftSlot = findWord(
                    s + left, wordLen, words,
                    table, capacity, wordLen
                );

                seen[leftSlot]--;
                count--;
                left += wordLen;
            }
        }
    }

    free(table);
    free(required);
    free(seen);

    return result;
}

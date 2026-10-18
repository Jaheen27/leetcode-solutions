int strStr(char* haystack, char* needle) {
    int h = strlen(haystack);
    int n = strlen(needle);

    for (int i = 0; i <= h - n; i++) {
        int j = 0;

        while (j < n && haystack[i + j] == needle[j]) {
            j++;
        }

        if (j == n) {
            return i;
        }
    }

    return -1;
}

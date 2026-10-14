/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
void backtrack(char **result, char *current,
               int pos, int open, int close,
               int n, int *count) {
    if (pos == 2 * n) {
        current[pos] = '\0';

        result[*count] = malloc(2 * n + 1);
        strcpy(result[*count], current);
        (*count)++;
        return;
    }

    if (open < n) {
        current[pos] = '(';
        backtrack(result, current, pos + 1,
                  open + 1, close, n, count);
    }

    if (close < open) {
        current[pos] = ')';
        backtrack(result, current, pos + 1,
                  open, close + 1, n, count);
    }
}

char** generateParenthesis(int n, int* returnSize) {
    int capacity = 5000;
    char **result = malloc(capacity * sizeof(char *));
    char current[20];

    *returnSize = 0;

    backtrack(result, current, 0, 0, 0, n, returnSize);

    return result;
}
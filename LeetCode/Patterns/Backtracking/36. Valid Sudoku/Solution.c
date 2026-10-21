bool isValidSudoku(char** board, int boardSize,
                   int* boardColSize) {

    bool row[9][10] = {false};
    bool col[9][10] = {false};
    bool box[9][10] = {false};

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {

            if (board[i][j] == '.') {
                continue;
            }

            int digit = board[i][j] - '0';
            int boxIndex = (i / 3) * 3 + (j / 3);

            if (row[i][digit] ||
                col[j][digit] ||
                box[boxIndex][digit]) {
                return false;
            }

            row[i][digit] = true;
            col[j][digit] = true;
            box[boxIndex][digit] = true;
        }
    }

    return true;
}
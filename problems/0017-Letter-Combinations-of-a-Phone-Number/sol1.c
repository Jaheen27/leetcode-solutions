// ==========================================================
// 17. Letter Combinations of a Phone Number
// Difficulty : Medium
// Language   : C
// Solution   : #1
// Runtime    : 0 ms (Beats 100%)
// Memory     : 9.2 MB (Beats 13%)
// Link       : https://leetcode.com/problems/letter-combinations-of-a-phone-number/
// ==========================================================

char** letterCombinations(char* digits, int* returnSize) { 
    *returnSize = 0; 
    // Maximum combinations = 4^4 = 256 
    char** result = malloc(256 * sizeof(char*)); 
    char current[5]; 
    backtrack(digits, 0, current, result, returnSize); 
    return result; 
}
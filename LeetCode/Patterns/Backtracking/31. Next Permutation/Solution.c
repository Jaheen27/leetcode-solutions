void nextPermutation(int* nums, int numsSize) {
    int i, j, temp;

    // Step 1: Find the pivot from the right
    i = numsSize - 2;

    while (i >= 0 && nums[i] >= nums[i + 1]) {
        i--;
    }

    // Step 2: Find the next greater element and swap
    if (i >= 0) {
        j = numsSize - 1;

        while (nums[j] <= nums[i]) {
            j--;
        }

        temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    // Step 3: Reverse the suffix
    int left = i + 1;
    int right = numsSize - 1;

    while (left < right) {
        temp = nums[left];
        nums[left] = nums[right];
        nums[right] = temp;

        left++;
        right--;
    }
}

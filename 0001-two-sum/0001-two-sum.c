/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int* ans = malloc(2 * sizeof(int));
    *returnSize = 2;

    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] == target - nums[i]) {
                ans[0] = j;
                ans[1] = i;
                return ans;
            }
        }
    }

    return ans;
}
double findMedianSortedArrays(int* nums1, int nums1Size,
                              int* nums2, int nums2Size) {
    // Always binary search the smaller array
    if (nums1Size > nums2Size)
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);

    int m = nums1Size;
    int n = nums2Size;

    int low = 0, high = m;

    while (low <= high) {
        int cut1 = (low + high) / 2;
        int cut2 = (m + n + 1) / 2 - cut1;

        int left1  = (cut1 == 0) ? -1000000000 : nums1[cut1 - 1];
        int right1 = (cut1 == m) ?  1000000000 : nums1[cut1];

        int left2  = (cut2 == 0) ? -1000000000 : nums2[cut2 - 1];
        int right2 = (cut2 == n) ?  1000000000 : nums2[cut2];

        if (left1 <= right2 && left2 <= right1) {

            // Odd total length
            if ((m + n) % 2 == 1)
                return (double)(left1 > left2 ? left1 : left2);

            // Even total length
            int maxLeft = left1 > left2 ? left1 : left2;
            int minRight = right1 < right2 ? right1 : right2;

            return ((double)maxLeft + minRight) / 2.0;
        }

        if (left1 > right2)
            high = cut1 - 1;
        else
            low = cut1 + 1;
    }

    return 0.0;
}
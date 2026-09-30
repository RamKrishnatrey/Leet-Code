int lengthOfLongestSubstring(char* s) {
    int last[128] = {0};
    int left = 0;
    int maxLen = 0;

    for (int right = 0; s[right] != '\0'; right++) {
        unsigned char c = s[right];

        if (last[c] > left)
            left = last[c];

        last[c] = right + 1;

        int len = right - left + 1;

        if (len > maxLen)
            maxLen = len;
    }

    return maxLen;
}
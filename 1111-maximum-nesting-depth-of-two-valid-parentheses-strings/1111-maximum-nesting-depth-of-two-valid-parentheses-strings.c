int* maxDepthAfterSplit(char* seq, int* returnSize) {
    int n = strlen(seq);

    int* answer = malloc(n * sizeof(int));
    *returnSize = n;

    int depth = 0;

    for (int i = 0; i < n; i++) {
        if (seq[i] == '(') {
            depth++;
            answer[i] = depth % 2;
        } else {
            answer[i] = depth % 2;
            depth--;
        }
    }

    return answer;
}
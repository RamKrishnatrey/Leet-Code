#include <stdlib.h>
#include <stdbool.h>

bool hasValidPath(char** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];

    int len = m + n - 1;

    // Valid parentheses string must have even length
    if (len % 2 != 0)
        return false;

    // First and last character must be '(' and ')'
    if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(')
        return false;

    /*
        dp[i][j][balance]

        true = we can reach (i,j) with this balance.
    */
    int total = m * n * (len + 1);

    char *dp = calloc(total, sizeof(char));

    if (dp == NULL)
        return false;

    #define IDX(i, j, b) \
        (((i) * n + (j)) * (len + 1) + (b))

    // Starting cell '(' gives balance 1
    dp[IDX(0, 0, 1)] = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {

            if (i == 0 && j == 0)
                continue;

            int change = (grid[i][j] == '(') ? 1 : -1;

            for (int balance = 0; balance <= len; balance++) {

                int previousBalance = balance - change;

                if (previousBalance < 0 ||
                    previousBalance > len)
                    continue;

                // Come from above
                if (i > 0 &&
                    dp[IDX(i - 1, j, previousBalance)]) {

                    dp[IDX(i, j, balance)] = 1;
                }

                // Come from left
                if (j > 0 &&
                    dp[IDX(i, j - 1, previousBalance)]) {

                    dp[IDX(i, j, balance)] = 1;
                }
            }
        }
    }

    bool answer = dp[IDX(m - 1, n - 1, 0)];

    free(dp);

    return answer;
}
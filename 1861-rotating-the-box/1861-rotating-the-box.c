/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char** rotateTheBox(char** boxGrid, int boxGridSize,
                    int* boxGridColSize, int* returnSize,
                    int** returnColumnSizes) {

    int m = boxGridSize;
    int n = boxGridColSize[0];

    // Result is n x m
    char** result = malloc(n * sizeof(char*));

    *returnSize = n;
    *returnColumnSizes = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        result[i] = malloc(m * sizeof(char));
        (*returnColumnSizes)[i] = m;

        for (int j = 0; j < m; j++)
            result[i][j] = '.';
    }

    /*
        Process each row from right to left.
        'empty' represents the position where the next
        stone will fall.
    */
    for (int i = 0; i < m; i++) {

        int empty = n - 1;

        for (int j = n - 1; j >= 0; j--) {

            if (boxGrid[i][j] == '*') {
                // Obstacle stays in its rotated position
                int newRow = j;
                int newCol = m - 1 - i;

                result[newRow][newCol] = '*';

                // Stones can fall only up to this obstacle
                empty = j - 1;
            }

            else if (boxGrid[i][j] == '#') {
                // Stone falls to the lowest available position
                int newRow = empty;
                int newCol = m - 1 - i;

                result[newRow][newCol] = '#';

                empty--;
            }
        }
    }

    return result;
}
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int minMoves(char** classroom, int classroomSize, int energy) {
    int m = classroomSize;
    int n = strlen(classroom[0]);

    int sr = 0, sc = 0;
    int litterCount = 0;

    /* Find starting position and count litter */
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (classroom[i][j] == 'S') {
                sr = i;
                sc = j;
            }

            if (classroom[i][j] == 'L')
                litterCount++;
        }
    }

    if (litterCount == 0)
        return 0;

    /* Assign a bit to every litter */
    int id[20][20];

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            id[i][j] = -1;

    int k = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (classroom[i][j] == 'L')
                id[i][j] = k++;
        }
    }

    int masks = 1 << litterCount;

    /*
        State:
        position + energy + collected litter

        Total states:
        m * n * (energy + 1) * masks
    */
    int totalStates = m * n * (energy + 1) * masks;

    char *visited = calloc(totalStates, sizeof(char));

    /*
        Store each state in a single uint32_t
        instead of a large struct to save memory.
    */
    uint32_t *queue = malloc((size_t)totalStates * sizeof(uint32_t));

    if (visited == NULL || queue == NULL) {
        free(visited);
        free(queue);
        return -1;
    }

    /*
        Encoding:
        state = (((cell * (energy + 1)) + energyLeft) * masks) + mask
    */

    #define ENCODE(cell, e, mask) \
        ((((cell) * (energy + 1)) + (e)) * masks + (mask))

    int startCell = sr * n + sc;

    uint32_t startState = ENCODE(startCell, energy, 0);

    int front = 0;
    int rear = 0;

    queue[rear++] = startState;
    visited[startState] = 1;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    int distance = 0;

    while (front < rear) {

        int levelEnd = rear;

        while (front < levelEnd) {

            uint32_t state = queue[front++];

            /* Decode state */
            int mask = state % masks;
            state /= masks;

            int e = state % (energy + 1);
            int cell = state / (energy + 1);

            int r = cell / n;
            int c = cell % n;

            /* All litter collected */
            if (mask == masks - 1) {
                free(visited);
                free(queue);
                return distance;
            }

            /* Try four directions */
            for (int d = 0; d < 4; d++) {

                int nr = r + dr[d];
                int nc = c + dc[d];

                /* Outside grid */
                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;

                /* Obstacle */
                if (classroom[nr][nc] == 'X')
                    continue;

                /* No energy to make a move */
                if (e == 0)
                    continue;

                int newEnergy = e - 1;
                int newMask = mask;

                /* Collect litter */
                if (classroom[nr][nc] == 'L') {
                    int bit = id[nr][nc];
                    newMask |= (1 << bit);
                }

                /* Reset energy */
                if (classroom[nr][nc] == 'R') {
                    newEnergy = energy;
                }

                int newCell = nr * n + nc;

                uint32_t newState =
                    ENCODE(newCell, newEnergy, newMask);

                if (!visited[newState]) {
                    visited[newState] = 1;
                    queue[rear++] = newState;
                }
            }
        }

        distance++;
    }

    free(visited);
    free(queue);

    return -1;
}
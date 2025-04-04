#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define TABLE_SIZE (1 << 22)

int main() {
    uint64_t M, a, b, c;
    scanf("%" SCNu64 " %" SCNu64 " %" SCNu64 " %" SCNu64, &M, &a, &b, &c);

    uint64_t keys[TABLE_SIZE];
    int values[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) keys[i] = -1;

    uint64_t state = 1;
    for (int index = 0; ; index++) {
        uint64_t pos = state % TABLE_SIZE;
        while (keys[pos] != -1 && keys[pos] != state) pos = (pos + 1) % TABLE_SIZE;

        if (keys[pos] == state) {
            printf("%d %d", values[pos], index);
            break;
        }
        
        keys[pos] = state;
        values[pos] = index;
        state = (state * state * a + state * b + c) % M;
    }

    return 0;
}
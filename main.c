#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct matrix {
    int xsize;
    int ysize;
    int **values;
};

struct matrix *matrix_create(int xsize, int ysize, int mod) {
    struct matrix *new = malloc(sizeof *new);
    new->xsize = xsize;
    new->ysize = ysize;
    new->values = malloc(ysize * sizeof(int *));
    for(int y = 0; y < ysize; ++y) {
        new->values[y] = malloc(xsize * sizeof(int));
        for(int x = 0; x < xsize; ++x) {
            new->values[y][x] = rand() % mod;
        }
    }
    return new;
}

void matrix_free(struct matrix *this) {
    for(int y = 0; y < this->ysize; ++y) {
        free(this->values[y]);
    }
    free(this->values);
    free(this);
}

void matrix_print(struct matrix *this) {
    for(int y = 0; y < this->ysize; ++y) {
        printf("[ ");
        for(int x = 0; x < this->xsize; ++x) {
            printf("%2d ", this->values[y][x]);
        }
        printf("]\n");
    }
}

int main(void) {
    struct matrix *m = matrix_create(10, 10, 100);
    matrix_print(m);
    matrix_free(m);
}

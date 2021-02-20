#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct matrix {
    int xsize;
    int ysize;
    int **values;
};

struct matrix *matrix_create(int xsize, int ysize, int mod) {
    srand(time(NULL));
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

void _swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void _quicksort(int data[], int start, int end) {
    if(start >= end)
        return;
    int target = start;
    for(int i = start; i <= end; ++i) {
        if(data[i] < data[end]) {
            _swap(&data[i], &data[target++]);
        }
    }
    _swap(&data[target], &data[end]);
    _quicksort(data, start, target - 1);
    _quicksort(data, target + 1, end);
}

void matrix_sort(struct matrix *this) {
    for(int y = 0; y < this->ysize; ++y) {
        _quicksort(this->values[y], 0, this->xsize - 1);
    }
}

int main(void) {
    struct matrix *m = matrix_create(10, 10, 100);
    printf("Matrix:\n");
    matrix_print(m);
    matrix_sort(m);
    printf("Sorted Matrix:\n");
    matrix_print(m);
    matrix_free(m);
}

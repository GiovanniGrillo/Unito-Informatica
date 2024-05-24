#include <stdlib.h>
#include <string.h>

void merge(void *base, size_t size, int (*compar)(const void*, const void*), int start, int mid, int end) {
    int i, j, k;
    int n1 = mid - start + 1;
    int n2 = end - mid;
    void *L = malloc(n1 * size);
    void *R = malloc(n2 * size);
    memcpy(L, base + start * size, n1 * size);
    memcpy(R, base + (mid + 1) * size, n2 * size);
    i = 0;
    j = 0;
    k = start;
    while (i < n1 && j < n2) {
        if (compar(L + i * size, R + j * size) <= 0) {
            memcpy(base + k * size, L + i * size, size);
            i++;
        } else {
            memcpy(base + k * size, R + j * size, size);
            j++;
        }
        k++;
    }
    while (i < n1) {
        memcpy(base + k * size, L + i * size, size);
        i++;
        k++;
    }
    while (j < n2) {
        memcpy(base + k * size, R + j * size, size);
        j++;
        k++;
    }
    free(L);
    free(R);
}

void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) {
    if (nitems > 1) {
        int mid = nitems / 2;

        merge_sort(base, mid, size, compar);
        merge_sort(base + mid * size, nitems - mid, size, compar);
        merge(base, size, compar, 0, mid - 1, nitems - 1);
    }
}

void swap(void *a, void *b, size_t size) {
    void *temp = malloc(size);
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}

// Funzione per scegliere il pivot come mediano di tre
int median_of_three(void *base, size_t size, int (*compar)(const void*, const void*), int low, int high) {
    int mid = low + (high - low) / 2;

    if (compar(base + low * size, base + mid * size) > 0)
        swap(base + low * size, base + mid * size, size);

    if (compar(base + low * size, base + high * size) > 0)
        swap(base + low * size, base + high * size, size);

    if (compar(base + mid * size, base + high * size) > 0)
        swap(base + mid * size, base + high * size, size);

    return mid;
}

// Funzione di partizione modificata per utilizzare il mediano di tre come pivot
int partition(void *base, size_t size, int (*compar)(const void*, const void*), int low, int high) {
    int pivotIndex = median_of_three(base, size, compar, low, high);
    void *pivotValue = malloc(size);
    memcpy(pivotValue, base + pivotIndex * size, size);
    swap(base + pivotIndex * size, base + high * size, size);
    int storeIndex = low;

    for (int i = low; i < high; i++) {
        if (compar(base + i * size, pivotValue) < 0) {
            swap(base + i * size, base + storeIndex * size, size);
            storeIndex++;
        }
    }

    swap(base + storeIndex * size, base + high * size, size);
    free(pivotValue);
    return storeIndex;
}

// Funzione quick_sort modificata per utilizzare la partizione modificata
void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) {
    if (nitems > 1) {
        int pivotIndex = partition(base, size, compar, 0, nitems - 1);
        quick_sort(base, pivotIndex, size, compar);
        quick_sort(base + (pivotIndex + 1) * size, nitems - pivotIndex - 1, size, compar);
    }
}
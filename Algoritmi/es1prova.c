#include <stdio.h>
#include <stdlib.h>
#include "es1.h"
//max record è messo per limitare i record letti da file il codice mi sembra giusto ordina correttamente ma pe rla memoria della virtual machine 20M non li legge (10M funzionante si può salire fino a vedere quanto regge)
int max_records = 20000000;

typedef struct {
    int id;
    char field1[100];
    int field2;
    float field3;
} Record;
int compare_field1(const void *a, const void *b) {
    Record *recordA = (Record *)a;
    Record *recordB = (Record *)b;
    return strcmp(recordA->field1, recordB->field1);
}

int compare_field2(const void *a, const void *b) {
    Record *recordA = (Record *)a;
    Record *recordB = (Record *)b;
    return (recordA->field2 - recordB->field2);
}

int compare_field3(const void *a, const void *b) {
    Record *recordA = (Record *)a;
    Record *recordB = (Record *)b;
    if (recordA->field3 < recordB->field3) return -1;
    if (recordA->field3 > recordB->field3) return 1;
    return 0;
}
void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo) {
      FILE *file = fopen(infile, "r");
    if (file == NULL) {
        printf("Non è stato possibile aprire il file.\n");
        return ;
    }

    Record *records = (Record*) malloc(20000000 * sizeof(Record));
    if (records == NULL) {
        printf("Non è stato possibile allocare la memoria.\n");
        return ;
    }
    int i = 0;
    while (i < max_records &&fscanf(file, "%d,%[^,],%d,%f\n", &records[i].id, records[i].field1, &records[i].field2, &records[i].field3) != EOF) {
        i++;
    }
    fclose(file);
   
    int (*compare)(const void *, const void *);
    switch (field) {
        case 1:
            compare = compare_field1;
            break;
        case 2:
            compare = compare_field2;
            break;
        case 3:
            compare = compare_field3;
            break;
        default:
            printf("Campo non valido.\n");
            return;
    }
   
    switch (algo) {
        case 1:
            merge_sort(records, i, sizeof(Record), compare);
            break;
        case 2:
            quick_sort(records, i, sizeof(Record), compare);
            break;
        default:
            printf("Algoritmo non valido.\n");
            return;
    }

       FILE *outFile = fopen(outfile, "w");
    if (outFile == NULL) {
        printf("Non è stato possibile aprire il file di output.\n");
        return;
    }

   
     switch (field) {
        case 1:
             for (int j = 0; j < i; j++) {
            fprintf(outFile, "%s,%d,%f\n",  records[j].field1, records[j].field2, records[j].field3);
            }
            break;
        case 2:
             for (int j = 0; j < i; j++) {
        fprintf(outFile, "%d,%s,%f\n",  records[j].field2, records[j].field1, records[j].field3);
        }
            break;
        case 3:
             for (int j = 0; j < i; j++) {
        fprintf(outFile, "%f,%s,%d\n",  records[j].field3, records[j].field1, records[j].field2);
    }
            break;
        default:
            printf("Campo non valido.\n");
            return;
    }
    fclose(outFile);
    free(records);
}


int main() {
    
    sort_records("records.csv","es1prova.out",1,1);

    return 0;
}

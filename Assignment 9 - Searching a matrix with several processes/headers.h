#include <semaphore.h>
#include <stdbool.h>

typedef struct Cell{
    int bit;
    sem_t bit_sem;
}Cell;


typedef struct Map{
    Cell cells[100][100];
    sem_t row_edjes_sems[99][99];
    sem_t column_edjes_sems[99][99];
    bool row_edjes_flags[99][99];
    bool column_edjes_flags[99][99];
    sem_t k_sem;
    int k;
}Map;
/*========================== Stack ===============================*/
#include "Stack.h"
#include <stdlib.h>
#include <string.h>

Stack* buat_Stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->puncak = NULL;
    return stack;
}

void tumpuk(Stack* Stack, const char* data) {
    SimpulStack* simpul = (SimpulStack*)malloc(sizeof(SimpulStack));
    simpul->data = strdup(data);
    simpul->berikutnya = Stack->puncak;
    Stack->puncak = simpul;
}

char* ambil_dari_Stack(Stack* Stack) {
    if (Stack_kosong(Stack)) return NULL;
    
    SimpulStack* temp = Stack->puncak;
    char* data = temp->data;
    Stack->puncak = temp->berikutnya;
    free(temp);
    return data;
}

int Stack_kosong(Stack* Stack) {
    return Stack->puncak == NULL;
}

void hapus_Stack(Stack* Stack) {
    while (!Stack_kosong(Stack)) {
        char* data = ambil_dari_Stack(Stack);
        free(data);
    }
    free(Stack);
}

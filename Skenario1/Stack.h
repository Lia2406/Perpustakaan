/*=================================== Stack ===============================*/
#ifndef Stack_H
#define Stack_H

typedef struct SimpulStack {
    char* data;
    struct SimpulStack* berikutnya;
} SimpulStack;

typedef struct {
    SimpulStack* puncak;
} Stack;

Stack* buat_Stack();
void tumpuk(Stack* Stack, const char* data);
char* ambil_dari_Stack(Stack* Stack);
int Stack_kosong(Stack* Stack);
void hapus_Stack(Stack* Stack);

#endif

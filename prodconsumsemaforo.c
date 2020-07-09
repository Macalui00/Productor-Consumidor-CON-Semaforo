#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define BUFFER_SIZE 5

int fillCount = 0; //semáforo que indica la cantidad de datos almacenados en el buffer.
int emptyCount = BUFFER_SIZE; //semafor que indica la cantidad de posiciones disponibles en el buffer.
int item = 0;
int BUFFER[BUFFER_SIZE]; //Buffer finito.

int produceItem();
void sleepProdWakeupCons();
void sleepConsWakeupProd();
void consumer();
void producer();
void putItemIntoBuffer(int item,int BUFFER[],int fillCount);
int removeItemFromBuffer(int fillCount,int BUFFER[]);
void consumeItem();
void upFill();
void downEmpty(int *emptyCount);
void downFill(int *fillCount);
void upEmpty(int *emptyCount);
void downFill(int *fillCount);

void producer() {
    printf("El productor está ejecutando.\n");
    while (true) {
        int item = produceItem();
        downEmpty(&emptyCount);
        putItemIntoBuffer(item, BUFFER, fillCount);
        upFill(&fillCount);
    }
}
void sleepProdWakeupCons(){
    printf("Se pone a dormir al productor, se despierta al consumidor.\n");
    Sleep(3000);
    consumer();
}

void putItemIntoBuffer(int item,int BUFFER[],int fillCount){
    printf("El item que se agregará al Buffer: %d\n", item);
    BUFFER[fillCount] = item;
    printf("Item colocado en el buffer: %d\n", BUFFER[fillCount], ", en la posición: %d\n", fillCount);
    Sleep(3000);
   }


int produceItem(){
    printf("Se produce el ítem que se colocara en el buffer.\n");
    int numero = rand() % (2);
    return numero;
}

void downEmpty(int *emptyCount){
    printf("Se quiere decrementar el emptycount.\n");
    if (*emptyCount == 0){
        printf("El buffer esta lleno, no se puede decrementar el emptycount,\n no se pueden agregar más datos.\n");
        Sleep(3000);
    } else {
        printf("Se decrementa el emptycount.\n");
        Sleep(3000);
        *emptyCount= *emptyCount - 1;
        printf("El emptycount ahora es igual a: %d\n", *emptyCount);
    }
}

void upFill(int *fillCount){
    printf("Se quiere incrementar el fillcount.\n");
    if (*fillCount == BUFFER_SIZE){
        printf("No se puede incrementar el fillcount porque el buffer esta lleno.\n");
        Sleep(3000);
        sleepProdWakeupCons();
    } else {
        printf("Se incrementa el fillcount.");
        *fillCount = *fillCount + 1;
        printf("El fillcount ahora esta en: %d", *fillCount);
        Sleep(3000);
    }
}

void consumer() {
    printf("El consumidor esta ejecutando.");
    while (true) {
        item = removeItemFromBuffer(fillCount,BUFFER);
        downFill(&fillCount);
        upEmpty(&emptyCount);
        consumeItem(item);
    }
}

void downFill(int *fillCount){
    printf("Se quiere decrementar el fillcount.\n");
    if (*fillCount == 0){
        printf("El fillcount es igual a cero, buffer vacío.\n");
        Sleep(3000);
    } else {
        printf("Se decrementa el fillcount.\n");
        *fillCount = *fillCount - 1;
        Sleep(3000);
        printf("El fillcount ahora es igual a: %d", *fillCount);
    }
}
void upEmpty(int *emptyCount){
    printf("Se quiere incrementar el emptycount.\n");
    if (*emptyCount == BUFFER_SIZE){
        printf("No se puede incrementar porque el buffer ya esta vacio.\n");
        Sleep(3000);
        sleepConsWakeupProd();
    } else {
        printf("se incrementa el emptycount.\n");
        *emptyCount = *emptyCount + 1;
        printf("El emptycount ahora es igual a: %d", *emptyCount);
    }
}

void sleepConsWakeupProd(){
    printf("Se pone a dormir al consumidor y se despierta al productor.\n");
    Sleep(3000);
    producer();
}

int removeItemFromBuffer(int fillCount,int BUFFER[]){
    if(fillCount != 0){
        printf("Se remueve un item del buffer.\n");
        int i = 0;
        i = BUFFER[fillCount];
        for(int a = 0;a++; a<fillCount){
            BUFFER[a] = BUFFER[a+1];
        }
        return i;
    }
}

void consumeItem(int item){
    printf("El item removido es: %d\n", item);
    Sleep(3000);
}

void randomConsProd(){
    int numero = rand() % (2);
    if (numero = 0) {
        printf("Productor despierto.\n");
        Sleep(3000);
        producer();
    } else {
        printf("Consumidor despierto.\n");
        Sleep(3000);
        consumer();
    }
}
int main(void){
    randomConsProd();
    return 0;
}

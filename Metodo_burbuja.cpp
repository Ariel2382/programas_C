#include <stdio.h>

void intercambiar(int * a, int * b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void burbuja(int * arr, int n){
    int i, j, temp;
    // El bucle externo maneja el número de pasos
    // El bucle interno maneja el número de iteraciones
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-1; j++){
            if(arr[j]>arr[j+1]){
                intercambiar(&arr[j], &arr[j+1]);
            }    
        }
    }
}

void desplegar(int arr[], int n){
    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
}

int main(){
    int arr[] = {7, 3, 9, 0, 1, -3, 6, 8, 9};
    int n = sizeof(arr)/sizeof(int);
    printf("\nLista antes de ordenar: \n");
    desplegar(arr, n);
    printf("\n\nLista despues de ordenar: \n");
    burbuja(arr, n);
    desplegar(arr, n);
}

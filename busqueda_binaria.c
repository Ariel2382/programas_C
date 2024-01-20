#include <stdio.h>
#include <limits.h>

int busquedaBinaria(int arreglo[], int n, int buscado){
	int izquierdo = 0;
	int derecho = n-1;
	
	while(izquierdo <= derecho){
		int mitad = izquierdo + (derecho-izquierdo)/2;
		if(arreglo[mitad] == buscado){
			// Retorna el indice del elemento encontrado
			return mitad;
		}
		if(arreglo[mitad] < buscado){
			// Descartamos lado izquierdo
			izquierdo = mitad + 1;
		} else{
			// Descartamos lado derecho
			derecho = mitad - 1;
		}
	}
	
	return INT_MIN;
}

int main(){
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int n = sizeof(arr)/sizeof(arr[0]);
	int buscado = 7;
	int indice = busquedaBinaria(arr, n, buscado);
	if(indice == -1){
		printf("\nEl valor buscado no se encuentra en el arreglo");
	} else{
		printf("\nEl valor buscado se encuentra en el indice: %d", indice);
	}
	
	return 0;
}

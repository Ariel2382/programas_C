#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nombre[50];
    int puntos;
} Equipo;
void capturarDatosEquipos();
void generarCalendario(int numEquipos);
void generarMarcadores(int numEquipos);
void generarFinales(int numEquipos);
void mejoresEquipos(int numEquipos);



int main() {
    int numEquipos,opc;
    printf("Ingrese el numero de equipos: ");
    scanf("%d", &numEquipos);
    do{
	
    printf("\n1.presione uno para capturar los aquipos");
    printf("\n2.presione dos para generar calendario");
    printf("\n3.presione tres para generar finales");
    scanf("%i",&opc);
    switch(opc){
	
    case 1:
    capturarDatosEquipos();
    break;
    case 2:
    generarCalendario(numEquipos);
    generarMarcadores(numEquipos);
    break;
    
    case 3:
    generarFinales(numEquipos);
    mejoresEquipos(numEquipos);
    break;
    case 4:
    	printf("salida exitosa");
    default:
    	printf("opcion invalida intente nuevamente");
    }
}
while(opc!=4);
    return 0;
}

void capturarDatosEquipos() {
    FILE* archivo = fopen("equipos.txt", "w");
    int numEquipos,i;

    printf("Ingrese el numero de equipos: ");
    scanf("%d", &numEquipos);

    getchar(); // Consumir el carácter de nueva línea pendiente en el búfer

    for (i = 0; i < numEquipos; i++) {
        Equipo equipo;

        printf("Equipo %d:\n", i + 1);
        printf("Nombre: ");
        fgets(equipo.nombre, sizeof(equipo.nombre), stdin);

        // Eliminar el carácter de nueva línea al final de la cadena
        equipo.nombre[strcspn(equipo.nombre, "\n")] = '\0';

        equipo.puntos = 0;

        fwrite(&equipo, sizeof(Equipo), 1, archivo);
    }

    fclose(archivo);
}

void generarCalendario(int numEquipos) {
    FILE* archivoEquipos = fopen("equipos.txt", "r");
    FILE* archivoCalendario = fopen("calendario.txt", "w");
  


    Equipo* equipos = (Equipo*)malloc(numEquipos * sizeof(Equipo));
    fread(equipos, sizeof(Equipo), numEquipos, archivoEquipos);
int semana,i;
    for (semana = 1; semana <= numEquipos - 1; semana++) {
        printf("Semana %d:\n", semana);

        for (i = 0; i < numEquipos / 2; i++) {
            printf("Partido %d: %s vs %s\n", i + 1, equipos[i].nombre, equipos[numEquipos - 1 - i].nombre);
            fprintf(archivoCalendario, "Semana %d - Partido %d: %s vs %s\n", semana, i + 1, equipos[i].nombre,
                    equipos[numEquipos - 1 - i].nombre);
        }

        // Rotar los equipos para la siguiente semana
        Equipo temp = equipos[numEquipos - 1];
        for (i = numEquipos - 1; i > 1; i--) {
            equipos[i] = equipos[i - 1];
        }
        equipos[1] = temp;
    }

    fclose(archivoEquipos);
    fclose(archivoCalendario);
    free(equipos);
}

void generarMarcadores(int numEquipos) {
    FILE* archivoEquipos = fopen("equipos.txt", "r");
    FILE* archivoCalendario = fopen("calendario.txt", "r");
    FILE* archivoMarcadores = fopen("marcadores.txt", "w");
    FILE* archivoPuntajes = fopen("puntajes.txt", "w");
    srand(time(NULL));

    Equipo* equipos = (Equipo*)malloc(numEquipos * sizeof(Equipo));
    fread(equipos, sizeof(Equipo), numEquipos, archivoEquipos);

    // Resto del código para generar los marcadores y actualizar puntajes

    fclose(archivoEquipos);
    fclose(archivoCalendario);
    fclose(archivoMarcadores);
    fclose(archivoPuntajes);
    free(equipos);
}

void mejoresEquipos(int numEquipos) {
    FILE* archivoPuntajes = fopen("puntajes.txt", "r");
    FILE* archivoMejores = fopen("mejores.txt", "w");

    Equipo* equipos = (Equipo*)malloc(numEquipos * sizeof(Equipo));
    fread(equipos, sizeof(Equipo), numEquipos, archivoPuntajes);
int i,j;
    // Ordenar los equipos por puntaje de mayor a menor
    for (i = 0; i < numEquipos - 1; i++) {
        for (j = i + 1; j < numEquipos; j++) {
            if (equipos[j].puntos > equipos[i].puntos) {
                Equipo temp = equipos[i];
                equipos[i] = equipos[j];
                equipos[j] = temp;
            }
        }
    }

    // Escribir los datos de los mejores equipos en el archivo
    for (i = 0; i < numEquipos; i++) {
        fwrite(&equipos[i], sizeof(Equipo), 1, archivoMejores);
    }

    fclose(archivoPuntajes);
    fclose(archivoMejores);
    free(equipos);
}

void generarFinales(int numEquipos) {
    FILE* archivoMejores = fopen("mejores.txt", "r");
    FILE* archivoFinales = fopen("finales.txt", "w");
    
    srand(time(NULL));
    int numPartidos = 2;

    Equipo* equipos = (Equipo*)malloc(numEquipos * sizeof(Equipo));
    fread(equipos, sizeof(Equipo), numEquipos, archivoMejores);
int i;
    for (i = 0; i < numPartidos; i++) {
        int golesLocal = rand() % 5;  
        int golesVisitante = rand() % 5;  
        

        printf("Final %d: %s %d - %d %s\n", i + 1, equipos[i].nombre, golesLocal, golesVisitante,
            equipos[numEquipos - 1 - i].nombre);
        fprintf(archivoFinales, "Final %d: %s %d - %d %s\n", i + 1, equipos[i].nombre, golesLocal, golesVisitante,
            equipos[numEquipos - 1 - i].nombre);

        
        equipos[i].puntos += golesLocal == golesVisitante ? 1 : (golesLocal > golesVisitante ? 3 : 0);
        equipos[numEquipos - 1 - i].puntos += golesLocal == golesVisitante ? 1 : (golesLocal < golesVisitante ? 3 : 0);
    }

    
    fseek(archivoMejores, 0, SEEK_SET);
    fwrite(equipos, sizeof(Equipo), numEquipos, archivoMejores);

    fclose(archivoMejores);
    fclose(archivoFinales);
    free(equipos);
}


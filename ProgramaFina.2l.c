#include<stdio.h>
#include<stdlib.h> //Biblioteca malloc
#include<string.h>//Biblioteca de las cadenas
#include <locale.h> //Biblioteca para idiomas
 
struct fuente
{
	char nombre[20];
	float pH;
	int Conductividad, Turbidez, Coliformes;
};
struct fuenteaux
{
	char nombref[20],pHf[5],conductf[5], turbf[5], colif[5];
};

void Menu(char *opcion); 
int ImprimirFichero(char ncsv[]);
void CreaFichero(char ncsv[]);
void Instrucciones(char *informacion);
int csvAEstructura(char ncsv[],int nfil,struct fuente *num);
int nChar(char y[]);
int nFil(char ncsv[]);
void nomcsv(char ncsv[]);
void ordenar_fuente(struct fuente[], int);//Ordenar el pH de mayor a menor
void ordenar_fuente2(struct fuente[], int);//Ordenar el pH de menor a mayor

int main(){
	setlocale(LC_CTYPE,"Spanish");//Idioma español, poner tildes y "ñ". De la biblioteca locale
	struct fuente *num;
	int nfil=0;
	char opcion,informacion;
	char ncsv[26];
	
	
	
	
	do{
		Menu(&opcion);

		switch(opcion)
		{
			case 'a':
				system("cls");
				printf("IMPRIMIR UNA TABLA\n\n");
				//Pedir nombre
				nomcsv(ncsv);
				system("cls");
				printf("%s\n\n",ncsv);
				ImprimirFichero(ncsv);
				system("PAUSE");
				break;
			case 'b':
				system("cls");
				printf("COMPARAR EN UNA O MÁS TABLAS\n\n");
				nomcsv(ncsv);
				nfil=nFil(ncsv);
				num =  (struct fuente *) malloc (nfil*sizeof (struct fuente));
				csvAEstructura(ncsv,nfil,*&num);
				
				//Ordenar pH de mayor a menor
				ordenar_fuente2(num, nfil);
				
				
				//Preguntar cuántas tablas quiere comparar.
				//Bucle para pedir (tantas veces como haya puesto) que escriba nombre del fichero, si no lo encuentra pedir otro hasta que exista el que pide
				//Si falla 2 veces de nombre, mensaje de te estás equivocando mucho, volver al menú
				system("PAUSE"); //Parar para comprobar que coge la opción, cuando pongamos una función o algo podemos quitarlo
				break;
			case 'c':
				system("cls");
				printf("CREAR UNA NUEVA TABLA\n\n");
				nomcsv(ncsv);
				CreaFichero(ncsv);
				system("cls");
				printf("Has creado: %s\n\n",ncsv);
				ImprimirFichero(ncsv);
				system("PAUSE"); //Parar para comprobar que coge la opción, cuando pongamos una función o algo podemos quitarlo
				break;
			case 'd':
				system("cls");
				printf("INSTRUCCIONES IMPORTANTES\n\n");
				Instrucciones(&informacion); //LLAMADA A LA FUNCION 2. Vaya, que la pones a funcionar aquí
				break;
			case 'e':
				system("cls");
				printf("¡Nos vemos!\n\n");
				system("PAUSE"); //Parar para que vea el mensaje antes de que se cierre el programa
				break;
			default: 
				system("cls");
				printf("Opción no disponible\n\n");
				system("PAUSE"); //Parar para que vea el mensaje antes de que se repita la pregunta
				break;
		}
		//Aquí metemos el resto del programa con ifs
	}while(opcion!='e');
}

//Función. Menú
void Menu(char *opcion){
	system("cls");//Borrar pantalla	
	printf("FUENTES DE MADRID\n");	
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n",61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61);//Esto es un subrayado
	
	printf("Bienvenida al menú de opciones %c: \n",01);//Cara contenta
	printf("Introduce la opción:\n\n");
	printf("a-Imprimir tabla\n");
	printf("b-Comparar una o más tablas\n");
	printf("c-Crear una nueva tabla\n");
	printf("d-Instrucciones importantes\n");
	printf("e-Salir\n\n");
	fflush(stdin);
	scanf("%c",&*opcion);
}

//Función. Imprimir fichero
int ImprimirFichero(char ncsv[]){
	FILE * csvfichero;
	int nfil,contcol=0,contfil=0;
	
	//Primero abrir el fichero
	csvfichero= fopen(ncsv,"r");//Modo lectura	
	
	//Comprueba si encuentra el fichero si no lo siguiente no va
	if(csvfichero==NULL){
		printf("No se ha podido encontrar el fichero\n");
		return 0;
	}

	char csv=fgetc(csvfichero);
		
	//Mientras no haya acabado el csv
	while (!feof(csvfichero))
	{
		if(csv==';') //Cuando cambia de casilla 
		{
			printf("\t");
			contcol++;
			if(contcol>=3 && contfil!=0) //Solo por estética
			{
				printf("\t");
			}
		}else if(csv=='\n')
		{
			printf("%c",csv);
			contfil++;
			contcol=0;
		}else
		{
			printf("%c",csv);
		}
        csv=fgetc(csvfichero);
    }
    //Tercer paso es siempre cerrar el fichero al final
	fclose(csvfichero);
	printf("\n");
	return 1;
}

//Función. Crea un nuevo fichero
void CreaFichero(char ncsv[])
{
	struct fuente *num;
	int i,nfil=0;
	FILE *csvfichero;
	
	csvfichero = fopen(ncsv, "w+");//Abre fichero vacio
	printf("Introduce el numero de fuentes: ");
	scanf("%d", &nfil);
	//Memoria dinámica
	num =  (struct fuente *) malloc (nfil*sizeof (struct fuente));
	printf("Introduce los datos: \n\n");
	
	for(i=0; i<nfil; i++){
		printf("Fuente_%d. Introduce los siguientes datos:\n", i+1);
		printf("pH --> ");
		fflush(stdin);
		scanf("%f", &num[i].pH);
		printf("Conductividad --> ");
		scanf("%d", &num[i].Conductividad);
		printf("Turbidez --> ");
		scanf("%d", &num[i].Turbidez);
		printf("Coliformes --> ");
		scanf("%d", &num[i].Coliformes);
	}
		
		
	fprintf(csvfichero, "Parametros;pH;Conductividad;Turbidez;Coliformes\n");
		for (i=0; i<nfil; i++) { 
	fprintf(csvfichero, "Fuente_%d;%.2f;%d;%d;%d\n", i, num[i].pH, num[i].Conductividad, num[i].Turbidez, num[i].Turbidez);
	}
	
	fclose(csvfichero);
}

//Función. Instrucciones
void Instrucciones(char*informacion){					
	do{
		printf("\n¿Qué quieres saber?\n\n");
		printf("a-Nombres de los archivos\n");
		printf("b-Información proporcionada en los archivos\n");
		printf("c-Ya sé todo lo importante\n\n");
		fflush(stdin);
		scanf("%c",&*informacion);
		
		switch(*informacion)
		{
			case 'a':
				printf("NOMBRES DE LOS ARCHIVOS\n");
				printf("Para que el programa funcione, debes tener en tu ordenador uno o más ficheros llamados YYYYMM_Lugar, donde:\n");
				printf("YYYY: año\nMM: mes\nLugar:uno de los barrios de Madrid de los que se tengan archivos.\n");
				system("PAUSE"); //Parar para que vea el mensaje
				break;
			case 'b':
				printf("INFORMACIÓN PROPORCIONADA EN LOS ARCHIVOS\n");
				printf("Dentro del fichero hay una fila que corresponde a los datos de una fuente. En cada fila está:\n");
				printf("Nombre de la fuente\npH\nConductividad(%cS/cm)\nTurbidez(NTU)\nColiformes(UFC/100mL)\n",181); //el símbolo de micro
				system("PAUSE"); //Parar para que vea el mensaje
				break;
			case 'c':
				printf("¡Vuelve cuando te surjan más dudas!\n\n");
				system("PAUSE"); //Parar para que vea el mensaje antes de que se cierre el menú
				break;
			default: 
				printf("Opción no disponible\n\n");
				system("PAUSE"); //Parar para que vea el mensaje antes de que se repita la pregunta
				break;			
		}
	}while(*informacion!='c');
}

int csvAEstructura(char ncsv[],int nfil,struct fuente *num) { //Esto es la de comparar ficheros
	FILE * csvfichero;
	struct fuenteaux *numaux;
	
	int i=0,j=0,c0=0,c1=0,c2=0,c3=0,c4=0,contcol=0,contfil=0;
	
	//Memoria dinámica
	numaux =  (struct fuenteaux *) malloc (nfil*sizeof (struct fuenteaux));
	
	//Primero abrir el fichero
	csvfichero= fopen(ncsv,"r");//Modo lectura	
	
	//Comprueba si encuentra el fichero si no lo siguiente no va
	if(csvfichero==NULL){
		printf("No se ha podido encontrar el fichero\n");
		return 0;
	}
	
	char csv=fgetc(csvfichero);

	while (csv!=EOF)
	{
		if(csv==';')
		{
			contcol++;
		} else if(csv=='\n')
		{
			if(contfil>0)
			{
				i=contfil-1;
				numaux[i].nombref[c0]='\0',numaux[i].pHf[c1]='\0',numaux[i].conductf[c2]='\0',numaux[i].turbf[c3]='\0',numaux[i].colif[c4]='\0';
			}
			contcol=0,c0=0,c1=0,c2=0,c3=0,c4=0;
			contfil++;
		} else if(contfil>0)
		{
			i=contfil-1;
			if(contcol==0)
			{
				numaux[i].nombref[c0]=csv;
				c0++;
			}else if(contcol==1)
			{
				numaux[i].pHf[c1]=csv;
				c1++;
			} else if(contcol==2)
			{
				numaux[i].conductf[c2]=csv;
				c2++;
			} else if(contcol==3)
			{
				numaux[i].turbf[c3]=csv;
				c3++;
			} else if(contcol==4)
			{
				numaux[i].colif[c4]=csv;
				c4++;
			}
		}
		csv=fgetc(csvfichero);
	}
	
	//Tercer paso es siempre cerrar el fichero al final
	fclose(csvfichero);

	for(i=0;i<nfil-1;i++)
	{
		strcpy(num[i].nombre,numaux[i].nombref);
		//Pasar de string a float o int
		num[i].pH=atof(numaux[i].pHf),num[i].Conductividad=atoi(numaux[i].conductf),num[i].Turbidez=atoi(numaux[i].turbf),num[i].Coliformes=atoi(numaux[i].colif);
		//printf("%.2f\t%d\t%d\t%d\n",num[i].pH,num[i].Conductividad,num[i].Turbidez,num[i].Coliformes);
	}

    return 0;
}

//Función. Contador filas
int nFil(char ncsv[])
{
	FILE * csvfichero;
	int cont=0;
	
	//Primero abrir el fichero
	csvfichero= fopen(ncsv,"r");//Modo lectura	
	
	//Comprueba si encuentra el fichero si no lo siguiente no va
	if(csvfichero==NULL){
		printf("No se ha podido encontrar el fichero\n");
		return 0;
	}

	char csv=fgetc(csvfichero);
	
	//Mientras no haya acabado el csv
	while (!feof(csvfichero))
	{
        if(csv=='\n') //Cuando baja de fila
		{
			cont++;
		}
        csv=fgetc(csvfichero); 
    }
    //Tercer paso es siempre cerrar el fichero al final
	fclose(csvfichero);
	
    return cont;
}

//Función pedir el nombre del csv
void nomcsv(char ncsv[])
{
	int cont1,cont2;
	char y[4],m[2],L[20];
	
	//Pedir año, repetir mientras no sea 4 dígitos
	do{
		printf("Introduzca el año (con 4 dígitos):\n");
		scanf("%s",&y);
    	cont1=nChar(y);
	}while(cont1!=4);
	
	//Pedir mes, repetir mientras no sea 2 dígitos
	do{
		printf("Introduzca el mes (con 2 dígitos):\n");
		scanf("%s",&m);
    	cont2=nChar(m);
	}while(cont2!=2);
	
	//Pedir lugar, repetir mientras no tenga una consonante al principio
	do{
		printf("Introduzca el barrio: (la primera letra mayúscula)\n");
		scanf("%s",&L);
	}while(65>L[0]||L[0]>90);
	
	//Copia "y" en "ncsv" y se une el resto a "ncsv" para que quede guardado el nombre del archivo que se quiere abrir
	strcat(strcat(strcat(strcat(strcpy(ncsv,y),m),"_"),L),".csv");
}

//Función contador de caracteres
int nChar(char y[])
{
	int i=0, cont=0;
		
	while (y[i]!='\0')
	{
        cont++;
        i++; 
    }
    return cont;
}


//++++++++++++++++++++++++++++++++++++++++++++++

//Ordenar el pH de mayor a menor
void ordenar_fuente(struct fuente datos[], int nfuente) {
	
	int i, j;
	struct fuente aux;
	int v[nfuente];
	
	//Ordenar los vectores
	for (i=0; i<nfuente; i++) {
		for(j=i+1; j<nfuente; j++) {
			if(datos[i].pH < datos[j].pH) {
				aux = datos[i];
				datos[i]=datos[j];
				datos[j]= aux;
			}
			
		}
	}
	
	for(i=0; i<(nfuente-1);i++) {
		printf("%s\t%.2f\t%d\t%d\t%d\n", datos[i].nombre, datos[i].pH, datos[i].Conductividad, datos[i].Turbidez, datos[i].Coliformes);
	}
	
}

//Ordenar fuente de menor a mayor
void ordenar_fuente2(struct fuente datos[], int nfuente) {
	
	int i, j;
	struct fuente aux;
	int v[nfuente];
	
	//Ordenar los vectores
	for (i=0; i<nfuente-1; i++) {
		for(j=i+1; j<nfuente; j++) {
			if(datos[i].pH > datos[j].pH) {
				aux = datos[i];
				datos[i]=datos[j];
				datos[j]= aux;
			}
			
		}
	}
	
	for(i=1; i<(nfuente);i++) {
		printf("%s\t%.2f\t%d\t%d\t%d\n", datos[i].nombre, datos[i].pH, datos[i].Conductividad, datos[i].Turbidez, datos[i].Coliformes);
	}
	
}

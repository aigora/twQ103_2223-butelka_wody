#include<stdio.h>
#include<string.h>//Funciones de las cadenas
#include <locale.h> //Biblioteca para idiomas


int nChar(char y[]);
int nFil(char ncsv[]);
void nomcsv(char ncsv[]); 
void Menu(char *opcion); 
int ImprimirFichero();
void Instrucciones(char *informacion);
int main(){
	setlocale(LC_CTYPE,"Spanish");//Idioma espa�ol, poner tildes y "�". De la biblioteca locale
	char opcion,informacion;
	do{
		Menu(&opcion);

		switch(opcion)
		{
			case 'a':
				printf("IMPRIMIR UNA TABLA\n\n");
				ImprimirFichero();
				system("PAUSE"); //Parar para que lea el fichero
				break;
			case 'b':
				printf("COMPARAR EN UNA O M�S TABLAS\n\n");
				//Preguntar cu�ntos ficheros quiere comparar.
				//Bucle para pedir (tantas veces como haya puesto) que escriba nombre del fichero, si no lo encuentra pedir otro hasta que exista el que pide
				//Si falla 2 veces de nombre, mensaje de te est�s equivocando mucho, volver al men�
				system("PAUSE"); //Parar para comprobar que coge la opci�n, cuando pongamos una funci�n o algo podemos quitarlo
				break;
			case 'c':
				printf("CREAR UNA NUEVA TABLA\n\n");
				
				system("PAUSE"); //Parar para comprobar que coge la opci�n, cuando pongamos una funci�n o algo podemos quitarlo
				break;
			case 'd':
				printf("INSTRUCCIONES IMPORTANTES\n\n");
				Instrucciones(&informacion); //LLAMADA A LA FUNCION 2. Vaya, que la pones a funcionar aqu�
				break;
			case 'e':
				printf("�Nos vemos!\n\n");
				system("PAUSE"); //Parar para que vea el mensaje antes de que se cierre el programa
				break;
			default: 
				printf("Opci�n no disponible\n\n");
				system("PAUSE"); //Parar para que vea el mensaje antes de que se repita la pregunta
				break;
		}
		//Aqu� metemos el resto del programa con ifs
	}while(opcion!='e');
}

//Funci�n. Men�
void Menu(char *opcion){
	system("cls");//Borrar pantalla	
	printf("FUENTES DE MADRID\n");	
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n",61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61);//Esto es un subrayado
	
	printf("Bienvenida al men� de opciones %c: \n",01);//Cara contenta
	printf("Introduce la opci�n:\n\n");
	printf("a-Imprimir tabla\n");
	printf("b-Comparar una o m�s tablas\n");
	printf("c-Crear una nueva tabla\n");
	printf("d-Instrucciones importantes\n");
	printf("e-Salir\n\n");
	fflush(stdin);
	scanf("%c",&*opcion);
}

//Funci�n. Imprimir fichero
int ImprimirFichero(){
	FILE * csvfichero;
	int nfil;
	char ncsv[26];
	//Pedir nombre
	nomcsv(ncsv);
	//Contar filas
	nfil=nFil(ncsv);
	
	//AQU� HAY QUE VER C�MO QUEREMOS IMPRIMIR EL FICHERO
	
	
	return 1;
}

//Funci�n pedir el nombre del csv
void nomcsv(char ncsv[])
{
	int cont1,cont2;
	char y[4],m[2],L[20];
	
	//Pedir a�o, repetir mientras no sea 4 d�gitos
	do{
		printf("Introduzca el a�o (con 4 d�gitos):\n");
		scanf("%s",&y);
    	cont1=nChar(y);
	}while(cont1!=4);
	
	//Pedir mes, repetir mientras no sea 2 d�gitos
	do{
		printf("Introduzca el mes (con 2 d�gitos):\n");
		scanf("%s",&m);
    	cont2=nChar(m);
	}while(cont2!=2);
	
	//Pedir lugar, repetir mientras no tenga una consonante al principio
	do{
		printf("Introduzca el barrio: (la primera letra may�scula)\n");
		scanf("%s",&L);
	}while(65>L[0]||L[0]>90);
	
	//Copia "y" en "ncsv" y se une el resto a "ncsv" para que quede guardado el nombre del archivo que se quiere abrir
	strcat(strcat(strcat(strcat(strcpy(ncsv,y),m),"_"),L),".csv");
}

//Funci�n contador de caracteres
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

//Funci�n. Instrucciones
void Instrucciones(char*informacion){					
	do{
		printf("�Qu� quieres saber?\n\n");
		printf("a-Nombres de los archivos\n");
		printf("b-Informaci�n proporcionada en los archivos\n");
		printf("c-Ya s� todo lo importante\n\n");
		fflush(stdin);
		scanf("%c",&*informacion);
		
		switch(*informacion)
		{
			case 'a':
				printf("NOMBRES DE LOS ARCHIVOS\n");
				printf("Para que el programa funcione, debes tener en tu ordenador uno o m�s ficheros llamados YYYYMM_Lugar, donde:\n");
				printf("YYYY: a�o\nMM: mes\nLugar:uno de los barrios de Madrid de los que se tengan archivos.\n");
				system("PAUSE"); //Parar para que vea el mensaje
				break;
			case 'b':
				printf("INFORMACI�N PROPORCIONADA EN LOS ARCHIVOS\n");
				printf("Dentro del fichero hay una fila que corresponde a los datos de una fuente. En cada fila est�:\n");
				printf("Nombre de la fuente\npH\nConductividad(%cS/cm)\nTurbidez(NTU)\nColiformes(UFC/100mL)\n",181); //el s�mbolo de micro
				system("PAUSE"); //Parar para que vea el mensaje
				break;
			case 'c':
				printf("�Vuelve cuando te surjan m�s dudas!\n\n");
				system("PAUSE"); //Parar para que vea el mensaje antes de que se cierre el men�
				break;
			default: 
				printf("Opci�n no disponible\n\n");
				system("PAUSE"); //Parar para que vea el mensaje antes de que se repita la pregunta
				break;			
		}
	}while(*informacion!='c');
}

//Funci�n. Contador fuentes (filas-1)
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
	
	//Descontar la fila de  los t�tulos
    return cont-1;
}

#include<stdio.h>
#include<stdlib.h> //Biblioteca malloc
#include<string.h>//Biblioteca de las cadenas
#include <locale.h> //Biblioteca para idiomas
 
struct fuente //Estructura principal
{
	char nombre[20];
	float pH;
	int Conductividad, Turbidez, Coliformes;
};
struct fuenteaux //Estructura auxiliar para la funcion csvAEstructura
{
	char nombref[20],pHf[5],conductf[5], turbf[5], colif[5];
};

void Menu(char *opcion); 
int ImprimirFichero(int nfil,struct fuente *num);
void CreaFichero(char ncsv[]);
void Instrucciones(char *informacion);
int csvAEstructura(char ncsv[],int nfil,struct fuente *num);
void menuEstadisticas(char *opcion2, char *parametro);
void menuEstadisticas2(char *opcion2,char *parametro);
float MediaVector (int nfil,struct fuente *num, char parametro);
void OrdenarVectormM (int nfil,struct fuente *num,char parametro);
void OrdenarVectorMm (int nfil,struct fuente *num,char parametro);
float MedianaVector (int nfil,struct fuente *num, char parametro);
int nChar(char y[]);
int nFil(char ncsv[]);
void nomcsv(char ncsv[]);
int main(){
	setlocale(LC_CTYPE,"Spanish");//Idioma español, poner tildes y "ñ". De la biblioteca locale
	struct fuente *num,*num2;
	int nfil=0,nfil2=0,numtablas=0,i=0;
	float media[2],max[2],min[2],mediana[2];
	char opcion,informacion,parametro,opcion2;
	char ncsv[26],ncsv2[26];
	do{
		Menu(&opcion);

		switch(opcion)
		{
			case 'a':
				system("cls"); //Borrar pantalla
				printf("IMPRIMIR UNA TABLA\n\n");
				nomcsv(ncsv);
				system("cls");
				printf("%s\n\n",ncsv);
				nfil=nFil(ncsv);
				num =  (struct fuente *) malloc (nfil*sizeof (struct fuente));
				csvAEstructura(ncsv,nfil,*&num);
				ImprimirFichero(nfil,*&num);
				system("PAUSE");
				break;
			case 'b':
				system("cls");
				printf("COMPARAR EN UNA O MÁS TABLAS\n\n");
				do
				{
					printf("¿Quieres hacer hacer comparaciones en 1 o 2 tablas?\n");
					scanf("%d",&numtablas);
				}while(numtablas!=1 && numtablas!=2);
				if(numtablas==1)
				{
					nomcsv(ncsv);
					nfil=nFil(ncsv);
					num =  (struct fuente *) malloc (nfil*sizeof (struct fuente));
					csvAEstructura(ncsv,nfil,*&num);
					menuEstadisticas(&opcion2,&parametro);
					switch(opcion2)
					{
						case 'a':
							system("cls");
							printf("MEDIA\n");
							media[0]=MediaVector (nfil,*&num,parametro);
							switch(parametro)
							{
								case 'a':
									printf("La media de pH de %s es: %.2f\n",ncsv,media[0]);
									break;
								case 'b':
									printf("La media de conductividad de %s es: %.2f\n",ncsv,media[0]);
									break;
								case 'c':
									printf("La media de turbidez de %s es: %.2f\n",ncsv,media[0]);
									break;
								case 'd':
									printf("La media de coliformes de %s es: %.2f\n",ncsv,media[0]);
									break;
								default:
									break;
							}
							system("PAUSE");
							break;
						case 'b':
							system("cls");
							printf("MÁXIMO VALOR\n");
							OrdenarVectorMm(nfil,*&num,parametro);
							switch(parametro)
							{
								case 'a':
									max[0]=num[0].pH;
									printf("El valor máximo de pH de %s es:\n%s %.2f\n",ncsv,num[0].nombre,max[0]);
									break;
								case 'b':
									max[0]=num[0].Conductividad;
									printf("El valor máximo de conductividad de %s es:\n%s %.2f\n",ncsv,num[0].nombre,max[0]);
									break;
								case 'c':
									max[0]=num[0].Turbidez;
									printf("El valor máximo de turbidez de %s es:\n%s %.2f\n",ncsv,num[0].nombre,max[0]);
									break;
								case 'd':
									max[0]=num[0].Coliformes;
									printf("El valor máximo de coliformes de %s es:\n%s %.2f\n",ncsv,num[0].nombre,max[0]);
									break;
								default:
									break;
							}
							system("PAUSE");
							break;
						case 'c':
							system("cls");
							printf("MEDIANA\n");
							OrdenarVectorMm(nfil,*&num,parametro);
							mediana[0]=MedianaVector(nfil,*&num,parametro);
							switch(parametro)
							{
								case 'a':
									printf("La mediana de pH de %s es: %.2f\n",ncsv,mediana[0]);
									break;
								case 'b':
									printf("La mediana de conductividad de %s es: %.2f\n",ncsv,mediana[0]);
									break;
								case 'c':
									printf("La mediana de turbidez de %s es: %.2f\n",ncsv,mediana[0]);
									break;
								case 'd':
									printf("La mediana de coliformes de %s es: %.2f\n",ncsv,mediana[0]);
									break;
								default:
									break;
							}
							system("PAUSE");
							break;
						case 'd':
							system("cls");
							printf("VECTOR DE MAYOR A MENOR\n");
							OrdenarVectorMm(nfil,*&num,parametro);
							switch(parametro)
							{
								case 'a':
									printf("El vector pH de %s ordenado de mayor a menor es:\n",ncsv);
									for(i=0;i<nfil-1;i++)
									{
										printf("%s: %.2f\t",num[i].nombre,num[i].pH);
									}
									printf("\n");
									break;
								case 'b':
									printf("El vector conductividad de %s ordenado de mayor a menor es:\n",ncsv);
									for(i=0;i<nfil-1;i++)
									{
										printf("%s: %d\t",num[i].nombre,num[i].Conductividad);
									}
									printf("\n");
									break;
								case 'c':
									printf("El vector turbidez de %s ordenado de mayor a menor es:\n",ncsv);
									for(i=0;i<nfil-1;i++)
									{
										printf("%s: %d\t",num[i].nombre,num[i].Turbidez);
									}
									printf("\n");
									break;
								case 'd':
									printf("El vector coliformes de %s ordenado de mayor a menor es:\n",ncsv);
									for(i=0;i<nfil-1;i++)
									{
										printf("%s: %d\t",num[i].nombre,num[i].Coliformes);
									}
									printf("\n");
									break;
								default:
									break;
							}
							system("PAUSE");
							break;
						case 'e':
							system("cls");
							printf("VECTOR DE MENOR A MAYOR\n");
							OrdenarVectormM(nfil,*&num,parametro);
							switch(parametro)
							{
								case 'a':
									printf("El vector pH de %s ordenado de menor a mayor es:\n",ncsv);
									for(i=0;i<nfil-1;i++)
									{
										printf("%s: %.2f\t",num[i].nombre,num[i].pH);
									}
									printf("\n");
									break;
								case 'b':
									printf("El vector conductividad de %s ordenado de menor a mayor es:\n",ncsv);
									for(i=0;i<nfil-1;i++)
									{
										printf("%s: %d\t",num[i].nombre,num[i].Conductividad);
									}
									printf("\n");
									break;
								case 'c':
									printf("El vector turbidez de %s ordenado de menor a mayor es:\n",ncsv);
									for(i=0;i<nfil-1;i++)
									{
										printf("%s: %d\t",num[i].nombre,num[i].Turbidez);
									}
									printf("\n");
									break;
								case 'd':
									printf("El vector coliformes de %s ordenado de menor a mayor es:\n",ncsv);
									for(i=0;i<nfil-1;i++)
									{
										printf("%s: %d\t",num[i].nombre,num[i].Coliformes);
									}
									printf("\n");
									break;
								default:
									break;
							}
							system("PAUSE");
							break;
						default:
							break;
					}
				}else if(numtablas==2)
				{
					printf("\nPrimer archivo:\n");
					nomcsv(ncsv);
					nfil=nFil(ncsv);
					num =  (struct fuente *) malloc (nfil*sizeof (struct fuente));
					csvAEstructura(ncsv,nfil,*&num);
					printf("\nSegundo archivo:\n");
					nomcsv(ncsv2);
					nfil2=nFil(ncsv2);
					num2 =  (struct fuente *) malloc (nfil2*sizeof (struct fuente));
					csvAEstructura(ncsv2,nfil2,*&num2);
					menuEstadisticas2(&opcion2,&parametro);
					switch(opcion2)
					{
						case 'a':
							system("cls");
							printf("MEDIA DE CADA BARRIO\n");
							media[0]=MediaVector (nfil,*&num,parametro);
							media[1]=MediaVector (nfil2,*&num2,parametro);
							switch(parametro)
							{
								case 'a':
									printf("La media de pH de %s es: %.2f\n",ncsv,media[0]);
									printf("La media de pH de %s es: %.2f\n",ncsv2,media[1]);
									break;
								case 'b':
									printf("La media de conductividad de %s es: %.2f\n",ncsv,media[0]);
									printf("La media de conductividad de %s es: %.2f\n",ncsv2,media[1]);
									break;
								case 'c':
									printf("La media de turbidez de %s es: %.2f\n",ncsv,media[0]);
									printf("La media de turbidez de %s es: %.2f\n",ncsv2,media[1]);
									break;
								case 'd':
									printf("La media de coliformes de %s es: %.2f\n",ncsv,media[0]);
									printf("La media de coliformes de %s es: %.2f\n",ncsv2,media[1]);
									break;
								default:
									break;
							}
							system("PAUSE");
							break;
						case 'b':
							system("cls");
							printf("MEDIA DE LOS DOS BARRIOS\n");
							media[0]=MediaVector (nfil,*&num,parametro);
							media[1]=MediaVector (nfil2,*&num2,parametro);
							switch(parametro)
							{
								case 'a':
									if(media[0]<media[1])
									{
										printf("La media más alta de pH de %s y %s está en %s y es: %.2f\n",ncsv,ncsv2,ncsv2,media[1]);
									}else if(media[0]>media[1])
									{
										printf("La media más alta de pH de %s y %s está en %s y es: %.2f\n",ncsv,ncsv2,ncsv,media[0]);
									}else
									{
										printf("La media más alta de pH de %s y %s es la misma en los dos: %.2f\n",ncsv,ncsv2,media[0]);
									}
									break;
								case 'b':
									if(media[0]<media[1])
									{
										printf("La media más alta de conductividad de %s y %s está en %s y es: %.2f\n",ncsv,ncsv2,ncsv2,media[1]);
									}else if(media[0]>media[1])
									{
										printf("La media más alta de conductividad de %s y %s está en %s y es: %.2f\n",ncsv,ncsv2,ncsv,media[0]);
									}else 
									{
										printf("La media más alta de conductividad de %s y %s es la misma en los dos: %.2f\n",ncsv,ncsv2,media[0]);
									}
									break;
								case 'c':
									if(media[0]<media[1])
									{
										printf("La media más alta de turbidez de %s y %s está en %s y es: %.2f\n",ncsv,ncsv2,ncsv2,media[1]);
									}else if(media[0]>media[1])
									{
										printf("La media más alta de turbidez de %s y %s está en %s y es: %.2f\n",ncsv,ncsv2,ncsv,media[0]);
									}else
									{
										printf("La media más alta de turbidez de %s y %s es la misma en los dos: %.2f\n",ncsv,ncsv2,media[0]);
									}
									break;
								case 'd':
									if(media[0]<media[1])
									{
										printf("La media más alta de coliformes de %s y %s está en %s y es: %.2f\n",ncsv,ncsv2,ncsv2,media[1]);
									}else if(media[0]>media[1])
									{
										printf("La media más alta de coliformes de %s y %s está en %s y es: %.2f\n",ncsv,ncsv2,ncsv,media[0]);
									}else
									{
										printf("La media más alta de coliformes de %s y %s es la misma en los dos: %.2f\n",ncsv,ncsv2,media[0]);
									}
									break;
								default:
									break;
							}
							system("PAUSE");
							break;
						case 'c':
							system("cls");
							printf("MÁXIMO DE CADA BARRIO\n");
							OrdenarVectorMm(nfil,*&num,parametro);
							OrdenarVectorMm(nfil2,*&num2,parametro);
							switch(parametro)
							{
								case 'a':
									max[0]=num[0].pH;
									max[1]=num2[0].pH;
									printf("El valor máximo de pH de %s es:\n%s %.2f\n",ncsv,num[0].nombre,max[0]);
									printf("El valor máximo de pH de %s es:\n%s %.2f\n",ncsv2,num2[0].nombre,max[1]);
									break;
								case 'b':
									max[0]=num[0].Conductividad;
									max[1]=num2[0].Conductividad;
									printf("El valor máximo de conductividad de %s es:\n%s %.2f\n",ncsv,num[0].nombre,max[0]);
									printf("El valor máximo de conductividad de %s es:\n%s %.2f\n",ncsv2,num2[0].nombre,max[1]);
									break;
								case 'c':
									max[0]=num[0].Turbidez;
									max[1]=num2[0].Turbidez;
									printf("El valor máximo de turbidez de %s es:\n%s %.2f\n",ncsv,num[0].nombre,max[0]);
									printf("El valor máximo de turbidez de %s es:\n%s %.2f\n",ncsv2,num2[0].nombre,max[1]);
									break;
								case 'd':
									max[0]=num[0].Coliformes;
									max[1]=num2[0].Coliformes;
									printf("El valor máximo de coliformes de %s es:\n%s %.2f\n",ncsv,num[0].nombre,max[0]);
									printf("El valor máximo de coliformes de %s es:\n%s %.2f\n",ncsv2,num2[0].nombre,max[1]);
									break;
								default:
									break;
							}
							system("PAUSE");
							break;
						case 'd':
							system("cls");
							printf("MÁXIMO DE LOS DOS BARRIOS\n");
							OrdenarVectorMm(nfil,*&num,parametro);
							OrdenarVectorMm(nfil2,*&num2,parametro);
							switch(parametro)
							{
								case 'a':
									max[0]=num[0].pH;
									max[1]=num2[0].pH;
									if(max[0]<max[1])
									{
										printf("La medida más alta de pH de %s y %s está en %s y es:\n%s %.2f\n",ncsv,ncsv2,ncsv2,num2[0].nombre,max[1]);
									}else if(max[0]>max[1])
									{
										printf("La medida más alta de pH de %s y %s está en %s y es:\n%s %.2f\n",ncsv,ncsv2,ncsv,num2[0].nombre,max[0]);
									}else 
									{
										printf("La medida más alta de pH de %s y %s es la misma en los dos: %.2f\n",ncsv,ncsv2,max[0]);
									}
									break;
								case 'b':
									max[0]=num[0].Conductividad;
									max[1]=num2[0].Conductividad;
									if(max[0]<max[1])
									{
										printf("La medida más alta de conductividad de %s y %s está en %s y es:\n%s %.2f\n",ncsv,ncsv2,ncsv2,num2[0].nombre,max[1]);
									}else if(max[0]>max[1])
									{
										printf("La medida más alta de conductividad de %s y %s está en %s y es:\n%s %.2f\n",ncsv,ncsv2,ncsv,num2[0].nombre,max[0]);
									}else 
									{
										printf("La medida más alta de conductividad de %s y %s es la misma en los dos: %.2f\n",ncsv,ncsv2,max[0]);
									}
									break;
								case 'c':
									max[0]=num[0].Turbidez;
									max[1]=num2[0].Turbidez;
									if(max[0]<max[1])
									{
										printf("La medida más alta de turbidez de %s y %s está en %s y es:\n%s %.2f\n",ncsv,ncsv2,ncsv2,num2[0].nombre,max[1]);
									}else if(max[0]>max[1])
									{
										printf("La medida más alta de turbidez de %s y %s está en %s y es:\n%s %.2f\n",ncsv,ncsv2,ncsv,num[0].nombre,max[0]);
									}else 
									{
										printf("La medida más alta de turbidez de %s y %s es la misma en los dos: %.2f\n",ncsv,ncsv2,max[0]);
									}
									break;
								case 'd':
									max[0]=num[0].Coliformes;
									max[1]=num2[0].Coliformes;
									if(max[0]<max[1])
									{
										printf("La medida más alta de coliformes de %s y %s está en %s y es:\n%s %.2f\n",ncsv,ncsv2,ncsv2,num2[0].nombre,max[1]);
									}else if(max[0]>max[1])
									{
										printf("La medida más alta de coliformes de %s y %s está en %s y es:\n%s %.2f\n",ncsv,ncsv2,ncsv,num[0].nombre,max[0]);
									} else
									{
										printf("La medida más alta de coliformes de %s y %s es la misma en los dos: %.2f\n",ncsv,ncsv2,max[0]);
									}
									break;
								default:
									break;
							}
							system("PAUSE");
							break;
						case 'e':
							system("cls");
							printf("MEDIANA DE CADA BARRIO\n");
							OrdenarVectorMm(nfil,*&num,parametro);
							mediana[0]=MedianaVector(nfil,*&num,parametro);
							OrdenarVectorMm(nfil2,*&num2,parametro);
							mediana[1]=MedianaVector(nfil2,*&num2,parametro);
							switch(parametro)
							{
								case 'a':
									printf("La mediana de pH de %s es: %.2f\n",ncsv,mediana[0]);
									printf("La mediana de pH de %s es: %.2f\n",ncsv2,mediana[1]);
									break;
								case 'b':
									printf("La mediana de conductividad de %s es: %.2f\n",ncsv,mediana[0]);
									printf("La mediana de conductividad de %s es: %.2f\n",ncsv2,mediana[1]);
									break;
								case 'c':
									printf("La mediana de turbidez de %s es: %.2f\n",ncsv,mediana[0]);
									printf("La mediana de turbidez de %s es: %.2f\n",ncsv2,mediana[1]);
									break;
								case 'd':
									printf("La mediana de coliformes de %s es: %.2f\n",ncsv,mediana[0]);
									printf("La mediana de coliformes de %s es: %.2f\n",ncsv2,mediana[1]);
									break;
								default:
									break;
							}
							system("PAUSE");
							break;
						default:
							break;
					}
				}
				break;
			case 'c':
				system("cls");
				printf("CREAR UNA NUEVA TABLA\n\n");
				nomcsv(ncsv);
				CreaFichero(ncsv);
				nfil=nFil(ncsv);
				num =  (struct fuente *) malloc (nfil*sizeof (struct fuente));
				csvAEstructura(ncsv,nfil,*&num);
				system("cls");
				printf("Has creado: %s\n\n",ncsv);
				ImprimirFichero(nfil,*&num);
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
	do
	{
	system("cls");//Borrar pantalla	
	printf("     ` ' `                                        ` ' `            \n");
	printf(" .'''. ' .'''.                                .'''. ' .'''.       \n");
	printf("   .. ' ' ..                                    .. ' ' ..       \n");
	printf("  '  '.'.'  '        FUENTES DE MADRID         '  '.'.'  '      \n");
	printf("  .'''.'.'''.                                  .'''.'.'''.\n");
	printf(" ' .''.'.''. '          .----------.          ' .''.'.''. '\n");
	printf("   . . : . .            |__________|            . . : . .\n");
	printf(" _'___':'___'_         /|__________|%c         _'___':'___'_ \n",92);
	printf("(_____________)        /____________%c        (_____________)\n",92);
	printf("    (     )            ||          ||            (     )\n");
	printf("    _)   (_            |            |            _)   (_\n");
	printf("   (_______)                                    (_______)\n\n");
	
	printf("Bienvenida al menú de opciones %c: \n",01);//Cara contenta
	printf("Introduce la opción:\n\n");
	printf("a-Imprimir tabla\n");
	printf("b-Comparar una o más tablas\n");
	printf("c-Crear una nueva tabla\n");
	printf("d-Instrucciones importantes\n");
	printf("e-Salir\n\n");
	fflush(stdin);
	scanf("%c",&*opcion);	
	}while (*opcion!='a'&&*opcion!='b'&&*opcion!='c'&&*opcion!='d'&&*opcion!='e');
}

//Función. Imprimir fichero
int ImprimirFichero(int nfil,struct fuente *num){
	int i=0,bul=0;
	printf("Parametros\tpH\tConductividad\tTurbidez\tColiformes\n");
	for (i=0; i<nfil-1; i++) 
	{
		//Imprimir estructura en forma de tabla
		printf("%s\t%.2f\t%d\t\t%d\t\t%d", num[i].nombre, num[i].pH, num[i].Conductividad, num[i].Turbidez, num[i].Coliformes);
		if(num[i].pH>=9.5 ||num[i].pH<=6.5)
		{
			printf("\t\t¡AVISO!\n");
			bul=1; 	
		}
		printf("\n");
	}
	if(bul==1) //Se imprime si previamente se ha imprimido el AVISO
	{
		printf("\n¡AVISO!\n");
		printf("El agua apta para poder ser consumida tiene que tener un pH entre 6.5 y 9.5.\n");
		printf("Si la media del pH se sale del rango 6.5-9.5, es probable que esto se deba a un exceso de minerales,\npor lo que es inútil añadirle cloro al agua ya que este le impedirá actuar.\n");
	}
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
	//Pedir datos
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
		
	//Escribirlo en el documento	
	fprintf(csvfichero, "Parametros;pH;Conductividad;Turbidez;Coliformes\n");
	for (i=0; i<nfil; i++) 
	{ 
	fprintf(csvfichero, "Fuente_%d;%.2f;%d;%d;%d\n", i, num[i].pH, num[i].Conductividad, num[i].Turbidez, num[i].Coliformes);
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
				system("PAUSE"); 
				break;
			case 'c':
				printf("¡Vuelve cuando te surjan más dudas!\n\n");
				system("PAUSE"); 
				break;
			default: 
				printf("Opción no disponible\n\n");
				system("PAUSE"); 
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
	//Lee con char el documento hasta el fin del documento 
	while (csv!=EOF)
	{
		if(csv==';')
		{
			contcol++;
		} else if(csv=='\n')
		{
			//Mete el char en el vector que corresponda (en función de la columna)
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
	}

    return 0;
}

//Función. Menú para calcular estadísticas
void menuEstadisticas(char *opcion2,char *parametro) 
{
	do {
		system("cls");
		printf("Escoge entre una de las siguientes operaciones estadísticas:\n");
		printf("a-Media\n");
		printf("b-Máximo valor\n");
		printf("c-Mediana\n");
		printf("d-Ordenar las fuentes de mayor a menor\n");
		printf("e-Ordenar las fuentes de menor a mayor\n");
		printf("f-Salir\n");
		fflush(stdin);
		scanf("%c", &*opcion2);
	
		switch (*opcion2) 
		{
			case 'a':
				printf("¿De cuál de los siguientes parámetros quieres calcular la media?\n");
				printf("a-pH\n");
				printf("b-Conductividad\n");
				printf("c-Turbidez\n");
				printf("d-Coliformes\n");
				printf("e-Salir\n");
				fflush(stdin);
				scanf("%c", &*parametro);
				break;
				
			case 'b':
				printf("¿De cuál de los siguientes parámetros quieres ver el valor máximo?\n");
				printf("a-pH\n");
				printf("b-Conductividad\n");
				printf("c-Turbidez\n");
				printf("d-Coliformes\n");
				printf("e-Salir\n");
				fflush(stdin);
				scanf("%c", &*parametro);
				break;
			case 'c':
				printf("¿De cuál de los siguientes parámetros quieres calcular la mediana?\n");
				printf("a-pH\n");
				printf("b-Conductividad\n");
				printf("c-Turbidez\n");
				printf("d-Coliformes\n");
				printf("e-Salir\n");
				fflush(stdin);
				scanf("%c", &*parametro);
				break;
			case 'd':
				printf("¿Cuál de los siguientes parámetros quieres ordenar de mayor a menor?\n");
				printf("a-pH\n");
				printf("b-Conductividad\n");
				printf("c-Turbidez\n");
				printf("d-Coliformes\n");
				printf("e-Salir\n");
				fflush(stdin);
				scanf("%c", &*parametro);
				break;
			case 'e':
				printf("¿Cuál de los siguientes parámetros quieres ordenar de menor a mayor?\n");
				printf("a-pH\n");
				printf("b-Conductividad\n");
				printf("c-Turbidez\n");
				printf("d-Coliformes\n");
				printf("e-Salir\n");
				fflush(stdin);
				scanf("%c", &*parametro);
				break;
			case 'f':
				printf("¡Hasta pronto!\n");
				system("PAUSE");
				break;
			default:
				printf("Opción no disponible. Por favor, elige una opción válida o pulse la opción de Salir\n");
				system("PAUSE");
				break;
		}
	} while(*opcion2!='a'&&*opcion2!='b'&&*opcion2!='c'&&*opcion2!='d'&&*opcion2!='e'&&*opcion2!='f');
}

//Función. Menú para calcular estadísticas2
void menuEstadisticas2(char *opcion2,char *parametro) 
{
	do {
		system("cls");
		printf("Escoge entre una de las siguientes operaciones estadísticas:\n");
		printf("a-Media de cada barrio\n");
		printf("b-Media de los dos barrios\n");
		printf("c-Máximo valor de cada barrio\n");
		printf("d-Máximo valor de los dos barrios\n");
		printf("e-Mediana de cada barrio\n");
		printf("f-Salir\n");
		fflush(stdin);
		scanf("%c", &*opcion2);
	
		switch (*opcion2) 
		{
			case 'a':
				printf("¿De cuál de los siguientes parámetros quieres calcular la media?\n");
				printf("a-pH\n");
				printf("b-Conductividad\n");
				printf("c-Turbidez\n");
				printf("d-Coliformes\n");
				printf("e-Salir\n");
				fflush(stdin);
				scanf("%c", &*parametro);
				break;
				
			case 'b':
				printf("¿De cuál de los siguientes parámetros quieres calcular la media?\n");
				printf("a-pH\n");
				printf("b-Conductividad\n");
				printf("c-Turbidez\n");
				printf("d-Coliformes\n");
				printf("e-Salir\n");
				fflush(stdin);
				scanf("%c", &*parametro);
				break;
			case 'c':
				printf("¿De cuál de los siguientes parámetros quieres ver el valor máximo?\n");
				printf("a-pH\n");
				printf("b-Conductividad\n");
				printf("c-Turbidez\n");
				printf("d-Coliformes\n");
				printf("e-Salir\n");
				fflush(stdin);
				scanf("%c", &*parametro);
				break;
			case 'd':
				printf("¿De cuál de los siguientes parámetros quieres ver el valor máximo?\n");
				printf("a-pH\n");
				printf("b-Conductividad\n");
				printf("c-Turbidez\n");
				printf("d-Coliformes\n");
				printf("e-Salir\n");
				fflush(stdin);
				scanf("%c", &*parametro);
				break;
			case 'e':
				printf("¿De cuál de los siguientes parámetros quieres calcular la mediana?\n");
				printf("a-pH\n");
				printf("b-Conductividad\n");
				printf("c-Turbidez\n");
				printf("d-Coliformes\n");
				printf("e-Salir\n");
				fflush(stdin);
				scanf("%c", &*parametro);
				break;
			case 'f':
				printf("¡Hasta pronto!\n");
				system("PAUSE");
				break;
			default:
				printf("Opción no disponible. Por favor, elige una opción válida o pulse la opción de Salir\n");
				system("PAUSE");
				break;
		}
	} while(*opcion2!='a'&&*opcion2!='b'&&*opcion2!='c'&&*opcion2!='d'&&*opcion2!='e'&&*opcion2!='f');
}

//Función. Calcular media del vector
float MediaVector (int nfil,struct fuente *num,char parametro)
{
	int i=0;
	float suma=0,media=0;
	switch(parametro)
	{
		case 'a':
			for(i =0; i < nfil-1; i++)
			{
				suma+=num[i].pH; //sumatorio
			}
			break;
		case 'b':
			for(i =0; i < nfil-1; i++)
			{
				suma+=num[i].Conductividad;
			}
			break;
		case 'c':
			for(i =0; i < nfil-1; i++)
			{
				suma+=num[i].Turbidez;
			}
			break;
		case 'd':
			for(i =0; i < nfil-1; i++)
			{
				suma+=num[i].Coliformes;
			}
			break;
		case 'e':
			break;
		default:
			printf("Opción no disponible\n");
			system("PAUSE");
			break;
	}
	
	media=suma/(nfil-1);
	return media;
}

//Función. Ordenar el vector del vector menor a mayor
void OrdenarVectormM (int nfil,struct fuente *num,char parametro)
{
	char auxnom[26];
	int i=0,j=0,aux;
	float auxph=0;
	switch(parametro)
	{
		case 'a':
			for(j =0; j < nfil-2; j++)
			{
				for (i=0; i < nfil-2; i++)
				{
					if(num[i].pH>num[i+1].pH) 
					{
						auxph=num[i].pH; //en el aux se guarda el mayor
						strcpy(auxnom,num[i].nombre);
						num[i].pH=num[i+1].pH; //guardas el menor número en la primera posición del vector
						strcpy(num[i].nombre,num[i+1].nombre);
						num[i+1].pH=auxph;//guardas el mayor número en la segunda posición del vector
						strcpy(num[i+1].nombre,auxnom);
					}
				}
			}
			break;
		case 'b':
			for(j =0; j < nfil-2; j++)
			{
				for (i=0; i < nfil-2; i++)
				{
					if(num[i].Conductividad>num[i+1].Conductividad) 
					{
						aux=num[i].Conductividad;
						strcpy(auxnom,num[i].nombre);
						num[i].Conductividad=num[i+1].Conductividad;
						strcpy(num[i].nombre,num[i+1].nombre);
						num[i+1].Conductividad=aux;
						strcpy(num[i+1].nombre,auxnom);
					}
				}
			}
			break;
		case 'c':
			for(j =0; j < nfil-2; j++)
			{
				for (i=0; i < nfil-2; i++)
				{
					if(num[i].Conductividad>num[i+1].Conductividad) 
					{
						aux=num[i].Conductividad;
						strcpy(auxnom,num[i].nombre);
						num[i].Conductividad=num[i+1].Conductividad;
						strcpy(num[i].nombre,num[i+1].nombre);
						num[i+1].Conductividad=aux;
						strcpy(num[i+1].nombre,auxnom);
					}
				}
			}
			break;
		case 'd':
			for(j =0; j < nfil-2; j++)
			{
				for (i=0; i < nfil-2; i++)
				{
					if(num[i].Turbidez>num[i+1].Turbidez) 
					{
						aux=num[i].Turbidez;
						strcpy(auxnom,num[i].nombre);
						num[i].Turbidez=num[i+1].Turbidez;
						strcpy(num[i].nombre,num[i+1].nombre);
						num[i+1].Turbidez=aux;
						strcpy(num[i+1].nombre,auxnom);
					}
				}
			}
			break;
		case 'e':
			break;
		default:
			printf("Opción no disponible\n");
			system("PAUSE");
			break;
	}	
}

//Función. Ordenar el vector del vector mayor a menor
void OrdenarVectorMm (int nfil,struct fuente *num,char parametro)
{
	char auxnom[26];
	int i=0,j=0,k=nfil-2,aux;
	float auxph=0;
	switch(parametro)
	{
		case 'a':
			for(j =0; j < nfil-2; j++)
			{
				for (i=0; i < k; i++)
				{
					if(num[i].pH<num[i+1].pH) 
					{
						auxph=num[i].pH;
						strcpy(auxnom,num[i].nombre);
						num[i].pH=num[i+1].pH;
						strcpy(num[i].nombre,num[i+1].nombre);
						num[i+1].pH=auxph;
						strcpy(num[i+1].nombre,auxnom);
					}
				}
				k--;
			}
			break;
		case 'b':
			for(j =0; j < nfil-2; j++)
			{
				for (i=0; i < k; i++)
				{
					if(num[i].Conductividad<num[i+1].Conductividad) 
					{
						aux=num[i].Conductividad;
						strcpy(auxnom,num[i].nombre);
						num[i].Conductividad=num[i+1].Conductividad;
						strcpy(num[i].nombre,num[i+1].nombre);
						num[i+1].Conductividad=aux;
						strcpy(num[i+1].nombre,auxnom);
					}
				}
				k--;
			}
			break;
		case 'c':
			for(j =0; j < nfil-2; j++)
			{
				for (i=0; i < k; i++)
				{
					if(num[i].Conductividad<num[i+1].Conductividad) 
					{
						aux=num[i].Conductividad;
						strcpy(auxnom,num[i].nombre);
						num[i].Conductividad=num[i+1].Conductividad;
						strcpy(num[i].nombre,num[i+1].nombre);
						num[i+1].Conductividad=aux;
						strcpy(num[i+1].nombre,auxnom);
					}
				}
				k--;
			}
			break;
		case 'd':
			for(j =0; j < nfil-2; j++)
			{
				for (i=0; i < k; i++)
				{
					if(num[i].Turbidez<num[i+1].Turbidez) 
					{
						aux=num[i].Turbidez;
						strcpy(auxnom,num[i].nombre);
						num[i].Turbidez=num[i+1].Turbidez;
						strcpy(num[i].nombre,num[i+1].nombre);
						num[i+1].Turbidez=aux;
						strcpy(num[i+1].nombre,auxnom);
					}
				}
				k--;
			}
			break;
		case 'e':
			break;
		default:
			printf("Opción no disponible\n");
			system("PAUSE");
			break;
	}	
}

//Función. Calcular mediana del vector
float MedianaVector (int nfil,struct fuente *num,char parametro)
{
	float mediana=0,suma=0;
	int i=0,resultado=0,resultado1=0,resultado2=0;
	switch(parametro)
	{
		//pH
		case 'a':
			//número componentes del vector impar, mediana el componente del medio
			if((nfil-1)%2!=0)
			{
				resultado=(nfil/2);
				mediana=num[resultado].pH;
			}else //número componentes del vector par, mediana la media de los dos componentes del medio
			{
				resultado1=((nfil-1)/2);
				resultado2=((nfil-1)/2)-1;
				suma=num[resultado1].pH+num[resultado2].pH;
				mediana=suma/2;
			}
			break;
		//Conductividad
		case 'b':
			if((nfil-1)%2!=0)
			{
				resultado=(nfil/2);
				mediana=num[resultado].Conductividad;
			}else
			{
				resultado1=((nfil-1)/2);
				resultado2=((nfil-1)/2)-1;
				suma=num[resultado1].Conductividad+num[resultado2].Conductividad;
				mediana=suma/2;
			}
			break;
		//Turbidez
		case 'c':
			if((nfil-1)%2!=0)
			{
				resultado=(nfil/2);
				mediana=num[resultado].Turbidez;
			}else
			{
				resultado1=((nfil-1)/2);
				resultado2=((nfil-1)/2)-1;
				suma=num[resultado1].Turbidez+num[resultado2].Turbidez;
				mediana=suma/2;
			}
			break;
		//Coliformes
		case 'd':
			if((nfil-1)%2!=0)
			{
				resultado=(nfil/2);
				mediana=num[resultado].Coliformes;
			}else
			{
				resultado1=((nfil-1)/2);
				resultado2=((nfil-1)/2)-1;
				suma=num[resultado1].Coliformes+num[resultado2].Coliformes;
				mediana=suma/2;
			}
			break;
		case 'e':
			break;
		default:
			printf("Opción no disponible\n");
			system("PAUSE");
			break;
	}
	return mediana;
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

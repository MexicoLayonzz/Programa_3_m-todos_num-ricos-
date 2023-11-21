/*
IINTEGRANTES: 
Aguilar Martinez Fernando, 
Gonzalez Ordaz Ariel, 
Gutierrez Tapia Marco Antonio, 
Sandoval Madrigal Michelle
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define TOLERANCE 1e-6

bool CrearColumnas(double ***, int);
bool CrearFilas(double **, int);
bool CrearVector(double **, int);
void LlenarVector(double *, int);
void LlenarMatriz(double**, int);
void CopiaMatriz(double**, double**, int);
void ImprimirMatriz(double**, int);
double Determinante(double **, int);
int esDominante(double **,int);
void TriangularMatriz(double **, int);
void jacobi(double **, double *, double *, int, int, double);

int main(int argc, char const *argv[])
{
	double **md = NULL;
	double **mdc = NULL;
	double *vec = NULL;
	double correccion, determinante, tolerance;
	int num, aux, cori, corj;
	int i, j, n, maxIter;
	char var, hola[10];
	int res = 0,jacobires = 0;

	do
	{
		printf("\nIngrese el tamanio de la matriz: ");
		scanf("%d", &num);

		if(CrearColumnas(&md, num))
		{
			if (CrearFilas(md, num))
			{
				if(CrearVector(&vec, num))
				{
					LlenarMatriz(md, num);int i, j;
    				if (CrearColumnas(&mdc, num) && CrearFilas(mdc, num)) {
    				    for (i = 0; i < num; i++) {
    				        for (j = 0; j < num; j++) {
    					        mdc[i][j] = md[i][j];
    					    }
    					}
    				}
					printf("\nMatriz: ");
					ImprimirMatriz(md, num);
					aux = 2;
					do
		            {
		                printf("\n\nQuiere corregir algun elemento?\n1. Si\n2. No\nRespuesta: ");
		                scanf("%d", &aux);

		                if (aux == 1)
		                {
		                    printf("Ingrese la fila del elemento que desea corregir: ");
		                    scanf("%d", &cori);
		                    printf("Ingrese la columna del elemento que desea corregir: ");
		                    scanf("%d", &corj);
		                    printf("Ingrese el nuevo valor para esa posici?: ");
		                    scanf("%lf", &correccion);

		                    if (cori >= 0 && cori < num && corj >= 0 && corj < num)
		                    {
		                        md[cori-1][corj-1] = correccion;
		                        printf("\nMatriz Corregida:\n");
		                        ImprimirMatriz(md, num);
		                    }
		                    else
		                    {
		                        printf("Las coordenadas est? fuera de rango.\n");
		                    }
		                }
		            } while (aux == 1);

		            LlenarVector(vec, num);

		            if(esDominante(md, num) == 1)
		            {
		            	printf("\nLa matriz es dominante diagonalmente");
		            	determinante = Determinante(md, num);
		            	if (determinante == 0)
		            	{
		            		printf("\nEl sistema no tiene solucion");
		            		printf("\nDesea agregar otra matriz?\n1. Si\n2. No\nRespuesta: ");
		            		scanf("%d", &res);
		            	}else
		            	{
		            		printf("\nQuiere hacer la solucion de sistemas por Jacobi?\n1. Si\n2. No\nRespuesta: ");
		            		scanf("%d", &jacobires);
		            		if(jacobires == 1)
		            		{
								//ImprimirMatriz(md, num);
		            			double *x = (double *)malloc(num * sizeof(double));
		            			printf("Ingrese el número máximo de iteraciones: ");
								scanf("%d", &maxIter);
	
								printf("Ingrese la tolerancia: ");
								scanf("%lf", &tolerance);
							
								for (i = 0; i < num; i++) {
									x[i] = 0.0;
								}
							
								jacobi(mdc, vec, x, num, maxIter, tolerance);
								printf("Solución:\n");
								for (i = 0; i < num; i++) {
									printf("x[%d] = %lf\n", i, x[i]);
								}
								free(x);
							}
		            	}
		            }else
		            {
		            	printf("\nLa convergencia no se garantiza por no tratarse de un sistema EDD");
		            	TriangularMatriz(md, num);
		            	ImprimirMatriz(md, num);
		            	determinante = Determinante(md, num);
		            	printf("\nDeterminante = %lf", determinante);
		            	if (determinante == 0)
		            	{
		            		printf("\nEl sistema no tiene solucion");
		            		printf("\nDesea agregar otra matriz?\n1. Si\n2. No\nRespuesta: ");
		            		scanf("%d", &res);
		            	}else
		            	{
		            		printf("\nQuiere hacer la solucion de sistemas por Jacobi?\n1. Si\n2. No\nRespuesta: ");
		            		scanf("%d", &jacobires);
		            		if(jacobires == 1)
		            		{
								//ImprimirMatriz(md, num);
		            			double *x = (double *)malloc(num * sizeof(double));
		            			printf("Ingrese el número máximo de iteraciones: ");
								scanf("%d", &maxIter);
	
								printf("Ingrese la tolerancia: ");
								scanf("%lf", &tolerance);
							
								for (i = 0; i < num; i++) {
									x[i] = 0.0;
								}
							
								jacobi(mdc, vec, x, num, maxIter, tolerance);
								printf("Solución:\n");
								for (i = 0; i < num; i++) {
									printf("x[%d] = %lf\n", i, x[i]);
								}
								free(x);
							}
		            	}
		            }

					for (i = 0; i < num; i++)
		    		{
		        		free(md[i]);
		    		}

		    		free(md);
		    	}else
		    	{
		    		for (i = 0; i < num; i++)
		    		{
		        		free(md[i]);
		    		}

		    		free(md);
		    		exit(1);
		    	}
			}else
			{
				exit(1);
				free(md);
			}
		}else
		{
			exit(1);
		}
	}while(res == 1);
	
	getchar();
	
	return 0;
}

bool CrearColumnas(double ***matriz, int num)
{
	*matriz = (double **) malloc(sizeof(double *) * num);
	if(*matriz == NULL)
	{
		printf("\nNo hay memoria suficiente");
		return false;
	}else
	{
		return true;
	}
}

bool CrearFilas(double **md, int num)
{
	int i, j;
	for(i = 0; i < num; ++i)
	{
		*(md + i) = (double *) malloc(sizeof(double) * num);
		if(*(md + i) == NULL)
		{
			printf("\nNo hay memoria suficiente");
			for(j = 0; j < i; ++j)
			{
				free(*( md +j ));
			}
			free(md);
			return false;
		}
	}
	return true;
}

bool CrearVector(double **vec, int num)
{
	*vec = (double *) malloc(sizeof(double) * num);
	if (vec = NULL)
	{
		printf("\nNo hay memoria suficiente");
		return false;
	}else
	{
		return true;
	}
}

void LlenarVector(double *vec, int num)
{
	int i;
	putchar('\n');
	for (i = 0; i < num; i++) {
    	printf("\nIngrese el elemento %d del vector: ", i + 1);
    	scanf("%lf", &vec[i]);
    }
}

void LlenarMatriz(double **md, int num)
{
	int i , j;
	for (i = 0; i < num; ++i)
	{
		for (j = 0; j < num; ++j)
		{
			printf("\nIngrese el elemento (%d , %d): ", i, j);
			scanf("%lf", *(md + i) + j);
		}
	}
}

void ImprimirMatriz(double **md, int num)
{
	int i, j;
	for (i = 0; i < num; ++i)
	{
		printf("\n");
		for(j = 0; j < num; ++j)
		{
			printf("%lf\t", *(*(md + i) + j));
		}
	}
}


double Determinante(double **md, int num)
{
	double **matriz_copia = NULL;
    int i, j, k;
    double determinante = 1.0;
    
    if (CrearColumnas(&matriz_copia, num) && CrearFilas(matriz_copia, num)) {
        for (i = 0; i < num; i++) {
            for (j = 0; j < num; j++) {
                matriz_copia[i][j] = md[i][j];
            }
        }
    } else {
        return 0.0; // Error al crear la copia de la matriz
    }

    for (i = 0; i < num; i++) {
        for (j = i + 1; j < num; j++) {
            double factor = matriz_copia[j][i] / matriz_copia[i][i];
            for (k = i; k < num; k++) {
                matriz_copia[j][k] -= factor * matriz_copia[i][k];
            }
        }
        determinante *= matriz_copia[i][i];
    }

    for (i = 0; i < num; i++) {
        free(matriz_copia[i]);
    }
    free(matriz_copia);

    return determinante;
}

int esDominante(double **md,int num) 
{
    int dominante = 1;
	double suma,comp;
    int i,j;
	for (i = 0; i < num; i++) {
        suma = 0.0;
        for (j = 0; j < num; j++) {
            if (i != j) {
                suma += fabs(md[i][j]);
            }else{
            	comp = fabs(md[i][i]);
			}
        }
        if (comp < suma) {
        	//printf("%f >= %f\n",comp,suma);
            dominante = 0;
            break;
        }else{
        	//printf("%f >= %f\n",comp,suma);
        	dominante = 1;
		}
    }
    return dominante;
}

void TriangularMatriz(double **matriz, int n) 
{
    int i, j, k;
    for (k = 0; k < n; k++) {
        for (i = k + 1; i < n; i++) {
            double factor = matriz[i][k] / matriz[k][k];
            for (j = k; j < n; j++) {
                matriz[i][j] -= factor * matriz[k][j];
            }
        }
    }
}

void jacobi(double **a, double *b, double *x, int n, int maxIter, double tolerance) {
    int i, j, k;
    double *newX;

    newX = (double *)malloc(n * sizeof(double));

    for (k = 0; k < maxIter; k++) {
        for (i = 0; i < n; i++) {
            newX[i] = b[i];
            for (j = 0; j < n; j++) {
                if (i != j) {
                    newX[i] -= a[i][j] * x[j];
                }
            }
            newX[i] /= a[i][i];
        }

        // Verificar convergencia
        double error = 0.0;
        for (i = 0; i < n; i++) {
            error += fabs(newX[i] - x[i]);
        }

        if (error < tolerance) {
            printf("Convergencia alcanzada en la iteración %d\n", k + 1);
            break;
        }

        // Actualizar solución
        for (i = 0; i < n; i++) {
            x[i] = newX[i];
        }
    }
    free(newX);
}


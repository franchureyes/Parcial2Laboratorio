/*
 ============================================================================
 Name        : Parcial 2 Laboratorio.c
 Author      : Reyes Francisco Nicolás
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "inputs.h"
#include "Servicios.h"

int main(void) {
	setbuf(stdout, NULL);

	int opciones;
	int tipoAFiltrar;
	int flagOrdenar = 0;
	char path[TAMDESCRIPCION];

	LinkedList* listaServicios = ll_newLinkedList();
	LinkedList* listaMinoristas = ll_newLinkedList();
	LinkedList* listaMayoristas = ll_newLinkedList();
	LinkedList* listaExportar = ll_newLinkedList();
	LinkedList* listaPrecios = ll_newLinkedList();


	do{
		utn_getInt(&opciones,
						"************************"
						"\nMenu Principal:        *\n"
						"  1- Cargar archivo    *\n"
						"  2- Imprimir lista    *\n"
						"  3- Asignar totales   *\n"
						"  4- Filtrar por tipo  *\n"
						"  5- Mostrar servicios *\n"
						"  6- Guardar servicios *\n"
						"  7- Filtrar por precio mayor a 1000 *\n"
						"  8- Salir.	       *\n"
						"************************"
						"\nIngrese una opcion: ", "\nError. Elija una opcion valida.\n", 1, 8);

		switch(opciones)
		{
		case 1:
			if(utn_getName(path, "\nIngrese el nombre del archivo que desea cargar: ", "\nError. Ingrese un nombre valido.\n") == 0)
			{
				if(controller_cargarArchivo(path, listaServicios) == 0)
				{
					printf("\nLos datos han sido cargados exitosamente.\n");
				}
				else
				{
					printf("\nLos datos no se han podido cargar. Indique el nombre de un archivo valido.\n");
				}
			}
			break;
		case 2:
			if(controller_ListServicios(listaServicios) != 0)
			{
				printf("\nError. No se pudo mostrar la lista, se encuentra vacía o es invalida.\n");
			}
			break;
		case 3:
			if(controller_asignarTotales(listaServicios) == 0)
			{
				printf("\nSe han asignado los totales de los servicios correctamente.\n");
			}
			else
			{
				printf("\nError. La lista se encuentra vacia.\n");
			}
			break;
		case 4:
			utn_getInt(&tipoAFiltrar,
					"********************************"
					"\nOpciones para filtrar: *\n"
					"  1- Minorista 		       *\n"
					"  2- Mayorista		       *\n"
					"  3- Exportar		       *\n"
					"********************************"
					"\nIngrese una opcion: ", "\nError. Elija una opcion valida.\n", 1, 3);
			switch(tipoAFiltrar)
			{
			case 1:
				listaMinoristas = controller_FiltrarTipo(listaServicios, tipoAFiltrar);

				if(listaMinoristas != NULL)
				{
					printf("\nSe ha filtrado por MINORISTA correctamente.\n");

					if(controller_guardarArchivo("minoristas.csv", listaMinoristas) == 0)
					{
						printf("\nSe ha guardado con exito la lista filtrada por MINORISTA correctamente.\n");
					}
					else
					{
						printf("\nError. No se pudo guardar la lista filtrada.\n");
					}
				}
				else
				{
					printf("\nError. La lista se encuentra vacia o no hay servicios de este tipo.\n");
				}
				break;
			case 2:
				listaMayoristas = controller_FiltrarTipo(listaServicios, tipoAFiltrar);

				if(listaMayoristas != NULL)
				{
					printf("\nSe ha filtrado por MAYORISTA correctamente.\n");

					if(controller_guardarArchivo("mayoristas.csv", listaMayoristas) == 0)
					{
						printf("\nSe ha guardado con exito la lista filtrada por MAYORISTA correctamente.\n");
					}
					else
					{
						printf("\nError. No se pudo guardar la lista filtrada.\n");
					}
				}
				else
				{
					printf("\nError. La lista se encuentra vacia o no hay servicios de este tipo.\n");
				}
				break;
			case 3:
				listaExportar = controller_FiltrarTipo(listaServicios, tipoAFiltrar);

				if(listaExportar != NULL)
				{
					printf("\nSe ha filtrado por EXPORTAR correctamente.\n");

					if(controller_guardarArchivo("exportar.csv", listaExportar) == 0)
					{
						printf("\nSe ha guardado con exito la lista filtrada por EXPORTAR correctamente.\n");
					}
					else
					{
						printf("\nError. No se pudo guardar la lista filtrada.\n");
					}
				}
				else
				{
					printf("\nError. La lista se encuentra vacia o no hay servicios de este tipo.\n");
				}
				break;
			}
			break;
		case 5:
			if(controller_mostrarServiciosOrdenadosPorDescripcion(listaServicios) == 0)
			{
				flagOrdenar = 1;
			}
			else
			{
				printf("\nError. La lista se encuentra vacia.\n");
			}
			break;
		case 6:
			if(flagOrdenar == 1)
			{
				if(controller_guardarArchivo("data.txt", listaServicios) == 0)
				{
					printf("\nEl archivo fue guardado con exito en modo texto.\n");
				}
			}
			else
			{
				printf("\nError. Debe ordenar la lista antes de guardarla.\n");
			}
			break;
		case 7:
			listaPrecios = controller_FiltrarPrecio(listaServicios);

			if(controller_guardarArchivo("preciosfiltrados.csv", listaPrecios)==0)
			{
				printf("\nSe ha guardado con exito la lista filtrada por precios mayor a 1000 correctamente.\n");
			}
			break;
		default:
			printf("\nSaliendo...\n");
			break;
		}

	}while(opciones != 8);

	return 0;
}

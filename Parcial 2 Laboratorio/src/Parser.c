#include <stdio.h>
#include <stdlib.h>
#include "Servicios.h"
#include "LinkedList.h"

int parser_Servicios(FILE* pArchivo, LinkedList* pArrayServicios)
{
	int retorno = -1;

	if(pArchivo != NULL)
	{
		if(pArrayServicios != NULL)
		{
			eServicios* servicioAux;
			char id_servicio[TAMDATOS];
			char descripcion[TAMDESCRIPCION];
			char tipo[TAMDATOS];
			char precioUnitario[TAMDATOS];
			char cantidad[TAMDATOS];
			char precioTotal[TAMDATOS];

			fscanf(pArchivo, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", id_servicio, descripcion, tipo, precioUnitario, cantidad, precioTotal);

			while(1)
			{
				if(fscanf(pArchivo, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", id_servicio, descripcion, tipo, precioUnitario, cantidad, precioTotal) == 6)
				{
					servicioAux = Servicios_newParametros(id_servicio, descripcion, tipo, precioUnitario, cantidad, precioTotal);

					if(servicioAux != NULL)
					{
						if(ll_add(pArrayServicios, servicioAux) == 0)
						{
							retorno = 0;
						}
					}
				}

				if(feof(pArchivo) != 0)
				{
					break;
				}
			}
		}
	}

	return retorno;
}

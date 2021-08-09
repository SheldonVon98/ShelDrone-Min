/*
 * filters.c
 *
 *  Created on: 20 Jul 2021
 *      Author: sheldonvon
 */


#include "filters.h"

void complimentaryFilter(double *value, double update, double updatePerc){
	*value = (*value * (1-updatePerc)) + update*updatePerc;
}

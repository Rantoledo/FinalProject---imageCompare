/*
 * SPPoint.c
 *
 *  Created on: 6 αιεπ 2016
 *      Author: Rantoledo
 */

#include "SPPoint.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct sp_point_t{
	double* data;
	int index;
	int dim;
};

SPPoint spPointCreate(double* data, int dim, int index){

	if (data == NULL || dim <= 0 || index < 0){
		return NULL;
	}

	SPPoint point = (SPPoint)malloc(sizeof(*point));
	if (point == NULL){
		return NULL;
	}

	point->data = (double*)malloc(sizeof(double)*dim);
	if (point->data == NULL){
		free(point);
		return NULL;
	}

	int i;
	for (i = 0; i < dim ; i++){
		*(point->data+i) = *(data+i);
	}

	point->index = index;
	point->dim = dim;
	return point;
}

SPPoint spPointCopy(SPPoint source){

	assert(source != NULL);

	SPPoint copiedpoint = spPointCreate(source->data, source->dim, source->index);
	return copiedpoint;
}

void spPointDestroy(SPPoint point){

	if (point != NULL){
		free(point->data);
		free(point);
	}
}

int spPointGetDimension(SPPoint point){

	assert(point != NULL);
	return point->dim;
}

int spPointGetIndex(SPPoint point){

	assert(point != NULL);
	return point->index;
}

double spPointGetAxisCoor(SPPoint point, int axis){

	assert(point != NULL);
	assert(axis < point->dim);
	return point->data[axis];
}

double spPointL2SquaredDistance(SPPoint p, SPPoint q){

	assert(p != NULL);
	assert(q != NULL);
	assert(p->dim == q->dim);

	double Sqdistance = 0;
	int i;
	for (i = 0; i < p->dim; i++){
		Sqdistance += (((p->data[i])-(q->data[i])) * ((p->data[i])-(q->data[i])));
	}

	return Sqdistance;
}

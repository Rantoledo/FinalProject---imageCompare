/*
 * KD-tree.c
 *
 *  Created on: 2 баев 2016
 *      Author: E5430
*/

#include "SPPoint.h"
#include "KD-tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SPBPriorityQueue.h"

#include "SPConfig.h"


 struct thetuple{
	double data[2];
};

struct kd_array{
	int** Matt;
	int size;
	int dim;
	SPPoint* sppointarr;
};

int getTuplex(Tuple tup){
	return tup.data[0];
}
double getTupley(Tuple tup){
	return tup.data[1];
}
int** kdArraygetMatt(SPKDArray kdarr){
	if (kdarr == NULL){
		return NULL;
	}
	return kdarr->Matt;
}
int kdArraygetSize(SPKDArray kdarr){
	if (kdarr == NULL){
		return -1;
	}
	return kdarr->size;
}
int kdArraygetDim(SPKDArray kdarr){
	if (kdarr == NULL){
		return -1;
	}
	return kdarr->dim;
}
SPPoint* kdArraygetSParray(SPKDArray kdarr){
	if (kdarr == NULL){
		return NULL;
	}
	return kdarr->sppointarr;
}

struct kd_tree_node{
	int Dim;
	double Val;
	KDTreeNode Left;
	KDTreeNode Right;
	SPPoint Data;
};

int kdNodegetDim(KDTreeNode kdnode){
	if (kdnode == NULL){
		return -1;
	}
	return kdnode->Dim;
}
double kdNodegetVal(KDTreeNode kdnode){
	if (kdnode == NULL){
		return -1;
	}
	return kdnode->Val;
}
KDTreeNode kdNodegetLeftnode(KDTreeNode kdnode){
	if (kdnode == NULL){
		return NULL;
	}
	return kdnode->Left;
}
KDTreeNode kdNodegetRightnode(KDTreeNode kdnode){
	if (kdnode == NULL){
		return NULL;
	}
	return kdnode->Right;
}
SPPoint kdNodegetSParray(KDTreeNode kdnode){
	if (kdnode == NULL){
		return NULL;
	}
	return kdnode->Data;
}

void DestroySPPointarr(SPPoint* arr, int size){

	int i;
	for (i=0 ; i < size ; i++){
		spPointDestroy(*(arr+i));
	}
	free(arr);
}

void DestroyKdarray(SPKDArray kdArray){

	if (kdArray == NULL){
		return;
	}
	int i;
	for (i = 0 ; i < kdArray->dim ; i++){
		free(*(kdArray->Matt+i));
	}
	free(kdArray->Matt);
	free(kdArray->sppointarr);
	free(kdArray);
}

int CompTuples(const void* a, const void* b) {
	const Tuple* ptr_a = a;
	const Tuple* ptr_b = b;

	double res = ptr_a->data[1] - ptr_b->data[1];
	if (res > 0){
		return 1;
	}
	else if (res < 0){
		return -1;
	}
	else if (res == 0){
		return 0;
	}
	/*
	return (int)(ptr_a->data[1] - ptr_b->data[1]);
	*/
	return 0;
}

SPKDArray Init(SPPoint* arr, int size){

	if (arr == NULL || size <= 0){return NULL;}

	SPKDArray kdarray = (SPKDArray)malloc(sizeof(*kdarray));
	if (kdarray == NULL){ return NULL;}

	kdarray->size = size;
	kdarray->dim = spPointGetDimension(arr[0]);

	// coping the sppoint array to P
	SPPoint* P = (SPPoint*)malloc(sizeof(SPPoint)*size);
	if (P == NULL){
		free(kdarray);
		return NULL;
	}

	int i,j,k;
	int Pcurrsize = 0;
	for (i=0 ; i < size ; i++){
		*(P+i) = spPointCopy(*(arr+i));
		if(*(P+i) == NULL){
			DestroySPPointarr(P, Pcurrsize);
			free(kdarray);
			return NULL;
		}
		Pcurrsize++;
	}

	kdarray->sppointarr = P;

	// creating the Matrix
	int Mattdim = kdArraygetDim(kdarray);
	int** Matt = (int**)malloc(sizeof(int*)*Mattdim);
	if (Matt == NULL){
		DestroySPPointarr(P, size);
		free(kdarray);
		return NULL;
	}
	for (i=0 ; i < Mattdim ; i++){
		*(Matt+i) = (int*)malloc(sizeof(int)*size);
		if (*(Matt+i) == NULL){
			for (j=0 ; j < i ; j++){
				free(*(Matt+j));
			}
			free(Matt);
			DestroySPPointarr(P, size);
			free(kdarray);
			return NULL;
		}
	}

	// creating TupleArray for the sorting
	Tuple* tupArr = (Tuple*)malloc(sizeof(Tuple)*size);
	if (tupArr == NULL){
		free(Matt);
		DestroySPPointarr(P, size);
		free(kdarray);
		return NULL;
	}
	// sorting the values according to the ith coordinate and inserting to the Matrix
	for (j=0 ; j < Mattdim ; j++){
		for (i=0 ; i < size ; i++){
			(*(tupArr+i)).data[0] = i;
			double theAxiscoor = spPointGetAxisCoor(*(P+i), j);
			(*(tupArr+i)).data[1] = theAxiscoor;
		}

		qsort(tupArr, size, sizeof(Tuple), CompTuples);

		for (k=0 ; k < size ; k++){
			int theindexordered = (*(tupArr+k)).data[0];
			*(Matt[j]+k) = theindexordered;
		}
	}
	free(tupArr);
	kdarray->Matt = Matt;
	return kdarray;
}

int* Mapp(SPPoint* P, SPPoint* P12, int sizeofmap){

	if ( P == NULL || P12 == NULL){
		return NULL;
	}

	int* map12 = malloc(sizeof(int)*sizeofmap);
	if (map12 == NULL){
		return NULL;
	}
	int i;
	int j=0;
	for (i=0 ; i < sizeofmap ; i++){
		if ( *(P+i) == *(P12+j) ){
			*(map12+i) = j;
			j++;
		}
		else{
			*(map12+i) = -1;
		}
	}
	return map12;
}

int Middle(int kdsize){
	int res;
	if (kdsize % 2 == 0){
		res = kdsize/2;
	}
	else if (kdsize % 2 == 1){
		res = (kdsize/2)+1;
	}
	return res;
}

SPKDArray* Split(SPKDArray kdArr, int coor){

	if (kdArr == NULL || coor < 0){ return NULL;}

	int n = kdArraygetSize(kdArr);

	// finding the middle n/2 upper value
	int middle = Middle(n);

	// initialing X array
	int i;
	int Xarr[n];
	for (i=0 ; i < middle ; i++){
		int index = *(kdArr->Matt[coor]+i);
		Xarr[index] = 0;
	}
	for (i=middle ; i < n ; i++){
		int index = *(kdArr->Matt[coor]+i);
		Xarr[index] = 1;
	}

	//creating SPPoint* for the left and right kd-arrays
	SPPoint* SPPointLeft = (SPPoint*)malloc(sizeof(SPPoint)*middle);
	if (SPPointLeft == NULL){
		return NULL;
	}
	SPPoint* SPPointRight = (SPPoint*)malloc(sizeof(SPPoint)*(n-middle));
	if (SPPointRight == NULL){
		free(SPPointLeft);
		return NULL;
	}
	// pointing the relevant SPPoints from kdArr to the splited kd-arrays
	int l=0;
	int r=0;
	for (i=0 ; i < n ; i++){
		if (Xarr[i] == 0){
			*(SPPointLeft+l) = *(kdArr->sppointarr+i);
			l++;
		}
		if (Xarr[i] == 1){
			*(SPPointRight+r) = *(kdArr->sppointarr+i);
			r++;
		}
	}

	// creating map1 for left and map2 for right
	int* map1 = Mapp(kdArr->sppointarr , SPPointLeft, n);
	if (map1 == NULL){
		free(SPPointLeft);
		free(SPPointRight);
		return NULL;
	}
	int* map2 = Mapp(kdArr->sppointarr , SPPointRight, n);
	if (map2 == NULL){
		free(map1);
		free(SPPointLeft);
		free(SPPointRight);
		return NULL;
	}

	// create Matrix Matt1 (for left kdarray) and Matt2 (for right kdarray)
	int** Matt1;
	int** Matt2;
	int a,c;
	Matt1 = (int**)malloc(sizeof(int*)*kdArr->dim);
	if (Matt1 == NULL){
		free(SPPointLeft);
		free(SPPointRight);
		return NULL;
	}
	for (i=0 ; i < kdArr->dim ; i++){
		*(Matt1+i) = (int*)malloc(sizeof(int)*middle);
		if (*(Matt1+i) == NULL){
			for (a=0 ; a < i ; a++){
				free(*(Matt1+a));
			}
			free(Matt1);
			free(SPPointLeft);
			free(SPPointRight);
			return NULL;
		}
	}
	Matt2 = (int**)malloc(sizeof(int*)*kdArr->dim);
	if (Matt2 == NULL){
		for (i=0 ; i < kdArr->dim ; i++){
			free(*(Matt1+i));
		}
		free(Matt1);
		free(SPPointLeft);
		free(SPPointRight);
		return NULL;
	}
	for (i=0 ; i < kdArr->dim ; i++){
		*(Matt2+i) = (int*)malloc(sizeof(int)*(n-middle));
		if (*(Matt2+i) == NULL){
			for (a=0 ; a < i ; a++){
				free(*(Matt2+a));
			}
			free(Matt2);
			for (c=0 ; c < kdArr->dim ; c++){
				free(*(Matt1+c));
			}
			free(Matt1);
			free(SPPointLeft);
			free(SPPointRight);
			return NULL;
		}
	}
	int b;
	// fill left and right matrix
	for (i=0 ; i < kdArr->dim ; i++){
		int a1 = 0;
		int a2 = 0;
		for (b=0 ; b < n ; b++){
			int indFromMat = *(kdArr->Matt[i]+b);
			if (Xarr[indFromMat] == 0){
				int valToMat1 = map1[indFromMat];
				*(Matt1[i]+a1) = valToMat1;
				a1++;
			}
			else if (Xarr[indFromMat] == 1){
				int valToMat2 = map2[indFromMat];
				*(Matt2[i]+a2) = valToMat2;
				a2++;
			}
		}
	}
	// don't need map1 and map2 anymore
	free(map1);
	free(map2);

	// creating left and right kd-arrays
	SPKDArray kdLeft = (SPKDArray)malloc(sizeof(*kdLeft));
	if (kdLeft == NULL){
		for (i=0 ; i < kdArr->dim ; i++){
			free(*(Matt1+i));
			free(*(Matt2+i));
		}
		free(Matt1);
		free(Matt2);
		free(SPPointLeft);
		free(SPPointRight);
		return NULL;
	}
	SPKDArray kdRight = (SPKDArray)malloc(sizeof(*kdRight));
	if (kdRight == NULL){
		for (i=0 ; i < kdArr->dim ; i++){
			free(*(Matt1+i));
			free(*(Matt2+i));
		}
		free(Matt1);
		free(Matt2);
		free(SPPointLeft);
		free(SPPointRight);
		free(kdLeft);
		return NULL;
	}
	kdLeft->dim = kdArraygetDim(kdArr);
	kdLeft->size = middle;
	kdLeft->sppointarr = SPPointLeft;
	kdLeft->Matt = Matt1;

	kdRight->dim = kdArraygetDim(kdArr);
	kdRight->size = n-middle;
	kdRight->sppointarr = SPPointRight;
	kdRight->Matt = Matt2;

	SPKDArray* splitedArrays = (SPKDArray*)malloc(sizeof(SPKDArray)*2);
	if (splitedArrays == NULL){
		for (i=0 ; i < kdArr->dim ; i++){
			free(*(Matt1+i));
			free(*(Matt2+i));
		}
		free(Matt1);
		free(Matt2);
		free(SPPointLeft);
		free(SPPointRight);
		free(kdLeft);
		free(kdRight);
		return NULL;
	}
	splitedArrays[0] = kdLeft;
	splitedArrays[1] = kdRight;

	return splitedArrays;
}

void DestroyNode(KDTreeNode node){

	if (node == NULL){
		return;
	}
	spPointDestroy(node->Data);
	DestroyNode(node->Left);
	DestroyNode(node->Right);
	free(node);
}


KDTreeNode NodeBuilder(int Dim, double Val, KDTreeNode Left,
		KDTreeNode Right, SPPoint Data){

	KDTreeNode resNode = (KDTreeNode)malloc(sizeof(*resNode));
	if (resNode == NULL){
		return NULL;
	}
	resNode->Dim = Dim;
	resNode->Val = Val;
	resNode->Left = Left;
	resNode->Right = Right;
	resNode->Data = Data;
	return resNode;
}

KDTreeNode ConstructKDTreeByMaxspread(SPKDArray kdArray){

	if (kdArray == NULL){
		return NULL;
	}
	if (kdArray->size == 1){
		KDTreeNode finalNode = NodeBuilder(-1,-1,NULL,NULL,*(kdArray->sppointarr));
		return finalNode;
	}

	// getting the split coordination by calculating Max_spread
	int i;
	int splitcoor;
	double currentMaxSpread;
	for (i=0; i < kdArray->dim ; i++){
		int maxSPindex = *(kdArray->Matt[i]+kdArray->size-1);
		int minSPindex = *(kdArray->Matt[i]);
		double dimSpread = (spPointGetAxisCoor(kdArray->sppointarr[maxSPindex],i))-(spPointGetAxisCoor(kdArray->sppointarr[minSPindex],i));
		if (i == 0){
			currentMaxSpread = dimSpread;
			splitcoor = 0;
		}
		else if (dimSpread > currentMaxSpread){
			currentMaxSpread = dimSpread;
			splitcoor = i;
		}
	}

	SPKDArray* LeftkdRightkd = Split(kdArray, splitcoor);
	if (LeftkdRightkd == NULL){
		DestroyKdarray(kdArray);
		return NULL;
	}

	int middle = Middle(kdArraygetSize(kdArray));
	int medianIndex = *(*(kdArray->Matt+splitcoor)+(middle-1));
	double median = spPointGetAxisCoor(*(kdArray->sppointarr+medianIndex), splitcoor);

	KDTreeNode Leftnode = ConstructKDTreeByMaxspread(LeftkdRightkd[0]);
	KDTreeNode Rightnode = ConstructKDTreeByMaxspread(LeftkdRightkd[1]);

	//free the SPKDArray* LeftkdRightkd
	DestroyKdarray(LeftkdRightkd[0]);
	DestroyKdarray(LeftkdRightkd[1]);
	free(LeftkdRightkd);

	KDTreeNode finalNode = NodeBuilder(splitcoor, median, Leftnode, Rightnode, NULL);
	if (finalNode->Left == NULL || finalNode->Right == NULL){
		DestroyNode(finalNode);
		return NULL;
	}
	return finalNode;
}

KDTreeNode ConstructKDTreeByRandom(SPKDArray kdArray){

	if (kdArray == NULL){
		return NULL;
	}
	if (kdArray->size == 1){
		KDTreeNode finalNode = NodeBuilder(-1,-1,NULL,NULL,*(kdArray->sppointarr));
		return finalNode;
	}
	// choosing randomly split coordination
	int splitcoor = rand() % kdArray->dim;

	SPKDArray* LeftkdRightkd = Split(kdArray, splitcoor);
	if (LeftkdRightkd == NULL){
		DestroyKdarray(kdArray);
		return NULL;
	}

	int middle = Middle(kdArraygetSize(kdArray));

	int medianIndex = *(*(kdArray->Matt+splitcoor)+(middle-1));
	double median = spPointGetAxisCoor(*(kdArray->sppointarr+medianIndex), splitcoor);

	KDTreeNode Leftnode = ConstructKDTreeByRandom(LeftkdRightkd[0]);
	KDTreeNode Rightnode = ConstructKDTreeByRandom(LeftkdRightkd[1]);
	//free the SPKDArray* LeftkdRightkd
	DestroyKdarray(LeftkdRightkd[0]);
	DestroyKdarray(LeftkdRightkd[1]);
	free(LeftkdRightkd);

	KDTreeNode finalNode = NodeBuilder(splitcoor, median, Leftnode, Rightnode, NULL);
	if (finalNode->Left == NULL || finalNode->Right == NULL){
		DestroyNode(finalNode);
		return NULL;
	}
	return finalNode;
}

KDTreeNode ConstructKDTreeByIncremental(SPKDArray kdArray){

	if (kdArray == NULL){
		return NULL;
	}
	if (kdArray->size == 1){
		KDTreeNode finalNode = NodeBuilder(-1,-1,NULL,NULL,*(kdArray->sppointarr));
		return finalNode;
	}

	static int splitcoor = -1;
	splitcoor = (splitcoor+1) % kdArray->dim;

	SPKDArray* LeftkdRightkd = Split(kdArray, splitcoor);
	if (LeftkdRightkd == NULL){
		DestroyKdarray(kdArray);
		return NULL;
	}

	int middle = Middle(kdArraygetSize(kdArray));
	int medianIndex = *(*(kdArray->Matt+splitcoor)+(middle-1));
	double median = spPointGetAxisCoor(*(kdArray->sppointarr+medianIndex), splitcoor);

	KDTreeNode Leftnode = ConstructKDTreeByIncremental(LeftkdRightkd[0]);
	KDTreeNode Rightnode = ConstructKDTreeByIncremental(LeftkdRightkd[1]);

	//free the SPKDArray* LeftkdRightkd
	DestroyKdarray(LeftkdRightkd[0]);
	DestroyKdarray(LeftkdRightkd[1]);
	free(LeftkdRightkd);

	KDTreeNode finalNode = NodeBuilder(splitcoor, median, Leftnode, Rightnode, NULL);
	if (finalNode->Left == NULL || finalNode->Right == NULL){
		DestroyNode(finalNode);
		return NULL;
	}
	return finalNode;
}


void kNearestNeighbors(KDTreeNode currnode, SPBPQueue bpq, SPPoint P){

	if (currnode == NULL){
		return;
	}
	if (currnode->Dim == -1){
		double distance = spPointL2SquaredDistance(currnode->Data, P);
		SPListElement element = spListElementCreate(spPointGetIndex(currnode->Data), distance);
		spBPQueueEnqueue(bpq, element);
		spListElementDestroy(element);
		return;
	}
	SPListElement Elm;
	double DataOfP = spPointGetAxisCoor(P, kdNodegetDim(currnode));
	if (DataOfP <= currnode->Val){
		kNearestNeighbors(currnode->Left, bpq, P);
		Elm = spBPQueuePeekLast(bpq);
		double diff1 = currnode->Val - DataOfP;
		if (!spBPQueueIsFull(bpq) || ((diff1)*(diff1) < spListElementGetValue(Elm))){
			kNearestNeighbors(currnode->Right , bpq , P);
		}
		spListElementDestroy(Elm);
	}
	else {
		kNearestNeighbors(currnode->Right, bpq, P);
		Elm = spBPQueuePeekLast(bpq);
		double diff2 = currnode->Val - DataOfP;
		if (!spBPQueueIsFull(bpq) || ((diff2)*(diff2) < spListElementGetValue(Elm))){
			kNearestNeighbors(currnode->Left , bpq , P);
		}
		spListElementDestroy(Elm);
	}
}


SPBPQueue KDTreeSearch(KDTreeNode node, SPPoint p, int size){

	SPBPQueue bpq;
	bpq = spBPQueueCreate(size);
	if (bpq == NULL){
		return NULL;
	}
	kNearestNeighbors(node, bpq, p);
	return bpq;
}

KDTreeNode CreateTree(SPPoint* arr, int size, spTreeSplit* SplitMethod){

	// initialing kdArray out of the allFeatures array (arr)
	SPKDArray kdArray = Init(arr, size);

	// if Init failed
	if (kdArray == NULL){
		return NULL;
	}

	KDTreeNode treeHead;
	// MAX_SPREAD
	if (*SplitMethod == MAX_SPREAD){
		treeHead = ConstructKDTreeByMaxspread(kdArray);
	}
	// RANDOM
	else if (*SplitMethod == RANDOM){
		treeHead = ConstructKDTreeByRandom(kdArray);
	}
	// INCREMENTAL
	else if (*SplitMethod == INCREMENTAL){
		treeHead = ConstructKDTreeByIncremental(kdArray);
	}
	DestroyKdarray(kdArray);
	return treeHead;
}



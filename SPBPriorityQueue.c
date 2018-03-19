#include "SPBPriorityQueue.h"
#include "SPList.h"
#include "SPListElement.h"
#include <stdlib.h>

struct sp_bp_queue_t{
	int maxSize;
	SPList elementsList;
};

SPBPQueue spBPQueueCreate(int maxSize){
	if (maxSize<=0){
		return NULL;
	}
	struct sp_bp_queue_t *newQ = (struct	 sp_bp_queue_t*) malloc(sizeof(struct sp_bp_queue_t));
	newQ->maxSize=maxSize;
	newQ->elementsList= spListCreate();
	if (newQ->elementsList==NULL){
		return NULL;
	}
	return newQ;
}
SPBPQueue spBPQueueCopy(SPBPQueue source){
	if (source==NULL){
		return NULL;
	}
	SPBPQueue newQ=spBPQueueCreate(1);
	newQ->maxSize=source->maxSize;
	newQ->elementsList=spListCopy(source->elementsList);
	if (newQ->elementsList==NULL){
		return NULL;
	}
	return newQ;
}
void spBPQueueClear(SPBPQueue source){
	if (source!=NULL){
		spListClear(source->elementsList);
}
}
void spBPQueueDestroy(SPBPQueue source){
	if (source!=NULL){
		spBPQueueClear(source);
		spListDestroy(source->elementsList);
		free(source);

}}

int spBPQueueSize(SPBPQueue source){
	if (source==NULL){
		return -1;
	}
	return spListGetSize(source->elementsList);
}
int spBPQueueGetMaxSize(SPBPQueue source){
	if (source==NULL){
		return -1;
	}
	return source->maxSize;
}
bool spBPQueueIsEmpty(SPBPQueue source){
	if (source==NULL){
		return false;
	}
	if (spBPQueueSize(source)==0){
		return true;
	}
	return false;
}
bool spBPQueueIsFull(SPBPQueue source){
	if (source==NULL){
		return false;
	}
	int size=spBPQueueSize(source);
	int maxsize=spBPQueueGetMaxSize(source);
	if (size==maxsize){
		return true;
	}
	return false;
}
SP_BPQUEUE_MSG spBPQueueEnqueue(SPBPQueue source, SPListElement element){
	SP_LIST_MSG Enqueue;
	if (source==NULL){
		return SP_BPQUEUE_INVALID_ARGUMENT;}
	SPListElement elementCompared = spListGetFirst(source->elementsList);
	if (elementCompared==NULL){
		Enqueue=spListInsertFirst(source->elementsList,element);
		if (Enqueue==SP_LIST_SUCCESS){
			return SP_BPQUEUE_SUCCESS;}
		if (Enqueue==SP_LIST_NULL_ARGUMENT){
			return SP_BPQUEUE_INVALID_ARGUMENT;}
		if (Enqueue==SP_LIST_OUT_OF_MEMORY){
			return SP_BPQUEUE_OUT_OF_MEMORY;}}
	int i=0;
	int size=spBPQueueSize(source);
	while (i<size){
		if (spListElementGetValue(elementCompared)>=spListElementGetValue(element)){
			break;}
		elementCompared=spListGetNext(source->elementsList);
		i++;}
	if (elementCompared==NULL){
		if (spBPQueueIsFull(source)){
			return SP_LIST_SUCCESS;}
		Enqueue=spListInsertLast(source->elementsList,element);}
	else{
		if (spListElementGetValue(elementCompared)==spListElementGetValue(element)){
			if (spListElementGetIndex(elementCompared)>
					spListElementGetIndex(element)){
				Enqueue = spListInsertBeforeCurrent(source->elementsList,element);}
			else{
				Enqueue = spListInsertAfterCurrent(source->elementsList,element);}}
		else if (spBPQueueIsFull(source)){
			Enqueue = spListInsertBeforeCurrent(source->elementsList,element);
			spListGetLast(source->elementsList);
			spListRemoveCurrent(source->elementsList);}
		else{
			Enqueue = spListInsertBeforeCurrent(source->elementsList,element);}}
	if (Enqueue==SP_LIST_NULL_ARGUMENT){
		return SP_BPQUEUE_INVALID_ARGUMENT;}
	if (Enqueue==SP_LIST_OUT_OF_MEMORY){
		return SP_BPQUEUE_OUT_OF_MEMORY;}
	return SP_BPQUEUE_SUCCESS;
}
SP_BPQUEUE_MSG spBPQueueDequeue(SPBPQueue source){
	SP_LIST_MSG Enqueue;
	if (source==NULL){
		return SP_BPQUEUE_INVALID_ARGUMENT;
	}
	if (spBPQueueIsEmpty(source)){
		return SP_BPQUEUE_EMPTY;
	}
	spListGetFirst(source->elementsList);
	Enqueue=spListRemoveCurrent(source->elementsList);
	if (Enqueue==SP_LIST_SUCCESS){
		return SP_BPQUEUE_SUCCESS;
	}
	if (Enqueue==SP_LIST_NULL_ARGUMENT){
		return SP_BPQUEUE_INVALID_ARGUMENT;
}
	return SP_BPQUEUE_SUCCESS;

}
SPListElement spBPQueuePeek(SPBPQueue source){
	if ((source==NULL)||(spBPQueueIsEmpty(source))){
		return NULL;
	}
		return spListElementCopy(spListGetFirst(source->elementsList));
}
SPListElement spBPQueuePeekLast(SPBPQueue source){
	if ((source==NULL)||(spBPQueueIsEmpty(source))){
		return NULL;
	}
	return spListElementCopy(spListGetLast(source->elementsList));
}
double spBPQueueMinValue(SPBPQueue source){
	if ((source==NULL)||(spBPQueueIsEmpty(source))){
		return -1;
	}
	return spListElementGetValue(spListGetFirst(source->elementsList));
}
double spBPQueueMaxValue(SPBPQueue source){
	if ((source==NULL)||(spBPQueueIsEmpty(source))){
		return -1;
	}
	return spListElementGetValue(spListGetLast(source->elementsList));
}



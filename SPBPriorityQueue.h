#ifndef SPBPRIORITYQUEUE_H_
#define SPBPRIORITYQUEUE_H_
#include "SPListElement.h"
#include <stdbool.h>
#include "SPList.h"
/**
 * SP Bounded Priority Queue summary
 *
 * TODO Complete documentation
 */

/** type used to define Bounded priority queue **/
typedef struct sp_bp_queue_t* SPBPQueue;

/** type for error reporting **/
typedef enum sp_bp_queue_msg_t {
	SP_BPQUEUE_OUT_OF_MEMORY,
	SP_BPQUEUE_FULL,
	SP_BPQUEUE_EMPTY,
	SP_BPQUEUE_INVALID_ARGUMENT,
	SP_BPQUEUE_SUCCESS
} SP_BPQUEUE_MSG;

/**
 * Allocates a new Queue.
 *
 * This function creates a new empty Queue.
 * @param maxSize the maximum number of elements in the new queue.
 * @return
 * 	NULL - If allocations failed or if maxSize<=0 or if maxSize is NULL
 * 	A new Queue in case of success.
 */
SPBPQueue spBPQueueCreate(int maxSize);

/**
 * Creates a copy of target queue.
 *
 * The new copy will contain all the elements from the source queue in the same
 * order. The internal iterator for both the new copy and the target queue will not be
 * defined afterwards.
 *
 * @param source The target queue to copy
 * @return
 * NULL if a NULL was sent or a memory allocation failed.
 * A queue containing the same elements with same order as list otherwise.
 */
SPBPQueue spBPQueueCopy(SPBPQueue source);
/**
 * queueDestroy: Deallocates an existing queue. Clears all elements by using the
 * stored free function.
 *
 * @param source Target queue to be deallocated. If queue is NULL nothing will be
 * done
 */

void spBPQueueDestroy(SPBPQueue source);

/**
 * Removes all elements from target queue. The state of the current element will not be defined afterwards.
 *
 * The elements are deallocated using the stored freeing function
 * @param source Target queue to remove all element from. If queue is NULL nothing will be
 * done
 */
void spBPQueueClear(SPBPQueue source);

/**
 * Returns the number of elements in the queue. the iterator state will not change.
 *
 * @param source The target queue which size is requested.
 * @return
 * -1 if a NULL pointer was sent.
 * Otherwise the number of elements in the source.
 */
int spBPQueueSize(SPBPQueue source);

/**
 * Returns the maximum number of elements that can be stored in the queue.
 *
 * @param source The target queue which max size is requested.
 * @return
 * -1 if a NULL pointer was sent.
 * Otherwise the maximum number of elements in the source.
 */
int spBPQueueGetMaxSize(SPBPQueue source);
/**
 * Adds a new element to the queue, a new copy of the elements will be entered to the queue,
 * in it's right position as the queue is sorted in an ascending order.
 *
 * @param source The queue for which to add an element in its end
 * @param element The element to insert. A copy of the element will be
 * inserted
 * @return
 * SP_BPQUEUE_INVALID_ARGUMENT if a NULL was sent as queue
 * SP_BPQUEUE_OUT_OF_MEMORY if an allocation failed
 * SP_BPQUEUE_FULL if the queue has reached its maximum size
 * SP_BPQUEUE_SUCCESS the element has been inserted successfully
 */
SP_BPQUEUE_MSG spBPQueueEnqueue(SPBPQueue source, SPListElement element);

/**
 * Removes the minimum valued element of the queue using the stored freeing
 * function. The state of the current element will not be defined afterwards.
 *
 * @param source The queue for which the current element will be removed
 * @return
 * SP_BPQUEUE_INVALID_ARGUMENT if queue is NULL
 * SP_BPQUEUE_EMPTY if the queue is empty
 * SP_LIST_SUCCESS the min element was removed successfully
 */
SP_BPQUEUE_MSG spBPQueueDequeue(SPBPQueue source);

/**
 * retrieves a copy of the min element in the queue.
 * @param source The queue for which to retrieve the min element's copy from
 * @return
 * SP_BPQUEUE_INVALID_ARGUMENT is a NULL pointer was sent
 * SP_BPQUEUE_EMPTY if the queue is empty.
 * A copy of the min element from the queue otherwise
 */
SPListElement spBPQueuePeek(SPBPQueue source);

/**
 * retrieves a copy of the max element in the queue.
 * @param source The queue for which to retrieve the max element's copy from
 * @return
 * NULL if a NULL pointer was sent or if the queue is empty.
 * A copy of the max element from the queue otherwise
 */
SPListElement spBPQueuePeekLast(SPBPQueue source);

/**
 * retrieves the min element's value in the queue.
 * @param source The queue for which to retrieve the min element's value from
 * @return
 * -1 if a NULL pointer was sent or if the queue is empty.
 * The min element's value from the queue otherwise
 */
double spBPQueueMinValue(SPBPQueue source);

/**
 * retrieves the max element's value in the queue.
 * @param source The queue for which to retrieve the max element's value from
 * @return
 * -1 if a NULL pointer was sent or if the queue is empty.
 * The max element's value from the queue otherwise
 */
double spBPQueueMaxValue(SPBPQueue source);

/**
 * Retreieves true if the queue is empty, and false otherwise.
 * @param source the queue checked.
 * @return
 * true if the queue exists and empty
 * false if the queue is not empty or it doesnt exist.
 */
bool spBPQueueIsEmpty(SPBPQueue source);

/**
 * Retreieves true if the queue is full, and false otherwise.
 * @param source the queue checked.
 * @return
 * true if the queue exists and full
 * false if the queue is not full or it doesnt exist.
 */
bool spBPQueueIsFull(SPBPQueue source);
SPList getList(SPBPQueue source);

#endif

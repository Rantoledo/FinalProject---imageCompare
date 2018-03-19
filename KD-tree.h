/*
 * KD-tree.h
 *
 *  Created on: 31 баев 2016
 *      Author: E5430
 */

#ifndef KD_TREE_H_
#define KD_TREE_H_
#include "SPBPriorityQueue.h"
#include "SPPoint.h"
#include "SPConfig.h"
#include "SPHelpFunctions.h"

typedef struct kd_array* SPKDArray;
typedef struct kd_tree_node* KDTreeNode;
typedef struct thetuple Tuple;

/*
 * getter for fields of SPKDArray
 */
int** kdArraygetMatt(SPKDArray kdarr);
int kdArraygetSize(SPKDArray kdarr);
int kdArraygetDim(SPKDArray kdarr);
SPPoint* kdArraygetSParray(SPKDArray kdarr);

/*
 * getter fir fields of KDNode
 */
int kdNodegetDim(KDTreeNode kdnode);
double kdNodegetVal(KDTreeNode kdnode);
KDTreeNode kdNodegetLeftnode(KDTreeNode kdnode);
KDTreeNode kdNodegetRightnode(KDTreeNode kdnode);
SPPoint kdNodegetSParray(KDTreeNode kdnode);

/*
 * compare function between two tuples, used by qsort at Split
 * this funtion get two Tuples, and compare them by their value at data[i]
 * (data[] is a field of a Tuple)
 */
int CompTuples(const void* a, const void* b);

/*
 * this function Destroys a SPPoints array
 * the function gets a point to a SPPoint array and its size
 * and destroys all the SPPoint that are in the array and the array itself
 */
void DestroySPPointarr(SPPoint* arr, int size);

/*
 * this function Destroys a SPKDArray
 * the function gets a SPKDArray and destroys it's fields that are allocated
 * (Matt, SPPoint*)
 * note: this function doesn't free the SPPoint themselves, only the SPPoint array itself.
 */
void DestroyKdarray(SPKDArray kdArray);

/*
 * this function destryos a KDTree
 * the function gets the head of the tree and recursively destroy all the nodes and its fields
 * destroys also the leaf's data (SPPoint)
 */
void DestroyNode(KDTreeNode node);

/*
 * this function initialize a SPKDArray and it's fields
 */
SPKDArray Init(SPPoint* arr,int size);

/*
 * this function Split an existing SKPDArray
 * the function gets a SPKDArray and a Split coordination
 * the function gives an array of two SPKDArray, left SPKDarray at place 0 and right SPKDArray at place 1
 */
SPKDArray* Split(SPKDArray kdArr, int coor);

/*
 * this function gets two arrays of SPPoints and size,
 * the function maps the two SPPoint arrays to one int array used by Split function
 */
int* Mapp(SPPoint* P, SPPoint* P12, int sizeofmap);

/*
 * this function gets the SPKDArray's SPPoints* size and returns the upper value of size/2
 */
int Middle(int kdsize);

/*
 * this function allocated and returns a new KDTreeNode
 * the function gets all the necessary fields and creates a new KDTreeNode
 */
KDTreeNode NodeBuilder(int Dim, double Val, KDTreeNode Left,
		KDTreeNode Right, SPPoint Data);

/*
 * this function construct a new KDTree with MAX_SPREAD method
 * the fucntion get a SPKDArray and return a KDTreeNode which is the head Node for a KDTree
 */
KDTreeNode ConstructKDTreeByMaxspread(SPKDArray kdArray);

/*
 * this function construct a new KDTree with Random method
 * the fucntion get a SPKDArray and return a KDTreeNode which is the head Node for a KDTree
 */
KDTreeNode ConstructKDTreeByRandom(SPKDArray kdArray);

/*
 * this function construct a new KDTree with Incremental method
 * the fucntion get a SPKDArray and return a KDTreeNode which is the head Node for a KDTree
 */
KDTreeNode ConstructKDTreeByIncremental(SPKDArray kdArray);

/*
 * this function creates a KDTree
 * the function gets SPPoint array, it's size and a split method from the config file
 * first the function initialize SPKDArray with Init and build the KDTree by calling the right construction
 * function according to the split method
 * finally the funciton destroy the SPKDArray and returns a KDTreeNode which is the head Node for a KDTree
 */
KDTreeNode CreateTree(SPPoint* arr, int size, spTreeSplit* SplitMethod);

/*
 * this function gets a SPPoint, SPBPQueue and the head node of KDTree
 * the function recursively search for the closest SPPoints in the KDTree for SPPoint P
 * the function Enqueue the best matches indexes to the bpq
 */
void kNearestNeighbors(KDTreeNode curr, SPBPQueue bpq, SPPoint P);

/*
 * this function gets a KDTree head node, SPPoint and size
 * the function creates a SPBPQueue bpq (it's size donated bye int size)
 * and returns it after running KNearestNeighbors on it with node and the SPPoint P
 */
SPBPQueue KDTreeSearch(KDTreeNode node, SPPoint p, int size);

#endif /* KD_TREE_H_ */

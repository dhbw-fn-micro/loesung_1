#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <Windows.h>

#define MAX_LINE_BUFFER  256
#define MAX_TEXT_LINES 1024 

static uint64_t result[MAX_TEXT_LINES];
static int32_t operands_a[MAX_TEXT_LINES];
static int32_t operands_b[MAX_TEXT_LINES];

typedef struct statistics 
{
	uint32_t min_operand_a;
	uint32_t max_operand_a;
	uint32_t min_operand_b;
	uint32_t max_operand_b;
	uint32_t avg_operand_a;
	uint32_t avg_operand_b;
	uint32_t sum_operand_a;
	uint32_t sum_operand_b;
	uint32_t counter;
}statistics_t;

/**
 * @struct listNode 
 * @brief This struct defines a list element or
 *        somethimes called a list node.
 */
typedef struct listNode 
{
	/**@brief Pointer to previous Element */
	struct listNode *pPrev;
	/**@brief Pointer to next Element */
	struct listNode *pNext;
	/**@brief Operant A for the MAC Operation */
	uint32_t operand_a;
	/**@brief Operant B for the MAC Operation */
	uint32_t operand_b;
	/**@brief Result the MAC Operation */
	uint64_t result;
} listNode_t ;

typedef struct listNodeMem 
{
	listNode_t node;
	uint32_t inUse;
} listNodeMem_t;

#define STATIC_MEM 1 /* use static memory pool instead of malloc/free*/
#define MEM_POOL_SIZE 124 /* memory pool size */

/** @brief the static memory pool itself */
listNodeMem_t list_node_mem_pool[MEM_POOL_SIZE];
/**
 * @struct doubleLinkedList 
 * @brief Helper struct to hold the head and Tail of the list
 */
typedef struct doubleLinkedList 
{
	/** @brief Pointer to the head of the list. NULL if list is empty. */
	listNode_t *headOfList;
	/** @brief Pointer to the tail of the list. NULL if list is empty. */
	listNode_t *tailOfList;
}doubleLinkedList_t;

void calculate_statistics(statistics_t * stat,uint32_t operand_a,uint32_t operand_b);
/**
 * @brief create a new list Element and setup the initial values
 * 
 * @param [in] operand_a The operand a for the MAC operation
 * @param [in] operand_b The operand b for the MAC operation
 * @param [in] result The result of the MAC operation
 * @result he new element or NULL in case of error
 */
listNode_t* list_get_new_element(uint32_t operand_a,uint32_t operand_b,uint64_t result);

/**
 * @brief free a list Node this returns the memory to the os
 * 
 * @param elem [in] Pointer to a list node
 */
void list_free_element(listNode_t* elem);

/**
 * @brief insert element before another one
 * 
 * @param list [in] The list where the element should be linked in
 * @param old [in] The element where to insert in front of.
 * @param elem [in] The element to be added
 * @return EXIT_SUCCESS in case of success otherwise EXIT_FAILURE
 */
int list_insert_before(doubleLinkedList_t *list , listNode_t* old ,listNode_t* elem);

/**
 * @brief insert element after another one
 * 
 * @param list [in] The list where the element should be linked in
 * @param old [in] The element where to insert after.
 * @param elem [in] The element to be added
 * @return EXIT_SUCCESS in case of success otherwise EXIT_FAILURE
 */
int list_insert_after(doubleLinkedList_t *list , listNode_t* old ,listNode_t* elem);

/**
 * @brief Add element to the beginning of the list.
 * 
 * @param list [inout] list where element should be appended to.
 * @param elem [in] element to be appended to the list
 * @return EXIT_SUCCESS in case of success
 */
int list_push_front(doubleLinkedList_t *list , listNode_t* elem);

/**
 * @brief Add element to the end of the list.
 * 
 * @param list [inout] list where element should be appended to.
 * @param elem [in] element to be appended to the list
 * @return EXIT_SUCCESS in case of success
 */
int list_push_back(doubleLinkedList_t *list, listNode_t* elem);


/**
 * @brief Calculates S_n = S_n-1 + A * B
 * 
 * @param operand_a [in] Operand A
 * @param operand_b [in] Operand B
 * @param pre_result [in] Previous result (S_n-1)
 * 
 * @return result of the operation.
 */
uint64_t do_mac_operation(int32_t operand_a,uint32_t operand_b,uint64_t prev_result);

/**
 * @brief initilaize the memory pool 
 * 
 * @param pool [inout] pool to be initialized 
 * @param size [in] size of pool
 * @return EXIT_SUCCESS on success
 */ 
uint32_t init_list_node_mem_pool(listNodeMem_t *pool, uint32_t size);
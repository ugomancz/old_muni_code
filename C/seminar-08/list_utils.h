#ifndef LIST_UTILS_H
#define LIST_UTILS_H

/**
 * \file   list_utils.h
 * \author ...
 */

#include <stdbool.h>
#include "list.h"

//-----------------------------------------------------------------------------
//  Types
//-----------------------------------------------------------------------------

/**
 * \brief Predicate.
 */
typedef bool (*predicate)(const void*);

/**
 * \brief Comparator.
 *
 * Let a1 &lt; a2 denote that argument 1 should be before argument 2 in the
 * ordering implemented by this function; then the comparator returns number
 * <ul>
 *     <li> &lt; 0 if a1 &lt; a2</li>
 *     <li> &gt; 0 if a1 &gt; a2</li>
 *     <li> 0 otherwise </li>
 * </ul>
 */
typedef int (*comparator)(const void*, const void*);

/**
 * \brief Action.
 */
typedef void (*action)(void*);

//-----------------------------------------------------------------------------
//  List predicates
//-----------------------------------------------------------------------------

/**
 * \brief Returns \c true if at least one element satisfies the predicate \p p.
 *
 * \param p         the predicate
 *
 * \note In empty list there is no element that satisfies \p p.
 */
bool listAny(const struct list *list, predicate p);

/**
 * \brief Returns \c false if at least one element does not satisfy
 * the predicate \p p.
 *
 * \param p         the predicate
 *
 * \note In empty list there is no element that does not satisfy \p p.
 */
bool listAll(const struct list *list, predicate p);

//-----------------------------------------------------------------------------
//  Index-based functions
//-----------------------------------------------------------------------------

/**
 * \brief Inserts a new element at position specified by \p index from the head.
 *
 * The original element at the specified index will be moved after the new one.
 *
 * \param index     distance from list's head
 * \param data      pointer to memory containing the element
 *
 * \note If \p index is \c listSize(&list), then the new element
 * will be pushed back after the tail.
 *
 * \return \c true if the operation was successful
 */
bool listInsert(struct list *list, size_t index, void *data);

/**
 * \brief Returns an unmodifiable pointer to the element at the position
 * \p index or \c NULL if no such element exists.
 *
 * \param index     distance from list's head
 * \return Element or \c NULL if not found.
 */
const void *listGet(const struct list *list, size_t index);

/**
 * \brief Finds the first index of the specified element in the list.
 *
 * \param data      the element to search
 * \return Index in the list or -1 if not found.
 */
int listGetIndex(const struct list *list, const void *data);

/**
 * \brief Removes the element at position \p index.
 *
 * If \p data is not null, value from the discarded element will be copied
 * to memory pointed to by \p data.
 *
 * \param index     distance from list's head
 * \return \c true if an element was removed, \c false otherwise
 */
bool listRemove(struct list *list, size_t index, void *data);

//-----------------------------------------------------------------------------
//  Search functions
//-----------------------------------------------------------------------------

/**
 * Returns the the first element that satisfies predicate \p p
 * or \c NULL if no such element exists.
 *
 * \param p         the predicate
 */
const void *listFindFirst(const struct list *list, predicate p);

/**
 * Returns the the last element that satisfies predicate \p p
 * or \c NULL if no such element exists.
 *
 * \param p         the predicate
 */
const void *listFindLast(const struct list *list, predicate p);

//-----------------------------------------------------------------------------
//  Enumeration
//-----------------------------------------------------------------------------

/**
 * \brief Calls function \p f on each element from head to tail.
 *
 * \param list  the list
 * \param f     the function to call
 */
void listForEach(struct list *list, action f);

/**
 * \brief Calls function \p f on each element from tail to head.
 *
 * \param list  the list
 * \param f     the function to call
 */
void listForEachReverse(struct list *list, action f);

//-----------------------------------------------------------------------------
//  Sorting
//-----------------------------------------------------------------------------

/**
 * \brief Sorts all elements in the list using \p cmp comparator.
 *
 * \param list  the list
 * \param cmp   the comparator
 */
void listSort(struct list *list, comparator cmp);

#endif // LIST_UTILS_H

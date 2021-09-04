//
// Created by Peter Stanko on 15.2.16.
//

#ifndef DYNAMIC_LIB_H
#define DYNAMIC_LIB_H

#include <stddef.h>

/**
 * Copies string and returns pointer to new string
 *
 * @param str - original string
 * @return New string allocated by malloc
 */
char *dynamicStringCopy(const char *str);

/**
 * Joins both strings into one
 *
 * @param pre - First string
 * @param post - Second string
 * @return New string
 */
char *dynamicStringJoin(const char *pre, const char *post);

/**
 * Reads full line from standard input (stdin)
 *
 * @return Whole line
 */
char *readLine();

/**
 * Allocates 2D Array for provided number of rows and cols
 *
 * @param[in] rows Number of rows for 2D array
 * @param[in] colSizes Length of the columns for each row
 */
void **dynamic2DAlloc(size_t rows, size_t colSizes[rows]);

/**
 * Frees Memory for 2D array
 *
 * @param[in] memory - memory allocated using `dynamic2DAlloc`
 * @param[in] rows - number of rows
 */
int dynamic2DFree(void **memory, size_t rows);

/*
 * -------
 * Bonuses
 * -------
 */

/**
 * Compuate the Pascal triangle and return matrix filled with values
 *
 * @param[in] depth Depth of the triangle
 */
unsigned **pascalTriangle(size_t depth);

/**
 * Implementation of dynamic split
 */
char **dynamicStringSplitSub(const char *orig, const char *splitter, size_t *size);

#endif //DYNAMIC_LIB_H

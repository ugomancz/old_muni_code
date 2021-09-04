#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "readline.h"
#include "list.h"
#include "list_utils.h"

#define UNUSED(VAR) \
    ((void) (VAR))

/**
 * Auxiliary structure to hold information about file lines.
 */
struct lineInfo
{
    int number; ///< line number
    char *text; ///< pointer to text inside line attribute
    char *line; ///< pointer to the beggining of line
                ///<    this pointer will be used to deallocate
                ///<    the line when calling freeLineInfo
};

/**
 * Compares two lineInfo strucutres according to their number.
 */
int lineInfoCmp(const void *a, const void *b)
{
    return ((const struct lineInfo*) a)->number - ((const struct lineInfo*) b)->number;
}

/**
 * Reads lines from \p in and stores them inside the list
 * as \c lineInfo structures.
 *
 * \param   list        pointer to the linked list
 * \param   in          input file
 * \return  0 on success, an arbitrary error code on failure
 */
int readLines(struct list *list, FILE *in)
{
    assert(list != NULL);
    assert(in != NULL);
    char* line;
    while ((line = readline(in)) != NULL) {
        struct lineInfo newLine;
        newLine.line = strtok(line, ":");
        newLine.text = strtok(NULL, ":");
        newLine.number = (int) strtol(line, NULL, 10);
        listPushBack(list, &newLine);
    }
    return 0;
}

/**
 * Writes lines from list to output file.
 * The lines in the list should already be sorted.
 *
 * \param   list        pointer to the linked list
 * \param   out         output file
 */
void writeLines(struct list *list, FILE *out)
{
    assert(list != NULL);
    assert(out != NULL);
    for (struct node *node = list->head; node != NULL; node = node->next) {
        fprintf(out, "%s", (((struct lineInfo*) node->data)->text));
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s INPUT OUTPUT\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    int status;
    struct list list;
    listInit(&list, sizeof(struct lineInfo));

    if ((status = readLines(&list, input)) == 0) {
        listSort(&list, &lineInfoCmp);
        writeLines(&list, output);
        status = 0;
    }

    // ‹listDestroy()› would leak memory on ‹struct listInfo›, because
    // it contains pointer to another memory block.

//  listDestroy(&list);

    // Instead we will implement our own loop:

    struct lineInfo item;
    while (listPopFront(&list, &item)) {
        // TODO: deallocate line
        free(item.line);
        // Q: Do you have to do this?
//      free(item);
    }

    // TODO: close files

    return status;
}

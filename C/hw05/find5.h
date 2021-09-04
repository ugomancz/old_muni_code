//
// Created by xkostik on 26-May-20 as part of HW05 project for PB071 course.
//

#ifndef HW05_FIND5_H
#define HW05_FIND5_H
/*
 * enum sortBy is used to represent flag defining ordering of files
 * on output
 */
typedef enum {SIZE = 's', PATH = 'f', NAME} sortBy;

/*
 * struct option represents different options and their arguments
 * entered at program run, union argument represents their arguments,
 * which can be a string or an int
 */
union argument { // union to hold options' arguments
    char *charArg;
    int intArg;
};

typedef struct { // struct to hold different options
    char name;
    union argument arg;
} opt;

/*
 * struct file represents each file found that fits the given criteria
 * it stores the file's name, path and size, because those are all the
 * file info needed to print found files in correct order
 */
typedef struct {
    char *name;
    char *path;
    long size;
} file;

/**
 * This program aims to emulate the find bash command.
 *
 * Options from input are parsed using getopt(), then file tree is walked using nftw()
 * and each found entry is parsed. If entry couldn't be read an error is printed on stderr
 * and the walk continues. If entry's depth in tree reaches the limit set by options, it's
 * subtree is skiped. Same behaviour occurs should the entry represent a hidden directory or file.
 * If entry's depth isn't greater than limit set by options, it continues the walk.
 * All found files that fit the given criteria are then printed to stdin, ordered implicitly by
 * file name or explicitly by size or path.
 */
int main(int argc, char *argv[]);

#endif //HW05_FIND5_H

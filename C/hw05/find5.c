#include "find5.h"
#include <dirent.h>
#include <errno.h>
#include <ftw.h>
#include <getopt.h>
#include <limits.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

opt options[3] = {{0},{0},{0}}; // creates an array of structs representing different options defined on program run
int optionsCounter = 0;         // indexes the above array
file **files = NULL;            // list of found files
int filesIndex = 0;             // indexes the above array
int filesSize = 0;              // total size of the above array
char lineEnd = '\n';            // specifies line ending on output
bool searchHidden = false;      // specifies whether to add hidden files to the search
int minDepth = 0;               // minimal tree depth of search
int maxDepth = INT_MAX;         // maximal tree depth of search
unsigned int userID = 0;        // represents user's ID when -u option is used
char *path = ".";               // unless declared otherwise, initial path of search is the current working directory

/**
 * Frees array of files along with all its allocated members.
 */
static void freeAll() {
    for (int i = 0; i < filesIndex; i++) { // frees all file structures
        free(files[i]->name);
        free(files[i]->path);
        free(files[i]);
    }
    free(files);
}

/**
 * Prints manual with basic usage of program's arguments
 */
static void printHelp() {
    fprintf(stderr, "usage: ./find5 [-n ATTR] [-s f|s] [-m MASK] [-u USER] "
           "[-f NUM] [-t NUM] [-a] [-0] [-h] [beginning path]\n"
           "-n ATTR \"ATTR\" is substring that returned files' names need to contain\n"
           "-s f|s sorts returned files base on path \"f\" or size \"s\", default is by name\n"
           "-m MASK returns files with specified user permissions, represented by \"MASK\" in octal\n"
           "-u USER returns files owned by \"USER\"\n"
           "-f NUM specifies minimal depth of search\n"
           "-t NUM specifies maximal depth of search\n"
           "-a adds hidden files to the search\n"
           "-0 uses '\\0' instead of '\\n' at end of lines on output\n"
           "-h help\n");
}

/**
 * Checks found files against given options, file must fit all the criteria
 * to be added to the result list of files.
 */
static int checkFile(const char *name, const struct stat *sb) {
    for (int i = 0; i < optionsCounter; i++) {
        switch (options[i].name) {
            case 'n': // checks for substrings in filename
                if (!strstr(name, options[i].arg.charArg)) { // filename doesn't include given substring
                    return EXIT_FAILURE;
                }
                break;
            case 'm': ; // checks whether file has correct permissions set
                int filePerms = (sb->st_mode & S_IRUSR) | (sb->st_mode & S_IWUSR) | (sb->st_mode & S_IXUSR) |
                                (sb->st_mode & S_IRGRP) | (sb->st_mode & S_IWGRP) | (sb->st_mode & S_IXGRP) |
                                (sb->st_mode & S_IROTH) | (sb->st_mode & S_IWOTH) | (sb->st_mode & S_IXOTH);
                if (filePerms != options[i].arg.intArg) { // file doesn't have the correct permissions
                    return EXIT_FAILURE;
                }
                break;
            case 'u': ; // checks whether file is owned by correct user
                if (userID != sb->st_uid) {
                    return EXIT_FAILURE;
                }
                break;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * Function designed for use with nftw(). Decides what to do with each entry
 * that nftw() finds along the file tree walk. If entry couldn't be read an
 * error is printed on stderr and the walk continues. If entry's depth in tree
 * reaches the limit set by options, nftw() skips it's subtree (if it has any).
 * Same behaviour occurs should the entry represent a hidden directory or file.
 * If entry's depth isn't greater than limit set by options, it continues the walk.
 *
 * Then if a regular file is found, it's checked using checkFile() and if it fits
 * it's properties are added to list of found files.
 *
 * @param fpath full path of entry
 * @param sb struct stat of entry
 * @param typeflag defines file type of entry
 * @param ftwbuf struct FTW with more info about entry
 * @return 0 to continue walk, macro FTW_SKIP_SUBTREE to skip the entry's subtree
 */
static int checkEntry(const char *fpath, const struct stat *sb,
           int typeflag, struct FTW *ftwbuf) {
    (void) typeflag; // unused -> using struct stat to determine file type for compatibility reasons
    if (errno == EACCES) { // file or directory couldn't be read
        fprintf(stderr, "Couldn't read directory or file\n");
        return EXIT_SUCCESS;
    }
    if (ftwbuf->level < minDepth) { // entry isn't at corresponding depth in the file tree
        return EXIT_SUCCESS;
    }
    if (ftwbuf->level > maxDepth || (!searchHidden && *(fpath + ftwbuf->base) == '.' && ftwbuf->base != 0)) { // file is hidden and searchHidden is set to false
        return FTW_SKIP_SUBTREE;
    }
    if (S_ISREG(sb->st_mode)) { // entry is a regular file
        if (!checkFile(fpath + ftwbuf->base, sb)) { // file fits all given criteria
            if (filesIndex >= filesSize) { // allocating more memory
                filesSize+= 50;
                file **newFiles = realloc(files, filesSize * sizeof (file *));
                if (!newFiles) { // reallocation failed
                    fprintf(stderr, "Couldn't allocate more memory\n");
                    freeAll();
                    return EXIT_FAILURE;
                }
                files = newFiles;
            }
            *(files + filesIndex) = calloc(1, sizeof (file));
            (*(files + filesIndex))->name = calloc(strlen(fpath + ftwbuf->base) + 1, sizeof (char));
            (*(files + filesIndex))->path = calloc(strlen(fpath) + 1, sizeof (char));
            strcpy((*(files + filesIndex))->name, fpath + ftwbuf->base);
            strcpy((*(files + filesIndex))->path, fpath);
            (*(files + filesIndex))->size = sb->st_size;
            ++filesIndex;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * Comparator for files. Compares them by name, case-insensitive.
 * If they have the same name, comparation of their path, case-sensitive
 * is returned.
 */
static int compareName(const void* p1, const void* p2) {
    int nameCompare = strcasecmp((*(const file **) p1)->name, (*(const file **) p2)->name); // compares names, case insensitive
    if (nameCompare == 0) {
        return strcmp((*((const file **) p1))->path, ((*(const file **) p2))->path); // compares path, case sensitive
    }
    return nameCompare;
}

/**
 * Comparator for files. Compares them by their path, case-sensitive.
 */
static int comparePath(const void* p1, const void* p2) {
    return strcmp((*((const file**) p1))->path, (*((const file**) p2))->path);
}

/**
 * Comparator for files. Compares them by their size.
 */
static int compareSize(const void* p1, const void* p2) {
    if ((*((const file**) p1))->size > (*((const file**) p2))->size) {
        return -1;
    }
    if ((*((const file**) p1))->size < (*((const file**) p2))->size) {
        return 1;
    }
    return 0;
}

static void sortFiles(sortBy *sortBy) {
    switch (*sortBy) {
        case NAME:
            qsort(files, filesIndex, sizeof (file *), compareName);
            break;
        case PATH:
            qsort(files, filesIndex, sizeof (file *), comparePath);
            break;
        case SIZE:
            qsort(files, filesIndex, sizeof (file *), compareSize);
            break;
    }
}

/**
 * Prints the found files' paths to stdin.
 */
static void output() {
    for (int i = 0; i < filesIndex; i++) {
        printf("%s%c", (*(files + i))->path, lineEnd);
    }
}

int main(int argc, char *argv[]) {
    if (argc > 16) {
        fprintf(stderr, "Too many of arguments! See help below.\n\n");
        printHelp();
        return EXIT_FAILURE;
    }
    int op;
    sortBy sortBy = NAME;
    while ((op = getopt(argc, argv, "n:s:m:u:f:t:a0h")) != -1) { // reading options from argv[]
        char *strEnd;
        switch (op) {
            case 'u': ; // sets search by username option
                struct passwd *password = getpwnam(optarg);
                if (!password) {
                    fprintf(stderr, "User doesn't exist on this system\n");
                    return EXIT_FAILURE;
                }
                userID = password->pw_uid;
                break;
            case 'n': ; // sets search by substring in file name option
                opt newOpt1 = {op, {.charArg = optarg}};
                options[optionsCounter] = newOpt1;
                ++optionsCounter;
                break;
            case 's': ; // sets explicit ordering of files on output
                if (strlen(optarg) != 1 || (optarg[0] != 's' && optarg[0] != 'f')) {
                    fprintf(stderr, "Wrong argument for -s, use -h to see help\n");
                    return EXIT_FAILURE;
                }
                sortBy = optarg[0];
                break;
            case 'm': ; // sets search by permission mask option
                opt newOpt3 = {op, {.intArg = (int) strtol(optarg, &strEnd, 8)}};
                if (strEnd == optarg) {
                    fprintf(stderr, "Wrong argument for -m, use -h to see help\n");
                    return EXIT_FAILURE;
                }
                options[optionsCounter] = newOpt3;
                ++optionsCounter;
                break;
            case 'f': ; // sets minimal depth of search in file tree
                minDepth = (int) strtol(optarg, &strEnd, 0);
                if (strEnd == optarg) {
                    fprintf(stderr, "Wrong argument for -f, use -h to see help\n");
                    return EXIT_FAILURE;
                }
                break;
            case 't': ; // sets maximum depth of search in file tree
                maxDepth = (int) strtol(optarg, &strEnd, 0);
                if (strEnd == optarg) {
                    fprintf(stderr, "Wrong argument for -t, use -h to see help\n");
                    return EXIT_FAILURE;
                }
                break;
            case 'a': // includes hidden files in search
                searchHidden = true;
                break;
            case '0': // line endings change
                lineEnd = '\0';
                break;
            case 'h': // prints help
                printHelp();
                return EXIT_SUCCESS;
            default: // wrong use of or unknown option, includes case '?'
                if (strchr("nsmuft", optopt)) {
                    fprintf(stderr, "Option -%c requires an argument, use -h to see help\n", optopt);
                    return EXIT_FAILURE;
                }
                fprintf(stderr, "Unknown argument \"-%c\", use -h to see help\n", optopt);
                return EXIT_FAILURE;
        }
    }
    if (optind + 1 == argc) { // different path than "."
        path = argv[optind];
    } else if (optind < argc) { // too many non-option arguments
        fprintf(stderr, "Too many arguments, see help below\n\n");
        printHelp();
        return EXIT_FAILURE;
    }
    DIR *dir = opendir(path);
    if (!dir) { // initial directory couldn't be opened
        fprintf(stderr, "Couldn't open root directory\n");
        return EXIT_FAILURE;
    }
    closedir(dir);
    if (nftw(path, checkEntry, 15, FTW_PHYS | FTW_ACTIONRETVAL)) { // file tree walk
        fprintf(stderr, "Error reading files\n");
        freeAll();
        return EXIT_FAILURE;
    }
    sortFiles(&sortBy); // sorts found files
    output(); // prints sorted list of files to stdin
    freeAll();
    return EXIT_SUCCESS;
}

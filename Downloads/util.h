#ifndef UTIL_H
#define UTIL_H

/*
 * Define file linked list node
 */
struct Fnode_ {
	char name[512];
	int instances;
	struct Fnode_ *next;
	struct Fnode_ *prev;
};

typedef struct Fnode_ *fnode;

fnode FILELIST;

/*
 * Define prefix tree node
 */
struct Pnode_ {
	struct Pnode_ *alphanumeric[36];
	int level;
	int instances;
	fnode filelist;
};

typedef struct Pnode_ *pnode;

/* Creates a prefix tree node */
fnode create_pnode();

/* Creates a file node with given name */
fnode create_fnode(char *term);

/* Swaps two given file nodes */
void swap(fnode fn, fnode fn2);

/* Inserts a file node into a prefix node's filelist */
void append_filelist(pnode pn, char *term);

/* Destroys a filelist given the root file node */
void destroy_filelist(fnode fn);

/* Creates a prefix tree and returns the root */
pnode create_ptree();

/* Destroys a prefix tree given the root prefix node */
void destroy_ptree(pnode pn);

/* Inserts prefix node to prefix tree */
void insert_pnode(char *word, pnode pn, char *word2);

/* PrintTree's recursive function */
void recurse_rint(pnode pn, char *word, FILE *fp);

/* Print prefix tree */
void print_ptree(pnode pn, FILE *fp);

/* Fills tree with words from an inverted index file */
void fill_ptree(FILE *fp, pnode pn, char *var);

/* Returns prefix tree index for a given letter */
int get_ptreeIndex(int b);

/* Returns alphanumeric corresponding to a given prefix tree index */
int get_alphanumeric(int b);

/* Convenient lowercase utility */
void toLower(char *term);
#endif

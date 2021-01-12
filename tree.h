#ifndef TREE_HEADER
#define TREE_HEADER

#define NUM_LETTERS ((int)26)

typedef enum {FALSE=0, TRUE=1} boolean;


typedef struct node {
    char letter; // char of that node
    long unsigned int count; // how many words ended here 
    struct node* children[NUM_LETTERS]; // child array 
} node;

// more funcs that tree's use.
// returns a pointer to that new node
node * create_node(char letter); // create a node function

void add_child_to_node(node * n,char letter); // add a child to a node 

void remove_child_of_node(node * n,char letter); // free the space that a child node took

void dealocate(node * n); // free a node from the tree 

void walk_word(node * start,char * word); // walk the word through the tree 

void print_words(node * start,  char * part); // print the words in lexicographic order (up) a to z

void print_words_reversed(node * start,  char * part);  // print words in lexicographic order (down) z to a 

#endif
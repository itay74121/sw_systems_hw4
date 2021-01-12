#include <stdio.h>
#include "tree.h"
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 30 // max size of word is 30 

int getword(char * into); // cecleration of function 

int main(int argc, char ** argv) 
{
    node start; //  root of the tree 
    start.count = 0; // set root count to 0 
    bzero(start.children,sizeof(node*)*NUM_LETTERS); // put children of the root as NULL 
    char * word = (char *) calloc(30,sizeof(char)); // create a buffer word to get input into 
    int o; 
    while(1)
    {
        o = getword(word); // store the getword return in
        if (o)
        {
            walk_word(&start,word); // walk the word all over the tree 
        }
        else
        {
            walk_word(&start,word); // walk the word over the  tree 
            break; // break the loop since this is the end
        }
        
    }
    memset(word,'\0',WORD_SIZE); // init the word buffer 
    if (argc == 2 && strlen(argv[1])==1 && argv[1][0]=='r') // if r is second argument to the program proceed 
    {
        print_words_reversed(&start,word); // print reversed
    }
    else // otherwise 
    {
        print_words(&start,word);// print default order
    }
    
    for (size_t i = 0; i < NUM_LETTERS; i++) // go over all letter and dealocate them
    {
        dealocate(start.children[i]);
    }
    free(word); // free the word buffer 
    
    return 0;
}

int getword(char * into) // implementation of getword
{
    bzero(into,WORD_SIZE); // init into to zeros 
    char c; 
    int i = 0; // set i to 0;
    while(i<WORD_SIZE) // loop as long i < 30 
    {
        if(scanf("%c",&c)!=1) // take character from stdin into c 
            return 0; // if failed return 0 
        if(c == '\n'||c== '\t' || c == ' ' || c == EOF) // if any of them is shown 
        {
            into[i]='\0'; // set to null terminator '\0'
            i++; // add one 
            break; // break the loop
        }
        if ((c>='a'&&c<='z')||(c>='A'&&c<='Z')) // 
        {
            if(c>='A'&&c<='Z')
                c+=32; // convert to lowercase 
            into[i]=c; // put in index i at into buffer 
            i++; // add one 
        }
    }
    return 1; // return 1 as everything as planned
}

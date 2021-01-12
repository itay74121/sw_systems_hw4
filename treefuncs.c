#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

// implementation of all functions in .h file

/**
 * @param letter of type char, is a letter from a to z or A to Z 
 * @return a pointer to the node created.
 */
node * create_node(char letter) // create a node 
{
    if (letter>='A' && letter <='Z') // check if letter is uppercase 
    {
        letter+=32; // if so convert it 
    }
    if(letter<'a' || letter > 'z') // check if is not a letter 
    {
        return NULL; // if so return NULL since no pointer to such node should exist 
    }
    node * nodeptr = (node *)calloc(1,sizeof(node)); // allocate memory for the node and pass it's adress to the pointer 
    nodeptr->letter = letter; // insert letter into place in memory 
    nodeptr->count=0; // initiate count to 0
    for(int i = 0; i<NUM_LETTERS;i++) // go through all of the letters and set thier pointers to null since they shouldn't point at anything 
    {
        nodeptr->children[i]=NULL; // set to null
    }
    return nodeptr;// return the pointer to that node we just created 
}
/**
 * @param n of type node*  points to a node 
 * @param letter of type char
 * @return void.
*/
void add_child_to_node(node * n,char letter)
{
    if (n == NULL) // if n is null terminate 
        return;
    int index = letter-'a'; // get index in children array 
    node * child = *(n->children+index); // take pointer 
    if (child == NULL) // check to see if null 
        n->children[index] = create_node(letter);// put pointer in the child slot 
} // add a child to a node 
/**
 * @param n pointer to a node 
 * @param letter a char 
 * @return void.
 */
void remove_child_of_node(node * n,char letter) // free the space that a child node took
{
    int i = letter-'a'; // get index of letter in child array 
    node * child = *(n->children + i); // get the child pointer 
    dealocate(child);//dealocate the child 
}

/**
 * @param n pointer to a node
 * @return void.
 */
void dealocate(node * n)
{
    if (n==NULL) // if it's null terminate 
        return;
    for(int i = 0;i <NUM_LETTERS;i++) // go over all children 
    {
        if(n->children[i]!=NULL)  // if not null 
        { 
            dealocate(n->children[i]); // dealocate that node 
        }
    }
    free(n); // free n since there are no longer any dependencies 
}


/**
 * @param start pointer to a node 
 * @param word pointer to buffer of word
 * @return void.
 */ 
void walk_word(node * start,char * word)
{
    int index = 0; // set index 
    int len = (int)strlen(word); // get the strlen 
    node * temp = start; // put start in temp so we wouldn't lose it 
    char c; 
    for(;index<len;index++) //iterate over the chars in the word
    {
        c = *(word+index); // take the char at index  into c 
        if(temp->children[c-'a']!=NULL)  // if the child coresponding to letter c is not null 
        {
            temp = temp->children[c-'a']; // proceed 
        }
        else
        {
            char c = *(word+index); //take char into c 
            add_child_to_node(temp,c); // add a child to that node with letter c 
            temp = temp->children[c-'a']; // proceed to next node 
        }
        if(index == len-1) // if this is the last character 
        {
            temp->count+=1; // add one to node we stopped at 
        }
    }
}
/**
 * print the words in lexicographic order (up) a to z
 * @param start pointer to node 
 * @param part pointer to a buffer of part of a word 
 * @return void.
*/
void print_words(node * start, char * part)
{
    if (start == NULL) // if it's null terminate 
        return;
    if(part==NULL)
        return;
    int len = (int)strlen(part); // take len of the part 
    part[len] = start->letter; // put letter of node in part index as len 
    part[len+1]=0; // put \0 at the end 
    if(start->count>0) // if the count is above 0 print what we got with the count, since it's a word in the tree 
    {
        printf("%s %ld\n",part+1,start->count); // printing 
    }
    for(int i = 0;i<NUM_LETTERS;i++) // go through all children 
    {
        if(start->children[i]!=NULL) // check if child is not null 
        {
            print_words(start->children[i],part); //  recurse upon this node 
        }
    }
    part[len]=0; // taking a step back from recursion.
}
/**
 *  print words in lexicographic order (down) z to a
 * @param start pointer to node 
 * @param part pointer to a buffer of part of a word 
 * @return void.
*/
void print_words_reversed(node * start, char * part)
{
    if (start == NULL) // if null terminate 
        return;
    if (part==NULL)
        return;
    int len = (int)strlen(part); // take len of the part 
    part[len] = start->letter; // put at len index the current node letter 
    part[len+1]=0; // put \0 to symbol end of string 
    if(start->count>0) // if count is more than 0 it's a word 
    {
        printf("%s %ld\n",part+1,start->count); // print word and count 
    }
    for(int i = NUM_LETTERS-1;i>=0;i--) // go theough all children backwards 
    {
        if(start->children[i]!=NULL) // if child is not null recurse on it
        {
            print_words_reversed(start->children[i],part); // recursion call 
        }
    }
    part[len]=0; // step back from recursion call 
}

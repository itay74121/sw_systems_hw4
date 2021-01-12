#include <stdio.h>
#include "tree.h"
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 30

int getword(char * into);

int main(int argc, char ** argv)
{
    node start;
    start.count = 0;
    bzero(start.children,sizeof(node*)*NUM_LETTERS);
    char * word = (char *) calloc(30,sizeof(char));
    int o;
    while(1)
    {
        o = getword(word);
        if (o)
        {
            walk_word(&start,word);
        }
        else
        {
            walk_word(&start,word);
            break;
        }
        
    }
    printf("check\n");
    memset(word,'\0',WORD_SIZE);
    if (argc == 2 && strlen(argv[1])==1 && argv[1][0]=='r')
    {
        print_words_reversed(&start,word);
    }
    else
    {
        print_words(&start,word);
    }
    
    
    for (size_t i = 0; i < NUM_LETTERS; i++)
    {
        dealocate(start.children[i]);
    }
    free(word);
    
    return 0;
}

int getword(char * into)
{
    bzero(into,WORD_SIZE);
    char c;
    int i = 0;
    while(i<WORD_SIZE)
    {
        if(scanf("%c",&c)!=1)
            return 0;
        if(c == '\n'||c== '\t' || c == ' ' || c == EOF)
        {
            into[i]='\0';
            i++;
            break;
        }
        if ((c>='a'&&c<='z')||(c>='A'&&c<='Z'))
        {
            into[i]=c;
            i++;
        }
    }
    return 1;
}

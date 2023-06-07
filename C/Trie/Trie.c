//Code by Aditya Poddar
//SRN PES2UG21CS036
//for any help, contact: poddar.aditya2014@gmail.com

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 26         //number of alphabets. Only considering small case characters, can be expanded to included other symbols

struct node             //structure of a node
{
    int is_word;                        //indicates if a word ends here
    struct node *branch[SIZE];          //array to move through letters
};
typedef struct node TRIENODE;

TRIENODE* getnode()             //function to allocate memory for a node and return its address
{
    TRIENODE *newNode=(TRIENODE*)malloc(sizeof(TRIENODE));          //allocates memory for the node dynamically
    for(int i=0;i<SIZE;i++)                                         //iterate over the branch array variable 
    {
        newNode->branch[i]=NULL;                                    //initialize all the array address as NULL 
    }
    newNode->is_word=0;                                             //default value of is_word is set to false for every new node
    return newNode;                                                 //returns the address of the new node created
}

TRIENODE* insert(TRIENODE *root,char word[])                        //function to add a word to trie
{
    int index,i=0;                                                  //i variable is used to keep track of index of the position of the word being added to trie
    if(root==NULL)                                                  //if first word is inserted in the trie, then root shall be NULL
    {
        root=getnode();                                             //get new root node and save address in the root variable
    }
    TRIENODE *saveroot=root;                                        //make a copy of root nodes address in another variable
    while(word[i]!='\0')                                            //iterate untill the word to be inserted is not finished
    {
        index=word[i]-'a';                                          //calculate the position where a link will be created in the branch array, converts the character to an index(0-25)
        if(root->branch[index]==NULL)                               //if a branch at that index does not exist
        {
            root->branch[index]=getnode();                          //create another node at that index position of the branch array
        }
        root=root->branch[index];                                   //move the root variable to the next node in trie
        i++;                                                        //increase the i variable to move to the next character in the word
    }
    root->is_word=1;                                                //after inserting the last node(inserting the word in trie), mark the is_word flag to 1 indicating a word ends there
    return saveroot;                                                //returns the original address of the root 
}

int isEmpty(TRIENODE * root)                                        //checks if branch array has a link or not. If links present then return 0, 1 otherwise..
{
    for(int i=0;i<SIZE;i++)                                         //iterate over the branch array 
    {
        if(root->branch[i]!=NULL)                                   //if the branch array at index i contains a link
        {
            return 0;                                               //return 0, indicating the node is not empty
        }
    }
    return 1;                                                       //if no links are found, then return 1 indicating the array is empty
}

TRIENODE* delete(TRIENODE *root,char word[],int len,int *delete_len)        //function to delete a word from trie(recursive)
{
    int index;
    if(root==NULL)                                                              //if the root is NULL means trie is empty
    {
        return root;                                                            //returns root making no changes
    }
    if((*delete_len)==len)                                                      //if length of the word is equal to delete_length variable, means we have traversed length of the word in trie tree
    {
        if(root->is_word==1)                                                    //if the current node represents a word, remove it by setting the is_word flag to 0
        {
            printf("\n Word Deleted!.. \n");
            root->is_word=0;                                                    //marking the is_word flag to 0
        }
        else                                                                    //if the word is not found in trie
        {
            printf("\n Word Not present in trie\n");
        }
        if(isEmpty(root))                                                       //after removing the word,if the node becomes empty(no other word lies on the same path, or has same prefix)
        {
            free(root);                                                         //free the space allocated to that node
            root=NULL;                                                          //as root stores dangling pointer after freeing the memory, store a NULL in root to avoid error later
        }
        return root;                                                            //return root to the previous call
    }
    index=word[(*delete_len)]-'a';                                              //convert the charater to index
    (*delete_len)++;                                                            //increment the delete_len varibale by 1
    root->branch[index]=delete(root->branch[index],word,len,delete_len);        //recursively call the delete function by passing next nodes address 
    if(isEmpty(root) && root->is_word==0)                                       //after the word has been deleted, while coming out the stack function calls, check if the previous nodes contain any data
    {                                                                           //if the node does not represent a word and the branch array is empty(word till there is not the prefix of another word in trie)
        free(root);                                                             //free the space allocated to that node
        root=NULL;                                                              //as root stores dangling pointer after freeing the memory, store a NULL in root to avoid error later
    }
    return root;                                                                //returns root address to the previous call                                                                
}



int search(TRIENODE *root,char word[],int len)          //function to search for a word in trie
{
    for(int i=0;i<len;i++)                              //iterate till length of the word
    {
        if(root->branch[word[i]-'a']==NULL)             //if the branch relative to the index of the character does not exist
        {
            return 0;                                   //returns 0, indicating that word is not present
        }
        root=root->branch[word[i]-'a'];
    }
    if(root->is_word==1)                                //after traversing the trie till word length, if is_word flag is set to 1
    {
        return 1;                                       //returns 1, indicating that word is present                  
    }
    else                                                //if is_word flag is set to 0
    {
        return 0;                                      //returns 0, indicating that word is not present
    }
}



void print(TRIENODE *root,int *plen,char pword[])           //function to print all the words inserted in trie
{
    if(root==NULL)                                          //if the trie is empty, then root is NULL
    {
        return;                                             //comes out of the function
    }
    if(root->is_word==1)                                    //if the particlar node represents a word, then print the word
    {
        printf("\n");                       
        for(int j=0;j<(*plen);j++)                          //size of the word is given by (*plen)
        {
            printf("%c",pword[j]);                          //print the word character by character
        }
        printf("\n");
    }
    for(int i=0;i<SIZE;i++)                                 //iterate over the branch array
    {
        if(root->branch[i]!=NULL)                           //if the array contains a link, i.e. a character
        {
            pword[(*plen)++]=i+'a';                         //add the character to the pword list
            print(root->branch[i],plen,pword);              //recursively call the print fuction passing the address of the linked node
            (*plen)--;                                      //after that particular link has been explored, remove that word and continue to explore the rest of the branch array
        }
    }
}

void prefix(TRIENODE *root,char word[],int len,int *plen,char pword[])          //function to print words having a common prefix
{
    for(int i=0;i<len;i++)                                          //iterate and go down the trie till the word length
    {
        if(root->branch[word[i]-'a']==NULL)                         //if at any character index the link in branch array is NULL, that means the prefix itself does not exist in the trie
        {
            printf("\n Not Found");                                 //print no words with that prefix found
            return;                                                 //control comes out of the function
        }
        root=root->branch[word[i]-'a'];                             //if link is found in that character index, follow the links
    }
    if(isEmpty(root))                                               //after traversing the trie till the prefix length, if the node is empty then there are no words having that prefix
    {
        printf("\n No words to display");                           //print no words with that prefix found
        return;                                                     //control comes out of the function
    }
    else                                                            //if the node has links, i.e there exist words having the prefix
    {
        if(root->is_word==1)                                        //if the prefix itself is a word
        {
            printf("\n %s\n",word);                                   //print the prefix
        }
        (*plen)=len;                                                //plen is made equal to length of the prefix so that the prefix is printed along with other characters when the print function is called. This way the whole word is printed.                       
        print(root,plen,word);                                      //call print function pasing the present nodes address as root address so it prints all words present in trie starting from that node
    }
}



int main()
{
    TRIENODE *root=NULL;
    int ch,src;
    char word[20];
    do
    {
        int plen=0;
        char pword[20];
        printf("\n Enter 1:Insert 2:Delete 3:Search 4:Search_Prefix 5:Print 6:Exit :: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:printf("\n Enter word to insert : ");
                    scanf("%s",word);
                    root=insert(root,word);
                    break;
            case 2:if(root==NULL)
                    {
                        printf("\n Add words to trie first!..\n");
                    }
                    else
                    {
                        printf("\n Enter word to delete : ");
                        scanf("%s",word);
                        int delete_len=0;
                        root=delete(root,word,strlen(word),&delete_len);
                    }
                    break;
            case 3:if(root==NULL)
                    {
                        printf("\n Add words to trie first!..\n");
                    }
                    else
                    {
                        printf("\n Enter word to search: ");
                        scanf("%s",word);
                        src=search(root,word,strlen(word));
                        if(src==1)
                        {
                            printf("\n Word Found!.. \n");
                        }
                        else
                        {
                            printf("\n Word not found!.. \n");
                        }
                    }
                    break;
            case 4:if(root==NULL)
                    {
                        printf("\n Add words to trie first!..\n");
                    }
                    else
                    {
                        printf("\n Enter prefix word to search : ");
                        scanf("%s",word);
                        prefix(root,word,strlen(word),&plen,pword);
                    }
                    break;
            case 5:if(root==NULL)
                    {
                        printf("\n Add words to trie first!..\n");
                    }
                    else
                    {
                        print(root,&plen,pword);
                    }
                    break;
            case 6:printf("\n EXITING... \n");
                    break;
            default:printf("\n Wrong Input. Please try again.. \n");
                    break;
        }
    }while(ch!=6);
    printf("\n -----------------------------------------------------------------");
    return 1;
}
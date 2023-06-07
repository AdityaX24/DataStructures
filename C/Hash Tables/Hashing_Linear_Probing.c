//Code by Aditya Poddar
//SRN PES2UG21CS036
//for any help, contact: poddar.aditya2014@gmail.com

#include<stdio.h>
#include<stdlib.h>

//Hash table is a special data structure that can help us reduce the search time complexity to O(1)!

#define SIZE 1000       //max size of hash table. Can be changed according to the user

struct node             //structure to store the values. can also be implemented using two simple arrays of the same size
{
    int data;           //strores the actual data values
    int used;           //flag variable indicating if the place stores an actual data(0 means not occupied, 1 means ocupied)
};
typedef struct node NODE;

void init_hash_table(NODE *ht,int *n,int size)      //to initialize (or reinitialize) the hash table
{   
    (*n)=0;                                         //set the number of used spaces in hash table to 0
    for(int i=0;i<size;i++)
    {
        ht[i].used=0;                               //set flag field of all the places as 0, indicating not used
    }
}

int search_implicit(NODE *ht,int data,int *n,int size)      //function to search for data in hash table implicitly. Helper function to the insert function
{
    if((*n)==0)                                     //if there is no data in the hash table
    {    
        return 0;  
    }                                   
    int index=data%size;                            //finds the index position using hashing(hash value)
    int i=0;
    while(ht[index].data!=data && i!=(*n))          //iterate over the table untill data is found or we search n available items
    {
        index=(index+1)%size;                       //collision resolved using linear probing
        if(ht[index].used==1)                       //to reduce search time, increment counter everytime a legitimate data is encountered. Only search untill number of elements present. Also used as exit condition for the loop
        {
            i++;
        }
    }
    if(ht[index].data==data && ht[index].used==1)       //if the data is found and its legitimate(i.e used flag is 1)
    {    
        return 1;
    }
    else                                                //if data is not found    
    {    
        return 0;   
    }
}

void insert(NODE *ht,int data,int *n,int size)      //function to insert data to hash table
{
    if(search_implicit(ht,data,n,size)==1)          //to avoid inserting similar values in the hash table
    {
        printf("\n Data already present in the hash table!.. \n");
        return;
    }
    if(*n==size)                                    //if the hash table is already full
    {
        printf("\n Table full!.. \n");              //print hash table is full and come out of the fuction
        return;
    }
    int index=data%size;                            //if the table is not full, find the hash index
    while(ht[index].used!=0)                        //iterate untill the next free position starting from the index position is found
    {
        index=(index+1)%size;                       //resolve conflict by using Linear probing, i.e. adding 1 to index value
    }
    ht[index].data=data;                            //when the first free position is found, place the data there
    ht[index].used=1;                               //mark the place as used
    (*n)++;                                         //increase the number of used spaces by 1
}

void display(NODE *ht,int size)                     //to display the hash table
{
    for(int i=0;i<size;i++)                         //iterate over the whole hash table
    {
        printf("%d | ",i);                          //print the index value
        if(ht[i].used==1)                           //if data is present in the hash table
        {
            printf("%d \n",ht[i].data);             //print the data
        }
        else
        {
            printf("  \n");                         //otherwise print nothing
        }
        printf("----------\n");
    }
}

void search(NODE *ht,int data,int *n,int size)      //function to search for data in hash table. TIME COMPLEXITY O(1)
{
    if((*n)==0)                                     //if there is no data in the hash table
    {
        printf("\n Empty table!.. \n");             //prints hash table is empty
        return;                                     //comes out of the function
    }
    int index=data%size;                            //finds the index position using hashing(hash value)
    int i=0;
    while(ht[index].data!=data && i!=(*n))          //iterate over the table untill data is found or we search n available items
    {
        index=(index+1)%size;                       //collision resolved using linear probing
        if(ht[index].used==1)                       //to reduce search time, increment counter everytime a legitimate data is encountered. Only search untill number of elements present. Also used as exit condition for the loop
        {
            i++;
        }
    }
    if(ht[index].data==data && ht[index].used==1)       //if the data is found and its legitimate(i.e used flag is 1). The data can be inserted but deleted later which will lead to the data being found but flag value set as 0
    {
        printf("\n Data found at %d position!.. \n",index);     //print found message along with its index position in the hash table
    }
    else                                                //if data is not found
    {
        printf("\n Data not found!.. \n");                      //prints the data not found message        
    }
}

void delete(NODE *ht,int data,int *n,int size)          //to delete data from the hash table
{
    if((*n)==0)                                         //if the table has no data
    {   
        printf("\n Empty table!.. \n");                 //prints hash table is empty
        return;                                         //comes out of the function
    }
    int index=data%size;                                //finds the index position using hashing(hash value)
    int i=0;
    while(ht[index].data!=data && i!=(*n))              //iterate over the table untill data is found or we search n available items
    {
        index=(index+1)%size;                           //collision resolved using linear probing
        if(ht[index].used==1)                           //to reduce search time, increment counter everytime a legitimate data is encountered. Only search untill number of elements present. Also used as exit condition for the loop
        {   
            i++;
        }
    }
    if(ht[index].data==data && ht[index].used==1)       //if the data is found and its legitimate(i.e used flag is 1).
    {
        ht[index].used=0;                              //mark the flag variable as 0 making it unused. Hence, deleting the data
        (*n)--;                                        //reduces the number of items present in the hash table by 1
        printf("\n The data was removed successfully!.. \n");       //prompt that data has been removed from the hash table successfully
    }
    else                                                //if the data is not found (or used flag is 0).
    {
        printf("\n Data not found!.. \n");              //prompt that data is not present in the hash table
    }
}

int main()
{
    int ch,data;
    int n=0,size=0;
    NODE hash_table[SIZE];
    do
    {
        printf("\n Enter 1:Clear and Initiate Hash Table 2:Insert 3:Display 4:Search 5:Delete 6.Exit :: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:printf("\n Enter the size of the hash table: ");
                    scanf("%d",&size);
                    init_hash_table(hash_table,&n,size);            //resets the hash table and removes all element from the table
                    break;
            case 2:if(size==0)                                      //if the hash table has not been initialized yet 
                    {
                        printf("\n Initialize the table first!.. \n");
                    }
                    else
                    {
                        printf("\n Enter data: ");
                        scanf("%d",&data);
                        insert(hash_table,data,&n,size);
                    }
                    break;
            case 3:if(size==0)                                      //if the hash table has not been initialized yet
                    {
                        printf("\n Initialize the table first!.. \n");
                    }
                    else
                    {
                        display(hash_table,size);
                    }
                    break;
            case 4:if(size==0)                                      //if the hash table has not been initialized yet
                    {
                        printf("\n Initialize the table first!.. \n");
                    }
                    else
                    {
                        printf("\n Enter data to search: ");
                        scanf("%d",&data);
                        search(hash_table,data,&n,size);
                    }
                    break;
            case 5:if(size==0)                                     //if the hash table has not been initialized yet
                    {
                        printf("\n Initialize the table first!.. \n");
                    }
                    else
                    {
                        printf("\n Enter data to delete: ");
                        scanf("%d",&data);
                        delete(hash_table,data,&n,size);
                    }   
                    break;
            case 6:printf("\n EXITING.. \n");
                    break;
            default:printf("\n Wrong Input. Please try agian!.. \n");
                    break;
        }
    }while(ch!=6);
    return 1;
}
#include<stdio.h>
#include<stdlib.h>
#define SIZE 1000       //max size of hash table. Can be changed according to the user
struct node 
{
    int data;
    int used;
};
typedef struct node NODE;

void init_hash_table(NODE *ht,int *n,int size)
{
    (*n)=0;
    for(int i=0;i<size;i++)
    {
        ht[i].used=0;
    }
}

void insert(NODE *ht,int data,int *n,int size)
{
    if(*n==size)
    {
        printf("\n Table full!.. \n");
        return;
    }
    int index=data%size;
    while(ht[index].used!=0)
    {
        index=(index+1)%size;
    }
    ht[index].data=data;
    ht[index].used=1;
    (*n)++;
}

void display(NODE *ht,int size)
{
    for(int i=0;i<size;i++)
    {
        printf("%d | ",i);
        if(ht[i].used==1)
        {
            printf("%d \n",ht[i].data);
        }
        else
        {
            printf("  \n");
        }
        printf("----------\n");
    }
}

void search(NODE *ht,int data,int *n,int size)
{
    if((*n)==0)
    {
        printf("\n Empty table!.. \n");
        return;
    }
    int index=data%size;
    int i=0;
    while(ht[index].data!=data && i!=(*n))
    {
        index=(index+1)%size;
        if(ht[index].used==1)
        {
            i++;
        }
    }
    if(ht[index].data==data && ht[index].used==1)
    {
        printf("\n Data found at %d position!.. \n",index);
    }
    else
    {
        printf("\n Data not found!.. \n");
    }
}

void delete(NODE *ht,int data,int *n,int size)
{
    if((*n)==0)
    {
        printf("\n Empty table!.. \n");
        return;
    }
    int index=data%size;
    int i=0;
    while(ht[index].data!=data && i!=(*n))
    {
        index=(index+1)%size;
        if(ht[index].used==1)
        {
            i++;
        }
    }
    if(ht[index].data==data && ht[index].used==1)
    {
        ht[index].used=0;
        (*n)--;
        printf("\n The data was removed successfully!.. \n");
    }
    else
    {
        printf("\n Data not found!.. \n");
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
                    init_hash_table(hash_table,&n,size);
                    break;
            case 2:if(size==0)
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
            case 3:if(size==0)
                    {
                        printf("\n Initialize the table first!.. \n");
                    }
                    else
                    {
                        display(hash_table,size);
                    }
                    break;
            case 4:if(size==0)
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
            case 5:if(size==0)
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
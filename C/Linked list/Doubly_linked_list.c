#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *llink;
    struct node *rlink;
};
typedef struct node NODE; //giving "struct node" an alias "NODE" for easier implementation

struct list{
    NODE *head; //for storing head pointer for the boubly linked list
};
typedef struct list LIST;


//To initialize the linked list head pointer
void init(LIST *p) 
{
    p->head=NULL;
}

//To make a node with given data and return its address.
NODE * getnode(int data)
{
    NODE *temp;
    temp=(NODE *)malloc(sizeof(NODE)); //Allocates memory for the node
    temp->data=data;                   //Assigns data to data variable of the node
    temp->llink=NULL;                  //Makes the left link pointer of that node as NULL
    temp->rlink=NULL;                  //Makes the right link pointer of that node as NULL
    return temp;                       //Returns the address of that node
}

//To insert the element at the begining of the linked list
void insert_front(LIST *p,int data)
{
    NODE *newNode=getnode(data);
    if(p->head==NULL) //if list is empty, insert as first node
    {
        p->head=newNode;
    }
    else
    {
        newNode->rlink=p->head;
        p->head->llink=newNode;
        p->head=newNode;  //change head pointer if list is not empty
    }
}

//To insert the element at the end of the linked list
void insert_rear(LIST *p,int data)
{
    NODE *newNode=getnode(data);
    if(p->head==NULL)
    {
        p->head=newNode;    //if list is empty, insert as first node
    }
    else
    {
        NODE *cur;          //if list is not empty
        cur=p->head;        
        while(cur->rlink!=NULL)        //traverse to the end of the given list
        {
            cur=cur->rlink;
        }
        cur->rlink=newNode;             //make the newnode as the last node
        newNode->llink=cur;             //store the address of the previous last node as the left link of the new last node
    }
}

//To insert the element at a specific position in the linked list
void insert_at_position(LIST *p,int data,int pos)
{
    int count=0;
    if(pos==0)
    {
        insert_front(p,data);            //if position is 0 then insert as first node
    }
    else
    {
        NODE *newNode=getnode(data);
        NODE *cur=p->head;
        while(cur!=NULL && count!=pos)   //finding the node address where newnode is going to be added
        {
            cur=cur->rlink;
            count++;
        }
        if(cur==NULL)                    //if the position is more than the size of the list, then add the element as last node
        {
            insert_rear(p,data);
        }
        else                             //inserting the newnode at the specific position;
        {
            NODE *prev;
            prev=cur->llink;
            newNode->rlink=cur;         
            newNode->llink=prev;
            prev->rlink=newNode;
            cur->llink=newNode;
        }
    }
}

//To delete a node from the begining of the linked list
void delete_front(LIST *p)
{
    if(p->head==NULL)
    {
        printf("\n The list is empty!\n");
    }
    else if(p->head->rlink==NULL)
    {
        NODE *temp=p->head;
        p->head=NULL;
        printf("\n The deleted node data is %d \n",temp->data);
        free(temp);
    }
    else
    {
        NODE *temp=p->head;             //storing the address of the first node in a temporary variable.
        p->head=p->head->rlink;         //changing the head pointer to the second node
        p->head->llink=NULL;
        printf("\n The deleted node data is %d \n",temp->data);
        free(temp);                     //freeing the memory of the first node to save space. Memory optimization.
    }
}

//To delete a node from the end of the linked list
void delete_rear(LIST *p)
{
    NODE *cur=p->head;
    if(p->head==NULL)
    {
        printf("\n The list is empty!\n");
    }
    else
    {
        while(cur->rlink!=NULL)  //traversing till the end of the linked list
        {
            cur=cur->rlink;
        }
        if(cur->llink==NULL)   //if the list has only one node
        {
            delete_front(p);
        }
        else
        {
            NODE *prev=cur->llink;  //The second last node
            prev->rlink=NULL;       //Removing connection to last node;
            printf("\n The deleted node data is %d \n",cur->data);
            free(cur); //free the last node
        }
    }
}

//To delete a node with a particulat data from the linked list
void delete_node(LIST *p,int data)
{
    if(p->head==NULL)
    {
        printf("\n The list is empty!\n ");
    }
    else
    {
        NODE *cur=p->head;
        while(cur!=NULL && cur->data!=data)  //traverse to the node with the given data
        {
            cur=cur->rlink;
        }
        if(cur==NULL)  //If the data is not present in the linked list
        {
            printf("\n The data %d is not found in any node. Please try again! \n",data);
        }
        else if(cur->llink==NULL) //If the data is found in the first node itself
        {
            p->head=p->head->rlink;
            if(p->head!=NULL)
            {
                p->head->llink=NULL;
            }
            printf("\n Successfully deleted node with data %d \n",cur->data);
            free(cur);
            
        }
        else if(cur->rlink==NULL)   //If the data is found in the last node
        {
            NODE *prev=cur->llink;
            prev->rlink=NULL;
            printf("\n Successfully deleted node with data %d \n",cur->data);
            free(cur); //freeing the node containing the data
        }
        
        else        //The data is present in the middle of the list;
        {
            NODE *prev=cur->llink;
            prev->rlink=cur->rlink;
            cur->rlink->llink=prev;
            printf("\n Successfully deleted node with data %d \n",cur->data);
            free(cur); //freeing the node containing the data
        }

    }
}

//To search the position of an element in the linked list
int search(LIST *p,int ele)
{
    int count=0; //keeps track of the position of the node
    if(p->head==NULL) 
    {
        return -1;
    }
    else
    {
        NODE *temp=p->head;
        while(temp!=NULL && temp->data!=ele )  //traverse the list untill element is found or the list ends.
        {
            temp=temp->rlink;
            count++;
        }
        if(temp==NULL) //if the element is not found in the list
        {
            return -1;
        }
        else
        {
            return count; //if element is found then returns its position
        }
    }
}

//To destory the list and free up memory
void destroy(LIST *p)
{
    NODE *temp;
    while(p->head!=NULL) //till the list becomes empty
    {
        temp=p->head; //temp pointer to point to a node
        p->head=p->head->rlink; //shift the head pointer
        free(temp); //free the node whose address is stored in temp
    }
    printf("\n The list has been destroyed! \n");
}

//To print the elements of the linked list
void display(LIST *p)
{
    if(p->head==NULL)
    {
        printf("\n List is Empty\n");
    }
    else
    {
        NODE *temp=p->head;
        while(temp!=NULL) //traverses all the nodes of the linked list. If temp->rlink!=NULL is used then element in the last node won't be printed
        {
            printf("\n %d",temp->data); //prints the data of the nodes
            temp=temp->rlink;
        }
        printf("\n");
    }
}

//Menu based operation
int main()
{
    int choice,data,pos,x;
    LIST l1;
    init(&l1);
    do{
        printf("\n 1.Insert Front 2.Insert Rear 3.Insert at specific position ");
        printf("\n 4.Delete Front 5.Delete Rear 6.Delete a specific element ");
        printf("\n 7.Search an element 8.Display List 9.Destroy List 10.EXIT");
        printf("\n Enter choice: ");
        scanf(" %d",&choice); 
        switch(choice)
        {
            case 1:printf("\n Enter the element to be inserted at front: ");
                   scanf("%d",&data);
                   insert_front(&l1,data);
                   break;
            case 2:printf("\n Enter the element to be inserted at rear: ");
                   scanf("%d",&data);
                   insert_rear(&l1,data);
                   break;
            case 3:printf("\n Enter the element to be inserted: ");
                   scanf("%d",&data);
                   printf("\n Enter the position where the element is to be inserted: ");
                   scanf("%d",&pos);
                   insert_at_position(&l1,data,pos);
                   break;
            case 4:delete_front(&l1);
                   break;
            case 5:delete_rear(&l1);
                   break;
            case 6:printf("\n Enter the element to be deleted: ");
                   scanf("%d",&data);
                   delete_node(&l1,data);
                   break;
            case 7:printf("\n Enter element to be searched: ");
                   scanf("%d",&data);
                   x=search(&l1,data);
                   if(x==-1)
                   {
                       printf("\n The element is not  found!\n");
                   }
                   else
                   {
                       printf("\n The element is found at %d position in the list\n",x);
                   }
                   break;
            case 8:display(&l1);
                   break;
            case 9:destroy(&l1);
                   break;
            case 10:printf("\n THANK YOU. EXITING..\n");
                    break;
            default:printf("\n Invalid choice. Please try again! \n");
                    break;
        }
    }while(choice!=10);
}
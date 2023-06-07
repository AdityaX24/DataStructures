//Code by Aditya Poddar
//SRN PES2UG21CS036
//for any help, contact: poddar.aditya2014@gmail.com

#include<stdio.h>
#include<stdlib.h>
#define MAX 100     //maximun elements in the heap. Can be changed according to user need


void init(int *heap)    //To initialize first position of heap to 0
{
    heap[0]=0;
}

void heap_top_down(int *heap,int n)     //to insert elements to heap one by one
{
    int data,parent,child,temp;
    for(int i=1;i<n+1;i++)
    {
        printf("Enter element %d: ",i);     //takes element input
        scanf("%d",&data);
        heap[i]=data;
        parent=i/2;
        child=i;
        //(to construct a min heap use heap[parent]>heap[child])
        while(parent>0 && heap[parent]<heap[child])     //continue till root is reached or heap is constructed 
        {
            temp=heap[parent];              //if parent node has lower value than child, then swap the data
            heap[parent]=heap[child];
            heap[child]=temp;
            child=parent;                   //make parent the new child
            parent=child/2;                 //make parents parent the new parent
        }
    }
}

void delete_max(int *heap,int *n)       //to delete the max element which is always the root element of max heap
{
    printf("The deleted elemet is %d",heap[1]);
    int temp;
    temp=heap[1];   //deleteing the max element by swapping it with the last array and then heapifying in the next step
    heap[1]=heap[(*n)];
    heap[(*n)]=temp;
    (*n)--;
}

void heapify_array(int *heap,int n)           //To heapify the array containig the elements(Bottom_Up)
{
    int heaped,k,j,v;       //heaped is a counter to check if the subtree at pos k is already a heap
    for(int i=n/2;i>0;i--)      //To heapify all subtress starting from first parent(i.e n/2) to root(i.e 1)
    {
        k=i;                //parent node
        heaped=0;   
        v=heap[k];          //value at parent node
        while(!heaped && 2*k<=n)        //while the subtree is not completely heapifed or we reach leaf node
        {
            j=2*k;          //j is the left child of the parent k
            if(j<n)         //if there exists a right child 
            {
                if(heap[j+1]>heap[j])   //check if right child node has greater value.Change to heap[j+1]<heap[j] for minheap
                {
                    j=j+1;              //if right child has greater value, then make it as child
                }   
            }
            if(v>heap[j])           //if the parent has higher value (parental dominance property) then subtree is heapified.Change to v<heap[j] for minheap
            {   
                heaped=1;           //make heap counter is 1(heapified)
            }
            else        //if subtree is not heapified
            {
                heap[k]=heap[j];        //copy the child element data to parent node
                k=j;                    //make child as the new parent node and repeat the loop
            }
        }
        heap[k]=v;      
    }
}

void display(int *heap,int n)
{
    if(n==0)        //if no elements are in the array
    {
        printf("\n Please enter the elemets first!\n");
        return;
    }
    printf("\n");
    for(int i=1;i<n+1;i++)          //Display all elements of the heap in order
    {
        printf("%d ",heap[i]);
    }
    printf("\n");
}

int main()
{
    int heap_array[MAX];
    int n=0,choice,data;
    do
    {
        printf("\n Enter\n 1.Add Element to Heap\n 2.Display Max Element\n 3.Delete Max Element\n 4.Display heap 5.Exit : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:init(heap_array);
                   printf("\n Enter number of elements to be inserted into heap: ");
                   scanf("%d",&n);
                   heap_top_down(heap_array,n);
                   break;

            case 2:if(n==0)
                   {
                        printf("\n The heap is empty. Please enter elements first! \n");
                   }
                   else
                   {
                        printf("\n The maximum element is %d",heap_array[1]);
                   }
                   break;

            case 3:if(n<1)
                   {
                        printf("\n The heap is empty. Please enter elements first! \n");
                   }
                   else
                   {
                        delete_max(heap_array,&n);      //first delete the element
                        heapify_array(heap_array,n);    //then heapify the heap_array again. Time complexity=O(1)+O(logn)=O(logn)
                   }   
                   break;
            case 4:display(heap_array,n);
                   break;

            case 5:printf("\n THANK YOU. EXITING..\n");
                   break;

            default:printf("\n Invalid choice. Please try again! \n");
                    break;
        }

    } while(choice!=5);
}
/* Jacob Trappen and Artem Ivanov
Lecture Assignment 6
July 31, 2017
COP 3223C*/

// this code includes the basic library of functions and commands in c
#include<stdio.h>

// these next two lines initialize the functions mergesort and merge, which will be made later in the code.
void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);

// this is the main function that is executed in the code
int main()
{
    // these lines initializes the array of a[30], and two int variables n and i.
    // it then asks for a number of elements from the user and stores the user input into the n variable.
    // then it does a for loop using that n as a maximum and gets the user's elements for the array a[30] and saves it in the i variable.
    int a[30],n,i;
    printf("Enter # of elements:");
    scanf("%d", &n);
    printf("Enter array elements:");

    for(i =0 ; i < n; i++)
        scanf("%d", &a[i]);

    // this calls to the function mergesort, using the the array a, an int value of 0, and the n variable -1.
    // it then prints out the array as is sorted, using a for loop to get each value from the array.
    mergesort(a,0,n-1);
    printf("\nSorted array is :");
    for(i=0;i<n;i++)
        printf("%d ",a[i]);
    //this returns a 0 value for the main function and ending the main function
    return 0;
}

// this is the function mergesort, and is using the array a, 0 for i, and j is n-1.
void mergesort(int a[],int i,int j)
{
    int mid;

    //this if statement says that if the value of i (0) is less than the number of the size of the array, it will run the code
    //then the code sets a declared variable mid equal to the count i + the size of array - 1 divided by two.
    //the code will then run the mergesort function again using the mid as the j variable instead of n-1
    //the next line uses the function with the mid + 1 instead of i(which was 0)
    // then the last line calls the merge function.
    if(i<j)
    {
        mid=(i+j)/2;
        mergesort(a,i,mid);
        mergesort(a,mid+1,j);
        merge(a,i,mid,mid+1,j);
    }
}

//This fucntction does a merge and it uses the array a[], i for i1, mid for j1, mid+1 for i2, and j for j2.
void merge(int a[],int i1,int j1,int i2,int j2)
{
    int temp[50];    //array used for merging
    int i,j,k;	     //declaring i for i2, j for i2, k for 0.
    i=i1;            //beginning of the first list
    j=i2;            //beginning of the second list
    k=0;             //k is a collecting variable for temp[] array


    // This while loop is checking if i(0) is less or equal then j1(mid) and if j(size of the arrya(n-1)) is less or equal then j2(mid+1)
    // This if else put it array in order least to greatest

    while(i<=j1 && j<=j2)
    {
        if(a[i]<a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }

    //Those while loops are sorting firsly least values and then greatest values
    while(i<=j1)    
        temp[k++]=a[i++];

    while(j<=j2)
        temp[k++]=a[j++];

    //Transfer elements from temp[] back to a[]
    for(i=i1,j=0;i<=j2;i++,j++)
        a[i]=temp[j];
}

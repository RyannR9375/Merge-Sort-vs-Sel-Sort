//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

//User Libraries
struct Data{
    int size;
    short *hilow;
    short *c;
    
    short& operator[](int index){
        if (index >= size) {
            cout << "Array index out of bound, exiting";
            exit(0);
        }
            return c[index];
    }
};


//Global Constants

//Function Prototypes
Data *fill(int);
void print(Data *,int);
void merge(Data *,int,int,int);
void mrgSort(Data *,int,int,int&);
void destroy(Data *);
void selectionSort(vector<short>arr, int p, int& selectionOperations);

//Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number generator
    srand(static_cast<unsigned int>(time(0)));
    //Allocate the arrays
    const int p = 8;
    int n=100000;
    int perLine=10;
    Data *mergeSortArr = fill(n);
    std::vector<short> selSortArr(n);
    //Data *selSortArr = fill(n);
    //Print the arrays
    //print(mergeSort,perLine);
    //Sort the arrays then print
    
    //MERGE SORT TIMING
    int mergeOperations = 0;
    clock_t mergeStart = clock();
    mrgSort(mergeSortArr,0,mergeSortArr->size, mergeOperations);
    clock_t mergeEnd = clock();
    long mergeTime = mergeEnd - mergeStart;
    
    //SELECTION SORT TIMINGS
    int selectionOperations = 0;
    clock_t selectionStart = clock();
    selectionSort(selSortArr, p, selectionOperations);
    clock_t selectionEnd = clock();
    long selectionTime = selectionEnd - selectionStart;
    
    //OUTPUT TIMINGS
    std::cout << "Merge Sort Ticks: " << mergeTime << ".\nMerge Sort Operations: " << mergeOperations;
    std::cout << "\n\nSelection Sort Ticks: " << selectionTime << "\nSelection Sort Cycles: " << selectionOperations;;
    
    //Deallocate data
    destroy(mergeSortArr);
    //Exit stage right
    return 0;
}

void destroy(Data *a){
    //Deallocate data elements
    delete []a->hilow;
    delete []a->c;
    delete a;
}

void mrgSort(Data *a,int beg,int end, int& cycles){
    int center=(beg+end)/2;
    if((center-beg)>1){
        mrgSort(a,beg,center, cycles);
        cycles ++;
    }
    if((end-center)>1){
        cycles ++;
        mrgSort(a,center,end, cycles);
    }
    merge(a,beg,center,end);
}

void merge(Data *a,int beg,int nlow,int nhigh){
    //Create a merged array
    int span=nhigh-beg;    //Span the range to merge
    int cntl=beg,cnth=nlow;//Independent counters to merge
    //Fill the array
    for(int i=0;i<span;i++){
        if(cntl==nlow){
            a->c[i]=a->hilow[cnth++];
        }else if(cnth==nhigh){
            a->c[i]=a->hilow[cntl++];
        }else if(a->hilow[cntl]<a->hilow[cnth]){
            a->c[i]=a->hilow[cntl++];
        }else{
            a->c[i]=a->hilow[cnth++];
        }
    }
    //Copy back
    for(int i=0;i<span;i++){
        a->hilow[beg+i]=a->c[i];
    }
}

void print(Data *a,int perLine){
    //First print the unsorted array
    cout<<endl;
    for(int i=0;i<a->size;i++){
        cout<<a->hilow[i]<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

Data *fill(int n){
    //Allocate memory
    Data *data=new Data;
    data->size=n;
    data->hilow=new short[n];
    data->c=new short[n];
    for(int i=0;i<n;i++){
        data->hilow[i]=rand()%90+10;
        data->c[i]=0;
    }
    return data;
}

void selectionSort(vector<short> arr, int p, int& selectionOperations) {
    int n = arr.size();

    for (int i = 0; i < p; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[maxIndex]) {
                maxIndex = j;
            }
            selectionOperations++;
        }

        std::swap(arr[maxIndex], arr[i]);
    }
}
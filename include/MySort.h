#ifndef MYSORT_H
#define MYSORT_H


class MySort
{
public:
    //Bubble sort
    //average:O(n^2);
    //best:O(n);
    //worst:O(n^2);
    //space complication:O(1);
    //stable sort
    void BubbleSort(int A[], int n){
        for(int i = 0; i < n-1; ++i){
            for(int j = 0; j < n-i-1; ++j){
                if(A[j] > A[j+1])   //>= 则冒泡排序不稳定
                    swap(A[j], A[j+1]);
            }
        }
    }

    //Selection sort
    //average:O(n^2);
    //best:O(n^2);
    //worst:O(n^2);
    //space complication:O(1);
    //unstable sort
    void SelectionSort(int A[], int n){
        for(int i = 0; i < n-1; ++i){
            int minIndex = i;
            for(int j = i; j < n; ++j){
                if(A[j] < A[minIndex])
                    minIndex = j;
            }
            swap(A[i], A[minIndex]);    //这一步会导致不稳定，eg:5,8,5,2,9
        }
    }

    //Insertion sort
    //average:O(n^2);
    //best:O(n);
    //worst:O(n^2);
    //space complication:O(1);
    //stable sort
    //适用于数据量较小的；
    //在STL的sort算法和stdlib的qsort算法，将插入排序作为快速排序的补充，用于少量元素的排序（通常为8个或以下）
    void InsertionSort(int A[], int n){
        for(int i = 1; i < n; ++i){
            int get = A[i];     //手牌
            int j = i - 1;
            //将get插入到A[0],A[1],...,A[i-1]中
            while(j >=0 && A[j] > get){
                A[j+1] = A[j];  //往右边移
                --j;
            }
            A[j+1] = get;
        }
    }

    //Shell sort
    //average:依据步长不同而不同;
    //best:O(n);
    //worst:O(n(log n)^2);
    //space complication:O(1);
    //unstable sort
    void ShellSort(int A[], int n){
        int h = 1;
        while(h < n/3)
            h = 3 * h + 1; //步长序列:1,4,13,40...
        while(h >= 1){
            for(int i = h; i < n; i++){
                int get = A[i];
                int j = i - h;
                //将get插入到A[i-h],A[i-2h]...中
                while(j >= 0 && A[j] > get){
                    A[j + h] = A[j];
                    j -= h;
                }
                A[j+h] = get;
            }
            h /= 3; //减小步长
        }
    }

    //Merge sort
    //average:O(nlog n);
    //best:O(nlog n);
    //worst:O(nlog n);
    //space complication:O(n);
    //stable sort
    void MergeSort(int A[], int lo, int hi){
        //bound A[lo, hi];
        if(lo >= hi)
            return;
        int mid = lo + (hi - lo)/2;
        MergeSort(A, lo, mid);
        MergeSort(A, mid + 1, hi);
        Merge(A, lo, mid, hi);
    }

    void Merge(int A[], int lo, int mid, int hi){
        int len = hi - lo + 1;
        int *temp = new int[len];
        int i = lo, j = mid + 1, index = 0;
        while(i <= mid && j <= hi)
            temp[index++] = A[i] <= A[j] ? A[i++] : A[j++];
        while(i <= mid)
            temp[index++] = A[i++];
        while(j <= hi)
            temp[index++] = A[j++];
        for(int k = 0; k < len; ++k)
            A[lo++] = temp[k];
        delete []temp;
    }

    //Quick sort
    //average:O(nlog n);
    //best:O(nlog n);
    //worst:O(n^2);
    //space complication:O(log n)~O(n);
    //unstable sort
    void QuickSort(int A[], int lo, int hi){
        if(lo >= hi)
            return;
        int pivot_index = Partition(A, lo, hi);
        QuickSort(A, lo, pivot_index - 1);
        QuickSort(A, pivot_index + 1, hi);
    }

    int Partition(int A[], int lo, int hi){
        int pivot = A[hi];  //选择最后一个元素作为基准
        int tail = lo - 1;  //tail为小于基准的子数组的最后一个元素索引
        for(int i = lo; i < hi; ++i){
            if(A[i] <= pivot)
                swap(A[++tail], A[i]);  //将小于基准的元素放到子数组末尾
        }
        swap(A[tail + 1], A[hi]);   //将基准放置在子数组末尾
        return tail + 1;    //返回基准的索引
    }

    //Heap sort
    //average:O(nlog n);
    //best:O(nlog n);
    //worst:O(nlog n);
    //space complication:O(1);
    //unstable sort
    void HeapSort(int A[], int n){
        int heap_size = BuildHeap(A, n);
        while(heap_size > 1){
            swap(A[0], A[--heap_size]); //最后一个元素和当前最大的堆顶元素互换，并将堆的规模减1
            Heapify(A, 0, heap_size);
        }
    }

    void Heapify(int A[], int i, int size){     //从A[i]向下堆调整
        int left_child = 2 * i + 1;     //左孩子索引
        int right_child = 2 * i + 2;     //右孩子索引
        int max = i;        //选出父节点和子节点中最大的索引
        if(left_child < size && A[left_child] > A[max])
            max = left_child;
        if(right_child < size && A[right_child] > A[max])
            max = right_child;
        if(max != i){
            swap(A[i], A[max]);
            Heapify(A, max, size);
        }
    }

    int BuildHeap(int A[], int n){  //O(n)
        int heap_size = n;
        for(int i = heap_size / 2 - 1; i >= 0; --i){    //从每个非叶节点向下堆调整
            Heapify(A, i, heap_size);
        }
        return heap_size;
    }

};

#endif // MYSORT_H

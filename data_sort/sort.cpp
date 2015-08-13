#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define ARR_LEN 1000


void swapdata(int arr[],int i,int j)
{
	int temp;

	temp=arr[i];
	arr[i]=arr[j];
	arr[j]=temp;
}

void print_arr(int arr[],double time,int length)
{
	int i;
	for(i=0;i<length;i++)
		printf("%d\t",arr[i]);
	printf("\nrunning time:%.10lf s\n",time);
}

int bubble_rank1(int arr[],int length)
{
	int i,j;

	for(i=0;i<length;i++)
	{
		for(j=i+1;j<length;j++)//与i后面所有的数组元素进行相比，找出其中最小的元素
		{
			if(arr[i]>arr[j])
				swapdata(arr,i,j);
		}
	}
	return 1;
}

int bubble_rank2(int arr[],int length)
{
	int i,j;
	int	flag=2;//设置的标记位，并且初始化为2

	for(i=0;i<length && flag;i++)//若flag=0，则不进行遍历，这样可以减少比较有序的数列的遍历次数
	{                            //比如2,1,3,4,5,6,7,8。仅仅遍历一次可以得到结果，避免后面的不必要的遍历
		flag=0;                  //flag为0，表示数列未进行遍历，此处的i往后的元素均是有序的                  

		for(j=length-2;j>=i;j--)
		{
			if(arr[j]>arr[j+1])  //倒序寻找最小的元素
			{
			   swapdata(arr,j,j+1);
				flag=1;          //标记数列进行过变动
			}
		}
	}
	return 1;
}

int selectsort(int arr[],int length)
{
	int i,j;
	int minflag;   //设置最小元素的标记位

	for(i=0;i<length;i++)
	{
		minflag=i;         //标记为当前的i

		for(j=i+1;j<length;j++)
		{
			if(arr[minflag]>arr[j])  //寻找最小的元素
				minflag=j;           //设置最小标记位
		}
		if(i!=minflag)               //最小标记位是否发生改变
			 swapdata(arr,i,minflag);
	}
	return 1;
}

int insertsort(int arr[],int length)//插入排序
{
	int i,j;
	int temp;

	for(i=1;i<length;i++)
	{
		if(arr[i-1]>arr[i])//插入数组中较小的元素
		{
			temp=arr[i];   //设置交换数据，赋值待插入元素给temp
			for(j=i;arr[j-1]>temp;j--)  //将比a[i]大的元素向后移位,1`i形成有序的序列
				arr[j]=arr[j-1];
			            
			arr[j]=temp; //插入值到合适的位置
		}
	}
	return 1;
}

void shellsort(int arr[],int length)
{
	int i,j;
	int increasment=length;
	int temp;

	do
	{
		increasment=increasment/2;
		for(i=increasment;i<length;i++)
		{
			if(arr[i]<arr[i-increasment])
			{
			 	temp=arr[i];
				for(j=i-increasment;j>=0 && temp<arr[j];j-=increasment)
					arr[j+increasment]=arr[j];
				arr[j+increasment]=temp;
			}
		}
	}while(increasment>0);
}

/******heap sort*********/
void heapcreat(int arr[],int begin,int end)
{
	int temp,j;

	temp=arr[begin];
	for(j=2*begin+1;j<=end;j=j*2)
	{
		if(j<end && arr[j] < arr[j+1])
			++j;
		if(temp>=arr[j])
			break;
		arr[begin]=arr[j];
		begin=j;
	}
	arr[begin]=temp;
}
void heapsort(int arr[],int length)
{
	int i;
	int end;

	end = length-1;

	for(i=end/2;i>=0;i--)
		heapcreat(arr,i,end);
	for(i=end;i>0;i--)
	{
		swapdata(arr,0,i);
		heapcreat(arr,0,i-1);
	}
}
/*merge sort*/
void merge(int arr[],int tmp[],int begin,int mid,int end)
{
	int i,j,k;

    k=i=begin;       //前半部分的起始标记i，到mid结束
	j=mid+1;         //后半部分的标记j，到end结束
	while(j<=end && i<=mid) //前半部分与后半部分均未到达末尾，开始合并前后两部分
	{
		if(arr[i]<arr[j])   //  前半部分元素较小，插入到暂存数组tmp中
			tmp[k++]=arr[i++];
		else
			tmp[k++]=arr[j++]; //后半部分小，插入到暂存数组tmp中
	}
	while(i<=mid)             //如果前半部分中元素普遍大于后半部分元素，则i必然未到达mid，需要将剩下的元素添加到tmp数组中
		tmp[k++]=arr[i++];
	while(j<=end)           //如果后半部分中的元素普遍大于前半部分元素，则j未到达end，需要将剩下的元素添加tmp中；这里需要注意的是追加元素时只有两种情况。
		tmp[k++]=arr[j++];

	for(i=begin;i<=end;i++) //拷贝tmp中的元素到arr中，完成归并。
		arr[i]=tmp[i];
}

/*void mergesort(int arr[],int tmp[],int begin,int end)
{
    int mid,i;

    if(begin<end)
    {
        mid=(begin+end)/2;
        mergesort(arr,tmp,begin,mid);//前半部分归并有序
        mergesort(arr,tmp,mid+1,end);//后半部分归并有序

        merge(arr,tmp,begin,mid,end);//归并前后两部分合并到数组arr中。
    }
}
void m_sort(int arr[],int length)
{
		int *tmp;
	    tmp=(int*)malloc(length*sizeof(int));
	    if(tmp==NULL)
	    {
		  printf("out of memery!\n");
		  return;
	     }
         mergesort(arr,tmp,0,length-1);
		 free(tmp);
}*/
void mergesort_norecurse(int arr[],int tmp[],int step,int end)
{
	int i=0,j=0;

	while(i<=end-2*step+1)
	{
		merge(arr,tmp,i,i+step-1,i+2*step-1);
		i=i+2*step;
	}
	if(i<end-step+1)//剩余序列大于两个
        merge(arr,tmp,i,i+step-1,end);
	else
		for(j=i;j<end;j++)
			tmp[j]=arr[j];
}
void m_sort_norecurse(int arr[],int length)
{
		int *tmp;
		int step=1;
	    tmp=(int*)malloc(length*sizeof(int));
	    if(tmp==NULL)
	    {
		  printf("out of memery!\n");
		  return;
	     }
		while(step<length-1)
		{
         mergesort_norecurse(arr,tmp,step,length-1);
		 step=step*2;
		}
		 free(tmp);
}
/*fast sort*/

int find_key(int arr[],int low,int high)
{
	int key;
	key=arr[low];
	int tempdata;

	while(low<high)
	{
		while(low<high && arr[high]>key)
			high--;
		swapdata(low,high);
		while(low<high && arr[low]<key)
			low++;
		swapdata(low,high);
	}
	return low;
}

void fast_sort(int arr[],int low,int high)
{
	int keylocation;

	if(low<high)
	{
       keylocation=find_key(arr,low,high);
       fast_sort(arr,low,keylocation);
       fast_sort(arr,keylocation+1,high);
	}
}

void Qsort(int arr[],int length)
{
	fast_sort(arr,0,length-1);
}


int main()
{
	srand((unsigned int)time(NULL));
	int a[ARR_LEN],i;
    double  time=0;
	time_t begin,end;
	for(i=0;i<ARR_LEN;i++)
	{
		a[i]=rand()%1000;
	}
	//int b[10]={2,3,4,7,3,1,8,3,9,21};
    begin = clock();
    m_sort_norecurse(a,ARR_LEN);
	end = clock();
    time=double(end - begin)/CLOCKS_PER_SEC;
	print_arr(a,time,ARR_LEN);
}
//학과: 컴퓨터소프트웨어공학과
//학번: 20204024
//이름: 임지윤
//프로그램명: BLEP 데이터를 활용한 최소,최대 히프 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning (disable:4996)
#define MAX_ELEMENT 100000 // 히프 배열의 공간을 100000으로 설정함. 

typedef struct element { // 구조체를 선언하여 배열에 데이터 값을 저장함. 
	int key;
}element;

typedef struct {
	element heap[MAX_ELEMENT]; // 히프의 크기를 구조체로 정의함. 
	int heap_size;
}HeapType;

HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType)); // 히프를 동적할당하는 함수 
}

void init(HeapType* h)
{
	h->heap_size = 0; // 히프 초기화 함수 
}

void insert_max_heap(HeapType* h , element item)
{
	int i;

	i = ++(h->heap_size); // 히프 크기를 증가시킴 

	while ((i != 1) && (item.key > h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		
		i /= 2;
	} 

	h->heap[i] = item; // 최대 히프 함수 
}

void insert_min_heap(HeapType* h, element item)
{
	int i = 0; // 배열의 인덱스를 0으로 초기화함. 

	i = ++(h->heap_size); // 배열의 크기를 증가시킴.

	while ((i != 1) && (item.key < h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];

		i /= 2;

		
	}

	h->heap[i] = item; // 최소 히프 함수 
}


element deleteMaxHeap(HeapType* h) // 최대 히프 삭제 함수 
{
	int parent, child;
	element item, temp;

	item = h->heap[1]; // item에 히프 배열 첫번째 원소를 대입함 
	temp = h->heap[(h->heap_size)--];

	parent = 1;
	child = 2;

	while (child <= h->heap_size)
	{
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key))
		{
			child++;
		}

		if (temp.key >= h->heap[child].key)
		{
			break;
		}

		h->heap[parent] = h->heap[child];

		parent = child;

		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

element deleteMinHeap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];

	parent = 1;
	child = 2;

	while (child <= h->heap_size)
	{
		if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key))
		{
			child++;
		}

		if (temp.key <= h->heap[child].key)
		{
			break;
		}

		h->heap[parent] = h->heap[child];
		 // 히프 포인터 배열 parent 번째에 child 번째의 히프 값을 대입함. 
		parent = child;

		child *= 2; // 자식노드는 2를 곱한 인덱스의 값과 같음. 
	}
	h->heap[parent] = temp;

	return item;
}
void heap_sort1(element a[], int n) // 히프 정렬 함수 1
{
	int i;
	HeapType* h; // 히프 포인터 변수를 선언함. 

	h = create(); // 히프를 생성하여 초기화함. 
	init(h);

	for (i = 0; i < n; i++)
	{
		insert_max_heap(h,a[i]); // 최대 히프 삽입 함수 
	}

	for (i = (n - 1); i >= 0; i--)
	{
		a[i] = deleteMaxHeap(h); // 최대 히프 삭제 함수 
	}

	free(h);
}
void heap_sort2(element a[], int n) // 히프 정렬 함수 2
{
	int i;
	HeapType* h;

	h = create();
	init(h); // 히프를 생성하여 초기화함 

	for (i = 0; i < n; i++)
	{
		insert_min_heap(h, a[i]); // 최소 히프 삽입 함수 
	}

	for (i = (n - 1); i >= 0; i--)
	{
		a[i] = deleteMinHeap(h); // 최소 히프 삭제 함수 
	}

	free(h);
}
int main(void)
{
	FILE* fp; // 파일 포인터 변수 
	HeapType* heap; // 히프 포인터 변수 
	int i = 0;
	int count = 0; // 배열의 공간을 선언할 변수 
	int num;
	element* e; // 구조체 포인터 변수 
	clock_t start, stop; // 시간을 측정할 뱐수 선언 
	double duration; // 시간 변수 
	int exists[MAX_ELEMENT]; // 파일에서 중복 제거하고 존재하는 숫자를 담음
	int unique_count = 0; // exists의 길이
	int duplicate = 0; // 숫자가 반복할 경우를 표시함. 
	int temp;

	heap = create(); // 히프 생성
	init(heap); // 히츠 초기화

	fp = fopen("data.txt", "r"); // 파일 열기 

	if (fp == NULL) // 파일 포인터의 값이 NULL값일 경우 
	{
		printf("FILE NOT FOUND");
		return -1;
	}
	 
	while (!feof(fp)) // 파일 포인터가 끝에 도달할 때까지 반복함. 
	{
		fscanf(fp, "%d", &num);
		count++; // 배열의 크기를 동적할당하기 위하여 count를 증가시킴 
	}

	e = (element*)malloc(sizeof(element) * count); // e의 공간을 동적할당 받음. 
	 
	rewind(fp); // 파일 포인터 fp를 다시 읽어옴. 

	while (!feof(fp)) // 파일 포인터 fp를 끝까지 읽을 때까지 
	{

		fscanf(fp, "%d", &temp);
		for (int j = 0; j < unique_count; j++) // fscanf로 받은 값이 이미 exists에 있는지 검사
		{
			if (exists[j] == temp) {
				// 있으면 e[]에다가 넣지않음. 
				duplicate = 1;
				break;
			}
		}

		if (duplicate == 1) // 중복 발견함
		{
			duplicate = 0;
			continue;
		}
		else { // 중복 발견 못함
			e[i].key = temp;
			i++;

			exists[unique_count] = temp;
			unique_count++;
		}
		

	}
	count = i; // 배열의 인덱스의 총 인덱스 i값에 count값을 대입함. 

	start = clock(); // 시간 측정 시작 

	printf("최소 히프\n");

	heap_sort1(e, count); // 히프 정렬 함수를 선언함. 

	for (i = 0; i < 5; i++)
	{
		printf("%d\n", e[i].key);
	}

	printf("최대 히프\n");
	heap_sort2(e, count);

	for (i = 0; i < 5; i++)
	{
		printf("%d\n", e[i].key);
	}

	stop = clock(); // 시간 측정 종료 

	duration = (double)(stop - start); // 종료시간과 시작시간의 차이를 구함 

	printf("수행시간: %f초\n", duration);

	free(heap); // 히프를 동적할당해제함. 
	free(e);
	fclose(fp);
	return 0;
}

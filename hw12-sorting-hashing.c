 /*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);			
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);	// 배열에 할당된 공간을 해제합니다.
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);			// 배열 index 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);			// 배열 값 출력
	printf("\n");
}


int selectionSort(int *a)
{
	int min;					
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);								//정렬 전 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;							//최소값의 위치 저장(초기값은 비교 시작항 i)
		min = a[i];								//최소값 저장 (초기값 a[i])
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)	//i의 다음 항부터 마지막 항까지 비교
		{
			if (min > a[j])						// 더 작은 값 발견
			{
				min = a[j];						
				minindex = j;					// 최소값과 최소값의 위치를 바꾼다.
			}
		}
		a[minindex] = a[i];
		a[i] = min;								// a[i]와 최소값의 위치 변경
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);								// 정렬 후 배열 출력
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);								// 정렬 전 배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)			
	{
		t = a[i];								// i항의 값 임시 저장
		j = i;									// i항 부터 앞의 항으로 내려가며 비교 (j에 i 대입)
		while (a[j-1] > t && j > 0)				// 한칸 앞의 항과 비교
		{
			a[j] = a[j-1];						// 앞의 항이 크면, 뒷 항에 대입
			j--;								// j감소
		}
		a[j] = t;								// line 208이 실행됐다면, 값 변경 아니라면 유지됨
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);								// 정렬 후 배열 출력

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);								// 정렬 전 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)			
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++)    // j = 0 -> j=1로 변경
		{
			if (a[j-1] > a[j])					// 인접한 두 항을 차례대로 비교
			{
				t = a[j-1];						
				a[j-1] = a[j];
				a[j] = t;						// 앞의 항이 크면, 값 변경 -> 맨 뒤에 최대값이 위치하게 됨.
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);								// 정렬 후 배열 출력

	return 0;
}

int shellSort(int *a)				
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");					
	printf("----------------------------------------------------------------\n");

	printArray(a);				
	
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)			// i와 h, 2h .... 떨어진 항들끼리 비교하여 정렬
			{
				v = a[j];										// 시작 항 저장
				k = j;											// 시작 인덱스 저장
				while (k > h-1 && a[k-h] > v)					// h만큼 앞의 항과 비교
				{
					a[k] = a[k-h];								
					k -= h;
				}
				a[k] = v;										// 오름차순으로 정렬 (값 변경)
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1) 			// 배열 크기 > 1
	{
		v = a[n-1];		// 마지막 항 값 -> pivot
		i = -1;
		j = n - 1;		// pivot index

		while(1)
		{
			while(a[++i] < v);		// a[0] (left)부터 올라가며, a[n-1]보다 큰 값 찾기
			while(a[--j] > v);		// a[n-1] (right)부터 내려가며, a[n-1] 보다 작은 값 찾기
									
			if (i >= j) break;		// 교차되면 교환x
			t = a[i];
			a[i] = a[j];
			a[j] = t;				// a[i], a[j]의 값 교환
		}

		t = a[i];					// pivot값을 i위치의 값과 교환한다 (pivot을 i로 이동 -> 정렬 완료)
		a[i] = a[n-1];
		a[n-1] = t;
									// 바뀐 pivot을 중심으로, 
		quickSort(a, i);			// 왼쪽 레코드에 대한 퀵 정렬
		quickSort(a+i+1, n-i-1);	// 오른쪽 레코드에 대한 퀵 정렬
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;		// 해쉬함수, MOD 연산 이용
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;							// hash tabel 값 -1로 초기화

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;							// 해싱에 사용할 값 초기화
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)	// 배열 a에 대한 hash table 생성
	{
		key = a[i];							// key에 a[i] 대입
		hashcode = hashCode(key); 			// key에 대한 해싱
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) 	 	// 비어있는 bucket
		{
			hashtable[hashcode] = key;		// 대입
		} else 	{							// collision

			index = hashcode;				

			while(hashtable[index] != -1)	// 충돌 없을 때 까지
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;	// hash table의 다음 bucket으로
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;							// table에 key 값 대입
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);					// 찾으려는 key값을 hash함수에 넣으면 index(버킷 주소)가 반환됨.

	if(ht[index] == key)
		return index;							// 찾는 key가 맞다면 주소 반환

	while(ht[++index] != key)					
	{
		index = index % MAX_HASH_TABLE_SIZE;	// 버킷 내에서 key 찾을때까지 slot 탐색
	}
	return index;								// 주소 반환
}




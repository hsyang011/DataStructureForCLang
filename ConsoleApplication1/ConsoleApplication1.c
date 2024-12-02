#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef int element; // int타입을 element라는 별명을 붙입니다. 나중에 Stack<char>등으로 바꾸고 싶을 때 이부분을 수정하면 됩니다.
typedef struct {
	element* data; // data는 포인터로 정의됩니다.
	int capacity; // 현재 크기를 나타냅니다.
	int front;
	int rear;
} Queue;

// 큐 생성 함수
void init_queue(Queue* q) {
	q->front = -1;
	q->rear = -1;
	q->capacity = 1;
	q->data = (element*)malloc(q->capacity * sizeof(element));
}

// 공백 상태 검출 함수
int is_empty(Queue* q) {
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(Queue* q) {
	return (q->rear == q->capacity - 1);
}

// 추가 함수
void enqueue(Queue* q, element item) {
	if (is_full(q)) {
		q->capacity *= 2;
		q->data = (element*)realloc(q->data, q->capacity * sizeof(element));
	}
	q->data[++(q->rear)] = item;
}

// 삭제 함수
element dequeue(Queue* q) {
	if (is_empty(q)) {
		fprintf(stderr, "큐 공백 에러\n");
		exit(1);
	}
	else {
		return q->data[++(q->front)];
	}
}

int main() {
	Queue qu; // Queue타입 구조체 변수를 선언합니다.
	init_queue(&qu); // Queue를 초기화합니다. malloc을 통해 동적 메모리 할당을 수행합니다.

	enqueue(&qu, 1); // 스택에 element를 추가합니다. 만약 스택이 가득 찼다면
	enqueue(&qu, 2); // realloc을 통해 현재 사이즈의 2배만큼을 재할당 받습니다.
	enqueue(&qu, 3);

	printf("%d\n", dequeue(&qu));
	printf("%d\n", dequeue(&qu));
	printf("%d\n", dequeue(&qu));

	free(qu.data); // qu.data가 가리키는 포인터, 즉 malloc를 통해 할당 받은 메모리를 반환합니다.

	return 0;
}
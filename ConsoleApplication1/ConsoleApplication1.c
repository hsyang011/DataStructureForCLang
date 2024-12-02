#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef int element;
typedef struct {
	element* data; // data는 포인터로 정의된다.
	int capacity; // 현재 크기
	int top;
} Stack;

// 스택 생성 함수
void init_stack(Stack* s) {
	s->top = -1;
	s->capacity = 1;
	s->data = (element*)malloc(s->capacity * sizeof(element));
}

// 공백 상태 검출 함수
int is_empty(Stack* s) {
	return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(Stack* s) {
	return (s->top == s->capacity-1);
}

// 추가 함수
void push(Stack* s, element item) {
	if (is_full(s)) {
		s->capacity *= 2;
		s->data = (element*)realloc(s->data, s->capacity * sizeof(element));
	}
	s->data[++(s->top)] = item;
}

// 삭제 함수
element pop(Stack* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	} else {
		return s->data[(s->top)--];
	}
}

int main() {
	Stack st;
	init_stack(&st);

	push(&st, 1);
	push(&st, 2);
	push(&st, 3);

	printf("%d\n", pop(&st));
	printf("%d\n", pop(&st));
	printf("%d\n", pop(&st));

	free(st.data);

	return 0;
}

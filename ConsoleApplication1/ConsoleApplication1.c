#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef int element; // int타입을 element라는 별명을 붙입니다. 나중에 Stack<char>등으로 바꾸고 싶을 때 이부분을 수정하면 됩니다.
typedef struct {
	element* data; // data는 포인터로 정의됩니다.
	int capacity; // 현재 크기를 나타냅니다.
	int top; // 마지막 노드의 인덱스를 나타냅니다.
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
	return (s->top == s->capacity - 1);
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
	}
	else {
		return s->data[(s->top)--];
	}
}

int main() {
	Stack st; // Stack타입 구조체 변수를 선언합니다.
	init_stack(&st); // Stack을 초기화합니다. malloc을 통해 동적 메모리 할당을 수행합니다.

	push(&st, 1); // 스택에 element를 추가합니다. 만약 스택이 가득 찼다면
	push(&st, 2); // realloc을 통해 현재 사이즈의 2배만큼을 재할당 받습니다.
	push(&st, 3);

	printf("%d\n", pop(&st));
	printf("%d\n", pop(&st));
	printf("%d\n", pop(&st));

	free(st.data); // st.data가 가리키는 포인터, 즉 malloc를 통해 할당 받은 메모리를 반환합니다.

	return 0;
}
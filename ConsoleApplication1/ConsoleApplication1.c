#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct {
    element* data;  // 덱 데이터를 저장할 동적 배열
    int capacity;   // 덱의 최대 크기
    int front;      // 덱의 앞쪽 인덱스
    int rear;       // 덱의 뒤쪽 인덱스
} Deque;

// 덱 초기화 함수
void init_deque(Deque* dq) {
    dq->capacity = 4; // 초기 용량을 4로 설정
    dq->data = (element*)malloc(dq->capacity * sizeof(element));
    dq->front = 0;    // front를 0으로 설정
    dq->rear = 0;     // rear를 0으로 설정
}

// 덱이 비어 있는지 확인
int is_empty(Deque* dq) {
    return dq->front == dq->rear;
}

// 덱이 가득 찼는지 확인
int is_full(Deque* dq) {
    return (dq->rear + 1) % dq->capacity == dq->front;
}

// 덱 크기 확장
void resize(Deque* dq) {
    int new_capacity = dq->capacity * 2;
    element* new_data = (element*)malloc(new_capacity * sizeof(element));

    int i = dq->front;
    int j = 0;
    while (i != dq->rear) {
        new_data[j++] = dq->data[i];
        i = (i + 1) % dq->capacity;
    }

    free(dq->data);
    dq->data = new_data;
    dq->front = 0;
    dq->rear = j;
    dq->capacity = new_capacity;
}

// 앞쪽에 데이터 추가
void add_front(Deque* dq, element item) {
    if (is_full(dq)) resize(dq);

    dq->front = (dq->front - 1 + dq->capacity) % dq->capacity;
    dq->data[dq->front] = item;
}

// 뒤쪽에 데이터 추가
void add_rear(Deque* dq, element item) {
    if (is_full(dq)) resize(dq);

    dq->data[dq->rear] = item;
    dq->rear = (dq->rear + 1) % dq->capacity;
}

// 앞쪽에서 데이터 삭제
element delete_front(Deque* dq) {
    if (is_empty(dq)) {
        fprintf(stderr, "덱이 비어 있습니다.\n");
        exit(1);
    }

    element item = dq->data[dq->front];
    dq->front = (dq->front + 1) % dq->capacity;
    return item;
}

// 뒤쪽에서 데이터 삭제
element delete_rear(Deque* dq) {
    if (is_empty(dq)) {
        fprintf(stderr, "덱이 비어 있습니다.\n");
        exit(1);
    }

    dq->rear = (dq->rear - 1 + dq->capacity) % dq->capacity;
    return dq->data[dq->rear];
}

// 테스트용 메인 함수
int main() {
    Deque dq;
    init_deque(&dq);

    for (int i=1; i<=3; i++) {
        add_front(&dq, i);
    }

    for (int i=10; i<=12; i++) {
        add_rear(&dq, i);
    }

    for (int i=0; i<3; i++) {
        printf("%d\n", delete_front(&dq)); // 3, 2, 1 출력
    }

    for (int i=0; i<3; i++) {
        printf("%d\n", delete_rear(&dq)); // 12, 11, 10 출력
    }

    free(dq.data);

    return 0;
}

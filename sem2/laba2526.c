#include <stdio.h>
#include <stdlib.h>
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102

#define INIT_SIZE 4
#define MULTIPLIER 2

typedef struct {
        int size, top;
    int* data;
} Stack_t;

Stack_t* createStack() {
        Stack_t *out = NULL;
        out = malloc(sizeof(Stack_t));
        if (out == NULL) {
                exit(OUT_OF_MEMORY);
        }
        out->size = INIT_SIZE;
        out->data = malloc(out->size * sizeof(int));
        if (out->data == NULL) {
                free(out);
                exit(OUT_OF_MEMORY);
        }
        out->top = 0;
        return out;
}

void deleteStack(Stack_t **stack) {
        free((*stack)->data);
        free(*stack);
        *stack = NULL;
}

void resize(Stack_t *stack) {
    stack->size *= MULTIPLIER;
    stack->data = realloc(stack->data, stack->size * sizeof(int));
    if (stack->data == NULL) {
        exit(STACK_OVERFLOW);
    }
}

void push(Stack_t *stack, int value) {
    if (stack->top >= stack->size) {
        resize(stack);
    }
    stack->data[stack->top] = value;
    stack->top++;
}

int pop(Stack_t *stack) {
    if (stack->top == 0) {
        exit(STACK_UNDERFLOW);
    }
    stack->top--;
    return stack->data[stack->top];
}
int peek(const Stack_t *stack) {
    if (stack->top <= 0) {
        exit(STACK_UNDERFLOW);
    }
    return stack->data[stack->top - 1];
}


void implode(Stack_t *stack) {
    stack->size = stack->top;
    stack->data = realloc(stack->data, stack->size * sizeof(int));
}

void stack_print(Stack_t *stack) {
    for(int i = 0; i < stack->top; i++) {
        printf("%d\n", stack->data[stack->top - i - 1]);
    }
}

void stack_insert(Stack_t *stack, int index, int value) {
    if(index == stack->top) {
        push(stack, value);
    } else {
        Stack_t *stack_temp = createStack();
                int temp = stack->top - index;
        for(int i = 0; i < temp; i++) {
            push(stack_temp, pop(stack));
        }
        push(stack, value);
        temp = stack_temp->top;
        for(int i = 0; i < temp; i++) {
            push(stack, pop(stack_temp));
        }
    }
}

void InsertionSort(Stack_t *stack);

void main() {
    Stack_t *s = createStack();

    int n;
    printf("Введите число элементов:\n");
    scanf("%d", &n);
    int perem;

    for (int i = 0; i < n; i++)
   {
        printf("Введите элемент: ");
        scanf("%d", &perem);
        push(s, perem);
    }
    InsertionSort(s);
        printf("Отсортированный\n");
    stack_print(s);
    int c;
    while (c != EOF) {
        {
        printf("Добавьте элемент в стек\n");
        scanf("%d", &c);
        push(s, c);
        InsertionSort(s);
    printf("Отсортированный\n");
    stack_print(s);
     }
    }


    deleteStack(&s);
}


void InsertionSort(Stack_t *stack) {

    int n = stack->top;
    for(int i = 0; i < n; i++)
    {
        Stack_t *stack_unsort = createStack();
        Stack_t *stack_sort = createStack();
        int m =  stack->top - i - 1;
        if(i == 0) {
            stack_insert(stack, 0, pop(stack));
        } else {
            // compare это самый последний элемент отсортированного стэка
            // num это последний элемент стэка
            int num = pop(stack);
                printf("num равен %d\n", num);
            for(int j = 0; j < m; j++) {
                int number = pop(stack);
                push(stack_unsort, number);
                // stack_print(stack_unsort);
            }
            for(int j = 0; j < i; j++) {
                int compare = pop(stack);
                    printf("compare равен %d\n", compare);

                if(stack->top == 0 && compare > num) {
                     printf("(stack->top == 0 && compare > num)\n");
                    push(stack, num);
                    push(stack, compare);
                    int len_sort = stack_sort->top;
                    for(int k = 0; k < len_sort; k++) {
                        push(stack, pop(stack_sort));
                    }
                    for(int k = 0; k < m; k++) {
                        push(stack, pop(stack_unsort));
                    }
                    break;
                 } else
                 if (compare > num) {
                         printf("compare > num)\n");
                                 while(compare > num && stack->top != 0) {
                         push(stack_sort, compare);
                         compare = pop(stack);
                     }
                     if(compare < num) {
                           push(stack, compare);
                           push(stack, num);
                     } else {
                     push(stack, num);
                     push(stack, compare);
                     }
                     int len_sort = stack_sort->top;
                     for(int k = 0; k < len_sort; k++) {
                         push(stack, pop(stack_sort));
                     }
                     for(int k = 0; k < m; k++) {
                         push(stack, pop(stack_unsort));
                     }
                     break;

                         } else {
                        printf("compare < num)\n");
                                                push(stack, compare);
                                                push(stack, num);
                                                int len_sort = stack_sort->top;
                                                for(int k = 0; k < len_sort; k++) {
                                                        push(stack, pop(stack_sort));
                                                }
                                                for(int k = 0; k < m; k++) {
                                                        push(stack, pop(stack_unsort));
                                                }
                        break;
                                  }
            }
        }
    }
}

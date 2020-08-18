#include "benchcommon.h"

struct node {
    struct node* next;
    int value;
};

struct node heap [4000];

unsigned int free_;
struct node* root;

void init(void) {
    free_ = 0;
    root = 0;
}

struct node* alloc() {
    struct node* result;
    result = heap + free_;
    ++free_;
    return result;
}

void prepend(int x) {
    struct node* new;
    new = alloc();
    new->next = root;
    new->value = x;
    root = new;
}

int sum(void) {
    struct node* current;
    int s;
    s = 0;
    current = root;
    while (current) {
        s += current->value;
        current = current->next;
    }
    return s;
}

int main(void) {
    unsigned int i;
    unsigned char c;
    start();
    for(c = 0; c < 5; ++c) {
        init();
        for(i = 0; i < 3000; ++i) {
            prepend(i);
        }
        putchar((char)sum());
    }
    end();
    return 0;
}
// Copyright 2022 Wook-shin Han

#ifndef PROJECT1_H_
#define PROJECT1_H_

#include <cstring>
#include <iostream>

typedef struct node {
  int cnt;
  char barcode[5];
  struct node* next;
} Node;

typedef struct node_list {
  Node* head;
  Node* tail;
} NodeList;

void print_list(node_list* list) {  // for debugging
  Node* walk;
  for (walk = list->head; walk != NULL; walk = walk->next) {
    std::cout << walk->cnt << std::endl;
  }
}

void insert(node_list* list, node* newnode) {
  Node* walk;
  int check = 0;
  // when the list is empty, set the node to head & tail.
  if (list->head == NULL) {
    list->head = newnode;
    list->tail = newnode;
    newnode->cnt++;
  } else {
    for (walk = list->head; walk != NULL; walk = walk->next) {
    // when newnode is already in list,
    // Just increase the reference count. No insertion occurs.
      if (!strcmp(walk->barcode, newnode->barcode)) {
        walk->cnt++;
        check = 1;
        break;
      }
    }
    // If check == zero after traversing the list, insert the element.
    if (check == 0) {
      list->tail->next = newnode;
      list->tail = newnode;
      newnode->cnt++;
    }
  }
}

int is_in(NodeList* list, char* barcode) {
  int check = 0;
  node* walk;
  for (walk = list->head; walk != NULL; walk = walk->next) {
    if (!strcmp(walk->barcode, barcode) && walk->cnt >= 2) {
      check = 1;
      break;
    }
  }
  if (check)
    return 1;
  else
    return 0;
}

#endif  // PROJECT1_H_

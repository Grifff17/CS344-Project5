#include "llist.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void llist_insert_head(struct node **head, struct node *n) {
    if (*head == NULL) {;
        *head = (struct node*) malloc(sizeof(struct node));
    } else {
        n -> next = *head;
    }
    *head = n;
}

struct node *llist_delete_head(struct node **head) {
    if (*head == NULL) {
        return NULL;
    } else if ((*head)->next == NULL) {
        struct node *temp = *head;
        *head = NULL;
        return temp;
    } else {
        struct node *temp = (*head) -> next;
        *head = temp;
        return temp;
    }
}

void llist_insert_tail(struct node **head, struct node *n) {
    if (*head == NULL) {
        *head = (struct node*) malloc(sizeof(struct node));
        *head = n;
    } else {
        struct node *curr = *head;
        while (curr->next) {
            curr = curr -> next;
        }
        curr->next = n;
    }
}

void llist_print(struct node *head) {
    if (head == NULL) {
        printf("[empty]\n");
        return;
    }
    printf("%i", head -> value);
    if (head->next == NULL) {
        printf("\n");
        return;
    }
    struct node *curr = head->next;
    while (curr != NULL) {
        printf(" -> ");
        printf("%i", curr -> value);
        curr = curr -> next;
    }
    printf("\n");
}

void llist_free(struct node **head) {
    if (*head == NULL) {
        return;
    }
    struct node *curr = *head;
    while (curr->next) {
        struct node *temp = curr;
        curr = curr -> next;
        node_free(temp);
    }
    *head = NULL;
}

struct node *node_alloc(int value) {
    struct node *nnode;
    nnode = (struct node*) malloc(sizeof(struct node));
    nnode -> value = value;
    nnode -> next = NULL;
    return nnode;
}

void node_free(struct node *n) {
    //free(n -> value);
    //free(n -> next);
    free(n);
}

void main(int argc, char *argv[]) {
    struct node *head = NULL;

    char *command;
    command = argv[0];
    int i = 1;
    while (argv[i] != NULL) {
        command = argv[i];
        if (strcmp(command, "ih") == 0) {
            int val = atoi(argv[i+1]);
            struct node *n = node_alloc(val);
            llist_insert_head(&head, n);
            i++;
        } else if (strcmp(command, "it") == 0) {
            int val = atoi(argv[i+1]);
            struct node *n = node_alloc(val);
            llist_insert_tail(&head, n);
            i++;
        } else if (strcmp(command, "dh") == 0) {
            llist_delete_head(&head);
        } else if (strcmp(command, "f") == 0) {
            llist_free(&head);
        } else if (strcmp(command, "p") == 0) {
            llist_print(head);
        } else {
            printf("INVALID COMMAND: %s", command);
            exit(0);
        }
        i++;
    }
}
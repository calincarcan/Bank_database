#include "all.h"

Tpay init_pay(int val, int sender, int receiver, int id_pay) {
    Tpay pay_node = (Tpay)malloc(sizeof(pay));
    pay_node -> id_pay = id_pay;
    pay_node -> val = val;
    pay_node -> sender = sender;
    pay_node -> receiver = receiver;
    pay_node -> next = NULL;
    pay_node -> prev = NULL;
    return pay_node;
}

void insert_pay(lista list, int val, int sender, int receiver, int id_pay) {
    Tpay new_pay = init_pay(val, sender, receiver, id_pay);
    if (list -> head == NULL) {
        list -> head = list -> tail = new_pay;
        return;
    }
    new_pay -> prev = list ->tail;
    list ->tail -> next = new_pay;
    list ->tail = new_pay;
}

void delete_pay(int id_pay, lista list) {
    if (pay_exists(id_pay, list) == 0) {
        printf("Tranzactia nu exista.\n");
        return;
    }
    if (list ->head -> id_pay == id_pay) {
        Tpay temp = list ->head;
        list ->head = list ->head -> next;
        if (list ->head == NULL) {
            list ->tail = NULL;
            return;
        }
        if (list ->head -> next) 
            list ->head -> next -> prev = NULL;
        free(temp);
        return;
    }
    if (list ->tail -> id_pay == id_pay) {
        Tpay temp = list ->tail;
        list ->tail = list ->tail -> prev;
        if (list ->tail == NULL) {
            list ->head = NULL;
            return;
        }
        if (list ->tail -> prev)
            list ->tail -> prev -> next = NULL;
        free(temp);
        return;
    }
    Tpay temp = list ->head;
    while (temp) {
        if (temp -> id_pay == id_pay) {
            temp -> next -> prev = temp -> prev;
            temp -> prev -> next = temp -> next;
            free(temp);
            return;
        }
        temp = temp -> next;
    }
}

int pay_exists(int id, lista list) {
    if (list == NULL)
        return 0;
    Tpay temp = list ->head;
    while (temp) {
        if (temp -> id_pay == id)
            return 1;
        temp = temp -> next;
    }
    return 0;
}

void destroy_list(lista list) {
    if (list == NULL)
        return;
    while (list -> head) {
        delete_pay(list -> head -> id_pay, list);
    }
}

void print_list(lista list) {
    if (list == NULL)
        return;
    Tpay temp = list -> head;
    while (temp) {
        printf("========================================================\n");
        printf("    Tranzactia #%d:\n", temp -> id_pay);
        printf("    Suma: %d $\n", temp -> val);
        printf("    id Expeditor: %d   id Destinatar: %d\n", temp -> sender, temp -> receiver);
        printf("========================================================\n");
        temp = temp -> next;
    }
}
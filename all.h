#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct payptr {
    int id_pay; // id tranzactie
    int val; // suma tranzactie
    int sender; // id sender
    int receiver; // id receiver
    struct payptr *prev; // prev list
    struct payptr *next; // next list
} pay, *Tpay;

typedef struct{
    Tpay head; // head list
    Tpay tail; // tail list
} header_lista, *lista;

typedef struct{
    int id; // id user
    char nume[41]; // nume user
    char prenume[41]; // prenume user
    char email[41]; // email user
    lista received; // lista tranzactii primite
    lista sent; // lista tranzactii trimise
} user, *Tuser;

typedef struct nod{
    Tuser key; // user
    long height; // inaltime nod
    struct nod *left, *right, *parent; // linkuri alte noduri
} Node, *Tnode;

typedef struct treee{
    Tnode root; // radacine tree ului
    long size; // nr noduri in tree
} tree, *Ttree;

Tpay init_pay(int val, int sender, int receiver, int id_pay);
void insert_pay(lista list, int val, int sender, int receiver, int id_pay);
void delete_pay(int id_pay, lista list);
void destroy_list(lista list);
void print_list(lista list);
int pay_exists(int id, lista list);

Ttree create_tree();
int is_empty(Ttree tree);
Tnode minimum(Tnode x);
Tnode maximum(Tnode x);
Tnode search(Ttree tree, int id_key);
Tnode successor(Tnode x);
Tnode predecessor(Tnode x);
void update_height(Tnode x);
void avl_rotate_left(Ttree tree, Tnode x);
void avl_rotate_right(Ttree tree, Tnode x);
int balance_factor(Tnode x);
long maxim(long a, long b);
void avl_fix_up(Ttree tree, Tnode y);
Tnode init_node(Ttree tree, Tuser key);
void insert_node(Ttree tree, Tuser key);
Tnode build_tree_pivot(Tnode lt, Tnode rt);
Tnode deepest_node(Tnode root);
void destroy_node(Ttree tree, Tnode node);
void delete_node(Ttree tree, int key_id);
void destroy_tree(Ttree tree);
void destroy_tree_helper(Ttree tree, Tnode root);
Tuser create_user(int id, char *nume, char *prenume, char *email);
void destroy_user(Tuser user);
void inorder_print(Tnode node);
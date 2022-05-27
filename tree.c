#include "all.h"

long maxim(long a, long b) {
    if (a >= b)
        return a;
    return b;
}

void inorder_print(Tnode node) {
    if (node != NULL) {
        inorder_print(node->right);
        printf("========================================================\n");
        printf("id: %d\nnume: %s\nprenume: %s\nemail: %s\n", node->key->id, node->key->nume, node->key->prenume, node->key->email);
        printf("========================================================\n");
        inorder_print(node->left);
    }
}

Tuser create_user(int id, char *nume, char *prenume, char *email) {
    Tuser new_user = malloc(sizeof(user));
    new_user -> id = id;
    strncpy(new_user -> nume, nume, 40);
    strncpy(new_user -> prenume, prenume, 40);
    strncpy(new_user -> email, email, 40);
    new_user -> received = calloc(1, sizeof(header_lista));
    new_user -> sent = calloc(1, sizeof(header_lista));
    return new_user;
}

void destroy_user(Tuser user) {
    destroy_list(user -> received);
    destroy_list(user -> sent);
    free(user -> received);
    free(user -> sent);
    free(user);
}

Ttree create_tree() {
    Ttree new_tree = (Ttree) malloc(sizeof(tree));
    new_tree->size = 0;
    new_tree->root = NULL;
    return new_tree;
}

int is_empty(Ttree tree) {
    if (tree->size == 0)
        return 1;
    return 0;
}

Tnode search(Ttree tree, int id_key) {
    if (tree == NULL)
        return NULL;
    if (tree->root == NULL)
        return NULL;
    Tnode p = tree->root;
    while (p != NULL) {
        if (p->key->id > id_key) {
            p = p->left;
        } else {
            if (p->key->id < id_key) {
                p = p->right;
            }
            else
                return p;
        }
    }
    return NULL;
}

Tnode minimum(Tnode x) {
    if (x == NULL)
        return NULL;
    Tnode p = x;
    while (p->left != NULL) {
        p = p->left;
    }
    return p;
}

Tnode maximum(Tnode x) {
    if (x == NULL)
        return NULL;
    Tnode p = x;
    while (p->right != NULL) {
        p = p->right;
    }
    return p;
}

Tnode successor(Tnode x) {
    if (x == NULL)
        return NULL;
    Tnode p = x;
    if (p->right != NULL)
        return minimum(p->right);
    else {
        Tnode parent = p->parent;
        while (parent != NULL) {
            if (parent->right != p)
                return parent;
            p = parent;
            parent = parent->parent;
        }
        return NULL;
    }
}

Tnode predecessor(Tnode x) {
    if (x == NULL)
        return NULL;
    Tnode p = x;
    if (p->left != NULL)
        return maximum(p->left);
    else {
        Tnode parent = p->parent;
        while (parent != NULL) {
            if (parent->left != p)
                return parent;
            p = parent;
            parent = parent->parent;
        }
        return NULL;
    }
}

void update_height(Tnode x) {

    long leftHeight = 0;
    long rightHeight = 0;

    if (x != NULL) {
        if (x->left != NULL) leftHeight  = x->left->height;
        if (x->right != NULL) rightHeight = x->right->height;
        x->height = maxim(leftHeight, rightHeight) + 1;
    }
}


/* Functie ce primeste adresa unui arbore si
 * a unui nod x si realizeaza o rotatie la stanga
 * a subarborelui care are varful in x
 *
 *   (x)	 Rotatie    (y)
 *	 / \     stanga     / \
 *  a  (y)    ---->   (x)  c
 *	   / \			  / \
 *    b   c          a   b
 */
void avl_rotate_left(Ttree tree, Tnode x) {
    if (tree == NULL || x == NULL) return;
    if (x->right == NULL)
        return;
    Tnode y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->left = x;
    update_height(x);
    update_height(y);
    Tnode parent  = x->parent;
    if (parent != NULL) {
        if (parent->key->id < x->key->id) {
            parent->right = y;
            y->parent = parent;
        } else {
            parent->left = y;
            y->parent = parent;
        }
    } else {
        tree->root = y;
        y->parent = NULL;
    }
    x->parent = y;
}


/* Functie ce primeste adresa unui arbore si
 * a unui nod y si realizeaza o rotatie la dreapta
 * a subarborelui care are varful in y
 *
 *     (y)	 Rotatie    (x)
 *	   / \   dreapta    / \
 *   (x)  c   ---->    a  (y)
 *	 / \			      / \
 *  a   b                b   c
 */
void avl_rotate_right(Ttree tree, Tnode y) {
    if (tree == NULL || y == NULL) return;
    if (y->left == NULL)
        return;
    Tnode x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->right = y;
    update_height(y);
    update_height(x);
    Tnode parent  = y->parent;
    if (parent != NULL) {
        if (parent->key->id < y->key->id) {
            parent->right = x;
            x->parent = parent;
        } else {
            parent->left = x;
            x->parent = parent;
        }
    } else {
        tree->root = x;
        x->parent = NULL;
    }
    y->parent = x;
}


/* Calculeaza factorul de echilibrare pentru un nod x
 * (AVL balance factor)
*/
int balance_factor(Tnode x) {
    if (x != NULL) {
        long left_h = 0;
        long right_h = 0;
        if (x->left != NULL)
            left_h = x->left->height;
        if (x->right != NULL)
            right_h = x->right->height;
        return left_h - right_h;
    }
    return 0;
}


/* Functie pentru reechilibrarea unui arbore AVL
 * in urma unei inserari prin rotatii simple sau duble
 * si recalcularea inaltimii fiecarui nod intalnit parcurgand
 * arborele de jos in sus, spre radacina
 *
 */
void avl_fix_up(Ttree tree, Tnode y) {
    if (tree == NULL || tree->root == NULL)
        return;
    if (y == NULL)
        return;
    Tnode parent = NULL, parent_parent = NULL;
    if (y->parent != NULL) {
        parent = y->parent;
        update_height(parent);
        if (parent->parent != NULL) {
            parent_parent = parent->parent;
            while (parent_parent != NULL) {
                update_height(parent_parent);
                int bf = balance_factor(parent_parent);
                // stanga stanga
                if (bf > 1 && y->key->id < parent->key->id)
                    avl_rotate_right(tree, parent_parent);
                // dreapta dreapta
                if (bf < -1 && y->key->id > parent->key->id)
                    avl_rotate_left(tree, parent_parent);
                // stanga dreapta
                if (bf > 1 && y->key->id > parent->key->id) {
                    avl_rotate_left(tree, parent);
                    avl_rotate_right(tree, parent_parent);
                }
                // dreapta stanga
                if (bf < -1 && y->key->id < parent->key->id) {
                    avl_rotate_right(tree, parent);
                    avl_rotate_left(tree, parent_parent);
                }
                y = parent;
                parent = parent_parent;
                parent_parent = parent_parent->parent;
            }
        }
    }
}


/* Functie pentru crearea unui nod
 *
 * value: valoarea/cheia din cadrul arborelui
 * info: informatia/valoarea din dictionar
 */
Tnode init_node(Ttree tree, Tuser user) {

    if (tree == NULL)
        return NULL;

    // Alocarea memoriei
    Tnode node = (Tnode) malloc(sizeof(Node));

    // Initializarea informatiei din nod
    node -> key = user;

    // Initializarea legaturilor din cadrul arborelui
    node->parent = node->right = node->left = NULL;

    // Inaltimea unui nod nou este 1
    // Inaltimea lui NULL este 0
    node->height = 1;

    return node;
}


/* Inserarea unul nou nod in cadrul multi-dictionarului
 * ! In urma adaugarii arborele trebuie sa fie echilibrat
 *
 */
void insert_node(Ttree tree, Tuser key) {
    if (tree == NULL)
        return;
    Tnode new_node = init_node(tree, key);
    Tnode parent = NULL;
    Tnode p = tree->root;
    while (p != NULL) {
        parent = p;
        if (p->key->id > key->id)
            p = p->left;
        else {
            p = p->right;
        }
    }
    if (parent == NULL && p == NULL) {
        tree->root = new_node;
        tree->size++;
        return;
    }
    if (parent->key->id < key->id) {
        parent->right = new_node;
        new_node->parent = parent;
    } else {
        parent->left = new_node;
        new_node->parent = parent;
    }
    avl_fix_up(tree, new_node);
    tree->size++;
}

/* Functie care construieste un arbore
 * pornind de la subarborele stang si subarborele drept
 *
 * Ajuta la eliminarea unui nod din arbore!
 */

Tnode build_tree_pivot(Tnode lt, Tnode rt) {
    Tnode pivot = rt, parent = NULL;
    if (lt == NULL) return rt;
    if (rt == NULL) return lt;
    if (rt->left == NULL) {
        rt->left = lt;
        return rt;
    }
    while (pivot->left != NULL) {
        parent = pivot;
        pivot = pivot->left;
    }
    parent->left = pivot->right;
    if (pivot->right != NULL)
        pivot->right->parent = parent;
    pivot->left = lt;
    lt->parent = pivot;
    pivot->right = rt;
    rt->parent = pivot;
    while (parent != pivot) {
        update_height(parent);
        parent = parent->parent;
    }
    update_height(pivot);
    return pivot;
}

/* Functie care returneaza primul nod
 * de pe nivelul cel mai de jos
 * dintr-un arbore
 */
Tnode deepest_node(Tnode root) {
    Tnode p = root, parent = NULL;
    while (p != NULL) {
        parent = p;
        int bf = balance_factor(p);
        if (bf < 0)
            p = p->right;
        else
            p = p->left;
    }
    return parent;
}

void destroy_node(Ttree tree, Tnode node) {
    destroy_user(node -> key);
    free(node);
}

/* Eliminarea unui nod din arbore
 *
 * elem: cheia nodului ce trebuie sters
 * 	! In cazul in care exista chei duplicate
 *	  se va sterge ultimul nod din lista de duplicate
 */
void delete_node(Ttree tree, int key_id) {
    if (tree == NULL || is_empty(tree)) return;
    Tnode parent = NULL, p = tree->root;
    while (p != NULL) {
        if (p->key->id == key_id)
            break;
        parent = p;
        if (key_id < p->key->id)
            p = p->left;
        else
            p = p->right;
    }
    if (p == NULL) return;
    tree->size--;
    Tnode clean_tree = NULL;
    if (parent == NULL) {
        clean_tree = build_tree_pivot(p->left, p->right);
        tree->root = clean_tree;
        if (tree->root != NULL) {
            tree->root->parent = NULL;
            avl_fix_up(tree, deepest_node(tree->root->right));
        }
        destroy_node(tree, p);
        return;
    } else {
        if (p->right == NULL && p->left == NULL)
            clean_tree = NULL;
        else
            clean_tree = build_tree_pivot(p->left, p->right);
        if (parent->right != NULL && parent->right->key->id == key_id) {
            parent->right = clean_tree;
            avl_fix_up(tree, deepest_node(parent->left));
        } else {
            parent->left = clean_tree;
            avl_fix_up(tree, deepest_node(parent->right));
        }
        if (clean_tree != NULL)
            clean_tree->parent = parent;
        destroy_node(tree, p);
        return;
    }
}

void destroy_tree_helper(Ttree tree, Tnode root) {
    if (root != NULL) {
        destroy_tree_helper(tree, root->left);
        destroy_tree_helper(tree, root->right);
        destroy_node(tree, root);
    }
}

/* Eliberarea memoriei unui arbore
 */
void destroy_tree(Ttree tree){
    if (tree != NULL) {
        destroy_tree_helper(tree, tree->root);
        free(tree);
    }
}
#include "all.h"

int main() {
    int id_user = 1;
    int id_pay = 1;

    Ttree mytree = create_tree();

    // for (int i = 1; i < 10; i++) {
    //     char nume[50] = "Florian";
    //     char prenume[50]  = "Gigi";
    //     char email[50] = "programator@c.com";
    //     Tuser key = create_user(id_user++, nume, prenume, email);
    //     insert_node(mytree, key);
    // }

    // delete_node(mytree, mytree -> root -> left -> key);
    // inorder_print(mytree -> root);
    // destroy_tree(mytree);

    int exit_flag = 1;
    char buffer[1024] = {0};
    while (exit_flag) {
        scanf("%s", buffer);
        if (strncmp(buffer, "insert_user", strlen(buffer)) == 0) {
            Tuser key = create_user(id_user++, "", "", "");
            printf("Introdu numele:\n");
            scanf("%s", key -> nume);
            printf("Introdu prenumele:\n");
            scanf("%s", key -> prenume);
            printf("Introdu email-ul:\n");
            scanf("%s", key -> email);
            insert_node(mytree, key);
            printf("user introdus cu succes...\n");
        }
         
        if (strncmp(buffer, "insert_pay", strlen(buffer)) == 0) {
            int val, id_sender, id_receiver;
            printf("Introdu valoarea: \n");
            scanf("%d", &val);
            printf("Introdu id_expeditor: \n");
            scanf("%d", &id_sender);
            printf("Introdu id_destinatar: \n");
            scanf("%d", &id_receiver);
            
            Tnode send, recev;
            send = search(mytree, id_sender);
            recev = search(mytree, id_receiver);
            insert_pay(send -> key -> sent, val, id_sender, id_receiver, id_pay);
            insert_pay(recev -> key -> received, val, id_sender, id_receiver, id_pay);
            id_pay++;
            printf("Tranzactia a fost introdusa cu succes...\n");
        }
         
        if (strncmp(buffer, "delete_user", strlen(buffer)) == 0) {
            printf("introdu id ul userului...\n");
            int id_delete = 0;
            scanf("%d", &id_delete);
            delete_node(mytree, id_delete);
            printf("Stergerea s-a realizat cu succes...\n");
        }
         
        if (strncmp(buffer, "print_lists", strlen(buffer)) == 0) {
            printf("introdu id ul userului...\n");
            int temp_user = 0;
            scanf("%d", &temp_user);
            Tnode user_lists = search(mytree, temp_user);
            if (user_lists) {
                printf("lista de tranzactii trimise:\n");
                print_list(user_lists -> key -> sent);
                printf("lista de tranzactii primite:\n");
                print_list(user_lists -> key -> received);
                printf("printarile au fost realizate cu succes...\n");
            }
            else
                printf("Userul nu a fost gasit.\n");
        }
        
        if (strncmp(buffer, "print_users", strlen(buffer)) == 0) {
            inorder_print(mytree -> root);
            printf("printare users s-a realizat cu succes...\n");
        }

        if (strncmp(buffer, "exit", strlen(buffer)) == 0) {
            exit_flag = 0;
            destroy_tree(mytree);
        }
    }
    return 0;
}
#include "all.h"

int main() {
    int id_user = 1;
    int id_pay = 1;
    Ttree mytree = create_tree();

    printf("Bine ai venit in interfata bancara!\n");
    printf("Ai urmatoarele optiuni:\n\n");
    printf("insert_user - creeaza un nou client\n");
    printf("insert_pay - adauga o noua tranzactie\n");
    printf("delete_user - sterge un client din sistem\n");
    printf("print_lists - afiseaza toate tranzactiile care au legatura cu un client\n");
    printf("print_users - afiseaza toti clientii din sistem in ordinea descrescatoare a ID-ului\n");
    printf("exit - incheie rularea interfetei\n\n");

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
            printf("User introdus cu succes...\n\n");
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
            printf("Tranzactia a fost introdusa cu succes...\n\n");
        }
         
        if (strncmp(buffer, "delete_user", strlen(buffer)) == 0) {
            printf("Introdu id ul userului...\n");
            int id_delete = 0;
            scanf("%d", &id_delete);
            delete_node(mytree, id_delete);
            printf("Stergerea s-a realizat cu succes...\n\n");
        }
         
        if (strncmp(buffer, "print_lists", strlen(buffer)) == 0) {
            printf("Introdu id ul userului...\n");
            int temp_user = 0;
            scanf("%d", &temp_user);
            Tnode user_lists = search(mytree, temp_user);
            if (user_lists) {
                printf("Lista de tranzactii trimise:\n");
                print_list(user_lists -> key -> sent);
                printf("Lista de tranzactii primite:\n");
                print_list(user_lists -> key -> received);
                printf("Printarile au fost realizate cu succes...\n\n");
            }
            else
                printf("Userul nu a fost gasit!\n\n");
        }
        
        if (strncmp(buffer, "print_users", strlen(buffer)) == 0) {
            inorder_print(mytree -> root);
            printf("Printare users s-a realizat cu succes...\n\n");
        }

        if (strncmp(buffer, "exit", strlen(buffer)) == 0) {
            exit_flag = 0;
            destroy_tree(mytree);
        }
    }
    return 0;
}
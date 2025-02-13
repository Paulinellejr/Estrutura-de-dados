#include "ArvoreBinaria.h"

int main()
{
    int ch, op;
    Node *T = NULL;
    while (op != 0)
    {

        printf("__Arvore_Binaria_de_Busca__ \n");
        printf("1 - Inserir chave \n");
        printf("2 - remover chave \n");
        printf("3 - imprimir Arvore \n");
        printf("0 - Sair \n");
        printf("Digite a Opção: ");
        scanf("%d", &op);
        switch (op)
        {
        case 0:
            printf("Saindo... ");
            break;
        case 1:
            printf("Digite a chave:  ");
            scanf("%d", &ch);
            printf("\n");
            T = insertNode(T, ch);
            break;
        case 2:
            printf("Digite a chave: ");
            scanf("%d", &ch);
            printf("\n");
            T = removeNode(T, ch);
            break;
        case 3:
            printf("Arvore Binaria de Busca:\n");
            printTree(T, 0);
            break;
        default:
            printf("Opção inexitente!");
            break;
        }
    }

    return 1;
}

char menu_principal(void) {
    system("clear");

    printf("\t\t=====================================\n");
    printf("\t\t||           SIG-Cliente           ||\n");
    printf("\t\t=====================================\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t|       1 - Modulo de Cliente       |\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t|   2 - Modulo em Desenvolvimento   |\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t|   3 - Modulo em Desenvolvimento   |\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t|             4 - Sobre             |\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t|           0 - Finalizar           |\n");
    printf("\t\t-------------------------------------\n");

    char op;

    printf("\nDigite a opcao desejada: ");
    scanf("%c", &op);
    getchar();

    return op;
}
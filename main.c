#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>

#include "customer.h"
#include "product.h"
#include "request.h"
#include "report.h"
#include "about.h"
#include "inputs.h"
#include "util.h"

// Versão 0.12

void mod_main(void);
int menu_main(void);

int main(void) {
    setlocale(LC_ALL|~LC_NUMERIC, "");

    mod_main();
    
    return 0;
}

int menu_main(void) {
    terminal_clear();

    printf("\t\t=====================================\n");
    printf("\t\t||           SIG-Customer          ||\n");
    printf("\t\t=====================================\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t|       1 - Modulo de Cliente       |\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t|       2 - Modulo de Produto       |\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t|       3 - Modulo de Pedidos       |\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t|      4 - Modulo de Relatorio      |\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t|             5 - Sobre             |\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t|           0 - Finalizar           |\n");
    printf("\t\t-------------------------------------\n");

    printf("\nDigite a opcao desejada: ");
    int op = read_numeric_op(); 

    return op;
}

void mod_main(void) {
    int op = menu_main();

    while (op != 0) {
        switch (op) {
            case 1:
                mod_customer();

                break;

            case 2:
                mod_product();

                break;

            case 3:
                mod_request();

                break;

            case 4:
                mod_report();

                break;

            case 5:
                about();

                break;
                
            default:
                printf("\nOpcao invalida. Por favor, digite uma opcao valida.\n");

                break;
        }

        press_enter_to_continue();

        op = menu_main();
    }

    printf("\nPrograma encerrado\n");
}
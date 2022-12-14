#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#include "product.h"
#include "inputs.h"
#include "util.h"

int menu_product(void) {
    terminal_clear();

    printf("\t\t=====================================\n");
    printf("\t\t||         Modulo Produtos         ||\n");
    printf("\t\t=====================================\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t|       1 - Cadastrar Produto       |\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t|       2 - Pesquisar Produto       |\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t|       3 - Atualizar Produto       |\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t|        4 - Deletar Produto        |\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t|           0 - Regressar           |\n");
    printf("\t\t-------------------------------------\n");
    
    printf("\nDigite a opcao desejada: ");
    int op = read_numeric_op();

    return op;
}

void create_product(void) {
    Product* product = create_product_screen();

    if (search_product(product->product_code) == NULL) {
        save_product(product);

        printf("\nProduto cadastrado com sucesso.\n");
    }

    else {
        printf("\nProduto ja cadastrado.\n");
    }

    free(product);
}

Product* search_product(char* product_code) {
    FILE* file;
    Product* product;

    product = (Product*) malloc(sizeof(Product));

    if (access("product.dat", F_OK) != -1) {
        file = fopen("product.dat", "rb");

        if (file == NULL) {
            printf("\nErro ao abrir o arquivo.\n");
            
            exit(1);
        }

        while (!feof(file)) {
            fread(product, sizeof(Product), 1, file);

            if (strcmp(product->product_code, product_code) == 0 && product->deleted == 0) {
                fclose(file);

                return product;
            }
        }

        fclose(file);
    }

    return NULL;
}

char* get_product_name(char* product_code) {
    Product* product = search_product(product_code);

    if (product != NULL) {
        return product->product_name;
    }

    return "Produto deletado";
}

float get_product_price(char* product_code) {
    Product* product = search_product(product_code);

    return product->product_price;
}

void save_product(Product *product) {
    FILE* file = fopen("product.dat", "ab");

    if (file == NULL) {
        printf("\nErro ao abrir o arquivo.\n");
        exit(1);
    }

    fwrite(product, sizeof(Product), 1, file);

    fclose(file);
}

char* show_product_types(void) {
    char* type = (char*) malloc(255 * sizeof(char));

    int op = 0;

    do {
        printf("\n");

        printf("\t\t=====================================\n");
        printf("\t\t||    Informe o tipo do produto    ||\n");
        printf("\t\t=====================================\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t|            1 - Perfume            |\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t|          2 - Hidratantes          |\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t|            3 - Barbear            |\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t|           4 - Sabonetes           |\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t|            5 - Shampoo            |\n");
        printf("\t\t-------------------------------------\n");

        printf("\nDigite a opcao desejada: ");
        op = read_numeric_op();

        switch(op) {
            case 1:
                strcpy(type, "Perfume");

                break;

            case 2:
                strcpy(type, "Hidratante");

                break;

            case 3:
                strcpy(type, "Barbear");

                break;

            case 4:
                strcpy(type, "Sabonete");

                break;

            case 5:
                strcpy(type, "Shampoo");

                break;

            default:
                printf("\nOpcao invalida.\n");

                break;
        }   
    } while (op != 1 && op != 2 && op != 3 && op != 4 && op != 5);

    return type;
}

Product* create_product_screen(void) {
    terminal_clear();

    Product* product = (Product*) malloc(sizeof(Product));

    char product_code[50];
    char product_name[255];
    char product_description[255];
    char product_price[20];

    printf("\t\t========================================\n");
    printf("\t\t||                                    ||\n");
    printf("\t\t||            ------------            ||\n");
    printf("\t\t||            SIG-Customer            ||\n");
    printf("\t\t||            ------------            ||\n");
    printf("\t\t||                                    ||\n");
    printf("\t\t========================================\n");
    printf("\n");
    printf("\t\t========================================\n");
    printf("\t\t||          Cadastrar Produto         ||\n");
    printf("\t\t========================================\n");

    printf("\nDigite o codigo de barras do produto (Formato EAN13): ");
    read_product_code(product_code);
    
    printf("Digite o nome do produto: ");
    read_name(product_name);

    printf("Digite o tipo do produto:\n");
    strcpy(product->product_type, show_product_types());

    printf("Digite a descricao do produto: ");
    read_string(product_description);
                
    printf("Digite o preco do produto (Formato: 00.00): ");
    read_float(product_price);

    float price = atof(product_price);

    strcpy(product->product_code, product_code);
    strcpy(product->product_name, product_name);
    strcpy(product->product_description, product_description);
    
    product->product_price = price;
    product->deleted = 0;

    return product;
}

void show_product(Product* product) {
    printf("\t\t========================================\n");
    printf("\t\t||                                    ||\n");
    printf("\t\t||            ------------            ||\n");
    printf("\t\t||            SIG-Customer            ||\n");
    printf("\t\t||            ------------            ||\n");
    printf("\t\t||                                    ||\n");
    printf("\t\t========================================\n");
    printf("\n");
    printf("\t\t========================================\n");
    printf("\t\t||        Visualizando Produto        ||\n");
    printf("\t\t========================================\n");

    printf("\nCodigo de barras: %s\n", product->product_code);
    printf("Nome: %s\n", product->product_name);
    printf("Tipo: %s\n", product->product_type);
    printf("Descricao: %s\n", product->product_description);
    printf("Preco: %.2f\n", product->product_price);
}

void find_product(void) {
    terminal_clear();

    Product* product;
    char* product_code = search_product_screen();

    if (search_product(product_code) != NULL) {
        product = search_product(product_code);

        terminal_clear();

        show_product(product);

        free(product);
    }

    else {
        printf("\nProduto nao encontrado ou inexistente.\n");
    }

    free(product_code);
}

char* search_product_screen(void) {
    terminal_clear();

    char* product_code = (char*) malloc(sizeof(char) * 20);

    printf("\t\t========================================\n");
    printf("\t\t||                                    ||\n");
    printf("\t\t||            ------------            ||\n");
    printf("\t\t||            SIG-Customer            ||\n");
    printf("\t\t||            ------------            ||\n");
    printf("\t\t||                                    ||\n");
    printf("\t\t========================================\n");
    printf("\n");
    printf("\t\t========================================\n");
    printf("\t\t||         Pesquisar Produtos         ||\n");
    printf("\t\t========================================\n");

    printf("\nDigite o codigo do produto: ");
    read_product_code(product_code);

    return product_code;
}

void update_product_file(Product* product) {
    FILE* file = fopen("product.dat", "r+b");

    Product* aux_product = (Product*) malloc(sizeof(Product));

    int found = 0;
    long int minus_one = -1;

    if (file == NULL) {
        printf("\nErro ao abrir o arquivo.\n");

        exit(1);
    }

    while (!feof(file) && !found) {
        fread(aux_product, sizeof(Product), 1, file);

        if (strcmp(aux_product->product_code, product->product_code) == 0 && aux_product->deleted == 0) {
            found = 1;

            fseek(file, (minus_one) * sizeof(Product), SEEK_CUR);

            fwrite(product, sizeof(Product), 1, file);
        }
    }

    fclose(file);

    free(aux_product);
}

void update_product(void) {
    Product* product;

    char* product_code = update_product_screen();

    if (search_product(product_code) != NULL) {
        product = search_product(product_code);
        product = update_product_data(product);

        strcpy(product->product_code, product_code);

        update_product_file(product);

        free(product);
    }

    else {
        printf("\nProduto nao encontrado ou inexistente.\n");
    }

    free(product_code);
}

char* update_product_screen(void) {
    terminal_clear();

    char* product_code = malloc(sizeof(char) * 20);

    printf("\t\t========================================\n");
    printf("\t\t||                                    ||\n");
    printf("\t\t||            ------------            ||\n");
    printf("\t\t||            SIG-Customer            ||\n");
    printf("\t\t||            ------------            ||\n");
    printf("\t\t||                                    ||\n");
    printf("\t\t========================================\n");
    printf("\n");
    printf("\t\t========================================\n");
    printf("\t\t||         Atualizar Produtos         ||\n");
    printf("\t\t========================================\n");

    printf("\nDigite o codigo do produto: ");
    read_product_code(product_code);

    return product_code;
}

Product* update_product_data(Product* product) {
    terminal_clear();

    char product_price[20];

    int op;

    do {
        op = 0;

        printf("\t\t=====================================\n");
        printf("\t\t||  Qual(is) dado(s) quer editar?  ||\n");
        printf("\t\t=====================================\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t|        1 - Nome do Produto        |\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t|        2 - Tipo do Produto        |\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t|           3 - Descricao           |\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t|             4 - Preco             |\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t-------------------------------------\n");
        printf("\t\t|     0 - Encerrar Atualizacoes     |\n");
        printf("\t\t-------------------------------------\n");

        printf("\nDigite a opcao desejada: ");
        op = read_numeric_op();

        if (op != 0) {
            switch (op) {
                case 1:
                    printf("\nDigite o novo nome do produto: ");
                    read_name(product->product_name);
                    
                    printf("\nNome do produto atualizado com sucesso!\n");

                    press_enter_to_continue();
                    terminal_clear();

                    break;

                case 2:
                    printf("\nDigite o novo tipo do produto: \n");

                    strcpy(product->product_type, show_product_types());

                    printf("\nTipo do produto atualizado com sucesso!\n");

                    press_enter_to_continue();
                    terminal_clear();

                    break;

                case 3:
                    printf("\nDigite a nova descricao do produto: ");
                    read_string(product->product_description);

                    printf("\nDescricao do produto atualizada com sucesso!\n");

                    press_enter_to_continue();
                    terminal_clear();

                    break;

                case 4:
                    printf("\nDigite o novo preco do produto: ");
                    read_float(product_price);

                    float price = atof(product_price);

                    product->product_price = price;

                    printf("\nPreco do produto atualizado com sucesso!\n");

                    press_enter_to_continue();
                    terminal_clear();

                    break;

                default:
                    printf("\nOpcao invalida.\n");

                    break;
            }
        }
    } while (op != 0);

    return product;
}

void delete_product_file(Product* product) {
    FILE* file;
    Product* aux_product;

    int found = 0;
    long int minus_one = -1;

    if (confirm_product_delete(product)) {
        file = fopen("product.dat", "r+b");

        aux_product = (Product*) malloc(sizeof(Product));

        if (file == NULL) {
            printf("\nErro ao abrir o arquivo.\n");

            exit(1);
        }

        while (!feof(file) && !found) {
            fread(aux_product, sizeof(Product), 1, file);

            if (strcmp(aux_product->product_code, product->product_code) == 0 && aux_product->deleted == 0) {
                found = 1;

                fseek(file, (minus_one) * sizeof(Product), SEEK_CUR);

                aux_product->deleted = 1;

                fwrite(aux_product, sizeof(Product), 1, file);

                printf("\nProduto deletado com sucesso.\n");
            }
        }

        fclose(file);

        free(aux_product);
    }
}

int confirm_product_delete(Product* product) {
    char op;

    terminal_clear();

    show_product(product);

    printf("\nTem certeza que deseja excluir este produto? (s/n): ");
    op = read_alpha_op();

    if (tolower(op) == 's') {
        return 1;
    }

    return 0;
}

void delete_product(void) {
    Product* product;

    char* product_code = delete_product_screen();

    if (search_product(product_code) != NULL) {
        product = search_product(product_code);

        delete_product_file(product);

        free(product);
    }

    else {
        printf("\nProduto nao encontrado ou inexistente.\n");
    }

    free(product_code);
}

char* delete_product_screen(void) {
    terminal_clear();

    char* product_code = (char*) malloc(20 * sizeof(char));

    printf("\t\t========================================\n");
    printf("\t\t||                                    ||\n");
    printf("\t\t||            ------------            ||\n");
    printf("\t\t||            SIG-Customer            ||\n");
    printf("\t\t||            ------------            ||\n");
    printf("\t\t||                                    ||\n");
    printf("\t\t========================================\n");
    printf("\n");
    printf("\t\t========================================\n");
    printf("\t\t||          Deletar Produtos          ||\n");
    printf("\t\t========================================\n");

    printf("\nDigite o codigo do produto: ");
    read_product_code(product_code);

    return product_code;
}

void mod_product(void) {
    int op = menu_product();
    
    while (op != 0) {
        switch (op) {
            case 1:
                create_product();
                
                break;

            case 2:
                find_product();
                
                break;
                
            case 3:
                update_product();
                
                break;
                
            case 4:
                delete_product();
                
                break;
                
            default:
                printf("\nOpcao invalida. Por favor, digite uma opcao valida\n");
                
                break;
        }
        
        press_enter_to_continue();
        
        op = menu_product();
    }
}
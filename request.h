typedef struct st_request Request;

struct st_request {
    char id[50];
    char date[100];
    char customer_cpf[20];
    char product_code[20];
    char quantity[10];
    int deleted;
};

char menu_request(void);
void mod_request(void);
void create_request(void);
void save_request(Request* request);
Request* search_request(char *id);
Request* create_request_screen(void);
void find_request(void);
char* search_request_screen(void);
void update_request_screen(void);
void delete_request_screen(void);
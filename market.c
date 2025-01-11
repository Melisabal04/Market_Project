#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int password();
int lower_word();
int search();
int product_add();
int menu();
int ask_admin();

struct Market
{
    char name[20];
    float price;
    char category[20];
    int stock;
    long long barkod;
};


int main(){
    menu();   
    printf("Sucessfull!");
    return 0;
}

int password()
{
    int num,num2;
    char name[50];
    long long user_password,stored_password,new_password;
    FILE *dosya2=fopen("password.txt","a+");
    printf("What do you want?\n1)Sign in with an existing account\n2)Create new account.");
    scanf("%d",&num);
    FILE *readFile = fopen("password.txt", "r");
    if(num==1)
    {
       printf("enter your password: ");
       scanf("%lld",&user_password);
       rewind(dosya2);
       int found = 0;
       while (fscanf(readFile, "%*[^-]- %lld\n", &stored_password) != EOF) 
       {
            if (user_password == stored_password) 
            {
                printf("Login successful!\n");
                found = 1;
                return 1;
                break;
            }
        }
        
        fclose(readFile);

        if (found==0) 
        {
            printf("Invalid password.\n1) Try again\n2) Exit\n");
            scanf("%d", &num2);
            if (num2 == 1) {
                fclose(dosya2);
                return password();
            } else if (num2 == 2) {
                fclose(dosya2);
                return 0;
            }
        }
        
    }
    if(num==2)
    {

        if(ask_admin()==1)
        {   
            rewind(dosya2);
            getchar();
            printf("Please enter your name and surname: ");
            fgets(name,sizeof(name),stdin);
            printf("Please enter your password: ");
            scanf("%lld",&new_password);
            fprintf(dosya2,"%s - %lld\n",name,new_password);
            fclose(dosya2);
            return 1;
        }
        else 
        {
            printf("Invalid value.\n1) Try again\n2) Exit\n");
            scanf("%d",&num2);
            fclose(dosya2);
            if(num2==1) password();
            else if(num2==2) menu();
        }
    }
    else 
    {
        printf("Invalid values");
        fclose(dosya2);
        password();
    }
}

int ask_admin()
{
    long long admin_password, entered;
    admin_password=23800600;
    printf("Please enter the admin password: ");
    scanf("%lld",&entered);
    if(admin_password==entered)
    {
        printf("Success!");
        return 1;
    }
    else
    {
        printf("Incorrect password ");
        return 0;
    }
}

int menu()
{
    int n,choice;
    printf("1)Add Product\n2)Search Product\n What do you want to do?(1 or 2): ");
    scanf("%d",&n);
    switch (n) {
        case 1:
            if (product_add() == 1) 
            {
                printf("Would you like to keep going? (yes=1, no=2): ");
                scanf("%d", &choice);
                if (choice == 1) menu();
                else return 0;
            }
            break;

        case 2:
            search();
            break;

        default:
            printf("Invalid value. Try again.\n");
            menu();
            break;
    }
    return 0;
}

int lower_word(char *product)
{
    for (int i = 0; product[i]; i++) {
        if (product[i] >= 'A' && product[i] <= 'Z') {
            product[i] = product[i] + ('a' - 'A');
        }
    }
    return 1;
}

int product_add()
{
    if (password()!=1)
    {   
        printf("Unauthorized access. Exiting...\n");
        return 0;
    }

        int p_num=0;
        FILE *dosya;
        dosya=fopen("product_info.txt","a+");

        int start = 0;
        char line[100];
        while (fgets(line, sizeof(line), dosya))
        {
            int temp;
            if (sscanf(line, "%d)", &temp) == 1) 
            {
                 if (temp > start) 
                {
                    start = temp;
                }
            }
        }
        start++;

        printf("How many different product will you enter?\n");
        scanf("%d",&p_num);
        getchar();
        struct Market *product = (struct Market *)malloc((p_num + start)* sizeof(struct Market));

        
        for(int i=0;i<p_num;i++)
        {
            printf("%d. Product Name: ",i+1);
            fgets(product[i].name,sizeof(product[i].name),stdin);
            product[i].name[strcspn(product[i].name, "\n")] = '\0';
            printf("%d. Price: ",i+1);
            scanf("%f",&product[i].price);
            getchar();
            printf("%d. Category: ",i+1);
            fgets(product[i].category,sizeof(product[i].category),stdin);
            product[i].category[strcspn(product[i].category, "\n")] = '\0';
            printf("%d. Stock: ",i+1);
            scanf("%d",&product[i].stock);
            getchar();
            printf("%d. Barkod: ",i+1);
            scanf("%lld",&product[i].barkod);
            getchar();

            lower_word(product[i].name);

            fprintf(dosya, "%d)Product Name: %s\n",start+i, product[i].name);
            fprintf(dosya, "%d)Price: %.2f\n",start+i, product[i].price);
            fprintf(dosya, "%d)Category: %s\n",start+i, product[i].category);
            fprintf(dosya, "%d)Stock: %d\n",start+i, product[i].stock);
            fprintf(dosya, "%d)Barkod Num: %lld\n",start+i, product[i].barkod);
            
        }
        free(product);
        fclose(dosya);
        return 1;
    
}

int search()
{
    
    char searching_product[20];
    char line[100];
    int found=0;
    FILE *dosya;
    dosya=fopen("product_info.txt","r");
    printf("Enter the product name that you want to search: ");
    getchar();
    fgets(searching_product,19,stdin);
    lower_word(searching_product);

    while(fgets(line,sizeof(line),dosya))
    {
        if(strstr(line,searching_product))
        {
            printf("\nProduct Found:\n%s",line);
            found = 1;
            for (int i = 0; i < 4; i++) 
            {
                if (fgets(line, sizeof(line), dosya)) 
                {
                    printf("%s", line);
                } 
                else 
                {
                    break;
                }
            }
        }
    }

    fclose(dosya);
    if (!found) printf("Product not found.\n");
    return found;
}
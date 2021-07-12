#include <product_controller.h>

void simpleView(Product *prod, unsigned int *total ,unsigned int *viewLimit, unsigned int target){
    target++;
    unsigned int remain = ((target) % *viewLimit); // the exact number on the list of the current page
    unsigned int page = (target / *viewLimit) ; // current page of the target product
    unsigned int totalPage = (*total > *viewLimit) ? (remain > 0) ? (*total/ *viewLimit + 1): (*total / *viewLimit) : 1 ;
    unsigned int start = (remain > 0) ? page * (*viewLimit) : (page - 1) * (*viewLimit);

    unsigned int end = ((totalPage == page + 1) ? (start + remain) : (start + *viewLimit));
    end = (*total > *viewLimit) ? end : target;



    printf(" \t\t\t***** INVENTORY *****\n");
    printf("------------------------------------------------------------------\n");
    printf("S.N.|    %-5s|  %-10s|  %-10s| %-10s|  %-10s|\n", "ID", "Name", "Genre", "Quantity", "Price");
    printf("------------------------------------------------------------------\n");

    for (int i = start; i < end; i++)
    {
        (i == target-1) ?
            printf("%-4d|    %-5d|  %-10s|  %-10s| %-10d|  %-10.2f| UPDATED\n", i + 1, prod[i].id, prod[i].name, prod[i].genre, prod[i].quantity, prod[i].price) :
            printf("%-4d|    %-5d|  %-10s|  %-10s| %-10d|  %-10.2f|\n", i + 1, prod[i].id, prod[i].name, prod[i].genre, prod[i].quantity, prod[i].price);
        
    }
    printf("------------------------------------------------------------------\n\n");
    printf("target : %d\n", target);
    printf("Total : %d\n", *total);
    printf("Page : %d\n", page);
    printf("remain : %d\n", remain);
    printf("totalPage : %d\n", totalPage);
    printf("start : %d\n", start);
    printf("end : %d\n", end);
}

void listProduct(Product *prod, unsigned int *total, unsigned int *viewLimit)
{
    char input[10];

    // Default configuration for first page
    unsigned int remain = *total % *viewLimit;
    unsigned int page = 0;
    unsigned int start = 0;
    unsigned int end = (*total > *viewLimit) ? *viewLimit : *total ; // [left] multi page : [right] single page

    unsigned int totalPage = (*total > *viewLimit) ? ((remain > 0) ? ((*total / *viewLimit) + 1) : (*total / *viewLimit)) : 1 ;

    unsigned int state = 1;

    if (*total == 0)
    {
        printf("No products to view\n");
        return;
    }


    while(state){
        printf("Total Pages : %d\n", totalPage);
        printf(" \t\t\t***** INVENTORY *****\n");
        printf("------------------------------------------------------------------\n");
        printf("S.N.|    %-5s|  %-10s|  %-10s| %-10s|  %-10s|\n", "ID", "Name", "Genre", "Quantity", "Price");
        printf("------------------------------------------------------------------\n");

        for (unsigned int i = start; i < end; i++)
        {
            printf("%-4d|    %-5d|  %-10s|  %-10s| %-10d|  %-10.2f|\n", i + 1, prod[i].id, prod[i].name, prod[i].genre, prod[i].quantity, prod  [i].price);
        }
        printf("------------------------------------------------------------------\n\n"); 
        
        // Asking for pages to view only if
        if(*total > *viewLimit){
            printf("Current Page : %d\n", page + 1);
            printf("Which page to view: ");
            unsigned int ask = 1;
            while (ask)
            {
                fgets(input, 10, stdin);
                if(*input == '\n'){
                    ask = 0; // leave the ask loop [get input]
                    state = 0; // leave the state loop [view page]
                    break;
                }
                input[strcspn(input, "\n")] = 0;
                if(atoi(input) == 0 || atoi(input) > totalPage){
                    printf("Invalid input ! Enter again : ");
                    ask = 1;
                }else{
                    page = atoi(input)-1;
                    ask = 0;
                }
            }

            start = (page) * (*viewLimit);
            end = (remain > 0) ? (start + remain) : (start + *viewLimit);
            end = (totalPage == page+1) ? end : (start + (*viewLimit));

        }else{
            state = 0;
        }
    }
    
}

void addProduct(Product *prod, unsigned int *total, unsigned int *uid, unsigned int *viewLimit)
{
    printf("UID: %d\n", *uid);
    prod[*total].id = *uid + 1;

    printf("Product Name: ");
    gets(prod[*total].name);
    while(strcmp(prod[*total].name,"")==0){
        printf("Product Name cannot be left empty ! Enter again : ");
        gets(prod[*total].name);
    }

    printf("Product Genre: ");
    gets(prod[*total].genre);
    while(strcmp(prod[*total].genre,"")==0){
        printf("Product Genre cannot be left empty ! Enter again : ");
        gets(prod[*total].genre);
    }

    printf("Product Quantity: ");
    getDigit(&prod[*total].quantity);

    printf("Product Price: ");
    getFloat(&prod[*total].price);

    unsigned int target = (*total);
    (*total)++;
    (*uid)++;
    simpleView(prod, total, viewLimit, target);
    // listProduct(prod, total, viewLimit);
    writeCSV(prod, total);
}

void deleteProduct(Product *prod, unsigned int *total, unsigned int *viewLimit)
{
    unsigned int id;
    unsigned int exist = 0;
    listProduct(prod, total, viewLimit);
    printf("Please select the ID of the product to delete : ");
    getDigit(&id);

    for (int i = 0; i < *total; i++)
    {
        
        // (prod[i].id == id)  ? (exist = 1) : -1;
        // (exist==1) ? prod[i] = prod[i + 1] : prod[i];

        if (prod[i].id == id)
            exist = 1;
        if (exist)
            prod[i] = prod[i + 1];
    }

    if (exist)
    {
        printf("Product with ID %d deleted successfully\n", id);
        (*total)--;
    }
    else
    {
        printf("Product with ID %d does not exist.\n", id);
    }
    unsigned int result;
    result = (exist == 1) ? (*total) - 1 && printf("Product with ID %d deleted successfully\n", id) : printf("Product with ID %d does not exist.\n", id);
    printf("Result : %d\n", result);
    writeCSV(prod, total);
}

void updateProduct(Product *prod, unsigned int *total, unsigned int *viewLimit)
{
    unsigned int id;
    unsigned int exist = 0;
    unsigned int item;
    char input[128];

    listProduct(prod, total, viewLimit);
    printf("Please select the ID of the product to update : ");
    getDigit(&id);

    for (int i = 0; i < *total; i++)
    {
        if (prod[i].id == id)
        {
            exist = 1;
            item = i;
            break;
        }
    }
    if (exist)
    {
        prod[item].id = id;
        printf("- Type 'Enter' to skip and the data will remain the same.\n");
        printf("%22s%10s -> %-10s\n", "", "[Old]", "[New]");
        printf("%-20s: %10s -> ", "Product Name", prod[item].name);
        // fflush(stdin);
        fgets(input, 100, stdin);
        if (*input != '\n')
        {
            input[strcspn(input, "\n")] = 0;
            strcpy(prod[item].name, input);
        }

        printf("%-20s: %10s -> ", "Product Genre", prod[item].genre);
        // fflush(stdin);
        fgets(input, 100, stdin);
        if (*input != '\n')
        {
            input[strcspn(input, "\n")] = 0;
            strcpy(prod[item].genre, input);
        }

        printf("%-20s: %10d -> ", "Product Quantity", prod[item].quantity);
        // fflush(stdin);
        fgets(input, 100, stdin);
        if (*input != '\n')
        {
            input[strcspn(input, "\n")] = 0;
            if (atoi(input) == 0)
            {
                printf("Invalid input ! Enter again : ");
                getDigit(&prod[item].quantity);
            }
            else
            {
                prod[item].quantity = atoi(input);
            }
        }

        printf("%-20s: %10.2f -> ", "Product Price", prod[item].price);
        // fflush(stdin);
        fgets(input, 100, stdin);
        if (*input != '\n')
        {
            input[strcspn(input, "\n")] = 0;
            if (atof(input) == 0)
            {
                printf("Invalid input ! Enter again : ");
                getFloat(&prod[item].price);
            }
            else
            {
                prod[item].price = atof(input);
            }
        }

        printf("Product with ID %d updated successfully.\n", id);
    }
    else
    {
        printf("Product with ID %d does not exist.\n", id);
    }
    simpleView(prod, total, viewLimit, item);
    writeCSV(prod, total);
}

void searchProduct(Product *prod, unsigned int *total, unsigned int *viewLimit ,unsigned int action)
{
    unsigned size = *viewLimit;
    Product *result = (Product *)malloc((size) * sizeof(Product));
    unsigned int digit;
    char string[128];
    float number = 0;
    unsigned int *k = (unsigned int *)malloc(sizeof(unsigned int));
    *k = 0;

    if (action == 1)
    {
        printf("ID : ");
        getDigit(&digit);

        for (int i = 0; i < *total; i++)
        {
            if (prod[i].id == digit)
            {
                result[*k] = prod[i];
                (*k)++;
                if(*k >= size){
                    size++;
                    result = realloc(result, ((size) * sizeof(Product)));
                }
            }
        }
        listProduct(result, k, viewLimit);
        *k = 0;
    }
    else if (action == 2)
    {
        printf("Name : ");
        fflush(stdin);
        gets(string);

        for (int i = 0; i < *total; i++)
        {
            if (strcmp(prod[i].name, string) == 0)
            {
                result[*k] = prod[i];
                (*k)++;
                if(*k >= size){
                    size++;
                    result = realloc(result, ((size) * sizeof(Product)));
                }
            }
        }
        listProduct(result, k, viewLimit);
        *k = 0;
    }
    else if (action == 3)
    {
        printf("Genre : ");
        fflush(stdin);
        gets(string);

        for (int i = 0; i < *total; i++)
        {
            if (strcmp(prod[i].genre, string) == 0)
            {
                result[*k] = prod[i];
                (*k)++;
                if(*k >= size){
                    size++;
                    result = realloc(result, ((size) * sizeof(Product)));
                }
            }
        }
        listProduct(result, k, viewLimit);
        *k = 0;
    }
    else if (action == 4)
    {
        printf("Quantity : ");
        getDigit(&digit);

        for (int i = 0; i < *total; i++)
        {
            if (prod[i].quantity == digit)
            {
                result[*k] = prod[i];
                (*k)++;
                if(*k >= size){
                    size++;
                    result = realloc(result, ((size) * sizeof(Product)));
                }
            }
        }
        listProduct(result, k, viewLimit);
        *k = 0;
    }
    else if (action == 5)
    {
        printf("Price : ");
        getFloat(&number);

        for (int i = 0; i < *total; i++)
        {
            if (prod[i].price == number)
            {
                result[*k] = prod[i];
                (*k)++;
                if(*k >= size){
                    size++;
                    result = realloc(result, ((size) * sizeof(Product)));
                }
            }
        }
        listProduct(result, k, viewLimit);
        *k = 0;
    }
    free(k);
    free(result);
}

Product *initiate(Product *prod, unsigned int *total, unsigned int *uid, unsigned int *size,unsigned int *viewLimit)
{
    readINI(viewLimit);

    *total = totalProductCSV();
    *size = *total + 1;
    prod = (Product *)malloc((*size) * sizeof(Product));
    readCSV(prod);
    *uid = (*total == 0) ? 0 : prod[*total-1].id;
    return prod;
}


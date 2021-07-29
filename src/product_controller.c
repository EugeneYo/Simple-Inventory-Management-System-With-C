#include <product_controller.h>

void simpleView(Product *prod, unsigned int *total ,unsigned int *viewLimit, unsigned int target, unsigned int type){
    target++;
    unsigned int remain = (target % *viewLimit); // the exact number on the list of the current page
    unsigned int lastPageRemain = *total % *viewLimit;
    unsigned int page = (remain > 0) ? (target / *viewLimit + 1) :  (target / *viewLimit) ; // current page of the target product

    unsigned int totalPage = *total / *viewLimit;
    totalPage = ( lastPageRemain > 0) ? totalPage + 1 : totalPage;

    unsigned int start =  (page - 1) * (*viewLimit);

    unsigned int end = (lastPageRemain == 0) ? start + *viewLimit : start + lastPageRemain;
    end = (totalPage == page ) ?  end :start + *viewLimit; // 'end' depends on target's page

    // printf("Target : %d\n", target);
    // printf("remain : %d\n", remain);
    // printf("page : %d\n", page);
    // printf("total : %d\n", *total);
    // printf("totalPage : %d\n", totalPage);
    // printf("lastPageRemain : %d\n", lastPageRemain);
    // printf("start : %d\n", start);
    // printf("end : %d\n", end);



    printf(CYN" \t\t\t***** INVENTORY *****\n" reset);
    printf("------------------------------------------------------------------\n");
    printf("S.N.|    %-5s|  %-10s|  %-10s| %-10s|  %-10s|\n", "ID", "Name", "Category", "Quantity", "Price");
    printf("------------------------------------------------------------------\n");

    for (int i = start; i < end; i++)
    {
        // (i == target-1) ?
        //     (type == 0) ?
        //     printf(GRN "%-4d|    %-5d|  %-10s|  %-10s| %-10d|  %-10.2f| ADDED\n" reset, i + 1, prod[i].id, prod[i].name, prod[i].category, prod[i].quantity, prod[i].price) : 
        //     printf(GRN "%-4d|    %-5d|  %-10s|  %-10s| %-10d|  %-10.2f| UPDATED\n" reset, i + 1, prod[i].id, prod[i].name, prod[i].category, prod[i].quantity, prod[i].price) :
        //     printf("%-4d|    %-5d|  %-10s|  %-10s| %-10d|  %-10.2f|\n", i + 1, prod[i].id, prod[i].name, prod[i].category, prod[i].quantity, prod[i].price);
        
        if(i == target - 1){
            if(type == 0){
                printf(GRN "%-4d|    %-5d|  %-10s|  %-10s| %-10d|  %-10.2f| ADDED\n" reset, i + 1, prod[i].id, prod[i].name, prod[i].category, prod[i].quantity, prod[i].price);
            }else if (type == 1){
                printf(GRN "%-4d|    %-5d|  %-10s|  %-10s| %-10d|  %-10.2f| UPDATED\n" reset, i + 1, prod[i].id, prod[i].name, prod[i].category, prod[i].quantity, prod[i].price);
            }else{
                printf(RED "%-4d|    %-5d|  %-10s|  %-10s| %-10d|  %-10.2f| DELETED\n" reset, 0, 0, "Product", "is Null", 0, 0.00);
                printf("%-4d|    %-5d|  %-10s|  %-10s| %-10d|  %-10.2f|\n", i + 1, prod[i].id, prod[i].name, prod[i].category, prod[i].quantity, prod[i].price);
            }
        }else{
            printf("%-4d|    %-5d|  %-10s|  %-10s| %-10d|  %-10.2f|\n", i + 1, prod[i].id, prod[i].name, prod[i].category, prod[i].quantity, prod[i].price);
        }
        
    }
    printf("------------------------------------------------------------------\n\n");

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
        printf(RED"No products to view\n" reset);
        printf("Press enter to continue...");
        int c = getchar();
        ClearScreen();
        return;
    }


    while(state){
        printf(CYN" \t\t\t***** INVENTORY *****\n"reset);
        printf("------------------------------------------------------------------\n");
        printf("S.N.|    %-5s|  %-10s|  %-10s| %-10s|  %-10s|\n", "ID", "Name", "Category", "Quantity", "Price");
        printf("------------------------------------------------------------------\n");

        for (unsigned int i = start; i < end; i++)
        {
            printf("%-4d|    %-5d|  %-10s|  %-10s| %-10d|  %-10.2f|\n", i + 1, prod[i].id, prod[i].name, prod[i].category, prod[i].quantity, prod  [i].price);
        }
        printf("------------------------------------------------------------------\n\n"); 
        
        // Asking for pages to view only if
        if(*total > *viewLimit){
            printf("Current Page : "YEL"%-34d"reset" Total Pages: "RED"%d\n"reset, page+1 ,totalPage);
            printf("Which page to view (Enter nothing to skip): ");
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
                    printf(RED "Invalid Input !" reset " Enter again : ");
                    ask = 1;
                }else{
                    page = atoi(input)-1;
                    ask = 0;
                    ClearScreen();

                }
            }

            start = (page) * (*viewLimit);
            end = (remain > 0) ? (start + remain) : (start + *viewLimit);
            end = (totalPage == page+1) ? end : (start + (*viewLimit));

        }else{
            state = 0;
            printf("Press enter to continue...");
            int c = getchar();
            ClearScreen();
        }
    }
}

void addProduct(Product *prod, unsigned int *total, unsigned int *uid, unsigned int *viewLimit)
{
    prod[*total].id = *uid + 1;
    printf("UID: %d\n",prod[*total].id);

    printf("Product Name: ");
    gets(prod[*total].name);
    while(strcmp(prod[*total].name,"")==0){
        printf(RED"Product Name cannot be left empty !"reset" Enter again : ");
        gets(prod[*total].name);
    }

    printf("Product Category: ");
    gets(prod[*total].category);
    while(strcmp(prod[*total].category,"")==0){
        printf(RED"Product category cannot be left empty !"reset" Enter again : ");
        gets(prod[*total].category);
    }

    printf("Product Quantity: ");
    getDigit(&prod[*total].quantity);

    printf("Product Price: ");
    getFloat(&prod[*total].price);

    unsigned int target = (*total);
    (*total)++;
    (*uid)++;
    
    ClearScreen();
    simpleView(prod, total, viewLimit, target, 0);
    printf(GRN"Product with ID %d added successfully\n\n"reset, prod[*total - 1].id);

    printf("Press enter to continue...");
    int c = getchar();
    ClearScreen();
    // listProduct(prod, total, viewLimit);
    writeCSV(prod, total);
}

void deleteProduct(Product *prod, unsigned int *total, unsigned int *viewLimit)
{
    unsigned int id;
    unsigned int exist = 0;
    unsigned int item = 0;
    listProduct(prod, total, viewLimit);
    printf("Please select the ID of the product to delete : ");
    getDigit(&id);

    for (int i = 0; i < *total; i++)
    {
        if (prod[i].id == id){
            exist = 1;
            item = i;
        }
        if (exist)
            prod[i] = prod[i + 1];
    }

    if (exist)
    {
        ClearScreen();
        (*total)--;
        writeCSV(prod, total);
        simpleView(prod, total, viewLimit, item, 2);
        printf(CYN"Product with ID %d deleted successfully\n"reset, id);

        printf("\nPress enter to continue...");
        int c = getchar();
        ClearScreen();
    }
    else
    {
        printf(RED"Product with ID %d does not exist.\n"reset, id);
        printf("\nPress enter to continue...");
        int c = getchar();
        ClearScreen();
    }
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
        printf("%22s"YEL"%10s"reset" -> "CYN"%-10s"reset"\n", "", "[Old]", "[New]");
        printf("%-20s: "YEL"%10s"reset" -> "CYN, "Product Name", prod[item].name);
        // fflush(stdin);
        fgets(input, 100, stdin);
        if (*input != '\n')
        {
            input[strcspn(input, "\n")] = 0;
            strcpy(prod[item].name, input);
        }

        printf(reset"%-20s: "YEL"%10s"reset" -> "CYN, "Product Category", prod[item].category);
        // fflush(stdin);
        fgets(input, 100, stdin);
        if (*input != '\n')
        {
            input[strcspn(input, "\n")] = 0;
            strcpy(prod[item].category, input);
        }

        printf(reset"%-20s: "YEL"%10d"reset" -> "CYN, "Product Quantity", prod[item].quantity);
        // fflush(stdin);
        fgets(input, 100, stdin);
        if (*input != '\n')
        {
            input[strcspn(input, "\n")] = 0;
            if (atoi(input) == 0)
            {
                printf(RED"Invalid input !"reset" Enter again : "CYN);
                getDigit(&prod[item].quantity);
            }
            else
            {
                prod[item].quantity = atoi(input);
            }
        }

        printf(reset"%-20s: "YEL"%10.2f"reset" -> "CYN, "Product Price", prod[item].price);
        // fflush(stdin);
        fgets(input, 100, stdin);
        if (*input != '\n')
        {
            input[strcspn(input, "\n")] = 0;
            if (atof(input) == 0)
            {
                printf(RED"Invalid input !"reset" Enter again : "CYN);
                getFloat(&prod[item].price);
            }
            else
            {
                prod[item].price = atof(input);
            }
        }

        printf(reset);
        ClearScreen();
        simpleView(prod, total, viewLimit, item, 1);
        printf(GRN"Product with ID %d updated successfully.\n"reset, id);

        printf("\nPress enter to continue...");
        int c = getchar();
        ClearScreen();
    }
    else
    {
        printf(RED"Product with ID %d does not exist.\n"reset, id);
        printf("\nPress enter to continue...");
        int c = getchar();
        ClearScreen();
    }
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
        printf("Category : ");
        fflush(stdin);
        gets(string);

        for (int i = 0; i < *total; i++)
        {
            if (strcmp(prod[i].category, string) == 0)
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


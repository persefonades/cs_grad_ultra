#include <stdio.h>
#include <stdlib.h>

typedef struct product {
        char* name;
        int qty;
        float price, amt;
} item;

int main(int argc, char const *argv[]) {
        float price, total = 0;
        int items, i, qty;
        char* name;
        scanf("%d\n", &items);
        item products[items];
        for (i = 0; i < items; i++) {
                char* name = (char*)malloc(100 * sizeof(char));
                scanf("%s %d %f", name, &qty, &price);
                products[i].name = name;
                products[i].qty = qty;
                products[i].price = price;
                products[i].amt = products[i].qty * products[i].price;
                total += products[i].amt;
        }
        printf("******************** B I L L ********************\n");
        printf("–––––––––––––––––––––––––––––––––––––––––––––––––\n");
        printf("%-16s%-12s%-12s%-12s\n", "Item", "Quantity", "Price", "Amount");
        printf("–––––––––––––––––––––––––––––––––––––––––––––––––\n");
        for (i = 0; i < items; i++) {
                printf("%-16s%4d%14.2f%12.2f\n",
                       products[i].name, products[i].qty, products[i].price, products[i].amt);
        }
        printf("–––––––––––––––––––––––––––––––––––––––––––––––––\n");
        printf("Total Amount to be paid: %12.2f\n", total);
        printf("–––––––––––––––––––––––––––––––––––––––––––––––––\n");
        return 0;
}

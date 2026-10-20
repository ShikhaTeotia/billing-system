
#include <stdio.h>

#define MAX_ITEMS 50
#define GST_RATE 18.0f

typedef struct {
    const char *name;
    float price;
} Product;

typedef struct {
    int product;
    int qty;
    float amount;
} BillItem;

static void clearInput(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void)
{
    Product products[] = {
        {"Laptop", 50000}, {"Mouse", 500}, {"Keyboard", 1000},
        {"Printer", 8000}, {"Pen Drive", 700}
    };
    int numProducts = sizeof(products) / sizeof(products[0]);
    BillItem bill[MAX_ITEMS];
    int count = 0;
    float total = 0;
    char more = 'Y';

    printf("=====================================\n");
    printf("      BILLING SYSTEM WITH DISCOUNT\n");
    printf("=====================================\n");

    do {
        int choice, qty;

        printf("\nProduct List\n");
        for (int i = 0; i < numProducts; i++)
            printf("%d. %-10s Rs.%.2f\n", i + 1, products[i].name, products[i].price);

        printf("\nEnter Product Choice: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > numProducts) {
            clearInput();
            printf("Invalid choice! Try again.\n");
            continue;
        }

        printf("Enter Quantity: ");
        if (scanf("%d", &qty) != 1 || qty <= 0) {
            clearInput();
            printf("Invalid quantity! Try again.\n");
            continue;
        }

        if (count == MAX_ITEMS) {
            printf("Bill is full!\n");
            break;
        }

        bill[count].product = choice - 1;
        bill[count].qty = qty;
        bill[count].amount = products[choice - 1].price * qty;
        total += bill[count].amount;
        printf("Item Amount = Rs.%.2f\n", bill[count].amount);
        count++;

        printf("\nAdd More Items (Y/N): ");
        scanf(" %c", &more);
    } while (more == 'Y' || more == 'y');

    if (count == 0) {
        printf("\nNo items purchased.\n");
        return 0;
    }

    float discountRate;
    if (total >= 100000)      discountRate = 20;
    else if (total >= 50000)  discountRate = 15;
    else if (total >= 20000)  discountRate = 10;
    else if (total >= 10000)  discountRate = 5;
    else                      discountRate = 0;

    float discountAmount = total * discountRate / 100;
    float netAmount = total - discountAmount;
    float gst = netAmount * GST_RATE / 100;
    float grandTotal = netAmount + gst;

    printf("\n=====================================\n");
    printf("              FINAL BILL\n");
    printf("=====================================\n");
    printf("%-12s %5s %12s\n", "Item", "Qty", "Amount");
    for (int i = 0; i < count; i++)
        printf("%-12s %5d %12.2f\n", products[bill[i].product].name,
               bill[i].qty, bill[i].amount);
    printf("-------------------------------------\n");
    printf("Total Amount          : Rs.%.2f\n", total);
    printf("Discount (%.0f%%)        : Rs.%.2f\n", discountRate, discountAmount);
    printf("Amount After Discount : Rs.%.2f\n", netAmount);
    printf("GST (%.0f%%)             : Rs.%.2f\n", GST_RATE, gst);
    printf("Grand Total           : Rs.%.2f\n", grandTotal);
    printf("=====================================\n");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100
struct Item {
    int id;
    char name[50];
    int quantity;
    float price;
    int day, month, year;
};
struct Item inventory[MAX];
int count = 0;
void addItem();
void displayItems();
void updateItem();
void deleteItem();
void saveToFile();
void loadFromFile();
void lowStockAlert();
void totalStockValue();
void expiryCheck();

void addItem() {
    printf("\nEnter Item ID: ");
    scanf("%d", &inventory[count].id);

    printf("Enter Item Name: ");
    scanf("%s", inventory[count].name);

    printf("Enter Quantity: ");
    scanf("%d", &inventory[count].quantity);

    printf("Enter Price: ");
    scanf("%f", &inventory[count].price);

    printf("Enter Expiry Date (DD MM YYYY): ");
    scanf("%d %d %d",
          &inventory[count].day,
          &inventory[count].month,
          &inventory[count].year);

    count++;
    printf("\nItem Added Successfully!\n");
}
void displayItems() {
    int i;
    if(count == 0) {
        printf("\nNo Items Available!\n");
        return;
    }
    printf("\n================ INVENTORY LIST ================\n");
    printf("ID\tName\tQty\tPrice\tExpiry Date\n");
    for(i = 0; i < count; i++) {
        printf("%d\t%s\t%d\t%.2f\t%d/%d/%d\n",
               inventory[i].id,
               inventory[i].name,
               inventory[i].quantity,
               inventory[i].price,
               inventory[i].day,
               inventory[i].month,
               inventory[i].year);
    }
}
void updateItem() {
    int id, i, found = 0;
    printf("\nEnter Item ID to Update: ");
    scanf("%d", &id);
    for(i = 0; i < count; i++) {
        if(inventory[i].id == id) {
            found = 1;
            printf("Enter New Quantity: ");
            scanf("%d", &inventory[i].quantity);
            printf("Enter New Price: ");
            scanf("%f", &inventory[i].price);
            printf("\nItem Updated Successfully!\n");
            break;
        }
    }
    if(!found) {
        printf("\nItem Not Found!\n");
    }
}
void deleteItem() {
    int id, i, j, found = 0;
    printf("\nEnter Item ID to Delete: ");
    scanf("%d", &id);
    for(i = 0; i < count; i++) {
        if(inventory[i].id == id) {
            found = 1;
            for(j = i; j < count - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            count--;
            printf("\nItem Deleted Successfully!\n");
            break;
        }
    }
    if(!found) {
        printf("\nItem Not Found!\n");
    }
}
void saveToFile() {
    FILE *fp;
    fp = fopen("inventory.txt", "w");
    if(fp == NULL) {
        printf("\nFile Error!\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(inventory, sizeof(struct Item), count, fp);
    fclose(fp);
    printf("\nData Saved Successfully!\n");
}
void loadFromFile() {
    FILE *fp;
    fp = fopen("inventory.txt", "r");
    if(fp == NULL) {
        return;
    }
    fread(&count, sizeof(int), 1, fp);
    fread(inventory, sizeof(struct Item), count, fp);
    fclose(fp);
}
void lowStockAlert() {
    int i;
    printf("\n========== LOW STOCK ITEMS ==========" );
    for(i = 0; i < count; i++) {
        if(inventory[i].quantity < 5) {
            printf("\n%s (ID: %d) is Low in Stock! Qty = %d",
                   inventory[i].name,
                   inventory[i].id,
                   inventory[i].quantity);
        }
    }
    printf("\n");
}
void totalStockValue() {
    int i;
    float total = 0;
    for(i = 0; i < count; i++) {
        total += inventory[i].quantity * inventory[i].price;
    }
    printf("\nTotal Stock Value = %.2f\n", total);
}
void expiryCheck() {
    int i;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currentYear = tm.tm_year + 1900;
    int currentMonth = tm.tm_mon + 1;
    int currentDay = tm.tm_mday;
    printf("\n========== EXPIRY CHECK ==========" );
    for(i = 0; i < count; i++) {
        if(inventory[i].year < currentYear ||
          (inventory[i].year == currentYear && inventory[i].month < currentMonth) ||
          (inventory[i].year == currentYear && inventory[i].month == currentMonth && inventory[i].day <= currentDay)) {
            printf("\n%s (ID: %d) has Expired!",
                   inventory[i].name,
                   inventory[i].id);
        }
    }
    printf("\n");
}
int main() {
    int choice;
    loadFromFile();
    do {
        printf("\n========= INVENTORY MANAGEMENT SYSTEM =========\n");
        printf("1. Add Item\n");
        printf("2. Display Items\n");
        printf("3. Update Item\n");
        printf("4. Delete Item\n");
        printf("5. Save Data\n");
        printf("6. Low Stock Alert\n");
        printf("7. Total Stock Value\n");
        printf("8. Expiry Check\n");
        printf("9. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addItem();
                break;

            case 2:
                displayItems();
                break;

            case 3:
                updateItem();
                break;

            case 4:
                deleteItem();
                break;

            case 5:
                saveToFile();
                break;

            case 6:
                lowStockAlert();
                break;

            case 7:
                totalStockValue();
                break;

            case 8:
                expiryCheck();
                break;

            case 9:
                saveToFile();
                printf("\nThank You! Exiting Program...\n");
                break;

            default:
                printf("\nInvalid Choice! Please Try Again.\n");
        }

    } while(choice != 9);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

// CREATE ACCOUNT
void createAccount() {
    FILE *fp;
    struct Account acc;

    fp = fopen("bank.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acc.accNo);

    printf("Enter Name: ");
    scanf(" %[^\n]", acc.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("✅ Account created successfully!\n");
}

// DISPLAY ALL ACCOUNTS
void displayAccounts() {
    FILE *fp;
    struct Account acc;

    fp = fopen("bank.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n===== Account Records =====\n");

    while (fread(&acc, sizeof(acc), 1, fp)) {
        printf("Acc No: %d | Name: %s | Balance: %.2f\n",
               acc.accNo, acc.name, acc.balance);
    }

    fclose(fp);
}

// DEPOSIT
void deposit() {
    FILE *fp;
    struct Account acc;
    int accNo, found = 0;
    float amount;

    fp = fopen("bank.dat", "rb+");
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            acc.balance += amount;

            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);

            printf("✅ Deposit successful! Updated Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("❌ Account not found!\n");

    fclose(fp);
}

// WITHDRAW
void withdraw() {
    FILE *fp;
    struct Account acc;
    int accNo, found = 0;
    float amount;

    fp = fopen("bank.dat", "rb+");
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {

            if (acc.balance >= amount) {
                acc.balance -= amount;

                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);

                printf("✅ Withdrawal successful! Remaining Balance: %.2f\n", acc.balance);
            } else {
                printf("❌ Insufficient balance!\n");
            }

            found = 1;
            break;
        }
    }

    if (!found)
        printf("❌ Account not found!\n");

    fclose(fp);
}

// BALANCE ENQUIRY
void balanceEnquiry() {
    FILE *fp;
    struct Account acc;
    int accNo, found = 0;

    fp = fopen("bank.dat", "rb");
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("\n✅ Account Details:\n");
            printf("Acc No: %d\nName: %s\nBalance: %.2f\n",
                   acc.accNo, acc.name, acc.balance);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("❌ Account not found!\n");

    fclose(fp);
}

// MAIN FUNCTION
int main() {
    int choice;

    do {
        printf("\n===== Banking System =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Display All Accounts\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;

            case 2:
                deposit();
                break;

            case 3:
                withdraw();
                break;

            case 4:
                balanceEnquiry();
                break;

            case 5:
                displayAccounts();
                break;

            case 0:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 0);

    return 0;
}

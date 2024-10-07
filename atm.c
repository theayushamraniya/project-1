#include <stdio.h>

int main()
{
    float balance = 100000;
    int pin =  1603;
    int enteredpin;
    float amt;
    float deposit;
    while (1){
    printf("Welcome to an abc bank atm \n");
    printf("Enter your PIN: ");
    scanf("%d", &enteredpin);
     if(enteredpin == pin  )
    {
        printf("Login successful!\n");
        printf("Welcome MR. RAJESH SHAH\n");
        printf("Your balance is: %f\n", balance);

        int choice;
        printf("1. Withdrawal\n");
        printf("2. Deposit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

         switch (choice) {
            case 1:
                 printf("Enter your PIN: ");
                 scanf("%d", &enteredpin);
                if(enteredpin == pin  ){
                printf("Enter amount to withdraw: ");
                scanf("%f", &amt);
                if (amt > balance) {
                    printf("Insufficient balance!\n");
                } 
                else 
                {
                    balance-=amt;
                    printf("~~~~~~~~~~ AMOUNT DEPOSITED SUCCESSFULLY ~~~~~~~\n");
                    
                }
                }
                break;
            case 2:
               printf("Enter your PIN: ");
               scanf("%d", &enteredpin);
               if(enteredpin == pin  ){
               printf("enter the ammount that you want to deposit  ");
               scanf("%f", deposit);
               balance +=  deposit;
               printf("~~~~~~~~~~ AMOUNT DEPOSITED SUCCESSFULLY ~~~~~~~\n");
                break;
            }
         }
    }
    else 
    printf("you entered an incorrect pin \n enter a valid PIN ");
    }
 
    
}



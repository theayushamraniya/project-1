#include <stdio.h>
#include <string.h>

void signUp();
int login();
int isUsernameAvailable(char *username);
int isPasswordStrong(char *password);
void viewProducts();
void addToCart();
void viewCart();
float calculateTotal();+
void checkout();

struct user
{
    char userName[100];
    char password[100];
};

struct product
{
    int id;
    char name[100];
    float price;
    int quantity;
};

struct cartItem
{
    int productId;
    int quantity;
};

#define MAX_CART_ITEMS 10
struct cart
{
    struct cartItem items[MAX_CART_ITEMS];
    int itemCount;
};
struct cart userCart;

#define MAX_PRODUCTS 100
struct product products[MAX_PRODUCTS];
int productCount = 0;

int main()
{
    printf("\033[44m");
    printf("\033[1;44m**\033[0m\n");
    printf("\033[1;33m*            E-COMMERCE SYSTEM               *\033[0m\n");
    printf("\033[1;44m**\033[0m\n");

    int choice;
    printf("1. Sign-up\n2. Login\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        signUp();
    }
    else if (choice == 2)
    {
        if (login())
        {
            printf("\nWelcome to the e-commerce system!\n");
            while (1)
            {
                int choice;
                printf("\n1. View Products\n");
                printf("2. Add to Cart\n");
                printf("3. View Cart\n");
                printf("4. Checkout\n");
                printf("5. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    viewProducts();
                    break;
                case 2:
                    addToCart();
                    break;
                case 3:
                    viewCart();
                    break;
                case 4:
                    checkout();
                    break;
                case 5:
                    printf("Exiting....... .");
                    return 0;
                default:
                    printf("Invalid choice. Please enter valied choice.\n");
                    break;
                }
            }
        }
        else
        {
            printf("Please try again.\n");
        }
    }
    else
    {
        printf("Invalid choice!\n");
    }
    return 0;
}

int isUsernameAvailable(char *username)
{
    FILE *file = fopen("users.txt", "r");
    struct user storedName;

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 1; // File doesn't exist yet, so username is available
    }

    // Check if username already exists
    while (fscanf(file, "%s %s", storedName.userName, storedName.password) == 2)
    { // Ensure both fields are read
        if (strcmp(username, storedName.userName) == 0)
        {
            fclose(file);
            return 0; // Username already taken
        }
    }

    fclose(file);
    return 1; // Username is available
}

int isPasswordStrong(char *password)
{
    int length = strlen(password);
    int hasLetter = 0, hasDigit = 0;

    if (length < 8)
    {
        return 0; // Password too short
    }

    for (int i = 0; i < length; i++)
    {
        if ((password[i] >= 'A' && password[i] <= 'Z') || (password[i] >= 'a' && password[i] <= 'z'))
        {
            hasLetter = 1;
        }
        else if (password[i] >= '0' && password[i] <= '9')
        {
            hasDigit = 1;
        }
    }

    return hasLetter && hasDigit; // Must have both letters and digits
}

void signUp()
{
    struct user newUser;
    FILE *file = fopen("users.txt", "a"); // Open file in append mode

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    // Get user input
    printf("\nEnter username: ");
    scanf("%s", newUser.userName);

    if (!isUsernameAvailable(newUser.userName))
    {
        printf("Username already taken! Please choose a different one.\n");
        fclose(file);
        return;
    }

    // Get password input and validate
    do
    {
        printf("Enter password (min 8 characters, must include letters and numbers): ");
        scanf("%s", newUser.password);

        if (!isPasswordStrong(newUser.password))
        {
            printf("Password is too weak. Please try again.\n");
        }
        else
        {
            break;
        }

    } while (1);

    // Write user data to file
    fprintf(file, "%s %s\n", newUser.userName, newUser.password);

    printf("Sign-up successful!\n");
    fclose(file);
}

int login()
{
    struct user loginUser;
    struct user storedUser;

    FILE *file = fopen("users.txt", "r"); // Open file in read mode

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }

    // Get user input
    printf("\nEnter username: ");
    scanf("%s", loginUser.userName);
    printf("Enter password: ");
    scanf("%s", loginUser.password);

    // Check credentials against stored data
    while (fscanf(file, "%s %s", storedUser.userName, storedUser.password) == 2)
    { // Ensure both fields are read
        if (strcmp(loginUser.userName, storedUser.userName) == 0 && strcmp(loginUser.password, storedUser.password) == 0)
        {
            printf("Login successful!\n");
            fclose(file);
            return 1; // Login successful
        }
    }

    printf("Invalid username or password! Please try again.\n");
    fclose(file);
    return 0; // Login failed
}

void viewProducts()
{
    FILE *file = fopen("products.txt", "r");
    if (file == NULL)
    {
        printf("Could not open products.txt for reading.\n");
        return;
    }
    productCount = 0; // Reset product count
    while (fscanf(file, "%d,%99[^,],%f\n", &products[productCount].id, products[productCount].name, &products[productCount].price) == 3)
    {
        productCount++;
        if (productCount >= MAX_PRODUCTS)
        {
            break; // Prevent overflow
        }
    }

    fclose(file);

    if (productCount == 0)
    {
        printf("No products available.\n");
        return;
    }

    printf("Available Products:\n");
    printf("ID\tName\t\t\t\tPrice\n");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < productCount; i++)
    {
        printf("%d\t%-24s\t%.2f\n", products[i].id, products[i].name, products[i].price);
    }
}

void addToCart()
{
    int productId, quantity;
    printf("Enter the product ID to add to cart: ");
    scanf("%d", &productId);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    // Check if the product exists
    int found = 0;
    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == productId)
        {
            found = 1;
            if (userCart.itemCount < MAX_CART_ITEMS)
            {
                // Check if product is already in the cart
                for (int j = 0; j < userCart.itemCount; j++)
                {
                    if (userCart.items[j].productId == productId)
                    {
                        userCart.items[j].quantity += quantity;
                        printf("Updated %d of product ID %d in the cart.\n", quantity, productId);
                        return;
                    }
                }
                // Add new product to the cart
                userCart.items[userCart.itemCount].productId = productId;
                userCart.items[userCart.itemCount].quantity = quantity;
                userCart.itemCount++;
                printf("Added %d of product ID %d to the cart.\n", quantity, productId);
            }
            else
            {
                printf("Cart is full! Cannot add more items.\n");
            }
            return;
        }
    }

    if (!found)
    {
        printf("Product ID %d not found.\n", productId);
    }
}

void viewCart()
{
    if (userCart.itemCount == 0)
    {
        printf("Your cart is empty.\n");
        return;
    }

    printf("Your Cart:\n");
    printf("ID\tName\t\t\t\tPrice\tQuantity\n");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < userCart.itemCount; i++)
    {
        int productId = userCart.items[i].productId;
        for (int j = 0; j < productCount; j++)
        {
            if (products[j].id == productId)
            {
                printf("%d\t%-24s\t%.2f\t%6d\n", products[j].id, products[j].name, products[j].price, userCart.items[i].quantity);
                break;
            }
        }
    }
}

float calculateTotal()
{
    float total = 0.0;
    for (int i = 0; i < userCart.itemCount; i++)
    {
        int productId = userCart.items[i].productId;
        for (int j = 0; j < productCount; j++)
        {
            if (products[j].id == productId)
            {
                total += products[j].price * userCart.items[i].quantity;
                break;
            }
        }
    }
    return total;
}

void checkout()
{
    if (userCart.itemCount == 0)
    {
        printf("Your cart is empty. Cannot proceed to checkout.\n");
        return;
    }

    float total = calculateTotal();
    printf("Your total amount is: $%.2f\n", total);

    // Simulate payment processing
    char paymentConfirmation;
    printf("Do you want to proceed with the payment? (y/n): ");
    scanf(" %c", &paymentConfirmation);

    if (paymentConfirmation == 'y' || paymentConfirmation == 'Y')
    {
        // Save the bill to a file
        FILE *billFile = fopen("bill.txt", "a");
        if (billFile == NULL)
        {
            printf("Error saving bill. Payment failed.\n");
            return;
        }

        fprintf(billFile, "\n---------------------------------------------------\n");
        fprintf(billFile, "Bill Receipt\n");
        fprintf(billFile, "---------------------------------------------------\n");

        fprintf(billFile, "ID\tName\t\t\t\t\t\tPrice\tQuantity\tSubtotal\n");
        fprintf(billFile, "---------------------------------------------------\n");

        for (int i = 0; i < userCart.itemCount; i++)
        {
            int productId = userCart.items[i].productId;
            for (int j = 0; j < productCount; j++)
            {
                if (products[j].id == productId)
                {
                    float subtotal = products[j].price * userCart.items[i].quantity;
                    fprintf(billFile, "%d\t%-24s\t%.2f\t%6d\t\t%.2f\n",
                            products[j].id, products[j].name, products[j].price, userCart.items[i].quantity, subtotal);
                    break;
                }
            }
        }

        fprintf(billFile, "---------------------------------------------------\n");
        fprintf(billFile, "Total Amount: $%.2f\n", total);
        fprintf(billFile, "---------------------------------------------------\n");

        fclose(billFile);

        printf("Payment successful! Thank you for your purchase.\n");
        printf("A bill has been saved to 'bill.txt'.\n");

        // Clear the cart
        userCart.itemCount = 0;
    }
    else
    {
        printf("Payment cancelled.\n");
    }
}
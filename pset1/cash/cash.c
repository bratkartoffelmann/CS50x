#include <stdio.h>
#include <math.h>

int main(void)
{
    // get change form user input
    int change;
    int result;
    do {
        printf("Change owed: ");
        result = scanf("%i", &change);

        // Clear the input buffer in case of invalid input
        while (getchar() != '\n');

    } while (result != 1 || change <= 0);  // Ensure valid integer input and positive value


    // get coin values and no. of coins
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;
    int coins = 0;


    while (change != 0) {
        // check if change is larger than each coin (starting from the largest denomination)
        if (change >= quarter) {
            change -= quarter;
        } else if (change >= dime) {
            change -= dime;
        } else if (change >= nickel) {
            change -= nickel;
        } else if (change >= penny) {
            change -= penny;
        } 

        coins++;
    }

    printf("%i\n", coins);
}
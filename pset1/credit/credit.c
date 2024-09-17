#include <stdio.h>
#include <math.h>

int main(void)
{
    // get card number (between 13 and 20 digits)
    long card;
    do {
        printf("Number: ");
        scanf("%ld", &card);
    } while (!(card > 0));


    // get length of card
    int length;
    int div;
    for (int i = 20; i > 0; i--) {
        div = card / (long)pow(10, i-1);
        if (div > 0) {
            length = i;
            break;
        }
    }


    // get checksum
    int checksum = 0;
    // - rule 1: Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
    for (int i = 1; i < 20; i += 2) {
        long topBoundry = card % (long)pow(10, i+1);
        long bottomBoundry = card % (long)pow(10, i);
        int num = (topBoundry - bottomBoundry) / pow(10, i);

        num *= 2;

        if (num >= 10) {
            int ones = num % 10;
            int tens = num / 10;
            checksum += (tens + ones);
        } else {
            checksum += (num);
        } 
    }

    // - rule 2: Add the sum to the sum of the digits that weren’t multiplied by 2.
    for (int i = 0; i < 20; i += 2) {
        long topBoundry = card % (long)pow(10, i+1);
        long bottomBoundry = card % (long)pow(10, i);
        int num = (topBoundry - bottomBoundry) / pow(10, i);
        
        checksum += num;
    }

    // - rule 3: If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
    int amex_start = card / (long)pow(10, 15-2);
    int mc_start = card / (long)pow(10, 16-2);
    int visa_start_13 = card / (long)pow(10, 13-1);
    int visa_start_16 = card / (long)pow(10, 16-1);

    if (checksum % 10 != 0) {
        printf("INVALID\n");
    } else if (length == 15 && (amex_start == 34 || amex_start == 37)) {
        printf("AMEX\n");
    } else if (length == 16 && (mc_start == 51 || mc_start == 52 || mc_start == 53 || mc_start == 54 || mc_start == 55)) {
        printf("MASTERCARD\n");
    } else if ((length == 13 || length == 16) && (visa_start_13 == 4 || visa_start_16 == 4)) {
        printf("VISA\n");
    } else {
        printf("INVALID\n");
    }
    
}
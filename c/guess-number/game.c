#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



int main(void){
    printf("Welcome to guess the number the most generic of programs. !!\n");

    const int MIN_RANGE = 1;
    const int MAX_RANGE = 100;
    int userInput;
    int num;
    int guesses;
    srand(time(0));
    num = (rand() % MAX_RANGE) + MIN_RANGE;
    
    do
    {
        printf("Enter your guess: \n");
        scanf("%d", &userInput);
        if (userInput < num)
        {
            printf("Your guess is too low\n");
        }
        else if(userInput > num){
            printf("Your guess is to high\n");
        }
        else{
            printf("Correct your guess is on point\n");
        }
        guesses++;
    } while (num != userInput);

    printf("*********************\n");
    printf("Your answer %d \n", userInput);
    printf("Correct Number %d \n", num);
    printf("number of tries %d \n", guesses);
    
    return 0;
}

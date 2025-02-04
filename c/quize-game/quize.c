#include <stdio.h>
#include <ctype.h>

int main(void){
    char questions [][100] = {"1. What year did C language debut?: ",
                            "2. Who is credited with creating C ?:",
                            "3. What is the predecessor to C ?:",
                            "4. What is best food on the world? :"};

    char options [][100] = {"A. 2022", "B. 1972", "C. 1975", "D. 54BC",
                            "A. John lemon", "B. Dennis Ritchie", "C. Nikola Tesla", "D. John Carmack",
                            "A. B","B. Objective C", "C. Latin", "D. C#",
                            "A. Burger", "B. Pizza", "C. Poverty Soupe or Noodle", "D. Tortoise"};

    char answers[4] = {'B', 'B', 'A', 'B'};

    int numberOfQuestions = sizeof(questions)/ sizeof(questions[0]);

    char guess;
    int score;

    printf("QuZe TiMe!!!\n");   

    for (int i = 0; i < numberOfQuestions; i++)
    {
        printf("****************\n");
        printf("%s\n", questions[i]);        

        for(int j = (i*4); j < (i * 4) + 4; j++)
        {
            printf("%s\n", options[j]);
        }

        printf("guess: ");
        scanf("%c", &guess);
        getchar();// Clear \n in buufer after Enter key

        guess = toupper(guess);

        if (guess == answers[i])
        {
            printf("Correct!!\n");
            score++;
        }
        else{
            printf("Wrong!!\n");
            printf("Answer %c", answers[i]);
        }
        
    }
    
    printf("**************\n");
    printf("Your Score! %d/%d\n", score, numberOfQuestions);
    printf("**************\n");

    return 0;
}
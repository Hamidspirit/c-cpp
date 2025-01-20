#include <stdio.h>

int main(){
    char operator;
    double num1;
    double num2;
    double result;

    printf("Enter your operator(+ - * /); \n");
    scanf("%c", &operator);

    printf("Enter 1 number: \n");
    scanf("%lf", &num1);
    printf("Enter 2 number: \n");
    scanf("%lf", &num2);

    switch (operator){
        case '+':
            result = num1 + num2;
            printf("Result %.2lf", result);
            break;
        case '-':
            result = num1 - num2;
            printf("Result %.2lf", result);
            break;
        case '*':
            result = num1 * num2;
            printf("Result %.2lf", result);
            break;
        case '/':
            result = num1 / num2;
            printf("Result %.2lf", result);
            break;

        default:
            printf("%c , is mot a valid operator", operator);
            break;
    }
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[100];
int top = -1;
int temp = 1;

void push(char c) {
	stack[++top] = c;
}

char pop() {
	return stack[top--];
}

int precedence(char c) {
	if (c == '*' || c == '/') 
		return 2;
	
	if (c == '+' || c == '-') 
		return 1;

	return 0;
}

int main() {
	char expr[100];
	char postfix[100];
	int i,j = 0;

	printf("Enter expression: ");
	scanf("%s", expr);

	for (i = 0; expr[i] != '\0'; i++) {
		if (isalnum(expr[i])) 
			postfix[j++] = expr[i];
		
		else if (expr[i] == '(')
			push(expr[i]);

		else if (expr[i] == ')') {
			while (top != -1 && stack[top] != '(') 
				postfix[j++] = pop();
		
			pop();
		}
		else {
			while (top != -1 && (precedence(stack[top]) >= precedence(expr[i]))) 
				postfix[j++] = pop();
	
			push(expr[i]);
		}
	}

	while (top != -1)
		postfix[j++] = pop();
	
	postfix[j] = '\0';


	printf("\nThree Address Code: \n");

	char operandStack[100][10];
	int otop = -1;

	for (i = 0; postfix[i] != '\0'; i++) {
	
		if (isalnum(postfix[i])) {
			
			operandStack[++otop][0] = postfix[i];
			operandStack[otop][1] = '\0';
		}
		else {
			char op2[10], op1[10], result[10];

			strcpy(op2, operandStack[otop--]);
			strcpy(op1, operandStack[otop--]);

			sprintf(result, "t%d", temp++);

			printf("%s = %s %c %s\n", result, op1, postfix[i], op2);

			strcpy(operandStack[++otop], result);
		}
	}
	return 0;
}
	
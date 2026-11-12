#include <stdio.h>
#include <string.h>

char stack[100] = "";
int top = -1;


void display(char input[], int pos, char action[]) {
	printf("%s\t%s\t%s\n", stack, input+pos, action); 
}

int reduce() {
	char *rhs[] = {"(E)", "E+E", "E*E", "i"};
	int i;
	for (i = 0; i < 4; i++) {
		int len = strlen(rhs[i]);
		if ( top + 1 >= len &&
		strcmp(stack + top - len + 1, rhs[i]) == 0) {
			top = top - len + 1;
			stack[top] = 'E';
			stack[top+1] = '\0';
			return 1;
		}
	}
	return 0;
}


int main() {
	char input[100];
	int pos = 0;

	printf("Enter the string: ");
	scanf("%99s", input);

	printf("STACK\tINPUT\tACTION\n");

	while(input[pos]) {
		stack[++top] = input[pos++];
		stack[top+1] = '\0';
		display(input, pos, "SHIFT");
		while(reduce()) 
			display(input, pos, "REDUCE to E");
		
	}

	while (reduce())
		display(input, pos, "REDUCE to E");

	if (strcmp(stack, "E") == 0) 
		printf("String Accepted\n");
	else
		printf("String Rejected\n");

	return 0;
}
		
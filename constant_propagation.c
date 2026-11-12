#include <stdio.h>
#include <string.h>

struct {
	char name[10];
	int val;
} var[20];

int count = 0;

int find(char *name) {
	
	for (int i = 0; i < count; i++) {
		if (strcmp(name, var[i].name) == 0)
			return i;
	}
	return -1;
}

void setVar(char *name, int val) {
	
	int pos = find(name);
	
	if (pos == -1) {
		strcpy(var[count].name, name);
		var[count++].val = val;
	}
	else 
		var[pos].val = val;

}

int main() {
	int n, v1, v2;
	char line[50], lhs[10], r1[10], r2[10], op;

	printf("Enter the number of statements: ");
	scanf("%d", &n);
	getchar();

	for (int i=0; i<n; i++) {
		fgets(line, sizeof(line), stdin);
		line[strcspn(line, "\n")] = 0;
	

		if (sscanf(line, "%s = %s %c %s", lhs, r1, &op, r2) == 4) {
		
			int p1 = find(r1);
			int p2 = find(r2);

			if (p1 != -1 && p2 != -1) {
				int res = 0;
				v1 = var[p1].val;
				v2 = var[p2].val;

				if (op == '+') res = v1 + v2;
				if (op == '-') res = v1 - v2;
				if (op == '*') res = v1 * v2;
				if (op == '/' && v2 != 0) res = v1 / v2;

				setVar(lhs, res);
				printf("%s = %d\n", lhs, res);
			}

			else 
				printf("%s\n", line);
		}

		else if (sscanf(line, "%s = %d", lhs, &v1) == 2) {
	
			setVar(lhs, v1);
			printf("%s = %d\n", lhs, v1);
		}

		else if (sscanf(line, "%s = %s", lhs, r1) == 2) {
		
			int p = find(r1);
	
			if (p != -1) {
				setVar(lhs, var[p].val);
				printf("%s = %d\n", lhs, var[p].val);
			}
			else
				printf("%s\n", line);
		}
	}
	printf("After Successful Constant Propagation: \n");

	for (int i = 0; i < count; i++) 
		printf("%s = %d\n", var[i].name, var[i].val);
	
	return 0;
}
	
	
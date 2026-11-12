#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *keywords[] = {
	"int", "char", "float", "double", "if", "else", "for", "while", "do", "return", "void", "main", NULL
}; 

int isKeyword(char *word) {
	for (int i=0; keywords[i]; i++) {
		if (strcmp(word, keywords[i]) == 0)
			return 1;
	}
	return 0;
}

int main() {
	FILE *fp;
	char ch;
	int i;
	char buffer[100];
	fp = fopen("input.c", "r");
	
	if (fp == NULL) {
		printf("Unable to open input file!!\n");
		return 1;
	}

	while ((ch = fgetc(fp)) != EOF) {
		
		if (isspace(ch)) {
			continue;
		}

		if (isalpha(ch) || ch == '_') {	
			
			i = 0;
			buffer[i++] = ch;

			while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_')) {
				buffer[i++] = ch;
			}

			buffer[i] = '\0';

			if (isKeyword(buffer)) 
				printf("%s : KEYWORD\n", buffer);
			else
				printf("%s : IDENTIFIER\n", buffer);

			if (ch != EOF)
				ungetc(ch, fp);
		}

		else if (isdigit(ch)) {
			i = 0;
			buffer[i++] = ch;

			while ((ch = fgetc(fp)) != EOF && isdigit(ch)) {
				buffer[i++] = ch;
			}

			buffer[i] = '\0';

			printf("%s : NUMBER\n", buffer);
			
			if (ch != EOF) 
				ungetc(ch, fp);
		}

		else if(ch == '/') {
			
			ch = fgetc(fp);

			if (ch == '/') {
				while ((ch = fgetc(fp)) != EOF && ch != '\n') {}
			}

			else if(ch == '*') {
				int pvs = 0;
				while ((ch = fgetc(fp)) != EOF) {
					if (pvs == '*' && ch == '/')
						break;
					pvs = ch;
				}
			}

			else if (ch == '=') {
				printf("/= : OPERATOR\n");
			} 

			else {
				printf("/ : OPERATOR\n");
				if (ch != EOF)
					ungetc(ch, fp);
			}
		}

		else if ( ch == '+' || ch == '-' ||
			  ch == '*' || ch == '=' ||
			  ch == '%' || ch == '!' ||
			  ch == '<' || ch == '>' ||
 			  ch == '&' || ch == '|') {
			

			char next = fgetc(fp);

			if (ch == '+' && (next == '+' || next == '=') ||
			    ch == '-' && (next == '-' || next == '=') ||
			    ch == '*' && next == '=' ||
			    ch == '=' && next == '=' ||
			    ch == '%' && next == '=' ||
			    ch == '<' && next == '=' ||
		            ch == '>' && next == '=' ||
			    ch == '&' && next == '=' ||
			    ch == '|' && next == '|') {
			
				printf("%c%c : OPERATOR\n", ch, next);

			}

			else {
				printf("%c : OPERATOR\n", ch);
				if (next != EOF)
					ungetc(next, fp);
			}
		}

		else if( ch == '(' || ch == ')' ||
			 ch == '[' || ch == ']' ||
 			 ch == '{' || ch == '}' ||
			 ch == ';' || ch == ',' ||
			 ch == '.') {
			
			printf("%c : SPECIAL SYMBOL\n", ch);

		}

		else {
			printf("%c : UNKNOWN\n", ch);

		}

	}
	fclose(fp);
	return 0; 
}
		

		
			
	
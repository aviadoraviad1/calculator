#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

#define SIZE 1000
#define MAX_SIZE 1999
#define MAX_LONG_LONG 9223372036854775807
#define MIN_LONG_LONG -9223372036854775807
#define SIZE 1000
#define MAX_SIZE 1999



int size = SIZE;
char firstNonSpace(char *str);
char* handlePara(char str[]);
char* getBeforeL(char* str);
void addSpace(char str[], int index);
int countOccur(char* str, char ch);
char* plusMinus(char str[]);
char* multipliteDivide(char str[]);
void reverseString(char str[]);
void removeDoubleSpaces(char str[]);
char* getAfterL(char* str);
bool isAllSpaces(const char *str);
char* addSpaceToInput(char* str);
long long powerLongLong(char *baseStr, char *exponentStr, char* pinput);
int checkIfOverflow(char* first, char* second, char oper);
bool isSmaller(char *str1, char *str2) {
    int n1 = strlen(str1), n2 = strlen(str2);

    if (n1 < n2) {
        return true;
    }
    if (n2 < n1) {
        return false;
    }
	int i;
    for (i = 0; i < n1; i++) {
        if (str1[i] < str2[i]) {
            return true;
        } else if (str1[i] > str2[i]) {
            return false;
        }
    }
    return false;
}

void subtractLargeNumbers(char* num1, char* num2, char* result) {
    bool num1IsSmaller = isSmaller(num1, num2);
    if (num1IsSmaller) {
        // Swap num1 and num2
        char* temp = num1;
        num1 = num2;
        num2 = temp;
    }

    reverseString(num1);
    reverseString(num2);

    int length1 = strlen(num1);
    int length2 = strlen(num2);
    int borrow = 0, resultIndex = 0;
	int i;
    for (i = 0; i < length2; i++) {
        int sub = (num1[i] - '0') - (num2[i] - '0') - borrow;
        if (sub < 0) {
            sub = sub + 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[resultIndex++] = sub + '0';
    }
    for (i = length2; i < length1; i++) {
        int sub = (num1[i] - '0') - borrow;
        if (sub < 0) {
            sub = sub + 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[resultIndex++] = sub + '0';
    }

    // Remove leading zeros
    while (resultIndex > 1 && result[resultIndex - 1] == '0') {
        resultIndex--;
    }

    result[resultIndex] = '\0';
    reverseString(result);

    if (num1IsSmaller) {
        // Add minus sign if result is negative
        for  (i = resultIndex; i >= 0; i--) {
            result[i + 1] = result[i];
        }
        result[0] = '-';
    }
}
void removeSpaces(char *str) {
    int i = 0, j = 0;

    while (str[i]) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
        i++;
    }

    str[j] = '\0';
}

char* addLargeNumbers(char *num1, char *num2, char* result) {
	printf("num1: |%s|", num1);
	printf("num2: |%s|", num2);

	removeSpaces(num1);
	removeSpaces(num2);


    int length1 = strlen(num1);
    int length2 = strlen(num2);
    int carry = 0;
    int resultIndex = 0;  

    reverseString(num1);
    reverseString(num2);

	int i = 0;
	if(num1[0] == '-')
	{
		num1[0] = ' ';
		subtractLargeNumbers(num2, num1, result);

	}
	
	else{
		for (i = 0; i < length1 || i < length2; i++) {

			int digit1 = i < length1 ? num1[i] - '0' : 0;
			int digit2 = i < length2 ? num2[i] - '0' : 0;//9109
			int sum = digit1 + digit2 + carry;
			result[resultIndex++] = (sum % 10) + '0';
			carry = sum / 10;//carry 0
		}

		if (carry) {
			result[resultIndex++] = carry + '0';
		}


	}
	result[resultIndex] = '\0';
	reverseString(result);
	return result;
	free(result);
}

char* removeAll(char* str, char ch)
{
	int i, j;
	int len = strlen(str);

	for (i = 0; i < len; i++)
	{

		if (str[i] == ch)
		{
			for (j = i; j < len; j++)
			{
				str[j] = str[j + 1];
			}

			len--;

			i--;
		}
	}
	return str;
}
bool checkLastIsDigit(char* str)
{
	int strLen = strlen(str)-1;
	while(str[strLen] == ' ' || str[strLen] == ')')
	{strLen--;}
	if(str[strLen] == '+' || str[strLen] == '-' || str[strLen] == '*' || str[strLen] == '/')
	{
		return true;
	}
	return false;
}
long long mulDiv(char* num1, char* num2, char oper, char* pinput) {
    long long answer = 0;
    if (checkIfOverflow(num1, num2, oper) == 1) {
        *pinput = 'F';
        return answer;
    }

    long long fir = atoll(num1);
    long long sec = atoll(num2);

    if (oper == '*') {
        answer = fir * sec;
    } else if (oper == '/') {
        if (sec == 0) {
            *pinput = 'F';
            return answer;
        }

        answer = fir / sec;
    }

    return answer;
}
long long addSub(char* num1, char* num2, char oper, char* pinput) {
    long long answer = 0;
    if (checkIfOverflow(num1, num2, oper) == 1) {
        *pinput = 'F';
        return answer;
    }

    long long fir = atoll(num1);
    long long sec = atoll(num2);

    if (oper == '+') {
        answer = fir + sec;
    } else if (oper == '-') {
        answer = fir - sec;
    }

    return answer;
}

int checkIfOverflow(char* first, char* second, char oper) {
    char* p;
    long long fir = strtoll(first, &p, 10);
    long long sec = strtoll(second, &p, 10);

    switch (oper) {
        case '+':
            if ((sec > 0 && fir > MAX_LONG_LONG - sec) || (sec < 0 && fir < MIN_LONG_LONG - sec)) {
                printf("Overflow addition!\n");
                return 1;
            }
            break;
        case '-':
            if ((sec > 0 && fir < MIN_LONG_LONG + sec) || (sec < 0 && fir > MAX_LONG_LONG + sec)) {
                printf("Overflow subtraction!\n");
                return 1;
            }
            break;
        case '*':
            if (fir > 0) {
                if (sec > MAX_LONG_LONG / fir || sec < MIN_LONG_LONG / fir) {
                    printf("Overflow multiplication!\n");
                    return 1;
                }
            } else if (fir < -1) {
                if ((sec > 0 && fir < MIN_LONG_LONG / sec) || (sec < MAX_LONG_LONG / fir)) {
                    printf("Overflow multiplication!\n");
                    return 1;
                }
            }
            break;
		case '/':
			if (sec == 0 || (fir == MIN_LONG_LONG && sec == -1)) {
				printf("Overflow division!\n");
				return 1;
			}
			break;
		case '^':  
				if (fir == 0) {
                if (sec == 0) {
                    return 1;
                }
                return 0;
				}
				if (fir == 1) {
					return 0; 
				}
				if (fir == -1) {
					return 0; \
				}
				if (fir > 1 && sec > (log(LLONG_MAX) / log(fir))) {
					printf("Overflow exponentiation!\n");
					return 1;
				}
				if (fir < -1 && sec % 2 == 0 && sec > (log(LLONG_MAX) / log(-fir))) {
					printf("Overflow exponentiation!\n");
					return 1;
				}
				if (fir < -1 && sec % 2 != 0 && sec > (log(-LLONG_MIN) / log(-fir))) {
					printf("Overflow exponentiation!\n");
					return 1;
				}
				break;
    }

    return 0;
}

int getStringLengthWithoutSpaces(const char *str) {
    int length = 0;
	if(*str == '-')
	{
		length++;
		str++;
	}

    while (*str != '\0') {
        if (*str != ' ') {
            length++;
        }
        str++;
    }

    return length;
}
long long powerLongLong(char *baseStr, char *exponentStr, char* pinput) 
{
    long long result = 1;
	if(checkIfOverflow(baseStr, exponentStr, '^') == 1)
	{
		*pinput = 'F';
		return result;
	}
	// i should take care about overflow of **
	long long i;
    long long base = atoll(baseStr);	
    long long exponent = atoll(exponentStr);

	if(exponentStr[0] == '-')
	{
		result = 0;
		return result;
	}

    for (i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;


}
void reverseString(char str[])
{

	int length = strlen(str);
	int start = 0;
	int end = length - 1;
	while (start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}
char lastNonSpace(char *str) {
	char* in = (char*)malloc(size * sizeof(char));
	strcpy(in, str);
	reverseString(in);
	char a =  firstNonSpace(in);
	return a;
	free(in);
}

char firstNonSpace(char *str) {
    while (*str != '\0') {
        if (*str != ' ') {
            return *str;
        }
        str++;
    }

    return '\0';
}

char* getAfterL(char* str) {
	int originalLength = strlen(str);

	char* lastL = strrchr(str, 'L');

	if (lastL == NULL) {
		char* emptyString = (char*)malloc(1);
		emptyString[0] = '\0';
		return emptyString;
	}

	int substringLength = originalLength - (lastL - str) - 1;

	char* afterLastL = (char*)malloc(substringLength + 1);

	strncpy(afterLastL, lastL + 1, substringLength);

	afterLastL[substringLength] = '\0';

	return afterLastL;
}
char* getBeforeL(char* str) {
	int originalLength = strlen(str);

	char* lettersBeforeL = (char*)malloc(originalLength + 1);
	lettersBeforeL[0] = '\0';

	char* ptr = str;

	while (*ptr) {
		if (*ptr == 'L') {
			break;
		}
		else {
			strncat(lettersBeforeL, ptr, 1);
			ptr++;
		}
	}

	return lettersBeforeL;
}

char* plusMinus(char str[])
{
	char* final_str = (char*)malloc(sizeof(char) * size);
	if(checkLastIsDigit(str))
	{
		strcpy(final_str, "1Wrong input");
		return final_str;
	}
	int num = checkLetterInInput(str);
	if (num != 0)
	{
		printf("2Wrong input");
		exit(1);
	}
	char pinput = 'T';
	char* arr_before = (char*)malloc(sizeof(char) * size);
	char* arr_after = (char*)malloc(sizeof(char) * size);
	char oper;
	int i;

	for (i = 0; str[i]; i++)
	{
		if ((str[i] == '+' || str[i] == '-') && str[i + 1] == ' ')
		{

			int index = strrchr(str, str[i]) - str;
			int j;
			for (j = 0; j < i; j++)
			{
				arr_before[j] = str[j];// input before + as string
				str[j] = 'L';
			}
			arr_before[i] = '\0';
			oper = str[i];
			str[i] = 'L';
			i++;

			if (str[i] != '\0')
			{
				for (j = 0; str[i] != '\0' && (str[i] != '+' && str[i] != '-'); j++)
				{
					arr_after[j] = str[i]; // input after + as string
					str[i] = 'L';
					i++;
				}
				arr_after[j] = '\0';
			}
			if(isAllSpaces(arr_before))
			{
				arr_before[0] = '0'; 
			}
			
			if(oper == '+')
			{
				addLargeNumbers(arr_before, arr_after, final_str);
			}
			if(oper == '-')
			{
				subtractLargeNumbers(arr_before, arr_after, final_str);
				printf("%s", final_str);
			}
			str = removeAll(str, 'L');
			strcat(final_str, " ");
			strcat(final_str, str);
			int times_minus = countOccur(final_str, '-');
			int len = strlen(final_str);
			final_str[len] = '\0';
	
			free(arr_after);
			free(arr_before);	
			return final_str;
		
	

		}
	}
}
int countOccur(char* str, char ch) {

	int count = 0;

	while (*str) {
		if (*str == ch) {
			count++;
		}

		str++;
	}

	return count;
}
char* multipliteDivide(char str[])
{

	char* final_arr = (char*)malloc(sizeof(char) * size);

	if(checkLastIsDigit(str))
	{
		strcpy(final_arr, "Wrong input");
		return final_arr;
	}
	int num = checkLetterInInput(str);
	if (num != 0)
	{
		strcpy(final_arr, "Wrong input");
		return final_arr;
	}
	removeDoubleSpaces(str);
	char arr_before[size];
	char arr_after[size];
	char pinput = 'T';
	int i;
	char oper;
	int waffa = 0;
	for (i = 0; str[i]; i++)
	{
		if (str[i] == '*' || str[i] == '/')
		{
			int index = i + 1;
			while(str[index] == ' ' && str[index] != '\0')
			{index++;}

			if (str[index] == '-')
			{
				arr_after[waffa] = '-';
				waffa++;
				index++;
				while (str[index] == ' ')
				{
					index++;
				}
			}
			if(str[index] == '\0')
			{
				strcpy(final_arr, "Wrong input");
				return final_arr;
			}
			for (index; str[index] != '\0' && str[index] != ' '; index++)
			{
				arr_after[waffa] = str[index];
				str[index] = 'L';
				waffa++;
			}
			arr_after[waffa] = '\0';
			oper = str[i];
			str[i] = 'L';
			index = i - 1;
			while(str[index] == ' ' && index > 0)
			{
				index--;
			}

			waffa = 0;
			for (index; str[index] != ' ' && index >= 0; index--)
			{
				arr_before[waffa] = str[index];
				str[index] = 'L';
				waffa++;
			}
			arr_before[waffa] = '\0';
			reverseString(arr_before);

			long long answer;
			int len_before = getStringLengthWithoutSpaces(arr_after);
			int len_after = getStringLengthWithoutSpaces(arr_before);
			int check_fir = 19;
			int check_sec = 19;
			if(arr_after[0] == '-')
			{
				check_sec++;
			}
			if(arr_before[0] == '-')
			{
				check_fir++;
			}
			if(len_before > check_fir || len_after > check_sec)
			{
				strcpy(final_arr, "Wrong input");
				return final_arr;				
			}
			waffa = 0;
			strcpy(final_arr, getBeforeL(str));
			answer = mulDiv(arr_before, arr_after, oper, &pinput);
			if (pinput == 'F')
			{
				strcpy(final_arr, "Mul Over flow");
				return final_arr;
			}
			sprintf(final_arr, "%s%lld%s", final_arr, answer, getAfterL(str));
			checkLetterInInput(final_arr);
			
			if (strchr(final_arr, '*') != NULL || strchr(final_arr, '/') != NULL)
			{
				return multipliteDivide(final_arr);
			}
			else {
				return final_arr;
			}
			free(final_arr);
			break;
		}
	}
}
char* power(char* input)
{
					int mult = 1;
					char* final = (char*)malloc(size * sizeof(char));
					removeDoubleSpaces(input);
					int num  = hasConsecutiveAsterisks(input);
	

					char arr_after[size];
					char arr_before[size];
					int waffa = 0;
					int i = num + 1;

					while(input[i] == ' ')
					{
						i++;
					}
					while(input[i] == '-' || input[i] == '+'|| input[i] == ' ')
					{
						if(input[i] == '-')
						{
							input[i] = 'L';	
							mult = -1*mult;
						}
						i++;
						
					}
					if(mult < 0)
					{
						arr_after[waffa] = '-';
						waffa++;
					}
				
					if(input[i] == '\0' || isdigit(input[i]) == 0)
					{
						char* s = "Wrong input1";
						return s;
					}
					for(i;  input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && input[i] != '\0'; i++)
					{
						arr_after[waffa] = input[i];
						waffa++;
						input[i] = 'L';
					}
					arr_after[waffa] = '\0';

					// get the arr_before

					waffa = 0;
					i = num - 2;
					while(input[i] == ' ' || input[i] == '*')
					{
						i--;
					}
					if(i == 0)
					{
						arr_before[waffa] = input[i];
						waffa++;
						input[i] = 'L';	
						arr_before[waffa] = '\0';

					}
					else{
						for(i = i; input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && i >= 0; i--)
						{
							if(input[i] == ' ')
							{
								input[i] = 'L';

							}
							else{
								arr_before[waffa] = input[i];
								waffa++;
								input[i] = 'L';
							}
						}
						while(input[i] == '+' || input[i] == '-' || input[i] == ' ')
						{
							if(input[i] == '+' || input[i] == '-')
							{
								int check = i-1;
								while(input[check] == ' ')
								{
									check--;
								}
								if(isdigit(input[check]))
								{
									break;
								}
							}
							if(input[i] == ' ')
							{
								input[i] = 'L';
								i--;							
							}
							else{
								arr_before[waffa] = input[i];
								waffa++;
								input[i] = 'L';
								i--;
							}
						}
						
						arr_before[waffa] = '\0';
						reverseString(arr_before);
					}
					char pinput = 'T';
					long long answer = powerLongLong(arr_before, arr_after, &pinput);

					if(pinput == 'F')
					{
						char* s = "Power Over flow";
						return s;
					}

					strcpy(final, getBeforeL(input));
					sprintf(final, "%s %lld %s", final, answer, getAfterL(input));
					strcpy(input, final);
					if (hasConsecutiveAsterisks(input))
					{
						return power(input);
					}
					else {
						return input;
					}

}
void removeDoubleSpaces(char str[]) {
	int length = strlen(str);
	int i;
	for (i = 0; i < length - 1; i++) {
		if (str[i] == ' ' && str[i + 1] == ' ') {
			int j;
			for (j = i; j < length; j++) {
				str[j] = str[j + 1];
			}
			length--;
			i--;
		}
	}
}
int hasConsecutiveAsterisks(char* str) {

    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '*') {
            while (isspace(str[i + 1])) {
                i++;
            }

            if (str[i + 1] == '*') {
                return i+1;
            }
        }

        i++;
    }

    return 0;
}
char* ToLetter(char arr[], int start, int end, char letter) {

	if (start < 0 || end < 0 || start > end) {
		char* T = {"wrong input"};
		return T;
	}
	int i;
	for (i = start; i <= end; i++) {
		arr[i] = letter;
	}
	return arr;
}

bool isAllSpaces(const char *str) {
    while (*str) {
        if (*str != ' ') {
            return false;
        }
        str++;
    }
    return true;
}
char* handlePara(char str[])
{

	char* start_parentheses = strrchr(str, '(');
	char* end_parentheses = strchr(start_parentheses, ')');

	int start_index = start_parentheses - str;
	int end_index = end_parentheses - str;
	int inner_length = end_index - start_index - 1;
	char* exersice = (char*)malloc((inner_length + 1) * sizeof(char));
	strncpy(exersice, start_parentheses + 1, inner_length);
	exersice[inner_length] = '\0';
	int checkExersice = 0;
	while(exersice[checkExersice] == ' ')
	{checkExersice++;}
	if(exersice[checkExersice] == '*' || exersice[checkExersice] == '/')
	{
		char* b = {"Wrong input"};
		return b;		
	}
	if(isAllSpaces(exersice))
	{
		char* s = {"Wrong input"};
		return s;
	}
	str = ToLetter(str, start_index, end_index, 'L');
	
	
	if(hasConsecutiveAsterisks(exersice))
	{
		removeDoubleSpaces(exersice);
		exersice = power(exersice);
	}
	
	if (strchr(exersice, '*') != NULL || strchr(exersice, '/') != NULL)
	{
		exersice = multipliteDivide(exersice);
		if (strcmp(exersice, "Wrong input/") == 0)
		{
			return exersice;
		}
	}
	int times_minus = countOccur(exersice, '-');
	int check = 0;
	while(exersice[check] == ' ')
	{check++;}
	if (strchr(exersice, '+') != NULL || (times_minus == 1 && exersice[check] != '-') || times_minus > 1)
	{
		exersice = plusMinus(exersice);
	}

	char* final = (char*)malloc(size * sizeof(char));
	char firstL = firstNonSpace(getAfterL(str));
	if(firstL != ')' && firstL != '+' && firstL != '-' && firstL != '*' && firstL != '/' && firstL  != '\0')
	{
		char* s = {"wrong 2input"};
		return s;
	}
	char secondL = lastNonSpace(getBeforeL(str));
	if(secondL != '(' && secondL != '+' && secondL != '-' && secondL != '*' && secondL != '/' && secondL  != '\0' )
	{
		char* s = {"wrong 1input"};
		return s;
	}
	strcpy(final, getBeforeL(str));
	strcat(final, exersice);
	strcat(final, getAfterL(str));
	if (strchr(final, '(') != NULL)
	{
		
		return handlePara(final);
	}
	else {

		return final;
	}
	free(final);
	free(exersice);
}
char* addSpaceToInput(char* str)
{
	char* input = (char*)malloc(size * sizeof(char));
	int i;
	i = 0;
	int waffa = 0;
	if (str[0] == '-')
	{
		input[waffa] = '-';
		waffa++;
		i = 1;
	}
	for (i = i; str[i] != '\0'; i++)
	{

		if (str[i] == '+' || str[i] == '*' || str[i] == '/' || str[i] == '-')

		{
			if (str[i] == '-')
			{
				if (str[i - 1] == '(')
				{
					input[waffa] = str[i];
					waffa++;
				}
				else {
					input[waffa] = ' ';
					waffa++;
					input[waffa] = str[i];
					waffa++;
					input[waffa] = ' ';
					waffa++;
				}
			}

			else {
				input[waffa] = ' ';
				waffa++;
				input[waffa] = str[i];
				waffa++;
				input[waffa] = ' ';
				waffa++;
			}
		}
		else {
			if (str[i] != ' ')
			{
				input[waffa] = str[i];
				waffa++;
			}
		}
	}
	input[waffa] = '\0';
	return input;
	free(input);

}
int checkpara(char* str)
{
	int i;
	int para = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '(')
		{
			para++;
		}
		if (str[i] == ')')
		{
			para--;
		}
		if (para < 0)
		{
			return 0;
		}
	}
	if (para != 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int checkLetterInInput(char* str)
{	
	int length = strlen(str) - 1;
	int i;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (isdigit(str[i]) == 0 && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' && str[i] != '(' && str[i] != ')' && str[i] != ' ')
		{
			return 1;
		}
	}
	for(i = 0; str[i] != '\0'; i++)
	{
		if(str[i] == '+')
		{
			int index = i;
			index++;
			while(str[index] == ' ')
			{index++;}
			
			if(str[index] == '+')
			{
				str[index] = ' ';
			}
		}
			
	}
	for(i = 0; str[i] != '\0'; i++)
	{
		if(str[i] == '+')
		{
			int index = i;
			index++;
			while(str[index] == ' ')
			{index++;}
			
			if(str[index] == '-')
			{
				str[i] = '-';
				str[index] = ' '; 
			}
		}
			
	}
	for(i = 0; str[i] != '\0'; i++)
	{
		if(str[i] == '-')
		{
			int index = i;
			index++;
			while(str[index] == ' ')
			{index++;}
			
			if(str[index] == '-')
			{
				str[index] = ' ';
				str[i] = '+';
			}
		}
			
	}
	for(i = 0; str[i] != '\0'; i++)
	{
		if(str[i] == '/')
		{
			int index = i;
			index++;
			while(str[index] == ' ')
			{index++;}
			
			if(str[index] == '+')
			{
				str[index] = ' ';

			}
		}	
	}
	for(i = 0; str[i] != '\0'; i++)
	{
		if(str[i] == '/')
		{
			int index = i;
			index++;
			while(str[index] == ' ')
			{index++;}
			
			if(str[index] == '/')
			{
				return 1;

			}
		}	
	}

	for(i = 0; str[i] != '\0'; i++)
	{
		if(str[i] == '*')
		{
			int index = i;
			index++;
			while(str[index] == ' ')
			{index++;}
			
			if(str[index] == '/')
			{
				return 1;
			}
		}
			
	}
	for(i = 0; str[i] != '\0'; i++)
	{
		if(str[i] == '/')
		{
			int index = i;
			index++;
			while(str[index] == ' ')
			{index++;}
			
			if(str[index] == '*')
			{
				return 1;
			}
		}
			
	}
	for(i = 0; str[i] != '\0'; i++)
	{
		if(str[i] == '-')
		{
			int index = i;
			index++;
			while(str[index] == ' ')
			{index++;}
			
			if(str[index] == '+')
			{
				str[index] = ' ';
				str[i] = '-';
			}
		}
			
	}
	for(i = 0; str[i] != '\0'; i++)
	{
		if(str[i] == '+' || str[i] == '-')
		{
			int index = i;
			index++;
			while(str[index] == ' ')
			{index++;}
			
			if(str[index] == '*' || str[index] == '/')
			{
				return 1;
			}
		}
			
	}
	for(i = 0; str[i] != '\0'; i++)
	{
		if(str[i] == '*')
		{
			int index = i;
			index++;
			while(str[index] == ' ')
			{index++;}
			
			if(str[index] == '+')
			{
				str[index] = ' ';
			}
		}
			
	}
	return 0;
}
int isFirstCharOperator(const char* inputString) {
	while (*inputString == ' ' || *inputString == '\0') {
		inputString++;
	}

	if (*inputString != '\0') {
		if (*inputString == '+' || *inputString == '-' || *inputString == '*' || *inputString == '/')
		{
			if (*inputString == '-' ||  *inputString == '+')
			{
				*inputString++;
				while (*inputString == ' ' || *inputString == '+' || *inputString == '-' || *inputString == '-') {
					inputString++;
				}
				if (isdigit(*inputString) != 0)
				{
					return 0;
				}
			}
			return 1;
		}
	}

	return 0;
}

void appendToBeginning(char* original, char newChar) {
    int originalLength = strlen(original);

    char newString[originalLength + 2];
	

    newString[0] = newChar;

    strcpy(newString + 1, original);

    strcpy(original, newString);
}

int onlySpaces(char* str) {
	int i;
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] != ' ') {
			return 0;
		}
	}
	return 1;
}

int main()
{ 
		printf("Enter Exersice: ");
		char* input = (char*)malloc(sizeof(char) * SIZE);
		
		fgets(input, SIZE, stdin);
		
		input[strcspn(input, "\n")] = '\0';
		
		size_t input_length = strlen(input);
		
			if(strlen(input) > 400 && strlen(input) < 1000)
			{
				input = (char*)realloc(input, MAX_SIZE * sizeof(char));
				size = MAX_SIZE;
			
			}		
			int num;
			int run = 0;
			while(input[run] == ' ')
			{run++;}
			if(input[run] == '-' || input[run] == '+')
			{
				appendToBeginning(input, '0');
			}
			if (isFirstCharOperator(input) == 1)
			{
				printf("1wrong input");
				return 1;
			}
			if (onlySpaces(input))
			{
				printf("2wrong input");
				return 0;
			}
			
			num = checkLetterInInput(input);
			if (num == 0 && checkpara(input))
			{

				input = addSpaceToInput(input);

				num = checkLetterInInput(input);
				if (num == 0)
				{
					if (strchr(input, '(') != NULL)
					{
						input = handlePara(input);
						input = addSpaceToInput(input);

						int j;
						for (j = 0; input[j] != '\0'; j++)
						{
							if (input[j] == '-' && input[j + 2] == '-' && input[j + 1] == ' ')
							{
								input[j] = '+';
								input[j + 2] = ' ';
								input = addSpaceToInput(input);
							}
						}
					}
					if(hasConsecutiveAsterisks(input))
					{
						input = power(input);
					}
				
					if (strchr(input, '*') != NULL || strchr(input, '/') != NULL)
					{

						removeDoubleSpaces(input);	
						input = multipliteDivide(input);


					}
					int times_minus = countOccur(input, '-');
					if (strchr(input, '+') != NULL || strchr(input, '-') != NULL && (times_minus == 1 && input[0] != '-') || times_minus > 1)
					{
						input = plusMinus(input);
						printf("Answer: %s", input);
						while (strchr(input, '+') != NULL || strchr(input, '-') != NULL)
						{
							input = plusMinus(input);
							printf("Answer: %s", input);

						}


					}

					printf("%s", input);

				

					return 1;
				}
				else {
						printf("Wrong input");
				}
			}
			else {
				printf("Wrong input4");

			}
		
		free(input);
  

    return 0;
}

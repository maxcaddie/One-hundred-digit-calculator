/* Extended precision integer calculator
 * Implements +, *, and ^ (power of) operations
 *
 * Skeleton code written by Jianzhong Qi, March 2018
 * Rest of the program written by Maxwell Caddie, Student ID: 1003994
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define INT_SIZE	100	/* max number of digits per integer value */
#define LINE_LEN	103	/* maximum length of any input line */
#define NUM_VARS	10	/* number of different huge int "variables" */

#define ASN_OP		'='	/* assignment operator */
#define ECH_OP		'?'	/* echo operator */
#define ADD_OP		'+'	/* addition operator */
#define MUL_OP		'*'	/* multiplication operator */
#define POW_OP		'^'	/* power of operator */

#define OPR1_POS	1	/* position of the first operand */
#define OPR2_POS	3	/* position of the second operand */
#define OP_POS		2	/* position of the operator */

#define CH_ZERO		'0'	/* character 0 */

#define EXIT_CMD 	"exit"	/* command to exit */
#define PROMPT		"> "	/* command prompt */
#define CMT_FLAG	'%'		/* indicator for comment line */

typedef int digit_t;			/* a decimal digit */
typedef digit_t huge_t[INT_SIZE];	/* one huge int "variable" */

/* add your constant and type definitions here */

/****************************************************************/

/* function prototypes */
void read_line(char *line, int max_len);
void init(huge_t vars[], int lens[]);
void echo(huge_t vars[], int lens[], int opr1_index);
void assign(huge_t vars[], int lens[], int opr1_index, char *opr2_str);
void add(huge_t vars[], int lens[], int opr1_index, char *opr2_str);
void multiply(huge_t vars[], int lens[], int opr1_index, char *opr2_str);
void multiply2(huge_t vars[], int lens[], int opr1_index, char *opr2_str);
void power(huge_t vars[], int lens[], int opr1_index, char *opr2_str);
int convertStringToIntArray(char *string, int *number);
void printArray(int *array, int length);


/* add your function prototypes here */

/****************************************************************/

/* main function controls all the action, do NOT modify this function */
int
main(int argc, char *argv[]) {
	char line[LINE_LEN+1];		/* to hold the input line */
	huge_t vars[NUM_VARS];		/* to hold 10 huge integers */
	int lens[NUM_VARS];			/* to hold the length of the 10 vars */

	int opr1_index;				/* index of the first operand in command */
	char op;					/* operator in command */

	init(vars, lens);

	while (1) {
		printf(PROMPT);						/* print prompt */
		read_line(line, LINE_LEN);			/* read one line of command */

		if (line[0] == CMT_FLAG) {			/* print comment in the test data */
			printf("%s\n", line);			/* used to simplify marking */
			continue;
		}

		if (strcmp(line, EXIT_CMD) == 0) {	/* see if command is "exit" */
			return 0;
		}

		opr1_index = line[OPR1_POS] - CH_ZERO;/* first var number at line[1] */
		op = line[OP_POS];					/* operator at line[2] */

		if (op == ECH_OP) {					/* print out the variable */
			echo(vars, lens, opr1_index);
			continue;
		}


		/* do the calculation, second operand starts at line[3] */
		if (op == ASN_OP) {
			assign(vars, lens, opr1_index, line+OPR2_POS);
		} else if (op == ADD_OP) {
			add(vars, lens, opr1_index, line+OPR2_POS);
		} else if (op == MUL_OP) {
			multiply(vars, lens, opr1_index, line+OPR2_POS);
		} else if (op == POW_OP) {
			power(vars, lens, opr1_index, line+OPR2_POS);
		}
	}

	/* all done; take some rest */
	return 0;
}

/* read a line of input into the array passed as argument */
void
read_line(char *line, int max_len) {
	int i = 0, c;
	while (((c = getchar()) != EOF) && (c != '\n') && (c != '\r')) {
		if (i < max_len) {
			line[i++] = c;
		} else {
			printf("Invalid input line, toooooooo long.\n");
			exit(0);
		}
	}
	line[i] = '\0';
}

/* print out a huge integer */
void echo(huge_t vars[], int lens[], int opr1_index) {
	int i;


	/* print the digits in a reverse order */
	for (i = lens[opr1_index]-1; i >= 0; i--) {
		printf("%d", vars[opr1_index][i]);
	}

	printf("\n");
}


/****************************************************************/

/* add code below to complete the function bodies,
 * add more functions where appropriate.
 */
 /* "algorithms are fun" */


/* set the vars array to zeros */
void
init(huge_t vars[], int lens[]) {
	int i,j;

	/* Loops through each variable and each digit in variable and sets to 0 */
	for (i = 0; i < NUM_VARS; i++){
		lens[i] = 1;
		for (j = 0; j < INT_SIZE; j++){
			vars[i][j] = 0;
		}
	}

}

/* process the '=' operator */
void
assign(huge_t vars[], int lens[], int opr1_index, char *opr2_str) {

	int i,strPlace=0;

	/*strPlace is there to allow the number to be entered backwards*/

	if (opr2_str[0] != 'n'){ /* If not deepcopying variables */

		lens[opr1_index] = strlen(opr2_str);

		for (i = strlen(opr2_str)-1; i >= 0; i--){
			vars[opr1_index][i] = opr2_str[strPlace]-'0';
			/* ASCII value of char - ASCII value of 0 to give interger value
			*  of the char */
			strPlace++;
		}
	}else{
		/* Sets the variable to the value of the number after the = */
		lens[opr1_index] = lens[opr2_str[1]-'0'];
		for (i = lens[opr2_str[1]-'0'];i >= 0; i--){
			vars[opr1_index][i] = vars[opr2_str[1]-'0'][i];
		}


	}
}

/* process the '+' operator */
void
add(huge_t vars[], int lens[], int opr1_index, char *opr2_str) {

	int lengthOfSecondNumber,i;
	int currentFirstNumber, currentSecondNumber, carry = 0;
	int secondNumber[INT_SIZE] = {0};
	/* Put both numbers into backwards arrays of ints */

	/* Since opr1 has to be a variable it is all ready formated */
	
	if (opr2_str[0] != 'n'){
		lengthOfSecondNumber = convertStringToIntArray(opr2_str,
														secondNumber);

	}else{
		/* Sets the secondNumber int array to the value of the second var */
		for (i = 0; i < INT_SIZE; i++){
			secondNumber[i] = vars[opr2_str[1]-'0'][i];
		}
		lengthOfSecondNumber = lens[opr2_str[1]-'0'];
	}


	/* Find out which of the arrays is longer */
	if (lengthOfSecondNumber > lens[opr1_index]){
		lens[opr1_index] = lengthOfSecondNumber;
	}


	/* For loop at the length of the longer one */

	for (i = 0; i < lens[opr1_index]; i++){

		/* Convert the current two numbers to int's */
		currentFirstNumber = vars[opr1_index][i];
		currentSecondNumber = secondNumber[i];

		/* Add the numbers together */
		currentFirstNumber += currentSecondNumber;

		/* Add carry bit */
		currentFirstNumber += carry;

		/* If number > 9 then take 10 off and make carry bit 1
		* else make carry 0*/
		if (currentFirstNumber > 9){
			carry = 1;
			currentFirstNumber -= 10;
			while (currentFirstNumber > 9){
				carry++;
				currentFirstNumber -= 10;
			}
			
		}else{
			carry = 0;
		}


		/* Save to vars[opr1][i] position */
		vars[opr1_index][i] = currentFirstNumber;


	}
	/* If there is a carry digit change length to accomadate */
	if (carry){
		vars[opr1_index][lens[opr1_index]] = carry;
		lens[opr1_index]++;
		lens[opr1_index]+= carry/10;
		
	}




}

/* process the '*' operator */
void multiply(huge_t vars[], int lens[], int opr1_index, char *opr2_str){
	
	huge_t tempArrays[3];
	int lensTemp[3] = {0};/* 0: holds second number (secondNumber)
								  * 1: holds the calculation (tempArray)
								  * 2: holds the answer (tempAnswer) */
	
	int i,j,k,tempNum,lengthOfTempStr,numOfZeros,carry; /* Carry acts a bool*/
	char tempNumStr[INT_SIZE];
	
	/* Set arrays to zero */
	for (i = 0; i <3; i++){
		for (j = 0; j < INT_SIZE; j++){
			tempArrays[i][j]=0;
		}
	}
	
	if (opr2_str[0] != 'n'){ /*If not a variable */
		lensTemp[0] = convertStringToIntArray(opr2_str, tempArrays[0]);
		
	}else{
		/* Sets tempArray[0] to the value of the secondVariable */
		for (i = 0; i < INT_SIZE; i++){
			tempArrays[0][i] = vars[opr2_str[1]-'0'][i];
		}
		lensTemp[0] = lens[opr2_str[1]-'0'];
	}
	
	for (i = lens[opr1_index]-1; i >= 0; i--){
		for (j = lensTemp[0]-1; j >= 0; j--){
			carry = 0;
			tempNum = vars[opr1_index][i] * tempArrays[0][j];
			
			/* Since two one digit multiplied together 0<=x<=81 the product 
			 * Can only be at most 2 digits long so only checking if > 9 */
			 
			if (tempNum > 9){
				carry = 1;
			}
			
			/* Find out how many 0's there are */
			numOfZeros = i + j;
			
			lengthOfTempStr = numOfZeros+carry+1; /* If carry then 1 longer */
			tempNumStr[lengthOfTempStr] = '\0';
			/* Save the two numbers before the zeros */
			
			if (carry){ /*If a double digit number */
				tempNumStr[0] = (tempNum / 10) + '0';
				tempNumStr[1] = (tempNum % 10) + '0';
			}else{
				tempNumStr[0] = (tempNum % 10) + '0';
			}
			
			/*Add the zeros and the end of string */
			for (k=0;k<numOfZeros;k++){
				tempNumStr[k+carry+1] = '0';
			}
			
			/* Check to ensure overflow is accounted for */
			if(numOfZeros > 98){
				tempNumStr[1] = '0';
				if (numOfZeros > 99){
					tempNumStr[0] = '0';
				}
			}
			
			/* Adds the temporary number to the temporary answer */
			lensTemp[1] = convertStringToIntArray(tempNumStr, tempArrays[1]);
			add(tempArrays,lensTemp,2,tempNumStr);
		}
	}
	/* Re-calculate length */
	lensTemp[2] = 0;
	for (i = INT_SIZE-1; i >=0; i--){
		if (tempArrays[2][i]){
			lensTemp[2] = i;
			break;
		}
		
	}
	lensTemp[2] += 1;
	
	/* Set outside array to tempArray */
	for (i = 0; i < INT_SIZE; i++){
		vars[opr1_index][i] = tempArrays[2][i];
	}
	lens[opr1_index] = lensTemp[2];
	
}

/* process the '^' operator */
void
power(huge_t vars[], int lens[], int opr1_index, char *opr2_str) {

	/* Create temp arrays */
	
	huge_t tempArrays[3];
	int lensTemp[3] = {0};/* 0: holds second number (secondNumber)
								  * 1: holds the calculation
								  * 2: holds the orginal num */
	int i,j,power;
	
	/*Deep copy's orginal number*/
	for (i=0;i<lens[opr1_index];i++){
		tempArrays[2][i] = vars[opr1_index][i];
	}
	lensTemp[2] = lens[opr1_index];
	
	/* Gets second value and copies it into tempArray*/
	
	if (opr2_str[0] != 'n'){
		lensTemp[0] = convertStringToIntArray(opr2_str, tempArrays[0]);
	}else{

		for (i = 0; i < INT_SIZE; i++){
			tempArrays[0][i] = vars[opr2_str[1]-'0'][i];
		}
		lensTemp[0] = lens[opr2_str[1]-'0'];
	}

	
	/* Set calclation temp to 1 for powers */
	tempArrays[1][0] = 1;
	lensTemp[1] = 1;

	/* Multiply into temp array */
	
	for (i=0; i < lensTemp[0]; i++){
		power = pow(10,i); /* Calculates the number of times the 
							 * Multiplication needs to occur */
		for (j=0; j < power*tempArrays[0][i];j++){
			multiply(tempArrays,lensTemp,1,"n2");
		}
	}
	
	/* Set outside array to temp array */
	
	for (i=0; i < lensTemp[1]; i++){
		vars[opr1_index][i] = tempArrays[1][i];
		
	}
	lens[opr1_index] = lensTemp[1];
}

/*Takes a string and an empty int list and converts string in to ints in the
 * list */
int
convertStringToIntArray(char *string, int *number){
	
	int length,i,count;
	length = strlen(string);
	if (length > INT_SIZE){ /*Removes any numbers after 100 digits */
		length = INT_SIZE;
	}


	count = 0;
	for (i = length-1; i >= 0; i--){
		number[i] = string[count]-'0'; 	/*Takes the string converts to an int*/
		count++;
	}

	return length;
}

/* Prints out the array in the correct order for debugging */
void
printArray(int *array, int length){ 
	int i;
	printf("The value of the array is: ");
	/* Back tracks through the array in order to print out the correct order */
	for (i = length;i > 0; i--){
		printf("%d",array[i-1]);

	}
	printf("\n");
}
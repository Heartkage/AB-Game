#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char possible[5040][4];
int guessing[4];
int solution[4];
int used[10]={0};
int count = 0, a, b;

int computer_num[4];
int test[10][4];

char first_input[10];
char second_input[10];
char last_input[10];

int questioning;
int starting;
int breaking;

void instruction(void)
{
	char nothing[10];
	system("cls");
	printf("Goal: Guessing computer's number before it guesses yours.\n\n");
	printf("Step 1: write down a 4-different-digit number on a piece of paper.\n\n");
	printf("Example: 1234.\tThese would be wrong: 1223, 123, 12345.\n");
	printf("Press any key(not Enter) + enter to continue\n");
	scanf("%s", nothing);
	system("cls");
	printf("Step 2: Receiving (a) means amount of correct number in the correct place.\n");
	printf("Receiving (b) means amount of correct number in the wrong place.\n\n");
	printf("Example: 1234 is 2a 1b.\tThis means TWO of the numbers are already in the\ncorrect place and ONE number in the wrong place.\n");
	printf("It could be 12XX in the correct place or X23X, X2X4, XX34, 1X3X, 1XX4 for (a).\n");
	printf("And (b) could be X1XX, XX1X, XXX1, for all 1 to 4.\n");
	printf("Press any key(not Enter) + enter to continue\n");
	scanf("%s", nothing);
	system("cls");
	printf("Step 3: If computer gives you 1234 and askes you for (a) and (b),\nthen you should give back the correct amount of (a) and (b)\nfrom the number you wrote down.\n\n");
	printf("Example: Suppose your number is 5021 and the computer guesses 0271,\nthen you should enter: 1 2 for (a) and (b)\n");
	printf("because you have 0 and 2 in the wrong place, but 1 in the right place.\nSo it is 1a 2b.\n");
	printf("Press any key(not Enter) + enter to continue\n");
	scanf("%s", nothing);
	system("cls");
	printf("Tip: It is good to write down the numbers and (a,b)\nto help you figure out the number.\n");
	printf("\nMay odds be ever in your favor.\n");
	printf("Press any key(not Enter) + enter to start the game\n");
	scanf("%s", nothing);
	fflush(stdin);
}
void recursive(int n)
{
	int tem, i;
	
	if (n == 4)
	{
		for(tem = 0; tem < 4; tem++)
			possible[count][tem] = solution[tem];
		//printf("%d%d%d%d\n", possible[count][0], possible[count][1], possible[count][2], possible[count][3]);
		count++;
		return;
	}
	
	for(i = 0; i < 10; i++)
	{
		if (used[i] == 0)
		{
			used[i] = 1;
			solution[n] = i;
			recursive(n+1);
			used[i] = 0;
		}
	}
}

void com_num(void)
{
	int use[10]={0};
	int i, tem;
	srand(time(NULL));
	
	for(i = 0; i < 4;)
	{
		tem = rand()%10;
		//printf("tem = %d\n", tem);
		if (use[tem] == 0)
		{
			computer_num[i] = tem;
			use[tem] = 1;
			i++;
		}
	}
	//printf("%d%d%d%d\n", computer_num[0], computer_num[1], computer_num[2], computer_num[3]);
}

int checking(void)
{
	int i, j, counta = 0, countb = 0;
	for(i = 0; i < 4; i++)
	{
		if (guessing[i] != computer_num[i])
		{
			for(j = 0; j < 4; j++)
			{
				if(guessing[j] == computer_num[i])
				{
					countb++;
					break;
				}	
			}
		}
		else
		{
			counta++;
		}	
	}
	printf("It's %da, %db.", counta, countb);
	if(counta == 4)
		return(counta);
}
void checking2(int *counta, int *countb, int i, int tem)
{
	int j, k;
	
	for(j = 0; j < 4; j++)
	{
		if(possible[i][j] != possible[tem][j])
		{
			for(k = 0; k < 4; k++)
			{
				if(possible[i][k] == possible[tem][j])
				{
					(*countb)++;
					break;		
				}
			}
		}
		else
			(*counta)++;
	}
}
void anti_stupid1(void)
{
	int tem;
	while(1)
	{
		for(tem = 0; (first_input[tem] = getchar()) != '\n'; tem++);
		first_input[tem] = '\n';
		
		if((first_input[0] == ' ') || (first_input[4] == ' '))
			printf("Please do not include space at the front or back of your entry.\nPlease re-enter: ");
		else if (first_input[4] != '\n' || tem != 4)
			printf("Please enter 4 digits: ");
		else if ((first_input[0] == first_input[1]) || (first_input[0] == first_input[2]) || (first_input[0] == first_input[3]) || (first_input[1] == first_input[2]) || (first_input[1] == first_input[3]) || (first_input[2] == first_input[3])) 
			printf("Please make sure they are different numbers: ");
		else
		{
			for(tem = 0; tem < 4; tem++)
			{
				first_input[tem] -= 48;
				guessing[tem] = first_input[tem];
			}
			//printf("%d%d%d%d\n", guessing[0], guessing[1], guessing[2], guessing[3]);
			return;
		}
	}
}
void anti_stupid2(void)
{
	int tem;
	while(1)
	{
		for(tem = 0; (second_input[tem] = getchar()) != '\n'; tem++);
		second_input[tem] = '\n';
		if(second_input[0] == 40)
			printf("Do not include the parenthesis, please re-enter: ");
		else if(second_input[0] == ' ')
			printf("Do not add extra space at the beginning or end of your entry.\nPlease re-enter: ");
		else if (tem != 3 || second_input[3] != '\n')
			printf("Please Enter in the form (a b): ");
		else if(second_input[1] != ' ')
			printf("Please make sure there is a space between two numbers: ");
		else if((second_input[0] < 48 || second_input[0] > 52) && (second_input[2] < 48 || second_input[2] > 52))
			printf("Please make sure your numbers are bettwen 0 and 4: ");
		else if(second_input[0] + second_input[2] > 100)
			printf("How is it possible to be %da and %db?\nPlease re-enter: ", second_input[0]-48, second_input[2]-48);
		else if(second_input[0] == 51 && second_input[2] == 49)
			printf("3a and 1b? Do you mean 4a?\nPlease re-enter: ");
		else
		{
			a = second_input[0]-48;
			b = second_input[2]-48;
			return;
		}
	}
} 
void anti_stupid3(void)
{
	int tem;
	while(1)
	{
		for(tem = 0; (last_input[tem] = getchar()) != '\n'; tem++);
		last_input[tem] = '\n';
		last_input[0] -= 48;
		
		if (last_input[1] != '\n')
			printf("Please enter correctly: ");
		else if((last_input[0] == 1) || (last_input[0] == 2))
		{
			questioning = last_input[0];
			starting = last_input[0];
			breaking = last_input[0];
			return;
		}
		else if(last_input[0] != 1)
			printf("Please enter only 1 or 2: ");
	}	
}

int main()
{
	int n, c, i, j;
	int player_done, computer_done;
	int player, computer, error, tem;
	int turn;
	int counta, countb;
	
	int test_count;
	int test_a[10][1];
	int test_b[10][1];
	
	printf("AB game - ver. 1.2.\n");
	printf("\nWould you like to read the instruction?\n(1).Yes (2).No\tAnswer: ");
	anti_stupid3();
	if (questioning == 1)
		instruction();
	system("cls");
	
	do
	{
		n = 0, c = 0, i = 0, j = 0;
		player_done = 0, computer_done = 0;
		player = 0, computer = 0, error = 0, tem = 0, count = 0;
		turn = 0;
		test_count = 0;
		
		recursive(n);
		com_num();
		//printf("count = %d", count);
		printf("AB game - ver. 1.2.\n");
		printf("\nDo you want to start first?\n(1).Yes (2).No\tAnswer: ");
		anti_stupid3();
		
		if(starting == 1)
		{
			turn = 0;
			printf("You can start first.\n");
		}
		else if(starting == 2)
		{
			turn = 1;
			printf("Okay, I will start first.\n");
		}
		
		while(player_done == 0 || computer_done == 0)
		{
			if (turn == 0)
			{
				if(computer_done == 1 && starting == 2)
					printf("\nI started first, so you have your last try: ");
				else if(computer_done == 1 && starting == 1)
				{
					player++;
					break;
				}	
				else
					printf("\nIt's your turn!\nPlease enter a number: ");
					
				anti_stupid1();
				
				if (checking() == 4)
				{
					player++;
					printf("Congradulation! You finished in %d times.\n", player);
					player_done++;
				}					
				else
					player++;
					
				if(computer_done == 1)
				{
					player++;
					break;
				}
				turn = 1;
			}
			
			else if (turn == 1)
			{
				if(player_done == 1 && starting == 1)
					printf("\n\nYou started first, so I have my last try.\n");
				else if(player_done == 1 && starting == 2)
				{
					computer++;
					break;
				}
				else
					printf("\n\nIt's my turn!\n");
					
				for(tem = rand()%5040; possible[tem][0] == -1;)
					tem = rand()%5040;

				printf("Guessing: %d%d%d%d\n", possible[tem][0], possible[tem][1], possible[tem][2], possible[tem][3]);
				printf("How many A and B(a b): ");
				anti_stupid2();
				
				if(a == 4)
				{
					computer++;
					printf("I finished in %d tries!\n", computer);
					computer_done++;
					turn = 0;
					continue;
				}	
				
				for(i = 0; i < 5040; i++)
				{
					counta = 0, countb = 0;
					
					if(possible[i][0] == -1)
						continue;
					else if(tem == i)
					{
						for(j = 0; j < 4; j++)
							test[test_count][j] = possible[i][j];
						test_a[test_count][0] = a;
						test_b[test_count][0] = b;
						
						test_count++;
						continue;
					}	
					else 
					{
						checking2(&counta, &countb, i, tem); 
						
						if((counta != a) || (countb != b))
						{
							possible[i][0] = -1;
							c++;
						}	
					}
					
				}
				
				possible[tem][0] = -1;
				c++;
				//printf("c = %d\n", c);
				
				if(c >= 5040)
				{
					counta = 0, countb = 0;
					
					printf("\nThere is no possible solution!\n");
					error = 1;
					printf("\n *Checking-system activating*\n");
					printf("Please enter the correct number that I was guessing: ");
					anti_stupid1();
					for(i = 0; i < 4; i++)
						computer_num[i] = guessing[i]; 
					
					for(i = 0; i < test_count; i++)
					{
						for(j = 0; j < 4; j++)
						{
							guessing[j] = test[i][j];
							printf("%d",test[i][j]);	
						}
						printf(" --> ");
						checking();
						printf(" And you enter %da, %db.\n", test_a[i][0], test_b[i][0]);
					}
					
					printf("\nWould you like to read the instructions again?\n(1).Yes (2).No\tAnswer: ");
					anti_stupid3();
					if (questioning == 1)
						instruction();
					break;
				}
				if(player_done == 1)
				{
					computer += 2;
					break;
				}
				computer++;
				turn = 0;
			}
		}
		
		if(error == 0)
		{
			if(player < computer)
				printf("\nYou Won~!\n");
			else if(player > computer)
				{
					printf("\nMy number is %d%d%d%d.\n", computer_num[0], computer_num[1], computer_num[2], computer_num[3]);
					printf("You lost~!\n");	
				}
			else if(player == computer)
				printf("\nIt's draw~!\n");
		}	
		
		printf("\nDo you want to play again?\n(1).Yes (2).No\tAnswer: ");
		anti_stupid3();
		
		system("cls");		
  	}while(breaking != 2);
	
	return 0;
}


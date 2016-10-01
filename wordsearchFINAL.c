//wordsearch.c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int getMax(int x, int y);
int getSlope(int iValue, int jValue, char board2[50][50], char* words2, int rows2, int columns2, int switchCase);
void board2Low(char board2[50][50], int rows, int columns);
void applySlope(int slopeInput);
void generateBoard(int rows3, int columns3);
//In order to be able to manipulate these values within independant functions they are declared as global variables
int colCount, rowCount;


int main(void){
		int cases, rows, columns, caseCount, i, j, wordCount;
		scanf("%d", &cases);

	for(caseCount = 0 ; caseCount < cases ; ++caseCount){

			char board[50][50] = {0};
			
			//In this section of code the user is asked how many rows and columns the board will have
			scanf("%d", &rows);
			scanf("%d", &columns);

			for (i = 0 ; i < rows ; i++){
				scanf("%s", board[i]);
			}

		// This Secion Of Code Asks The User How Many Words, And establishes a suitable array
		int maxLength = getMax(rows, columns);
			scanf("%d", &wordCount);
			char words[20][maxLength+1];

			/* This Seciont unitialize the Array "words" to zeros (nul character). Because we don't know the size of each of the words
			when we use i and j within forLoops, we need to have an indicator as to when the relevant data is done. This is nul char's job*/
			for (i = 0 ; i < wordCount ; i++){
				for (j = 0 ; j < maxLength ; j++){
					words[i][j] = (char) 0;
				}
			}

			
			// This Portion Accepts the Users Words And Stores Them In An Array					 
			for(i=0 ; i < wordCount ; i++){
				scanf("%s", words[i]);
				
				// This Portion of Code Makes The User Input Lowercase So Comparison Will Be Easy
				for ( j=0 ; j < maxLength ; j++){ 
					int upOrLowLetter = words[i][j];
					int lowLetter = tolower(upOrLowLetter);
					words[i][j] = (char) lowLetter;
				}
			}

		//This section of code makes the entire board lowercase so comparison will be easy
		board2Low(board,rows,columns);
		//letterNum and wordNum are the letter and word in question, respectively. They originally set to 0, the first letter of the first word.
		int letterNum = 0, wordNum, slope, switchNumber = 1, i, j;
			
		//This for loop will control which word is being processed. It begins with the first, and increments until the last
		for (wordNum=0 ; wordNum < wordCount; wordNum++){
			
			for(i = 0 ; i < rows ; i++){ 
			rowCount = i;
				for(j = 0 ; j < columns ; j++){ 
				colCount = j;	

					/* For every element on the board, if it is a match, the 'if' statement below will run, if it is not, the 'else' will run until it 
					breaks out of the for loop (explained below) and the program moves on to checking the next tile*/
					for(letterNum = 0 ; words[wordNum][letterNum] != 0 ; letterNum++){ 		

						if (words[wordNum][letterNum] == board[rowCount][colCount]){

							slope = getSlope(i, j, board, words[wordNum], rows, columns, switchNumber);	
							if(!slope) break;

							//If the Letter is the last letter of the word, and it satisfied the outer if, then the whole word has been found, so we...				
							if (words[wordNum][letterNum+1] == 0){

								//Print the Location of the First Letter, reset row/colCount, move onto the next word, and...
								printf("%d %d\n", i+1, j+1);
								i = 0;
								rowCount = i;
								j = -1;
								colCount = j;
								wordNum++;
								//Break the for loop. So we return to the outer 'i/j' for loops that search the board
								break;	 
							}	


							//Sees if the second letter is a match, and if it is not, exits the loop	
							applySlope(slope);			 				
								

						}

						else {
							if (switchNumber  == 8){
								switchNumber = 1;
								break;
							}
							rowCount = i;
							colCount = j;
							letterNum = -1;
							switchNumber++;
						}

					}// End Inner For Loop



				}//End 'j' for loop
			}//End 'i' for loop
		}//end 'wordNum' for loop

	if( (caseCount + 1) != cases ) printf("\n");
	}//End 'caseCount' Loop
				
return(0);
}//end main

int getMax(int x, int y){

	//Whole function is very self explanatory
	int max;
	max = x;
	if (y > x){
		max = y;
	}
	return(max);
}

int getSlope(int iValue, int jValue, char board2[50][50], char* words2, int rows2, int columns2, int switchCase){
	--rows2;
	--columns2;

	int nextChar = words2[1];
	int slopeValue = 0;

	switch (switchCase){
		case 1:
			if(jValue < columns2)
			if ( (int)board2[iValue][jValue+1] == nextChar){
				slopeValue = 1;
				break;
			}
		case 2:
			if ( (jValue < columns2) && (iValue > 0) )
			if ( (int)board2[iValue-1][jValue+1] == nextChar){
				slopeValue=2;
				break;
			}
		case 3:	
			if (iValue > 0)
			if ( (int)board2[iValue-1][jValue] == nextChar){
				slopeValue=3;
				break;
			}
		case 4:
			if ( (iValue > 0) && (jValue > 0) )
			if ( (int)board2[iValue-1][jValue-1] == nextChar){
				slopeValue=4;
				break;
			}
		case 5:
			if (jValue > 0)
			if ( (int)board2[iValue][jValue-1] == nextChar){
				slopeValue=5;
				break;
			}
		case 6:
			if ( (jValue > 0) && (iValue < rows2) )
			if ( (int)board2[iValue+1][jValue-1] == nextChar){
				slopeValue=6;
				break;
			}	
		case 7:
			if (iValue < rows2)
			if ( (int)board2[iValue+1][jValue] == nextChar){
				slopeValue=7;
				break;
			}
		case 8:
			if ( (iValue < rows2) && (jValue < columns2) )
			if ( (int)board2[iValue+1][jValue+1] == nextChar){
				slopeValue=8;
				break;
			}	
	}//End Switch
return(slopeValue);
}

void board2Low(char board2[50][50], int rows, int columns){
	//Pretty self explanatory. 
	int i, j;
	for (i=0 ; i < rows ; i++){
		for (j=0 ; j < columns ; j++){
			int lowerChar = tolower(board2[i][j]);
			board2[i][j] = lowerChar;
		}
	}
}

void applySlope(int slopeInput){

	switch (slopeInput){
		case 1: 
			++colCount;
			break;
		case 2:
			++colCount;
			--rowCount;
			break;
		case 3:
			--rowCount;
			break;
		case 4: 
			--rowCount;
			--colCount;
			break;
		case 5:
			--colCount;
			break;
		case 6: 
			--colCount;
			++rowCount;
			break;
		case 7:
			++rowCount;
			break;
		case 8:
			++rowCount;
			++colCount;
			break;
	}
}











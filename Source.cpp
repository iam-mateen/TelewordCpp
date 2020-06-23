#include<iostream>
#include<fstream>
#include<cstring>
#include<windows.h>
#include<conio.h>
#include<time.h>

using namespace std;

// ---------------------------------------------- ALL FUNCTION DEFINATION ---------------------------------------------//
int getTeleFileData(char[][15],char[][16]);
void gotoxy(int,int,int,char);
void solveGrid(char[][15],char[][16],int[][15],int,bool);
void solveGrid(char[][15], char[][16],int[][15],int,bool);
int init(char[][15],char[][16],int[][15]);
bool findWord(int[],string,char[][15],int[][15],int,int, bool,bool);
void option1(char[][15],char[][16],int[][15],int);
void option3(char[][16],int, int[][15]);
void printColoredGrid(char[][15],int[][15], int);
char printOptions();

// ---------------------------------------------- GLOBAL VARIABLES --------------------------------------------------//

char filename[] = "teleword_1.txt";
int wordDist[6];

int main() {
	char choice, alphabetGrid[15][15], wordList[100][16];
	int totalWords, solvedGrid[15][15];

	totalWords = init(alphabetGrid, wordList, solvedGrid);
	choice = printOptions();

	if(choice == 'S') {
		option1(alphabetGrid, wordList, solvedGrid, totalWords);
	} 
	else if(choice == 'T') {
		solveGrid(alphabetGrid, wordList, solvedGrid, totalWords, true);
		cout <<endl<<endl<<endl<<endl<<endl<<endl<<endl;
		cout << "Teleword is: ";
		for(int i=0; i<15;i++) {
			for(int j=0; j<15;j++) {
				if(solvedGrid[i][j] == 0)
					cout << alphabetGrid[i][j];
			}
		}
		cout << endl;
	} 
	else {
		clock_t tStart = clock();
		option1(alphabetGrid, wordList, solvedGrid, totalWords);
		printf("\nTime taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
		option3(wordList, totalWords, solvedGrid);
	}

	cout << endl;
	return 0;
}

int init(char alphabetGrid[][15], char wordList[][16],int solvedGrid[][15]) {
	int totalWords;
	for(int i=0; i<15;i++)
		for(int j=0; j<15;j++)
			solvedGrid[i][j] = 0;

	totalWords= getTeleFileData(alphabetGrid, wordList);

	for(int i=0; i < 15;i++) {
		for(int j=0; j<15; j++) {
			cout << alphabetGrid[i][j] << " ";
		}
		cout << endl;
	}

	for(int i=0; i<totalWords; i++) {
		if(i < totalWords - 1)
			cout << wordList[i] << ", ";
		else
			cout << wordList[i] << "." <<endl<<endl;
	}
	return totalWords;
}

void option1(char alphabetGrid[][15], char wordList[][16], int solvedGrid[][15], int totalWords) {
	solveGrid(alphabetGrid, wordList, solvedGrid, totalWords, false);
	printColoredGrid(alphabetGrid, solvedGrid, 26);
	cout <<endl<< "Telword is: ";
	for(int i=0; i<15;i++) {
		for(int j=0; j<15; j++) {
			if(solvedGrid[i][j] == 0) {
				cout << alphabetGrid[i][j];
			}
		}
	}
}

void option3(char wordList[][16], int totalWords, int solvedGrid[][15]) {
	int temp = -1, total = 0, avg = 0;
	for(int i=0; i<totalWords; i++) {
		int length = strlen(wordList[i]);
		total += length;
		if(length > temp)
			temp = length;
	}
	cout << "Largest word length: " << temp;
	temp = 16;
	for(int i=0; i<totalWords; i++) {
		int length = strlen(wordList[i]);
		if(length < temp)
			temp = length;
	}
	cout<< ", Smallest word length: " << temp;
	cout << ", Average word is: " << (total / totalWords);
	int rows = 0;
	for(int i=0; i<15;i++) {
		int flag = false;
		for(int j=0; j<15; j++) {
			if(!flag) {
				if(solvedGrid[i][j] == 0) {
					rows++;
					flag = true;
				}
			}
		}
	}
	cout << endl << "Word Distribution: ";
	cout <<"Horizontal: " << (wordDist[0] + wordDist[1]) << "(" << wordDist[0] << "," << wordDist[1] << ") ";
	cout <<"Vertical: " << (wordDist[2] + wordDist[3]) << "(" << wordDist[2] << "," << wordDist[3] << ") ";
	cout <<"Diagonal: " << (wordDist[4] + wordDist[5]) << "(" << wordDist[4] << "," << wordDist[5] << ")";
	cout << endl << "Teleword Scatter: " << rows << endl;
	int rowSum[15];
	int columnSum[15];
	for(int i=0; i<15;i++) {
		rowSum[i] = 0;
		columnSum[i] = 0;
	}
	for(int i=0; i< 15; i++) {
		for(int j=0; j<15;j++) {
			rowSum[i] += solvedGrid[i][j];
			columnSum[i] += solvedGrid[j][i];
		}
	}
	int heaviestRow, heavietstColumn;
	int largestR = rowSum[0];
	int largestC = columnSum[0];
	for(int i=0; i<15;i++) {
		if(rowSum[i] > largestR) {
			heaviestRow = i;
			largestR = rowSum[i];
		}
		if(columnSum[i] > largestC) {
			heavietstColumn = i;
			largestC = columnSum[i];
		}
	}
	cout << "Heaviest Row: " << heaviestRow << endl;
	cout << "Heaviest Column: " << (heavietstColumn);


}

char printOptions() {
	char choice;
	cout << "1. Press S to solve the puzzle at once."<<endl;
	cout << "2. Press T to solve step by step." << endl;
	cout << "3. Press X to print puzzle statistics."<<endl;
	cin >> choice;
	
	if(choice == 'S' || choice == 's')
		return 'S';
	else if(choice == 'T' || choice == 't')
		return 'T';
	else
		return 'X';
}

int getTeleFileData(char telewords[15][15], char words[][16]) {
	ifstream file;
	file.open(filename);

	int rIndex=0;
	bool flag = true;
	char ch;
	file >> ch;
	while(ch != '.') {
		if(flag) {
			for(int i=0; i< 15;i++)
				for(int j=0; j < 15;j++) {
					telewords[i][j] = ch;
					file >> ch;
				}

		flag = false;
		}
		int cIndex = 0;
		while(ch != ',' && ch != '.') {
			words[rIndex][cIndex] = ch;
			cIndex++;
			file >> ch;
		}
		words[rIndex][cIndex] = '\0';
		rIndex++;
		file >> ch;
	}
	return rIndex;
}

void gotoxy(int xpos, int ypos, int col, char ch)
{
	 COORD scrn;
	 HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	 scrn.X = xpos; scrn.Y = ypos;
	 SetConsoleCursorPosition(hOuput,scrn);
	 HANDLE  screen=GetStdHandle(STD_OUTPUT_HANDLE);
	 SetConsoleTextAttribute(screen,col);
	 DWORD useless;
	 WriteConsole(screen,&ch,1,(LPDWORD)&useless,NULL);
	 SetConsoleTextAttribute(screen,15);
	 SMALL_RECT windowSize = {0, 0, 100, 100};
	 SetConsoleWindowInfo(screen, TRUE, &windowSize);
}

void solveGrid(char alphabetGrid[][15], char wordList[][16],int finalGrid[][15], int totalWords, bool isOption2Selected) {
	if(isOption2Selected) {
		cout <<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		COORD cord;
		cord.X = 0;
		cord.Y = 25;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),cord);
		for(int i=0; i<15; i++) {
			for(int j=0; j<15;j++) {
				cout << alphabetGrid[i][j] << " ";
			}
			cout << endl;
		}
		cout <<endl;
		for(int i=0; i<totalWords; i++)
			cout << wordList[i] << ", ";
	}

	for(int i=0; i < totalWords; i++) {
		string word = wordList[i];
		if(isOption2Selected) {
			char ch = getch();
			while(ch != 13)
				ch = getch();
		}
			
		for(int j=0; j < 15; j++) {
			
			for(int k=0; k< 15; k++) {
				bool isFound = false;
				int axis[] = {j,k};
				if(!isFound) {
					isFound = findWord(axis, word, alphabetGrid, finalGrid, -1, 0, true, isOption2Selected);
					if(isFound) {
						j = 16;
						k = 16;
						wordDist[3]++;
					}
				}
				if(!isFound) {
					isFound = findWord(axis, word, alphabetGrid, finalGrid, -1, -1, true, isOption2Selected);
					if(isFound) {
						j = 16;
						k = 16;
						wordDist[5]++;
					}
				}
				if(!isFound){
					isFound = findWord(axis, word, alphabetGrid, finalGrid, 0, -1, true, isOption2Selected);
					if(isFound) {
						j = 16;
						k = 16;
						wordDist[1]++;
					}
				}
				if(!isFound){
					isFound = findWord(axis, word, alphabetGrid, finalGrid, 1, -1, false, isOption2Selected);
					if(isFound) {
						j = 16;
						k = 16;
						wordDist[5]++;
					}
				}
				if(!isFound){
					isFound = findWord(axis, word, alphabetGrid, finalGrid, 1, 0, false, isOption2Selected);
					if(isFound) {
						j = 16;
						k = 16;
						wordDist[2]++;
					}
				}
				if(!isFound){
					isFound = findWord(axis, word, alphabetGrid, finalGrid, 1, 1, false, isOption2Selected);
					if(isFound) {
						j = 16;
						k = 16;
						wordDist[4]++;
					}
				}
				if(!isFound) {
					isFound = findWord(axis, word, alphabetGrid, finalGrid, 0, 1, false, isOption2Selected);
					if(isFound) {
						j = 16;
						k = 16;
						
						wordDist[0]++;
					}
				}
				if(!isFound) {
					isFound = findWord(axis, word, alphabetGrid, finalGrid, -1, 1, true, isOption2Selected);
					if(isFound) {
						j = 16;
						k = 16;
						wordDist[4]++;
					}
				}

			}
		}
	}
}

bool findWord(int axis[], string word, char alphabetGrid[][15], int finalGrid[][15], int RC, int CC, bool isDec, bool isOption2Selected) {
	int index = 0;
	bool isFound = false;
	int traces[15][2];
	int row = axis[0];
	int column = axis[1];

	if(isDec) {
		while(row >= 0 && column >=0) {
			if(word[index] == alphabetGrid[row][column] || char(word[index]-32) == alphabetGrid[row][column]) {
				traces[index][0] = row;
				traces[index][1] = column;
				index++;
				if(index == word.length() && isFound == false) {
					row = -3;
					column = -3;
					isFound = true;
					for(int i=0; i<index; i++) {
						finalGrid[traces[i][0]][traces[i][1]] += 1;
					}

					if(isOption2Selected)
						printColoredGrid(alphabetGrid, finalGrid, 25);
				}
			} else
				index = 0;
			row += RC;
			column += CC;
		}

	} else {

		while(row <= 15 && column <= 15) {
			if(word[index] == alphabetGrid[row][column] || char(word[index]-32) == alphabetGrid[row][column]) {
				traces[index][0] = row;
				traces[index][1] = column;
				index++;
				if(index == word.length() && isFound == false) {
					row = 20;
					column =20;
					isFound = true;
					for(int i=0; i<index; i++) {
						finalGrid[traces[i][0]][traces[i][1]] += 1;
					}


					if(isOption2Selected)
						printColoredGrid(alphabetGrid, finalGrid, 25);
				}
			} else
				index = 0;
			row += RC;
			column += CC;
		}
		
	}
	return isFound;
}

void printColoredGrid(char alphabetGrid[][15], int finalGrid[][15], int startIndex) {
	for(int i=0; i<15; i++) {
		int space = 0;
		for(int j=0; j<15;j++) {
			if(finalGrid[i][j] == 0) {
				gotoxy(space, startIndex+i, 15, alphabetGrid[i][j]);
				gotoxy(space+1, startIndex+i, 2, ' '); 
			} else {
				if(finalGrid[i][j] == 1) {
					gotoxy(space, startIndex+i, 14, alphabetGrid[i][j]);
					gotoxy(space+1, startIndex+i, 2, ' '); 
				} else if(finalGrid[i][j] == 2) {
					gotoxy(space, startIndex+i, 1, alphabetGrid[i][j]);
					gotoxy(space+1, startIndex+i, 2, ' '); 
				} else if(finalGrid[i][j] > 2) {
					gotoxy(space, startIndex+i, 4, alphabetGrid[i][j]);
					gotoxy(space+1, startIndex+i, 2, ' '); 
				} else {
					gotoxy(space, startIndex+i, 15, alphabetGrid[i][j]);
					gotoxy(space+1, startIndex+i, 2, ' '); 
						}
					}
			if(j == 0)
				space = j + 2;
			else
				space = space+2;
		}
	}
}
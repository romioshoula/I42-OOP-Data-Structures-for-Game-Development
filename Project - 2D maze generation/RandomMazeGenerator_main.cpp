//RandomMazeGenerator_main.h RamiWailShoula 
// Function extentions from Header file (definitions) including Function bodies and main for a 2D SFML maze
// Program uses randomization to create resizable mazes and ends when player reaches exit or presses 'Esc' Key
//Keys are WASD & UP, Left. Down, RIght arrow keys

//#includes

#include"RandomMazeGenerator_header.h" //everything is there

/*
int main()
{
	//User interface
	MazeSize = 11; //Defined in header //Only odd numbers have Complete closed boundaries
	char ans = 'n';
	//cout << "";
	cout << "A maze that is randomized and can be reset on 'Space' Key\n";
	cout << "Goal is to move the player through maze to reach exit\n";
	cout << "Program ends when player reaches goal or presses 'Esc' Key\n";
	cout << "PLayer may move with WASD keys || Up, Left, Down, Right keys\n";
	cout << "Maze is resizable ( and can be reset (cleared and re-randomized in runtime)\n";
	cout << "Default size is 11 x 11, do you want to resize (Only odd square sizes greater than 11^2 accepted)? y/n ";
	//ans = _getch(); //ITI.h
	cin >> ans;
	if ((ans == 'y') || (ans == 'Y'))
	{
		cout << "\nPlease enter ODD integer for maze size (Mazesize x Mazesize): ex: 11 for 11 x 11 maze (default):\n ";
		cin >> MazeSize;
		while ( ( MazeSize % 2 == 0 ) || (MazeSize<11) ) { //Even numbers have broken borders so are not accepted (even though algorithm runs)
			cout << "\nSorry, Please Enter ODD integer ( 11 or grater) only:\n";
			cin >> MazeSize;
		}
		cout << "\nMaze Size is " << MazeSize << " x " << MazeSize << endl;
	}
	else
	{
		cout << "\nMaze Size is 11 x 11:\n";
	}

	//MAZE COMMENCE
	unsigned int Seed = time(0);
	srand(Seed);
	Game NewGame(896, 896, 32);
	NewGame.Run();
	return 0;
}
*/

//I added a while loop to stay in program unless user exits

//While loop
char Check = 'y';

int main()
{
	while ((Check == 'y') || (Check == 'Y')) {
		system("cls");
		//User interface
		MazeSize = 11; //Defined in header //Only odd numbers have Complete closed boundaries
		char ans = 'n';
		//cout << "";
		cout << "A maze that is randomized and can be reset on 'Space' Key\n";
		cout << "Goal is to move the player through maze to reach exit\n";
		cout << "Program ends when player reaches goal or presses 'Esc' Key\n";
		cout << "PLayer may move with WASD keys || Up, Left, Down, Right keys\n";
		cout << "Maze is resizable ( and can be reset (cleared and re-randomized in runtime)\n";
		cout << "Default size is 11 x 11, do you want to resize (Only odd square sizes greater than 11^2 accepted)? y/n ";
		//ans = _getch(); //ITI.h
		cin >> ans;
		if ((ans == 'y') || (ans == 'Y'))
		{
			cout << "\nPlease enter ODD integer for maze size (Mazesize x Mazesize): ex: 11 for 11 x 11 maze (default):\n ";
			cin >> MazeSize;
			while ((MazeSize % 2 == 0) || (MazeSize < 11)) { //Even numbers have broken borders so are not accepted (even though algorithm runs)
				cout << "\nSorry, Please Enter ODD integer ( 11 or grater) only:\n";
				cin >> MazeSize;
			}
			cout << "\nMaze Size is " << MazeSize << " x " << MazeSize << endl;
		}
		else
		{
			cout << "\nMaze Size is 11 x 11:\n";
		}

		//MAZE COMMENCE
		unsigned int Seed = time(0);
		srand(Seed); //stdlib: // Maximum value that can be returned by the rand function:
		Game NewGame(896, 896, 32);
		NewGame.Run();

		cout << "\nYou have successfully completed the maze, want to restart the game? XD (y/n): \n";
		cin >> Check;
	}
	return 0;
}
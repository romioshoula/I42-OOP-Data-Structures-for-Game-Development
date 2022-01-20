//RandomMazeGenerator_header.h RamiWailShoula //One header file for functions declarations and bodies
//Entire Header for box2d/SFML SolarSpaceSystem

//Definistion of header

#ifndef RANDOMMAZEGENERATOR_FUNCTIONS_HPP
#define RANDOMMAZEGENERATOR_FUNCTIONS_HPP
 
int MazeSize = 11; //Odd No. for complete closed boundaries

//#includes

#include "SFML/Graphics.hpp"
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
//#include<stdio.h>
//#include <stdlib.h>
//#include <windows.h>
#include <conio.h> //for _getch

using namespace std;
using namespace sf;

//Function Classes

//1//MazeGeneration Functions Class

enum Direction { //Keys Directions (WASD,Up,Left,Down,Right)
	Left,
	Right,
	Up,
	Down,
	A,//A_Left,
	D,//D_Right,
	W,//W_Up,
	S//S_Down
};
class MazeGenerator //Class to handle Mazes (Generation, Paths, Clearing)
{
private:
	bool Generate(std::vector<int>& MazeArray, int x, int y);
	bool ClearMaze(std::vector<int>& MazeArray);
	void ProcessPath(std::vector<int>& MazeArray, int NewTileA, int NewTileB); // new tile a is 2 tiles from start point
																	// TileB is the inbetween tile
	int MazeSizeX;
	int MazeSizeY;
	std::vector<bool> Visited;
	std::stack <int> MyStack;
	int StartPoint;
public:
	void GenerateNewMaze(std::vector<int>& MazeArray, int sizeX, int sizeY);
};

//2//Game Functions Class

class Game //Class to hold all Game Processes 
{
public:
	Game(int ScreenWidth, int ScreenHeight, int TileSize);
	void Run(); // main game loop
private: // methods
	void ProcessEvents();
	void Update();
	void Render();
	void HandlePlayerInput(sf::Keyboard::Key Key, bool IsPressed);
	void SetStartandExitTiles(); // returns location of exit tile
	void TileCollision(int DirectionOfTravel);
public:  // variables
private: // variables
	sf::RenderWindow m_Window;
	std::vector<int> m_MazeData;
	MazeGenerator Maze;
	sf::Vector2i m_TileSize;
	sf::Vector2i m_MazeSize;
	sf::Clock m_FPS;
	sf::Vector2i m_ScreenSize;
	sf::Texture m_WallTexture;
	sf::Texture m_FloorTexture;
	sf::Texture m_PlayerTexture;
	sf::Texture m_ExitTexture;
	sf::Sprite m_Wall;
	sf::Sprite m_Floor;
	sf::Sprite m_Player;
	sf::Sprite m_Exit;
	float m_timesincelastupdate;
	const float m_TimePerFrame; // updates per frame.
	float m_LevelTime;
	sf::Vector2i m_ExitPos;
	float m_PlayerSpeed;
	bool m_PlayerExitedLevel;
	bool m_IsMovingLeft;
	bool m_IsMovingLeft_A;
	bool m_IsMovingRight;
	bool m_IsMovingRight_D;
	bool m_IsMovingUp;
	bool m_IsMovingUp_W;
	bool m_IsMovingDown;
	bool m_IsMovingDown_S;
	//sf::view
	sf::View m_GameView;
	sf::View m_GameInfoView;
};

//Functions

//1//MazeGeneration Functions

void MazeGenerator::GenerateNewMaze(std::vector<int>& mazearray, int mazexsize, int mazeysize) //Function Clears, Creates and Generates a randomized maze
{
	// maze maker using std::stack for extra large mazes, Eg.. 2001 x 2001 (resizable mazes)
	MazeSizeX = mazexsize;
	MazeSizeY = mazeysize;
	Visited.resize(MazeSizeX * MazeSizeY);
	for (auto c : Visited)
	{
		Visited[c] = false;
	}
	ClearMaze(mazearray);
	bool odd = false;
	while (!odd) // Randomize start position on grid for Maze Creation 
	{
		int startx = rand() % (MazeSizeX - 1) + 1;
		int starty = rand() % (MazeSizeY - 1) + 1;
		if (startx % 2 == 1 && starty % 2 == 1) // check to see if we have 2 odd numbers
		{
			odd = true;
			StartPoint = startx + (starty * MazeSizeX); // set new start point
		}
	}
	Visited[StartPoint] = true;
	mazearray[StartPoint] = 1;
	int xposcell = StartPoint % MazeSizeX; // x pos in tiles
	int yposcell = StartPoint / MazeSizeX; // y pos in tiles
	// call Map Generation function( Non Recursive )
	Generate(mazearray, xposcell, yposcell);
	return;
}
bool MazeGenerator::Generate(std::vector<int>& mazearray, int x, int y)
{
	int TileX = x;
	int TileY = y;
	int VisitedCells = 1; // start point has been visited
	int CurrentCell = StartPoint;
	MyStack.push(CurrentCell);
	std::vector <int> AvailableDirections;
	while (!MyStack.empty())
	{   //check available directions. if one is found push it onto available directions vector
		if (TileX - 2 > 0 && !Visited[CurrentCell - 2] &&
			TileX - 1 > 0 && !Visited[CurrentCell - 1]) // If both new tile and between tile is not visited and not outside map
		{
			// tiles are 1 option to visit.
			AvailableDirections.push_back(Direction::Left);
			AvailableDirections.push_back(Direction::A);
		}
		if (TileX + 2 < MazeSizeX && !Visited[CurrentCell + 2] &&
			TileX + 1 < MazeSizeX && !Visited[CurrentCell + 1]) // If both new tile and between tile is not visited and not outside map
		{
			// tiles are 1 option to visit.
			AvailableDirections.push_back(Direction::Right);
			AvailableDirections.push_back(Direction::D);
		}
		if (TileY - 2 > 0 && !Visited[CurrentCell - (MazeSizeX * 2)] &&
			TileY - 1 > 0 && !Visited[CurrentCell - MazeSizeX]) // If both new tile and between tile is not visited and not outside map
		{
			// tiles are 1 option to visit.
			AvailableDirections.push_back(Direction::Up);
			AvailableDirections.push_back(Direction::W);
		}
		if (TileY + 2 < MazeSizeY && !Visited[CurrentCell + (MazeSizeX * 2)] &&
			TileY + 1 < MazeSizeY && !Visited[CurrentCell + MazeSizeX]) // If both new tile and between tile is not visited and not outside map
		{
			// tiles are 1 option to visit.
			AvailableDirections.push_back(Direction::Down);
			AvailableDirections.push_back(Direction::S);
		}
		if (AvailableDirections.size() > 0)
		{
			std::random_shuffle(AvailableDirections.begin(), AvailableDirections.end()); // randomizes new direction for DFS
			switch (AvailableDirections[0])
			{
			case Direction::Up:
				ProcessPath(mazearray, CurrentCell - (MazeSizeX * 2), CurrentCell - MazeSizeX);
				MyStack.push(CurrentCell);
				CurrentCell -= MazeSizeX * 2;
				VisitedCells += 2;
				TileY -= 2;
				AvailableDirections.clear();
				break;
			case Direction::W:
				ProcessPath(mazearray, CurrentCell - (MazeSizeX * 2), CurrentCell - MazeSizeX);
				MyStack.push(CurrentCell);
				CurrentCell -= MazeSizeX * 2;
				VisitedCells += 2;
				TileY -= 2;
				AvailableDirections.clear();
				break;
			case Direction::Down:
				ProcessPath(mazearray, CurrentCell + (MazeSizeX * 2), CurrentCell + MazeSizeX);
				MyStack.push(CurrentCell);
				CurrentCell += MazeSizeX * 2;
				VisitedCells += 2;
				TileY += 2;
				AvailableDirections.clear();
				break;
			case Direction::S:
				ProcessPath(mazearray, CurrentCell + (MazeSizeX * 2), CurrentCell + MazeSizeX);
				MyStack.push(CurrentCell);
				CurrentCell += MazeSizeX * 2;
				VisitedCells += 2;
				TileY += 2;
				AvailableDirections.clear();
				break;
			case Direction::Left:
				ProcessPath(mazearray, CurrentCell - 2, CurrentCell - 1);
				MyStack.push(CurrentCell);
				CurrentCell -= 2;
				VisitedCells += 2;
				TileX -= 2;
				AvailableDirections.clear();
				break;
			case Direction::A:
				ProcessPath(mazearray, CurrentCell - 2, CurrentCell - 1);
				MyStack.push(CurrentCell);
				CurrentCell -= 2;
				VisitedCells += 2;
				TileX -= 2;
				AvailableDirections.clear();
				break;
			case Direction::Right:
				ProcessPath(mazearray, CurrentCell + 2, CurrentCell + 1);
				MyStack.push(CurrentCell);
				CurrentCell += 2;
				VisitedCells += 2;
				TileX += 2;
				AvailableDirections.clear();
				break;
			case Direction::D:
				ProcessPath(mazearray, CurrentCell + 2, CurrentCell + 1);
				MyStack.push(CurrentCell);
				CurrentCell += 2;
				VisitedCells += 2;
				TileX += 2;
				AvailableDirections.clear();
				break;
			}
		} // if available directions is not 0;
		else // no avialable direction to follow
		{
			// pop one from the stack to retry
			CurrentCell = MyStack.top();
			TileX = CurrentCell % MazeSizeX; // x pos in tiles
			TileY = CurrentCell / MazeSizeX; // y pos in tiles
			MyStack.pop();
		}
	}// while totalcells !=0
	return true;
}
bool MazeGenerator::ClearMaze(std::vector<int>& mazearray)
{
	for (auto&& a : Visited)
	{
		a = false;
	}
	for (unsigned int x = 0; x < mazearray.size(); x++)
	{
		mazearray[x] = 0;
	}
	return true;
}
void MazeGenerator::ProcessPath(std::vector<int>& mazearray, int NewTile, int BetweenTile)
{
	Visited[NewTile] = true;
	Visited[BetweenTile] = true;
	mazearray[NewTile] = 1;
	mazearray[BetweenTile] = 1;
}

//2//Game Functions

Game::Game(int ScreenWidth, int ScreenHeight, int TSize)
	:m_Window(sf::VideoMode(ScreenWidth, ScreenHeight), "2D Maze"),
	m_TileSize(TSize, TSize),
	m_MazeSize(MazeSize, MazeSize), //resizable maze size you can resize to large mazes (Eg.. (2001, 2001) )
	m_TimePerFrame(1.f / 120.f), //Frame update time
	//Keys
	m_IsMovingLeft(false),
	m_IsMovingLeft_A(false),
	m_IsMovingRight(false),
	m_IsMovingRight_D(false),
	m_IsMovingUp(false),
	m_IsMovingUp_W(false),
	m_IsMovingDown(false),
	m_IsMovingDown_S(false),
	m_PlayerSpeed(4.0f), //speed of movement
	m_ScreenSize(ScreenWidth, ScreenHeight)
{
	m_MazeData.resize(m_MazeSize.x * m_MazeSize.y);
	Maze.GenerateNewMaze(m_MazeData, m_MazeSize.x, m_MazeSize.y);
	SetStartandExitTiles();
	m_LevelTime = 0;
	//./Res/
	//Loading Textures //game entities //yes these comments are mine Rami Wail Shoula
	m_FloorTexture.loadFromFile("Floor.png", sf::IntRect(0, 0, m_TileSize.x, m_TileSize.y));
	m_WallTexture.loadFromFile("Wall.png", sf::IntRect(0, 0, m_TileSize.x, m_TileSize.y));
	m_PlayerTexture.loadFromFile("Player.png", sf::IntRect(0, 0, m_TileSize.x, m_TileSize.y));
	m_ExitTexture.loadFromFile("Exit.png", sf::IntRect(0, 0, m_TileSize.x, m_TileSize.y));

	m_Wall.setTexture(m_WallTexture);
	m_Floor.setTexture(m_FloorTexture);
	m_Player.setTexture(m_PlayerTexture);
	m_Exit.setTexture(m_ExitTexture);

	m_PlayerExitedLevel = false;
	m_GameView.setCenter(m_Player.getPosition().x, m_Player.getPosition().y);
	m_GameView.setSize(m_ScreenSize.x, m_ScreenSize.y); // change to variable screenwidth and screenheight
}
void Game::Run()
{
	sf::Clock Clock;
	float TimeSinceLastUpdate = 0;
	while (m_Window.isOpen())
	{
		float elapsedtime = Clock.restart().asSeconds();
		TimeSinceLastUpdate += elapsedtime;
		m_LevelTime += elapsedtime;
		while (TimeSinceLastUpdate > m_TimePerFrame)
		{
			TimeSinceLastUpdate = 0;
			ProcessEvents();
			Update();
		}
		Render();
	}
}
void Game::ProcessEvents()
{
	sf::Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_Window.close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			HandlePlayerInput(event.key.code, true);
		}
		if (event.type == sf::Event::KeyReleased)
		{
			HandlePlayerInput(event.key.code, false);
		}
	}
}
void Game::Update()
{
	// move player based on IsmovingLeft etc variables and check collisions

	if (m_IsMovingLeft)
	{
		m_Player.move(-m_PlayerSpeed, 0);
		TileCollision(Direction::Left);
	}
	if (m_IsMovingLeft_A)
	{
		m_Player.move(-m_PlayerSpeed, 0);
		TileCollision(Direction::Left);
	}
	if (m_IsMovingRight)
	{
		m_Player.move(m_PlayerSpeed, 0);
		TileCollision(Direction::Right);
	}
	if (m_IsMovingRight_D)
	{
		m_Player.move(m_PlayerSpeed, 0);
		TileCollision(Direction::Right);
	}
	if (m_IsMovingUp)
	{
		m_Player.move(0, -m_PlayerSpeed);
		TileCollision(Direction::Up);
	}
	if (m_IsMovingUp_W)
	{
		m_Player.move(0, -m_PlayerSpeed);
		TileCollision(Direction::Up);
	}
	if (m_IsMovingDown)
	{
		m_Player.move(0, m_PlayerSpeed);
		TileCollision(Direction::Down);
	}
	if (m_IsMovingDown_S)
	{
		m_Player.move(0, m_PlayerSpeed);
		TileCollision(Direction::Down);
	}
	if (!m_PlayerExitedLevel)
	{
		if (m_Player.getPosition().x == m_ExitPos.x * m_TileSize.x
			&& m_Player.getPosition().y == m_ExitPos.y * m_TileSize.y)
			// player has exited
		{
			m_PlayerExitedLevel = true;
		}
	}
	if (m_PlayerExitedLevel)
	{
		m_Window.close();
	}
}
void Game::Render()
{
	m_Window.clear(sf::Color::Magenta);
	m_GameView.setCenter(m_Player.getPosition().x, m_Player.getPosition().y);
	m_Window.setView(m_GameView);

	sf::Vector2f centrescreen;
	centrescreen = m_GameView.getCenter(); // view centre of player x and y
	int minx, miny, maxx, maxy;
	int renderx = centrescreen.x;
	int rendery = centrescreen.y;
	int a = (m_ScreenSize.x / m_TileSize.x + 3) / 2; // formula to draw additional tiles outside screen to allow smooth scrolling
	int xsize = a * m_TileSize.x;
	int ysize = a * m_TileSize.y;
	minx = renderx - xsize;
	miny = rendery - ysize;
	maxx = renderx + xsize;
	maxy = rendery + ysize;

	if (minx < 0)
	{
		minx = 0;
	}
	if (miny < 0)
	{
		miny = 0;
	}
	if (maxx > m_MazeSize.x * m_TileSize.x)
	{
		maxx = m_MazeSize.x * m_TileSize.x;
	}
	if (maxy > m_MazeSize.y * m_TileSize.y)
	{
		maxy = m_MazeSize.y * m_TileSize.y;
	}
	// setup ready for drawing method, 
	minx /= m_TileSize.x;
	maxx /= m_TileSize.x;
	miny /= m_TileSize.y;
	maxy /= m_TileSize.y;


	// DRAW TILES
	for (int x = minx; x < maxx; x++)
	{
		for (int y = miny; y < maxy; y++)
		{
			int a = m_MazeData[x + y * m_MazeSize.x];
			if (a == 0)//draw wall
			{
				m_Wall.setPosition(x * m_TileSize.x, y * m_TileSize.y);
				m_Window.draw(m_Wall);
			}
			else // draw floor
			{
				m_Floor.setPosition(x * m_TileSize.x, y * m_TileSize.y);
				m_Window.draw(m_Floor);
			}
		}
	}

	// Draw Exit
	m_Window.draw(m_Exit);
	// Draw Player
	m_Window.draw(m_Player);
	m_Window.display();
	m_Window.setView(m_GameInfoView); // status bar, time, lives etc
	m_Window.setView(m_Window.getDefaultView());
}
void Game::HandlePlayerInput(sf::Keyboard::Key Key, bool IsPressed)
{
	if (Key == sf::Keyboard::Escape)
	{
		m_Window.close();
	}
	if (Key == sf::Keyboard::Space && IsPressed == false) // Generate new maze when space is released
	{
		Maze.GenerateNewMaze(m_MazeData, m_MazeSize.x, m_MazeSize.y);
		SetStartandExitTiles();
		m_LevelTime = 0; // reset leveltime
	}

	if (Key == sf::Keyboard::Left)
	{
		m_IsMovingLeft = IsPressed;
	}
	if (Key == sf::Keyboard::A)
	{
		m_IsMovingLeft_A = IsPressed;
	}
	else if (Key == sf::Keyboard::Right)
	{
		m_IsMovingRight = IsPressed;
	}
	else if (Key == sf::Keyboard::D)
	{
		m_IsMovingRight_D = IsPressed;
	}
	if (Key == sf::Keyboard::Up)
	{
		m_IsMovingUp = IsPressed;
	}
	if (Key == sf::Keyboard::W)
	{
		m_IsMovingUp_W = IsPressed;
	}
	if (Key == sf::Keyboard::Down)
	{
		m_IsMovingDown = IsPressed;
	}
	else if (Key == sf::Keyboard::S)
	{
		m_IsMovingDown_S = IsPressed;
	}
}
void Game::SetStartandExitTiles() // returns location of exit tile
{
	int Pstartx = 1; int Pstarty = 1;
	bool playerstart = false;

	while (!playerstart)
	{
		int x = rand() % 3 + 1;
		int y = rand() % 3 + 1;
		int pstarttile = x + (y * m_MazeSize.x);
		Pstartx = x;
		Pstarty = y;
		if (m_MazeData[pstarttile] == 1)
		{
			playerstart = true;
		}
		m_Player.setPosition(Pstartx * m_TileSize.x, Pstarty * m_TileSize.x);
	}
	bool IsExitValid = false;
	while (!IsExitValid)
	{
		int percentx = (m_MazeSize.x / 10) + 4;
		int percenty = (m_MazeSize.y / 10) + 4; // use when ready!!!!!!
		int Exitx = rand() % percentx + (m_MazeSize.x - percentx);
		int Exity = rand() % percenty + (m_MazeSize.y - percenty); // change to percenty when ready!!!!!!
		int exit = Exitx + (Exity * m_MazeSize.x);
		if (m_MazeData[exit] == 1)
		{
			IsExitValid = true;
			m_ExitPos.x = Exitx;
			m_ExitPos.y = Exity;
			m_Exit.setPosition(m_ExitPos.x * m_TileSize.x, m_ExitPos.y * m_TileSize.y);
		}
	}
	return;
}
void Game::TileCollision(int DirectionOfTravel)
//No need to repeat for WASD keys so I will use the same switch case
{
	int xtile = -1;
	int ytile = -1;
	int CheckTileA = -1;
	int CheckTileB = -1;
	switch (DirectionOfTravel)
	{
	case Direction::Down:
		//Bottom Left Corner
		xtile = (m_Player.getPosition().x) / m_TileSize.x;
		ytile = (m_Player.getPosition().y + m_TileSize.y - 1) / m_TileSize.x;
		CheckTileA = xtile + (ytile * m_MazeSize.x);
		//Bottom Right Corner
		xtile = (m_Player.getPosition().x + m_TileSize.x - 1) / m_TileSize.x;
		ytile = (m_Player.getPosition().y + m_TileSize.y - 1) / m_TileSize.x;
		CheckTileB = xtile + (ytile * m_MazeSize.x);
		break;
	case Direction::Left:
		//Top Left Corner
		xtile = m_Player.getPosition().x / m_TileSize.x;
		ytile = m_Player.getPosition().y / m_TileSize.y;
		CheckTileA = xtile + (ytile * m_MazeSize.x);
		//Bottom Left
		xtile = m_Player.getPosition().x / m_TileSize.x;
		ytile = (m_Player.getPosition().y + m_TileSize.y - 1) / m_TileSize.y;
		CheckTileB = xtile + (ytile * m_MazeSize.x);
		break;
	case Direction::Up:
		// Top Left Corner
		xtile = m_Player.getPosition().x / m_TileSize.x;
		ytile = m_Player.getPosition().y / m_TileSize.y;
		CheckTileA = xtile + (ytile * m_MazeSize.x);
		//TopRight Corner
		xtile = (m_Player.getPosition().x + m_TileSize.x - 1) / m_TileSize.x;
		ytile = m_Player.getPosition().y / m_TileSize.y;
		CheckTileB = xtile + (ytile * m_MazeSize.x);
		break;
	case Direction::Right:
		// Top Right Corner
		xtile = (m_Player.getPosition().x + m_TileSize.x - 1) / m_TileSize.x;
		ytile = m_Player.getPosition().y / m_TileSize.y;
		CheckTileA = xtile + (ytile * m_MazeSize.x);
		//Bottom Right Corner
		xtile = (m_Player.getPosition().x + m_TileSize.x - 1) / m_TileSize.x;
		ytile = (m_Player.getPosition().y + m_TileSize.y - 1) / m_TileSize.y;
		CheckTileB = xtile + (ytile * m_MazeSize.x);
		break;
	}

	if (m_MazeData[CheckTileA] == 0 || m_MazeData[CheckTileB] == 0) // Check both points of players direction
	{																// IE Down Check Bottom Left & Bottom Right Corners
		switch (DirectionOfTravel)
		{
		case Direction::Up:
			m_Player.setPosition(m_Player.getPosition().x, (ytile + 1) * m_TileSize.y);
			break;
		case Direction::Down:
			m_Player.setPosition(m_Player.getPosition().x, (ytile - 1) * m_TileSize.y);
			break;
		case Direction::Left:
			m_Player.setPosition((xtile + 1) * m_TileSize.x, m_Player.getPosition().y);
			break;
		case Direction::Right:
			m_Player.setPosition((xtile - 1) * m_TileSize.x, m_Player.getPosition().y);
			break;
		}
	}
	return;
}


#endif // RANDOMMAZEGENERATOR_FUNCTIONS_HPP
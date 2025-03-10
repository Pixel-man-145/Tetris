#include<iostream>
class Figure
{
	private:

	static int fieldX;				//field size
	static int fieldY;
	int posX;						//figure position
	int posY;
	int sizeX;						//figure size
	int sizeY;
	int centerX;					//the center relative to the position of the figure around which it will rotate
	int centerY;
	bool **hXY = nullptr;			//shape of the figure
	int type;						//body type: 0 - rotates freely; 1 - only two positions; 2 - does not rotate
	bool turn = 0;					//figure position for figure type 1

	public:

	Figure(int posX_, int posY_, bool** hXY_, int sizeX_, int sizeY_, int centerX_, int centerY_, int type_ = 0, bool turn_ = 0)	//constructor
	{
		posX = posX_;
		posY = posY_;
		sizeX = sizeX_;
		sizeY = sizeY_;
		centerX = centerX_;
		centerY = centerY_;
		type = type_;
		turn = turn_;

		hXY = new bool*[sizeX];
		for (int i = 0; i < sizeX; i++)
		{
			hXY[i] = new bool[sizeY];
		}
		for (int j = 0; j < sizeY; j++)
		{
			for (int i = 0; i < sizeX; i++)
			{
				hXY[i][j] = hXY_[i][j];
			}
		}	
	}

	Figure(Figure& Figure_)			//copy constructor
	{
		posX = Figure_.posX;
		posY = Figure_.posY;
		sizeX = Figure_.sizeX;
		sizeY = Figure_.sizeY;
		centerX = Figure_.centerX;
		centerY = Figure_.centerY;
		type = Figure_.type;
		turn = Figure_.turn;

		hXY = new bool*[sizeX];
		for (int i = 0; i < sizeX; i++)
		{
			hXY[i] = new bool[sizeY];
		}
		for (int j = 0; j < sizeY; j++)
		{
			for (int i = 0; i < sizeX; i++)
			{
				hXY[i][j] = Figure_.hXY[i][j];
			}
		}
	}

	~Figure()						//destructor
	{
		for (int i = 0; i < sizeX; i++)
		{
			delete[] hXY[i];
		}
		delete[] hXY;
	}

	Figure& operator=(Figure& Figure_)
	{

		bool** nhXY = new bool*[Figure_.sizeX];
		for (int i = 0; i < Figure_.sizeX; i++)
		{
			nhXY[i] = new bool[Figure_.sizeY];
		}
		for (int j = 0; j < Figure_.sizeY; j++)
		{
			for (int i = 0; i < Figure_.sizeX; i++)
			{
				nhXY[i][j] = Figure_.hXY[i][j];
			}
		}
		
		for (int i = 0; i < sizeX; i++)
		{
			delete[] hXY[i];
		}
		delete[] hXY;	

		hXY=nhXY;
		posX = Figure_.posX;
		posY = Figure_.posY;
		sizeX = Figure_.sizeX;
		sizeY = Figure_.sizeY;
		centerX = Figure_.centerX;
		centerY = Figure_.centerY;
		type = Figure_.type;

		return *this;
	}
	Figure& operator+(Figure& Figure_)		//overlapping of figures; the first figure must completely contain the second
	{
		for (int j = 0; j < Figure_.sizeY; j++)
		{
			for (int i = 0; i < Figure_.sizeX; i++)
			{
				hXY[i+Figure_.posX-posX][j+Figure_.posY-posY] = hXY[i+Figure_.posX-posX][j+Figure_.posY-posY] || Figure_.hXY[i][j];
			}
		}
		return *this;
	}

	Figure& operator-(Figure& Figure_)		//subtracting a figure from another figure; the first figure must completely contain the second
	{
		for (int j = 0; j < Figure_.sizeY; j++)
		{
			for (int i = 0; i < Figure_.sizeX; i++)
			{
				hXY[i+Figure_.posX-posX][j+Figure_.posY-posY] = hXY[i+Figure_.posX-posX][j+Figure_.posY-posY] && !Figure_.hXY[i][j];
			}
		}
		return *this;
	}

	void move(int a, int b)
	{
		posX += a;
		posY += a;
	}
	
	void rotate(bool a)			//figure rotation; a = 0 - clockwise; a = 1 - counterclockwise
	{
		switch (type)
		{
			case 1:
				a = turn;
				turn += 1;
			case 0:
			int ncenterX = !a*(sizeY-1)+(!a-a)*centerY;
			int ncenterY = a*(sizeX-1)+(a-!a)*centerX;
			int nposX = posX + centerX - ncenterX;
			int nposY = posY + centerY - ncenterY;

			bool** nhXY = new bool*[sizeX];
			for (int i = 0; i < sizeX; i++)
			{
				nhXY[i] = new bool[sizeY];
			}
			for (int j = 0; j < sizeY; j++)
			{
				for (int i = 0; i < sizeX; i++)
				{
					nhXY[j][i] = hXY[a?sizeX-1-i:i][a?j:sizeY-1-j];
				}
			}
			for (int i = 0; i < sizeX; i++)
			{
				delete[] hXY[i];
			}
			delete[] hXY;

			hXY = nhXY;
			sizeX += sizeY;
			sizeY = sizeX - sizeY;
			sizeX -= sizeY;
			centerX = ncenterX;
			centerY = ncenterY;
			posX = nposX;
			posY = nposY;
			break;
		}
	}

	bool CheckFigure(Figure& Figure_)		//checks if there are any intersections between shapes; the first figure must completely contain the second
	{
		for (int j = 0; j < Figure_.sizeY; j++)
		{
			for (int i = 0; i < Figure_.sizeX; i++)
			{
				if (hXY[i+Figure_.posX-posX][j+Figure_.posY-posY] && Figure_.hXY[i][j])
				{
					return 0;
				}
			}
		}
		return 1;
	}

	bool CheckField()			//checks if the figure is in the field
	{
		return (posX >= 0) && (posY >=0) && (posX + sizeX-1 < fieldX) && (posX + sizeX-1 < fieldX);
	}
	
	void ClearLine(int a)		//zeroes the horizontal line by counting from zero vertically
	{
		for (int i; i < sizeX; i++)
		{
			hXY[i][a] = 0;
		}
	}

	int SearchFullLine()		//finds the closest filled line relative to the origin vertically
	{
		for (int j = 0; j < sizeY; j++)
		{
			for (int i = 0; i < sizeX; i++)
			{
				if (hXY[i][j] == 0)
				{
					break;
				}
			}
			return j;
		}
		return -1;
	}

	void shift(int a)			//shifts all lines of the figure down to the specified y coordinate
	{
		for (int j = a; j > 0; j--)
		{
			for (int i = 0; i < sizeX; i++)
			{
				hXY[i][j]=hXY[i][j-1];
			}
		}

		for (int i = 0; i < sizeX; i++)
			{
				hXY[i][0]=0;
			}
	}
	
	void PrintFigure()
	{
		for (int j = 0; j < sizeY; j++)
		{
			for (int i = 0; i < sizeX; i++)
			{
				std::cout << hXY[i][j];
			}
			std::cout << std::endl;
		}
	}
	
};
class Figure
{
	private:

	static int fieldX;
	static int fieldY;	
	int posX;
	int posY;
	int sizeX;
	int sizeY;
	int centerX;
	int centerY;
	bool **hXY = nullptr;
	int type;
	bool turn = 0;

	public:

	Figure(int posX_, int posY_, bool** hXY_, int sizeX_, int sizeY_, int centerX_, int centerY_, int type_ = 0, bool turn_ = 0)
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

	Figure(Figure& Figure_)
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

	~Figure()
	{
		for (int i = 0; i < sizeX; i++){
			delete[] hXY[i];
		}
		delete[] hXY;
	}

	Figure& operator=(Figure& Figure_){

		for (int i = 0; i < sizeX; i++){
			delete[] hXY[i];
		}
		delete[] hXY;	
		
		posX = Figure_.posX;
		posY = Figure_.posY;
		sizeX = Figure_.sizeX;
		sizeY = Figure_.sizeY;
		centerX = Figure_.centerX;
		centerY = Figure_.centerY;
		type = Figure_.type;

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
		return *this;
	}
	Figure& operator+(Figure& Figure_){
		for (int j = 0; j < Figure_.sizeY; j++){
			for (int i = 0; i < Figure_.sizeX; i++){
				hXY[i+Figure_.posX][j+Figure_.posY] |= Figure_.hXY[i][j];
			}
		}
		return *this;
	}

	void move(int a, int b){
		posX += a;
		posY += a;
	}
	
	void rotate(bool a){
		switch (type){
			case 1:
				a = turn;
				turn += 1;
			case 0:
			int ncenterX = !a*(sizeY-1)+(!a-a)*centerY;
			int ncenterY = a*(sizeX-1)+(a-!a)*centerX;
			int nposX = posX + centerX - ncenterX;
			int nposY = posY + centerY - ncenterY;

			bool** nhXY = nullptr;
			nhXY = new bool*[sizeX];
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
			for (int i = 0; i < sizeX; i++){
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

	Figure& operator-(Figure& _Figure){}
	Figure& operator==(Figure& _Figure){}
	bool CheckField(Figure& _Figure){}
	bool CheckLine(int a){}
	void ClearLine(int a){}
	int SearchFullLine(Figure& _Figure){}
	void shift(int a){}
};
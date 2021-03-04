
#include "iGraphics.h"
#include<time.h>
#include<stdlib.h>
#include<string.h>

#define open  1
#define close 0

// structure for High scorer
struct players 
{
	char name[30];
	int score;
};
FILE *file;
players highScorer[10] = { { NULL }, { 0 } };
char strScore[10];

//A structure for rectangles of maze
struct rectangle {
	int x, y, width, hight; 
};
rectangle rectangles[100] = { { 10, 465, 680, 25 }, { 10, 275, 25, 200 }, { 665, 275, 25, 200 }, { 10, 10, 680, 25 }, { 10, 10, 25, 215 },
{ 665, 10, 25, 215 }, { 160, 430, 25, 35 }, { 510, 430, 25, 35 }, { 165, 35, 60, 35 }, { 475, 35, 60, 35 }, { 35, 275, 35, 25 },
{ 630, 275, 35, 25 }, { 30, 165, 40, 60 }, { 630, 165, 60, 60 }, { 245, 390, 55, 25 }, { 400, 390, 55, 25 }, { 205, 355, 20, 20 },
{ 475, 355, 20, 20 }, { 280, 315, 25, 25 }, { 395, 315, 25, 25 }, { 88, 85, 25, 25 }, { 590, 85, 25, 25 }, { 125, 165, 60, 60 },
{ 165, 125, 60, 60 }, { 225, 165, 75, 20 }, { 280, 90, 135, 20 }, { 475, 125, 60, 60 }, { 395, 165, 80, 20 }, { 515, 165, 60, 60 }, 
{ 243, 240, 213, 20 }, { 243, 240, 20, 57 }, { 437, 240, 20, 57 }, { 125, 275, 60, 20 }, { 125, 275, 20, 100 }, { 88, 355, 40, 20 }, 
{ 88, 355, 20, 55 }, { 515, 275, 57, 22 }, { 552, 293, 20, 80 }, { 565, 355, 46, 18 }, {592,355,20,55} };

//flags for pages
int welcomePage = open, name_inputPG = close, game_startPG = close, instructPG = close, highscorePG = close, gameOverPG = close; 
int r, g, b; //random color.

bool pause = false;

//Declaration related to mice.
int mouse_alive[3] = { 15, 45, 75 };//Show mice number 
int mLife = 3, caught = 0, index = 0;
char mName[20] = { "Unknown" }, strCaught[10], strmLife[10], strpowerTime[10];
double mice_x = 15, mice_y = 230;
double special_x = 320, special_y = 520;
int cheese_x[6] = { 335, 320, 520, 40, 630, 150 }, cheese_y[6] = { 270, 45, 305, 40, 40, 305 };

//for mice character rendering
char jerryRight[3][50] = { "images\\character\\miceR0.bmp", "images\\character\\miceR1.bmp", "images\\character\\miceR2.bmp" };
char jerryLeft[3][50] = { "images\\character\\miceL0.bmp", "images\\character\\miceL1.bmp", "images\\character\\miceL2.bmp" };
int jerryIndex = 0, in = 0, jerrySpeed = 2.5, jk = 0, jpTime = 15;
bool jerryDirection = true, jerryKilled = false, jrPower = false;

//for cat character rendering
double cat_x[10] = { 320, 315, 335, 245, 578, 40, 85, 585 };
double cat_y[10] = { 115, 40, 265, 420, 305, 410, 45, 45 };
char tomRight[3][50] = { "images\\character\\CatR1.bmp", "images\\character\\CatR2.bmp", "images\\character\\CatR3.bmp" };
char tomLeft[3][50] = { "images\\character\\CatL1.bmp", "images\\character\\CatL2.bmp", "images\\character\\CatL3.bmp" };
int tomIndex[10] = { 0 };
int catMovement[10] = { 0 }, cIn = 0, vIndex = 0;
int tomDirection[10] = { 0, 1, 0, 1, 0, 1, 0, 1 };
int bell_x = -1000, bell_y = -1000;
int kill = 0;
bool belled = false, belled1=false;

//High scores text co-ordinates.
double high_n_x[5] = { 200, 200, 200, 200, 200 }, high_s_x[5] = { 430, 430, 430, 430, 430 };
double high_n_y[5] = { 270, 240, 210, 180, 150 }, high_s_y[5] = { 270, 240, 210, 180, 150 };

bool musicOn = true;

//Methods of drawings
/////////////////////

void renderColor()//randoming colour.
{
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
}
void draw_welcome_page()//Drawing welcome page
{
	iShowBMP(0, 0, "images\\Background.bmp");
	iShowBMP2(80, 230, "images\\button\\playIcon.bmp",0);
	iShowBMP2(80, 150, "images\\button\\highscoreIcon0.bmp",0);
	iShowBMP2(80, 75, "images\\button\\instructionIcon.bmp",0);
	iSetColor(r, g, b);
	iText(50, 30, "CLICK TO PROCEED...", GLUT_BITMAP_TIMES_ROMAN_24);
}

void draw_Input_page()//Drawing name input page
{
	iShowBMP(0, 0, "images\\InputPageBC.bmp");
	iShowBMP2(0, 545, "images\\button\\backButton.bmp",0);
	iSetColor(164, 0, 164);
	iText(25, 300, "  Enter Your mouse name:", GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(r, g, b);
	iText(25, 165, "  Press 'ENTER' to continue..", GLUT_BITMAP_TIMES_ROMAN_24);
	iShowBMP2(25, 185, "images\\button\\textInput.bmp",0);
	iSetColor(255,255,255);
	iText(70, 225, mName, GLUT_BITMAP_TIMES_ROMAN_24);
}

void draw_gaming_page()//Drawing gaming page
{
	iShowBMP(0, 500, "images\\GamingPageUpperBC.bmp");
	iShowBMP(0, 0, "images\\GamingPageBc.bmp");
	for (int i = 0; i < 100; i++)//Drawing maze
	{
		iSetColor(189, 56, 47);
		iFilledRectangle(rectangles[i].x, rectangles[i].y, rectangles[i].width, rectangles[i].hight);
	}

	//info on gaming status
	iSetColor(0, 0, 0);
	iText(15, 570, "Mouse Name :", GLUT_BITMAP_9_BY_15);
	iText(130, 570, mName, GLUT_BITMAP_HELVETICA_18);
	iText(15, 540, "Mouse Alive :", GLUT_BITMAP_9_BY_15);
	iText(530, 570, "Cat Caught :", GLUT_BITMAP_9_BY_15);
	_itoa_s(caught, strCaught, 10);
	iText(645, 570, strCaught, GLUT_BITMAP_TIMES_ROMAN_24);
	_itoa_s(mLife,strmLife, 10);
	iText(137, 540, "0", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(150, 540, strmLife, GLUT_BITMAP_TIMES_ROMAN_24);
	iShowBMP2(0, 225, "images\\jerryHomeLeft.bmp", 0);
	iShowBMP2(650, 225, "images\\jerryHomeRight.bmp", 0);

	for (int i = 0; i < mLife; i++)//draw number of alive mice
	{
		iShowBMP2(mouse_alive[i], 495, "images\\mice.bmp", 0);
	}
	if (jrPower) //Jerry powered up draw
	{
		if (!jerryKilled)
		{
			iText(280, 515, "Time remaining:");
			_itoa_s(jpTime, strpowerTime, 10);
			iShowBMP2(320, 535, "images\\character\\poweredJerry.bmp", 0);
			iText(405, 515, strpowerTime);
		}
	}
	if (!jrPower && !jerryKilled)
	{
		iShowBMP2(320, 535, "images\\character\\normalJerry.bmp", 0);
	}

	//Cheese draw
	for (int i = 0; i < 6;i++)
	iShowBMP2(cheese_x[i], cheese_y[i], "images\\cheese.bmp", 0);

	//Drawing character
	if (!jerryKilled)
	{
		if (jerryDirection)
		{
			iShowBMP2(mice_x, mice_y, jerryRight[jerryIndex], 0);
		}
		else
		{
			iShowBMP2(mice_x, mice_y, jerryLeft[jerryIndex], 0);
		}
	}
	if (jerryKilled) //Tom emo when jerry killed
	{
		iShowBMP2(320, 510, "images\\character\\tomEmo.bmp", 0);
	}
	
	for (int i = 0; i < 8; i++) //drawing cats
	{
			if (tomDirection[i] == 0)
			{
				iShowBMP2(cat_x[i], cat_y[i], tomRight[tomIndex[i]], 0);
			}
			if (tomDirection[i] == 1)
			{
				iShowBMP2(cat_x[i], cat_y[i], tomLeft[tomIndex[i]], 0);
			}
	}

	//Bell the cat
	if (belled)
	iShowBMP2(bell_x, bell_y, "images\\character\\bell.bmp", 0);
}

//Drawing High Score page.
void draw_highscore_page()
{
	iShowBMP(0, 0, "images\\highScoreBC.bmp");
	iShowBMP2(0, 545, "images\\button\\backButton.bmp", 0);
	for (int i = 0; i < 5; i++)
	{
		iText(high_n_x[i], high_n_y[i], highScorer[i].name,GLUT_BITMAP_HELVETICA_18);
		_itoa_s(highScorer[i].score,strScore, 10);
		iText(high_s_x[i], high_s_y[i], strScore, GLUT_BITMAP_HELVETICA_18);
	}
}

//Drawing Instruction page.
void draw_instruction_page()
{
	iShowBMP(0, 0, "images\\instructionBCa.bmp");
	iShowBMP2(0, 545, "images\\button\\backButton.bmp", 0);
}

//Drawing Game Over page.
void draw_gameOver_page()
{
	for (int i = 1; i <= 8; i++)
	{
		iPauseTimer(i);
		pause = true;
	}

	iShowBMP(100, 100, "images\\gameOverBC.bmp");
	iShowBMP2(190, 310, "images\\gameOver.bmp", 0);
	iShowBMP2(155, 130, "images\\button\\retryButton1.bmp", 0);
	iShowBMP2(310, 130, "images\\button\\homeButton.bmp", 0);
	iShowBMP2(460, 130, "images\\button\\endButton.bmp", 0);
	iSetColor(255, 255, 0);
	iText(250, 280, "Hey, ", GLUT_BITMAP_HELVETICA_18);
	iText(300, 280, mName, GLUT_BITMAP_HELVETICA_18);
	iText(250, 245, "You caught ", GLUT_BITMAP_HELVETICA_18);
	iText(355, 245, strCaught, GLUT_BITMAP_HELVETICA_18);
	iText(375, 245, " cats", GLUT_BITMAP_HELVETICA_18);
	iText(230, 220, "HELP: Go to 'HOME' and see instructions...");
	iSetColor(r, g, b);
	iText(150, 107, "RETRY", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(310, 107, "HOME", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(460, 107, "QUITE", GLUT_BITMAP_TIMES_ROMAN_24);
}

void iDraw()
{
	iClear();

	//Calling to draw pages.
	if (welcomePage == open)
	{
		draw_welcome_page();
	}
	else if (name_inputPG == open)
	{
		draw_Input_page();
	}
	else if (game_startPG == open)
	{
		draw_gaming_page();
	}
	else if (highscorePG == open)
	{
		draw_highscore_page();
	}
	else if (instructPG == open)
	{
		draw_instruction_page();
	}
	if (gameOverPG == open && game_startPG == open)
	{
		draw_gameOver_page();
	}
}

void iMouseMove(int mx, int my)
{
	//place your codes here
}
//Set cats default co-ordinates for re-appearing
void setDefaultCat()
{
	cat_x[0] = 320;
	cat_y[0] = 115;
	cat_x[1] = 315;
	cat_y[1] = 40;
	cat_x[2] = 335;
	cat_y[2] = 265;
	cat_x[3] = 245;
	cat_y[3] = 420;
	cat_x[4] = 578;
	cat_y[4] = 305;
	cat_x[5] = 40;
	cat_y[5] = 410;
	cat_x[6] = 85;
	cat_y[6] = 45;
	cat_x[7] = 585;
	cat_y[7] = 45;
}

//Methodes for actions using mouse
void mouseListener(int mx,int my)
{
	if (welcomePage == open ) //Actions in welcome page
	{
		if (mx > 80 && mx<260 && my>230 && my < 300) //Start button.
		{
			name_inputPG = open;
			welcomePage = close;
		}
		if (mx > 85 && mx<260 && my>155 && my < 212) //HighScore button.
		{
			highscorePG = open;
			welcomePage = close;
		}
		if (mx > 85 && mx<255 && my>75 && my < 132) //Instruction button.
		{
			instructPG = open;
			welcomePage = close;
		}
	}

	if (highscorePG == open) //Actions in Score page
	{
		if (mx > 0 && mx<180 && my>545 && my < 600) //Back button
		{
			highscorePG = close;
			welcomePage = open;
		}
	}

	if (instructPG == open) //Actions in instruction page
	{
		if (mx > 0 && mx<180 && my>545 && my < 600) //Back button
		{
			instructPG = close;
			welcomePage = open;
		}
	}

	if (name_inputPG == open) //Actions in name input page
	{
		if (mx > 0 && mx<180 && my>545 && my < 600) //Back button
		{
			name_inputPG = close;
			welcomePage = open;
		}
	}

	if (gameOverPG == open) //Actions in game over page
	{
		if (mx > 160 && mx < 220 && my > 135 && my < 195) //Retry button
		{
			mLife = 3;
			caught = 0;
			for (int i = 1; i <= 8; i++)
				iResumeTimer(i);

			gameOverPG = close;
			pause = false;
			setDefaultCat();
		}
		if (mx > 310 && mx<375 && my>135 && my < 200) //Home button
		{
			welcomePage = open;
			gameOverPG = close;
			game_startPG = close;
			mLife = 3;
			caught = 0;
			pause = false;
			for (int i = 1; i <= 8; i++)
			{
				iResumeTimer(i);
			}
			setDefaultCat();
		}
		if (mx > 465 && mx<530 && my>135 && my < 195) //Quite button
		{
			exit(0);
		}
	}
}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//printf("x:%d\ty:%d\n", mx, my);
		mouseListener(mx, my);
		PlaySound("sounds\\buttonSound0.wav", NULL, SND_ASYNC);		
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	}
}

//Getting name of mouse.
void input(char key) 
{
	if (key != '\r')
	{
		if (key != ' ')
		{
			if (key != '\b')
			{
				mName[index] = key;
				index++;
				mName[index] = NULL;
			}
			else
			{
				if (index != 0)
					index--;
				mName[index] = NULL;
			}
		}
	}
	else
	{
		name_inputPG = close;
		game_startPG = open;
	}
}

void iKeyboard(unsigned char key)
{
	if (name_inputPG == open)
	{
		input(key);
	}
	if (key == 'm' && name_inputPG == close)
	{
		if (musicOn)
		{
			musicOn = false;
			PlaySound(0, 0, 0);
		}
		else
		{
			musicOn = true;
			PlaySound("sounds\\backgroundMusic0.wav", NULL, SND_LOOP | SND_ASYNC);
		}
	}
	if (key == 'p' && game_startPG == open)
	{
		for (int i = 1; i <= 8; i++)
		{
			iPauseTimer(i);
		}
		pause = true;
	}
	if (key == 'r' && game_startPG == open)
	{
		for (int i = 1; i <= 8; i++)
		{
			iResumeTimer(i);
		}
		pause = false;
	}
}

//methods for checking rectangles area.
int check(char direction,int i)
{
	if (direction == 'r') //Right move check
	{
		if (mice_x + 40 <= rectangles[i].x || mice_x - 5 >= rectangles[i].x + rectangles[i].width || mice_y + 35 <= rectangles[i].y || mice_y - 5 >= rectangles[i].y + rectangles[i].hight)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	if (direction == 'l') //Left move check
	{
		if (mice_x + 35 <= rectangles[i].x || mice_x - 10 >= rectangles[i].x + rectangles[i].width || mice_y + 35 <= rectangles[i].y || mice_y - 5 >= rectangles[i].y + rectangles[i].hight)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	if (direction == 'u') //Up move check
	{
		if (mice_x + 35 <= rectangles[i].x || mice_x - 5 >= rectangles[i].x + rectangles[i].width || mice_y + 40 <= rectangles[i].y || mice_y - 5 >= rectangles[i].y + rectangles[i].hight)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	if (direction == 'd') //Down move check
	{
		if (mice_x + 35 <= rectangles[i].x || mice_x - 5 >= rectangles[i].x + rectangles[i].width || mice_y + 35 <= rectangles[i].y || mice_y - 10 >= rectangles[i].y + rectangles[i].hight)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

//Method to move mice
void miceMove(char key)
{
	if (key == GLUT_KEY_RIGHT)
	{
		if (check('r', 0) && check('r', 1) && check('r', 2) == 1 && check('r', 3) == 1 && check('r', 4) == 1 &&
			check('r', 5) == 1 && check('r', 6) == 1 && check('r', 7) == 1 && check('r', 8) == 1 && check('r', 9) == 1 &&
			check('r', 10) == 1 && check('r', 11) == 1 && check('r', 12) == 1 && check('r', 13) == 1 && check('r', 14) == 1 &&
			check('r', 15) == 1 && check('r', 16) == 1 && check('r', 17) == 1 && check('r', 18) == 1 && check('r', 19) == 1 &&
			check('r', 20) == 1 && check('r', 21) == 1 && check('r', 22) == 1 && check('r', 23) == 1 && check('r', 24) == 1 &&
			check('r', 25) == 1 && check('r', 26) == 1 && check('r', 27) == 1 && check('r', 28) == 1 && check('r', 29) == 1 &&
			check('r', 30) == 1 && check('r', 31) == 1 && check('r', 32) == 1 && check('r', 33) == 1 && check('r', 34) == 1 &&
			check('r', 35) == 1 && check('r', 36) == 1 && check('r', 37) == 1 && check('r', 38) == 1 && check('r', 39) == 1)
		{
			if (!jerryKilled)
			{
				mice_x += jerrySpeed;
				in++;
				if (in % 2 == 0)
					jerryIndex++;
				if (jerryIndex == 3)
				{
					jerryIndex = 0;
				}
				jerryDirection = true;
			}
		}
	}
	if (key == GLUT_KEY_LEFT)
	{
		if (check('l', 0) == 1 && check('l', 1) == 1 && check('l', 2) == 1 && check('l', 3) == 1 && check('l', 4) == 1 &&
			check('l', 5) == 1 && check('l', 6) == 1 && check('l', 7) == 1 && check('l', 8) == 1 && check('l', 9) == 1 &&
			check('l', 10) == 1 && check('l', 11) == 1 && check('l', 12) == 1 && check('l', 13) == 1 && check('l', 14) == 1 &&
			check('l', 15) == 1 && check('l', 16) == 1 && check('l', 17) == 1 && check('l', 18) == 1 && check('l', 19) == 1 &&
			check('l', 20) == 1 && check('l', 21) == 1 && check('l', 22) == 1 && check('l', 23) == 1 && check('l', 24) == 1 &&
			check('l', 25) == 1 && check('l', 26) == 1 && check('l', 27) == 1 && check('l', 28) == 1 && check('l', 29) == 1 &&
			check('l', 30) == 1 && check('l', 31) == 1 && check('l', 32) == 1 && check('l', 33) == 1 && check('l', 34) == 1 &&
			check('l', 35) == 1 && check('l', 36) == 1 && check('l', 37) == 1 && check('l', 38) == 1 && check('l', 39) == 1)
		{
			if (!jerryKilled)
			{
				mice_x -= jerrySpeed;
				in++;
				if (in % 2 == 0)
					jerryIndex++;
				if (jerryIndex == 3)
				{
					jerryIndex = 0;
				}
				jerryDirection = false;
			}
		}
	}
	if (key == GLUT_KEY_UP)
	{
		if (check('u', 0) == 1 && check('u', 1) == 1 && check('u', 2) == 1 && check('u', 3) == 1 && check('u', 4) == 1 &&
			check('u', 5) == 1 && check('u', 6) == 1 && check('u', 7) == 1 && check('u', 8) == 1 && check('u', 9) == 1 &&
			check('u', 10) == 1 && check('u', 11) == 1 && check('u', 12) == 1 && check('u', 13) == 1 && check('u', 14) == 1 &&
			check('u', 15) == 1 && check('u', 16) == 1 && check('u', 17) == 1 && check('u', 18) == 1 && check('u', 19) == 1 &&
			check('u', 20) == 1 && check('u', 21) == 1 && check('u', 22) == 1 && check('u', 23) == 1 && check('u', 24) == 1 &&
			check('u', 25) == 1 && check('u', 26) == 1 && check('u', 27) == 1 && check('u', 28) == 1 && check('u', 29) == 1 &&
			check('u', 30) == 1 && check('u', 31) == 1 && check('u', 32) == 1 && check('u', 33) == 1 && check('u', 34) == 1 &&
			check('u', 35) == 1 && check('u', 36) == 1 && check('u', 37) == 1 && check('u', 38) == 1 && check('u', 39) == 1)
		{
			if (!jerryKilled)
			{
				mice_y += jerrySpeed;
				in++;
				if (in % 2 == 0)
					jerryIndex++;
				if (jerryIndex == 3)
				{
					jerryIndex = 0;
				}
			}
		}
	}
	if (key == GLUT_KEY_DOWN)
	{
		if (check('d', 0) == 1 && check('d', 1) == 1 && check('d', 2) == 1 && check('d', 3) == 1 && check('d', 4) == 1 &&
			check('d', 5) == 1 && check('d', 6) == 1 && check('d', 7) == 1 && check('d', 8) == 1 && check('d', 9) == 1 &&
			check('d', 10) == 1 && check('d', 11) == 1 && check('d', 12) == 1 && check('d', 13) == 1 && check('d', 14) == 1 &&
			check('d', 15) == 1 && check('d', 16) == 1 && check('d', 17) == 1 && check('d', 18) == 1 && check('d', 19) == 1 &&
			check('d', 20) == 1 && check('d', 21) == 1 && check('d', 22) == 1 && check('d', 23) == 1 && check('d', 24) == 1 &&
			check('d', 25) == 1 && check('d', 26) == 1 && check('d', 27) == 1 && check('d', 28) == 1 && check('d', 29) == 1 &&
			check('d', 30) == 1 && check('d', 31) == 1 && check('d', 32) == 1 && check('d', 33) == 1 && check('d', 34) == 1 &&
			check('d', 35) == 1 && check('d', 36) == 1 && check('d', 37) == 1 && check('d', 38) == 1 && check('d', 39) == 1)
		{
			if (!jerryKilled)
			{
				mice_y -= jerrySpeed;
				in++;
				if (in % 2 == 0)
					jerryIndex++;
				if (jerryIndex == 3)
				{
					jerryIndex = 0;
				}
			}
		}
	}

	//Jerry Home Entering
	if (mice_x + 35 >= 685)
	{
		mice_x = 12;
		PlaySound("sounds\\transport.wav", NULL, SND_ASYNC);
	}
	if (mice_x <= 10)
	{
		mice_x = 650;
		PlaySound("sounds\\transport.wav", NULL, SND_ASYNC);
	}

	//Clashing
	for (int i = 0; i < 8; i++)
	{
		if (tomDirection[i] == 0)
		{
			if (jerryDirection)
			{
				if (mice_x + 35 >= cat_x[i] && mice_x + 35 <= cat_x[i] + 5 && mice_y + 10 >= cat_y[i] && mice_y+10 <= cat_y[i] + 30)
				{
					caught++;
					bell_x = cat_x[i];
					bell_y = cat_y[i];
					cat_x[i] = -10000;
					belled1 = true;
					kill = i;
					belled = true;
					PlaySound("sounds\\bellSound.wav", NULL, SND_ASYNC);
				}
			}
		}
		if (tomDirection[i] == 1)
		{
			if (!jerryDirection)
			{
				if (mice_x <= cat_x[i] + 38 && mice_x  >= cat_x[i] + 30 && mice_y + 10 >= cat_y[i] && mice_y + 10 <= cat_y[i] + 30)
				{
					caught++;
					bell_x = cat_x[i];
					bell_y = cat_y[i];
					cat_x[i] = -10000;
					belled1 = true;
					kill = i;
					belled = true;
					PlaySound("sounds\\bellSound.wav", NULL, SND_ASYNC);
				}
			}
		}
	}
	
	for (int i = 0; i < 6; i++)//Cheese Eating.
	{
		if ((mice_x + 38 >= cheese_x[i] && mice_x <= cheese_x[i] + 30 && mice_y + 5 >= cheese_y[i] && mice_y <= cheese_y[i] + 25)||
			(mice_x >= cheese_x[i] && mice_x <= cheese_x[i] + 30 && mice_y + 5 >= cheese_y[i] && mice_y <= cheese_y[i] + 25))
		{
			if (!jrPower)
			{
				cheese_x[i] = -100;
				jerrySpeed = 5;
				jrPower = true;
				PlaySound("sounds\\poweUp.wav", NULL, SND_ASYNC);
			}
		}
	}
}

void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	if (game_startPG == open)
	{
		if (!pause)
		miceMove(key);
	}
}

//methods for checking rectangles area
int checkCat(char direction, int r,int i)
{
	if (direction == 'r') //Right move check
		{
			if (cat_x[i] + 40 <= rectangles[r].x || cat_x[i] - 5 >= rectangles[r].x + rectangles[r].width || cat_y[i] + 35 <= rectangles[r].y || cat_y[i] - 5 >= rectangles[r].y + rectangles[r].hight)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	if (direction == 'l') //Left move check
		{
			if (cat_x[i] + 35 <= rectangles[r].x || cat_x[i] - 10 >= rectangles[r].x + rectangles[r].width || cat_y[i] + 35 <= rectangles[r].y || cat_y[i] - 5 >= rectangles[r].y + rectangles[r].hight)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	if (direction == 'u') //Up move check
		{
			if (cat_x[i] + 35 <= rectangles[r].x || cat_x[i] - 5 >= rectangles[r].x + rectangles[r].width || cat_y[i] + 40 <= rectangles[r].y || cat_y[i] - 5 >= rectangles[r].y + rectangles[r].hight)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	if (direction == 'd') //Down move check
		{
			if (cat_x[i] + 35 <= rectangles[r].x || cat_x[i] - 5 >= rectangles[r].x + rectangles[r].width || cat_y[i] + 35 <= rectangles[r].y || cat_y[i] - 10 >= rectangles[r].y + rectangles[r].hight)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
}

//Set default co-ordinates of jerry
void jerryDefault()
{
	mice_x = 20;
	mice_y = 230;
	jerryDirection = true;
	jerryIndex = 0;
	jerryKilled = true;
}

// Saving Scores in a file
void saveScore() 
{
	fopen_s(&file, "Files\\highScores.txt", "w");
	if (gameOverPG == open)
	{
		for (int i = 0; i < 5; i++)
		{
			if (highScorer[i].score < caught)
			{
				for (int j = 5; j >= i; j--)
				{
					strcpy_s(highScorer[j + 1].name, highScorer[j].name);
					highScorer[j + 1].score = highScorer[j].score;
				}
				strcpy_s(highScorer[i].name, mName);
				highScorer[i].score = caught;
				break;
			}
		}
		for (int i = 0; i < 5; i++)
		{
			fprintf(file, "%s ", highScorer[i].name);
			fprintf(file, "%d\n", highScorer[i].score);
		}
	}
	fclose(file);
}

//method for moving cats
void catMoving(){
	if (game_startPG == open)
	{
		for (int i = 0; i < 8; i++){
			if (catMovement[i] == 0)
			{
				if (checkCat('r', 0, i) && checkCat('r', 1, i) && checkCat('r', 2, i) == 1 && checkCat('r', 3, i) == 1 && checkCat('r', 4, i) == 1 &&
					checkCat('r', 5, i) == 1 && checkCat('r', 6, i) == 1 && checkCat('r', 7, i) == 1 && checkCat('r', 8, i) == 1 && checkCat('r', 9, i) == 1 &&
					checkCat('r', 10, i) == 1 && checkCat('r', 11, i) == 1 && checkCat('r', 12, i) == 1 && checkCat('r', 13, i) == 1 && checkCat('r', 14, i) == 1 &&
					checkCat('r', 15, i) == 1 && checkCat('r', 16, i) == 1 && checkCat('r', 17, i) == 1 && checkCat('r', 18, i) == 1 && checkCat('r', 19, i) == 1 &&
					checkCat('r', 20, i) == 1 && checkCat('r', 21, i) == 1 && checkCat('r', 22, i) == 1 && checkCat('r', 23, i) == 1 && checkCat('r', 24, i) == 1 &&
					checkCat('r', 25, i) == 1 && checkCat('r', 26, i) == 1 && checkCat('r', 27, i) == 1 && checkCat('r', 28, i) == 1 && checkCat('r', 29, i) == 1 &&
					checkCat('r', 30, i) == 1 && checkCat('r', 31, i) == 1 && checkCat('r', 32, i) == 1 && checkCat('r', 33, i) == 1 && checkCat('r', 34, i) == 1 &&
					checkCat('r', 35, i) == 1 && checkCat('r', 36, i) == 1 && checkCat('r', 37, i) == 1 && checkCat('r', 38, i) == 1 && checkCat('r', 39, i) == 1
					&& cat_x[i]>=10 && cat_x[i]+30<=690)
				{
					tomDirection[i] = 0;
					cat_x[i] += 2.5;
					tomIndex[i]++;
					if (tomIndex[i] == 3)
					{
						tomIndex[i] = 0;
					}
				}
				else
				{
					srand(time(NULL));
					catMovement[i] = (rand() + i) % 4;
				}
			}
			else if (catMovement[i] == 1)
			{
				if (checkCat('l', 0, i) == 1 && checkCat('l', 1, i) == 1 && checkCat('l', 2, i) == 1 && checkCat('l', 3, i) == 1 && checkCat('l', 4, i) == 1 &&
					checkCat('l', 5, i) == 1 && checkCat('l', 6, i) == 1 && checkCat('l', 7, i) == 1 && checkCat('l', 8, i) == 1 && checkCat('l', 9, i) == 1 &&
					checkCat('l', 10, i) == 1 && checkCat('l', 11, i) == 1 && checkCat('l', 12, i) == 1 && checkCat('l', 13, i) == 1 && checkCat('l', 14, i) == 1 &&
					checkCat('l', 15, i) == 1 && checkCat('l', 16, i) == 1 && checkCat('l', 17, i) == 1 && checkCat('l', 18, i) == 1 && checkCat('l', 19, i) == 1 &&
					checkCat('l', 20, i) == 1 && checkCat('l', 21, i) == 1 && checkCat('l', 22, i) == 1 && checkCat('l', 23, i) == 1 && checkCat('l', 24, i) == 1 &&
					checkCat('l', 25, i) == 1 && checkCat('l', 26, i) == 1 && checkCat('l', 27, i) == 1 && checkCat('l', 28, i) == 1 && checkCat('l', 29, i) == 1 &&
					checkCat('l', 30, i) == 1 && checkCat('l', 31, i) == 1 && checkCat('l', 32, i) == 1 && checkCat('l', 33, i) == 1 && checkCat('l', 34, i) == 1 &&
					checkCat('l', 35, i) == 1 && checkCat('l', 36, i) == 1 && checkCat('l', 37, i) == 1 && checkCat('l', 38, i) == 1 && checkCat('l', 39, i) == 1
					&& cat_x[i] >= 10 && cat_x[i] + 30 <= 690)
				{
					tomDirection[i] = 1;
					cat_x[i] -= 2.5;
					tomIndex[i]++;
					if (tomIndex[i] == 3)
					{
						tomIndex[i] = 0;
					}
				}
				else
				{
					srand(time(NULL));
					catMovement[i] = (rand() + i) % 4;
				}
			}
			else if (catMovement[i] == 2)
			{
				if (checkCat('u', 0, i) == 1 && checkCat('u', 1, i) == 1 && checkCat('u', 2, i) == 1 && checkCat('u', 3, i) == 1 && checkCat('u', 4, i) == 1 &&
					checkCat('u', 5, i) == 1 && checkCat('u', 6, i) == 1 && checkCat('u', 7, i) == 1 && checkCat('u', 8, i) == 1 && checkCat('u', 9, i) == 1 &&
					checkCat('u', 10, i) == 1 && checkCat('u', 11, i) == 1 && checkCat('u', 12, i) == 1 && checkCat('u', 13, i) == 1 && checkCat('u', 14, i) == 1 &&
					checkCat('u', 15, i) == 1 && checkCat('u', 16, i) == 1 && checkCat('u', 17, i) == 1 && checkCat('u', 18, i) == 1 && checkCat('u', 19, i) == 1 &&
					checkCat('u', 20, i) == 1 && checkCat('u', 21, i) == 1 && checkCat('u', 22, i) == 1 && checkCat('u', 23, i) == 1 && checkCat('u', 24, i) == 1 &&
					checkCat('u', 25, i) == 1 && checkCat('u', 26, i) == 1 && checkCat('u', 27, i) == 1 && checkCat('u', 28, i) == 1 && checkCat('u', 29, i) == 1 &&
					checkCat('u', 30, i) == 1 && checkCat('u', 31, i) == 1 && checkCat('u', 32, i) == 1 && checkCat('u', 33, i) == 1 && checkCat('u', 34, i) == 1 &&
					checkCat('u', 35, i) == 1 && checkCat('u', 36, i) == 1 && checkCat('u', 37, i) == 1 && checkCat('u', 38, i) == 1 && checkCat('u', 39, i) == 1
					&& cat_x[i] >= 10 && cat_x[i] + 30 <= 690)
				{
					cat_y[i] += 2.5;
					tomIndex[i]++;
					if (tomIndex[i] == 3)
					{
						tomIndex[i] = 0;
					}
				}
				else
				{
					srand(time(NULL));
					catMovement[i] = (rand() + i) % 4;
				}
			}
			else if (catMovement[i] == 3 || catMovement[i] == 4)
			{
				if (checkCat('d', 0, i) == 1 && checkCat('d', 1, i) == 1 && checkCat('d', 2, i) == 1 && checkCat('d', 3, i) == 1 && checkCat('d', 4, i) == 1 &&
					checkCat('d', 5, i) == 1 && checkCat('d', 6, i) == 1 && checkCat('d', 7, i) == 1 && checkCat('d', 8, i) == 1 && checkCat('d', 9, i) == 1 &&
					checkCat('d', 10, i) == 1 && checkCat('d', 11, i) == 1 && checkCat('d', 12, i) == 1 && checkCat('d', 13, i) == 1 && checkCat('d', 14, i) == 1 &&
					checkCat('d', 15, i) == 1 && checkCat('d', 16, i) == 1 && checkCat('d', 17, i) == 1 && checkCat('d', 18, i) == 1 && checkCat('d', 19, i) == 1 &&
					checkCat('d', 20, i) == 1 && checkCat('d', 21, i) == 1 && checkCat('d', 22, i) == 1 && checkCat('d', 23, i) == 1 && checkCat('d', 24, i) == 1 &&
					checkCat('d', 25, i) == 1 && checkCat('d', 26, i) == 1 && checkCat('d', 27, i) == 1 && checkCat('d', 28, i) == 1 && checkCat('d', 29, i) == 1 &&
					checkCat('d', 30, i) == 1 && checkCat('d', 31, i) == 1 && checkCat('d', 32, i) == 1 && checkCat('d', 33, i) == 1 && checkCat('d', 34, i) == 1 &&
					checkCat('d', 35, i) == 1 && checkCat('d', 36, i) == 1 && checkCat('d', 37, i) == 1 && checkCat('d', 38, i) == 1 && checkCat('d', 39, i) == 1
					&& cat_x[i] >= 10 && cat_x[i] + 30 <= 690)
				{
					cat_y[i] -= 2.5;
					tomIndex[i]++;
					if (tomIndex[i] == 3)
					{
						tomIndex[i] = 0;
					}
				}
				else
				{
					srand(time(NULL));
					catMovement[i] = (rand() + i) % 4;
				}
			}
		}

		//Clashing of Tom & Jerry
		for (int i = 0; i < 8; i++)
		{
			if (tomDirection[i] == 0)
			{
				if (cat_x[i] + 36 >= mice_x && cat_x[i] + 36 <= mice_x + 10 && cat_y[i] + 5 >= mice_y && cat_y[i] <= mice_y + 30)
				{
					jerryDefault();
					mLife--;
					PlaySound("sounds\\killed.wav", NULL, SND_ASYNC);
				}
			}
			if (tomDirection[i] == 1)
			{
				if (cat_x[i]<= mice_x+36 && cat_x[i] >= mice_x + 30 && cat_y[i] + 5 >= mice_y && cat_y[i] <= mice_y + 30)
				{
					jerryDefault();
					mLife--;
					PlaySound("sounds\\killed.wav", NULL, SND_ASYNC);
				}
			}
			if (catMovement[i] == 2)
			{
				if (cat_x[i] + 5 >= mice_x && cat_x[i] <= mice_x + 38 && cat_y[i]+38 >= mice_y && cat_y[i] + 38 <= mice_y + 5)
				{
					jerryDefault();
					mLife--;
					PlaySound("sounds\\killed.wav", NULL, SND_ASYNC);
				}
			}
			if (catMovement[i] == 3)
			{
				if (cat_x[i] + 10 >= mice_x && cat_x[i] <= mice_x + 38 && cat_y[i] <= mice_y + 30 && cat_y[i] >= mice_y)
				{
					jerryDefault();
					mLife--;
					PlaySound("sounds\\killed.wav", NULL, SND_ASYNC);
				}
			}
		}

		if (mLife == 0)//Game over window appear after life is 0
		{
			gameOverPG = open;
			saveScore();
			PlaySound("sounds\\gameOver.wav", NULL, SND_ASYNC);
		}
	}
}

//cat will change direction randomely after time without clash
void catRndChange()
{
	for (int i = 0; i < 8; i++)
		catMovement[i] = (rand() + i) % 4;
}

//draw belled timer
void belledCat()
{
	if (belled)
	{
		cIn++;
		if (cIn == 3)
			cIn = 0;
	}
	if (cIn==2)
	belled = false;
}

//After being killed Jerry re-appear after some time
void jerryAppear()
{
	if (jerryKilled)
	{
		jk++;
		if (jk == 3)
			jk = 0;
		if (jk==2)
			jerryKilled = false;
	}
}

//Timer of cheese power
void jerryPowered()
{
	if (jrPower)
	{
		jpTime--;
		if (jpTime == -2)
			jpTime = 15;
		if (jpTime == -1)
		{
			jerrySpeed = 2.5;
			jrPower = false;
		}
	}
}

//Cat re-appear after certain time.
void catAppear()
{
	if (belled1)
	{
		if (kill == 0)
		{
			cat_x[0] = 320;
			cat_y[0] = 115;
		}
		if (kill == 1)
		{
			cat_x[1] = 315;
			cat_y[1] = 40;
		}
		if (kill == 2)
		{
			cat_x[2] = 335;
			cat_y[2] = 265;
		}
		if (kill == 3)
		{
			cat_x[3] = 245;
			cat_y[3] = 420;
		}
		if (kill == 4)
		{
			cat_x[4] = 578;
			cat_y[4] = 305;
		}
		if (kill == 5)
		{
			cat_x[5] = 40;
			cat_y[5] = 410;
		}
		if (kill == 6)
		{
			cat_x[6] = 85;
			cat_y[6] = 45;
		}
		if (kill == 7)
		{
			cat_x[7] = 585;
			cat_y[7] = 45;
		}
		belled1 = false;
	}
	
}

//For appearing cheese
void cheeseAppear()
{
	cheese_x[0] = 335;
	cheese_y[0] = 270;
	cheese_x[1] = 320;
	cheese_y[1] = 45;
	cheese_x[2] = 520;
	cheese_y[2] = 305;
	cheese_x[3] = 40;
	cheese_y[3] = 40;
	cheese_x[4] = 630;
	cheese_y[4] = 40;
	cheese_x[5] = 150;
	cheese_y[5] = 305;
}

//Reading High scorer from file
void readScores()
{
	int i = 0;
	fopen_s(&file, "Files\\highScores.txt", "r+");
	while (!feof(file))
	{
		fscanf_s(file, "%s", highScorer[i].name,30);
		fscanf_s(file, "%d", &highScorer[i].score);
		if (i == 4)
			break;
		i++;
	}
	fclose(file);
}

void main()
{
	iSetTimer(1000, renderColor);//for rendering colour
	iSetTimer(100, catMoving);//for moving cat
	iSetTimer(5000, catRndChange);//random movement change for cat
	iSetTimer(1000, belledCat);// Bell time set
	iSetTimer(1000, jerryAppear);// Rat re-appear time set
	iSetTimer(1000, jerryPowered); //jerry power time set
	iSetTimer(25000, catAppear); //cat re-appear
	iSetTimer(60000, cheeseAppear); //cheese re-appear.

	readScores();

	//PlaySound("sounds\\backgroundMusic0.wav", NULL, SND_LOOP | SND_ASYNC);
	iInitialize(700, 600, "Who Will Bell The Cat");
}
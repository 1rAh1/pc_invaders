#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream> 
#include <string>
#include <time.h>

const Uint16 MAX_ALIENS_ROWS = 5;
const Uint16 ALIENS_BY_ROW = 8;

const Uint16 MAX_SHOOTS_NUMBER = 30;

typedef struct Area_t {
	Sint16 x;
	Sint16 y;
	Sint16 w;
	Sint16 h;
};

typedef struct Image_t{
	SDL_Texture* image;
	Sint32 w;
	Sint32 h;
	float screenScale;
};

enum imageIndex {
	ALIEN = 0,
	CRAFT,
	CRAFT_SHOOT,
	ALIEN_SHOOT,
	IMAGES_NUMBER
};

enum InformationBarTextsMessageIndex {
	SCORE_LABEL = 0,
	LIVES_LABEL,
	SCORE_VALUE,
	INFROMATION_BAR_TEXTS_MESSAGES_NUMBER
};

typedef struct InformationBar_t {
	Area_t area;
	Uint16 upperMarginPixels;
	Uint16 leftMarginPixels;
	TTF_Font* p_font;
	Image_t textMessage[INFROMATION_BAR_TEXTS_MESSAGES_NUMBER];
};

typedef struct GameScreen_t{
	struct {
		Uint16 w;
		Uint16 h;
	} total;
	InformationBar_t iformationBar;
	Area_t gameArea;
};

typedef struct GameScreenInitIn_t {
	struct {
		Uint16 w;
		Uint16 h;
	} total;
	struct {
		Uint16 fontSize;
		Uint16 upperMarginPixels;
		Uint16 leftMarginPixels;
	} iformationBar;
	SDL_Renderer* screenRenderer;
};

typedef struct CloseIn_t {
	SDL_Window** p_widowHandler;
	SDL_Renderer** p_screenRenderer;
	GameScreen_t* p_gameScreen;
	Image_t* imageHandlers;
};

typedef struct InitIn_t {
	SDL_Window** p_widowHandler;
	SDL_Renderer** p_screenRenderer;
	Uint16 screenW;
	Uint16 screeH;
};

typedef struct LoadMediaIn_t {
	SDL_Renderer* screenRenderer;
	Image_t* imageHandlers;
};

typedef struct MoveParameters_t {
	Sint16 xSteepDistance;
	Sint16 ySteepDistance;
	Uint16 Period;
};

typedef struct AliensInitIn_t {
	Uint16 aliensRows;
	Uint16 aliensByRow;
	MoveParameters_t moveParameters;
	Image_t* p_alienImage;
	GameScreen_t* p_gameScreen;
	float screenFactor;
};

typedef struct Alien_t {
	Sint16 x;
	Sint16 y;
	Uint16 w;
	Uint16 h;
	Sint16 xSteepDistance;
	Sint16 ySteepDistance;
	bool active;
	Image_t* image;
};

typedef struct Aliens_t{
	Uint16 totalNumber;
	Uint16 activeNumber;
	Uint16 aliensByRow;
	Uint16 aliensRows;
	Uint16 inititialRow;
	Sint16 xMin;
	Sint16 xMax;
	Sint16 yMin;
	Sint16 yMax;
	Uint16 hDistanceBeteweenAliens;
	Uint16 vDistanceBeteweenAliens;
	Uint16 movePeriod;
	Uint16 shootProbability;
	Uint32 lastMoveTime;
	Alien_t members[MAX_ALIENS_ROWS * ALIENS_BY_ROW];
};

typedef struct Craft_t {
	Sint16 x;
	Sint16 y;
	Uint16 w;
	Uint16 h;
	Sint16 xMin;
	Sint16 xMax;
	Sint16 yMin;
	Sint16 yMax;
	Sint16 xSteepDistance;
	Sint16 ySteepDistance; 
	Uint16 health;
	Uint32 score;
	Image_t* image;
};

typedef struct CraftInitIn_t {
	GameScreen_t* p_gameScreen;
		Image_t* p_craftImage;
	float screenFactor;

};

typedef struct Shoot_t {
	Area_t area;
	Sint16 xSteepDistance;
	Sint16 ySteepDistance;
	bool active;
	Image_t* image;
};

typedef struct Shoots_t {
	Uint16 totalNumber;
	Sint16 xMin;
	Sint16 xMax;
	Sint16 yMin;
	Sint16 yMax;
	Uint16 movePeriod;
	Uint16 automaticShootPeriod;
	Uint32 lastMoveTime;
	Uint32 lastShootTime;
	Shoot_t members[MAX_SHOOTS_NUMBER];
};

typedef struct ShootsInitIn_t {
	Uint16 shootsNumber;
	Sint16 automaticShootPeriod;
	Image_t* p_shootImage;
	MoveParameters_t moveParameters;
	GameScreen_t* p_gameScreen;
	float screenFactor;
};

enum TextPosition {
	XY_POSITION = 0,
	WINDOW_CENTERED
};

typedef struct ShowMessageIn_t {
	std::string text;
	Uint16 position;
	Uint16 x;
	Uint16 y;
	Uint16 size;
	SDL_Color fontColor;
	GameScreen_t* p_gameScreen;
};


bool init(InitIn_t* initIn);
bool loadMedia(LoadMediaIn_t* loadMediaIn);
void close(CloseIn_t* closeIn);

void showMessage(ShowMessageIn_t* p_showMessageIn, SDL_Renderer* screenRenderer);

void gameScreenInit(GameScreen_t* gameScreen, GameScreenInitIn_t* p_gameScreenInitIn);
void gameScreenDraw(GameScreen_t* p_gameScreen, Craft_t* p_craft, SDL_Renderer* screenRenderer);

void informationBarUpdate(InformationBar_t* p_informationBar, Craft_t* p_craft, SDL_Renderer* screenRenderer);

void aliensInit(Aliens_t* p_aliens, AliensInitIn_t* p_aliensInitIn);
void aliensDraw(Aliens_t* p_aliens, SDL_Renderer* screenRenderer);
void aliensErase(Aliens_t* p_aliens, SDL_Renderer* screenRenderer);
void alienErase(Alien_t* p_alien, SDL_Renderer* screenRenderer);
void aliensMove(Aliens_t* p_aliens, SDL_Renderer* screenRenderer);
bool aliensImpactDetect(Aliens_t* p_aliens, Craft_t* p_craft, Shoots_t* p_craftShoots, SDL_Renderer* screenRenderer);
void aliensShoot(Shoots_t* p_shoots, Aliens_t* p_aliens);
void setAliensMovePeriod(Aliens_t* p_aliens);

void craftInit(Craft_t* p_craft, CraftInitIn_t* p_craftInitIn);
void craftDraw(Craft_t* p_craft, SDL_Renderer* screenRenderer);
void craftErase(Craft_t* p_craft, SDL_Renderer* screenRenderer);
void craftMove(Craft_t* p_craft, SDL_Renderer* screenRenderer);
bool craftImpactDetect(Craft_t* p_craft, Shoots_t* p_aliensShoots, SDL_Renderer* screenRenderer);

void shootsInit(Shoots_t* p_shoots, ShootsInitIn_t* p_shootsInitIn);
void shootsDraw(Shoots_t* p_shoots, SDL_Renderer* screenRenderer);
void shootErase(Shoot_t* p_shoot, SDL_Renderer* screenRenderer);
void shootsErase(Shoots_t* p_shoots, SDL_Renderer* screenRenderer);
void shootsMove(Shoots_t* p_shoots, SDL_Renderer* screenRenderer);

void craftShoot(Shoots_t* p_shoots, Craft_t* p_craft);

bool detectCollision(SDL_Rect* elementA, SDL_Rect* elementB);

void keyboardRead(Craft_t* p_craft, Shoots_t* p_craftShoots);
bool gameOverDetect(Craft_t* p_craft, Aliens_t* p_aliens);


int main( int argc, char* args[] ){	
	//main declarations---------------------
	//Screen dimension constants
	const float SCREEN_SCALE_FACTOR = 5.0f;
	const Uint16 SCREEN_WIDTH = Uint16(float(128) * SCREEN_SCALE_FACTOR);
	const Uint16 SCREEN_HEIGHT = Uint16(float(128) * SCREEN_SCALE_FACTOR);

	SDL_Window* widowHandler = NULL;
	SDL_Renderer* screenRenderer = NULL;
	Image_t imageHandlers[IMAGES_NUMBER];
	GameScreen_t gameScreen;
	Aliens_t aliens;
	Craft_t craft;
	Shoots_t craftShoots, aliensShoots;
	InitIn_t initIn;
	LoadMediaIn_t loadMediaIn;
	bool SetupDone = false;

	const Uint16 INFORMATION_BAR_FONT_SIZE = Uint16(SCREEN_SCALE_FACTOR * (float(28) / 5.0f));

	Uint16 aliensMovePeriod = 50; //[ms]
	Sint16 aliensSteepDistance = Sint16(float(3) * SCREEN_SCALE_FACTOR);
		
	Uint16 CRAFT_SHOOTS_MOVE_PERIOD = 40; //[ms]
	Sint16 craftShootsSteepDistance = Sint16(float(- 4) * SCREEN_SCALE_FACTOR);

	Uint16 aliensShootsMovePeriod = 200; //[ms]
	Sint16 aliensAutomaticShootPeriod = 1000; //[ms]
	Sint16 aliensShootsSteepDistance = Sint16(float(7) * SCREEN_SCALE_FACTOR);
	//----------------
	

	//mainSetup()
	{
		srand(time(NULL));

		//Start up SDL and create window
		initIn.p_widowHandler = &widowHandler;
		initIn.p_screenRenderer = &screenRenderer;
		initIn.screenW = SCREEN_WIDTH;
		initIn.screeH = SCREEN_HEIGHT;
		if (!init(&initIn)){
			printf("Failed to initialize!\n");
		}
		else
		{		
			//Load media
			loadMediaIn.screenRenderer = screenRenderer;
			loadMediaIn.imageHandlers = imageHandlers;
			if (!loadMedia(&loadMediaIn)){
				printf("Failed to load media!\n");
			}
			else
			{
				//Init gameScreen
				{
					GameScreenInitIn_t gameScreenInitIn;
					gameScreenInitIn.total.w = SCREEN_WIDTH;
					gameScreenInitIn.total.h = SCREEN_HEIGHT;
					gameScreenInitIn.iformationBar.fontSize = INFORMATION_BAR_FONT_SIZE;
					gameScreenInitIn.iformationBar.upperMarginPixels = Uint16(float(3) * SCREEN_SCALE_FACTOR);
					gameScreenInitIn.iformationBar.leftMarginPixels = Uint16(float(1) * SCREEN_SCALE_FACTOR);
					gameScreenInitIn.screenRenderer = screenRenderer;
					gameScreenInit(&gameScreen, &gameScreenInitIn);

				} 		
				
				//Init aliens
				{
					AliensInitIn_t aliensInitIn;
					aliensInitIn.aliensRows = MAX_ALIENS_ROWS;
					aliensInitIn.aliensByRow = ALIENS_BY_ROW;
					aliensInitIn.moveParameters.Period = aliensMovePeriod;
					aliensInitIn.moveParameters.xSteepDistance = aliensSteepDistance;
					aliensInitIn.p_alienImage = &imageHandlers[ALIEN];
					aliensInitIn.p_gameScreen = &gameScreen;
					aliensInitIn.screenFactor = float(SCREEN_SCALE_FACTOR);
					aliensInit(&aliens, &aliensInitIn);
				}

				//Init craft
				{
					CraftInitIn_t craftInitIn;
					craftInitIn.p_craftImage = &imageHandlers[CRAFT];
					craftInitIn.p_gameScreen = &gameScreen;
					craftInitIn.screenFactor = float(SCREEN_SCALE_FACTOR);
					craftInit(&craft, &craftInitIn);
				}

				//Init craftShoots
				{
					ShootsInitIn_t shootsInitIn;
					shootsInitIn.shootsNumber = MAX_SHOOTS_NUMBER;
					shootsInitIn.moveParameters.Period = CRAFT_SHOOTS_MOVE_PERIOD;
					shootsInitIn.moveParameters.ySteepDistance = craftShootsSteepDistance;
					shootsInitIn.p_shootImage = &imageHandlers[CRAFT_SHOOT];
					shootsInitIn.automaticShootPeriod = -1;
					shootsInitIn.p_gameScreen = &gameScreen;
					shootsInitIn.screenFactor = float(SCREEN_SCALE_FACTOR);
					shootsInit(&craftShoots, &shootsInitIn);
				}

				//Init aliensShoots
				{
					ShootsInitIn_t shootsInitIn;
					shootsInitIn.shootsNumber = MAX_SHOOTS_NUMBER;
					shootsInitIn.moveParameters.Period = aliensShootsMovePeriod;
					shootsInitIn.moveParameters.ySteepDistance = aliensShootsSteepDistance;
					shootsInitIn.p_shootImage = &imageHandlers[ALIEN_SHOOT];
					shootsInitIn.automaticShootPeriod = aliensAutomaticShootPeriod;
					shootsInitIn.p_gameScreen = &gameScreen;
					shootsInitIn.screenFactor = float(SCREEN_SCALE_FACTOR);
					shootsInit(&aliensShoots, &shootsInitIn);
				}

				SDL_RenderClear(screenRenderer);

				gameScreenDraw(&gameScreen, &craft, screenRenderer);
				aliensDraw(&aliens, screenRenderer);
				craftDraw(&craft, screenRenderer);
				
				SDL_RenderPresent(screenRenderer);
				
				SetupDone = true;
				
			}
		}
	}
	
	//mainLoop()
	{
		if(true == SetupDone){			
			//code to get window to stay up
			SDL_Event event;
			bool quit = false;
			bool gameOver = false;
			while (false == quit) {
				while ((false == gameOver) && (false == quit)){

					//testingEndProgram()
					{
					while (SDL_PollEvent(&event)) {
							if (event.type == SDL_QUIT) {
								quit = true;
							}
						}
						if (true == quit) {
							break;
						}
					}

					keyboardRead(&craft, &craftShoots);

					aliensMove(&aliens, screenRenderer);
					shootsMove(&craftShoots, screenRenderer);
					shootsMove(&aliensShoots, screenRenderer);

					//Impact detection
					{
						bool aliensImpact = aliensImpactDetect(&aliens, &craft, &craftShoots, screenRenderer);
						bool craftImpact = craftImpactDetect(&craft, &aliensShoots, screenRenderer);
						if ((true == aliensImpact) || (true == craftImpact)) {
							informationBarUpdate(&gameScreen.iformationBar, &craft, screenRenderer);
						}
					}

					//Test gameOver
					gameOver = gameOverDetect(&craft, &aliens);
					if (true == gameOver) {
						//Show game over message
						ShowMessageIn_t showMessageIn;
						showMessageIn.position = WINDOW_CENTERED;
						showMessageIn.text = "GAME OVER";
						showMessageIn.size = Uint16(SCREEN_SCALE_FACTOR * (float(60) / 5.0f));
						showMessageIn.fontColor = { 0x00,0xFF,0x00,0xFF };
						showMessageIn.p_gameScreen = &gameScreen;
						showMessage(&showMessageIn, screenRenderer);

						SDL_RenderPresent(screenRenderer);

						continue;
					}

					if (aliens.activeNumber <= 0) {
						//Init aliens
						{
							AliensInitIn_t aliensInitIn;
							aliensInitIn.aliensRows = MAX_ALIENS_ROWS;
							aliensInitIn.aliensByRow = ALIENS_BY_ROW;
							aliensInitIn.moveParameters.Period = aliensMovePeriod;
							aliensInitIn.moveParameters.xSteepDistance = aliensSteepDistance;
							aliensInitIn.p_alienImage = &imageHandlers[ALIEN];
							aliensInitIn.p_gameScreen = &gameScreen;
							aliensInitIn.screenFactor = float(SCREEN_SCALE_FACTOR);
							aliensInit(&aliens, &aliensInitIn);
						}

					}

					//Set aliens movePeiod
					setAliensMovePeriod(&aliens);

					//Mange movements
					aliensShoot(&aliensShoots, &aliens);
					shootsDraw(&aliensShoots, screenRenderer);
					craftMove(&craft, screenRenderer);

					//Update the render
					SDL_RenderPresent(screenRenderer);
				}

				//Testing end program
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						quit = true;
						break;
					}
				}
			}
		}

		//Free resources and close SDL
		{
			CloseIn_t closeIn;
			closeIn.p_gameScreen = &gameScreen;
			closeIn.p_screenRenderer = &screenRenderer;
			closeIn.p_widowHandler = &widowHandler;
			closeIn.imageHandlers = imageHandlers;
			close(&closeIn);
		}
	}
	//------------------
	
	return 0;
	
}

bool init(InitIn_t* initIn){
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		//Create window
		*initIn->p_widowHandler = SDL_CreateWindow("My Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, initIn->screenW, initIn->screeH, SDL_WINDOW_SHOWN);
		
			if (*initIn->p_widowHandler == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			*initIn->p_screenRenderer = SDL_CreateRenderer(*initIn->p_widowHandler, -1, SDL_RENDERER_ACCELERATED);
			if (*initIn->p_screenRenderer == NULL) {
				printf("Render could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

Image_t loadTexture(std::string path, SDL_Color* colorKey, SDL_Renderer* screenRenderer) {
	SDL_Texture* loadedTexture = NULL;
	SDL_Surface* loadedSurface = NULL;
	Image_t textImage;

	//Load image at specified path
	loadedSurface = SDL_LoadBMP(path.c_str());
	textImage.w = loadedSurface->w;
	textImage.h = loadedSurface->h;
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		if ((colorKey->r != 0) || (colorKey->g != 0) || (colorKey->b != 0)) {
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, colorKey->r, colorKey->g, colorKey->b));
		}

		loadedTexture = SDL_CreateTextureFromSurface(screenRenderer, loadedSurface);
		if (loadedTexture == NULL) {
			printf("Unable to create texture %s\n", SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	textImage.image = loadedTexture;
	return textImage;
}

Image_t getTextImage(std::string text, TTF_Font* p_font, SDL_Color p_color, SDL_Renderer* screenRenderer) {
	SDL_Texture* loadedTexture = NULL;
	SDL_Surface* loadedSurface = NULL;
	Image_t textImage;

	loadedSurface = TTF_RenderText_Solid(p_font, text.c_str(), p_color);
	textImage.w = loadedSurface->w;
	textImage.h = loadedSurface->h;
	if (loadedSurface == NULL)
	{
		printf("Unable to create text surface %s!\n", SDL_GetError());
	}
	else {
		loadedTexture = SDL_CreateTextureFromSurface(screenRenderer, loadedSurface);
		if (loadedTexture == NULL) {
			printf("Unable to create texture %s\n", SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		loadedSurface = NULL;
	}
	textImage.image = loadedTexture;
	return textImage;
}

bool loadMedia(LoadMediaIn_t* loadMediaIn) {
	const Uint16 GAME_MESSAGE_FONT_SIZE = 36;

	SDL_Color colorKey;

	//Loading success flag
	bool success = true;

	//Load images	
	colorKey.r = 0xFF;
	colorKey.g = 0xFF;
	colorKey.b = 0xFF;
	loadMediaIn->imageHandlers[ALIEN] = loadTexture("img/alien.bmp", &colorKey, loadMediaIn->screenRenderer);
	if (loadMediaIn->imageHandlers[ALIEN].image == NULL) {
		printf("Unable to load image %s!\n", "img/alien.bmp");
	}

	colorKey.r = 0xFF;
	colorKey.g = 0xFF;
	colorKey.b = 0xFF;
	loadMediaIn->imageHandlers[CRAFT] = loadTexture("img/craft.bmp", &colorKey, loadMediaIn->screenRenderer);
	if (loadMediaIn->imageHandlers[CRAFT].image == NULL) {
		printf("Unable to load image %s!\n", "img/craft.bmp");
	}

	colorKey.r = 0xFF;
	colorKey.g = 0xFF;
	colorKey.b = 0xFF;
	loadMediaIn->imageHandlers[CRAFT_SHOOT] = loadTexture("img/craft_shoot.bmp", &colorKey, loadMediaIn->screenRenderer);
	if (loadMediaIn->imageHandlers[CRAFT_SHOOT].image == NULL) {
		printf("Unable to load image %s!\n", "img/craft_shoot.bmp");
	}

	colorKey.r = 0xFF;
	colorKey.g = 0xFF;
	colorKey.b = 0xFF;
	loadMediaIn->imageHandlers[ALIEN_SHOOT] = loadTexture("img/alien_shoot.bmp", &colorKey, loadMediaIn->screenRenderer);
	if (loadMediaIn->imageHandlers[ALIEN_SHOOT].image == NULL) {
		printf("Unable to load image %s!\n", "img/alien_shoot.bmp");
	}
	return success;
}


void close(CloseIn_t* p_closeIn) {
	//Deallocate images
	for (Uint16 i = 0; i < IMAGES_NUMBER; i++) {
		SDL_DestroyTexture(p_closeIn->imageHandlers[i].image);
		p_closeIn->imageHandlers[i].image = NULL;
	}

	//Deallocate informationBarr text images and fonts
	for (Uint16 i = 0; i < INFROMATION_BAR_TEXTS_MESSAGES_NUMBER; i++) {
		SDL_DestroyTexture(p_closeIn->p_gameScreen->iformationBar.textMessage[i].image);
		p_closeIn->p_gameScreen->iformationBar.textMessage[i].image = NULL;
	}
	
	TTF_CloseFont(p_closeIn->p_gameScreen->iformationBar.p_font);
	p_closeIn->p_gameScreen->iformationBar.p_font = NULL;

	//Destroy render
	SDL_DestroyRenderer(*p_closeIn->p_screenRenderer);
	*p_closeIn->p_screenRenderer = NULL;

	//Destroy window
	SDL_DestroyWindow(*p_closeIn->p_widowHandler);
	*p_closeIn->p_widowHandler = NULL;

	TTF_Quit();

	//Quit SDL subsystems
	SDL_Quit();
}

void gameScreenInit(GameScreen_t* p_gameScreen, GameScreenInitIn_t* p_gameScreenInitIn){
	SDL_Color fontColor = { 0x00, 0xFF, 0x00, 0xFF };

	p_gameScreen->total.w = p_gameScreenInitIn->total.w;
	p_gameScreen->total.h = p_gameScreenInitIn->total.h;

	p_gameScreen->iformationBar.p_font = TTF_OpenFont("img/space_invaders.ttf", p_gameScreenInitIn->iformationBar.fontSize);
	p_gameScreen->iformationBar.textMessage[SCORE_LABEL] = getTextImage("SCORE  ", p_gameScreen->iformationBar.p_font, fontColor, p_gameScreenInitIn->screenRenderer);
	p_gameScreen->iformationBar.textMessage[LIVES_LABEL] = getTextImage("LIVES", p_gameScreen->iformationBar.p_font, fontColor, p_gameScreenInitIn->screenRenderer);

	p_gameScreen->iformationBar.upperMarginPixels = p_gameScreenInitIn->iformationBar.upperMarginPixels;
	p_gameScreen->iformationBar.leftMarginPixels = p_gameScreenInitIn->iformationBar.leftMarginPixels;
		
	p_gameScreen->iformationBar.area.x = 0;
	p_gameScreen->iformationBar.area.y = 0;
	p_gameScreen->iformationBar.area.h = p_gameScreen->iformationBar.textMessage[SCORE_LABEL].h + p_gameScreen->iformationBar.upperMarginPixels;
	p_gameScreen->iformationBar.area.w = p_gameScreenInitIn->total.w;

	p_gameScreen->gameArea.x = 0;
	p_gameScreen->gameArea.y = p_gameScreen->iformationBar.area.h;
	p_gameScreen->gameArea.w = p_gameScreenInitIn->total.w;
	p_gameScreen->gameArea.h = (p_gameScreenInitIn->total.h - p_gameScreen->iformationBar.area.h);
}

void gameScreenDraw(GameScreen_t* p_gameScreen, Craft_t* p_craft, SDL_Renderer* screenRenderer) {
	SDL_Rect stretchRect;

	stretchRect.x = p_gameScreen->iformationBar.leftMarginPixels;
	stretchRect.y = p_gameScreen->iformationBar.upperMarginPixels;
	stretchRect.h = p_gameScreen->iformationBar.textMessage[SCORE_LABEL].h;
	stretchRect.w = p_gameScreen->iformationBar.textMessage[SCORE_LABEL].w;
	SDL_RenderCopy(screenRenderer, p_gameScreen->iformationBar.textMessage[SCORE_LABEL].image, NULL, &stretchRect);

	stretchRect.x = p_gameScreen->iformationBar.area.w / 2;
	stretchRect.y = p_gameScreen->iformationBar.upperMarginPixels;
	stretchRect.w = p_gameScreen->iformationBar.textMessage[LIVES_LABEL].w;
	stretchRect.h = p_gameScreen->iformationBar.textMessage[LIVES_LABEL].h;
	SDL_RenderCopy(screenRenderer, p_gameScreen->iformationBar.textMessage[LIVES_LABEL].image, NULL, &stretchRect);

	informationBarUpdate(&p_gameScreen->iformationBar, p_craft, screenRenderer);
}

void informationBarUpdate(InformationBar_t* p_informationBar, Craft_t* p_craft, SDL_Renderer* screenRenderer) {
	SDL_Color fontColor = {0x00,0xFF,0x00,0xFF};
	SDL_Rect rectangle;

	rectangle.x = p_informationBar->area.x + p_informationBar->textMessage[SCORE_LABEL].w;
	rectangle.y = p_informationBar->area.y + p_informationBar->upperMarginPixels;
	
	//Erase score
	rectangle.w = p_informationBar->textMessage[SCORE_VALUE].w;
	rectangle.h = p_informationBar->textMessage[SCORE_VALUE].h;
	SDL_SetRenderDrawColor(screenRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(screenRenderer, &rectangle);

	
	//Print score
	{
		std::string s_score = std::to_string(p_craft->score);
		p_informationBar->textMessage[SCORE_VALUE] = getTextImage(s_score, p_informationBar->p_font, fontColor, screenRenderer);

		rectangle.h = p_informationBar->textMessage[SCORE_VALUE].h;
		rectangle.w = p_informationBar->textMessage[SCORE_VALUE].w;
		SDL_RenderCopy(screenRenderer, p_informationBar->textMessage[SCORE_VALUE].image, NULL, &rectangle);

		SDL_DestroyTexture(p_informationBar->textMessage[SCORE_VALUE].image);
	}

	//Erase health
	Uint16 healthValueX = p_informationBar->area.x + (p_informationBar->area.w / 2) + p_informationBar->textMessage[LIVES_LABEL].w + Uint16(float(2) * p_craft->image->screenScale);
	rectangle.x = healthValueX;
	rectangle.y = p_informationBar->area.y + Uint16(float(1) * p_craft->image->screenScale);
	rectangle.h = p_craft->h;
	rectangle.w = 2 * (Uint16(float(2) * p_craft->image->screenScale) + p_craft->w);

	SDL_SetRenderDrawColor(screenRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(screenRenderer, &rectangle);
	
	//Print health
	{

		rectangle.h = p_craft->h;
		rectangle.w = p_craft->w;
		
		for (Uint8 i = 0; i < (p_craft->health - 1); i++) {	
			rectangle.x = healthValueX + i * (Uint16(float(2) * p_craft->image->screenScale) + p_craft->w);
			SDL_RenderCopy(screenRenderer, p_craft->image->image, NULL, &rectangle);
		}
	}
}

void keyboardRead(Craft_t* p_craft, Shoots_t* p_craftShoots) {
	const Uint32 KEYBOARD_SCAND_PERIOD_MS = 30;
	Uint32 currentTime = 0;
	static Uint32 lastKeyboardRead = 0;

	currentTime = SDL_GetTicks();

	if (currentTime > (lastKeyboardRead + KEYBOARD_SCAND_PERIOD_MS)) {
		lastKeyboardRead = currentTime;

		const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
		if ((1 == keyboardState[SDL_SCANCODE_LEFT]) && (0 == keyboardState[SDL_SCANCODE_RIGHT])) {
			p_craft->xSteepDistance = -Sint16(p_craft->image->screenScale);
		}
		if ((0 == keyboardState[SDL_SCANCODE_LEFT]) && (1 == keyboardState[SDL_SCANCODE_RIGHT])) {
			p_craft->xSteepDistance = +Sint16(p_craft->image->screenScale);
		}
		if (1 == keyboardState[SDL_SCANCODE_SPACE]) {
			craftShoot(p_craftShoots, p_craft);
		}
	}
}

void aliensInit(Aliens_t* p_aliens, AliensInitIn_t* p_aliensInitIn){
	const Uint16 H_DISTANCE_BETWEEN_ALIENS = 2;
	const Uint16 V_DISTANCE_BETWEEN_ALIENS = 1;
	const Uint16 INITIAL_SHOOT_PROBABILITY = 20;

	static bool firstExecution = true;

	
	Uint16 alienW = Uint16(float(p_aliensInitIn->p_alienImage->w) * p_aliensInitIn->screenFactor);
	Uint16 alienH = Uint16(float(p_aliensInitIn->p_alienImage->h) * p_aliensInitIn->screenFactor);

	p_aliens->totalNumber = p_aliensInitIn->aliensRows * p_aliensInitIn->aliensByRow;
	p_aliens->activeNumber = p_aliens->totalNumber;
	p_aliens->aliensRows = p_aliensInitIn->aliensRows;
	p_aliens->aliensByRow = p_aliensInitIn->aliensByRow;
	if (true == firstExecution) {
		firstExecution = false;
		p_aliens->inititialRow = 0;
		p_aliens->shootProbability = INITIAL_SHOOT_PROBABILITY;
	}
	else {
		p_aliens->inititialRow++;
		p_aliens->shootProbability = p_aliens->shootProbability + 10;
	}
	p_aliens->xMin = p_aliensInitIn->p_gameScreen->gameArea.x;
	p_aliens->xMax = p_aliensInitIn->p_gameScreen->gameArea.x + p_aliensInitIn->p_gameScreen->gameArea.w - alienW;
	p_aliens->yMin = p_aliensInitIn->p_gameScreen->gameArea.y;
	p_aliens->yMax = p_aliensInitIn->p_gameScreen->gameArea.y + p_aliensInitIn->p_gameScreen->gameArea.h - alienH;
	p_aliens->hDistanceBeteweenAliens = Uint16(float(H_DISTANCE_BETWEEN_ALIENS) * p_aliensInitIn->screenFactor);
	p_aliens->vDistanceBeteweenAliens = Uint16(float(V_DISTANCE_BETWEEN_ALIENS) * p_aliensInitIn->screenFactor);
	 
	p_aliens->movePeriod = p_aliensInitIn->moveParameters.Period;
	p_aliens->lastMoveTime = 0;
	for (Uint16 i = 0; i < p_aliens->totalNumber; i++) {
		p_aliens->members[i].w = alienW;
		p_aliens->members[i].h = alienH;
		p_aliens->members[i].x = ((i % p_aliens->aliensByRow) * alienW) + Uint16(float((i % p_aliens->aliensByRow) * H_DISTANCE_BETWEEN_ALIENS) * p_aliensInitIn->screenFactor);
		p_aliens->members[i].y = p_aliens->yMin + ((i / p_aliens->aliensByRow) + +p_aliens->inititialRow) * alienH + Uint16(float((i / p_aliens->aliensByRow) * V_DISTANCE_BETWEEN_ALIENS) * p_aliensInitIn->screenFactor);
		p_aliens->members[i].xSteepDistance = p_aliensInitIn->moveParameters.xSteepDistance;
		p_aliens->members[i].ySteepDistance = 0;
		p_aliens->members[i].active = true;
		p_aliens->members[i].image = p_aliensInitIn->p_alienImage;
		p_aliens->members[i].image->screenScale = p_aliensInitIn->screenFactor;
		
	}
}

void aliensDraw(Aliens_t* p_aliens, SDL_Renderer* screenRenderer) {
	SDL_Rect stretchRect;

	for (Uint16 i = 0; i < p_aliens->totalNumber; i++) {
		if (true == p_aliens->members[i].active) {
			
			stretchRect.x = p_aliens->members[i].x;
			stretchRect.y = p_aliens->members[i].y;
			stretchRect.w = p_aliens->members[i].w;
			stretchRect.h = p_aliens->members[i].h;
			SDL_RenderCopy(screenRenderer, p_aliens->members[i].image->image, NULL, &stretchRect);
			
		}
	}

}

void alienErase(Alien_t* p_alien, SDL_Renderer* screenRenderer) {
	SDL_Rect fillRect;

	fillRect.x = p_alien->x;
	fillRect.y = p_alien->y;
	fillRect.w = p_alien->w;
	fillRect.h = p_alien->h;

	SDL_SetRenderDrawColor(screenRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(screenRenderer, &fillRect);
}

void aliensErase(Aliens_t* p_aliens, SDL_Renderer* screenRenderer) {
	SDL_Rect fillRect;

	SDL_SetRenderDrawColor(screenRenderer, 0x00, 0x00, 0x00, 0xFF);
	for (Uint16 i = 0; i < p_aliens->totalNumber; i++) {
		if (true == p_aliens->members[i].active) {
			alienErase(&p_aliens->members[i], screenRenderer);
		}
	}
}

void aliensMove(Aliens_t* p_aliens, SDL_Renderer* screenRenderer) {
	Uint32 currentTime = 0;
	
	Sint16 limitDistance = 0;
	Sint16 steepDistance = 0;
	Sint16 advance = 0;

	bool changeRow = false;
	
	currentTime = SDL_GetTicks();

	if (currentTime > (p_aliens->lastMoveTime + p_aliens->movePeriod)) {
		p_aliens->lastMoveTime = currentTime;

		//Get min distance to limit
		{
			if (p_aliens->members[0].xSteepDistance > 0) {
				steepDistance = p_aliens->members[0].xSteepDistance;
				for (Uint16 i = 0; i < p_aliens->totalNumber; i++) {
					if (true == p_aliens->members[i].active){

						limitDistance = p_aliens->xMax - p_aliens->members[i].x;
						if (abs(limitDistance) <= abs(steepDistance)) {
							steepDistance = limitDistance;
							changeRow = true;
							for (Uint16 j = 0; j < p_aliens->totalNumber; j++) {
								p_aliens->members[j].xSteepDistance = -p_aliens->members[j].xSteepDistance;								
							}
							break;
						}

					}
				}	
			}
			else {
				steepDistance = p_aliens->members[0].xSteepDistance;
				for (Uint16 i = 0; i < p_aliens->totalNumber; i++) {
					if (true == p_aliens->members[i].active) {
						limitDistance = p_aliens->xMin - p_aliens->members[i].x;
						if (abs(limitDistance) <= abs(steepDistance)) {
							steepDistance = limitDistance;
							changeRow = true;
							for (Uint16 j = 0; j < p_aliens->totalNumber; j++) {								
								p_aliens->members[j].xSteepDistance = -p_aliens->members[j].xSteepDistance;								
							}
							break;
						}
					}
				}
			}

		}

		aliensErase(p_aliens, screenRenderer);
		for (Uint16 i = 0; i < p_aliens->totalNumber; i++) {
			p_aliens->members[i].x = p_aliens->members[i].x + steepDistance;
			if (true == changeRow) {				
				p_aliens->members[i].y = p_aliens->members[i].y + p_aliens->members[i].h + p_aliens->vDistanceBeteweenAliens;
			}
		}
		changeRow = false;
	
		aliensDraw(p_aliens, screenRenderer);
	}

}

void setAliensMovePeriod(Aliens_t* p_aliens) {
	const Uint16 MAX_MOVE_PERIOD = 600;
	const Uint16 MIN_MOVE_PERIOD = 30;

	p_aliens->movePeriod = MIN_MOVE_PERIOD + Uint16(float(MAX_MOVE_PERIOD - MIN_MOVE_PERIOD) * (float(p_aliens->activeNumber) / float(p_aliens->totalNumber)));
}

void craftInit(Craft_t* p_craft, CraftInitIn_t* p_craftInitIn){
	const Uint16 INITIAL_HEALTH = 3;

	Uint16 craftW = Uint16(float(p_craftInitIn->p_craftImage->w) * p_craftInitIn->screenFactor);
	Uint16 craftH = Uint16(float(p_craftInitIn->p_craftImage->h) * p_craftInitIn->screenFactor);
	
	p_craft->w = craftW;
	p_craft->h = craftH;
	p_craft->x = p_craftInitIn->p_gameScreen->gameArea.y + ((p_craftInitIn->p_gameScreen->gameArea.w - craftW) / 2);
	p_craft->y = p_craftInitIn->p_gameScreen->gameArea.y + p_craftInitIn->p_gameScreen->gameArea.h - craftH;
	p_craft->xMin = p_craftInitIn->p_gameScreen->gameArea.x;
	p_craft->xMax = p_craftInitIn->p_gameScreen->gameArea.x + p_craftInitIn->p_gameScreen->gameArea.w - craftW;
	p_craft->yMin = p_craftInitIn->p_gameScreen->gameArea.y;
	p_craft->yMax = p_craftInitIn->p_gameScreen->gameArea.y + p_craftInitIn->p_gameScreen->gameArea.h - craftH;
	p_craft->xSteepDistance = 0;
	p_craft->ySteepDistance = 0;
	p_craft->health = INITIAL_HEALTH;
	p_craft->score = 0;
	p_craft->image = p_craftInitIn->p_craftImage;
	p_craft->image->screenScale = p_craftInitIn->screenFactor;
}

void craftDraw(Craft_t* p_craft, SDL_Renderer* screenRenderer) {
	SDL_Rect stretchRect;
		
	stretchRect.x = p_craft->x;
	stretchRect.y = p_craft->y;
	stretchRect.w = p_craft->w;
	stretchRect.h = p_craft->h;
	SDL_RenderCopy(screenRenderer, p_craft->image->image, NULL, &stretchRect);
}

void craftErase(Craft_t* p_craft, SDL_Renderer* screenRenderer) {
	SDL_Rect fillRect;

	fillRect.x = p_craft->x;
	fillRect.y = p_craft->y;
	fillRect.w = p_craft->w;
	fillRect.h = p_craft->h;
	
	SDL_SetRenderDrawColor(screenRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(screenRenderer, &fillRect);
}

void craftMove(Craft_t* p_craft, SDL_Renderer* screenRenderer) {
	if (0 != p_craft->xSteepDistance) {
		craftErase(p_craft, screenRenderer);

		p_craft->x = p_craft->x + p_craft->xSteepDistance;
		if (p_craft->x > p_craft->xMax) {
			p_craft->x = p_craft->xMax;
		}
		if (p_craft->x < p_craft->xMin) {
			p_craft->x = p_craft->xMin;
		}

		craftDraw(p_craft, screenRenderer);

		p_craft->xSteepDistance = 0;
	}

}

void shootsInit(Shoots_t* p_shoots, ShootsInitIn_t* p_shootsInitIn) {

	Uint16 shootW = Uint16(float(p_shootsInitIn->p_shootImage->w) * p_shootsInitIn->screenFactor);
	Uint16 shootH = Uint16(float(p_shootsInitIn->p_shootImage->h) * p_shootsInitIn->screenFactor);

	p_shoots->totalNumber = p_shootsInitIn->shootsNumber;
	p_shoots->xMin = p_shootsInitIn->p_gameScreen->gameArea.x;
	p_shoots->xMax = p_shootsInitIn->p_gameScreen->gameArea.x + p_shootsInitIn->p_gameScreen->gameArea.w - shootW;
	p_shoots->yMin = p_shootsInitIn->p_gameScreen->gameArea.y;
	p_shoots->yMax = p_shootsInitIn->p_gameScreen->gameArea.y + p_shootsInitIn->p_gameScreen->gameArea.h - shootH;
	p_shoots->lastMoveTime = 0;
	p_shoots->lastShootTime = 0;
	p_shoots->movePeriod = p_shootsInitIn->moveParameters.Period;
	p_shoots->automaticShootPeriod = p_shootsInitIn->automaticShootPeriod;
	for (Uint16 i = 0; i < p_shoots->totalNumber; i++) {
		p_shoots->members[i].area.w = shootW;
		p_shoots->members[i].area.h = shootH;
		p_shoots->members[i].area.x = 0;
		p_shoots->members[i].area.y = 0;
		p_shoots->members[i].xSteepDistance = 0;
		p_shoots->members[i].ySteepDistance = p_shootsInitIn->moveParameters.ySteepDistance;
		p_shoots->members[i].active = false;
		p_shoots->members[i].image = p_shootsInitIn->p_shootImage;
	}
}


void shootsDraw(Shoots_t* p_shoots, SDL_Renderer* screenRenderer) {
	SDL_Rect stretchRect;

	for (Uint16 i = 0; i < p_shoots->totalNumber; i++) {
		if (true == p_shoots->members[i].active) {

			stretchRect.x = p_shoots->members[i].area.x;
			stretchRect.y = p_shoots->members[i].area.y;
			stretchRect.w = p_shoots->members[i].area.w;
			stretchRect.h = p_shoots->members[i].area.h;
			SDL_RenderCopy(screenRenderer, p_shoots->members[i].image->image, NULL, &stretchRect);
		}
	}
}

void shootErase(Shoot_t* p_shoot, SDL_Renderer* screenRenderer) {
	SDL_Rect fillRectangle;

	fillRectangle.x = p_shoot->area.x;
	fillRectangle.y = p_shoot->area.y;
	fillRectangle.w = p_shoot->area.w;
	fillRectangle.h = p_shoot->area.h;

	SDL_SetRenderDrawColor(screenRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(screenRenderer, &fillRectangle);
}

void shootsErase(Shoots_t* p_shoots, SDL_Renderer* screenRenderer) {
	SDL_SetRenderDrawColor(screenRenderer, 0x00, 0x00, 0x00, 0xFF);
	for (Uint16 i = 0; i < p_shoots->totalNumber; i++) {
		if (true == p_shoots->members[i].active) {
			shootErase(&p_shoots->members[i], screenRenderer);
		}
	}
}

void shootsMove(Shoots_t* p_shoots, SDL_Renderer* screenRenderer) {
	Uint32 currentTime = 0;

	currentTime = SDL_GetTicks();

	if (currentTime > (p_shoots->lastMoveTime + p_shoots->movePeriod)) {
		p_shoots->lastMoveTime = currentTime;

		shootsErase(p_shoots, screenRenderer);
		for (Uint16 i = 0; i < p_shoots->totalNumber; i++) {
			p_shoots->members[i].area.y = p_shoots->members[i].area.y + p_shoots->members[i].ySteepDistance;
			if ((p_shoots->members[i].area.y <= p_shoots->yMin) ||
				(p_shoots->members[i].area.y >= p_shoots->yMax) ||
				(p_shoots->members[i].area.x <= p_shoots->xMin) ||
				(p_shoots->members[i].area.x >= p_shoots->xMax)
				) {
				p_shoots->members[i].active = false;
			}
		}
		shootsDraw(p_shoots, screenRenderer);
	}
}

void craftShoot(Shoots_t* p_shoots, Craft_t* p_craft) {
	const Uint32 SHOOT_DELAY_MS = 300;
	static Uint32 lastShoot = 0;
	Uint32 currentTime = 0;
	Uint16 xShoot = 0;
	Uint16 yShoot = 0;
	Uint16 i = 0;

	currentTime = SDL_GetTicks();

	if (currentTime > (lastShoot + SHOOT_DELAY_MS)) {
		lastShoot = currentTime;

		while ((true == p_shoots->members[i].active) && (i < p_shoots->totalNumber)) {
			i++;
		}

		if (i < p_shoots->totalNumber) {
			xShoot = p_craft->x + (p_craft->w / 2) - (p_shoots->members[0].area.w / 2);
			yShoot = p_craft->y - p_shoots->members[i].area.h;

			p_shoots->members[i].active = true;
			p_shoots->members[i].area.x = xShoot;
			p_shoots->members[i].area.y = yShoot;
		}
	}
}

bool areAliensInColumn(Aliens_t* p_aliens, Uint16 columNumber) {
	bool areAlienes = false;

	for (Uint16 i = 0; i < p_aliens->aliensRows; i ++) {
		if (true == p_aliens->members[columNumber + (i * p_aliens->aliensByRow)].active) {
			areAlienes = true;
			break;
		}
	}

	return areAlienes;
}

Sint16 getShootColumn(Aliens_t* p_aliens) {
	Sint16 shootColumn = -1;
	Uint16 columnNumberSelected = 0;
	Uint16 columnIndexSelected = 0;
	Uint16 activeColumnsNumber = 0;
	Uint16 iterationLimit = ALIENS_BY_ROW;

	//Counting columsn whith active aliens
	for (Uint16 i = 0; i < p_aliens->aliensByRow; i ++) {
		for (Uint16 j = 0; j < p_aliens->aliensRows; j++) {
			if (true == p_aliens->members[i + j * p_aliens->aliensByRow].active) {
				activeColumnsNumber++;
				break;
			}
		}
	}

	if (activeColumnsNumber > 0) {
		columnNumberSelected = Uint16(rand() % activeColumnsNumber) + 1;

		do {


			//if (true == p_aliens->members[columnIndexSelected].active) {
			if (true == areAliensInColumn(p_aliens, columnIndexSelected)) {
				columnNumberSelected--;
			}
			if (columnNumberSelected > 0) {
				columnIndexSelected++;
			}

			iterationLimit--;

		} while ((columnNumberSelected > 0) && (iterationLimit > 0));


		//Informing no active aliens.
		if (iterationLimit >= 0) {
			shootColumn = columnIndexSelected;
		}
		else {
			shootColumn = -1;
		}
	}
	else {
		shootColumn = -1;
	}

	return shootColumn;
}

void aliensShoot(Shoots_t* p_shoots, Aliens_t* p_aliens){
	Uint16 xShoot = 0; 
	Uint16 yShoot = 0;
	Sint16 shootColumn = 0;
	Uint16 shootValue = 0;
	Sint16 alienShootIndex = 0;
	Uint16 shootIndex = 0;

	Uint32 currentTime = 0;

	currentTime = SDL_GetTicks();

	if (currentTime > (p_shoots->lastShootTime + p_shoots->automaticShootPeriod)) {
		p_shoots->lastShootTime = currentTime;

		shootValue = Uint16(rand() % 100) + 1;

		if ((shootValue <= p_aliens->shootProbability) && (p_shoots->automaticShootPeriod >= 0)) {
			shootColumn = getShootColumn(p_aliens);

			if (shootColumn >= 0) {
				alienShootIndex = (p_aliens->totalNumber - p_aliens->aliensByRow) + shootColumn;

				while ((false == p_aliens->members[alienShootIndex].active) && (alienShootIndex > shootColumn)) {
					alienShootIndex = alienShootIndex - p_aliens->aliensByRow;
				}

				while ((true == p_shoots->members[shootIndex].active) && (shootIndex < p_shoots->totalNumber)) {
					shootIndex++;
				}

				xShoot = p_aliens->members[alienShootIndex].x + (p_aliens->members[alienShootIndex].w / 2) - (p_shoots->members[shootIndex].area.w / 2);
				yShoot = p_aliens->members[alienShootIndex].y + p_aliens->members[alienShootIndex].h;

				p_shoots->members[shootIndex].area.x = xShoot;
				p_shoots->members[shootIndex].area.y = yShoot;
				p_shoots->members[shootIndex].active = true;
			}

		}
	}
}

bool detectCollision(SDL_Rect* elementA, SDL_Rect* elementB) {
	bool crash = true;
	Sint16 elementAX0 = 0;
	Sint16 elementAY0 = 0;
	Sint16 elementAX1 = 0;
	Sint16 elementAY1 = 0;

	Sint16 elementBX0 = 0;
	Sint16 elementBY0 = 0;
	Sint16 elementBX1 = 0;
	Sint16 elementBY1 = 0;

	elementAX0 = elementA->x;
	elementAY0 = elementA->y;
	elementAX1 = elementA->x + elementA->w;
	elementAY1 = elementA->y + elementA->h;

	elementBX0 = elementB->x;
	elementBY0 = elementB->y;
	elementBX1 = elementB->x + elementB->w;
	elementBY1 = elementB->y + elementB->h;


	if ((elementAX1 <= elementBX0) ||
		(elementBX1 <= elementAX0) ||
		(elementAY1 <= elementBY0) ||
		(elementBY1 <= elementAY0)
		) {

		crash = false;
	}

	return crash;
}

bool aliensImpactDetect(Aliens_t* p_aliens, Craft_t* p_craft, Shoots_t* p_craftShoots, SDL_Renderer* screenRenderer) {
	bool impactDetection = false;
	SDL_Rect alienRectangle, craftShootsRectangel;

	for (Uint16 shoots_i = 0; shoots_i < p_craftShoots->totalNumber; shoots_i++) {
		craftShootsRectangel.x = p_craftShoots->members[shoots_i].area.x;
		craftShootsRectangel.y = p_craftShoots->members[shoots_i].area.y;
		craftShootsRectangel.w = p_craftShoots->members[shoots_i].area.w;
		craftShootsRectangel.h = p_craftShoots->members[shoots_i].area.h;

		for (Uint16 aliens_i = 0; aliens_i < p_aliens->totalNumber; aliens_i++) {
			if ((true == p_aliens->members[aliens_i].active) && (true == p_craftShoots->members[shoots_i].active)) {
				alienRectangle.x = p_aliens->members[aliens_i].x;
				alienRectangle.y = p_aliens->members[aliens_i].y;
				alienRectangle.w = p_aliens->members[aliens_i].w;
				alienRectangle.h = p_aliens->members[aliens_i].h;

				if (true == detectCollision(&alienRectangle, &craftShootsRectangel)) {
					impactDetection = true;
					p_aliens->members[aliens_i].active = false;
					p_craftShoots->members[shoots_i].active = false;
					alienErase(&p_aliens->members[aliens_i], screenRenderer);
					shootErase(&p_craftShoots->members[shoots_i], screenRenderer);
					p_aliens->activeNumber = p_aliens->activeNumber - 1;
					p_craft->score = p_craft->score + 5;
				}
			}
		}
	}
	return impactDetection;
}

bool craftImpactDetect(Craft_t* p_craft, Shoots_t* p_aliensShoots, SDL_Renderer* screenRenderer) {
	bool impactDetection = false;
	SDL_Rect craftRectangle, aliensShootsRectangel;

	craftRectangle.x = p_craft->x;
	craftRectangle.y = p_craft->y;
	craftRectangle.w = p_craft->w;
	craftRectangle.h = p_craft->h;

	for (Uint16 shoots_i = 0; shoots_i < p_aliensShoots->totalNumber; shoots_i++) {
		aliensShootsRectangel.x = p_aliensShoots->members[shoots_i].area.x;
		aliensShootsRectangel.y = p_aliensShoots->members[shoots_i].area.y;
		aliensShootsRectangel.w = p_aliensShoots->members[shoots_i].area.w;
		aliensShootsRectangel.h = p_aliensShoots->members[shoots_i].area.h;

		
		if (true == p_aliensShoots->members[shoots_i].active) {
			if (true == detectCollision(&craftRectangle, &aliensShootsRectangel)) {
				impactDetection = true;			
				p_aliensShoots->members[shoots_i].active = false;
				shootErase(&p_aliensShoots->members[shoots_i], screenRenderer);
				p_craft->health = p_craft->health - 1;
			}
		}
	}
	return impactDetection;
}

bool gameOverDetect(Craft_t* p_craft, Aliens_t* p_aliens) {
	bool gameOver = false;

	//Testing health
	if (p_craft->health <= 0) {
		gameOver = true;
	}

	//Testing aliens collision
	SDL_Rect craftRectangle;
	SDL_Rect alienRectangle;

	craftRectangle.x = p_craft->x;
	craftRectangle.y = p_craft->y;
	craftRectangle.w = p_craft->w;
	craftRectangle.h = p_craft->h;

	for (Uint16 i = 0; i < p_aliens->totalNumber; i++) {
		alienRectangle.x = p_aliens->members[i].x;
		alienRectangle.y = p_aliens->members[i].y;
		alienRectangle.w = p_aliens->members[i].w;
		alienRectangle.h = p_aliens->members[i].h;

		if ((true == p_aliens->members[i].active) && (true == detectCollision(&craftRectangle, &alienRectangle))) {
			gameOver = true;
		}
	}

	return gameOver;
}

void showMessage(ShowMessageIn_t* p_showMessageIn, SDL_Renderer* screenRenderer) {
	SDL_Texture* textTexture = NULL;
	TTF_Font* p_font = NULL;
	Image_t messageImage;

	SDL_Rect stretchRect;

	p_font = TTF_OpenFont("img/space_invaders.ttf", p_showMessageIn->size);

	messageImage = getTextImage(p_showMessageIn->text, p_font, p_showMessageIn->fontColor, screenRenderer);

	TTF_CloseFont(p_font);
	p_font = NULL;

	switch (p_showMessageIn->position) {
		case WINDOW_CENTERED:
			stretchRect.x = (p_showMessageIn->p_gameScreen->total.w - messageImage.w) / 2;
			stretchRect.y = (p_showMessageIn->p_gameScreen->total.h - messageImage.h) / 2;
			break;
		default:
			stretchRect.x = p_showMessageIn->x;
			stretchRect.y = p_showMessageIn->y;
			break;
	}

	stretchRect.w = messageImage.w;
	stretchRect.h = messageImage.h;
	SDL_RenderCopy(screenRenderer, messageImage.image, NULL, &stretchRect);

	SDL_DestroyTexture(messageImage.image);
	messageImage.image = NULL;
}






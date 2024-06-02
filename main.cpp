// Safwan Hafeez     22I-0588
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <unistd.h>
#include <time.h>

using namespace sf;

struct sprite                                                   // A structure is a collection of different datatypes of variables
{                                                               // in one place at the same time
    int xaxis, yaxis;
    int x1, y1;
    int nature, check1;                                         // Making a structure sprite having following variables
    int check2;

    sprite()
    {
        check1 = 0 ;
        check2 = 255 ;
    }
}   board[10][10];

int swapSprites(sprite a, sprite b);                           // Swap function prototype

void mainMenu();                                                // Main Menu function prototype

void game();                                                    // Game function prototype

void game2();                                                   // Level 2 Game Function Prototype

void modeSelect();                                              // Mode Selector function prototype

void pauseMenu();                                               // Pause Menu Function Prototype

int main()                                                      // Main Function
{
    mainMenu();                                                 // Main Menu function called

    return 0;
}

void game()
{
    int ts = 54;                                                // Tile Size

    Vector2i offset(48,24);                                     // Vector Offset

    srand(time(0));

    RenderWindow app ( VideoMode ( 740, 480 ) , "Menegerie");   // Screen Resolution and Title
    app.setFramerateLimit(60);                                  // Screen FPS

    Texture t1,t2,t3;                                           // Declaring Textures

    t1.loadFromFile("images/back2.jpg");                        
    t2.loadFromFile("images/newanimals.png");                   // Loading Textures
    t3.loadFromFile("images/cursor.png");

    SoundBuffer swap;
    swap.loadFromFile("sound/swap.ogg");

    Sound sScore;
    sScore.setBuffer(swap);

    SoundBuffer combo;
    combo.loadFromFile("sound/combo.ogg");

    Sound divine;
    divine.setBuffer(combo);

    Sprite background(t1), gems(t2), Cursor(t3);                // Settings Sprites as Background, gems, and cursor

    for (int i = 1 ; i <= 8 ; i++)
    {
        for (int j = 1 ; j <= 8 ; j++)                          // Making a Board
        {
            board[i][j].nature = rand()%7;
            board[i][j].x1 = j*ts;
            board[i][j].y1 = i*ts;
            board[i][j].yaxis = j;
            board[i][j].xaxis = i;
        }
    }
    
    int checkInput = 0;
    int xPos, yPos;
    int x,y;
    
    Vector2i pos;

    bool swapable = 0;
    bool moveable = 0;

    int score = 0;

    while (app.isOpen())                                        // When app is open
    {
        Event e;

        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)                        // If Close / Cross is Pressed
            {
                app.close();                                    // Close App
            }

            if (e.type == Event::KeyPressed)
            { 
		        if (e.key.code == Keyboard::H)                  // When H is Pressed
                {
		            pauseMenu();                                // Pause Menu
                }
            }

            if (e.type == Event::MouseButtonPressed)            
            {
                if (e.mouseButton.button == Mouse::Left)        // When Left Mouse Button Pressed
                {
                   if (!swapable && !moveable) checkInput++;    // Check condition for swap
                   pos = Mouse::getPosition(app)-offset;        // Getting Position of Mouse
                }
            }
        }

        if (checkInput == 1)                                    // When Click is pressed once
        {
            xPos = pos.x / ts + 1;
            yPos = pos.y / ts + 1;
        }

        if (checkInput == 2)                                    // When Click is pressed twice
        {
            x = pos.x / ts + 1;
            y = pos.y / ts + 1;

            if ( abs(x - xPos) + abs( y - yPos ) == 1 )         // Check Condition for swap
            {
                swapSprites( board[yPos][xPos], board[y][x]);   // Swapping Positions of sprites, Calling swapSprites Function
            
                swapable = 1;                                   // Swap True
                checkInput = 0;
            }

            else
            {
                checkInput = 1;
            }
        }

        for (int i = 1; i <= 8; i++)                            // Nested Loops for Finding a Match On the Board                         
        {
        	for (int j = 1; j <= 8; j++)
        	{
        		if (board[i][j].nature == board[i + 1][j].nature)
        		{
        			if (board[i][j].nature == board[i - 1][j].nature)
        			{
        				for (int n = -1; n <= 1; n++)
        				{
        					board[i + n][j].check1++;           // For Rows
        				}
        			}
        		}

        		if (board[i][j].nature == board[i][j + 1].nature)
        		{
        			if (board[i][j].nature == board[i][j - 1].nature)
        			{
        				for (int n = -1 ; n <= 1; n++)
        				{
        					board[i][j + n].check1++;           // For Columns
        				}
        			}
        		}
        	}
        }

        moveable = false;

        int cnt = 1;

        while (cnt <= 8)                                        // Moving Animation of Swapped Sprites
        {
            int j = 1;

            while (j <= 8)
            {
                sprite &p = board[cnt][j];

                int changeX, changeY;                           // Change in Position

                int n = 0;
                while (n < 4)
                {
                    changeX = p.x1 - p.yaxis * ts;
                    changeY = p.y1 - p.xaxis * ts;

                    if (changeX)
                    {
                        p.x1 = p.x1 - changeX / abs(changeX);
                    }

                    if (changeY)
                    {
                        p.y1 = p.y1 - changeY / abs(changeY);
                    }

                    if (changeX || changeY)
                    {
                        moveable = 1;
                    }

                    n++;
                }

                j++;
            }

            cnt++;
        }


        if (!moveable)                                          // Amination loop for deletion of Swapped Sprites
        {
        	for (int i = 1; i <= 8; i++)
        	{
        		for (int j = 1; j <= 8; j++)
        		{
        			if (board[i][j].check1)
        			{
        				if (board[i][j].check2 > 10)
        				{
        					board[i][j].check2 -= 10;       
        					moveable = true;                    // Checked that sprite is Swapable
        				}
        			}
        		}
        	}
        }

        int swapCheck = 0;

        int i = 1;

        while (i <= 8)
        {
            int j = 1;

            while (j <= 8)
            {
                swapCheck += board[i][j].check1;                // Swap Check, If there is no Swap
                j++;                                            
            }
            i++;
        }

        int count = 0;

        for (int i = 1; i <= 8; i++)                            // Updation of the Board
        {
        	for (int j = 1; j <= 8; j++)                        // After the Swapped Sprites Get Deleted 
        	{
        		if (board[i][j].check1 == 2)
                {
                    sScore.play();
                    score = score + 5;

                    count++;
                }

                else if (board[i][j].check1 == 1)
                {
                    sScore.play();
                    score = score + 3;
                }

                if (count == 4)
                {
                    count = 0;
                    divine.play();
                }
        	}
        }

        Font font;                                              // Declaring Font
        font.loadFromFile("font/font.ttf");                     // Loading Font

        Text text;                                              // Declaring Text
        Text help;

        text.setFont(font);                                     // Setting font of text to be Loaded Font
        help.setFont(font);

        text.setString("Score:   " + std::to_string(score));    // Displaying Score on the Screen

        help.setString("Press H for Help");                     // Displaying Help on the Screen

        text.setCharacterSize(35);                              // Character Size in Pixels
        help.setCharacterSize(35);

        text.setFillColor(sf::Color::Green);                    // Setting Text Color
        text.setStyle(sf::Text::Style::Bold);                   // Setting Bold Style
        text.setOutlineColor(sf::Color::Black);                 // Setting Outline

        help.setFillColor(sf::Color::Green);                    // Setting Text Color
        help.setStyle(sf::Text::Style::Bold);                   // Setting Bold Style
        help.setOutlineColor(sf::Color::Black);                 // Setting Outline

        text.setOutlineThickness(3.5);                          // Outline Thickness

        text.setPosition(510,50);                               // Setting Position on the Screen

        help.setOutlineThickness(3.5);                          // Outline Thickness

        help.setPosition(510,400);

        if (swapable && !moveable)
        {
        	if (!swapCheck)                                     // If there is no Match, swap again
        	{
        		swapSprites(board[yPos][xPos], board[y][x]);
        	}

        	swapable = 0;
        }

        if (!moveable)
        {
        	for (int i = 8; i > 0; i--)
        	{
        		for (int j = 1; j <= 8; j++)
        		{
        			if (board[i][j].check1)
        			{
        				for (int n = i; n > 0; n--)
        				{
        					if (!board[n][j].check1)            // Displaying Board without matched sprites
        					{
        						swapSprites(board[n][j], board[i][j]);
        						break;
        					}
        				}
        			}
        		}
        	}

        	int j = 1;

            while (j <= 8)
            {
                int i = 8, n = 0;

                while (i > 0)
                {
                    if (board[i][j].check1)
                    {
                        board[i][j].nature = rand() % 7;        // Displaying New Sprites after the Swapped ones are matched 
                        board[i][j].y1 = -ts * n++;
                        board[i][j].check1 = 0;
                        board[i][j].check2 = 255;
                    }
                    i--;
                }
                j++;
            }
        }

        app.draw(background);                                   // Drawing Background on the Display Screen

        for (int i = 1; i <= 8; i++)
        {
        	for (int j = 1; j <= 8; j++)                        // Loop for Drawing Gems on the Display Screen
        	{
        		sprite p = board[i][j];
        		gems.setTextureRect(IntRect(p.nature *49, 0, 49, 49));
        		gems.setColor(Color(255, 255, 255, p.check2));
        		gems.setPosition(p.x1, p.y1);
        		gems.move(offset.x - ts, offset.y - ts);
        		app.draw(gems);                                 // Drawing Gems
        	}
        }

        app.draw(text);
        app.draw(help);
        app.display();
    }
}

int swapSprites( sprite a, sprite b)
{
    int temp1, temp2;

    temp1 = a.xaxis;
    a.xaxis = b.xaxis;                                          // Swapping X-Axis of 1st Sprite with 2nd
    b.xaxis = temp1;

    temp2 = a.yaxis;
    a.yaxis = b.yaxis;                                          // Swapping Y-Axis of 1st Sprite with 2nd
    b.yaxis = temp2;

    board[a.xaxis][a.yaxis] = a;                                // Sorting Position on Board of Sprite A 
    board[b.xaxis][b.yaxis] = b;                                // Sorting Position on Board of Sprite B
   
    return 0;
}

void mainMenu()
{
    RenderWindow app(VideoMode(740, 480), "Main Menu");         // Screen resolution and Screen Title
    app.setFramerateLimit(60);                                  // Setting FPS

    Texture menu;                                               // Declaring a Texture named Menu
    menu.loadFromFile("images/mainMenu.jpg");                   // Loading texture
    Sprite background(menu);                                   // Setting Background to be Menu
    
    Font font;                                                  // Declaring Font
    font.loadFromFile("font/font.ttf");                         // Loading Font

    Text text;                                                  // Declaring Text
    text.setFont(font);                                         // Setting font of text to be Loaded Font

    app.draw(background);                                       // Drawing Background

    text.setString("\t\t\t\t\t\t\t\t--Welcome to Menegerie-- \n\n The Goal of the game is to make sequence of any animal \n \t\t\t\tSequences have to be more than of 3 tiles \n\n \t\t\t\t\t\t\t\t\t\t\t\t  START \n\n \t\t\t\t\t\t\t\t\t\t\t\t   EXIT");
    
    text.setCharacterSize(35);                                  // Character Size in Pixels

    text.setFillColor(sf::Color::Green);                        // Setting Text Color
    text.setStyle(sf::Text::Style::Bold);                       // Setting Bold Style
    text.setOutlineColor(sf::Color::Black);                     // Setting Outline

    text.setOutlineThickness(3.5);                              // Outline Thickness

    sf::FloatRect textRect = text.getLocalBounds();             // Getting Text Position

    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);

    text.setPosition(sf::Vector2f(740/2.0f,480/2.0f));          // Centering Text on the Main Screen

    RectangleShape startButton;                                 // Making Shape Start Button
    startButton.setSize(Vector2f(85, 50));                      // Sizing Start
    startButton.setPosition(410-75, 300-25);                    // Positioning Start
    startButton.setFillColor(Color::Green);                     // Color Green

    startButton.setOutlineColor(Color::Black);                  // Outlining Start
    startButton.setOutlineThickness(3.5);                       // Outline Thickness of Start

    RectangleShape endButton;                                   // Making Shape End Button
    endButton.setSize(Vector2f(85, 50));                        // Sizing End
    endButton.setPosition(410-75, 300+50);                      // Positioning End
    endButton.setFillColor(Color::Red);                         // Color Red

    endButton.setOutlineColor(Color::Black);                    // Outlining End
    endButton.setOutlineThickness(3.5);                         // Outline Thickness of End

    SoundBuffer play, start, end;
    play.loadFromFile("sound/play.ogg");
    start.loadFromFile("sound/start.ogg");
    end.loadFromFile("sound/end.ogg");

    Sound main, sbtn, ebtn, sScore;
    main.setBuffer(play);
    sbtn.setBuffer(start);
    ebtn.setBuffer(end);

    app.draw(endButton);
    app.draw(startButton);
    app.draw(text);                                             // Drawing Text

    app.display();
    main.play();

    while (app.isOpen())                                        // While App is Open
    {
        Event event;

        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)                    // If Cross / Close is pressed
            {
                app.close();
            }
        }

        Vector2i mousePos = Mouse::getPosition(app);            // Getting Position of Mouse

        if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            if (Mouse::isButtonPressed(Mouse::Left))            // If Start is pressed
            {
                sbtn.play();
                app.close();                                    // Close App
                modeSelect();                                   // Mode Slector Called
            }
        }

        if (endButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            if (Mouse::isButtonPressed(Mouse::Left))            // If End is pressed
            {
                ebtn.play();
                sleep (1);
                app.close();                                    // Close App
            }  
        }
    }
}

void modeSelect()
{
    RenderWindow window(VideoMode(740, 480), "Mode Selector");  // Screen Resolution
    window.setFramerateLimit(60);

    Texture levelBackground;
    levelBackground.loadFromFile("images/back1.jpg");           // Loading Background
    Sprite background(levelBackground);

    Font font;
    font.loadFromFile("font/font.ttf");                         // Loading Font

    Text text;
    text.setFont(font);                                         // Setting Font

    window.draw(background);                                    // Drawing Background

    text.setString("\t\t\t  Mode Selector \n\n 1. Press Q for Normal Mode \n\n   2. Press W for Trial Mode \n\n   \t\t3. Press E to Exit");
    
    text.setCharacterSize(35);

    text.setFillColor(sf::Color::Green);                        // Color Set to Green
    text.setStyle(sf::Text::Style::Bold);                       // Style Set to Bold
    text.setOutlineColor(sf::Color::Black);                    // Outline Black

    text.setOutlineThickness(3.5);                              // OutlineThickness Setting

    sf::FloatRect textRect = text.getLocalBounds();

    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);

    text.setPosition(sf::Vector2f(740/2.0f,480/2.0f));          // Centering the Text

    SoundBuffer start;
    start.loadFromFile("sound/start.ogg");

    Sound sbtn;
    sbtn.setBuffer(start);

    window.draw(text);                                          // Drawing Text
    window.display();                                           // Displaying Window

    while (window.isOpen()) 
    {
        Event e;

        while (window.pollEvent(e)) 
        {
            if (e.type == Event::KeyPressed) 
            {
                if (e.key.code == Keyboard::Q)                  // Q pressed
                {
                    sbtn.play();
                    window.close();                             // Window Closed
                    game();                                     // Normal Game Called
                }

                if (e.key.code == Keyboard::W)                  // W pressed
                {
                    sbtn.play();
                    window.close();                             // Window Closed
                    game2();                                    // Time Trial Game Called
                }

                if (e.key.code == Keyboard::E)                  // E Pressed
                {
                    window.close();                             // Window Closed
                }

                window.close();
            }

            if (e.type == Event::Closed)
            {
                window.close();
            }
        }
    }
}

void game2()
{
    int ts = 54;                                                // Tile Size

    Vector2i offset(48,24);                                     // Vector Offset

    srand(time(0));

    RenderWindow app ( VideoMode ( 740, 480 ) , "Menegerie");   // Screen Resolution and Title
    app.setFramerateLimit(60);                                  // Screen FPS

    Texture t1,t2,t3;                                           // Declaring Textures

    t1.loadFromFile("images/back2.jpg");                        
    t2.loadFromFile("images/newanimals.png");                   // Loading Textures
    t3.loadFromFile("images/cursor.png");

    Sprite background(t1), gems(t2), Cursor(t3);                // Settings Sprites as Background, gems, and cursor

    RectangleShape progressBar;
    progressBar.setPosition(510,130);                           // Position of Progress Bar
    progressBar.setSize(Vector2f(100,20));                      // Setting Size of Progress Bar
    progressBar.setFillColor(sf::Color::Green);                 // Setting Color of Progress Bar

    progressBar.setOutlineColor(sf::Color::Black);              // Setting outline of Bar
    progressBar.setOutlineThickness(2.5);                       // Setting Thickness of Outline

    SoundBuffer swap;
    swap.loadFromFile("sound/swap.ogg");

    Sound sScore;
    sScore.setBuffer(swap);

    SoundBuffer combo;
    combo.loadFromFile("sound/combo.ogg");

    Sound divine;
    divine.setBuffer(combo);

    const float decayRate = 0.12f;                              // Decay Rate of the Progress Bar
    const float growthRate = 0.08f;                             // Growth Rate of the Progress Bar

    for (int i = 1 ; i <= 8 ; i++)
    {
        for (int j = 1 ; j <= 8 ; j++)                          // Making a Board
        {
            board[i][j].nature = rand()%7;
            board[i][j].x1 = j*ts;
            board[i][j].y1 = i*ts;
            board[i][j].yaxis = j;
            board[i][j].xaxis = i;
        }
    }
    
    int checkInput = 0;
    int xPos, yPos;
    int x,y;
    
    Vector2i pos;

    bool swapable = 0;
    bool moveable = 0;

    int score = 0;

    while (app.isOpen())                                        // When app is open
    {
        Event e;

        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)                        // If Close / Cross is Pressed
            {
                app.close();                                    // Close App
            }

            if (e.type == Event::KeyPressed)
            { 
		        if (e.key.code == Keyboard::H)                  // When H is Pressed
                {
		            pauseMenu();                                // Pause Menu
                }
            }

            if (e.type == Event::MouseButtonPressed)            
            {
                if (e.mouseButton.button == Mouse::Left)        // When Left Mouse Button Pressed
                {
                   if (!swapable && !moveable) checkInput++;    // Check condition for swap
                   pos = Mouse::getPosition(app)-offset;        // Getting Position of Mouse
                }
            }
        }

        progressBar.setSize(Vector2f(progressBar.getSize().x - decayRate, progressBar.getSize().y));

        if (checkInput == 1)                                    // When Click is pressed once
        {
            xPos = pos.x / ts + 1;
            yPos = pos.y / ts + 1;
        }

        if (checkInput == 2)                                    // When Click is pressed twice
        {
            x = pos.x / ts + 1;
            y = pos.y / ts + 1;

            if ( abs(x - xPos) + abs( y - yPos ) == 1 )         // Check Condition for swap
            {
                swapSprites( board[yPos][xPos], board[y][x]);   // Swapping Positions of sprites, Calling swapSprites Function
            
                swapable = 1;                                   // Swap True
                checkInput = 0;
            }

            else
            {
                checkInput = 1;
            }
        }
        
        for (int i = 1; i <= 8; i++)                            // Nested Loops for Finding a Match on the Board              
        {
        	for (int j = 1; j <= 8; j++)
        	{
        		if (board[i][j].nature == board[i + 1][j].nature)
        		{
        			if (board[i][j].nature == board[i - 1][j].nature)
        			{
        				for (int n = -1; n <= 1; n++)
        				{
        					board[i + n][j].check1++;           // For rows
        				}
        			}
        		}

        		if (board[i][j].nature == board[i][j + 1].nature)
        		{
        			if (board[i][j].nature == board[i][j - 1].nature)
        			{
        				for (int n = -1 ; n <= 1; n++)          // For Columns
        				{
        					board[i][j + n].check1++;
        				}
        			}
        		}
        	}
        }

        moveable = false;

        int cnt = 1;

        while (cnt <= 8)                                        // Moving Animation of Swapped Sprites
        {
            int j = 1;

            while (j <= 8)
            {
                sprite &p = board[cnt][j];

                int changeX, changeY;                           // Change in Position x-axis and y-axis

                int n = 0;
                while (n < 4)
                {
                    changeX = p.x1 - p.yaxis * ts;
                    changeY = p.y1 - p.xaxis * ts;

                    if (changeX)
                    {
                        p.x1 = p.x1 - changeX / abs(changeX);
                    }

                    if (changeY)
                    {
                        p.y1 = p.y1 - changeY / abs(changeY);
                    }

                    if (changeX || changeY)
                    {
                        moveable = 1;
                    }

                    n++;
                }

                j++;
            }

            cnt++;
        }


        if (!moveable)
        {
        	for (int i = 1; i <= 8; i++)
        	{
        		for (int j = 1; j <= 8; j++)
        		{
        			if (board[i][j].check1)
        			{
        				if (board[i][j].check2 > 10)
        				{
        					board[i][j].check2 -= 10;           // Amination loop for deletion of swapped Sprites
        					moveable = true;
        				}
        			}
        		}
        	}
        }

        int swapCheck = 0;

        int i = 1;

        while (i <= 8)
        {
            int j = 1;

            while (j <= 8)
            {
                swapCheck += board[i][j].check1;                // Swap Check, If there is No swap
                j++;
            }
            i++;
        }

        int temp_score = 0;
        int count = 0;

        for (int i = 1; i <= 8; i++)                            // Updation of the Board
        {
        	for (int j = 1; j <= 8; j++)                        // After the Swapped Sprites Get Deleted 
        	{
        		if (board[i][j].check1 == 2)
                {
                    sScore.play();
                    score = score + 5;

                    count++;
                }

                else if (board[i][j].check1 == 1)
                {
                    sScore.play();
                    score = score + 3;
                }

                if (count == 4)
                {
                    count = 0;
                    divine.play();
                }
        	}
        }

        progressBar.setSize(Vector2f(progressBar.getSize().x + growthRate, progressBar.getSize().y));

        Font font;                                              // Declaring Font
        font.loadFromFile("font/font.ttf");                     // Loading Font

        Text text;                                              // Declaring Text
        Text help;

        text.setFont(font);                                     // Setting font of text to be Loaded Font
        help.setFont(font);

        text.setString("Score:   " + std::to_string(score));    // Displaying Score on the Screen

        help.setString("Press H for Help");                     // Displaying Help on the Screen

        text.setCharacterSize(35);                              // Character Size in Pixels
        help.setCharacterSize(35);

        text.setFillColor(sf::Color::Green);                    // Setting Text Color
        text.setStyle(sf::Text::Style::Bold);                   // Setting Bold Style
        text.setOutlineColor(sf::Color::Black);                 // Setting Outline

        help.setFillColor(sf::Color::Green);                    // Setting Text Color
        help.setStyle(sf::Text::Style::Bold);                   // Setting Bold Style
        help.setOutlineColor(sf::Color::Black);                 // Setting Outline

        text.setOutlineThickness(3.5);                          // Outline Thickness

        text.setPosition(510,50);                               // Setting Position on the Screen

        help.setOutlineThickness(3.5);                          // Outline Thickness

        help.setPosition(510,400);

        if (swapable && !moveable)
        {
        	if (!swapCheck)                                     // If there is no Match, swap again
        	{
        		swapSprites(board[yPos][xPos], board[y][x]);
        	}

        	swapable = 0;
        }

        if (!moveable)
        {
        	for (int i = 8; i > 0; i--)
        	{
        		for (int j = 1; j <= 8; j++)
        		{
        			if (board[i][j].check1)
        			{
        				for (int n = i; n > 0; n--)
        				{
        					if (!board[n][j].check1)        // Displaying Board without matched sprites
        					{
        						swapSprites(board[n][j], board[i][j]);
        						break;
        					}
        				}
        			}
        		}
        	}

        	int j = 1;

            while (j <= 8)
            {
                int i = 8, n = 0;

                while (i > 0)
                {
                    if (board[i][j].check1)
                    {
                        board[i][j].nature = rand() % 7;    // Displaying New Sprites after the Swapped ones are matched 
                        board[i][j].y1 = -ts * n++;
                        board[i][j].check1 = 0;
                        board[i][j].check2 = 255;
                    }
                    i--;
                }
                j++;
            }
        }

        app.draw(background);                               // Drawing Background on the Display Screen

        for (int i = 1; i <= 8; i++)
        {
        	for (int j = 1; j <= 8; j++)                    // Loop for Drawing Gems on the Display Screen
        	{
        		sprite p = board[i][j];
        		gems.setTextureRect(IntRect(p.nature *49, 0, 49, 49));
        		gems.setColor(Color(255, 255, 255, p.check2));
        		gems.setPosition(p.x1, p.y1);
        		gems.move(offset.x - ts, offset.y - ts);
        		app.draw(gems);                             // Drawing Gems
        	}
        }

        app.draw(progressBar);
        app.draw(text);
        app.draw(help);
        app.display();
    }
}

void pauseMenu()
{
    RenderWindow window(VideoMode(740, 480), "Pause Menu");

	Texture pauseMenu;

	pauseMenu.loadFromFile("images/back1.jpg");

	Sprite background(pauseMenu);

	Font font;
	font.loadFromFile("font/font.ttf");

	Text text;
    Text credits;

	text.setFont(font);
    credits.setFont(font);
	window.draw(background);
	 
	text.setString("The Goal of the game is to make sequence of any animal \n \t\t\t\tSequences have to be more than of 3 tiles \n\n \t\t\t\t\t\t\t\t\t\t Press B for Back");
	credits.setString("Game Made By: \n \t\t\t\t\t Safwan Hafeez \n");

    text.setCharacterSize(35);                              // Character Size in Pixels

    text.setFillColor(sf::Color::Green);                    // Setting Text Color
    text.setStyle(sf::Text::Style::Bold);                   // Setting Bold Style
    text.setOutlineColor(sf::Color::Black);                 // Setting Outline

    text.setOutlineThickness(3.5);                          // Outline Thickness

    credits.setCharacterSize(20);                           // Character Size in Pixels

    credits.setFillColor(sf::Color::Green);                 // Setting Text Color
    credits.setStyle(sf::Text::Style::Bold);                // Setting Bold Style
    credits.setOutlineColor(sf::Color::Black);              // Setting Outline

    credits.setOutlineThickness(2.25);                       // Outline Thickness

    credits.setPosition(10,350);

    sf::FloatRect textRect = text.getLocalBounds();         // Getting Text Position

    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);

    text.setPosition(sf::Vector2f(740/2.0f,480/2.0f));      // Centering Text on the Main Screen
	
    window.draw(text);
    window.draw(credits);
	window.display();

	while (window.isOpen())
    {
	    Event e;

	    while (window.pollEvent(e))
        {
	        if (e.type == Event::KeyPressed)
            {
	            if (e.key.code == Keyboard::B)
                {
	                window.close();
                }   
	        }

            if (e.type == Event::Closed)
            {                   
                window.close();
            }
	    }
    }
}
// #include <iostream>
// #include <vector>
// #include <cstdlib>
// #include <ctime>

// #ifdef _WIN32
// #include <conio.h> // For _kbhit() and _getch()
// #include <windows.h> // For Sleep()
// #else
// #include <unistd.h> // For usleep()
// #include <termios.h> // For non-blocking input
// #include <fcntl.h> // For file control options
// #endif

// using namespace std;

// // Dimensions for the grid
// const int WIDTH = 20;
// const int HEIGHT = 20;

// // Directions for movement
// enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
// Direction dir;

// // Game variables
// int score;
// int foodX, foodY;
// int headX, headY;
// vector<pair<int, int>> snake; // Snake's body (queue-like)

// // Function to initialize the game
// void setup() {
//     score = 0;
//     dir = STOP; // Start with the direction set to STOP
//     headX = WIDTH / 2;
//     headY = HEIGHT / 2;
//     snake.clear();
    
//     // Initial snake size is 3
//     snake.push_back({headX, headY});       // Head
//     snake.push_back({headX - 1, headY});   // 1st segment
//     snake.push_back({headX - 2, headY});   // 2nd segment

//     // Place the initial food
//     srand(time(0));
//     foodX = rand() % WIDTH;
//     foodY = rand() % HEIGHT;
// }

// // Draw the game board
// void draw() {
//     // Clear screen
//     #ifdef _WIN32
//     system("cls"); // Windows specific
//     #else
//     system("clear"); // Linux specific
//     #endif

//     // Top boundary
//     for (int i = 0; i < WIDTH + 2; ++i) cout << "#";
//     cout << endl;

//     for (int i = 0; i < HEIGHT; ++i) {
//         for (int j = 0; j < WIDTH; ++j) {
//             if (j == 0) cout << "#"; // Left boundary

//             // Display the snake's head and body
//             if (i == headY && j == headX)
//                 cout << "O"; // Snake's head
//             else if (i == foodY && j == foodX)
//                 cout << "F"; // Food
//             else {
//                 bool isBody = false;
//                 for (auto segment : snake) {
//                     if (segment.first == j && segment.second == i) {
//                         cout << "o";
//                         isBody = true;
//                         break;
//                     }
//                 }
//                 if (!isBody) cout << " ";
//             }

//             if (j == WIDTH - 1) cout << "#"; // Right boundary
//         }
//         cout << endl;
//     }

//     // Bottom boundary
//     for (int i = 0; i < WIDTH + 2; ++i) cout << "#";
//     cout << endl;

//     // Display the score
//     cout << "Score: " << score << endl;
// }

// // Handle player input
// void input() {
//     #ifdef _WIN32
//     if (_kbhit()) {
//         switch (_getch()) {
//             case 'w': if (dir != DOWN) dir = UP; break;
//             case 's': if (dir != UP) dir = DOWN; break;
//             case 'a': if (dir != RIGHT) dir = LEFT; break;
//             case 'd': if (dir != LEFT) dir = RIGHT; break;
//             case 'q': exit(0); // Quit the game
//             default: break;
//         }
//     }
//     #else
//     // Non-blocking input for Linux
//     struct termios oldt, newt;
//     tcgetattr(STDIN_FILENO, &oldt);
//     newt = oldt;
//     newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
//     tcsetattr(STDIN_FILENO, TCSANOW, &newt);
//     int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
//     fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

//     char ch = getchar();
//     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//     fcntl(STDIN_FILENO, F_SETFL, oldf);

//     switch (ch) {
//         case 'w': if (dir != DOWN) dir = UP; break;
//         case 's': if (dir != UP) dir = DOWN; break;
//         case 'a': if (dir != RIGHT) dir = LEFT; break;
//         case 'd': if (dir != LEFT) dir = RIGHT; break;
//         case 'q': exit(0); // Quit the game
//         default: break;
//     }
//     #endif
// }

// // Update the game logic
// void logic() {
//     if (dir == STOP) return; // If the direction is STOP, don't update the game

//     // Move the snake's body
//     pair<int, int> prev = {headX, headY};
//     pair<int, int> prev2;

//     // Move the body, starting from the tail
//     for (size_t i = snake.size() - 1; i > 0; --i) {
//         snake[i] = snake[i - 1];
//     }

//     // Move the head based on the direction
//     switch (dir) {
//         case UP: headY--; break;
//         case DOWN: headY++; break;
//         case LEFT: headX--; break;
//         case RIGHT: headX++; break;
//         default: break;
//     }

//     // Add the new head position to the snake
//     snake[0] = {headX, headY};

//     // Check if the snake eats the food
//     if (headX == foodX && headY == foodY) {
//         score++;
//         snake.push_back({-1, -1}); // Grow the snake

//         // Place new food
//         foodX = rand() % WIDTH;
//         foodY = rand() % HEIGHT;
//     }

//     // Check collisions with walls
//     if (headX < 0 || headX >= WIDTH || headY < 0 || headY >= HEIGHT) {
//         cout << "Game Over! Final Score: " << score << endl;
//         cout << "Press 'r' to restart or 'q' to quit: ";
//         char choice;
//         cin >> choice;
//         if (choice == 'r') {
//             setup();  // Restart the game
//         } else if (choice == 'q') {
//             exit(0); // Quit the game
//         }
//     }

//     // Check collisions with itself
//     for (size_t i = 1; i < snake.size(); ++i) {
//         if (snake[i].first == headX && snake[i].second == headY) {
//             cout << "Game Over! Final Score: " << score << endl;
//             cout << "Press 'r' to restart or 'q' to quit: ";
//             char choice;
//             cin >> choice;
//             if (choice == 'r') {
//                 setup();  // Restart the game
//             } else if (choice == 'q') {
//                 exit(0); // Quit the game
//             }
//         }
//     }
// }

// // Main function
// int main() {
//     // Instructions
//     cout << "Welcome to this snake game where the snake grows every time it grabs food. :>" << endl;
//     cout << "Instructions of this game are: " << endl;
//     cout << "PRESS 'w' = Move UP | PRESS 's' = Move DOWN | PRESS 'd' = Move RIGHT | PRESS 'a' = Move LEFT" << endl;
//     cout << "PRESS 'q' to quit this game and PRESS 'r' to restart this game" << endl; 
//     cout << "If the snake's head touches the wall or its tail, the game ends." << endl;
    
//     cout << "Press 'Enter' to start the game..." << endl;
//     cin.get(); // Wait for the player to press Enter

//     setup();
    
//     while (true) {
//         draw();
//         input();
//         logic();
//         #ifdef _WIN32
//         Sleep(50); // Windows-specific sleep
//         #else
//         usleep(50000); // Linux-specific sleep (in microseconds)
//         #endif
//     }
//     return 0;
// }
#include <iostream>
#include <conio.h>  // for _kbhit() and _getch()
#include <windows.h> // for Sleep()

using namespace std;

// Define the screen size
const int width = 20;
const int height = 20;

// Declare variables
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
bool gameOver;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// Function to initialize the game
void Setup() {
    gameOver = false;
    dir = STOP;  // Initially, the snake doesn't move
    x = width / 2;  // Initial x-coordinate of the snake's head
    y = height / 2; // Initial y-coordinate of the snake's head
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 2;  // Set initial length of the snake to 3

    // Initialize the snake's tail positions (it starts with length 3)
    for (int i = 0; i < nTail; i++) {
        tailX[i] = x - i - 1;  // Tail positions are one unit to the left of the head initially
        tailY[i] = y;
    }
}

// Function to draw the screen
void Draw() {
    system("cls"); // clear the console
    for (int i = 0; i < width + 2; i++) cout << "#"; // Top border
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#"; // Left border
            if (i == y && j == x) cout << "O"; // Snake head
            else if (i == fruitY && j == fruitX) cout << "F"; // Fruit
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Tail
                        printTail = true;
                        break;
                    }
                }
                if (!printTail) cout << " "; // Empty space
            }
            if (j == width - 1) cout << "#"; // Right border
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) cout << "#"; // Bottom border
    cout << endl;
    cout << "Score: " << score << endl; // Display score
}

// Function to take user input for movement
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': if (dir != RIGHT) dir = LEFT; break;
            case 'd': if (dir != LEFT) dir = RIGHT; break;
            case 'w': if (dir != DOWN) dir = UP; break;
            case 's': if (dir != UP) dir = DOWN; break;
            case 'x': gameOver = true; break; // Press 'x' to quit the game
            case 'r': gameOver = false; Setup(); break; // Press 'r' to restart the game
        }
    }
}

// Function to update the game state
void Logic() {
    if (dir == STOP) return;  // If the direction is STOP, the snake won't move

    int prevX = tailX[0], prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break;
    }

    // Check for collision with the wall
    if (x >= width || x < 0 || y >= height || y < 0) gameOver = true;

    // Check for collision with itself
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) gameOver = true;
    }

    // Check if the snake eats the fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;  // Increase the length of the snake after eating fruit
    }
}

// Function to prompt for restart after game over
void RestartPrompt() {
    char restartChoice;
    cout << "Game Over! Press 'r' to restart or 'x' to exit: " << endl;
    cout << "FINAL SCORE: " << score << endl;
    cin >> restartChoice;

    if (restartChoice == 'r') {
        Setup(); // Re-initialize the game state
    } else if (restartChoice == 'x') {
        gameOver = true; // Exit the game
    }
}

int main() {
    // Display welcome message once
    cout << "Welcome! to this amazing game where snake grows every time it's moved." << endl;
    cout << "Instructions of this game are: " << endl;
    cout << "PRESS 'w' = Move UP | PRESS 's' = Move DOWN | PRESS 'd' = Move Right | PRESS 'a' = Move Left" << endl;
    cout << "PRESS 'x' to quit this game and PRESS 'r' to restart this game" << endl; 
    cout << "If the snake touches the wall, the game ends and if the snake's mouth touches its tail, the game ends." << endl;

    // Wait for the user to press any key before starting the game
    cout << "Press any key to start the game..." << endl;
    _getch(); // Wait for the user to press a key

    // Main game loop
    while (true) {
        Setup();

        // Loop until game over
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(100); // Delay to make the game playable at a normal speed
        }

        // Ask for restart when the game ends
        RestartPrompt();

        // Exit if the user presses 'x'
        if (gameOver) {
            break;
        }
    }

    return 0;
}
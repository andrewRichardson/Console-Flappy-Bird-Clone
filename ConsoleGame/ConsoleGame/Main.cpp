#include "Main.h"

int main() {
	// Game variables
	char key = ' ';
	bool flag = true;
	int maxWidth = 40;
	int maxHeight = 21;
	string playerArt = "#";
	string obstacleArt = "!!!";
	/*int xl = (maxWidth- playerArt.length)/4;
	int xr = (maxWidth- playerArt.length)/4*3;
	int yt = (maxHeight - 1) / 2;
	int yb = (maxHeight - 1) / 2;*/
	string spaceChar = ".";

	// Player variables
	float velY = 0;
	float speedY = 4.0f;
	float maxSpeed = 2.0f;
	float gravity = 0.25f;
	int playerY = (maxHeight - 1) / 2;

	// Obstacle variables
	int obstacleSpread = 8;
	int obsLength = maxWidth / (obstacleSpread + obstacleArt.length()-1);
	int *obstacleY = new int[obsLength]; //Top of opening of size: openingSize
	int openingSize = 4;
	int minObsY = 3;
	int maxObsY = maxHeight - 3 - openingSize;

	// Scrolling variables
	double *scrollIndex = new double[obsLength];
	double scrollSpeed = 0.5;
	int offsetIndex = 0;

	// Input timing variables
	double refreshTime = 0.0;
	double refreshDuration = 0.35;
	bool hasPressedKey = false;
	
	// Time variables
	long time, previousTime;
	previousTime = clock();
	time = clock();
	double startTime;
	bool hasStarted = false;
	double fps = 24.0;
	double convDT = 0.0;
	double totalTime = 0.0;
	
	cout << "  Use 'W' to jump, press 'Q' to quit.\n\n - Press any key to start the game! - \n";
	_getch();
	
	while (flag) {
		if (!hasStarted) {
			hasStarted = true;
			startTime = clock()/1000.0;

			for (int i = 0; i < obsLength; i++) {
				obstacleY[i] = (int)(((double)rand() / RAND_MAX) * (double)(maxObsY - minObsY)) + minObsY;
				scrollIndex[i] = maxWidth;
			}
		}
		double deltaTime = previousTime - time;
		time = clock();
		convDT += deltaTime / (1000.0 / fps);
		totalTime = (clock()/1000.0)-startTime;
		if (hasPressedKey) {
			refreshTime += deltaTime;
		}
		if (refreshTime >= refreshDuration && key != 'w') {
			hasPressedKey = false;
			refreshTime = 0;
		}

		if (convDT >= 1) {
			// Update logic
			convDT--;
			string output = "";
			system("cls");
			cout << "  Time: "  << totalTime << " \t|   Velocity: " << -velY << "\n";

			// Key parsing
			if (key == 'w' && !hasPressedKey) {
				velY -= speedY;
				hasPressedKey = true;
			}
			else if (key == 'q') {
				flag = false;
				break;
			}

			// Player velocity logic
			velY += gravity;

			if (velY < -maxSpeed / 3 * 2) {
				velY = -maxSpeed / 3 * 2;
			}
			if (velY > maxSpeed) {
				velY = maxSpeed;
			}

			playerY += (int)velY;

			if (playerY < 0)
				playerY = 0;
			if (playerY > maxHeight - 1)
				playerY = maxHeight - 1;

			// Obstacle logic
			for (int i = 0; i < obsLength; i++) {
				if (offsetIndex >= i) {
					scrollIndex[i] -= scrollSpeed;
				}
				else {
					if (scrollIndex[i - 1] <= maxWidth - obstacleSpread-1) {
						offsetIndex++;
					}
				}
				int temp = -(int)obstacleArt.length()+1;
				if (scrollIndex[i] <= temp) {
					scrollIndex[i] = maxWidth;
					obstacleY[i] = (int)(((double)rand() / RAND_MAX) * (double)(maxObsY - minObsY))+minObsY;
				}
			}

			// Calculate graphics
			for (int y = 0; y < maxHeight; y++) {
				for (int x = 0; x < maxWidth; x++) {
					bool sflag = false;
					for (int i = 0; i < obsLength; i++) {
						if (x == (int)scrollIndex[i] && x <= maxWidth-obstacleArt.length() && (y < obstacleY[i] || y >= obstacleY[i] + openingSize)) {
							output += obstacleArt;
							x += obstacleArt.length()-1;
							i = obsLength;
							sflag = false;
						}
						else {
							sflag = true;
						}
					}
					if (sflag) {
						output += spaceChar;
					}
				}
				output += "\n";
			}
			int playerPos = playerY*(maxWidth+1) + maxWidth / 4;
			output.replace(playerPos, 1, playerArt);
			output += "\n";
			
			cout << output;

			// Update logic
			if (_kbhit()) {
				key = _getch();
			}
			else {
				key = ' ';
			}
		}
		previousTime = clock();
	}
	return 0;
}
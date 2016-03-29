#include "Main.h"

int main() {
	char key = ' ';
	bool flag = true;
	int maxWidth = 41;
	int maxHeight = 21;
	string playerArt = "#";
	string obstacleArt = "!!!";
	/*int xl = (maxWidth- playerArt.length)/4;
	int xr = (maxWidth- playerArt.length)/4*3;
	int yt = (maxHeight - 1) / 2;
	int yb = (maxHeight - 1) / 2;*/
	string spaceChar = ".";

	float velY = 0;
	float speedY = 5.0f;
	float maxSpeed = 2.6f;
	float gravity = 0.45f;
	int playerY = (maxHeight - 1) / 2;

	cout << "  Use 'W' to jump, press 'Q' to quit.\n\n - Press any key to start the game! - \n";
	_getch();
	long time, previousTime;
	previousTime = clock();
	time = clock();
	double startTime;
	bool hasStarted = false;
	double fps = 24.0;
	double convDT = 0.0;
	double totalTime = 0.0;
	double refreshTime = 0.0;
	double refreshDuration = 0.35;
	bool hasPressedKey = false;
	while (flag) {
		if (!hasStarted) {
			hasStarted = true;
			startTime = clock()/1000.0;
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
			convDT--;
			string output = "";
			system("cls");
			cout << "  Time: "  << totalTime << " \t|   Velocity: " << velY << "\n";

			if (key == 'w' && !hasPressedKey) {
				velY -= speedY;
				hasPressedKey = true;
			}
			else if (key == 'q') {
				flag = false;
				break;
			}

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

			for (int i = 0; i < playerY; i++) {
				for (int j = 0; j < maxWidth; j++) {
					output += spaceChar;
				}
				output += "\n";
			}
			for (int i = 0; i < maxWidth/4; i++) {
				output += spaceChar;
			}
			output += playerArt;
			for (int i = 0; i < maxWidth/4*3; i++) {
				output += spaceChar;
			}
			output += "\n";
			for (int i = 0; i < maxHeight-playerY-1; i++) {
				for (int j = 0; j < maxWidth; j++) {
					output += spaceChar;
				}
				output += "\n";
			}
			output += "\n";

			cout << output;

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
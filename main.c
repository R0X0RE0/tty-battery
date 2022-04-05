#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

void drawBatteryScreen(FILE *fp, FILE *fpStatus) {
	
	bool running = true;

	
	char battery[3];
	char batteryStatus[255];
	char batteryBar[255] = "";

	char blank = '.', block = '#';

	fscanf(fp, "%s", battery);
	fscanf(fpStatus, "%s", batteryStatus);

	int batteryLevel = atoi(battery);

	mvprintw(LINES / 2, LINES / 2, "%i\% (%s)", batteryLevel, batteryStatus);

	for (int i = 0; i < batteryLevel / 5; i++) {
		strcat(batteryBar, "#");
	}
	
	for (int i = 0; i < 20 - (batteryLevel / 5); i++) {
		strcat(batteryBar, ".");
	}
	
	mvprintw(LINES / 2 + 1, LINES / 2, "%s\n", batteryBar);
}

int main() {
	FILE *fp, *fpStatus;

	fp = fopen("/sys/class/power_supply/BAT1/capacity", "r");

	if (fp == NULL) {
		printf("Error opening battery capacity\n");
		exit(1);
	}

	fpStatus = fopen("/sys/class/power_supply/BAT1/status", "r");

	if (fpStatus == NULL) {
		printf("Error opening battery status\n");
		exit(1);
	}

	initscr();
	start_color();
	
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	attron(COLOR_PAIR(1));

	int key;
	do {
		wrefresh(stdscr);
		drawBatteryScreen(fp, fpStatus);
		key = wgetch(stdscr);
		switch(key) {
			case '1':
				attrset(COLOR_PAIR(1));
				break;
				
			case '2':
				attrset(COLOR_PAIR(2));
				break;

			case '3':
				attrset(COLOR_PAIR(3));
				break;

			case '4':
				attrset(COLOR_PAIR(4));
				break;

			case '5':
				attrset(COLOR_PAIR(5));
				break;
			}
	} while (key != 'q');
	
	endwin();
	fclose(fp);
	fclose(fpStatus);
	return 0;
}

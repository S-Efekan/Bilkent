// OMER KESKIN 22401777 164-4 Dune Piercer
// We have a balista as weapon and targets as enemies,
// We have 3 ammos which are reloaded after we are out of any.
// Targets appear as waves each cordinates are randomized.
// Arrows can go through red targets but not blue ones.Red is 1 blue is 3 points.
// There is an hourglass animation to see how much time left and Ammo reloading animation.
// Instead of MOVING the weapon I decided to make it so that it will follow my mouse.

//libs
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>
//
#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 960
#define TIMER_PERIOD   20   // Period for the timer
#define TIMER_ON        1   // 0:Disable timer, 1:Enable timer
#define PI  3.14159265358
#define D2R 0.01745329252
#define BALISTAPOS -270
#define MAX_TARGETS 100
#define MAX_ARROWS 3
// Global variables 
int  winWidth, winHeight, count = 0;
float timePassed = 0;
int reloadArrow = 0;
bool activeTimer = false;
int r = 180, g = 172, b = 50;
float delta = TIMER_PERIOD / 10;
int timesMoved = 0;
int score = 0;
float GAME_TIME = 30;
//
typedef struct {
	double x, y;
} point_t;
point_t mouse;
typedef struct {
	int x, y;
	float vx, vy;
	int hit;
	int hard;
}target_t;
target_t TARGETS[MAX_TARGETS];
int target_count = 0;
typedef struct {
	double x, y;
	float vx, vy;
	float angle;
	int hit;
	int out;
}arrow_t;
arrow_t ARROWS[MAX_ARROWS];
int arrow_count = 0;
//
void restartGame ( );
int checkCollision ( arrow_t arrow, target_t target );
// To display text
void vprint ( int x, int y, void* font, const char* string, ... ) {
	va_list ap;
	va_start ( ap, string );
	char str[1024];
	vsprintf_s ( str, sizeof ( str ), string, ap );
	va_end ( ap );
	int len = (int)strlen ( str );
	glRasterPos2f ( x, y );
	for (int i = 0; i < len; i++)
		glutBitmapCharacter ( font, str[i] );
}
// To create circles
void circle ( int x, int y, int r ) {
	float angle;
	glBegin ( GL_POLYGON );
	for (int i = 0; i < 100; i++) {
		angle = 2 * PI * i / 100;
		glVertex2f ( x + r * cos ( angle ), y + r * sin ( angle ) );
	}
	glEnd ( );
}
void circle_target ( int x, int y, int r ) {
	float angle;
	glBegin ( GL_POLYGON );
	for (int i = 0; i < 100; i++) {
		angle = 2 * PI * i / 10;
		glVertex2f ( x + r * cos ( angle ), y + r * sin ( angle ) );
	}
	glEnd ( );
}
//empty circles
void circle_wire_balista ( int x, int y, int r, float angle ) {
	glBegin ( GL_LINE_LOOP );
	for (int i = -60; i < 60; i += 2) {
		float theta = (i + angle * (180 / PI)) * D2R;
		glVertex2f ( x + r * cos ( theta ), y + r * sin ( theta ) );
	}
	glEnd ( );
}
void circle_target_empty ( int x, int y, int r ) {
	float angle;
	glBegin ( GL_LINE_LOOP );
	for (int i = 0; i < 100; i++) {
		angle = 2 * PI * i / 10;
		glVertex2f ( x + r * cos ( angle ), y + r * sin ( angle ) );
	}
	glEnd ( );
}
//
void vertex ( point_t P, point_t Tr, double angle ) {
	double xp = (P.x * cos ( angle ) - P.y * sin ( angle )) + Tr.x;
	double yp = (P.x * sin ( angle ) + P.y * cos ( angle )) + Tr.y;
	glVertex2d ( xp, yp );
}
//Spawning & Drawing Targets
void spawnRedTarget ( float x, float y, float vx, float vy ) {
	if (target_count < MAX_TARGETS) {
		TARGETS[target_count].x = x;
		TARGETS[target_count].y = y;
		TARGETS[target_count].vx = vx;
		TARGETS[target_count].vy = vy;
		TARGETS[target_count].hit = 0;
		TARGETS[target_count].hard = 0;
		target_count++;
	}
}
void spawnBlueTarget ( float x, float y, float vx, float vy ) {
	if (target_count < MAX_TARGETS) {
		TARGETS[target_count].x = x;
		TARGETS[target_count].y = y;
		TARGETS[target_count].vx = vx;
		TARGETS[target_count].vy = vy;
		TARGETS[target_count].hit = 0;
		TARGETS[target_count].hard = 1;
		target_count++;
	}
}
//
void drawRedTarget ( int x, int y ) {
	glColor3ub ( 225, 11, 65 );
	circle_target ( x, y, 25 );
	glColor3ub ( 255, 255, 255 );
	circle_target_empty ( x, y, 15 );
	circle_target_empty ( x, y, 5 );
}
void drawBlueTarget ( int x, int y ) {
	glColor3ub ( 38, 197, 245 );
	circle_target ( x, y, 25 );
	glColor3ub ( 255, 255, 255 );
	circle_target_empty ( x, y, 15 );
	circle_target_empty ( x, y, 5 );

}
//
void drawBalista ( ) {
	float angle = atan2 ( mouse.y - BALISTAPOS, mouse.x );
	glColor3f ( 0.6f, 0.3f, 0.1f );
	glBegin ( GL_QUADS );
	vertex ( { -25, -7 }, { 0, BALISTAPOS }, angle );
	vertex ( { -25, +7 }, { 0, BALISTAPOS }, angle );
	vertex ( { +40, +7 }, { 0, BALISTAPOS }, angle );
	vertex ( { +40, -7 }, { 0, BALISTAPOS }, angle );
	glEnd ( );
	//
	if (arrow_count < MAX_ARROWS) {
		glColor3f ( 0, 0, 0 );
		glBegin ( GL_QUADS );
		vertex ( { 0, -4 }, { 0, BALISTAPOS }, angle );
		vertex ( { 0, +4 }, { 0, BALISTAPOS }, angle );
		vertex ( { +60, +4 }, { 0, BALISTAPOS }, angle );
		vertex ( { +60, -4 }, { 0, BALISTAPOS }, angle );
		glEnd ( );
		glColor3f ( 1, 0, 0 );
		glBegin ( GL_TRIANGLES );
		vertex ( { 60, -25 }, { 0, BALISTAPOS }, angle );
		vertex ( { 60, +25 }, { 0, BALISTAPOS }, angle );
		vertex ( { 90, 0 }, { 0, BALISTAPOS }, angle );
		glEnd ( );
	}
	//
	glColor3f ( 0.8f, 0.8f, 0.8f );
	glBegin ( GL_LINES );
	vertex ( { 0, 0 }, { 0, BALISTAPOS }, angle );
	vertex ( { 12.5 / sin ( 30 * D2R ), 40 }, { 0, BALISTAPOS }, angle );
	glEnd ( );
	glBegin ( GL_LINES );
	vertex ( { 0, 0 }, { 0, BALISTAPOS }, angle );
	vertex ( { 12.5 / sin ( 30 * D2R ), -40 }, { 0, BALISTAPOS }, angle );
	glEnd ( );
	//
	glEnable ( GL_LINE_STIPPLE );
	glLineStipple ( 1, 0x00F0 );
	glBegin ( GL_LINES );
	vertex ( { 80, 0 }, { 0, BALISTAPOS }, angle );
	vertex ( { 300, 0 }, { 0, BALISTAPOS }, angle );
	glEnd ( );
	glDisable ( GL_LINE_STIPPLE );
	//
	glColor3f ( 0.6f, 0.3f, 0.1f );
	circle_wire_balista ( 0, BALISTAPOS, 50, angle );
	if (angle < 0)
		angle += 2 * PI;
}
void updateArrow ( ) {
	for (int i = 0; i < arrow_count; i++)
	{
		if (!ARROWS[i].out)
		{

			ARROWS[i].x += ARROWS[i].vx * delta;
			ARROWS[i].y += ARROWS[i].vy * delta;
			if (ARROWS[i].x < -winWidth / 2 + 120 || ARROWS[i].x > winWidth / 2 - 120 ||
				 ARROWS[i].y < -winHeight / 2 + 50 || ARROWS[i].y > winHeight / 2 - 170)
				ARROWS[i].out = 1;
			for (int j = 0; j < target_count; j++) {
				if (!TARGETS[j].hit && checkCollision ( ARROWS[i], TARGETS[j] )) {
					TARGETS[j].hit = 1;
					score += 1;
					if (TARGETS[j].hard == 1) {
						score += 2;
						ARROWS[i].out = 1;
						break;
					}
				}
			}
		}
	}
}
void shootArrow ( ) {
	if (arrow_count < MAX_ARROWS) {
		ARROWS[arrow_count].angle = atan2 ( mouse.y - BALISTAPOS, mouse.x );
		ARROWS[arrow_count].x = 0;
		ARROWS[arrow_count].y = BALISTAPOS;
		int speed = 8;
		ARROWS[arrow_count].vx = speed * cos ( ARROWS[arrow_count].angle );
		ARROWS[arrow_count].vy = speed * sin ( ARROWS[arrow_count].angle );
		ARROWS[arrow_count].out = 0;
		ARROWS[arrow_count].hit = 0;
		arrow_count++;
	}
}
int checkCollision ( arrow_t arrow, target_t target ) {
	float tipX = arrow.x + 90 * cos ( arrow.angle );
	float tipY = arrow.y + 90 * sin ( arrow.angle );

	float dx = tipX - target.x;
	float dy = tipY - target.y;
	float distance = sqrt ( dx * dx + dy * dy );

	if (distance < 28)
		return 1;
	return 0;
}
void drawArrow ( ) {

	for (int i = 0; i < arrow_count; i++)
	{
		if (!ARROWS[i].out)
		{
			glColor3f ( 0, 0, 0 );
			glBegin ( GL_QUADS );
			vertex ( { 0, -4 }, { ARROWS[i].x, ARROWS[i].y }, ARROWS[i].angle );
			vertex ( { 0, +4 }, { ARROWS[i].x, ARROWS[i].y }, ARROWS[i].angle );
			vertex ( { +60, +4 }, { ARROWS[i].x, ARROWS[i].y }, ARROWS[i].angle );
			vertex ( { +60, -4 }, { ARROWS[i].x, ARROWS[i].y }, ARROWS[i].angle );
			glEnd ( );

			glColor3f ( 1, 0, 0 );
			glBegin ( GL_TRIANGLES );
			vertex ( { 60, -25 }, { ARROWS[i].x, ARROWS[i].y }, ARROWS[i].angle );
			vertex ( { 60, +25 }, { ARROWS[i].x, ARROWS[i].y }, ARROWS[i].angle );
			vertex ( { 90, 0 }, { ARROWS[i].x, ARROWS[i].y }, ARROWS[i].angle );
			glEnd ( );
		}
	}
}
//
void drawCastleBrick ( ) {
	double windowWidth = WINDOW_WIDTH * 0.9; // Just to fit it in
	double windowHeight = WINDOW_HEIGHT * 0.7;
	int x, y;



	for (int i = -windowWidth / 2 + 2; i <= windowWidth / 2; i += 120)
	{
		glColor3ub ( 79, 51, 34 );
		glRectf ( i, -windowHeight / 2, i + 120, -windowHeight / 3 );


		glColor3ub ( 72, 69, 84 );
		glBegin ( GL_LINE_LOOP );
		glVertex2d ( i + 35, -windowHeight / 3 );
		glVertex2d ( i + 35, -windowHeight / 3 - 30 );
		glEnd ( );
		glBegin ( GL_LINE_LOOP );
		glVertex2d ( i + 100, -windowHeight / 3 );
		glVertex2d ( i + 100, -windowHeight / 3 - 30 );
		glEnd ( );
		glBegin ( GL_LINE_LOOP );
		glVertex2d ( i, -windowHeight / 3 - 30 );
		glVertex2d ( i + 120, -windowHeight / 3 - 30 );
		glEnd ( );

		glBegin ( GL_LINE_LOOP );
		glVertex2d ( i + 55, -windowHeight / 3 - 30 );
		glVertex2d ( i + 55, -windowHeight / 3 - 60 );
		glEnd ( );
		glBegin ( GL_LINE_LOOP );
		glVertex2d ( i + 80, -windowHeight / 3 - 30 );
		glVertex2d ( i + 80, -windowHeight / 3 - 60 );
		glEnd ( );
		glBegin ( GL_LINE_LOOP );
		glVertex2d ( i, -windowHeight / 3 - 60 );
		glVertex2d ( i + 120, -windowHeight / 3 - 60 );
		glEnd ( );

		glBegin ( GL_LINE_LOOP );
		glVertex2d ( i + 15, -windowHeight / 3 - 60 );
		glVertex2d ( i + 15, -windowHeight / 3 - 90 );
		glEnd ( );
		glBegin ( GL_LINE_LOOP );
		glVertex2d ( i + 70, -windowHeight / 3 - 60 );
		glVertex2d ( i + 70, -windowHeight / 3 - 90 );
		glEnd ( );
		glBegin ( GL_LINE_LOOP );
		glVertex2d ( i, -windowHeight / 3 - 90 );
		glVertex2d ( i + 120, -windowHeight / 3 - 90 );
		glEnd ( );

		glBegin ( GL_LINE_LOOP );
		glVertex2d ( i + 60, -windowHeight / 3 - 90 );
		glVertex2d ( i + 60, -windowHeight / 3 - 113 );
		glEnd ( );
		glBegin ( GL_LINE_LOOP );
		glVertex2d ( i + 100, -windowHeight / 3 - 90 );
		glVertex2d ( i + 100, -windowHeight / 3 - 113 );
		glEnd ( );
		glLineWidth ( 3 );
		glColor3ub ( 127, 127, 127 );
		glBegin ( GL_LINE_LOOP );
		glVertex2d ( i, -windowHeight / 3 );
		glVertex2d ( i, -windowHeight / 2 );
		glVertex2d ( i + 120, -windowHeight / 2 );
		glVertex2d ( i + 120, -windowHeight / 3 );
		glEnd ( );
	}

	for (int j = -windowWidth / 2 + 2; j <= windowWidth / 2; j += 120)
	{
		glColor3ub ( 60, 60, 60 );
		glBegin ( GL_QUADS );
		glVertex2d ( j, -windowHeight / 2.8 );
		glVertex2d ( j + 40, -windowHeight / 3.3 );
		glVertex2d ( j + 80, -windowHeight / 3.3 );
		glVertex2d ( j + 120, -windowHeight / 2.8 );
		glEnd ( );
	}

}
//
void drawFrame ( ) {
	// Draw Right and Left Pillar
	glColor3ub ( 70, 50, 30 );
	glRectf ( -WINDOW_WIDTH * 0.9 / 2, WINDOW_HEIGHT * 0.7 / 2 + 180,
			  -WINDOW_WIDTH * 0.9 / 2 - 200, -WINDOW_HEIGHT * 0.7 / 2 - 180 );
	glRectf ( WINDOW_WIDTH * 0.9 / 2, WINDOW_HEIGHT * 0.7 / 2 + 180,
			  WINDOW_WIDTH * 0.9 / 2 + 200, -WINDOW_HEIGHT * 0.7 / 2 - 180 );
	// Gold borders for each
	glLineWidth ( 4 );
	glColor3ub ( 165, 73, 55 );
	glBegin ( GL_LINE_LOOP );
	glVertex2f ( -WINDOW_WIDTH / 2 + 1, WINDOW_HEIGHT / 2 - 1 );
	glVertex2f ( -WINDOW_WIDTH / 2 + 63, WINDOW_HEIGHT / 2 - 1 );
	glVertex2f ( -WINDOW_WIDTH / 2 + 63, -WINDOW_HEIGHT / 2 );
	glVertex2f ( -WINDOW_WIDTH / 2 + 1, -WINDOW_HEIGHT / 2 );
	glEnd ( );
	glLineWidth ( 4 );
	glColor3ub ( 165, 73, 55 );
	glBegin ( GL_LINE_LOOP );
	glVertex2f ( WINDOW_WIDTH / 2 - 1, WINDOW_HEIGHT / 2 - 1 );
	glVertex2f ( WINDOW_WIDTH / 2 - 63, WINDOW_HEIGHT / 2 - 1 );
	glVertex2f ( WINDOW_WIDTH / 2 - 63, -WINDOW_HEIGHT / 2 );
	glVertex2f ( WINDOW_WIDTH / 2 - 1, -WINDOW_HEIGHT / 2 );
	glEnd ( );
}
void drawTime ( ) {
	// Draw time display background 
	glColor3ub ( 194, 178, 128 );
	glRectf ( -WINDOW_WIDTH * 0.9 / 2, WINDOW_HEIGHT * 0.7 / 2 + 95,
			  -WINDOW_WIDTH * 0.9 / 2 + 180, WINDOW_HEIGHT * 0.7 / 2 + 25 );

	// border effect
	glLineWidth ( 2 );
	glColor3ub ( 1, 1, 1 );
	glBegin ( GL_LINE_LOOP );
	glVertex2f ( -WINDOW_WIDTH * 0.9 / 2, WINDOW_HEIGHT * 0.7 / 2 + 95 );
	glVertex2f ( -WINDOW_WIDTH * 0.9 / 2 + 180, WINDOW_HEIGHT * 0.7 / 2 + 95 );
	glVertex2f ( -WINDOW_WIDTH * 0.9 / 2 + 180, WINDOW_HEIGHT * 0.7 / 2 + 25 );
	glVertex2f ( -WINDOW_WIDTH * 0.9 / 2, WINDOW_HEIGHT * 0.7 / 2 + 25 );
	glEnd ( );

	// Hourglass 
	float timeScaler = (timePassed / 50) * 0.95;
	float posx1 = -WINDOW_WIDTH * 0.9 / 2 + 5;
	float posx2 = -WINDOW_WIDTH * 0.9 / 2 + 65;
	float topposy1 = WINDOW_HEIGHT * 0.7 / 2 + 90;
	float botposy1 = WINDOW_HEIGHT * 0.7 / 2 + 30;
	float midposy = WINDOW_HEIGHT * 0.7 / 2 + 60;
	float midposx = -WINDOW_WIDTH * 0.9 / 2 + 35;
	if (!activeTimer)
	{
		glColor3ub ( 121, 99, 56 );
		glEnable ( GL_LINE_STIPPLE );
		glLineStipple ( 2, 0xAAAA );
		glBegin ( GL_LINES );
		glVertex2f ( midposx, midposy + rand ( ) % 2 + 1 );
		glVertex2f ( midposx, botposy1 );
		glEnd ( );
		glDisable ( GL_LINE_STIPPLE );
	}
	glColor3ub ( 100, 80, 50 );
	glBegin ( GL_LINE_LOOP );
	glVertex2f ( posx1, topposy1 );
	glVertex2f ( posx2, topposy1 );
	glVertex2f ( midposx, midposy );
	glEnd ( );
	glColor3ub ( 121, 99, 56 );
	glBegin ( GL_TRIANGLES );
	glVertex2f ( posx1 + timeScaler, topposy1 - timeScaler );
	glVertex2f ( posx2 - timeScaler, topposy1 - timeScaler );
	glVertex2f ( midposx, midposy ); // absloute
	glEnd ( );
	//
	glLineWidth ( 4 );
	glColor3ub ( 100, 80, 50 );
	glBegin ( GL_LINE_LOOP );
	glVertex2f ( posx1, botposy1 );
	glVertex2f ( posx2, botposy1 );
	glVertex2f ( midposx, midposy );
	glEnd ( );
	glColor3ub ( 121, 99, 56 );
	glBegin ( GL_TRIANGLES );
	glVertex2f ( posx1, botposy1 );// absloute
	glVertex2f ( posx2, botposy1 );// absloute
	glVertex2f ( midposx, botposy1 + timeScaler );
	glEnd ( );
	// Time text
	glColor3ub ( 70, 50, 30 );
	vprint ( -WINDOW_WIDTH * 0.9 / 2 + 55, WINDOW_HEIGHT * 0.7 / 2 + 52,
			 GLUT_BITMAP_TIMES_ROMAN_24, "Time: %.1f", fabs ( GAME_TIME - timePassed / 50 ) );
}
void drawScore ( ) {
	// Draw score board
	glColor3ub ( 70, 50, 30 );
	glRectf ( -WINDOW_WIDTH * 0.9 / 2 + 200, -WINDOW_HEIGHT * 0.7 / 2 - 30,
			  -WINDOW_WIDTH * 0.9 / 2 + 350, -WINDOW_HEIGHT * 0.7 / 2 - 140 );

	// Gold border
	glLineWidth ( 3 );
	glColor3ub ( 212, 175, 55 );
	glBegin ( GL_LINE_LOOP );
	glVertex2f ( -WINDOW_WIDTH * 0.9 / 2 + 200, -WINDOW_HEIGHT * 0.7 / 2 - 30 );
	glVertex2f ( -WINDOW_WIDTH * 0.9 / 2 + 350, -WINDOW_HEIGHT * 0.7 / 2 - 30 );
	glVertex2f ( -WINDOW_WIDTH * 0.9 / 2 + 350, -WINDOW_HEIGHT * 0.7 / 2 - 140 );
	glVertex2f ( -WINDOW_WIDTH * 0.9 / 2 + 200, -WINDOW_HEIGHT * 0.7 / 2 - 140 );
	glEnd ( );

	// Score text
	glColor3ub ( 212, 175, 55 );
	vprint ( -WINDOW_WIDTH * 0.9 / 2 + 210, -WINDOW_HEIGHT * 0.7 / 2 - 60, GLUT_BITMAP_TIMES_ROMAN_24, "SCORE: %d ", score );
	// Adding another line here
	glColor3ub ( 70, 70, 70 );
	glBegin ( GL_LINES );
	glVertex2f ( -120, WINDOW_HEIGHT * 0.7 / 2 + 110 );
	glVertex2f ( 120, WINDOW_HEIGHT * 0.7 / 2 + 110 );
	glEnd ( );

}
void drawAmmo ( ) {
	// Leather quiver
	glColor3ub ( 92, 64, 51 );
	glRectf ( WINDOW_WIDTH * 0.9 / 2 - 120, -WINDOW_HEIGHT * 0.7 / 2 - 30,
			  WINDOW_WIDTH * 0.9 / 2 - 30, -WINDOW_HEIGHT * 0.7 / 2 - 100 );
	// Arrow icons
	glColor3ub ( 70, 70, 70 );
	for (int i = MAX_ARROWS - arrow_count; i > 0; i--) {
		glColor3f ( 0, 0, 0 );
		glRectf ( WINDOW_WIDTH * 0.9 / 2 - 120 + i * 20, -WINDOW_HEIGHT * 0.7 / 2 - 95, WINDOW_WIDTH * 0.9 / 2 - 115 + i * 20, -WINDOW_HEIGHT * 0.7 / 2 - 55 );
		glColor3f ( 1, 0, 0 );
		glBegin ( GL_TRIANGLES );
		glVertex2f ( WINDOW_WIDTH * 0.9 / 2 - 117.5 + i * 20 - 7, -WINDOW_HEIGHT * 0.7 / 2 - 55 );
		glVertex2f ( WINDOW_WIDTH * 0.9 / 2 - 117.5 + i * 20, -WINDOW_HEIGHT * 0.7 / 2 - 45 );
		glVertex2f ( WINDOW_WIDTH * 0.9 / 2 - 117.5 + i * 20 + 7, -WINDOW_HEIGHT * 0.7 / 2 - 55 );
		glEnd ( );
	}
	// Ammo text
	if (arrow_count != MAX_ARROWS)
	{
		glColor3ub ( 212, 175, 55 );
		vprint ( WINDOW_WIDTH * 0.9 / 2 - 95, -WINDOW_HEIGHT * 0.7 / 2 - 40,
				 GLUT_BITMAP_HELVETICA_12, "Ammo" );
	}
	else
	{
		glColor3ub ( 212, 175, 55 );
		vprint ( WINDOW_WIDTH * 0.9 / 2 - 115, -WINDOW_HEIGHT * 0.7 / 2 - 40,
				 GLUT_BITMAP_HELVETICA_12, "RELOADING..." );
	}
	int calcReTime = reloadArrow / 20;
	for (int i = 1; i <= calcReTime; i++)
	{
		glColor4ub ( 0, 0, 0, 64 );
		glRectf ( WINDOW_WIDTH * 0.9 / 2 - 120 + i * 20, -WINDOW_HEIGHT * 0.7 / 2 - 95, WINDOW_WIDTH * 0.9 / 2 - 115 + i * 20, -WINDOW_HEIGHT * 0.7 / 2 - 55 );
		glColor4ub ( 255, 0, 0, 128 );
		glBegin ( GL_TRIANGLES );
		glVertex2f ( WINDOW_WIDTH * 0.9 / 2 - 117.5 + i * 20 - 7, -WINDOW_HEIGHT * 0.7 / 2 - 55 );
		glVertex2f ( WINDOW_WIDTH * 0.9 / 2 - 117.5 + i * 20, -WINDOW_HEIGHT * 0.7 / 2 - 45 );
		glVertex2f ( WINDOW_WIDTH * 0.9 / 2 - 117.5 + i * 20 + 7, -WINDOW_HEIGHT * 0.7 / 2 - 55 );
		glEnd ( );
	}
}
//
void drawSign ( ) { // My name sign and information etc
	if (timePassed / 50 >= 30)
	{
		glColor4ub ( 0, 0, 0, 128 );
		glRectf ( WINDOW_WIDTH * 0.9, -WINDOW_HEIGHT * 0.7, -WINDOW_WIDTH * 0.9, WINDOW_HEIGHT * 0.7 );
		glColor3ub ( 230, 230, 200 );
		vprint ( -65, WINDOW_HEIGHT * 0.7 / 2 - 268, GLUT_BITMAP_TIMES_ROMAN_24, "Game Over!" );
		glColor3ub ( 230, 200, 200 );
		vprint ( -65, WINDOW_HEIGHT * 0.7 / 2 - 298, GLUT_BITMAP_HELVETICA_18, "Score: %d", score );
	}
	else if (activeTimer)
	{
		glColor4ub ( 0, 0, 0, 64 );
		glRectf ( WINDOW_WIDTH * 0.9, -WINDOW_HEIGHT * 0.7, -WINDOW_WIDTH * 0.9, WINDOW_HEIGHT * 0.7 );
		glColor3ub ( 70, 50, 30 );
		glRectf ( -70, WINDOW_HEIGHT * 0.7 / 2 - 275, +85, WINDOW_HEIGHT * 0.7 / 2 - 245 );
		glColor3ub ( 255, 1, 1 );
		vprint ( -65, WINDOW_HEIGHT * 0.7 / 2 - 268, GLUT_BITMAP_TIMES_ROMAN_24, "Game Paused!" );
	}
	drawTime ( );
	drawScore ( );
	// Game title 
	glColor3ub ( 100, 100, 100 );
	glRectf ( -150, WINDOW_HEIGHT * 0.7 / 2 + 80, 150, WINDOW_HEIGHT * 0.7 / 2 + 180 );
	glColor3ub ( 230, 230, 200 );
	vprint ( -65, WINDOW_HEIGHT * 0.7 / 2 + 120, GLUT_BITMAP_TIMES_ROMAN_24, "Dune Piercer" );
	glColor3ub ( 180, 180, 180 );
	vprint ( -65, WINDOW_HEIGHT * 0.7 / 2 + 90, GLUT_BITMAP_HELVETICA_18, "By Omer Keskin" );
	drawAmmo ( );
	glColor3ub ( 230, 200, 200 );
	vprint ( -65, 0 - (WINDOW_HEIGHT * 0.7) / 2 - 55, GLUT_BITMAP_HELVETICA_18, "Space to shoot" );
	vprint ( -65, 0 - (WINDOW_HEIGHT * 0.7) / 2 - 80, GLUT_BITMAP_HELVETICA_18, "F1 to pause/resume" );
	vprint ( -65, 0 - (WINDOW_HEIGHT * 0.7) / 2 - 105, GLUT_BITMAP_HELVETICA_18, "ESC to exit" );
	drawRedTarget ( -WINDOW_WIDTH * 0.9 / 2 + 50, -WINDOW_HEIGHT * 0.7 / 2 - 40 );
	glColor3ub ( 230, 200, 200 );
	vprint ( -WINDOW_WIDTH * 0.9 / 2 + 77, -WINDOW_HEIGHT * 0.7 / 2 - 45, GLUT_BITMAP_HELVETICA_18, "= 1 Score" );
	drawBlueTarget ( -WINDOW_WIDTH * 0.9 / 2 + 50, -WINDOW_HEIGHT * 0.7 / 2 - 95 );
	glColor3ub ( 230, 200, 200 );
	vprint ( -WINDOW_WIDTH * 0.9 / 2 + 77, -WINDOW_HEIGHT * 0.7 / 2 - 100, GLUT_BITMAP_HELVETICA_18, "= 3 Score" );
}
//
void drawArea ( ) {
	double windowWidth = WINDOW_WIDTH * 0.9; // Just to fit it in
	double windowHeight = WINDOW_HEIGHT * 0.7;
	//
	glBegin ( GL_QUADS );
	glColor3ub ( 93, 108, 202 );
	glVertex2f ( -windowWidth / 2, windowHeight / 2 );
	glVertex2f ( windowWidth / 2, windowHeight / 2 );
	glColor3ub ( 143, 158, 252 );
	glVertex2f ( windowWidth / 2, windowHeight / 4 );
	glVertex2f ( -windowWidth / 2, windowHeight / 4 );
	glEnd ( );
	//
	glBegin ( GL_QUADS );
	glColor3ub ( 156, 119, 46 );
	glVertex2f ( -windowWidth / 2, windowHeight / 4 );
	glVertex2f ( windowWidth / 2, windowHeight / 4 );
	glColor3ub ( 236, 179, 126 );
	glVertex2f ( windowWidth / 2, -windowHeight / 4 );
	glVertex2f ( -windowWidth / 2, -windowHeight / 4 );
	glEnd ( );
	//
	glBegin ( GL_QUADS );
	glColor3ub ( 156, 99, 46 );
	glVertex2f ( -windowWidth / 2, -windowHeight / 4 );
	glVertex2f ( windowWidth / 2, -windowHeight / 4 );
	glVertex2f ( windowWidth / 2, -windowHeight / 2 );
	glVertex2f ( -windowWidth / 2, -windowHeight / 2 );
	glEnd ( );
}

//
void updateRedTargets ( ) {
	for (int i = 0; i < 12; i++)
		if (!TARGETS[i].hit) {
			TARGETS[i].x += TARGETS[i].vx * delta;
			if (TARGETS[i].x > 1.5 * winWidth || TARGETS[i].x < -1.5 * winWidth)
				TARGETS[i].hit = 1;
		}
	if (timePassed / 50 > 12)
		for (int i = 14; i < 21; i++)
			if (!TARGETS[i].hit) {
				TARGETS[i].x += TARGETS[i].vx * delta;
				if (TARGETS[i].x > 1.5 * winWidth || TARGETS[i].x < -1.5 * winWidth)
					TARGETS[i].hit = 1;
			}
	if (timePassed / 50 > 23)
		for (int i = 25; i < 31; i++)
			if (!TARGETS[i].hit) {
				TARGETS[i].x += TARGETS[i].vx * delta;
				if (TARGETS[i].x > 1.5 * winWidth || TARGETS[i].x < -1.5 * winWidth)
					TARGETS[i].hit = 1;
			}
}
void updateBlueTargets ( ) {
	if (timePassed / 50 > 8 && timePassed / 50 < 20)
		for (int i = 12; i < 14; i++) { //
			if (!TARGETS[i].hit) {
				if (timePassed / 50 < 9.5)
					TARGETS[i].x += TARGETS[i].vx * delta;
				else if (timePassed / 50 > 10.5)
					TARGETS[i].x -= TARGETS[i].vx * delta;
				if (TARGETS[i].x > 1.5 * winWidth || TARGETS[i].x < -1.5 * winWidth)
					TARGETS[i].hit = 1;

			}
		}
	else if (timePassed / 50 > 20)
		for (int i = 21; i < 25; i++)
			if (!TARGETS[i].hit) {
				if (timePassed / 50 < 21.5)
					TARGETS[i].x += TARGETS[i].vx * delta;
				else if (timePassed / 50 > 22.5)
					TARGETS[i].x -= TARGETS[i].vx * delta;
				if (TARGETS[i].x > 2 * winWidth || TARGETS[i].x < -2 * winWidth)
					TARGETS[i].hit = 1;
			}
}
//
void drawingAllTargets ( ) {
	for (int i = 0; i < 12; i++)
		if (!TARGETS[i].hit)
			drawRedTarget ( TARGETS[i].x, TARGETS[i].y );
	if (timePassed / 50 > 8 && timePassed / 50 < 16)
		for (int i = 12; i < 14; i++)
			if (!TARGETS[i].hit)
				drawBlueTarget ( TARGETS[i].x, TARGETS[i].y );
	if (timePassed / 50 > 12)
		for (int i = 14; i < 21; i++)
			if (!TARGETS[i].hit)
				drawRedTarget ( TARGETS[i].x, TARGETS[i].y );
	if (timePassed / 50 > 20)
		for (int i = 21; i < 25; i++)
			if (!TARGETS[i].hit)
				drawBlueTarget ( TARGETS[i].x, TARGETS[i].y );
	if (timePassed / 50 > 23)
		for (int i = 25; i < 31; i++)
			if (!TARGETS[i].hit)
				drawRedTarget ( TARGETS[i].x, TARGETS[i].y );
}
//
void display ( ) {
	glClearColor ( 0.25, 0.25, 0.25, 0 );
	glClear ( GL_COLOR_BUFFER_BIT );
	glColor3ub ( r, g, b );
	//Drawings
	drawArea ( );
	drawCastleBrick ( );
	drawBalista ( );
	drawArrow ( );
	drawingAllTargets ( );
	drawSign ( );
	drawFrame ( );

	glutSwapBuffers ( );
}
//
void onMove ( int x, int y ) {
	if (!activeTimer)
	{
		mouse.x = x - winWidth / 2;
		mouse.y = winHeight / 2 - y;
	}
}
void onSpecialKeyDown ( int key, int x, int y ) {
	if (key == GLUT_KEY_F1) {
		if (timePassed / 50 >= 30)
			restartGame ( );
		else
			activeTimer = !activeTimer;
	}
	glutPostRedisplay ( );
}
void onKeyDown ( unsigned char key, int x, int y ) {
	if (!activeTimer)
		if (key == 32)
			shootArrow ( );
	if (key == 27)
		exit ( 0 );
	glutPostRedisplay ( );
}
void onResize ( int w, int h ) {
	winWidth = w;
	winHeight = h;
	glViewport ( 0, 0, w, h );
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ( );
	glOrtho ( -w / 2, w / 2, -h / 2, h / 2, -1, 1 );
	glMatrixMode ( GL_MODELVIEW );
	glLoadIdentity ( );
	display ( );
}
//
#if TIMER_ON == 1
void onTimer ( int v ) {
	if (!activeTimer) {
		timePassed++;
		updateRedTargets ( );
		updateBlueTargets ( );
		updateArrow ( );
		if (arrow_count == MAX_ARROWS) {
			reloadArrow++;
			if (reloadArrow % 80 == 0) {
				arrow_count = 0;
				reloadArrow = 0;
			}
		}
	}
	if (timePassed / 50 > 30)
	{
		activeTimer = true;
		glutPostRedisplay ( );
	}
	glutTimerFunc ( TIMER_PERIOD, onTimer, 0 );
	glutPostRedisplay ( );
}
#endif
//
void init ( ) {
	glEnable ( GL_BLEND );
	glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	timePassed = 0;
}
void initWaves ( ) {
	// Red Wave 1
	for (int i = 0; i < 6; i++)
		spawnRedTarget ( i * 55 - WINDOW_WIDTH + 150, rand ( ) % 200 - 100, 1.5, 0 );
	// Red Wave 2
	for (int i = 6; i < 12; i++)
		spawnRedTarget ( (i - 6) * 55 + WINDOW_WIDTH / 2, rand ( ) % 300 - 150, -1.5, 0 );
	// Blue Wave 1
	spawnBlueTarget ( -WINDOW_WIDTH / 2, rand ( ) % 151 - 100, 1.7, 0 );
	spawnBlueTarget ( WINDOW_WIDTH / 2, rand ( ) % 51 + 100, -1.7, 0 );
	// Red Wave 3
	for (int i = 14; i < 18; i++)
		spawnRedTarget ( (i - 14) * 55 - WINDOW_WIDTH + 10, rand ( ) % 200 - 100, 2, 0 );
	// Red Wave 4
	for (int i = 18; i < 21; i++)
		spawnRedTarget ( (i - 18) * 55 + WINDOW_WIDTH / 2, rand ( ) % 300 - 150, -2, 0 );
	// Blue Wave 2
	spawnBlueTarget ( WINDOW_WIDTH / 2, -(rand ( ) % 201) + 200, -1.9, 0 );
	spawnBlueTarget ( WINDOW_WIDTH / 2, -(rand ( ) % 301) + 200, -1.7, 0 );
	spawnBlueTarget ( -WINDOW_WIDTH / 2, -(rand ( ) % 401) + 200, 1.9, 0 );
	spawnBlueTarget ( -WINDOW_WIDTH / 2, -(rand ( ) % 501) + 200, 1.7, 0 );
	// Red Wave 5
	for (int i = 25; i < 28; i++)
		spawnRedTarget ( (i - 25) * 55 - WINDOW_WIDTH / 2, rand ( ) % 300 - 150, 2, 0 );
	// Red Wave 6
	for (int i = 28; i < 31; i++)
		spawnRedTarget ( (i - 28) * 55 + WINDOW_WIDTH / 2, rand ( ) % 200 - 100, -2, 0 );
}
//
void restartGame ( ) {
	activeTimer = false;
	timePassed = 0;
	target_count = 0;
	arrow_count = 0;
	score = 0;
	initWaves ( );
}
int main ( int argc, char* argv[] ) {
	//Waves
	initWaves ( );
	//
	glutInit ( &argc, argv );
	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE );
	glutInitWindowSize ( WINDOW_WIDTH, WINDOW_HEIGHT );
	glutInitWindowPosition ( 600, 300 );
	glutCreateWindow ( "Omer Keskin - HomeWork#2: Dune Piercer" );
	// Keyboard Events
	glutSpecialFunc ( onSpecialKeyDown );
	glutKeyboardFunc ( onKeyDown );
	// Window Events
	glutDisplayFunc ( display );
	glutReshapeFunc ( onResize );
	glutPassiveMotionFunc ( onMove );
	srand ( time ( NULL ) );
#if TIMER_ON == 1
	// Timer Event
	glutTimerFunc ( TIMER_PERIOD, onTimer, 0 );
#endif
	init ( );
	glutMainLoop ( );
	return 0;
}
/**
 * Adam Rasfeld
 * CSE 274
 * CatPictureApp
 *
 */

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CatPictureApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);
  private:
	// Variables
	Surface* mySurface;
	float red, green, blue;
	float time;

	// Screen dimensions
	static const int kAppWidth = 800;
	static const int kAppHeight = 600;
	static const int kTextureSize = 1024;

	// My methods
	void drawLine(uint8_t* pixels, int x1, int y1, int x2, int y2, Color8u color);
	void drawRectangle(uint8_t* pixels, int xCoord, int yCoord, int width, int height, Color8u color);
	void drawCircle(uint8_t* pixels, int xCoord, int yCoord, int radius, Color8u color);
	void drawTriangle(uint8_t* pixels, int xCoord, int yCoord, int width, int height, Color8u color);
};

void CatPictureApp::prepareSettings(Settings* settings) {
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

void CatPictureApp::setup() {
	mySurface = new Surface(kAppWidth, kAppHeight, false);
	time = 0.0;
}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update() {
	uint8_t* pixels = (*mySurface).getData(); // Get our array of pixel information
	time = time + 0.05; // Add to timer

	// Some colors
	Color8u white = Color8u( 255, 255, 255);
	Color8u black = Color8u( 0, 0, 0 );

	// Makes a color that changes
	red = (.5*sin(time/2) + 0.5)*255;
	green = (.5*sin(time) + 0.5)*255;
	blue = (.5*sin(time*2) + 0.5)*255;
	Color8u x = Color8u( red, green, blue );

	// Colors the background
	for(int i = 0; i < kAppWidth*kAppHeight; i++) {
		pixels[3*(i)] = 0;
		pixels[3*(i)+1] = 0;
		pixels[3*(i)+2] = 0;
	}

	// Draws two triangles
	drawLine(pixels, 100, 100, 700, 500, white);
	drawRectangle(pixels, 100, 200, 100, 100, white);
	drawTriangle(pixels, 400, 200, 230, 200, white);
	drawTriangle(pixels, 400, 220, 195, 170, x);
}

/**
 *  Draws a line from one point to another
 *
 *  @param pixels The array of pixels that we will be drawing the line on
 *  @param x1 The x-coordinate of 1st point
 *  @param y1 The y-coordinate of 1st point
 *  @param x2 The x-coordinate of 2nd point
 *  @param y2 The y-coordinate of 2nd point
 *  @param color The color for our line
 */
void CatPictureApp::drawLine(uint8_t* pixels, int x1, int y1, int x2, int y2, Color8u color) {
	if(x1 == x2) {
        int yBeg, yEnd;
        if(y1 > y2){
            yEnd = y1;
			yBeg = y2;
        }
		else {
           yBeg = y1;
           yEnd = y2;
        }
        for(int i = yBeg; i <= yEnd; i++){
			int a = 3*((i*kAppWidth) + x1);
			pixels[a] = color.r;
			pixels[a+1] = color.g;
			pixels[a+2] = color.b;
        }
    }
	else {
		double angle;
        int deltY;
        int xBeg, xEnd, yBeg, yEnd;
        if(x1 >= x2) {
			xEnd = x1;
            yEnd = y1;
            xBeg = x2;
            yBeg = y2;
        }
		else {
            xEnd = x2;
            yEnd = y2;
            xBeg = x1;
            yBeg = y1;
        }
            
        angle = atan((double)(yEnd-yBeg)/(xEnd-xBeg));

        for(int i = xBeg; i <= xEnd; i++){
			deltY = (int)((i-xBeg)*tan(angle));
			int a = 3*((deltY+yBeg)*kAppWidth + i);
            pixels[a] = color.r;
			pixels[a+1] = color.g;
			pixels[a+2] = color.b;
        }
    }
}

/**
 *  Draws a rectangle with center at a given point on the surface
 *
 *  @param pixels The array of pixels that we will be drawing the rectangle on
 *  @param xCoord The x-coordinate of the center of the rectangle
 *  @param yCoord The y-coordinate of the center of the rectangle
 *  @param width The width of the rectangle
 *  @param height The height of the rectangle
 *  @param color The color to fill our rectangle with
 */
void CatPictureApp::drawRectangle(uint8_t* pixels, int xCoord, int yCoord, int width, int height, Color8u color) {
	int xBeg = xCoord;
	int xEnd = xCoord + width;
	int yBeg = yCoord;
	int yEnd = yCoord + height;

	for(int y = yBeg; y < yEnd; y++){
		for(int x = xBeg; x < xEnd; x++){

			pixels[3*(x + y*kAppWidth)] = color.r;
			pixels[3*(x + y*kAppWidth)+1] = color.g;
			pixels[3*(x + y*kAppWidth)+2] = color.b;
		}
	}
}

/**
 *  Draws a circle with center at a given point on the surface
 *
 *  @param pixels The array of pixels that we will be drawing the circle on
 *  @param xCoord The x-coordinate of the center of the circle
 *  @param yCoord The y-coordinate of the center of the ricle
 *  @param radius The radius of the circle
 *  @param color The color to fill our circle with
 */
void CatPictureApp::drawCircle(uint8_t* pixels, int xCoord, int yCoord, int radius, Color8u color) {
	for(int y = yCoord-radius; y <= yCoord+radius; y++) {
		for(int x = xCoord-radius; x <= xCoord+radius; x++) {

		}
	}
}

/**
 *  Draws a triangle with top point at specified coordinates
 *
 *  @param pixels The array of pixels that we will be drawing the triangle on
 *  @param xCoord The x-coordinate of the top of the triangle
 *  @param yCoord The y-coordinate of the top of the triangle
 *  @param width The width of the rectangle
 *  @param height The height of the rectangle
 *  @param color The color to fill our triangle with
 */
void CatPictureApp::drawTriangle(uint8_t* pixels, int xCoord, int yCoord, int width, int height, Color8u color) {
	double currentWidth = 1;
	double rate = .75;
	int yEnd = yCoord+height;

	for(int y = yCoord; y < yEnd; y++) {
		int xLeft = xCoord-(int)(currentWidth-1);
		int xRight = xCoord+(int)(currentWidth-1);
		for(int x = xLeft; x < xRight; x++) {
			pixels[3*(x + y*kAppWidth)] = color.r;
			pixels[3*(x + y*kAppWidth)+1] = color.g;
			pixels[3*(x + y*kAppWidth)+2] = color.b;
		}
		currentWidth += rate;
	}
}

void CatPictureApp::draw() {
	// Draws our surface onto the screen
	gl::draw(*mySurface); 
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )

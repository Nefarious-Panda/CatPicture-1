/**
 *  Adam Rasfeld
 *  CSE 274
 *  9/5/2012
 *  CatPictureApp
 */

// ND: First things first. I saw your program in class and from what I could see you did a really good job.
// I really dont think there is much I would change... And no I'm not saying that because im a pink floyd fan.
// Also I will just be commenting the recommended changes and will be marked with a ND
// One change I would try to do for the next program is to comment a little more.. I'm not that much of a commenting 
//   person either, but it would help with some clearity as to what exactly each method does, but not to much more!

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

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
	float red_, green_, blue_;
	float time;

	// Screen dimensions
	static const int kAppWidth = 800;
	static const int kAppHeight = 600;
	static const int kTextureSize = 1024;

	// My methods
	void copy(uint8_t* pixels, int x1, int y1, int width, int height, int x2, int y2);
	void drawLine(uint8_t* pixels, int x1, int y1, int x2, int y2, Color8u color);
	void drawRectangle(uint8_t* pixels, int xCoord, int yCoord, int width, int height, Color8u color);
	void drawCircle(uint8_t* pixels, int xCoord, int yCoord, int radius, Color8u color);
	void drawTriangle(uint8_t* pixels, int xCoord, int yCoord, int width, int height, Color8u color);
	void blur(uint8_t* pixels);
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

	// ND: maybe put these in an Array for easy access?
	// Some colors
	Color8u white = Color8u( 255, 255, 255);
	Color8u black = Color8u( 0, 0, 0 );
	Color8u red = Color8u( 255, 0, 0 );
	Color8u orange = Color8u( 255, 140, 0 );
	Color8u yellow = Color8u( 255, 255, 0 );
	Color8u green = Color8u( 102, 205, 0 );
	Color8u cyan = Color8u( 0, 205, 205 );
	Color8u blue = Color8u( 0, 0, 255 );
	Color8u purple = Color8u( 224, 102, 255 );

	// Makes a color that changes
	red_ = (.5*sin(time/2) + 0.5)*255;
	green_ = (.5*sin(time) + 0.5)*255;
	blue_ = (.5*sin(time*2) + 0.5)*255;
	Color8u x = Color8u( red_, green_, blue_ );

	// Colors the background
	for(int i = 0; i < kAppWidth*kAppHeight; i++) {
		pixels[3*(i)] = 255;
		pixels[3*(i)+1] = 255;
		pixels[3*(i)+2] = 255;
	}

	// Draws rectangle border
	drawRectangle(pixels, 10, 10, 780, 580, black);

	int rainbowWidth = 60;
	int phase = 1;
	double rate = .58;
	double rainbowXBeg = 442;
	// Draws rainbow
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 8; j++) {
			if(phase == 1)
				drawLine(pixels, (int)rainbowXBeg, 270+(j+(i*10)), 800, 330+(j+(i*10)), red);
			else if(phase == 2)
				drawLine(pixels, (int)rainbowXBeg, 270+(j+(i*10)), 800, 330+(j+(i*10)), orange);
			else if(phase == 3)
				drawLine(pixels, (int)rainbowXBeg, 270+(j+(i*10)), 800, 330+(j+(i*10)), yellow);
			else if(phase == 4)
				drawLine(pixels, (int)rainbowXBeg, 270+(j+(i*10)), 800, 330+(j+(i*10)), green);
			else if(phase == 5)
				drawLine(pixels, (int)rainbowXBeg, 270+(j+(i*10)), 800, 330+(j+(i*10)), cyan);
			else
				drawLine(pixels, (int)rainbowXBeg, 270+(j+(i*10)), 800, 330+(j+(i*10)), purple);
			rainbowXBeg += rate;
		}
		phase++;
	}
	double whiteXBeg = 340;
	// Draws white left part
	for(int i = 0; i < 10; i++) {
		drawLine(pixels, (int)whiteXBeg, 300+i, 0, 370+i, white);
		whiteXBeg -= rate;
	}

	// Draws two triangles
	drawTriangle(pixels, 400, 200, 230, 200, white);
	drawTriangle(pixels, 400, 220, 195, 170, x);

	// Makes three circles
	drawCircle(pixels, 400, 185, 15, blue);
	drawCircle(pixels, 265, 405, 15, red);
	drawCircle(pixels, 535, 405, 15, yellow);

	// Blurs the image
	blur(pixels);
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
			//Bounds test, to make sure we don't access array out of bounds
			if(y<0 || x<0 || x>=kAppWidth || y>=kAppHeight) 
				continue;
			int dist = (int)sqrt((double)((x-xCoord)*(x-xCoord) + (y-yCoord)*(y-yCoord)));
			if(dist <= radius) {
				int a = 3*(x + y*kAppWidth);
				pixels[a] = color.r;
				pixels[a+1] = color.g;
				pixels[a+2] = color.b;
			}
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
	double rate = .60;
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

/**
 *  Applies a blur to the image
 *
 *  @param pixels The array of pixels that we will be applying the blur to
 **/
void CatPictureApp::blur(uint8_t* pixels) {
	int r, g, b;
    for(int y = 1; y < kAppHeight-1; y++){
        for(int x = 1; x < kAppWidth-1; x++){
            r = 0;
            g = 0;
            b = 0;
			// Adds up the values for each r, g, and b value
            for(int yAvg = -1; yAvg <= 1; yAvg++){
                for(int xAvg = -1; xAvg <= 1; xAvg++){
					int a = 3*((x+xAvg) + (y+yAvg)*kAppWidth);
                    r = r+pixels[a];
                    g = g+pixels[a+1];
                    b = b+pixels[a+2];
                }
            }
			// Applies the average values to these pixels
			int a = 3*(x + y*kAppWidth);
			pixels[a] = (int)(r/9.0);
			pixels[a+1] = (int)(g/9.0);
			pixels[a+2] = (int)(b/9.0);
        }
    }
}

void CatPictureApp::draw() {
	// Draws our surface onto the screen
	gl::draw(*mySurface); 
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )

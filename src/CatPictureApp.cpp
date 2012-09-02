#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CatPictureApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
  private:
	float red, green, blue;
	int phase;
};

void CatPictureApp::setup()
{
	red = 1.0f;
	green = 0.0f;
	blue = 0.0f;
	phase = 1;
}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update()
{
	// Phase 1 - Fade from red to orange
	if(phase == 1) {
		if(green < 0.27f) {
			green = green + 0.002f;
		}
		else {
			phase = 2;
		}
	}
	// Phase 2 - Fade from orange to yellow
	else if(phase == 2) {
		if(green < 1.0f) {
			green = green + 0.006f;
		}
		else {
			phase = 3;
		}
	}
	// Phase 3 - Fade from yellow to green
	else if(phase == 3) {
		if(red > 0.0f) {
			red = red - 0.01f;
		}
		else {
			phase = 4;
		}
	}
	// Phase 4 - Fade from green to cyan
	else if(phase == 4) {
		if(blue < 1.0f) {
			blue = blue + 0.01f;
		}
		else {
			phase = 5;
		}
	}
	// Phase 5 - Fade from cyan to blue
	else if(phase == 5) {
		if(green > 0.0f) {
			green = green - 0.01f;
		}
		else {
			phase = 6;
		}
	}
	// Phase 6 - Fade from blue to purple
	else if(phase == 6) {
		if(blue > 0.5f) {
			blue = blue - 0.005f;
			red = red + 0.005f;
		}
		else {
			phase = 7;
		}
	}
	// Phase 7 - Fade from purple to pink
	else if(phase == 7) {
		if(red < 1.0f) {
			red = red + 0.005f;
			blue = blue + 0.005f;
		}
		else {
			phase = 8;
		}
	}
	// Phase 8 - Fade from pink to red
	else {
		if(blue > 0.0f) {
			blue = blue - 0.01f;
		}
		else {
			phase = 1;
		}
	}
}

void CatPictureApp::draw()
{
	// Colors the screen with set values of red, green and blue
	gl::clear( Color( red, green, blue ) ); 
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )

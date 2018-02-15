#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class hellocinderApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void hellocinderApp::setup()
{
	setWindowSize({ 900,600 });
}

void hellocinderApp::mouseDown( MouseEvent event )
{
}

void hellocinderApp::update()
{
}

void hellocinderApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
	vec2 center = getWindowCenter();
	
	gl::pushModelMatrix();
	gl::translate(center);

	int numCircles = 32;
	float radius = getWindowHeight() / 2 - 30;

	for (int c = 0; c < numCircles; c++) {
		float rel = c / (float)numCircles;
		float angle = rel * M_PI * 2;
		vec2 offset(cos(angle), sin(angle));

		gl::pushModelMatrix();
		gl::translate(offset * radius);
		gl::scale(8, 0.25f);
		gl::rotate(angle);

		gl::color(Color(CM_HSV, rel, 1, 1));
		gl::drawSolidCircle(vec2(), 20);
		gl::popModelMatrix();
	}
	gl::color(Color(1, 1, 1));
	gl::drawSolidCircle(vec2(), 15);
	gl::popModelMatrix();

}

CINDER_APP( hellocinderApp, RendererGl )

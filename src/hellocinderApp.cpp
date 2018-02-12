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
}

CINDER_APP( hellocinderApp, RendererGl )

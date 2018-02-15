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

void testTransform() {
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

void test3D() {
	gl::enableDepthRead();
	gl::enableDepthWrite();

	CameraPersp cam;
	cam.lookAt(vec3(3, 4.5, 4.5), vec3(0, 1, 0));
	gl::setMatrices(cam);

	auto lambert = gl::ShaderDef().lambert().color();
	auto shader = gl::getStockShader(lambert);
	shader->bind();

	int numSpheres = 64;
	float maxAngle = M_PI * 7;
	float spiralRadius = 1;
	float height = 2;
	float anum = getElapsedFrames() / 30.0f;

	for (int s = 0; s < numSpheres; s++) {
		float rel = s / (float)numSpheres;
		float angle = rel * maxAngle;
		float y = fabs(cos(rel * M_PI + anum)) * height;
		float r = rel * spiralRadius;
		vec3 offset(r * cos(angle), y / 2, r * sin(angle));

		gl::pushModelMatrix();
		gl::translate(offset);
		gl::scale(vec3(0.05f, y, 0.05f));
		gl::color(Color(CM_HSV, rel, 1, 1));
		gl::drawCube(vec3(), vec3(1));
		gl::popModelMatrix();
		//console() << gl::getProjectionMatrix() << std::endl;
	}
}

void hellocinderApp::draw()
{
	gl::clear();
	//testTransform();
	test3D();
	

}

CINDER_APP( hellocinderApp, RendererGl )

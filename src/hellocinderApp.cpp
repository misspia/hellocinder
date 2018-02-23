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

	void batches();
	void texShaderWheel();

	CameraPersp mCam;
	gl::BatchRef mBox;
	gl::BatchRef mRect;
	gl::GlslProgRef mGlsl;

};

void hellocinderApp::setup()
{
	setWindowSize({ 900,600 });
	
	// Batches
	//auto lambert = gl::ShaderDef().lambert().color();
	//gl::GlslProgRef shader = gl::getStockShader(lambert);
	//mBox = gl::Batch::create(geom::Cube(), shader);
	//mCam.lookAt(vec3(3.0, 4.5, 4.5), vec3(0.0, 1.0, 0.0));
	
	// texShaderWheel
	//auto img = loadImage(loadAsset("texture.jpg"));
	mCam.lookAt(vec3(3, 2, 3), vec3(0));

	mGlsl = gl::GlslProg::create(gl::GlslProg::Format()
		.vertex(CI_GLSL(150,
			uniform mat4	ciModelViewProjection;
			in vec4			ciPosition;

			void main(void) {
				gl_Position = ciModelViewProjection * ciPosition;
			}
		))
		.fragment(CI_GLSL(150,
			uniform vec4	uColor;
			out vec4		oColor;

			void main(void) {
				oColor = uColor;
			}
		)));
		
	mRect = gl::Batch::create(geom::Plane(), mGlsl);

	gl::enableDepthWrite;
	gl::enableDepthRead;
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

void hellocinderApp::batches() {
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::setMatrices(mCam);

	int numSpheres = 64;
	float maxAngle = M_PI * 7.0;
	float spiralRadius = 1.0;
	float height = 2.0;
	float boxSize = 0.05f;
	float anim = getElapsedFrames() / 30.0f;

	for (int s = 0; s < numSpheres; s++) {
		float rel = s / (float)numSpheres;
		float angle = rel * maxAngle;
		float y = fabs(cos(rel * M_PI + anim)) * height;
		float r = rel * spiralRadius;
		vec3 offset(r * cos(angle), y / 2, r *sin(angle));

		gl::pushModelMatrix();
		gl::translate(offset);
		gl::scale(vec3(boxSize, y, boxSize));
		gl::color(Color(CM_HSV, rel, 1, 1));
		mBox->draw();
		gl::popModelMatrix();
	}
}

void hellocinderApp::texShaderWheel() {
	gl::clear(Color(0.2f, 0.2f, 0.2f));
	gl::setMatrices(mCam);

	const int NUM_PLANES = 30;
	for (int p = 0; p < NUM_PLANES; p++) {
		float hue = p / (float)NUM_PLANES;
		ColorAf color(CM_HSV, hue, 1, 1, 1);
		mGlsl->uniform("uColor", color);

		gl::ScopedModelMatrix scpMtx;
		float angle = M_PI * p / (float)NUM_PLANES;
		gl::rotate(angleAxis(angle, vec3(1, 0, 0)));
		mRect->draw();
	}
}


void hellocinderApp::draw()
{
	gl::clear();
	
	//testTransform();
	//test3D();
	//batches();
	texShaderWheel();


	
}

CINDER_APP( hellocinderApp, RendererGl )

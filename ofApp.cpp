#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();
	ofSetLineWidth(1);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 50, true, true, true);
	this->word = "0123456789";
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofRotateY(ofGetFrameNum() * 1.44);

	ofSeedRandom(39);
	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	for (int z = -150; z < 150; z += 3) {

		auto base_location = glm::vec3(-25, 25, z);

		ofPushMatrix();
		ofTranslate(base_location);
		ofRotateZ(ofMap(ofNoise(noise_seed.x, z * 0.004 + ofGetFrameNum() * 0.005), 0, 1, -180, 180));
		ofRotateY(ofMap(ofNoise(noise_seed.y, z * 0.004 + ofGetFrameNum() * 0.005), 0, 1, -180, 180));
		ofRotateX(ofMap(ofNoise(noise_seed.z, z * 0.004 + ofGetFrameNum() * 0.005), 0, 1, -180, 180));

		ofPath chara_path = this->font.getCharacterAsPoints(this->word[0], true, false);
		vector<ofPolyline> outline = chara_path.getOutline();

		ofFill();
		ofSetColor(0);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			ofNextContour(true);

			auto vertices = outline[outline_index].getResampledByCount(100).getVertices();
			for (auto& vertex : vertices) {

				ofVertex(vertex);
			}
		}
		ofEndShape(true);

		ofNoFill();
		ofSetColor(255);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			ofNextContour(true);

			auto vertices = outline[outline_index].getResampledByCount(100).getVertices();
			for (auto& vertex : vertices) {

				ofVertex(vertex);
			}
		}
		ofEndShape(true);

		ofPopMatrix();
	}

	this->cam.end();

	/*
	int start = 300;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
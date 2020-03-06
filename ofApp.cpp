#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	this->number_of_vertices = 400;

	for (int i = 0; i < this->number_of_vertices - 3; i += 4) {

		this->face.addIndex(i + 0); this->face.addIndex(i + 1); this->face.addIndex(i + 2);
		this->face.addIndex(i + 0); this->face.addIndex(i + 2); this->face.addIndex(i + 3);

		this->frame.addIndex(i + 0); this->frame.addIndex(i + 1);
		this->frame.addIndex(i + 0); this->frame.addIndex(i + 3);
		this->frame.addIndex(i + 2); this->frame.addIndex(i + 1);
		this->frame.addIndex(i + 2); this->frame.addIndex(i + 3);
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	
	int len = 200;
	vector<glm::vec3> vertices;
	int param = ofRandom(100);
	if (ofRandom(1) < 0.5) {

		vertices.push_back(glm::vec3(this->make_point(len, param), len * 0.5));
		vertices.push_back(glm::vec3(this->make_point(len, param + 2), len * 0.5));
		vertices.push_back(glm::vec3(this->make_point(len, 100 - param - 2), len * 0.5));
		vertices.push_back(glm::vec3(this->make_point(len, 100 - param), len * 0.5));
	}
	else {

		vertices.push_back(glm::vec3(this->make_point(len, param), len * 0.5));
		vertices.push_back(glm::vec3(this->make_point(len, param + 2), len * 0.5));
		vertices.push_back(glm::vec3(this->make_point(len, 150 - param - 2), len * 0.5));
		vertices.push_back(glm::vec3(this->make_point(len, 150 - param), len * 0.5));
	}

	int r = (int)ofRandom(6);

	if (r < 4) {
	
		auto angle_y = r * 90;
		auto rotation_y = glm::rotate(glm::mat4(), (float)(angle_y * DEG_TO_RAD), glm::vec3(0, 1, 0));

		for (auto& vertex : vertices) {

			vertex = glm::vec4(vertex, 0) * rotation_y;
		}
	}
	else {

		auto angle_x = r == 5 ? 90 : 270;
		auto rotation_x = glm::rotate(glm::mat4(), (float)(angle_x * DEG_TO_RAD), glm::vec3(1, 0, 0));

		for (auto& vertex : vertices) {

			vertex = glm::vec4(vertex, 0) * rotation_x;
		}
	}

	auto index = this->face.getNumVertices();
	this->face.addVertices(vertices);
	this->frame.addVertices(vertices);

	while (this->face.getNumVertices() > this->number_of_vertices) {

		this->face.removeVertex(0);
		this->face.removeVertex(0);
		this->face.removeVertex(0);
		this->face.removeVertex(0);	

		this->frame.removeVertex(0);
		this->frame.removeVertex(0);
		this->frame.removeVertex(0);
		this->frame.removeVertex(0);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.85);
	ofRotateX(ofGetFrameNum() * 0.5);

	ofSetColor(39);
	this->face.draw();

	ofSetColor(239);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = (param + 100) % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
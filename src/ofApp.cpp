#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255, 255, 255);
	ofSetVerticalSync(true);
	ofSetFrameRate(40);
	ofSetWindowShape(800, 800);
    //ofSetWindowPosition(10, 10);
	gui.setup();
	gui.add(radius.setup("radius", 106.95, 3, 300));
	gui.add(spring_k.setup("K", 8.4, 0.001, 10));
	gui.add(spring_relaxed_length.setup("Spring Length", 0.0145, 0.01, 0.1));
	gui.add(drag.setup("Drag", 0.0006, 0.0001, 1));
	int num = 20;
	vector<blobParticle> p;
	p.assign(num, blobParticle());
	blobs.push_back(p);
	glEnable(GL_POINT_SMOOTH);
	resetBlobs();
}

//--------------------------------------------------------------
void ofApp::resetParticles(vector<blobParticle> &p){
	for(int i = 0; i < p.size(); i++){
		p[i].reset(radius, spring_k, spring_relaxed_length, drag, i, p.size());
	}	
	for(int i = 0; i < p.size(); i++){ 
		if (i != 0 && i != (p.size()-1)){ 
			p[i].particle_left = &(p[i-1]); 
			p[i].particle_right = &(p[i+1]);
		}
		else{
			if (i == 0){
				p[i].particle_left = &(p[p.size()-1]); 
				p[i].particle_right = &(p[1]); 
			}
			else{
				p[i].particle_left = &(p[i-1]); 
				p[i].particle_right = &(p[0]); 
			}
		}
	}	
}

//--------------------------------------------------------------
void ofApp::resetBlobs(){
	for (auto& blob: blobs){
		resetParticles(blob);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	std::stringstream strm;
	strm << "fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());
	for (auto& blob: blobs){
		updateBlob(blob);
	}
}

//--------------------------------------------------------------
void ofApp::updateBlob(vector<blobParticle> &p){
	for(int i=0; i<p.size(); i++){
		for(int j= i+1; j<p.size(); j++){
			p[i].addRepulsionForce(p[j]);
		}
	}
	for(int i=0; i<p.size(); i++){
		p[i].addSpringForce();
	}
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].update();
	}
}


//--------------------------------------------------------------
void ofApp::draw(){
	//ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));
	for (auto& blob: blobs){
		drawBlob(blob);
	}
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::drawBlob(const vector<blobParticle> &p){
	ofPolyline blob;
	blob.curveTo(p[p.size()-1].pos.x, p[p.size()-1].pos.y);
	for(unsigned int i = 0; i < p.size(); i++){
		blob.curveTo(p[i].pos.x, p[i].pos.y);
		//p[i].draw();
	}
	blob.curveTo(p[0].pos.x, p[0].pos.y);
	ofSetColor(169,252,201,200);
	ofBeginShape();
	for( int i = 0; i < blob.getVertices().size(); i++) {
		ofVertex(blob.getVertices().at(i).x, blob.getVertices().at(i).y);
	}
	ofEndShape();
	blob.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if( key == ' ' ){
		resetBlobs();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

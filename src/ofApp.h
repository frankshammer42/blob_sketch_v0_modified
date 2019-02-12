#include "ofMain.h"
#include "blobParticle.hpp"
#include "ofxGui.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		
		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


		//Helper functions
		void resetBlobs();
		void resetParticles(vector<blobParticle> &p);
		void updateBlob(vector<blobParticle> &p);
		void drawBlob(const vector<blobParticle> &p);
		
		//TODO: make a struct to store all the parameters 
		vector<vector <blobParticle>> blobs;
		
		ofxPanel gui;
		ofxFloatSlider radius; 
		ofxFloatSlider spring_k;
		ofxFloatSlider spring_relaxed_length;
		ofxFloatSlider drag;
};

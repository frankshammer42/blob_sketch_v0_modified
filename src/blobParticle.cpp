#include "blobParticle.hpp"

blobParticle::blobParticle(){
}


void blobParticle::reset(float particle_radius, float particle_spring_k, float particle_spring_relaxed_length, float particle_drag, int particle_id, int total_size){
	calculate_pos(id, total_size);
	vel.x = ofRandom(-3.9, 3.9);
	vel.y = ofRandom(-3.9, 3.9);
	frc   = ofPoint(0,0,0);
	scale = ofRandom(0.5, 1.0);
	drag  = ofRandom(0.6, 0.9); //slow down the moving speed 
	radius = particle_radius; spring_k = particle_spring_relaxed_length;
	spring_relaxed_length = particle_spring_relaxed_length;
	drag = particle_drag;
	id = particle_id;
}


void blobParticle::calculate_pos(int id, int total_size){
	float fraction = float(id)/float(total_size);  
	float fraction_degree = 360.0 * fraction;
	float fraction_radiant = ofDegToRad(fraction_degree); 
	float cx = 400; 
	float cy = 400; 
	float r = 100;
	pos.x = cx + r * cos(fraction_radiant);
	pos.y = cy + r * sin(fraction_radiant);
}


void blobParticle::addRepulsionForce(blobParticle &anotherParticle){
    ofVec2f posOfForce;
    posOfForce.set(anotherParticle.pos.x, anotherParticle.pos.y);
	//This seems too lazy, not good for understanding
	//Diff also plays the role for understanding direction
    ofVec2f diff    = -(posOfForce - pos); //Since it is repulsion force
    float length    = diff.length();

    bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }

    if (bAmCloseEnough == true){
        float pct = 1 - (length / radius);  // stronger on the inside
        diff.normalize();
        frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
        anotherParticle.frc.x = anotherParticle.frc.x - diff.x * scale * pct; //reaction force is applied to the opposite direction
        anotherParticle.frc.y = anotherParticle.frc.y - diff.y * scale * pct;
    }
}


void blobParticle::addSpringForce(){
	ofVec2f left_particle_pos;
	ofVec2f right_particle_pos;
	left_particle_pos.set(particle_left->pos.x, particle_left->pos.y);
	right_particle_pos.set(particle_right->pos.x, particle_right->pos.y);
	ofVec2f left_diff = left_particle_pos - pos;    
	ofVec2f right_diff = right_particle_pos - pos;
	float left_length = left_diff.length();
	float right_length = right_diff.length();
	float left_deformation = spring_relaxed_length - left_length;
	float right_deformation = spring_relaxed_length - right_length;
	int left_dir = 1;
	int right_dir = 1;
	//Calculate left force
	if (left_deformation > 0){
		left_dir = -1;
	}
	float left_spring_force = spring_k * abs(left_deformation);
	ofVec2f left_diff_with_dir = left_dir * left_diff;
	left_diff_with_dir.normalize();
	frc.x = frc.x + left_diff_with_dir.x*left_spring_force; 
	frc.y = frc.y + left_diff_with_dir.y*left_spring_force; 
	//Calculate right force
	if (right_deformation > 0){
		right_dir = -1;
	}
	float right_spring_force = spring_k * abs(right_deformation);
	ofVec2f right_diff_with_dir = right_dir * right_diff;
	right_diff_with_dir.normalize();
	frc.x = frc.x + right_diff_with_dir.x*right_spring_force; 
	frc.y = frc.y + right_diff_with_dir.y*right_spring_force; 
}



//Make sure all the particles stay on the screen 
void blobParticle::inbound_check(){
	if( pos.x > ofGetWidth() ){
		pos.x = ofGetWidth();
		vel.x *= -5.0;
	}else if( pos.x < 0 ){
		pos.x = 0;
		vel.x *= -5.0;
	}
	if( pos.y > ofGetHeight() ){
		pos.y = ofGetHeight();
		vel.y *= -5.0;
	}
	else if( pos.y < 0 ){
		pos.y = 0;
		vel.y *= -5.0;
	}	
}


//------------------------------------------------------------------
void blobParticle::update(){
	vel *= drag; // Make the particles move slower 
	vel += frc;  
	pos += vel; 
	inbound_check();
}

//------------------------------------------------------------------
void blobParticle::draw(){
	ofSetColor(85, 70, 185);
	ofDrawCircle(pos.x, pos.y, scale * 4.0);
	//ofDrawCircle(pos.x, pos.y, 10);
}


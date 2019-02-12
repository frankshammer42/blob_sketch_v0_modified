//
//  blobParticle.hpp
//  blob_sketch_2
//
//  Created by Frankshammer42 on 2/12/19.
//

#ifndef blobParticle_hpp
#define blobParticle_hpp

#include <stdio.h>
#include "ofMain.h"

#endif /* blobParticle_hpp */

// In the particle system, the mass is equal to 1 and the time between update is presumed to be 1 
class blobParticle{

	public:
		blobParticle();
		void reset(float particle_radius, float particle_spring_k, float particle_spring_relaxed_length, float particle_drag, int particle_id, int total_size);
		void calculate_pos(int id, int total_size);
		void update();
		void draw();		
		void addRepulsionForce(blobParticle &anotherParticle);
		void addSpringForce();
		void inbound_check();
		
		ofPoint pos;
		ofPoint vel;
		ofPoint frc;
		
		int id; //for connecting springs
		float drag; 
		float scale; //control the size -> control the force
		float radius;
		float spring_k; //control the k in hook's law
		float spring_relaxed_length; //control the X in hook's law

		blobParticle* particle_left; // for springs 
		blobParticle* particle_right; // for springs


		
};


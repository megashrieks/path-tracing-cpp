#include<iostream>
#include <cstdlib>
#include <time.h>
#include<vector>
#include "transform3d.h"
#include "vec3.h"
#include "raytrace.h"
#include "primitiveshapes.h"
#include "bmp.h"

#define PI 3.1412857

using namespace std;

void createscene(scene &s){
	static material tm(5,MTYPE::DIFFUSE, vec3(.2,.2,1));
	static material tl(0.3,MTYPE::SPECULAR, vec3(0.5,0.5,1));
	static material tl1(0,MTYPE::SPECULAR, vec3(1));
	static material pleftmat(5,MTYPE::DIFFUSE, vec3(1,0,0)),
	prightmat(5,MTYPE::DIFFUSE, vec3(0,1,0)),
	ptopmat(5,MTYPE::DIFFUSE, vec3(1)),
	pbottommat(5,MTYPE::DIFFUSE, vec3(1)),
	pfrontmat(5,MTYPE::DIFFUSE, vec3(1,1,1)),
	pboxmat(2,MTYPE::LIGHT, vec3(1,1,1));
	static primitivesphere ps1(
		vec3(-.2,-.5,2),
		0.5,
		tm
	);
	static primitivesphere ps2(
		vec3(0.3,-.7,1),
		.3,
		tl
	);
	static primitivebox pbox1(
		vec3(0,1,1),
		vec3(.4,.05,.4),
		pboxmat
	);
	static primitivebox pbox2(
		vec3(-.35,-.7,1),
		vec3(.2,.2,.2),
		tl1
	);
	float offset = 1.0;
	static primitiveplane plane1(
		vec3(1,0,0),
		offset,
		pleftmat
	), plane2(
		vec3(-1,0,0),
		offset,
		prightmat
	), plane3(
		vec3(0,-1,0),
		1,
		ptopmat
	), plane4(
		vec3(0,1,0),
		1,
		pbottommat
	), plane5(
		vec3(0,0,-1),
		3,
		pfrontmat
	),plane6(
		vec3(0,0,1),
		1,
		pfrontmat
	);
	static transform3d t1(&pbox2);
	t1.rotate('y',PI/4.0);
	t1.rotate('x',PI/4.0);
	s.addobject(ps1);
	s.addobject(plane1);
	s.addobject(plane2);
	s.addobject(plane3);
	s.addobject(plane4);
	s.addobject(plane5);
	s.addobject(plane6);
	s.addobject(ps2);
	s.addobject(pbox1);
	s.addobject(t1);
}
int main() {
	srand(time(0));
	//16k
	// const int width = 15360, height = 8640;
	const int width = 700, height = 700;
	// const int width = 1024, height = 768;
	// const int width = 3840, height = 2160;
	// const int width = 256, height = 256;
	scene s;
	createscene(s);
	raytrace rt(width, height, s);

	while(rt.iteration < 10000){
		cout<<"in iteration : "<<rt.iteration<<"\n";
		rt.render();
		bmp b = bmp(width,height);
		for(int i = 0;i < height;++i){
			for(int j = 0;j < width;++j){
				b.set_pixel(
					j,i,
					std::min(rt.image[i][j].x/rt.iteration,1.0f)*255,
					std::min(rt.image[i][j].y/rt.iteration,1.0f)*255,
					std::min(rt.image[i][j].z/rt.iteration,1.0f)*255
				);
			}
		}
		// cout<<b->bytes_per_pixel<<endl;
		b.write_to_file("raytrace.bmp");
	}
	return 0;

}

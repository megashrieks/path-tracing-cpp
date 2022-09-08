#include <vector>
#include <thread>
#include <iostream>
#include "raytrace.h"
#include "scene.h"
#include "utils.h"
#define PI 3.1412857
#define MAX_DIST 100.0

raytrace::raytrace(int w, int h): width(w), height(h){
    image = std::vector<std::vector<vec3>>(height, std::vector<vec3>(width));
    iteration = 0;
}

raytrace::raytrace(int w, int h, scene &wo): width(w), height(h){
    image = std::vector<std::vector<vec3>>(height, std::vector<vec3>(width));
    iteration = 0;
    world = wo;
}

void raytrace::addscene(scene &w){
    world = w;
}

void raytrace::setpixel(int xx, int yy, vec3 &col){
    float x = (float)xx-width * 0.5,
          y = -((float)yy-height * 0.5);
    x /= (float)height;
    y /= (float)height;
    vec3 camera(0,0,-1);
    vec3 ro(x,y, 0.0), rd = std::move((ro-camera).normal());
    //TODO: fix anti aliasing
    // rd += vec3((rand()%100000+1)/100000-.5,(rand()%100000+1)/100000-.5,0)*(1.0/10);
    col += trace(ro, rd);
}
vec3 raytrace::lightray(vec3 &pos,vec3 &normal){
    vec3 col(0);
    for(shape* s: world.lights){
        vec3 lpos = s->getpos();
        // vec3 dir = (lpos-pos).normal();
        vec3 dir = (lpos-pos+hemrandom()*0.3).normal();
        float d = 0.0;
        vec3 p = pos;
        while(d < MAX_DIST){
            p += dir*d;
            int objid = -1;
            d = world.intersect(p,objid);
            if(d < EP){
                if(world.objects[objid]->shapematerial.type == MTYPE::LIGHT) 
                col += world.objects[objid]->shapematerial.color*dot(normal,dir);
                break;
            }
        }
    }
    return min(col,vec3(1));
}
void raytrace::render(){
    const int cores = 8;
    srand(time(NULL));
    ++iteration;
    std::thread ts[cores];
    auto cf = [&](int i, int j){
        setpixel(j,i,image[i][j]);
    };
    for(int i = 0;i < height;++i){
        for(int j = 0;j < width;j+=cores){
            for(int k = 0;k < cores;++k)
                if(j+k < width)
                    ts[k] = std::thread(cf,i,j+k);
                else break;
            for(int k = 0;k < cores;++k)
                if(j+k < width)
                    ts[k].join();
                else break;
        }
    }
}
vec3 raytrace::trace(vec3 &ro, vec3 &rd) {
    float d = 0;
    vec3 color(1);
    vec3 directlight(0);
    int objid = -1;
    float totaldist = 0;
    int count = 0;
    for(int i = 0;i < 100;++i){
        ro += rd*d;
        d = world.intersect(ro, objid);
        totaldist += d;
        if(d < EP){
            material m = world.objects[objid]->shapematerial;
            if(m.type == MTYPE::LIGHT) return color*m.color*vec3(m.roughness)+directlight*(1.0f/2.0);
            ro -= rd*EP;
            vec3 onormal = world.objects[objid]->getnormal(ro);
            if(m.type == MTYPE::DIFFUSE){
                rd = uhr(onormal);
                vec3 dl = lightray(ro,onormal);
                ro += rd*EP;
                color = 
                    color*m.color * (1.0f/PI) *
                    PI * 2 * dot(onormal,rd)
                ;
                // return dl*m.color;
                directlight = directlight+(dl*m.color*(2.0f/PI))*(1.0f/(1<<(count++)));
            }else if(m.type == MTYPE::SPECULAR){
                rd = reflect(rd, onormal);
                ro += rd*EP;
                if(m.roughness > 0){
                    vec3 trd = hemrandom()*m.roughness;
                    rd = (rd + trd).normal();
                }
            }
        }
    }
    if(totaldist > MAX_DIST) return color;
    return directlight*(1.0f/2.0);
}


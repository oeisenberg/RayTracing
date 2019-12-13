#pragma once

#include <random>
#include <algorithm>
#include "tracer.h"
#include "photonmap.h"

class RayTracer : public Tracer {
public:
	RayTracer()
	{
	}

    Vector getLightDir(std::vector<Light*> lights, int iLight, Hit hitObj){
        Vector lightDir;
        try{
            lightDir = lights[iLight]->getDirection();
        } catch(const std::exception e){
            lightDir = lights[iLight]->getDirection(hitObj.position);
        }
        return lightDir;
    }

    bool checkForShadow(Hit closest, std::vector<Object*> objs, Ray ray, Light* light){
        Hit new_t = Hit();
        float light_distance = light->getDistance(closest.position);
        for (int i = 0; i < objs.size(); i++) {
            objs[i]->intersection(ray, new_t);

            if (new_t.flag && ((light_distance-new_t.t) >= 0)) return true;
        }
        return false;
    }

    Colour specularReflect(Scene &scene, Camera &camera, Hit closest, Ray lRay, float depth, PhotonMap &gPm, PhotonMap &cPm){
        Vector r;
        closest.normal.reflection(lRay.direction, r);
        r.normalise();
        Ray reflectionRay = Ray("indirect", closest.position + r.multiply(0.001f), r);
        return raytrace(scene, camera, reflectionRay, depth-1, gPm, cPm) * closest.what->objMaterial->reflectionDegree;
    }

    Colour diffuseReflect(Scene &scene, Camera &camera, Hit closest, Ray lRay, float depth, PhotonMap &gPm, PhotonMap &cPm){
        Vector r;
        closest.normal.diffreflection(lRay.direction, r);
        r.normalise();
        Ray reflectionRay = Ray("diffReflection", closest.position + r.multiply(0.001f), r);

        Hit newhit = Hit();
        newhit.t = std::numeric_limits<int>::max();
        newhit = checkForIntersection(reflectionRay, newhit.t, newhit, scene.objects);
        
        float diff = newhit.normal.dot(reflectionRay.direction);
        // Colour colour = gPm.calcRadiance(closest, camera.e, diff); 
        // Colour colour = closest.what->objMaterial->compute_light_colour(newhit.normal, camera.e - closest.position, reflectionRay.direction, diff);
        Colour colour;
        colour += sample(scene, newhit, gPm, camera) * newhit.what->objMaterial->diffuse.getStrength();
        return colour;
    }

    Colour refract(Scene& scene, Camera &camera, Hit closest, Ray lRay, float depth, PhotonMap &gPm, PhotonMap &cPm){
        Vector refraction, R, G, B;
        lRay.direction.normalise();
        Vector bias = closest.normal.multiply(0.001f);
        bool outside = lRay.direction.dot(closest.normal) < 0;

        closest.normal.refraction(lRay.direction, closest.what->objMaterial->ior, refraction);
        refraction.normalise();

        Vertex origin = outside ? closest.position - bias  : closest.position + bias;
        Ray transparentRay = Ray("indirect", origin, refraction);

        return raytrace(scene, camera, transparentRay, depth-1, gPm, cPm) * closest.what->objMaterial->transparentDegree;
    }

    Colour sample(Scene &scene, Hit closest, PhotonMap &gPm, Camera &camera){
        std::vector<Photon> photons = gPm.getNSurroundingPoints(closest.position);
<<<<<<< Updated upstream
        int subsample = 500;
=======
        int subsample = 10;
>>>>>>> Stashed changes
        std::random_shuffle(photons.begin(), photons.end());

        Colour total = Colour();
        int iPhoton = 0; int nSamples = 0;
         while (nSamples < subsample && iPhoton < photons.size()){
            if (photons[iPhoton].type != "direct"){
                // get photon incoming dir
                photons[iPhoton].direction.negate();
                photons[iPhoton].position = closest.position;
                photons[iPhoton].power = Colour();
                
                Hit hit = Hit();
                hit.t = std::numeric_limits<int>::max();
                hit = checkForIntersection(photons[iPhoton], hit.t, hit, scene.objects);
                if (hit.t != std::numeric_limits<int>::max()){
                    float diff = hit.normal.dot(photons[iPhoton].direction);
                    total += gPm.calcRadiance(hit, camera.e, diff);
                }
                nSamples++;
            }
            iPhoton++;
        }
        return total / nSamples;
    }

    Colour raytrace(Scene &scene, Camera &camera, Ray lRay, int depth, PhotonMap &gPm, PhotonMap &cPm){
        Colour colour = Colour();

        Hit closest = Hit();
        closest.t = std::numeric_limits<int>::max();
        closest = checkForIntersection(lRay, closest.t, closest, scene.objects);

        if (closest.t != std::numeric_limits<int>::max()){
            if (depth == 0) return colour;

            Vector SurfaceNormal = closest.normal;
            for (float iLight = 0; iLight < scene.lights.size(); iLight++){
                Vector lightDir = getLightDir(scene.lights, iLight, closest);
                lightDir.negate();
                float diff = SurfaceNormal.dot(lightDir);
                if (diff > 0.0f){
                    Ray shadowRay = Ray("shadow", closest.position + lightDir.multiply(0.0001f), lightDir);
                    if(!checkForShadow(closest, scene.objects, shadowRay, scene.lights[iLight])){
                        if (depth == 4){
                            Colour scale = scene.lights[iLight]->getIntensity();
                            Colour intensity = closest.what->objMaterial->compute_light_colour(SurfaceNormal, camera.e - closest.position, lightDir, diff);
                            colour += intensity * scale * 0.7;
                        } else {
                            colour += gPm.calcRadiance(closest, camera.e, diff) * 200; 
                        }
                    } else {
                        colour += cPm.calcRadiance(closest, camera.e, diff) / 15;
                    }
                }
            }

            if(closest.what->objMaterial->isReflective && closest.what->objMaterial->isTransparent){
                Colour refractionColour = Colour();
                float kr = fresnel(lRay.direction, closest.normal, closest.what->objMaterial->ior);
                if (kr < 1) {
                    refractionColour += refract(scene, camera, closest, lRay, depth, gPm, cPm);
                }
                Colour reflectionColour = specularReflect(scene, camera, closest, lRay, depth, gPm, cPm);
                colour += (reflectionColour * kr + refractionColour * (1 - kr));
            } else {
                if(closest.what->objMaterial->isReflective){
                    colour += specularReflect(scene, camera, closest, lRay, depth, gPm, cPm);
                }
            }
            colour +=diffuseReflect(scene, camera, closest, lRay, depth, gPm, cPm) * 200;
        }
        return colour;
    }
    

};

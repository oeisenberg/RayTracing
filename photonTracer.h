#pragma once

#include "tracer.h"

class PhotonTracer : public Tracer {
public:
    PhotonTracer()
	{

	}

    Colour reflect(Scene &scene, Camera &camera, std::vector<Photon> &photonHitsMap, Hit closest, Photon pRay, float probability, Colour coeff){
        Vector r;
        closest.normal.reflection(pRay.direction, r);
        r.normalise();
        pRay.calcTransmissivePower(probability, coeff);
        Photon photonRay = Photon(pRay.type, closest.position + r.multiply(0.001f), r, pRay.power);
        return photontrace(scene, camera, photonRay, photonHitsMap) * closest.what->objMaterial->reflectionDegree; 
    }

    Colour refract(Scene &scene, Camera &camera, std::vector<Photon> &photonHitsMap, Hit closest, Photon pRay, float probability, Colour coeff){
        Vector r;
        Vector bias = closest.normal.multiply(0.001f);
        bool outside = pRay.direction.dot(closest.normal) < 0;
        closest.normal.refraction(pRay.direction, closest.what->objMaterial->ior, r);
        r.normalise();
        pRay.calcTransmissivePower(probability, coeff);
        Vertex origin = outside ? closest.position - bias  : closest.position + bias;
        Photon photonRay = Photon(pRay.type, origin, r, pRay.power);
        return photontrace(scene, camera, photonRay, photonHitsMap) * closest.what->objMaterial->transparentDegree;
    }

    Colour photontrace(Scene &scene, Camera &camera, Photon pRay, std::vector<Photon> &photonHitsMap){
        Colour colour = Colour();

        Hit closest = Hit();
        closest.t = std::numeric_limits<int>::max();
        closest = checkForIntersection(pRay, closest.t, closest, scene.objects);

        if (closest.t != std::numeric_limits<int>::max()){
            colour = closest.what->objMaterial->computeBaseColour();

            float probDiffuse = (pRay.power * closest.what->objMaterial->diffuse).getStrength() / pRay.power.getStrength();
            float probSpecular = (pRay.power * closest.what->objMaterial->specular).getStrength() / pRay.power.getStrength();
            float probTransmission = (pRay.power * closest.what->objMaterial->transparentDegree).getStrength() / pRay.power.getStrength();
            float probAbsorbtion = 1 - (probDiffuse + probSpecular + probTransmission);

            float r = (float) ((rand() % 100) + 1) / 100; // 0.00 to 1.00

            if (0 <= r && r < probDiffuse){
                if (pRay.type != "caustic"){
                    photonHitsMap.push_back(pRay);
                    Vector r;
                    closest.normal.diffreflection(pRay.direction, r);
                    r.normalise();
                    pRay.calcTransmissivePower(probDiffuse, closest.what->objMaterial->diffuse);
                    Photon photonRay = Photon(pRay.type, closest.position + r.multiply(0.001f), r, pRay.power);
                    colour += photontrace(scene, camera, photonRay, photonHitsMap); 
                }
            } else if (probDiffuse <= r && r < probDiffuse+probSpecular){
                Vector r;
                closest.normal.reflection(pRay.direction, r);
                r.normalise();
                pRay.calcTransmissivePower(probSpecular, closest.what->objMaterial->specular);
                Photon photonRay = Photon(pRay.type, closest.position + r.multiply(0.001f), r, pRay.power);
                colour += photontrace(scene, camera, photonRay, photonHitsMap); 
            } else if (probDiffuse+probSpecular <= r && r < probDiffuse+probSpecular+probTransmission) {
                if(closest.what->objMaterial->isReflective && closest.what->objMaterial->isTransparent){
                    Colour refraction = Colour();
                    float kr = fresnel(pRay.direction, closest.normal, closest.what->objMaterial->ior);
                    if (kr < 1) {
                        Colour refraction = refract(scene, camera, photonHitsMap, closest, pRay, probTransmission, closest.what->objMaterial->transparentDegree);
                    }
                    Colour reflection = reflect(scene, camera, photonHitsMap, closest, pRay, probDiffuse, closest.what->objMaterial->reflectionDegree);
                    colour += reflection * kr + refraction * (1 - kr);
                } else {
                    if(closest.what->objMaterial->isReflective){
                        colour += reflect(scene, camera,photonHitsMap, closest, pRay, probDiffuse, closest.what->objMaterial->reflectionDegree);
                    }
                }
            } else if (probDiffuse+probSpecular <= r && r <= 1) {
                photonHitsMap.push_back(pRay);
            }
        }

        return colour;
    }

};

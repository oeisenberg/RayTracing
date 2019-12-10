#pragma once

#include "vector.h"
#include "photon.h"
#include "colour.h"
#include "scene.h"
#include "camera.h"

class Tracer {
public:

    Hit checkForIntersection(Ray ray, float t, Hit closest, std::vector<Object*> objs){
        Hit new_t = Hit();
        for (int i = 0; i < objs.size(); i++) {
            objs[i]->intersection(ray, new_t);
            if (new_t.flag)
            {
            if (new_t.t < t)
            {
                t = new_t.t;
                closest = new_t;
            }
            }
        }
        return closest;
    }

    float fresnel(Vector lRayDir, Vector N, float ior){
        float cosi = N.dot(lRayDir);
        cosi = std::min(1.0f, std::max(cosi, -1.0f));
        float etai = 1, etat = ior;
        if (cosi > 0) { std::swap(etai, etat); }
        // Compute sini using Snell's law
        float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
        // Total internal reflection
        if (sint >= 1) {
            float kr = 1;
            return kr;
        } else {
            float cost = sqrtf(std::max(0.f, 1 - sint * sint));
            cosi = fabsf(cosi);
            float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
            float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
            float kr = (Rs * Rs + Rp * Rp) / 2;
            return kr;
        }
        // As a consequence of the conservation of energy, transmittance is given by:
        // kt = 1 - kr;
    }

};
/***************************************************************************
 *
 * ohe21 - Oliver's Photon Map class
 *
 */

// PhotonMap is a class to wrap method calls to an external library.

#pragma once

#include "ap.h"
#include "alglibmisc.h"
#include <math.h>
#include "photon.h"
#include "vertex.h"
#include "colour.h"
#include "hit.h"

class PhotonMap {
private:
	int nSamples;
	alglib::kdtree tree;

	Colour calcTotalIncomingFlux(Hit hit, Vector toViewer, float diff){
		return getTotalIntensity(getNSurroundingPoints(hit.position), hit, toViewer);
	}

	Colour calcTotalIncomingFlux(Hit hit, Vector toViewer, float diff, std::string filter){
		return getTotalIntensity(getNSurroundingPoints(hit.position, filter), hit, toViewer);
	}
	
	alglib::real_1d_array convertVertex(Vertex point){
		alglib::real_1d_array data;
		data.setlength(3);
		data[0] = point.x;
		data[1] = point.y;
		data[2] = point.z;

		return data;
	}
	alglib::real_2d_array convertPhotonVectorTo2DArr(std::vector<Photon> inputData, alglib::ae_int_t x, alglib::ae_int_t y){
		alglib::real_2d_array data;
		data.setlength(inputData.size(), x+y);
		Photon ph;
		for (int i = 0; i < inputData.size(); i++){
			ph = inputData[i];
			data[i][0] = ph.position.x;
			data[i][1] = ph.position.y;
			data[i][2] = ph.position.z;
			data[i][3] = ph.direction.x;
			data[i][4] = ph.direction.y;
			data[i][5] = ph.direction.z;
			data[i][6] = ph.power.R;
			data[i][7] = ph.power.G;
			data[i][8] = ph.power.B;
			data[i][9] = convertPhotonTypeToDouble(ph.type);
		}

		return data;
	}
	std::vector<Photon> convert2DArrToPhotonVector(alglib::real_2d_array inputData){
		std::vector<Photon> outputData;
		Photon ph;
		for (int i = 0; i < inputData.rows(); i++){
			ph.position.x = inputData[i][0];
			ph.position.y = inputData[i][1];
			ph.position.z = inputData[i][2];
			ph.direction.x = inputData[i][3];
			ph.direction.y = inputData[i][4];
			ph.direction.z = inputData[i][5];
			ph.power.R = inputData[i][6];
			ph.power.G = inputData[i][7];
			ph.power.B = inputData[i][8];
			ph.type = convertDoubleToPhotonType(inputData[i][9]);
			outputData.push_back(ph);
		}

		return outputData;
	}
	Colour getTotalIntensity(std::vector<Photon> ph, Hit hit, Vector toViewer){
		Colour maxColour;
		Vector r;
		float coeff;
		for (int i = 0; i < ph.size(); i++){
			// maxColour += ph[i].power;
			ph[i].direction.negate();
			hit.normal.reflection(ph[i].direction, r);
			r.normalise();
			coeff = r.dot(toViewer);
			if (coeff > 0.0f){
				maxColour += ph[i].power;
			}

		}
		return maxColour;
	}
	float getMax(alglib::real_1d_array arr){
		return arr[arr.length()-1]; 
	}	
	float calculateAreaofPoints(){
		alglib::real_1d_array outputData;
		outputData.setlength(nSamples);
	 	kdtreequeryresultsdistances(tree, outputData);
		float maxDistance = getMax(outputData);
		return M_PI * pow(maxDistance, 2);
	}

	float convertPhotonTypeToDouble(std::string input){
		if(input == "direct"){
			return 0;
		}
		if(input == "indirect"){
			return 1;
		}
		if(input == "caustic"){
			return 2;
		}
	}

	std::string convertDoubleToPhotonType(float input){
		if(input == 0){
			return  "direct";
		}
		if(input == 1){
			return "indirect";
		}
		if(input == 2){
			return "caustic";
		}
	}
public:

	PhotonMap(int nsamples){
		// wrapper class constructor
		nSamples = nsamples;
	}

	void populateMap(std::vector<Photon> inputData){
		// wrapper function that prepares vector input into a 2D.
		alglib::ae_int_t nx = 3;
		alglib::ae_int_t ny = 7;
		alglib::ae_int_t normtype = 2;
		alglib::real_2d_array photons = convertPhotonVectorTo2DArr(inputData, nx, ny);
		kdtreebuild(photons, nx, ny, normtype, tree);
	}

	Colour calcRadiance(Hit hit, Vertex camEye, float diff){
		Colour c = calcTotalIncomingFlux(hit, camEye-hit.position, diff);
		float a = calculateAreaofPoints();
		return c / a;
	}

	Colour calcRadiance(Hit hit, Vertex camEye, float diff, std::string filter){
		Colour c = calcTotalIncomingFlux(hit, camEye-hit.position, diff, filter);
		float a = calculateAreaofPoints();
		return c / a;
	}

	std::vector<Photon> getNSurroundingPoints(Vertex position){
		alglib::real_1d_array query = convertVertex(position);
		alglib::real_2d_array outputData;
		kdtreequeryknn(tree, query, nSamples);
		kdtreequeryresultsxy(tree, outputData);
		return convert2DArrToPhotonVector(outputData);
	}

	std::vector<Photon> getNSurroundingPoints(Vertex position, std::string filter){
		alglib::real_1d_array query = convertVertex(position);
		alglib::real_2d_array outputData;
		kdtreequeryknn(tree, query, nSamples);
		kdtreequeryresultsxy(tree, outputData);
		std::vector<Photon> data = convert2DArrToPhotonVector(outputData);
		std::vector<Photon> output;
		int count = 0;
		for (int iPhoton = 0; iPhoton<data.size(); iPhoton++){
			if(data[iPhoton].type != filter){
				output.push_back(data[iPhoton]);
				count++;
			}
		}
		return output;
	}
};

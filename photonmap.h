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

class PhotonMap {
private:
	int nSamples;
	alglib::kdtree tree;

	Colour calcTotalIncomingFlux(Vertex position){
		return getTotalIntensity(getNSurroundingPoints(position));
	}
	std::vector<Photon> getNSurroundingPoints(Vertex position){
		alglib::real_1d_array query = convertVertex(position);
		alglib::real_2d_array outputData;
		kdtreequeryknn(tree, query, nSamples);
		kdtreequeryresultsxy(tree, outputData);
		return convert2DArrToPhotonVector(outputData);
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
			outputData.push_back(ph);
		}

		return outputData;
	}
	Colour getTotalIntensity(std::vector<Photon> ph){
		Colour maxColour;

		for (int i = 0; i < ph.size(); i++){
			maxColour += ph[i].power;
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

public:

	PhotonMap(int nsamples){
		// wrapper class constructor
		nSamples = nsamples;
	}

	void populateMap(std::vector<Photon> inputData){
		// wrapper function that prepares vector input into a 2D.
		alglib::ae_int_t nx = 3;
		alglib::ae_int_t ny = 6;
		alglib::ae_int_t normtype = 2;
		alglib::real_2d_array photons = convertPhotonVectorTo2DArr(inputData, nx, ny);
		kdtreebuild(photons, nx, ny, normtype, tree);
	}

	Colour calcRadiance(Vertex position){
		Colour c = calcTotalIncomingFlux(position);
		float a = calculateAreaofPoints();
		return c / a;
	}
};

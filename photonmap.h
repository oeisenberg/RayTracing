/***************************************************************************
 *
 * ohe21 - Oliver's Photon Map class
 *
 */

// PhotonMap is a class to wrap method calls to an external library.

#pragma once

#include "ap.h"
#include "alglibmisc.h"
#include "photon.h"
#include "vertex.h"

class PhotonMap {
private:
	alglib::kdtree tree;

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
			data[i][0] = ph.x;
			data[i][1] = ph.y;
			data[i][2] = ph.z;
			data[i][3] = ph.power.R;
			data[i][4] = ph.power.G;
			data[i][5] = ph.power.B;
		}

		return data;
	}
	std::vector<Photon> convert2DArrToPhotonVector(alglib::real_2d_array inputData){
		std::vector<Photon> outputData;
		Photon ph;
		for (int i = 0; i < inputData.rows(); i++){
			ph.x = inputData[i][0];
			ph.y = inputData[i][1];
			ph.z = inputData[i][2];
			ph.power.R = inputData[i][3];
			ph.power.G = inputData[i][4];
			ph.power.B = inputData[i][5];
			outputData.push_back(ph);
		}

		return outputData;
	}

public:

	PhotonMap(){
		// wrapper class constructor 
	}

	void populateMap(std::vector<Photon> inputData){
		// wrapper function that prepares vector input into a 2D.
		alglib::ae_int_t nx = 3;
		alglib::ae_int_t ny = 3;
		alglib::ae_int_t normtype = 2;
		alglib::real_2d_array photons = convertPhotonVectorTo2DArr(inputData, nx, ny);
		kdtreebuild(photons, nx, ny, normtype, tree);
	}

	std::vector<Photon> getNSurroundingPoints(Vertex position, int nSamples){
		alglib::real_1d_array query = convertVertex(position);
		alglib::real_2d_array outputData;
		kdtreequeryknn(tree, query, nSamples);
		kdtreequeryresultsxy(tree, outputData);
		return convert2DArrToPhotonVector(outputData);
	}

};

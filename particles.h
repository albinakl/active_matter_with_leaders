#pragma once

#ifndef PARTICLES_H
#define PARTICLES_H

#include <vector>

using namespace std;

class Particles
{
public:
	Particles(int Size = 10, double sigma = 0.05, double R_leader_coef = 0.2, double q = 0);
	~Particles();

	void update_vel();
	void update_pos();
	double compute_vacf();
	double compute_nx();
	double compute_ny();
	double number_of_correlated(double angle); 

//private:
	int Size, t = 0;

	double dt = 0.5;
	double x_min = 0, x_max = 50;
	double y_min = 0, y_max = 50;

	double lx = x_max - x_min;
	double ly = y_max - y_min;

	double sigma; //noise level
	double R = 0.2 * (lx + ly) / 2;
	double R_leader;
	double q;

	double vx_0 = 0.8, vy_0 = -0.2;

	vector<double> x;
	vector<double> y;
	vector<double> vx;
	vector<double> vy;
	/*vector<double> v_des;*/
};

#endif 
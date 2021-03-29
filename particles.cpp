#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <numeric>
#include <algorithm> 
#include "particles.h"
//#include "anim.h"

double dist(double ax, double ay, double bx, double by)
{
	double R;
	R = (bx - ax) * (bx - ax) + (by - ay) * (by - ay);
	return sqrt(R);
}

Particles::Particles(int Size, double sigma, double R_leader_coef, double q)
{
	vector <double> x;
	vector <double> y;
	vector <double> vx;
	vector <double> vy;

	double vx_max = 1.0, vx_min = -1.0;
	double vy_max = 1.0, vy_min = -1.0;

	Particles::sigma = sigma;
	Particles::R_leader = R_leader_coef * (Particles::lx + Particles::ly) / 2;
	Particles::q = q;

	x.push_back(Particles::lx / 2);
	y.push_back(Particles::ly / 2);
	vx.push_back(Particles::vx_0);
	vy.push_back(Particles::vy_0);
	for (int i = 1; i < Size; i++) {
		x.push_back((double)rand() / (double)RAND_MAX * Particles::lx + Particles::x_min);
		y.push_back((double)rand() / (double)RAND_MAX * Particles::ly + Particles::y_min);

		vx.push_back((double)rand() / (double)RAND_MAX * (vx_max - vx_min) + vx_min);
		vy.push_back((double)rand() / (double)RAND_MAX * (vy_max - vy_min) + vy_min);
	}
	Particles::Size = Size;
	Particles::x = x;
	Particles::y = y;
	Particles::vx = vx;
	Particles::vy = vy;
}

Particles::~Particles()
{
	Particles::x.clear();
	Particles::y.clear();
	Particles::vx.clear();
	Particles::vy.clear();
}

void Particles::update_vel()
{
	vector<double> zeta_x(Particles::Size);
	vector<double> zeta_y(Particles::Size);
	vector<double> Vx(Particles::Size);
	vector<double> Vy(Particles::Size);
	double cur_vx, cur_vy;
	double N, VR, ex, ey, eR, R, R_leader, q_rand;
	R = Particles::R;
	R_leader = Particles::R_leader;
	//Vicsek model
	for (int i = 0; i < Particles::Size; i++) {
		cur_vx = -Particles::vx[i];
		cur_vy = -Particles::vy[i];
		N = 0;
		for (int j = 0; j < Particles::Size; j++) {
			if (dist(Particles::x[i], Particles::y[i], Particles::x[j], Particles::y[j]) < R or
				dist(Particles::x[i], Particles::y[i], Particles::x[j], Particles::y[j] + Particles::ly) < R or
				dist(Particles::x[i], Particles::y[i], Particles::x[j], Particles::y[j] - Particles::ly) < R or
				dist(Particles::x[i], Particles::y[i], Particles::x[j] + Particles::lx, Particles::y[j]) < R or
				dist(Particles::x[i], Particles::y[i], Particles::x[j] - Particles::lx, Particles::y[j]) < R or
				dist(Particles::x[i], Particles::y[i], Particles::x[j] + Particles::lx, Particles::y[j] + Particles::ly) < R or
				dist(Particles::x[i], Particles::y[i], Particles::x[j] - Particles::lx, Particles::y[j] + Particles::ly) < R or
				dist(Particles::x[i], Particles::y[i], Particles::x[j] + Particles::lx, Particles::y[j] - Particles::ly) < R or
				dist(Particles::x[i], Particles::y[i], Particles::x[j] - Particles::lx, Particles::y[j] - Particles::ly) < R) {
				N += 1;
				cur_vx += Particles::vx[j];
				cur_vy += Particles::vy[j];
			}
		}
		//ordinary case (NO LEADER)
		Vx.push_back(cur_vx / N);
		Vy.push_back(cur_vy / N);
	}
	//F_fluct
	for (int i = 0; i < Particles::Size; i++) {
		zeta_x[i] += Particles::sigma * 2 * ((double)rand() / (double)RAND_MAX - 0.5);
		zeta_y[i] += Particles::sigma * 2 * ((double)rand() / (double)RAND_MAX - 0.5);
	}
	//update vel
	//Particles::vx[0] = Particles::vx_0;
	//Particles::vy[0] = Particles::vy_0;
	for (int i = 0; i < Particles::Size; i++) {
		//ex = Particles::vx[i] + Vx[i];
		//ey = Particles::vy[i] + Vy[i];
		
		//leader input 
		if (dist(Particles::x[i], Particles::y[i], Particles::x[0], Particles::y[0]) < R_leader or
			dist(Particles::x[i], Particles::y[i], Particles::x[0], Particles::y[0] + Particles::ly) < R_leader or
			dist(Particles::x[i], Particles::y[i], Particles::x[0], Particles::y[0] - Particles::ly) < R_leader or
			dist(Particles::x[i], Particles::y[i], Particles::x[0] + Particles::lx, Particles::y[0]) < R_leader or
			dist(Particles::x[i], Particles::y[i], Particles::x[0] - Particles::lx, Particles::y[0]) < R_leader or
			dist(Particles::x[i], Particles::y[i], Particles::x[0] + Particles::lx, Particles::y[0] + Particles::ly) < R_leader or
			dist(Particles::x[i], Particles::y[i], Particles::x[0] - Particles::lx, Particles::y[0] + Particles::ly) < R_leader or
			dist(Particles::x[i], Particles::y[i], Particles::x[0] + Particles::lx, Particles::y[0] - Particles::ly) < R_leader or
			dist(Particles::x[i], Particles::y[i], Particles::x[0] - Particles::lx, Particles::y[0] - Particles::ly) < R_leader) {
			//Vx.push_back(Particles::q * Particles::vx[0] + (1 - Particles::q) * cur_vx / N);
			//Vy.push_back(Particles::q * Particles::vy[0] + (1 - Particles::q) * cur_vy / N);
			
			//Particles::vx[i] = Particles::q * Particles::vx[0] + (1 - Particles::q) * ex + zeta_x[i];
			//Particles::vy[i] = Particles::q * Particles::vy[0] + (1 - Particles::q) * ey + zeta_y[i];
			q_rand = (double)rand() / (double)RAND_MAX * 1.0;
			if (q_rand < Particles::q) {
				ex = Particles::vx[i] + Particles::q * Particles::vx[0] + (1 - Particles::q) * Vx[i] + zeta_x[i];
				ey = Particles::vy[i] + Particles::q * Particles::vy[0] + (1 - Particles::q) * Vy[i] + zeta_y[i];
			}
			else {
				ex = Particles::vx[i] + Vx[i] + zeta_x[i];
				ey = Particles::vy[i] + Vy[i] + zeta_y[i];
			}
			//cout << i << " leader zone" << endl;
		}
		else {
			ex = Particles::vx[i] + Vx[i] + zeta_x[i];
			ey = Particles::vy[i] + Vy[i] + zeta_y[i];
		}
		eR = dist(0, 0, ex, ey);
		VR = dist(0, 0, Particles::vx[i], Particles::vy[i]);
		ex = ex * VR / eR;
		ey = ey * VR / eR;
		Particles::vx[i] = ex;
		Particles::vy[i] = ey;

	}
	
}

void Particles::update_pos()
{
	for (int i = 0; i < Particles::Size; i++) {
		Particles::x[i] += Particles::vx[i] * Particles::dt;
		Particles::y[i] += Particles::vy[i] * Particles::dt;

		//lx periodic boundary conditions
		if (Particles::x[i] >= Particles::x_max)
			Particles::x[i] -= Particles::lx;
		else if (Particles::x[i] <= Particles::x_min)
			Particles::x[i] += Particles::lx;

		//ly periodic boundary conditions
		if (Particles::y[i] >= Particles::y_max)
			Particles::y[i] -= Particles::ly;
		else if (Particles::y[i] <= Particles::y_min)
			Particles::y[i] += Particles::ly;

		//reflecting boundary conditions
		//if (Particles::y[i] >= Particles::y_max or Particles::y[i] <= Particles::y_min)
		//	Particles::vy[i] = -Particles::vy[i];
	}
	Particles::t += 1;
}

double Particles::compute_vacf()
{
	double vacf = 0;
	double temp, abs_vl;
	abs_vl = dist(0, 0, Particles::vx[0], Particles::vy[0]);
	for (int i = 0; i < Particles::Size; i++) {
		temp = Particles::vx[0] * Particles::vx[i] + Particles::vy[0] * Particles::vy[i];
		temp /= abs_vl * dist(0, 0, Particles::vx[i], Particles::vy[i]);
		vacf += temp;
	}
	return vacf / Particles::Size;
}

double Particles::compute_nx()
{
	double nx = 0;
	double temp;
	for (int i = 0; i < Particles::Size; i++) {
		temp = Particles::vx[i] / dist(0, 0, Particles::vx[i], Particles::vy[i]);
		nx += temp;
	}
	return nx / Particles::Size;
}

double Particles::compute_ny()
{
	double ny = 0;
	double temp;
	for (int i = 0; i < Particles::Size; i++) {
		temp = Particles::vy[i] / dist(0, 0, Particles::vx[i], Particles::vy[i]);
		ny += temp;
	}
	return ny / Particles::Size;
}

double Particles::number_of_correlated(double angle)
{	
	double n_corr = 0;
	double temp_angle, abs_vl;
	abs_vl = dist(0, 0, Particles::vx[0], Particles::vy[0]);
	for (int i = 0; i < Particles::Size; i++) {
		temp_angle = Particles::vx[0] * Particles::vx[i] + Particles::vy[0] * Particles::vy[i];
		temp_angle /= abs_vl * dist(0, 0, Particles::vx[i], Particles::vy[i]);
		if (temp_angle >= angle) {
			n_corr += 1;
		}
	}
	return n_corr;
}
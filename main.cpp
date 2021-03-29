#include <iostream>
#include <glut.h>

#include <fstream>
#include <string>

#include "particles.h"
#include "anim.h"

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Simulation");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    init();

    glutMainLoop();

    /*Particles Group(200);
    const int len_arr_sigma = 4, len_arr_Rlcoef = 2, len_arr_q = 4;
    double arr_sigma[len_arr_sigma] = {0.01, 0.2, 0.4, 0.60 };
    double arr_Rlcoef[len_arr_Rlcoef] = { 0.2, 0.6 };
    double arr_q[len_arr_q] = { 0.2, 0.4, 0.6, 0.8};
    double sigma, Rlcoef, q;
    ofstream outfile, parfile;
    int N = 200;
    for (int i = 0; i < len_arr_sigma; i++) {
        for (int j = 0; j < len_arr_Rlcoef; j++) {
            for (int k = 0; k < len_arr_q; k++) {
                cout << i << "/" << len_arr_sigma << ' ' << j << "/" << len_arr_Rlcoef << ' ' << k << "/" << len_arr_q << endl;
                sigma = arr_sigma[i];
                Rlcoef = arr_Rlcoef[j];
                q = arr_q[k];
                Particles Group(N, sigma, Rlcoef, q);
                //outfile.open("vacf_rl" + to_string((int)(Rlcoef * 100)) + "_q" + to_string((int)(100 * q)) + "_noise" + to_string((int)(100 * sigma)) + ".txt");
                //outfile << "vacf " << "n_corr_0.9 " << "n_corr_0.95 " << "n_corr_0.98 " << "n_corr_0.99 " << "n_corr_0.996 " << "n_corr_0.999 " << endl;
                parfile.open("parf_rl" + to_string((int)(Rlcoef * 100)) + "_q" + to_string((int)(100 * q)) + "_noise" + to_string((int)(100 * sigma)) + ".txt");
                parfile << "parf " << "nx " << "ny " << endl;
                while (Group.t < 1000) {
                    Group.update_vel();
                    Group.update_pos();
                    //outfile << Group.compute_vacf();
                    //outfile << ' ' << Group.number_of_correlated(0.8);
                    //outfile << ' ' << Group.number_of_correlated(0.87);
                    //outfile << ' ' << Group.number_of_correlated(0.9);
                    //outfile << ' ' << Group.number_of_correlated(0.99);
                    //outfile << ' ' << Group.number_of_correlated(0.996);
                    //outfile << ' ' << Group.number_of_correlated(0.999) << endl;
                    parfile << Group.compute_nx() << ' ' << Group.compute_ny() << endl;
                }
                //outfile.close();
                parfile.close();
                Group.~Particles();
                cout << "finished" << endl;
            }
        }
    }*/
}




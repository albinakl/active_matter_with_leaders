#include <glut.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include "anim.h"
#include "particles.h"

Particles Group(200);
int stop_flag = 0;

const char* cmd = "ffmpeg -r 10 -f rawvideo -pix_fmt rgba -s 500x500 -i - "
"-threads 0 -preset fast -y -pix_fmt yuv420p -crf 21 -vf vflip output.mp4";

// open pipe to ffmpeg's stdin in binary write mode
FILE* ffmpeg = _popen(cmd, "wb");
int* buffer = new int[500 * 500];

ofstream outfile;

void init()
{
    glClearColor(0, 0, 0, 1);
    //outfile.open("vacf_rl_"+to_string((int)(100*Group.R_leader/Group.lx))+"_q_"+to_string((int)(100*Group.q))+"_noise_" + to_string((int)(100*Group.sigma)) + ".txt");
    //outfile << "vacf " << "n_corr_0.8 " << "n_corr_0.87 " << "n_corr_0.9 " << "n_corr_0.99 " << "n_corr_0.996 " << "n_corr_0.999 " << endl;
}

void display_xlabel()
{
    char text[10];
    float labels = 10;

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor4f(0.0, 1.0, 0.5, 0.1);
    for (int i = Group.x_min; i <= Group.x_max; i += (Group.x_max - Group.x_min) / labels)
    {
        glVertex2f(i, Group.y_min + 1.0 * (Group.y_max - Group.y_min));
        glVertex2f(i, Group.y_min + 0.9 * (Group.y_max - Group.y_min));
    }
    glEnd();

    for (int i = Group.x_min; i <= Group.x_max; i += (Group.x_max - Group.x_min) / labels)
    {
        strcpy_s(text, to_string(i).c_str());
        glRasterPos2f(i, Group.y_min + 0.65 * (Group.y_max - Group.y_min));
        for (int j = 0; text[j] != '\0'; j++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[j]);
    }

    strcpy_s(text, "X");
    glRasterPos2f(Group.x_min + 0.5 * (Group.x_max - Group.x_min), Group.y_min + 0.2 * (Group.y_max - Group.y_min));
    for (int j = 0; text[j] != '\0'; j++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[j]);
}

void display_ylabel()
{
    char text[10];
    float labels = 5;

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor4f(0.0, 1.0, 0.5, 0.1);
    for (int i = Group.y_min; i <= Group.y_max; i += (Group.y_max - Group.y_min) / labels)
    {
        glVertex2f(Group.x_min + 1.0 * (Group.x_max - Group.x_min), i);
        glVertex2f(Group.x_min + 0.9 * (Group.x_max - Group.x_min), i);
    }
    glEnd();

    for (int i = Group.y_min; i <= Group.y_max; i += (Group.y_max - Group.y_min) / labels)
    {
        strcpy_s(text, to_string(i).c_str());
        glRasterPos2f(Group.x_min + 0.5 * (Group.x_max - Group.x_min), i);
        for (int j = 0; text[j] != '\0'; j++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[j]);
    }
    strcpy_s(text, "Y");
    glRasterPos2f(Group.x_min + 0.12 * (Group.x_max - Group.x_min), Group.y_min + 0.5 * (Group.y_max - Group.y_min));
    for (int j = 0; text[j] != '\0'; j++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[j]);
}

void display_title()
{
    char text[] = "Active particles modelling, time step = ";
    char time[10];
    strcpy_s(time, to_string(Group.t).c_str());

    glColor3f(1, 0, 0);
    glRasterPos2f(Group.x_min + 0.2 * (Group.x_max - Group.x_min), (Group.y_max - Group.y_min) / 3);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    for (int i = 0; time[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, time[i]);
}

void display_legend()
{
    glColor3f(0.5, 0.2, 0.2);

    char text[] = "rho = ";
    char time[10];
    strcpy_s(time, to_string(Group.Size / (Group.x_max - Group.x_min) / (Group.y_max - Group.y_min)).c_str());
    glRasterPos2f(Group.x_min + 0.15 * (Group.x_max - Group.x_min), Group.y_min + 0.9 * (Group.y_max - Group.y_min));
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    for (int i = 0; i < 4; i++) //time[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, time[i]);

    strcpy_s(text, "chi = ");
    strcpy_s(time, to_string(0).c_str());
    glRasterPos2f(Group.x_min + 0.15 * (Group.x_max - Group.x_min), Group.y_min + 0.8 * (Group.y_max - Group.y_min));
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    for (int i = 0; i < 4; i++) //time[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, time[i]);


    strcpy_s(text, "left");
    glRasterPos2f(Group.x_min + 0.15 * (Group.x_max - Group.x_min), Group.y_min + 0.7 * (Group.y_max - Group.y_min));
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);

    strcpy_s(text, "right");
    glRasterPos2f(Group.x_min + 0.15 * (Group.x_max - Group.x_min), Group.y_min + 0.6 * (Group.y_max - Group.y_min));
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);

    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(0.0, 0.5 + 0.4 * (-1.2), 1.0);
    glVertex2f(Group.x_min + 0.6 * (Group.x_max - Group.x_min), Group.y_min + 0.72 * (Group.y_max - Group.y_min));
    glColor3f(0.0, 0.5 + 0.4 * (1.2), 1.0);
    glVertex2f(Group.x_min + 0.6 * (Group.x_max - Group.x_min), Group.y_min + 0.62 * (Group.y_max - Group.y_min));
    glEnd();
}

void display_axes()
{
    glLineWidth(2.0);

    glBegin(GL_LINES);
    glColor4f(1.0, 1.0, 1.0, 0.1);

    glVertex2f(Group.x_min, Group.y_min);
    glVertex2f(Group.x_max, Group.y_min);
    glVertex2f(Group.x_min, Group.y_min);
    glVertex2f(Group.x_min, Group.y_max);
    glEnd();
}

void display_particles()
{
    glPointSize(1.0);
    //draw
    glBegin(GL_LINES);
    for (int i = 1; i < Group.Size; i++) {
        glColor3f(0.0, 0.5 + 0.4 * 1.2, 1.0);
        glVertex2f(Group.x[i], Group.y[i]);
        glVertex2f(Group.x[i] + Group.dt * Group.vx[i], Group.y[i] + Group.dt * Group.vy[i]);
    }
    glEnd();
    glBegin(GL_POINTS);
    for (int i = 1; i < Group.Size; i++) {
        glColor3f(0.0, 0.5 + 0.4 * 1.2, 1.0);
        glVertex2f(Group.x[i], Group.y[i]);
        //glVertex2f(Group.x[i] + Group.dt * Group.vx[i], Group.y[i] + Group.dt * Group.vy[i]);
    }
    glEnd();
    glPointSize(4.0);
    //draw
    glBegin(GL_LINES);
    glColor3f(0.5, 0.5, 0.0);
    glVertex2f(Group.x[0], Group.y[0]);
    glVertex2f(Group.x[0] + Group.dt * Group.vx[0], Group.y[0] + Group.dt * Group.vy[0]);
    glEnd();
    glBegin(GL_POINTS);
    glColor3f(0.5, 0.5, 0.0);
    glVertex2f(Group.x[0], Group.y[0]);
    glVertex2f(Group.x[0], Group.y[0]);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //screen size is set in main.cpp to w = 500, h = 250
    /*glViewport(0, 200, 500, 50);
    glLoadIdentity();
    display_title();

    glViewport(50, 0, 350, 50);
    glLoadIdentity();
    display_xlabel();

    glViewport(0, 50, 50, 150);
    glLoadIdentity();
    display_ylabel();

    glViewport(400, 0, 100, 200);
    glLoadIdentity();
    display_legend();

    glViewport(50, 50, 350, 150);*/
    glViewport(0, 0, 500, 500);
    glLoadIdentity();
    /*display_axes();*/
    display_particles();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(Group.x_min, Group.x_max, Group.y_min, Group.y_max);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
    //"n_corr_0.8 " << "n_corr_0.87 " << "n_corr_0.9 " << "n_corr_0.99 " << "n_corr_0.996 " << "n_corr_0.999
    Group.update_vel();
    Group.update_pos();
    outfile << Group.compute_vacf();
    outfile << ' ' << Group.number_of_correlated(0.8);
    outfile << ' ' << Group.number_of_correlated(0.87);
    outfile << ' ' << Group.number_of_correlated(0.9);
    outfile << ' ' << Group.number_of_correlated(0.99);
    outfile << ' ' << Group.number_of_correlated(0.996);
    outfile << ' ' << Group.number_of_correlated(0.999) << endl;

    if (Group.t < 1000 && stop_flag == 0) {

        glViewport(0, 0, 500, 500);
        glReadPixels(0, 0, 500, 500, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        fwrite(buffer, sizeof(int) * 500 * 500, 1, ffmpeg);
        glutPostRedisplay();
        glutTimerFunc(1000 / 60, timer, 0);
    }
    else if (Group.t == 1000 || stop_flag == 1) {
        _pclose(ffmpeg);
        outfile.close();
        cout << Group.t << " steps; " << endl;
        //here we can start a new simulation
    }
}
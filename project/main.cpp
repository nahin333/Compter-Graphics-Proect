#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include<bits/stdc++.h>
#define PI 3.14159265359
#include "RGBpixmap.cpp"
RGBpixmap pix[10];
using namespace std;

void Init();
int width=1200;
int height=600;
int Depth=1;
static inline void set_material(GLfloat c[], GLfloat s[], GLfloat sh[])
{
    GLfloat a[4] = { c[0]*0.1f, c[1]*0.1f, c[2]*0.1f, c[3] };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
    glMaterialfv(GL_FRONT, GL_SPECULAR, s);
    glMaterialfv(GL_FRONT, GL_SHININESS, sh);
}

static GLfloat jack_mat_color[] = { 0, 1, 1, 1 };
static GLfloat jack_mat_spec[] = { 1, 1, 1, 1 };
static GLfloat jack_mat_shininess[] = { 120 };


static GLfloat side_wall_mat_color[] = { 1, 1, 1, 1 };
static GLfloat side_wall_spec[] = { 1, 1, 1, 1 };
static GLfloat side_wall_shininess[] = { 120 };


static GLfloat floor_wall_mat_color[] = { 1, 1, 1, 1 };
static GLfloat floor_wall_spec[] = { 1, 1, 1, 1 };
static GLfloat floor_wall_shininess[] = { 120 };


static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

   // glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void owns(GLfloat sx,GLfloat sy, GLfloat sz)
{
    GLfloat s[16]= {sx,0,0,0,
                    0,sy,0,0,
                    0,0,sz,0,
                    0,0,0,1
                   };
    glMatrixMode(GL_MATRIX_MODE);
    glMultMatrixf(s);
}

static GLdouble rx = 0;
static GLdouble ry = 0;///-40
static GLdouble rz = 0;
static GLdouble M = 0;
static GLdouble x_co=0,y_co=0,z_co=0;
static GLdouble ex=0,ey=0,ez=20,cx=0,cy=0,cz=0,hx=0,hy=1,hz=0;
static GLdouble winW,winH;



///lighr variable
static GLfloat table_top_mat_color[] = { 1, 1, 0, 1 };
static GLfloat table_mat_color[] = { 0, 1, 0, 1 };
static GLfloat table_mat_spec[] = { 1, 1, 1, 1 };
static GLfloat table_mat_shininess[] = { 150 };

static GLfloat table2_top_mat_color[] = { 1, 1, 0, 1 };
static GLfloat table2_mat_color[] = { 0, 1, 0, 1 };
static GLfloat table2_mat_spec[] = { 1, 1, 1, 1 };
static GLfloat table2_mat_shininess[] = { 150 };


static GLfloat head_mat_color[] = { 1, 1, 0, 1 };
static GLfloat head_mat_spec[] = { 1, 1, 1, 1 };
static GLfloat head_mat_shininess[] = { 150 };


static GLfloat body_mat_color[] = { 1, 0, 0, 1 };
static GLfloat body_mat_spec[] = { 1, 1, 1, 1 };
static GLfloat body_mat_shininess[] = { 150 };

static GLfloat bleg_foot_mat_color[] = { 0, 0, 1, 1 };
static GLfloat bleg_foot_mat_spec[] = { 1, 1, 1, 1 };
static GLfloat bleg_foot_mat_shininess[] = { 150 };



static GLfloat l0_ambient[] = { 0, 0, 0, 1 }; ///ambient RGBA intensity of the light
static GLfloat l0_diffuse[] = { 1, 1, 1, 1 };  ///diffuse RGBA intensity of the light
static GLfloat l0_specular[] = { 1, 1, 1, 1 }; ///the specular RGBA intensity of the light.
static GLfloat l0_position[] = { 4, 15, 4, 1 };  ///specify the position of the light in homogeneous object coordinates.

static GLfloat l1_ambient[] = { 0.05f, 0.05f, 0.05f, 1 };
static GLfloat l1_diffuse[] = { 1, 1, 1, 1 };
static GLfloat l1_specular[] = { 1, 1, 1, 1 };
static GLfloat l1_position[] = { 20, 20, 20, 1 };

static GLfloat l1_spot_dir[] = { -0.9, -1.5, -0.35}; ///The params parameter contains three floating-point values that specify the direction of the light in homogeneous object coordinates
static GLfloat l1_spot_cutoff[] = { 10 };  ///The params parameter is a single floating-point value that specifies the maximum spread angle of a light source
///light variable


static void set_lights()
{
    glLightfv(GL_LIGHT0, GL_AMBIENT, l0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, l0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, l0_position);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.005);

    // const double t = glutGet(GLUT_ELAPSED_TIME) / 10.0;
    const double t = 1750;
    //cout<<"time value is "<<t<<endl;

    glLightfv(GL_LIGHT1, GL_AMBIENT, l1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, l1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, l1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, l1_position);
    glPushMatrix();
    glRotated(t*0.5, 1, 1, 1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, l1_spot_dir);
    glPopMatrix();
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, l1_spot_cutoff);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.1);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.001f);
}


/// 2x2x2 cube centered at origin
static void cube()
{
    glBegin(GL_QUADS);

    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);

    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);

    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);

    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);

    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);

    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);

    glEnd();
}

static GLdouble circleXY[36][2];
static void circleInit()
{
    for (int i=0; i<=18; i++)
    {
        GLdouble angle = (GLdouble)i * 10.0 * PI / 180.0;
        circleXY[i][0] = cos(angle);
        circleXY[i][1] = sin(angle);
    }
    for (int i=19, j=2; i<36; i++, j+=2)
    {
        circleXY[i][0] = circleXY[i-j][0];
        circleXY[i][1] = -circleXY[i-j][1];
    }
}

static void cylinder()
{
    glBegin(GL_POLYGON);
    for (int i=0; i<36; i++)
        glVertex3d(circleXY[i][0], 0, circleXY[i][1]);
    glEnd();

    glBegin(GL_POLYGON);
    for (int i=35; i>=0; i--)
        glVertex3d(circleXY[i][0], 1, circleXY[i][1]);
    glEnd();

    glBegin(GL_QUAD_STRIP);
    for (int i=0; i<36; i++)
    {
        glVertex3d(circleXY[i][0], 0, circleXY[i][1]);
        glVertex3d(circleXY[i][0], 1, circleXY[i][1]);
    }
    glVertex3d(circleXY[0][0], 0, circleXY[0][1]);
    glVertex3d(circleXY[0][0], 1, circleXY[0][1]);
    glEnd();
}

void head()
{
    //glColor3f(1, 1, 0);
    glPushMatrix();
    glTranslated(0, 2, 0);
    glScaled(0.55, 1.2, 0.55);
    set_material(head_mat_color,head_mat_spec,head_mat_shininess);
    cylinder();
    glPopMatrix();
}
void body()
{
    //glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslated(0, 2, 0);
    glScaled(1.1, 1.4, 1.1);
    glTranslated(0, -1, 0);
    set_material(body_mat_color,body_mat_spec,body_mat_shininess);
    cube();
    glPopMatrix();

    //glColor3f(0, 0, 1);
    glPushMatrix();
    glTranslated(0, -0.8, 0);
    glScaled(1.1, 0.5, 1.1);
    glTranslated(0, -1, 0);
    set_material(bleg_foot_mat_color,bleg_foot_mat_spec,bleg_foot_mat_shininess);
    cube();
    glPopMatrix();
}
void left_leg()
{
    glPushMatrix();
    glTranslated(-0.6, -1.8, 0);
    glScaled(0.5, 0.5, 1.1);
    glTranslated(0, -1, 0);
    set_material(bleg_foot_mat_color,bleg_foot_mat_spec,bleg_foot_mat_shininess);
    cube();
    glPopMatrix();
}
void right_leg()
{
    glPushMatrix();
    glTranslated(0.6, -1.8, 0);
    glScaled(0.5, 0.5, 1.1);
    glTranslated(0, -1, 0);
    set_material(bleg_foot_mat_color,bleg_foot_mat_spec,bleg_foot_mat_shininess);
    cube();
    glPopMatrix();
}
void left_foot()
{
    glPushMatrix();
    glTranslated(-0.6, -2.8, -1.1);
    glScaled(0.5, 0.3, 1.35);
    glTranslated(0, -1, 1);
    set_material(bleg_foot_mat_color,bleg_foot_mat_spec,bleg_foot_mat_shininess);
    cube();
    glPopMatrix();
}
void right_foot()
{
    glPushMatrix();
    glTranslated(0.6, -2.8, -1.1);
    glScaled(0.5, 0.3, 1.35);
    glTranslated(0, -1, 1);
    set_material(bleg_foot_mat_color,bleg_foot_mat_spec,bleg_foot_mat_shininess);
    cube();
    glPopMatrix();
}
void left_arm()
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    int a=t*90;

    //glColor3f(0, 0, 1);
    glPushMatrix();
    glTranslated(0, 1, 0);
    glRotated(-90, 0, 0, 1);
    glScaled(0.5, 1.25, 0.5);
    glTranslated(0, -1, 0);
    set_material(floor_wall_mat_color,floor_wall_spec,floor_wall_shininess);
    cube();
    glPopMatrix();

    glPushMatrix();

    glTranslated(0,1,0);
    a=a%70;
    if(a<35)
        glRotated(-a,1,0,0);
    else
        glRotated(a-70,1,0,0);
    glTranslated(0,-1,0);

    glPushMatrix();
    glTranslated(-2, 0.5, 0);
    glRotated(-45, 1, 0, 0);
    glScaled(0.36, 1, 0.36);
    glTranslated(0, -1, 0);
    set_material(floor_wall_mat_color,floor_wall_spec,floor_wall_shininess);
    cube();
    glPopMatrix();
    glPopMatrix();
}
void right_arm()
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    int a=t*90;

    glPushMatrix();
    glTranslated(0, 1, 0);
    glRotated(90, 0, 0, 1);
    glScaled(0.5, 1.25, 0.5);
    glTranslated(0, -1, 0);
    set_material(floor_wall_mat_color,floor_wall_spec,floor_wall_shininess);
    cube();
    glPopMatrix();

    glPushMatrix();

    //rotation of hand begins
    glTranslated(0,1,0);
    a=a%70;
    if(a<35)
        glRotated(-a,1,0,0);
    else
        glRotated(a-70,1,0,0);

    glTranslated(0,-1,0);
    //rotation of hand ends
    glPushMatrix();
    glTranslated(2, 0.5, 0);
    glRotated(-45, 1, 0, 0);
    glScaled(0.36, 1, 0.36);
    glTranslated(0, -1, 0);
    set_material(floor_wall_mat_color,floor_wall_spec,floor_wall_shininess);
    cube();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}
void fireman()
{

    head();
    body();
    left_leg();
    right_leg();
    left_foot();
    right_foot();
    left_arm();
    right_arm();

}



void wall()
{

    glPushMatrix();
    ///bottom
    //glColor3f(0.3,0.3,0.3);
    glTranslatef(0,-2.0,0.0);
    glScalef(4.0, .1, 8.0);
    //set_material(floor_wall_mat_color,floor_wall_spec,floor_wall_shininess);
    glBindTexture(GL_TEXTURE_2D,12);
    glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    ///left
    //glColor3f(0.4,0.4,0.4);
    glScalef(1/4.0, 1/0.1, 1/8.0);
    glScalef(.1, 3.0, 5.0);
    glTranslatef(-39,1.02,-0.5);
  //  set_material(side_wall_mat_color, side_wall_spec, side_wall_shininess);
    glBindTexture(GL_TEXTURE_2D,10);
    glEnable(GL_TEXTURE_2D);
    cube(); /// back right
    glDisable(GL_TEXTURE_2D);







    glBindTexture(GL_TEXTURE_2D,10);
    glEnable(GL_TEXTURE_2D);
    glTranslatef(-0,-0.5,1);
    glScalef(0.05, 1, 1);
    glutSolidCube(1);  ///bottom
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,10);
    glEnable(GL_TEXTURE_2D);


    glTranslatef(10,1.25,0.25);
    glScalef(0.05, 0.5, 0.5);
    glutSolidCube(1); /// mid up
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,10);
    glEnable(GL_TEXTURE_2D);


    glTranslatef(10,0.47,0.7);
    glScalef(0.05, 2.07, 0.5);
    glutSolidCube(1); ///back right
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();




    glPushMatrix();

    glScalef(20, 1.0, 1.0);
    glTranslatef(-39,1.02,-2);
  //  set_material(side_wall_mat_color, side_wall_spec, side_wall_shininess);
    glBindTexture(GL_TEXTURE_2D,10);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glRotated(135,0,0,1);
    //cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();




    ///back
    //glColor3f(0.5,0.5,0.5);
    glScalef(1, 1/3.0, 1/8.0);
    glScalef(4.0, 13.09, 10);
    glTranslatef(0.98,-0.025,-80.4);
  //  set_material(side_wall_mat_color, side_wall_spec, side_wall_shininess);
    glBindTexture(GL_TEXTURE_2D,10);
    glEnable(GL_TEXTURE_2D);
    // cube();
    glDisable(GL_TEXTURE_2D);
    glScalef(1/4.0, 1/3.09, 1/0.1);

    glPopMatrix();



    glPushMatrix();
    glTranslated(0,1,-7);
    glScaled(8,6,0.1);
    glBindTexture(GL_TEXTURE_2D,10);
    glEnable(GL_TEXTURE_2D);
  //  cube();
    glutSolidCube(1); ///side right
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();










    glPushMatrix();
    glTranslated(0,1,-6.9);
    glScaled(4,3,0.1);
    glBindTexture(GL_TEXTURE_2D,13);
    glEnable(GL_TEXTURE_2D);
   // cube();
 glutSolidCube(1); ///side right
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();







glPushMatrix();

    //glScalef(1/4.0, 1/0.1, 1/8.0);
    glScalef(.1, 3.0, 5.2);
    glTranslatef(-48,0.50,0.5);
   // set_material(side_wall_mat_color, side_wall_spec, side_wall_shininess);
    glBindTexture(GL_TEXTURE_2D,13);
    glEnable(GL_TEXTURE_2D);
    cube(); /// back right
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}




void wall2()
{

    glPushMatrix();
    ///bottom
    //glColor3f(0.3,0.3,0.3);
    glTranslatef(0,-2.0,0.0);
    glScalef(4.0, .1, 8.0);
    set_material(floor_wall_mat_color,floor_wall_spec,floor_wall_shininess);
    //glBindTexture(GL_TEXTURE_2D,12);
    //glEnable(GL_TEXTURE_2D);
    cube();
    //glDisable(GL_TEXTURE_2D);
    ///left
    //glColor3f(0.4,0.4,0.4);
    glScalef(1/4.0, 1/0.1, 1/8.0);
    glScalef(.1, 3.0, 5.0);
    glTranslatef(-39,1.02,-0.5);
    set_material(side_wall_mat_color, side_wall_spec, side_wall_shininess);
   // glBindTexture(GL_TEXTURE_2D,10);
    //glEnable(GL_TEXTURE_2D);
    cube(); /// back right
    //glDisable(GL_TEXTURE_2D);







    //glBindTexture(GL_TEXTURE_2D,10);
    //glEnable(GL_TEXTURE_2D);
    glTranslatef(-0,-0.5,1);
    glScalef(0.05, 1, 1);
    glutSolidCube(1);  ///bottom
    //glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D,10);
   // glEnable(GL_TEXTURE_2D);


    glTranslatef(10,1.25,0.25);
    glScalef(0.05, 0.5, 0.5);
    glutSolidCube(1); /// mid up
    //glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
   // glBindTexture(GL_TEXTURE_2D,10);
   // glEnable(GL_TEXTURE_2D);


    glTranslatef(10,0.47,0.7);
    glScalef(0.05, 2.07, 0.5);
    glutSolidCube(1); ///back right
   // glDisable(GL_TEXTURE_2D);
    glPopMatrix();




    glPushMatrix();

    glScalef(20, 1.0, 1.0);
    glTranslatef(-39,1.02,-2);
    set_material(side_wall_mat_color, side_wall_spec, side_wall_shininess);
   // glBindTexture(GL_TEXTURE_2D,10);
   // glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glRotated(135,0,0,1);
    //cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    glPopMatrix();




    ///back
    //glColor3f(0.5,0.5,0.5);
    glScalef(1, 1/3.0, 1/8.0);
    glScalef(4.0, 13.09, 10);
    glTranslatef(0.98,-0.025,-80.4);
    set_material(side_wall_mat_color, side_wall_spec, side_wall_shininess);
    //glBindTexture(GL_TEXTURE_2D,10);
    //glEnable(GL_TEXTURE_2D);
    // cube();
    //glDisable(GL_TEXTURE_2D);
    glScalef(1/4.0, 1/3.09, 1/0.1);

    glPopMatrix();



    glPushMatrix();
    glTranslated(0,1,-7);
    glScaled(8,6,0.1);
    //glBindTexture(GL_TEXTURE_2D,10);
    //glEnable(GL_TEXTURE_2D);
    glutSolidCube(1); ///side right
    //glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,1,-6.9);
    glScaled(4,3,0.1);
    //glBindTexture(GL_TEXTURE_2D,13);
   // glEnable(GL_TEXTURE_2D);
    glutSolidCube(1); ///side right
 //   glDisable(GL_TEXTURE_2D);
    glPopMatrix();


  ///
    glPushMatrix();
    //glScalef(1/4.0, 1/0.1, 1/8.0);
    glScalef(.1, 3.0, 5.2);
    glTranslatef(-48,0.50,0.5);
   // set_material(side_wall_mat_color, side_wall_spec, side_wall_shininess);
    cube(); /// back right
    glPopMatrix();

///


}





void table()
{
    glPushMatrix();
    ///table surface
    //glColor3f(0,0.5,0);
    glTranslatef(0,0.0,0.0);
    glScalef(3.0, .1, 4.0);
    set_material(table_top_mat_color, table_mat_spec, table_mat_shininess);
    glBindTexture(GL_TEXTURE_2D,11);
    glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    ///front-left
    //glColor3f(0.1, 0.1, 0.1);
    glScalef(1/3.0, 1/0.1, 1/4.0);
    glScalef(.2, 0.9, 0.4);
    glTranslatef(0.0,-1.11,0.0);
    glTranslatef(-10.0,0,2.0);
    set_material(table_mat_color, table_mat_spec, table_mat_shininess);

    glBindTexture(GL_TEXTURE_2D,11);
    glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    ///back-left
    //glColor3f(0.1, 0.1, 0.1);
    glTranslatef(0,0,-4.0);
    glBindTexture(GL_TEXTURE_2D,11);
    glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    ///back-right
    // glColor3f(0.1, 0.1, 0.1);
    glTranslatef(20,0,0.0);
    glBindTexture(GL_TEXTURE_2D,11);
    glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    ///front-right
    // glColor3f(0.1, 0.1, 0.1);
    glTranslatef(0,0,4.0);
    glBindTexture(GL_TEXTURE_2D,11);
    glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);


    glPopMatrix();



}


void table2()
{
    glPushMatrix();
    ///table surface
    //glColor3f(0,0.5,0);
    glTranslatef(0,0.0,0.0);
    glScalef(3.0, .1, 4.0);
    set_material(table_top_mat_color, table_mat_spec, table_mat_shininess);
   // glBindTexture(GL_TEXTURE_2D,11);
    //glEnable(GL_TEXTURE_2D);
    cube();
    //glDisable(GL_TEXTURE_2D);
    ///front-left
    //glColor3f(0.1, 0.1, 0.1);
    glScalef(1/3.0, 1/0.1, 1/4.0);
    glScalef(.2, 0.9, 0.4);
    glTranslatef(0.0,-1.11,0.0);
    glTranslatef(-10.0,0,2.0);
    set_material(table_mat_color, table_mat_spec, table_mat_shininess);

   // glBindTexture(GL_TEXTURE_2D,11);
   // glEnable(GL_TEXTURE_2D);
    cube();
   // glDisable(GL_TEXTURE_2D);
    ///back-left
    //glColor3f(0.1, 0.1, 0.1);
    glTranslatef(0,0,-4.0);
    //glBindTexture(GL_TEXTURE_2D,11);
   // glEnable(GL_TEXTURE_2D);
    cube();
  //  glDisable(GL_TEXTURE_2D);
    ///back-right
    // glColor3f(0.1, 0.1, 0.1);
    glTranslatef(20,0,0.0);
    //glBindTexture(GL_TEXTURE_2D,11);
    //glEnable(GL_TEXTURE_2D);
    cube();
    //glDisable(GL_TEXTURE_2D);
    ///front-right
    // glColor3f(0.1, 0.1, 0.1);
    glTranslatef(0,0,4.0);
    //glBindTexture(GL_TEXTURE_2D,11);
    //glEnable(GL_TEXTURE_2D);
    cube();
  //  glDisable(GL_TEXTURE_2D);


    glPopMatrix();



}






void single_piece()
{

    glPushMatrix();
    //glColor3f(0.2, 0.2, 0.2);
    glScalef(0.3, 2.0, 0.3);
    glutSolidSphere(0.5, 500, 500);
    glScalef(1/0.3, 1/2.0, 1/0.3);
    glTranslatef(0.0, -1.0, 0);
    glutSolidSphere(0.15, 500, 500);
    glTranslatef(0.0, 2.0, 0);
    glutSolidSphere(0.15, 500, 500);
    glPopMatrix();
}


void jack()
{
    set_material(jack_mat_color, jack_mat_spec, jack_mat_shininess);
    for (int i=0; i<3; i++)
    {
        glPushMatrix();
        glRotated(i*120, 0, 1, 0);
        glRotated(40, 1, 0, 0);
        single_piece();
        glPopMatrix();
    }
    for (int i=0; i<3; i++)
    {
        glPushMatrix();
        glRotated(i*120, 0, 1, 0);
        glRotated(40, 1, 0, 0);
        single_piece();
        glPopMatrix();
    }
    for (int i=0; i<3; i++)
    {
        glPushMatrix();
        glRotated(i*120, 0, 1, 0);
        glRotated(40, 1, 0, 0);
        single_piece();
        glPopMatrix();
    }

}

void room()
{
    wall();
    table();
    glScalef(0.7, 0.7, 0.7);
    glTranslatef(-2.0, 1.01, 1.0);
    jack();
    glColor3f(0.1, 0.1, 0.1);

}


void room2()
{
    wall2();
    table2();
    glScalef(0.7, 0.7, 0.7);
    glTranslatef(-2.0, 1.01, 1.0);
    jack();
    glColor3f(0.1, 0.1, 0.1);

}


static GLfloat tsquare_bg_mat_color[] = { 1, 1, 1, 1 };
static GLfloat tsquare_bg_mat_spec[] = { 0, 0, 0, 1 };
static GLfloat tsquare_bg_mat_shininess[] = { 120 };

static GLfloat tsquare_mat_color[] = { 0, 0, 0, 1 };
static GLfloat tsquare_mat_spec[] = { 1, 1, 1, 1 };
static GLfloat tsquare_mat_shininess[] = { 120 };

static void _tsquare_recursive(int level, GLdouble t, GLdouble b, GLdouble l, GLdouble r)
{
    glVertex3d(l, t, 0.01);        /// left top vertex
    glVertex3d(l, b, 0.01);        /// left bottom vertex
    glVertex3d(r, b, 0.01);        /// right bottom vertex
    glVertex3d(r, t, 0.01);        /// right top vertex

    if (level <= 0)
        return;

    GLdouble hBy4 = (t-b)/4.0;
    GLdouble wBy4 = (r-l)/4.0;

    GLdouble x[2] = {l,r};
    GLdouble y[2] = {b,t};

    for (int i=0; i<2; i++)
    {
        for (int j=0; j<2; j++)
        {
            _tsquare_recursive(level-1, y[i]+hBy4, y[i]-hBy4, x[j]-wBy4, x[j]+wBy4);
        }
    }
}



static void tsquare(int level)
{
    set_material(tsquare_bg_mat_color, tsquare_bg_mat_spec, tsquare_bg_mat_shininess);

    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glVertex3f(-0.5, -0.5, 0);
        glVertex3f(0.5, -0.5, 0);
        glVertex3f(0.5, 0.5, 0);
        glVertex3f(-0.5, 0.5, 0);

    glEnd();

    set_material(tsquare_mat_color, tsquare_mat_spec, tsquare_mat_shininess);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        _tsquare_recursive(level, 0.2, -0.2, -0.3, 0.3);
    glEnd();
}



static void display(void)
{
    set_lights();
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;

//

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

//    glViewport(0,0, width/2,height);
//
//    glPushMatrix();
//    //glTranslated(0, 0, -30);
//    //glScaled(3, 3, 3);
//    glTranslated(x_co+0,y_co+0,z_co+-30);
//    //glScaled(M+3,M+3,M+3);
//    owns(M+3,M+3,M+3);
//    glRotated(rx, 1, 0, 0);
//    glRotated(ry, 0, 1, 0);
//    glRotated(rz, 0, 0, 1);
//    room2();
//    glScalef(0.5, 0.5, 0.5);
//    glTranslatef(6.0, 1.5, 0);
//    fireman();
//    glScalef(1/0.5, 1/0.5, 1/0.5);
//
//    glPopMatrix();
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    gluLookAt(ex,ey,ez,cx,cy,cz,hx,hy,hz);



   glViewport(0,0, width, height);

    glPushMatrix();


    //glTranslated(0, 0, -30);
    //glScaled(3, 3, 3);
    glTranslated(x_co+0,y_co+0,z_co+-30);
    //glScaled(M+3,M+3,M+3);
    owns(M+3,M+3,M+3);
    glRotated(rx, 1, 0, 0);
    glRotated(ry, 0, 1, 0);
    glRotated(rz, 0, 0, 1);
    room();

    glPushMatrix();
            glTranslated(-3.3,1.5,-3);
            glRotated(90,0,1,0);
            glScaled(5,5,5);
            tsquare(Depth);
    glPopMatrix();

    glScalef(0.5, 0.5, 0.5);
    glTranslatef(6.0, 1.5, 0);
    fireman();
    glScalef(1/0.5, 1/0.5, 1/0.5);

    glPopMatrix();


glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(ex,ey,ez,cx,cy,cz,hx,hy,hz);


    glutSwapBuffers();
}
float angle=0.0,tmp1,tmp2,tmp3;
// dif=abs(cy-0)
// int ck=0;
static void key(unsigned char key, int mouse_x, int mouse_y)
{
    switch (key)
    {
    case 'x':
        rx += 5;
        break;
    case 'y':
        ry += 5;
        break;
    case 'z':
        rz += 5;
        break;
    case 'X':
        rx -= 5;
        break;
    case 'Y':
        ry -= 5;
        break;
    case 'Z':
        rz -= 5;
        break;
    case 'M': //zoom in
        M+=0.05;
        break;
    case 'm': //zoom out
        M-=0.05;
        break;
    case '1': //1 2 3 for transformation in x y z axis
        x_co+=0.1;
        break;
    case '2':
        y_co+=0.1;
        break;
    case '3':
        z_co+=0.1;
        break;
    case '4': //4 5 6 for transformation in -x -y -z axis
        x_co-=0.1;
        break;
    case '5':
        y_co-=0.1;
        break;
    case '6':
        z_co-=0.1;
        break;
    case '\b':
        rx = 0;
        ry = 0;
        rz = 0;
        break;
    case 'a':
        ex-=.1;
        break;
    case 'A':
        ex+=.1;
        break;

    case 's':
        ey-=.1;
        break;
    case 'S':
        ey+=.1;
        break;

    case 'd':
        ez-=.1;
        break;
    case 'D':
        ez+=.1;
        break;

    case 'f':
        cx-=.1;
        break;
    case 'F':
        cx+=.1;
        break;

    case 'g':
        cy-=.1;
        break;
    case 'G':
        cy+=.1;
        break;

    case 'h':
        cz-=1;
        break;
    case 'H':
        cz+=1;
        break;

    case 'j':
        hx-=.1;
        break;
    case 'J':
        hx+=.1;
        break;

    case 'k':
        hy-=.1;
        break;
    case 'K':
        hy+=.1;
        break;

    case 'l':
        hz-=.1;
        break;

    case 'L':
        hz+=.1;
        break;
    case 'p': //rotate all around
        angle-=.1;
        ex=10*sin(angle);
        ez=10*cos(angle);
        break;
    case 'o': //roll
        angle-=.1;
        //hx=sin(angle);
        //hy=cos(angle);
        hx=0*cos(angle)-1*sin(angle);
        hz=0*sin(angle)+1*cos(angle);
        break;
    case 'O': //roll
        angle+=.1;
        //hx=sin(angle);
        //hy=cos(angle);
        hx=0*cos(angle)-1*sin(angle);
        hz=0*sin(angle)+1*cos(angle);
        break;
    case 'i': //pitch
        angle-=.1;
        //cy=sin(angle);
        //cy=sin(angle)+cos(angle);
        cy=0*cos(angle)-1*sin(angle);
        cz=0*sin(angle)+1*cos(angle);
        // cz=
//            angle-=.1;
//            cx=sin(angle);
//            cz=cos(angle);
        break;

    case 'I': //pitch
        angle+=.1;
        //cy=sin(angle);
        //cy=sin(angle)+cos(angle);
        cy=0*cos(angle)-1*sin(angle);
        cz=0*sin(angle)+1*cos(angle);
        break;
    case 'u': //yaw
        angle-=.1;
        //cx=sin(angle);
        //cz=cos(angle);
        cx=cos(angle)+sin(angle);
        cz=-sin(angle)+cos(angle);
        break;
    case 'U': //yaw
        angle+=.1;
        //cx=sin(angle);
        //cz=cos(angle);
        cx=cos(angle)+sin(angle);
        cz=-sin(angle)+cos(angle);
        break;
    case 't':
        tmp1=cx-ex;
        tmp2=cy-ey;
        tmp3=cz-ez;
        ex+=tmp1/15;
        ey+=tmp2/15;
        ez+=tmp3/15;
        break;
    case 'T':
        tmp1=cx-ex;
        tmp2=cy-ey;
        tmp3=cz-ez;
        ex-=tmp1/15;
        ey-=tmp2/15;
        ez-=tmp3/15;
        break;
    case 'w':
        glEnable(GL_LIGHT0);
        break;
    case 'W':
        glDisable(GL_LIGHT0);
        break;

    case 'n':
        glEnable(GL_LIGHT1);
        break;
    case 'N':
        glDisable(GL_LIGHT1);
        break;

    case '7' :
            Depth += 1;
            break;
    case '8':
            Depth += -1;
            break;

    case 27 :
    case 'q':
        exit(0);
        break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */
void Init()
{
    pix[0].readBMPFile("G:\\pic\\wall2.bmp");
    pix[0].setTexture(10);

    pix[1].readBMPFile("G:\\pic\\wood.bmp");
    pix[1].setTexture(11);

    pix[2].readBMPFile("G:\\pic\\floor.bmp");
    pix[2].setTexture(12);

    pix[3].readBMPFile("G:\\pic\\sunset.bmp");
    pix[3].setTexture(13);

    pix[4].readBMPFile("G:\\pic\\ab.bmp");
    pix[4].setTexture(14);


}
int main(int argc, char *argv[])
{
    circleInit();

    glutInit(&argc, argv);
    glutInitWindowSize(1040,780);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    Init();

    glutMainLoop();

    return EXIT_SUCCESS;
}

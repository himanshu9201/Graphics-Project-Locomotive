/*
 *  Textures and Lighting
 *
 *  Demonstrates using lighting and textures.
 *
 *  Key bindings:
 *  l          Toggle lighting on/off
 *  t          Change textures
 *  m          Toggles texture mode modulate/replace
 *  a/A        decrease/increase ambient light
 *  d/D        decrease/increase diffuse light
 *  s/S        decrease/increase specular light
 *  e/E        decrease/increase emitted light
 *  n/N        Decrease/increase shininess
 *  []         Lower/rise light
 *  x          Toggle axes
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif


int mode=0;       //  Texture mode
int ntex=0;       //  Cube faces
int axes=1;       //  Display axes
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int light=1;      //  Lighting
int rep=1;        //  Repitition
double asp=1;     //  Aspect ratio
double dim=20.0;   //  Size of world
// Light values
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 45;  // Diffuse intensity (%)
int specular  =  10;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;    // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light
unsigned int texture[24]; // Texture names
int inc       =  10;  // Ball increment
float lxpos = 0;
float lzpos = 0;
double speed = 1;
double mytime;
int day = 1;



/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimentions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Enable textures
  // glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
  // glColor3f(1,1,1);

   //  Front


   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
   glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
   glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
   glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
   glEnd();


   //  Back


   glBegin(GL_QUADS);
   glNormal3f( 0, 0,-1);
   glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
   glEnd();
   //  Right


   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
   glEnd();
   //  Left


   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();
   //  Top


   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();
   //  Bottom


   glBegin(GL_QUADS);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
   glEnd();
   //  Undo transformations and textures
   glPopMatrix();
   //glDisable(GL_TEXTURE_2D);
}

static void cube2(double x,double y,double z,
                 double dx,double dy,double dz,
                 double rx, double ry, double rz)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(rx,1,0,0);
   glRotated(ry,0,1,0);
   glRotated(rz,0,0,1);
   glScaled(dx,dy,dz);
   //  Enable textures
  // glEnable(GL_TEXTURE_2D);
   //glDisable(GL_TEXTURE_2D);
  // glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   //glColor3f(1,1,1);

   //  Front


   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,0); glVertex3f(0,0, 1);
   glTexCoord2f(1,0); glVertex3f(1,0, 1);
   glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
   glTexCoord2f(0,1); glVertex3f(0,1, 1);
   glEnd();
   //  Back


   glBegin(GL_QUADS);
   glNormal3f( 0, 0,-1);
   glTexCoord2f(0,0); glVertex3f(0,0,0);
   glTexCoord2f(1,0); glVertex3f(0,1,0);
   glTexCoord2f(1,1); glVertex3f(1,+1,0);
   glTexCoord2f(0,1); glVertex3f(+1,0,0);
   glEnd();
   //  Right


   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+1,0,0);
   glTexCoord2f(1,0); glVertex3f(+1,0,1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,1);
   glTexCoord2f(0,1); glVertex3f(1,+1,0);
   glEnd();
   //  Left


   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(0,0,0);
   glTexCoord2f(1,0); glVertex3f(0,0,+1);
   glTexCoord2f(1,1); glVertex3f(0,+1,+1);
   glTexCoord2f(0,1); glVertex3f(0,+1,0);
   glEnd();
   //  Top


   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0); glVertex3f(0,+1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,0);
   glTexCoord2f(0,1); glVertex3f(0,+1,0);
   glEnd();
   //  Bottom


   glBegin(GL_QUADS);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(0,0); glVertex3f(0,0,0);
   glTexCoord2f(1,0); glVertex3f(+1,0,0);
   glTexCoord2f(1,1); glVertex3f(+1,0,+1);
   glTexCoord2f(0,1); glVertex3f(0,0,+1);
   glEnd();
   //  Undo transformations and textures
   glPopMatrix();
   //glDisable(GL_TEXTURE_2D);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius r
 */
static void ball(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,0,0);
   glutSolidSphere(1.0,16,16);
   //  Undo transofrmations
   glPopMatrix();
}

static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}
static void smokeball(double x,double y,double z,double r)
{
   const int d=5;
   int th,ph;

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(r,r,r);

   //  Latitude bands

   for (ph=-90;ph<90;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=d)
      {
         Vertex(th,ph);
         Vertex(th,ph+d);
      }
      glEnd();
   }

   //  Undo transformations
   glPopMatrix();
}

static void dosmoke(){
glDisable(GL_TEXTURE_2D);
  glPushMatrix();
  //put our translation vars here
  double l = 1.8* fmod(mytime*speed, 4.0);
  double h = fmod(mytime*speed, 4.0);
  double s = .2* fmod(mytime*speed, 4.0);
  glEnable(GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glTranslated(0, h, -l);

  glColor4f(0.4, 0.4, 0.4, 1.0 - 0.05*h);
  smokeball(0, 10.5, 17.5, 1.0+s);
  glColor4f(0.4, 0.4, 0.4, 0.8 - 0.05*h);
  smokeball(0, 14.5, 10.3, 1.8+s);
  glColor4f(0.4, 0.4, 0.4, 0.6-0.05*h);
  smokeball(0, 18.5, 3.1, 2.6+s);
  glColor4f(0.4, 0.4, 0.4, 0.4 - 0.05 * h);
  smokeball(0, 22.5, -4.1, 3.4+s);
  glColor4f(0.4, 0.4, 0.4, 0.2 - 0.05 * h);
  smokeball(0, 26.5, -11.3, 4.2+s);

  glDisable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);

  glPopMatrix();

}

/*
static void Vertexinv(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(-x,-y,-z);
   glTexCoord2d(th/360.0, ph/180.0+0.5);
   glVertex3d(x,y,z);
} */

//draw vertex in cylindrical coords (h is the y value)
static void Vertexcyl(double th, double h)
{
    glNormal3d(Sin(th), 0, Cos(th));
	//only safe because h is either 0 or 1
	glTexCoord2d(th/360.0, h);
	glVertex3d(Sin(th), h , Cos(th));

}

static void Vertexcylinv(double th, double h)
{
    glNormal3d(-Sin(th), 0, -Cos(th));
	//only safe because h is either 0 or 1
	glTexCoord2d(th/360.0, h);
	glVertex3d(Sin(th), h , Cos(th));

}

//used for generating end caps to cylinders
static void Vertexcylnonormal(double th, double h)
{
	//set texture such that cos(0) ends up as 1, and cos(180) = 0, ie right and left
	//edges of circle are right and left edges of texture
    glTexCoord2d(0.5*Cos(th)+0.5, 0.5*Sin(th)+0.5);
	glVertex3d(Sin(th), h , Cos(th));

}

static void Vertexrim(double th, double h, double r)
{
	//set texture such that cos(0) ends up as 1, and cos(180) = 0, ie right and left
	//edges of circle are right and left edges of texture
    glTexCoord2d(0.5*Cos(th)+0.5, 0.5*Sin(th)+0.5);
	glVertex3d(r*Sin(th), h , r*Cos(th));

}


static void cylnocap(double x, double y, double z, double r, double h){

     const int d=5;
     int th;
        float white[] = {1,1,1,1};
     float black[] = {0,0,0,1};
     glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
     glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
     glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

     //  Save transformation
     glPushMatrix();
     //  Offset and scale
     glTranslated(x,y,z);
     glScaled(r,h,r);

     //  make a tube
        glBegin(GL_QUAD_STRIP);
        for (th=0;th<=360;th+=d)
        {
  		  //points at top and bottom
           Vertexcyl(th, 0);
           Vertexcyl(th, 1);
        }
        glEnd();

     //bottom cap

     //  Undo transformations
     glPopMatrix();

}

static void cylnocapinv(double x, double y, double z, double r, double h){

     const int d=5;
     int th;
        float white[] = {1,1,1,1};
     float black[] = {0,0,0,1};
     glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
     glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
     glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

     //  Save transformation
     glPushMatrix();
     //  Offset and scale
     glTranslated(x,y,z);
     glScaled(r,h,r);

     //  make a tube
        glBegin(GL_QUAD_STRIP);
        for (th=0;th<=360;th+=d)
        {
  		  //points at top and bottom
           Vertexcylinv(th, 0);
           Vertexcylinv(th, 1);
        }
        glEnd();

     //bottom cap

     //  Undo transformations
     glPopMatrix();

}





static void TriPrism(double x, double y, double z, double l, double h, double w, double rx, double ry, double rz)
{
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
	glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glRotated(rx, 1, 0, 0);
   glRotated(ry, 0, 1, 0);
   glRotated(rz, 0, 0, 1);
   glScaled(l,h,w);
   //glEnable(GL_TEXTURE_2D);

   glBegin(GL_QUADS);
   //bottom
   glNormal3f(0, -1, 0);
   //glColor3f(1, 0, 0);
   glTexCoord2d(0,0); glVertex3f(0, 0, 0);
   glTexCoord2d(1,0); glVertex3f(1, 0, 0);
   glTexCoord2d(1,1); glVertex3f(1, 0, 1);
   glTexCoord2d(0,1); glVertex3f(0, 0, 1);
   //vertical normal in -z
   glNormal3f(0, 0, -1);
  // glColor3f(0, 1, 0);
   glTexCoord2d(0,1); glVertex3f(0, 0, 0);
   glTexCoord2d(1,1); glVertex3f(1, 0, 0);
   glTexCoord2d(1,0); glVertex3f(1, 1, 0);
   glTexCoord2d(0,0); glVertex3f(0, 1, 0);

   //hypotenuse
   glNormal3f(0, 1, 1);
   //glColor3f(0, 0, 1);
   glTexCoord2d(0,1); glVertex3f(0, 1, 0);
   glTexCoord2d(1,1); glVertex3f(1, 1, 0);
   glTexCoord2d(1,0); glVertex3f(1, 0, 1);
   glTexCoord2d(0,0); glVertex3f(0, 0, 1);

   glEnd();
   glBegin(GL_TRIANGLES);
   //left cap
   glNormal3f(-1, 0, 0);

  // glColor3f(1, 1, 0);
   glTexCoord2d(1,0); glVertex3f(0, 0, 0);
   glTexCoord2d(1,1); glVertex3f(0, 1, 0);
   glTexCoord2d(0,0); glVertex3f(0, 0, 1);

   //right cap
   glNormal3f(1, 0, 0);
 //  glColor3f(0, 1, 1);

   glTexCoord2d(1,0); glVertex3f(1, 0, 0);
   glTexCoord2d(1,1); glVertex3f(1, 1, 0);
   glTexCoord2d(0,0); glVertex3f(1, 0, 1);

   glEnd();

   glPopMatrix();
}



static void skybox(double x,double y,double z,double r)
{


  //int th,ph;
  //float yellow[] = {1.0,1.0,0.0,1.0};

  /*
  texture[7] = LoadTexBMP("SBack.bmp");
  texture[8] = LoadTexBMP("SDown.bmp");
  texture[9] = LoadTexBMP("SFront.bmp");
  texture[10] = LoadTexBMP("SLeft.bmp");
  texture[11] = LoadTexBMP("SRight.bmp");
  texture[12] = LoadTexBMP("SUp.bmp");
  texture[13] = LoadTexBMP("wood2.bmp");
  texture[14] = LoadTexBMP("gold.bmp");
  texture[15] = LoadTexBMP("grass.bmp");
  texture[16] = LoadTexBMP("bark.bmp");
  texture[17] = LoadTexBMP("pine.bmp");
  texture[18] = LoadTexBMP("NBack.bmp");
  texture[19] = LoadTexBMP("NDown.bmp");
  texture[20] = LoadTexBMP("NFront.bmp");
  texture[21] = LoadTexBMP("NLeft.bmp");
  texture[22] = LoadTexBMP("NRight.bmp");
  texture[23] = LoadTexBMP("NUp.bmp");
  */
  //float Emission[]  = {0.0,0.0,0.01*emission,1.0};
  //  Save transformation
  glPushMatrix();
  glDisable(GL_LIGHTING);
  //  Offset, scale and rotate
  glTranslated(x,y,z);
  //glRotated(-90, 1, 0, 0);
  glScaled(r,r,r);

  glEnable(GL_TEXTURE_2D);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glDisable(GL_POLYGON_SMOOTH);
glColor3f(1,1,1);
  glBindTexture(GL_TEXTURE_2D, day ? texture[9] : texture[20]);

  //  Front
  glBegin(GL_QUADS);
  glNormal3f( 0, 0, -1);
  glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
  glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
  glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
  glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
  glEnd();



  //  Back
glBindTexture(GL_TEXTURE_2D, day ? texture[7] : texture[18]);
glBegin(GL_QUADS);
glNormal3f( 0, 0,1);
glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
glEnd();



  //  Right
glBindTexture(GL_TEXTURE_2D, day ? texture[10] : texture[21]);
glBegin(GL_QUADS);
glNormal3f(-1, 0, 0);
glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
glEnd();


  //  Left
glBindTexture(GL_TEXTURE_2D, day ? texture[11] : texture[22]);
glBegin(GL_QUADS);
glNormal3f(1, 0, 0);
glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
glEnd();


  //  Top
glBindTexture(GL_TEXTURE_2D, day ? texture[12] : texture[23] );
glBegin(GL_QUADS);
glNormal3f( 0,-1, 0);
glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
glEnd();


  //  Bottom
glBindTexture(GL_TEXTURE_2D, day ? texture[8] : texture[19]);
glBegin(GL_QUADS);
glNormal3f( 0, 1, 0);
glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
glEnd();

glDisable(GL_TEXTURE_2D);
  //  Undo transformations and textures
  glPopMatrix();
  glEnable(GL_LIGHTING);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glEnable(GL_POLYGON_SMOOTH);
/*
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(-90, 1, 0, 0);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texture[7]);
   //  Bands of latitude
   for (ph=-90;ph<90;ph+=5)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=5)
      {
         Vertexinv(th,ph);
         Vertexinv(th,ph+5);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix(); */
}


static void cylinder(double x,double y,double z,double r, double h, double ang, double rx, double ry, double rz)
{
   const int d=5;
   int th;
      float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glRotated(ang, rx, ry, rz);
   glScaled(r,h,r);
  // glColor3f(1, 1, 1);

   //  make a tube
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=d)
      {
		  //points at top and bottom
         Vertexcyl(th, 0);
         Vertexcyl(th, 1);
      }
      glEnd();

   //bottom cap
    glNormal3d(0, -1, 0);
	glBegin(GL_TRIANGLE_FAN);

		glTexCoord2d(0.5, 0.5); glVertex3f(0, 0, 0);
      for (th=0;th<=360;th+=d)
      {
         Vertexcylnonormal(th, 0);
      }
      glEnd();
	  //top cap
	    glNormal3d(0, 1, 0);
	  	glBegin(GL_TRIANGLE_FAN);

		//put center point of texture at center of fan
		glTexCoord2d(0.5, 0.5); glVertex3f(0, 1, 0);
      for (th=0;th<=360;th+=d)
      {

		  //points at top and bottom
         Vertexcylnonormal(th, 1);
      }
      glEnd();
   //  Undo transformations
   glPopMatrix();
}

static void lightcone(double x,double y,double z,double r, double h, double rx, double ry, double rz)
{
   const int d=1;
   float shiny[] = {16};
   float yellow[] = {1.0, 1.0, 0.0, 1.0};
   float black[] = {0,0,0,1};
    float white[] = {1,1,1,1};
   //glColor3f(1,1,1);
   glMaterialfv(GL_FRONT, GL_SHININESS, shiny);
   glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   int th;

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glRotated(rx, 1, 0, 0);
   glRotated(ry, 0, 1, 0);
   glRotated(rz, 0, 0, 1);
   glScaled(r,h,r);
   glBegin(GL_TRIANGLES);
   //glColor3f(1, 1, 0);
   //glVertex3f(0, 1, 0);
   for (th=0;th<=360;th+=2*d)
   {
	   //bottom left of a cone triangle
	   //currently texture just wraps around cone like a cylinder
	   //commented out texture maps either do it like a cylinder cap (I had problems with pixelation where
	   //there should be none) or having each triangle be a section of texture
	   //the current one looked best in spite of its weirdness so that's what i went with.
		 glNormal3d(Cos(th-d), 1, Sin(th-d));
		 glTexCoord2d((th-d)/360.0, 0);
		 //glTexCoord2d(0, 0);
		 //glTexCoord2d(0.5*Cos(th)+0.5, 0.5*Sin(th)+0.5);
		 glVertex3d(Cos(th-d), 0, Sin(th-d));

		 //tip of cone
		 glNormal3d(Cos(th), 1, Sin(th));
		 //tip of cone is set to center of texture
		 //glTexCoord2d(0.5, 0.5);
		 glTexCoord2d(th/360.0, 1);
		 //glTexCoord2d(0.5,1);
		 glVertex3d(0*Cos(th), 1, 0*Sin(th));

		 //bottom right of cone triangle
		 glNormal3d(Cos(th+d), 1, Sin(th+d));
		 //glTexCoord2d(1, 0);
		 //glTexCoord2d(0.5*Cos(th)+0.5, 0.5*Sin(th)+0.5);
		 glTexCoord2d((th+d)/360.0, 0);
		 glVertex3d(Cos(th+d), 0, Sin(th+d));

   }

      glEnd();
      //bottom cap reversed so it 'glows'
      glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, white);
       glNormal3d(0, 1, 0);
       glColor3f(1,1,1);
       glDisable(GL_TEXTURE_2D);
     glBegin(GL_TRIANGLE_FAN);

       glTexCoord2d(0.5, 0.5); glVertex3f(0, 0, 0);
         for (th=0;th<=360;th+=d)
         {
            Vertexcylnonormal(th, 0);
         }
         glEnd();
         glEnable(GL_TEXTURE_2D);
         glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
	  glPopMatrix();
}

static void cone(double x,double y,double z,double r, double h, double rx, double ry, double rz)
{
   const int d=1;
   float shiny[] = {16};
   float yellow[] = {1.0, 1.0, 0.0, 1.0};
   //glColor3f(1,1,1);
   glMaterialfv(GL_FRONT, GL_SHININESS, shiny);
   glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
   int th;

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glRotated(rx, 1, 0, 0);
   glRotated(ry, 0, 1, 0);
   glRotated(rz, 0, 0, 1);
   glScaled(r,h,r);
   glBegin(GL_TRIANGLES);
   //glColor3f(1, 1, 0);
   //glVertex3f(0, 1, 0);
   for (th=0;th<=360;th+=2*d)
   {
	   //bottom left of a cone triangle
	   //currently texture just wraps around cone like a cylinder
	   //commented out texture maps either do it like a cylinder cap (I had problems with pixelation where
	   //there should be none) or having each triangle be a section of texture
	   //the current one looked best in spite of its weirdness so that's what i went with.
		 glNormal3d(Cos(th-d), 1, Sin(th-d));
		 glTexCoord2d((th-d)/360.0, 0);
		 //glTexCoord2d(0, 0);
		 //glTexCoord2d(0.5*Cos(th)+0.5, 0.5*Sin(th)+0.5);
		 glVertex3d(Cos(th-d), 0, Sin(th-d));

		 //tip of cone
		 glNormal3d(Cos(th), 1, Sin(th));
		 //tip of cone is set to center of texture
		 //glTexCoord2d(0.5, 0.5);
		 glTexCoord2d(th/360.0, 1);
		 //glTexCoord2d(0.5,1);
		 glVertex3d(0*Cos(th), 1, 0*Sin(th));

		 //bottom right of cone triangle
		 glNormal3d(Cos(th+d), 1, Sin(th+d));
		 //glTexCoord2d(1, 0);
		 //glTexCoord2d(0.5*Cos(th)+0.5, 0.5*Sin(th)+0.5);
		 glTexCoord2d((th+d)/360.0, 0);
		 glVertex3d(Cos(th+d), 0, Sin(th+d));

   }

      glEnd();
      //bottom cap
       glNormal3d(0, -1, 0);
     glBegin(GL_TRIANGLE_FAN);

       glTexCoord2d(0.5, 0.5); glVertex3f(0, 0, 0);
         for (th=0;th<=360;th+=d)
         {
            Vertexcylnonormal(th, 0);
         }
         glEnd();
	  glPopMatrix();
}

static void treecone(double x,double y,double z,double r, double h, double rx, double ry, double rz)
{
   const int d=15;
   float shiny[] = {16};
   float yellow[] = {1.0, 1.0, 0.0, 1.0};
   //glColor3f(1,1,1);
   glMaterialfv(GL_FRONT, GL_SHININESS, shiny);
   glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
   int th;

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glRotated(rx, 1, 0, 0);
   glRotated(ry, 0, 1, 0);
   glRotated(rz, 0, 0, 1);
   glScaled(r,h,r);
   glBegin(GL_TRIANGLES);
   //glColor3f(1, 1, 0);
   //glVertex3f(0, 1, 0);
   for (th=0;th<=360;th+=2*d)
   {
	   //bottom left of a cone triangle
	   //currently texture just wraps around cone like a cylinder
	   //commented out texture maps either do it like a cylinder cap (I had problems with pixelation where
	   //there should be none) or having each triangle be a section of texture
	   //the current one looked best in spite of its weirdness so that's what i went with.
		 glNormal3d(Cos(th-d), 1, Sin(th-d));
		 glTexCoord2d((th-d)/360.0, 0);
		 //glTexCoord2d(0, 0);
		 //glTexCoord2d(0.5*Cos(th)+0.5, 0.5*Sin(th)+0.5);
		 glVertex3d(Cos(th-d), 0, Sin(th-d));

		 //tip of cone
		 glNormal3d(Cos(th), 1, Sin(th));
		 //tip of cone is set to center of texture
		 //glTexCoord2d(0.5, 0.5);
		 glTexCoord2d(th/360.0, 1);
		 //glTexCoord2d(0.5,1);
		 glVertex3d(0*Cos(th), 1, 0*Sin(th));

		 //bottom right of cone triangle
		 glNormal3d(Cos(th+d), 1, Sin(th+d));
		 //glTexCoord2d(1, 0);
		 //glTexCoord2d(0.5*Cos(th)+0.5, 0.5*Sin(th)+0.5);
		 glTexCoord2d((th+d)/360.0, 0);
		 glVertex3d(Cos(th+d), 0, Sin(th+d));

   }

      glEnd();
      //bottom cap
       glNormal3d(0, -1, 0);
     glBegin(GL_TRIANGLE_FAN);

       glTexCoord2d(0.5, 0.5); glVertex3f(0, 0, 0);
         for (th=0;th<=360;th+=d)
         {
            Vertexcylnonormal(th, 0);
         }
         glEnd();
	  glPopMatrix();
}

static void wheelrim(double x, double y, double z, double r){

int theta = 0;
glPushMatrix();
glTranslated(x, y, z);
glScaled(r, 1, r);

cylnocap(0, 0, 0, 1, .25);
cylnocapinv(0, 0, 0, .8, .25);

//top
glBegin(GL_QUAD_STRIP);
glNormal3f(0, 1, 0);
for (theta = 0; theta <= 360; theta += 5){
Vertexrim(theta, .25, 1);
Vertexrim(theta, .25, .8);
}
glEnd();
//bottom
glBegin(GL_QUAD_STRIP);
glNormal3f(0, -1, 0);
for (theta = 0; theta <= 360; theta += 5){
Vertexrim(theta, 0, 1);
Vertexrim(theta, 0, .8);
}

glEnd();
glPopMatrix();

}


//makes a circle of cylinders that lie along radius
static void wheelspokes(double x, double y, double z, double r){

  double theta = 0;
  glPushMatrix();
  glTranslated(x, y, z);
  glScaled(r, 1, r);

  for(theta = 0; theta <360; theta += 22.5){
  cylinder(0,.125,0, .0625, .9, 90, Cos(theta), 0, Sin(theta));

}
  //rotated around y axis,

  glPopMatrix();
}

static void wheel(double x, double y, double z, double r,double h, double theta, double rx, double ry, double rz ){
  //glMaterialfv
  //glMaterialfv
  glPushMatrix();

  glTranslated(x, y, z);
  glRotated(theta, rx, ry, rz);
  glScaled(r, h, r);

  glBindTexture(GL_TEXTURE_2D, texture[13]);
  glColor3f(0, 0, 0);

  wheelrim(0, 0, 0, 1);
  glColor3f(1, 0, 0);
  wheelspokes(0, 0, 0, 1);
  glColor3f(1, 0, 0);
  cylinder(0, 0, 0, 0.4, .25, 0, 0, 0, 0);

  glBindTexture(GL_TEXTURE_2D, texture[6]);
  glColor3f(0.5, 0.5, 0.5);
  cylinder(.3, 0, 0, .05, 1, 0, 0, 0, 0);


glPopMatrix();

}

static void rail(double x, double y, double z){

  glPushMatrix();
  glTranslated(x, y, z);
//  glDisable(GL_TEXTURE_2D);
  //x y z dx dy dz th
  //these two are going to be the main rails
  glBindTexture(GL_TEXTURE_2D, texture[3]);
  glColor3f(1, 1,1);

  cube(-2.8, -2.125, 7, .125, .125, 3.1415926/2, 0);
  cube(2.8, -2.125, 7, .125, .125, 3.1415926/2, 0);
  //now we make our ties underneath
  glBindTexture(GL_TEXTURE_2D, texture[5]);
    cube(0, -2.5, 7, 3.25, .25, .5, 0);
  /*cube(0, -2.5, 10, 3.25, .25, .5, 0);
  cube(0, -2.5, 13, 3.25, .25, .5, 0);
  cube(0, -2.5, 16, 3.25, .25, .5, 0);
  cube(0, -2.5, 19, 3.25, .25, .5, 0);
  cube(0, -2.5, 22, 3.25, .25, .5, 0);
  cube(0, -2.5, 25, 3.25, .25, .5, 0);
  cube(0, -2.5, 4, 3.25, .25, .5, 0);
  cube(0, -2.5, 1, 3.25, .25, .5, 0);
  cube(0, -2.5, -2, 3.25, .25, .5, 0);
  cube(0, -2.5, -5, 3.25, .25, .5, 0);
  cube(0, -2.5, -8, 3.25, .25, .5, 0);
*/

  glPopMatrix();

}

static void rails(double x, double y, double z){

glPushMatrix();
glTranslated(x, y, z);
//rail(-8, 0, 0);

for(double x = -320; x < 320; x += 3.1415926 ){
  rail(0, 0, x);
}

glPopMatrix();

}

//wheel without drive rod. for small wheels
static void wheel2(double x, double y, double z, double r,double h, double theta, double rx, double ry, double rz ){
  //glMaterialfv
  //glMaterialfv
  glPushMatrix();

  glTranslated(x, y, z);
  glRotated(theta, rx, ry, rz);
  glScaled(r, h, r);
glBindTexture(GL_TEXTURE_2D, texture[13]);
glColor3f(0, 0, 0);
  wheelrim(0, 0, 0, 1);
  glBindTexture(GL_TEXTURE_2D, texture[13]);
  glColor3f(1, 0, 0);
  wheelspokes(0, 0, 0, 1);
  cylinder(0, 0, 0, 0.4, .25, 0, 0, 0, 0);
  //cylinder(.3, 0, 0, .05, .5, 0, 0, 0, 0);


glPopMatrix();

}

//we want this centered at x y z (the axle anyway)
static void axle(double x, double y, double z, double w, double theta, double rx, double ry, double rz){

glPushMatrix();
glTranslated(x, y, z);
glRotated(theta, rx, ry, rz);
//x y z r h th rx ry rz
glBindTexture(GL_TEXTURE_2D, texture[6]);
cylinder(w/2, 0, 0, .1, w, 90, 0, 0, 1);

glColor3f(1, 1, 1);
wheel(w/2 - .35, 0, 0, 2, 1, -90, 0, 0, 1);
glPushMatrix();
glRotated(90, 1, 0, 0);
//glRotated(180, 1, 0, 0);

wheel(-w/2 +.35, 0, 0, 2, 1, 90, 0, 0, 1);
glPopMatrix();


glPopMatrix();
}

static void axle2(double x, double y, double z, double w, double theta, double rx, double ry, double rz){

glPushMatrix();
glTranslated(x, y, z);
glRotated(theta, rx, ry, rz);
//x y z r h th rx ry rz
glBindTexture(GL_TEXTURE_2D, texture[6]);
cylinder(w/2, 0, 0, .1, w, 90, 0, 0, 1);

glColor3f(1, 1, 1);
wheel2(w/2 - .35, 0, 0, 1, 1, -90, 0, 0, 1);
glPushMatrix();
glRotated(90, 1, 0, 0);
//glRotated(180, 1, 0, 0);

wheel2(-w/2 +.35, 0, 0, 1, 1, 90, 0, 0, 1);
glPopMatrix();


glPopMatrix();
}

static void cattleguard(){

  //WOOD TEXTURE

  glPushMatrix();
  glColor3f(1, 1, 1);
glBindTexture(GL_TEXTURE_2D, texture[13]);
glColor3f(1, 0, 0);


  cube(0, 1.5, 19.5, 2.5, .5, .5, 0);
  cube(1.425, -1.75, 21.5, 1.5, .25, .25, 30);
  cube(-1.425, -1.75, 21.5, 1.5, .25, .25, -30);
  TriPrism(0, -2, 22.45, .5, .25, .425, 0, 180, 90);
  TriPrism(0, -1.5, 22.45, .5, .25, .425, 0, 180, 270);

  cube2(.25, 2, 19.5, .25, 4.5, .25, 140, 0, 0);
  cube2(-.5, 2, 19.5, .25, 4.5, .25, 140, 0, 0);

  cube2(-1, 2, 19.5, .25, 4.25, .25, 145, 0, 0);
  cube2(.75, 2, 19.5, .25, 4.25, .25, 145, 0, 0);

  cube2(1.25, 2, 19.5, .25, 4.25, .25, 150, 0, 0);
  cube2(-1.5, 2, 19.5, .25, 4.25, .25, 150, 0, 0);

  cube2(1.75, 2, 19.5, .25, 4.25, .25, 155, 0, 0);
  cube2(-2, 2, 19.5, .25, 4.25, .25, 155, 0, 0);

  cube2(2.2, 2, 19.5, .25, 4, .25, 160, 0, 0);
  cube2(-2.45, 2, 19.5, .25, 4, .25, 160, 0, 0);


  glPopMatrix();

}

static void tree(double x, double y, double z, double sx, double sy, double sz){

  glPushMatrix();
  glTranslated(x, y, z);
  glScaled(sx, sy, sz);
  glEnable(GL_TEXTURE_2D);
  //x y z r h th rx ry rz
  glColor3f(1, 1, 1);
  glBindTexture(GL_TEXTURE_2D, texture[16]);
  cylinder(0, 0, 0, .25, 4, 0, 0, 0, 0);
  //x y z r h rx ry rz
  glBindTexture(GL_TEXTURE_2D, texture[17]);
  glColor3f(0, .39, 0);
  for(double x = 0.0; x <= 360.0; x += 18.0){
    treecone(0, 2, 0, .5, 3, 180, x, 55);
  }

  for(double x = -18.0; x <= 342.0; x += 36.0){
    treecone(0, 2.5, 0, .5, 2.5, 180, x, 60);
  }

  for(double x = 0.0; x <= 360.0; x += 45.0){
    treecone(0, 3, 0, .35, 2, 180, x, 65);
  }

  for(double x = -45.0/2.0; x <= 360.0-45.0/2.0; x += 45.0){
    treecone(0, 3.5, 0, .35, 1.5, 180, x, 70);
  }

  for(double x = 0.0; x <= 360.0; x += 45.0){
    treecone(0, 4, 0, .35, 1, 180, x, 75);
  }
//smaller
  for(double x = -45.0/2.0; x <= 360.0-45.0/2.0; x += 45.0){
    treecone(0, 4.25, 0, .25, .75, 180, x, 75);
  }

  for(double x = 0.0; x <= 360.0; x += 45.0){
    treecone(0, 4.5, 0, .25, .75, 180, x, 80);
  }

  //smaller still

  for(double x = -45.0/2.0; x <= 360.0-45.0/2.0; x += 45.0){
    treecone(0, 4.75, 0, .15, .5, 180, x, 85);
  }

  for(double x = 0.0; x <= 360.0; x += 45.0){
    treecone(0, 5, 0, .15, .45, 180, x, 90);
  }



  treecone(0, 4.2, 0, .35, 1.5, 0, 0, 0);

  glPopMatrix();
}

static void tree2(double x, double y, double z, double sx, double sy, double sz){

  glPushMatrix();
  glTranslated(x, y, z);
  glScaled(sx, sy, sz);
  //x y z r h th rx ry rz
  glColor3f(1, 1, 1);
  glBindTexture(GL_TEXTURE_2D, texture[16]);
  cylinder(0, 0, 0, .25, 4, 0, 0, 0, 0);
  //x y z r h rx ry rz
  glColor3f(0.1, .39, 0.1);
  glBindTexture(GL_TEXTURE_2D, texture[17]);
  for(double x = 0.0; x <= 360.0; x += 18.0){
    treecone(0, 2, 0, .5, 3, 180, x, 55);
  }

  for(double x = -18.0; x <= 342.0; x += 36.0){
    treecone(0, 2.5, 0, .5, 2.5, 180, x, 60);
  }

  for(double x = 0.0; x <= 360.0; x += 45.0){
    treecone(0, 3, 0, .35, 2, 180, x, 65);
  }

  for(double x = -45.0/2.0; x <= 360.0-45.0/2.0; x += 45.0){
    treecone(0, 3.5, 0, .35, 1.75, 180, x, 70);
  }

  for(double x = 0.0; x <= 360.0; x += 45.0){
    treecone(0, 4, 0, .35, 1.25, 180, x, 75);
  }
//smaller
  for(double x = -45.0/2.0; x <= 360.0-45.0/2.0; x += 45.0){
    treecone(0, 4.25, 0, .25, .95, 180, x, 75);
  }

  for(double x = 0.0; x <= 360.0; x += 45.0){
    treecone(0, 4.5, 0, .25, .75, 180, x, 80);
  }

  //smaller still

  for(double x = -45.0/2.0; x <= 360.0-45.0/2.0; x += 45.0){
    treecone(0, 4.75, 0, .15, .65, 180, x, 85);
  }

  for(double x = 0.0; x <= 360.0; x += 45.0){
    treecone(0, 5, 0, .15, .5, 180, x, 90);
  }



  treecone(0, 4.2, 0, .35, 1.5, 0, 0, 0);

  glPopMatrix();
}




//polygon gen for landscape
//should be centered at x y z
static void landscapepoly(double x, double y, double z, double r, double num){
 double mul = 2.0/num;
 int i, j;
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(-90, 1, 0, 0);
  glScaled(r,r,1);


glNormal3f(0, 0, 1);
glBindTexture(GL_TEXTURE_2D, texture[15]);
//the following code adapted from ex21
glBegin(GL_QUADS);
for (i=0;i<num;i++)
   for (j=0;j<num;j++)
   {
     /*
      glTexCoord2d(mul*(i+0),mul*(j+0)); glVertex2d(5*mul*(i+0)-5,5*mul*(j+0)-5);
      glTexCoord2d(mul*(i+1),mul*(j+0)); glVertex2d(5*mul*(i+1)-5,5*mul*(j+0)-5);
      glTexCoord2d(mul*(i+1),mul*(j+1)); glVertex2d(5*mul*(i+1)-5,5*mul*(j+1)-5);
      glTexCoord2d(mul*(i+0),mul*(j+1)); glVertex2d(5*mul*(i+0)-5,5*mul*(j+1)-5);
*/
      glTexCoord2d(0,0); glVertex2d(mul*(i+0)-1,mul*(j+0)-1);
         glTexCoord2d(1,0); glVertex2d(mul*(i+1)-1,mul*(j+0)-1);
         glTexCoord2d(1,1); glVertex2d(mul*(i+1)-1,mul*(j+1)-1);
         glTexCoord2d(0,1); glVertex2d(mul*(i+0)-1,mul*(j+1)-1);
   }
glEnd();
  glPopMatrix();

}

static void landscape(double x, double y, double z){

  glPushMatrix();
  glEnable(GL_LIGHTING);
  //double t = fmod( zh * speed,360.0);

  double landscapetime = fmod(speed * mytime, 104.0);
  glColor3f(1,1,1);
glTranslated(x, y, z - landscapetime*3.1415926);
landscapepoly(0,-2.6,0,52*3.1415926, 64);
//landscapepoly(0,-2.6,7+ 24 * 3.1415926, 24*3.1415926, 300);
//rails(0, 0, -zh*4*3.1415926/360.0);

for (int x1 = -150; x1 <= 150; x1 += 95){
  for (int z1 = -150; z1 <= 150; z1 += 95){
    if (x1 % 2 == 0){
      if (z1 % 2 == 0){
        tree(x1 + 20, -2.5, z1+36, 5,5,5);
      }
      else{
        tree2(x1 + 28, -2.5, z1-30, 4,4,4);
      }
      }

    else{
      if (z1 % 2 == 0){
        tree(x1 + 15, -2.5, z1+12, 6,6,6);
      }
      else{
        tree2(x1 - 15, -2.5, z1-17, 2,2,2);
      }
      }

    }
  }



  glPopMatrix();
}


//this is what is going to draw the wheels and rods at proper rotation and all that based on time, but we need a vehicle to work with first.
//ROTATE AXLES IN X DIRECTION ONLY!!!!!!!!!!!! little wheels get rotated twice as fast as big wheels
//rod positions dictated by time so glTranslated(0, Sin(something), Cos(something). that's it for the easy ones
//the more difficult ones are gonna need a center point and a rotation angle and a translate - this is hard. might be easier if we write our own cube function
//center it around the front rod coupler, and then translate like we would the other rods, but rotate differently
static void drive(){

  glPushMatrix();

  double t = zh * speed;
//bind textures in axle
  axle(0, 0, 0, 6, t, 1, 0, 0);
  axle(0, 0, 6, 6, t, 1, 0, 0);
  axle2(0, -1, 13, 6, 2*t, 1, 0, 0);
  axle2(0, -1, 18, 6, 2*t, 1, 0, 0);


//MATTE BLACK

glBindTexture(GL_TEXTURE_2D, texture[3]);
  //rear rods
  glColor3f(1,1,1);
  cylinder(-3.25, .6*Cos(t+90), .6*Sin(t+90)-.5, .175, 10, 90, 1, 0, 0);
  cylinder(3.25, .6*Cos(t+180), .6*Sin(t+180)-.5, .175, 10, 90, 1, 0, 0);

  //front rods
  //glColor3f(0, 0, 1);
    cylinder(-3.6, .6*Cos(t+90), .6*Sin(t+90)+8.5, .175, 7, 4.9*Cos(t+90)+90, 1, 0, 0);
    cylinder(3.6, .6*Cos(t+180), .6*Sin(t+180)+8.5, .175, 7, 4.9*Cos(t+180)+90, 1, 0, 0);

//GRAY STEEL LIKE ROCKETS I THINK
  //links
  //glColor3f(0, 1, 1);
  glBindTexture(GL_TEXTURE_2D, texture[6]);
  cylinder(3, .6*Cos(t+180), .6*Sin(t+180)+9, .125, 1, -90, 0, 0, 1);
  cylinder(-3, .6*Cos(t+90), .6*Sin(t+90)+9, .125, 1, 90, 0, 0, 1);


  glPopMatrix();
}

static void train(double x, double y, double z){
 glPushMatrix();
 glTranslated(x, y, z);
 glEnable(GL_TEXTURE_2D);


//bind textures inside drive as needed
drive();
//zh goes between 0 and 360, we need to move back 4pi every 360 so we divide our total by 360
//eventually we need to put rails inside landscape
//and deal with making that movement work well


//bind textures inside cattleguard as needed
cattleguard();



//glEnable(GL_TEXTURE_2D);
//piston chambers
//bind textures for these here
glBindTexture(GL_TEXTURE_2D, texture[14]);
glColor3f(1,1,1);
cylinder(-3.25, 0, 14, .75, 3, 90, 1, 0, 0);
cylinder(3.25, 0, 14, .75, 3, 90, 1, 0, 0);
//hooks into piston chambers
cylinder(3, .5, 16.5, .4, 3, 45, 0, 0, 1);
cylinder(3, .5, 14.5, .4, 3, 45, 0, 0, 1);
cylinder(-3, .5, 16.5, .4, 3, -45, 0, 0, 1);
cylinder(-3, .5, 14.5, .4, 3, -45, 0, 0, 1);

//trim cylinders
cylinder(0, 3.5, 5, 2.55, .25, 90, 1, 0, 0);
cylinder(0, 3.5, 10, 2.55, .25, 90, 1, 0, 0);
cylinder(0, 3.5, 15, 2.55, .25, 90, 1, 0, 0);
cylinder(0, 3.5, 18.95, 1.8, .25, 90, 1, 0, 0);

//maybe make this wood and red
glBindTexture(GL_TEXTURE_2D, texture[13]);
glColor3f(1,0,0);
cube(0, 1.25, 14.5, 2.25, .25, 5, 0);
//light thing
cube(0, 6.5, 18.25, .5, .5, .5,0);
lightcone(0, 6.5, 18.85, .4, .75, -90, 0, 0);
glColor3f(1,1,1);


//MATTE BLACK
glBindTexture(GL_TEXTURE_2D, texture[6]);
//main cylinder, front cone and base
cylinder(0, 3.5, 3, 2.5, 16, 90, 1, 0, 0);
cone(0, 3.5 , 19, 2, 1, 90, 0, 0);



//smoke stack
cylinder( 0, 5.5, 17.5, .5, 1.5, 0, 0, 0, 0);
cylinder( 0, 6.5, 17.5, .75, .75, 0, 0, 0, 0);
cone(0, 9, 17.5, 1.75, 3, 180, 0, 0);

//front wheel block
cube(0, 0, 15.5, 2.5, 1.125, 1.5, 0);
TriPrism(-2.5, -1.125, 17, 5, 2.25, 2, 0, 0, 0);
TriPrism(2.5, -1.125, 14, 5, 2.25, 2, 0, 180, 0);

//rear wheel block
//x y z l h w th
cube(0, 0.5, 3, 2.5, 1.5, 6, 0);
TriPrism(-2.5, 2, -3, 5, 3, 1, 180, 0, 0);
TriPrism(2.5, 2, 9, 5, 3, 2, 180, 180, 0);


//WOOD TEXTURE
//engineer area
glBindTexture(GL_TEXTURE_2D, texture[5]);

//main panel front
//top
cube(0, 5, 2.5, 3.5, 1, .5, 0);
//bottom
cube(0, 3, 2.5, 2.5, 1, .5, 0);

//vertical bars front corners done
cube(3.75, 6.5, 2.5, .25, 2.5, .5, 0);
cube(-3.75, 6.5, 2.5, .25, 2.5, .5, 0);

//vertical bars side window done
cube(-3.75, 7.25, -0.5, .25, 1.25, .5, 0);
cube(3.75, 7.25, -0.5, .25, 1.25, .5, 0);

//vertical bar center on front side done
cube(0, 7.25, 2.5, .5, 1.25, .5, 0);

//top window bar front
cube(0, 8.75, 2.5, 3.5, 0.25, .5, 0);

//main panel right and left done
cube(-3.75, 5, -0.5, .25, 1, 2.5, 0);
cube(3.75, 5, -0.5, .25, 1, 2.5, 0);

//bar top of window left and right done
cube(3.75, 8.75, -0.5, .25, 0.25, 2.5, 0);
cube(-3.75, 8.75, -0.5, .25, 0.25, 2.5, 0);

//roofs done
TriPrism(-1.5, 9, -7, 11, 1, 3, 0, -90, 0);
TriPrism(1.5, 9, 4, 11, 1, 3, 0, 90, 0);
cube(0, 9.5, -1.5, 1.5, 0.5, 5.5, 0);

//rear vertical bars done
cube(-3.75, 6.5, -3.5, .25, 2.5, 0.5, 0);
cube(3.75, 6.5, -3.5, .25, 2.5, 0.5, 0);

//triprism rear upside down
TriPrism(-4, 9, -4, 8, 0.5, 3, 180, 0, 0);

//triprism slope 1 left and right
TriPrism(3, 4, -4, 7, 1, 1, 180, 90, 0);
TriPrism(-3, 4, 3, 7, 1, 1, 180, 270, 0);

//lower panel left and right (hidden by triprsm mostly)
cube(2.75, 3.5, -0.5, .25, 0.5, 3.5, 0);
cube(-2.75, 3.5, -0.5, .25, 0.5, 3.5, 0);

//triprism slope 2 left right
TriPrism(2.5, 3, -4, 7, 1, .5, 180, 90, 0);
TriPrism(-2.5, 3, 3, 7, 1, .5, 180, 270, 0);

//vertical bars rear outside
cube(-3, 6.5, -3.75, .5, 2.5, 0.25, 0);
cube(3, 6.5, -3.75, .5, 2.5, 0.25, 0);

//vertical bars rear inside
cube(2, 5.5, -3.75, .5, 3.5, 0.25, 0);
cube(-2, 5.5, -3.75, .5, 3.5, 0.25, 0);

//rear horizontal bar top of door
cube(0, 8.5, -3.75, 1.5, .5, 0.25, 0);

//rear door
glColor3f(1, 0, 0);
glBindTexture(GL_TEXTURE_2D, texture[13]);
//main
cube(0, 4, -3.75, 1.5, 2, 0.25, 0);
//top
cube(0, 7.75, -3.75, 1.5, .25, 0.25, 0);
//sides
cube(1.25, 6.75, -3.75, .25, .75, 0.25, 0);
cube(-1.25, 6.75, -3.75, .25, .75, 0.25, 0);

glColor3f(1,1,1);
glBindTexture(GL_TEXTURE_2D, texture[14]);
cylinder(-1, 4.5, -3.75, .1, .5, -90, 1, 0, 0);
cylinder(-1, 4.5, -4.15, .08, .5, -90, 0, 0, 1);




glDisable(GL_TEXTURE_2D);
dosmoke();
//smokeball(10, 10, 10, 5);

 glPopMatrix();

}


void display()
{
   //  Length of axes
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
  // const double len=2.0;
   //  Eye position
   double Ex = -2*dim*Sin(th)*Cos(ph);
   double Ey = +2*dim        *Sin(ph);
   double Ez = +2*dim*Cos(th)*Cos(ph);
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Set perspective
   glLoadIdentity();
   gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   //  Light switch
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light direction
      float Position[]  = {-60,65,-180,1.0};
	  //float Position2[] = {0.0, 18.0, 0.0, 1.0};
	  //float direction2[] = {0.0, -1.0, 0.0};
	  //float cutoff = {64};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 10);
	  //ball(Position2[0],Position2[1],Position2[2] , 0.1);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      day ? glEnable(GL_LIGHT0) : glDisable(GL_LIGHT0);
	    glEnable(GL_LIGHT1);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);

	  glLightfv(GL_LIGHT1,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT1,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT1,GL_SPECULAR,Specular);
	  /*
      glLightfv(GL_LIGHT1,GL_POSITION,Position2);
	  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction2);
	  glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, 30.0);
	  glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0); */

	  //float light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	  //float light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	  //float light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	  float light1_position[] = { 0, 6.5, 18.75, 1.0 };
    //lightcone(0, 6.5, 18.85, .4, .75, -90, 0, 0);
	  float spot_direction[] = { 0.0, -.3, 1.0 };



	  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	  glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.21);
	  glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05);
	  glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);

	  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20);
	  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.1);


   }
   else
      glDisable(GL_LIGHTING);
   //  Draw scene
   skybox(0,0,0,160);
   glColor3f(1,1,1);

   glEnable(GL_TEXTURE_2D);
   landscape(0,0,0);
   landscape(0, 0, 104*3.1415926);
   double t = fmod(mytime*speed, 4.0);

   /*
   double landscapetime = fmod(speed * mytime, 104.0);
   glColor3f(1,1,1);
 glTranslated(x, y, z - landscapetime*3.1415926); */
   rails(0, 0, -t*3.1415926);
   //glEnable(GL_TEXTURE_2D);
   //glDisable(GL_TEXTURE_2D);
//translate z to -7, y to -4 probably only
   train(0, 0, -7);

   //tree(6, 2, 1, 1, 1, 1);
   //tree2(6, 2, 7, 1, 1, 1);

   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);

   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f Time=%s Speed=%.1f",th,ph,dim,day ?"Day":"Night", speed);
   /*if (light)
   {
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }*/
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   mytime = t;
   zh = fmod(90*t,360.0*speed*4);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 2.5;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 2.5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(45,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle texture mode
  else if (ch == 'd' || ch == 'D')
      day = 1-day;

    else if (ch == 's'){
      speed -= .2;
    }
    else if (ch == 'S'){
      speed += .2;
    }

   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(45,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*void mouse(int button, int state, int x, int y ){
if (button == GLUT_MIDDLE_BUTTON){
  if (state == GLUT_DOWN){
    dim -= .1;
  }
  else if (state == GLUT_UP){
    dim += .1;
  }
}

} */

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(45,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("Peter McPadden Graphics Project");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   //glutMouseFunc(mouse);
   glutIdleFunc(idle);
   //  Load textures
   texture[0] = LoadTexBMP("crate.bmp");
   texture[1] = LoadTexBMP("marble.bmp");
   texture[2] = LoadTexBMP("marble2.bmp");
   texture[3] = LoadTexBMP("rocket.bmp");
   texture[4] = LoadTexBMP("rocket2.bmp");
   texture[5] = LoadTexBMP("wood.bmp");
   texture[6] = LoadTexBMP("matteblack.bmp");
   texture[7] = LoadTexBMP("SBack.bmp");
   texture[8] = LoadTexBMP("SDown.bmp");
   texture[9] = LoadTexBMP("SFront.bmp");
   texture[10] = LoadTexBMP("SLeft.bmp");
   texture[11] = LoadTexBMP("SRight.bmp");
   texture[12] = LoadTexBMP("SUp.bmp");
   texture[13] = LoadTexBMP("wood2.bmp");
   texture[14] = LoadTexBMP("gold.bmp");
   texture[15] = LoadTexBMP("grass.bmp");
   texture[16] = LoadTexBMP("bark.bmp");
   texture[17] = LoadTexBMP("pine.bmp");
   texture[18] = LoadTexBMP("NBack.bmp");
   texture[19] = LoadTexBMP("NDown.bmp");
   texture[20] = LoadTexBMP("NFront.bmp");
   texture[21] = LoadTexBMP("NLeft.bmp");
   texture[22] = LoadTexBMP("NRight.bmp");
   texture[23] = LoadTexBMP("NUp.bmp");
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}

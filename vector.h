/*************************************************************************************************\
*                                                                                                 *
* "vector.h" - Constants, types, and fuctions for vector calculations.                            *
*              Angle measurements are in radians.                                                 *
*                                                                                                 *
*     Author - Tom McDonnell 2003                                                                 *
*                                                                                                 *
\*************************************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include <TomsLibrary/misc.h>

#include <math.h>
#include <iostream.h>

// GLOBAL VARIABLES ///////////////////////////////////////////////////////////////////////////////

namespace TomsLibVector
{

 const double pi     = 3.141592654,
              twoPi  = 2.0 * pi,
              halfPi = pi / 2.0;

}

// GLOBAL TYPE DEFINITIONS ////////////////////////////////////////////////////////////////////////

namespace TomsLibVector
{
 using namespace TomsLibMisc;

 // 2D vector types //

 class rec2vector
 {
  public:
    rec2vector(void)                 {x =  0; y =  0;}
    rec2vector(double x1, double y1) {x = x1; y = y1;}

    double x, y;
 };

 class pol2vector
 {
  public:
    pol2vector(void) {r = 0; angle = 0;}

    pol2vector(double r1, double a1)
    {
       if (0 <= r1)
         r = r1;
       else
         error("Attempted to set pol2vector.r to -tve value.");

       if (-pi <= a1 && a1 <= pi)
         angle = a1;
       else
         error("Attempted to set pol2vector.angle to value outside range [-pi, pi].");
    }

    void setR(double r1)
    {
       if (r >= 0)
         r = r1;
       else
         error("Attempted to set pol2vector.r to -tve value.");
    }

    void setAngle(double a)
    {
       if (-pi <= a && a <= pi)
         angle = a;
       else 
         error("Attempted to set pol2vector.angle to value outside range [-pi, pi].");
    }

    double getR(void)     {return     r;}
    double getAngle(void) {return angle;}

    void rotate(double a) {angle += a; if (a > pi) angle -= twoPi;}

  private:
    double r,     // r     must always be positive
           angle; // angle must always be within range [-pi, pi]
 };

 // 3D vector types //

 class rec3vector
 {
  public:
    rec3vector(void)                            {x =  0; y =  0; z =  0;}
    rec3vector(double x1, double y1, double z1) {x = x1; y = y1; z = z1;}

    double x, y, z;
 };

 class pol3vector
 {
  public:
    pol3vector(void) {r = 0; aXZ = 0; aY = 0;}

    void setR(double r1)
    {
       if (0 <= r1)
         r = r1;
       else error("Attempted to set pol3vector.r to -tve value.");
    }

    void setAXZ(double aXZ1)
    {
       if (-pi <= aXZ1 && aXZ1 <= pi)
         aXZ = aXZ1;
       else
         error("Attempted to set pol3vector.aXZ to value outside range [-pi, pi].");
    }

    void setAY(double aY1)
    {
       if (-pi <= aY1 && aY1 <= pi)
         aY = aY1;
       else
         error("Attempted to set pol3vector.aY to value outside range [-pi, pi].");
    }

    pol3vector(double r, double aXZ, double aY) {setR(r); setAXZ(aXZ); setAY(aY);}

    double getR(void)   {return   r;}
    double getAXZ(void) {return aXZ;}
    double getAY(void)  {return  aY;}

  private:
    double r,   // r   must always be positive
           aXZ, // aXZ = angle in xz plane. x dir. is 0 radians, z dir. is pi/2 radians etc.
                // aXZ must always be within range [-pi, pi]
           aY;  // aY  = angle from y dir. y dir. is 0 radians, xz plane is pi/2 radians etc.
                // aY  must always be within range [-pi, pi]
 };

} // end namespace TomsLibVector

// GLOBAL INLINE FUCNTION DEFINITIONS /////////////////////////////////////////////////////////////

namespace TomsLibVector
{

 // 2D VECTOR FUNCTIONS //

 // basic rec2vector functions
 inline double magnitude(rec2vector v) {return sqrt(pow(v.x, 2) + pow(v.y, 2));}
 inline double angle(rec2vector v)     {return atan2(v.y, v.x);}

 // basic pol2vector functions
 inline double xComponent(pol2vector v) {return v.getR() * cos(v.getAngle());}
 inline double yComponent(pol2vector v) {return v.getR() * sin(v.getAngle());}

 // conversion functions
 inline pol2vector convToPol(rec2vector v) {return pol2vector(magnitude(v), angle(v));}
 inline rec2vector convToRec(pol2vector v) {return rec2vector(xComponent(v), yComponent(v));}

 // rec2vector functions

 inline double distance(rec2vector p1, rec2vector p2)
 {
    return sqrt(pow(p1.x - p2.x, 2.0) + pow(p1.y - p2.y, 2.0));
 }

 inline double vectDotProduct(rec2vector v, rec2vector v2) {return v.x * v2.x + v.y * v2.y;}

 inline rec2vector operator-(rec2vector v)                {v.x  = -v.x; v.y  = -v.y; return v;}
 inline rec2vector operator+(rec2vector v, rec2vector v2) {v.x += v2.x; v.y += v2.y; return v;}
 inline rec2vector operator-(rec2vector v, rec2vector v2) {v.x -= v2.x; v.y -= v2.y; return v;}
 inline rec2vector operator*(rec2vector v, double c)      {v.x *= c;    v.y *= c;    return v;}
 inline rec2vector operator*(double c, rec2vector v)      {return v * c;}
 inline rec2vector operator/(rec2vector v, double c)      {return v * (1.0 / c);}
 inline rec2vector operator/(double c, rec2vector v)      {return v / c;}

 inline void operator+=(rec2vector &v, rec2vector v2) {v = v + v2;}
 inline void operator-=(rec2vector &v, rec2vector v2) {v = v - v2;}
 inline void operator*=(rec2vector &v, double      c) {v = v *  c;}
 inline void operator/=(rec2vector &v, double      c) {v = v /  c;}

 inline bool operator==(rec2vector v1, rec2vector v2)
 {
    if (v1.x == v2.x && v1.y == v2.y) return true;
    else                              return false;
 }

 inline bool operator!=(rec2vector v1, rec2vector v2)
 {
    if (!(v1 == v2)) return true;
    else             return false;
 }

 // pol2vector functions

 inline double vectDotProduct(pol2vector v, pol2vector v2)
 {
    return v.getR() * v2.getR() * cos(fabs(v.getAngle() - v2.getAngle()));
 }

 inline pol2vector operator-(pol2vector v)
 {
    double newAngle = v.getAngle() + pi;

    if (newAngle > pi)
      newAngle -= twoPi;

    v.setAngle(newAngle);

    return v;
 }

 inline pol2vector operator*(pol2vector v, double c)
 {
    if (c >= 0)
      v.setR(v.getR() * c);
    else
      v = -v * -c;
     
    return v;
 }

 inline pol2vector operator*(double c, pol2vector v) {return v *        c ;}
 inline pol2vector operator/(pol2vector v, double c) {return v * (1.0 / c);}

 inline void operator*=(pol2vector &v, double c) {v = v * c;}
 inline void operator/=(pol2vector &v, double c) {v = v / c;}

 inline bool operator==(pol2vector v1, pol2vector v2)
 {
    if (   v1.getR()     == v2.getR()
        && v1.getAngle() == v2.getAngle())
      return true;
    else
      return false;
 }

 inline bool operator!=(pol2vector v1, pol2vector v2)
 {
    if (!(v1 == v2)) return true;
    else             return false;
 }

 // 3D VECTOR FUNCTIONS //

 // basic rec3vector funtions
 inline double magnitude(rec3vector v) {return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));}
 inline double angleXZ(rec3vector v)   {return atan2(v.z, v.x);}
 inline double angleY(rec3vector v)    {return atan2(sqrt(pow(v.x, 2) + pow(v.z, 2)), v.y);}

 // basic pol3vector functions
 inline double xComponent(pol3vector v) {return cos(v.getAXZ()) * (v.getR() * sin(v.getAY()));}
 inline double yComponent(pol3vector v) {return                    v.getR() * cos(v.getAY()); }
 inline double zComponent(pol3vector v) {return sin(v.getAXZ()) * (v.getR() * sin(v.getAY()));}

 // conversion functions
 inline pol3vector convToPol(rec3vector v) {return pol3vector(magnitude(v), angleXZ(v), angleY(v));}
 inline rec3vector convToRec(pol3vector v)
 {
    return rec3vector(xComponent(v), yComponent(v), zComponent(v));
 }

 // rec3vector functions

 inline rec3vector operator-(rec3vector v)
 {
    v.x = -v.x;
    v.y = -v.y;
    v.z = -v.z;

    return v;
 }

 inline rec3vector operator+(rec3vector v, rec3vector v2)
 {
    v.x += v2.x;
    v.y += v2.y;
    v.z += v2.z;

    return v;
 }

 inline rec3vector operator-(rec3vector v, rec3vector v2)
 {
    v.x -= v2.x;
    v.y -= v2.y;
    v.z -= v2.z;

    return v;
 }

 inline rec3vector operator*(rec3vector v, double c)
 {
    v.x *= c;
    v.y *= c;
    v.z *= c;

    return v;
 }

 inline rec3vector operator*(double c, rec3vector v) {return v *        c ;}
 inline rec3vector operator/(rec3vector v, double c) {return v * (1.0 / c);}

 inline void operator+=(rec3vector &v, rec3vector v2) {v = v + v2;}
 inline void operator-=(rec3vector &v, rec3vector v2) {v = v - v2;}

 inline void operator*=(rec3vector &v, double c) {v = v * c;}
 inline void operator/=(rec3vector &v, double c) {v = v / c;}

 inline bool operator==(rec3vector v1, rec3vector v2)
 {
    if (   v1.x == v2.x
        && v1.y == v2.y
        && v1.z == v2.z) return true;
    else                 return false;
 }

 inline bool operator!=(rec3vector v1, rec3vector v2)
 {
    if (!(v1 == v2)) return true;
    else             return false;
 }

 // pol3vector functions

 inline pol3vector operator-(pol3vector v)
 {
    double newAXZ = v.getAXZ() + pi,
           newAY  = v.getAY()  + pi;

    if (newAXZ > pi)
      newAXZ -= twoPi;

    if (newAY > pi)
      newAY -= twoPi;

    v.setAXZ(newAXZ);
    v.setAY(newAY);

    return v;
 }

 inline pol3vector operator*(pol3vector v, double c)
 {
    if (c >= 0)
      v.setR(v.getR() * c);
    else
      v = -v * -c;

    return v;
 }

 inline pol3vector operator*(double c, pol3vector v) {return v * c;}
 inline pol3vector operator/(pol3vector v, double c) {return v * (1.0 / c);}

 inline void operator*=(pol3vector &v, double c) {v = v * c;}
 inline void operator/=(pol3vector &v, double c) {v = v / c;}

 inline bool operator==(pol3vector v1, pol3vector v2)
 {
    if (   v1.getR()   == v2.getR()
        && v1.getAXZ() == v2.getAXZ()
        && v1.getAY()  == v2.getAY() )
      return true;
    else
      return false;
 }

 inline bool operator!=(pol3vector v1, pol3vector v2)
 {
    if (!(v1 == v2)) return true;
    else             return false;
 }

 // functions to aid debugging
 inline ostream &operator<<(ostream &output, rec2vector const &v)
 {
    output << "(" << v.x << ", " << v.y << ")";
    return output;
 }

 inline ostream &operator<<(ostream &output, pol2vector &v)
 {
    output << "(" << v.getR() << ", " << v.getAngle() * (180.0 / pi) << ")";
    return output;
 }

 inline ostream &operator<<(ostream &output, rec3vector const &v)
 {
    output << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return output;
 }

 inline ostream &operator<<(ostream &output, pol3vector &v)
 {
    output << "(" << v.getR() << ", " << v.getAXZ() * (180.0 / pi) 
                              << ", " << v.getAY()  * (180.0 / pi) << ")";
    return output;
 }

} // end namespace TomsLibVector

#endif

/*****************************************END*OF*FILE*********************************************/

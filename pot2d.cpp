#include "pot2d.h"

//##### HARMONIC BONDS, LJ REPULSIONS #####
HLJ2D::HLJ2D():BasePotentialModel2D(){};

//Potential
double HLJ2D::bndPotential(double &x0, double &y0, double &x1, double &y1, int &p) {
    double dx=x1-x0;
    double dy=y1-y0;
    double r=sqrt((dx*dx+dy*dy));
    return 0.5*bndP[2*p]*pow((r-bndP[2*p+1]),2);
}

double HLJ2D::angPotential(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2, int &p) {
    return 0.0;
}

double HLJ2D::repPotential(double &x0, double &y0, double &x1, double &y1, int &p) {
    double u=0.0;
    double dx=x1-x0;
    double dy=y1-y0;
    double r02=repP[2*p];
    double r2=(dx*dx+dy*dy);
    if(r2<r02){
        double d2=r02/r2;
        double d12=pow(d2,6);
        double d24=pow(d12,2);
        double ep=repP[2*p+1];
        u+=ep*(d24-2.0*d12)+ep;
    }
    return u;
}

double HLJ2D::intPotential(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2, double &x3,
                           double &y3, int &p) {
    return 0.0;
}

double HLJ2D::gcnPotential(double &x0, double &y0) {
    return 0.0;
}

//Forces
void HLJ2D::bndForce(double &x0, double &y0, double &x1, double &y1,
                     double &fx0, double &fy0, double &fx1, double &fy1, int &p) {
    double dx=x1-x0;
    double dy=y1-y0;
    double r=sqrt(dx*dx+dy*dy);
    double m=-bndP[2*p]*(r-bndP[2*p+1])/r;
    dx*=m;
    dy*=m;
    fx0-=dx;
    fy0-=dy;
    fx1+=dx;
    fy1+=dy;
}

void HLJ2D::angForce(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2,
                     double &fx0, double &fy0, double &fx1, double &fy1, double &fx2, double &fy2, int &p) {
    return;
}

void HLJ2D::repForce(double &x0, double &y0, double &x1, double &y1,
                     double &fx0, double &fy0, double &fx1, double &fy1, int &p) {
    double dx=x1-x0;
    double dy=y1-y0;
    double r02=repP[2*p];
    double r2=(dx*dx+dy*dy);
    if(r2<r02){
        double d2=r02/r2;
        double d12=pow(d2,6);
        double d24=pow(d12,2);
        double ep=repP[2*p+1];
        double m=24.0*ep*(d24-d12)/r2;
        dx*=m;
        dy*=m;
        fx0-=dx;
        fy0-=dy;
        fx1+=dx;
        fy1+=dy;
    }
}

void HLJ2D::intForce(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2, double &x3, double &y3,
                     double &fx0, double &fy0, double &fx1, double &fy1, double &fx2, double &fy2, double &fx3,
                     double &fy3, int &p) {
    return;
}

void HLJ2D::gcnForce(double &x0, double &y0, double &fx0, double &fy0) {
    return;
}

//##### HARMONIC BONDS, LJ REPULSIONS, PERIODIC BOUNDARY #####
HLJ2DP::HLJ2DP(double periodicX, double periodicY):BasePotentialModel2D(){
    pbx=periodicX;
    pby=periodicY;
    pbrx=1.0/pbx;
    pbry=1.0/pby;
};

//Potential
double HLJ2DP::bndPotential(double &x0, double &y0, double &x1, double &y1, int &p) {
    double dx=x1-x0;
    double dy=y1-y0;
    dx-=pbx*nearbyint(dx*pbrx);
    dy-=pby*nearbyint(dy*pbry);
    double r=sqrt((dx*dx+dy*dy));
    return 0.5*bndP[2*p]*pow((r-bndP[2*p+1]),2);
}

double HLJ2DP::angPotential(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2, int &p) {
    return 0.0;
}

double HLJ2DP::repPotential(double &x0, double &y0, double &x1, double &y1, int &p) {
    double u=0.0;
    double dx=x1-x0;
    double dy=y1-y0;
    dx-=pbx*nearbyint(dx*pbrx);
    dy-=pby*nearbyint(dy*pbry);
    double r02=repP[2*p];
    double r2=(dx*dx+dy*dy);
    if(r2<r02){
        double d2=r02/r2;
        double d12=pow(d2,6);
        double d24=pow(d12,2);
        double ep=repP[2*p+1];
        u+=ep*(d24-2.0*d12)+ep;
    }
    return u;
}

double HLJ2DP::intPotential(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2, double &x3,
                           double &y3, int &p) {
    return 0.0;
}

double HLJ2DP::gcnPotential(double &x0, double &y0) {
    return 0.0;
}

//Forces
void HLJ2DP::bndForce(double &x0, double &y0, double &x1, double &y1,
                     double &fx0, double &fy0, double &fx1, double &fy1, int &p) {
    double dx=x1-x0;
    double dy=y1-y0;
    dx-=pbx*nearbyint(dx*pbrx);
    dy-=pby*nearbyint(dy*pbry);
    double r=sqrt(dx*dx+dy*dy);
    double m=-bndP[2*p]*(r-bndP[2*p+1])/r;
    dx*=m;
    dy*=m;
    fx0-=dx;
    fy0-=dy;
    fx1+=dx;
    fy1+=dy;
}

void HLJ2DP::angForce(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2,
                     double &fx0, double &fy0, double &fx1, double &fy1, double &fx2, double &fy2, int &p) {
    return;
}

void HLJ2DP::repForce(double &x0, double &y0, double &x1, double &y1,
                     double &fx0, double &fy0, double &fx1, double &fy1, int &p) {
    double dx=x1-x0;
    double dy=y1-y0;
    dx-=pbx*nearbyint(dx*pbrx);
    dy-=pby*nearbyint(dy*pbry);
    double r02=repP[2*p];
    double r2=(dx*dx+dy*dy);
    if(r2<r02){
        double d2=r02/r2;
        double d12=pow(d2,6);
        double d24=pow(d12,2);
        double ep=repP[2*p+1];
        double m=24.0*ep*(d24-d12)/r2;
        dx*=m;
        dy*=m;
        fx0-=dx;
        fy0-=dy;
        fx1+=dx;
        fy1+=dy;
    }
}

void HLJ2DP::intForce(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2, double &x3, double &y3,
                     double &fx0, double &fy0, double &fx1, double &fy1, double &fx2, double &fy2, double &fx3,
                     double &fy3, int &p) {
    return;
}

void HLJ2DP::gcnForce(double &x0, double &y0, double &fx0, double &fy0) {
    return;
}

void HLJ2DP::wrap(VecF<double>& x) {
    for(int i=0,j=1; i<x.n; i+=2, j+=2){
        x[i]-=pbx*nearbyint(x[i]*pbrx)-pbx*0.5;
        x[j]-=pby*nearbyint(x[j]*pbry)-pby*0.5;
    }
}

//##### HARMONIC BONDS, LJ REPULSIONS, CONSTRAINED TO CIRCLE #####
HLJ2DC::HLJ2DC():BasePotentialModel2D(){};

//Potential
double HLJ2DC::bndPotential(double &x0, double &y0, double &x1, double &y1, int &p) {
    double dx=x1-x0;
    double dy=y1-y0;
    double r=sqrt((dx*dx+dy*dy));
    return 0.5*bndP[2*p]*pow((r-bndP[2*p+1]),2);
}

double HLJ2DC::angPotential(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2, int &p) {
    return 0.0;
}

double HLJ2DC::repPotential(double &x0, double &y0, double &x1, double &y1, int &p) {
    double u=0.0;
    double dx=x1-x0;
    double dy=y1-y0;
    double r02=repP[2*p];
    double r2=(dx*dx+dy*dy);
    if(r2<r02){
        double d2=r02/r2;
        double d12=pow(d2,6);
        double d24=pow(d12,2);
        double ep=repP[2*p+1];
        u+=ep*(d24-2.0*d12)+ep;
    }
    return u;
}

double HLJ2DC::intPotential(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2, double &x3,
                           double &y3, int &p) {
    return 0.0;
}

double HLJ2DC::gcnPotential(double &x0, double &y0) {
    double r=sqrt(x0*x0+y0*y0);
    return 0.5*gcnP[0]*pow((r-gcnP[1]),2);
}

//Forces
void HLJ2DC::bndForce(double &x0, double &y0, double &x1, double &y1,
                     double &fx0, double &fy0, double &fx1, double &fy1, int &p) {
    double dx=x1-x0;
    double dy=y1-y0;
    double r=sqrt(dx*dx+dy*dy);
    double m=-bndP[2*p]*(r-bndP[2*p+1])/r;
    dx*=m;
    dy*=m;
    fx0-=dx;
    fy0-=dy;
    fx1+=dx;
    fy1+=dy;
}

void HLJ2DC::angForce(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2,
                     double &fx0, double &fy0, double &fx1, double &fy1, double &fx2, double &fy2, int &p) {
    return;
}

void HLJ2DC::repForce(double &x0, double &y0, double &x1, double &y1,
                     double &fx0, double &fy0, double &fx1, double &fy1, int &p) {
    double dx=x1-x0;
    double dy=y1-y0;
    double r02=repP[2*p];
    double r2=(dx*dx+dy*dy);
    if(r2<r02){
        double d2=r02/r2;
        double d12=pow(d2,6);
        double d24=pow(d12,2);
        double ep=repP[2*p+1];
        double m=24.0*ep*(d24-d12)/r2;
        dx*=m;
        dy*=m;
        fx0-=dx;
        fy0-=dy;
        fx1+=dx;
        fy1+=dy;
    }
}

void HLJ2DC::intForce(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2, double &x3, double &y3,
                     double &fx0, double &fy0, double &fx1, double &fy1, double &fx2, double &fy2, double &fx3,
                     double &fy3, int &p) {
    return;
}

void HLJ2DC::gcnForce(double &x0, double &y0, double &fx0, double &fy0) {
    double r=sqrt(x0*x0+y0*y0);
    double m=-gcnP[0]*(r-gcnP[1])/r;
    double dx=x0*m;
    double dy=y0*m;
    fx0+=dx;
    fy0+=dy;
    return;
}

//##### HARMONIC BONDS, INFINITE COST LINE INTERSECTIONS #####
HI2D::HI2D():BasePotentialModel2D(){};

//Potential
double HI2D::bndPotential(double &x0, double &y0, double &x1, double &y1, int &p) {
    double dx=x1-x0;
    double dy=y1-y0;
    double r=sqrt((dx*dx+dy*dy));
    return 0.5*bndP[2*p]*pow((r-bndP[2*p+1]),2);
}

double HI2D::angPotential(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2, int &p) {
    return 0.0;
}

double HI2D::repPotential(double &x0, double &y0, double &x1, double &y1, int &p) {
    return 0.0;
}

double HI2D::intPotential(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2, double &x3,
                           double &y3, int &p) {
    bool intx=properIntersectionLines(x0,y0,x1,y1,x2,y2,x3,y3);
    if(intx) return numeric_limits<double>::infinity();
    else return 0.0;
}

double HI2D::gcnPotential(double &x0, double &y0) {
    return 0.0;
}

//Forces
void HI2D::bndForce(double &x0, double &y0, double &x1, double &y1,
                     double &fx0, double &fy0, double &fx1, double &fy1, int &p) {
    double dx=x1-x0;
    double dy=y1-y0;
    double r=sqrt(dx*dx+dy*dy);
    double m=-bndP[2*p]*(r-bndP[2*p+1])/r;
    dx*=m;
    dy*=m;
    fx0-=dx;
    fy0-=dy;
    fx1+=dx;
    fy1+=dy;
}

void HI2D::angForce(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2,
                     double &fx0, double &fy0, double &fx1, double &fy1, double &fx2, double &fy2, int &p) {
    return;
}

void HI2D::repForce(double &x0, double &y0, double &x1, double &y1,
                     double &fx0, double &fy0, double &fx1, double &fy1, int &p) {
    return;
}

void HI2D::intForce(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2, double &x3, double &y3,
                     double &fx0, double &fy0, double &fx1, double &fy1, double &fx2, double &fy2, double &fx3,
                     double &fy3, int &p) {
    return;
}

void HI2D::gcnForce(double &x0, double &y0, double &fx0, double &fy0) {
    return;
}

//##### HARMONIC BONDS, INFINITE COST LINE INTERSECTIONS, PERIODIC BOUNDARY #####
HI2DP::HI2DP(double periodicX, double periodicY):BasePotentialModel2D(){
    pbx=periodicX;
    pby=periodicY;
    pbrx=1.0/pbx;
    pbry=1.0/pby;
};

//Potential
double HI2DP::bndPotential(double &x0, double &y0, double &x1, double &y1, int &p) {
    double dx=x1-x0;
    double dy=y1-y0;
    dx-=pbx*nearbyint(dx*pbrx);
    dy-=pby*nearbyint(dy*pbry);
    double r=sqrt((dx*dx+dy*dy));
    return 0.5*bndP[2*p]*pow((r-bndP[2*p+1]),2);
}

double HI2DP::angPotential(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2, int &p) {
    return 0.0;
}

double HI2DP::repPotential(double &x0, double &y0, double &x1, double &y1, int &p) {
    return 0.0;
}

double HI2DP::intPotential(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2, double &x3,
                            double &y3, int &p) {
    double px1,py1,px2,py2,px3,py3;
    px1=x1-x0;
    py1=y1-y0;
    px2=x2-x0;
    py2=y2-y0;
    px1-=pbx*nearbyint(px1*pbrx);
    py1-=pby*nearbyint(py1*pbry);
    px2-=pbx*nearbyint(px2*pbrx);
    py2-=pby*nearbyint(py2*pbry);
    px1+=x0;
    py1+=y0;
    px2+=x0;
    py2+=y0;
    px3=x3-px2;
    py3=y3-py2;
    px3-=pbx*nearbyint(px3*pbrx);
    py3-=pby*nearbyint(py3*pbry);
    px3+=px2;
    py3+=py2;
    bool intx=properIntersectionLines(x0,y0,px1,py1,px2,py2,px3,py3);
    if(intx) return numeric_limits<double>::infinity();
    else return 0.0;
}

double HI2DP::gcnPotential(double &x0, double &y0) {
    return 0.0;
}

//Forces
void HI2DP::bndForce(double &x0, double &y0, double &x1, double &y1,
                      double &fx0, double &fy0, double &fx1, double &fy1, int &p) {
    double dx=x1-x0;
    double dy=y1-y0;
    dx-=pbx*nearbyint(dx*pbrx);
    dy-=pby*nearbyint(dy*pbry);
    double r=sqrt(dx*dx+dy*dy);
    double m=-bndP[2*p]*(r-bndP[2*p+1])/r;
    dx*=m;
    dy*=m;
    fx0-=dx;
    fy0-=dy;
    fx1+=dx;
    fy1+=dy;
}

void HI2DP::angForce(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2,
                      double &fx0, double &fy0, double &fx1, double &fy1, double &fx2, double &fy2, int &p) {
    return;
}

void HI2DP::repForce(double &x0, double &y0, double &x1, double &y1,
                      double &fx0, double &fy0, double &fx1, double &fy1, int &p) {
    return;
}

void HI2DP::intForce(double &x0, double &y0, double &x1, double &y1, double &x2, double &y2, double &x3, double &y3,
                      double &fx0, double &fy0, double &fx1, double &fy1, double &fx2, double &fy2, double &fx3,
                      double &fy3, int &p) {
    return;
}

void HI2DP::gcnForce(double &x0, double &y0, double &fx0, double &fy0) {
    return;
}

void HI2DP::wrap(VecF<double>& x) {
    for(int i=0,j=1; i<x.n; i+=2, j+=2){
        x[i]-=pbx*nearbyint(x[i]*pbrx)-pbx*0.5;
        x[j]-=pby*nearbyint(x[j]*pbry)-pby*0.5;
    }
}

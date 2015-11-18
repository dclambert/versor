  /*
 * =====================================================================================
 *
 *       Filename:  xConstructions.cpp
 *
 *    Description:  scratch pad for constructions
 *
 *        Version:  1.0
 *        Created:  07/20/2015 19:13:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Pablo Colapinto (), gmail->wolftype
 *   Organization:  wolftype
 *
 * =====================================================================================
 */


#include "vsr_app.h"  
#include <vsr/form/vsr_twist.h> 

using namespace vsr;
using namespace vsr::cga;

struct MyApp : App {
 
  //Some Variables
  bool bReset = false;

  Point point;
  bool bSetMouse=true;

   Frame f;


  float amt,amt1,amt2,radius,iter;


  /*-----------------------------------------------------------------------------
   *  Setup Variables
   *-----------------------------------------------------------------------------*/
  void setup(){
    ///Bind Gui
    bindGLV();
    ///Add Variables to GUI
    gui(bReset);
    gui(amt,"amt",-10,10);
    gui(amt1,"amt1",-1000,1000);
    gui(amt2,"amt2",-1000,1000);
    gui(iter,"iter",-1000,1000);
    gui(radius,"radius",-10,1);
    
    objectController.attach(&f);
    bShadedOutput = false;

    amt = -PI;
    amt1 = 1;
    amt2 = 1;
    iter=100;

    
  }


  void onKeyDown(const gfx::Keyboard& k){
    
    switch (k.code){
      case 's':
        bSetMouse = !bSetMouse;
    }

    App::onKeyDown(k);
   }

  /*-----------------------------------------------------------------------------
   *  Draw Routines 
   *-----------------------------------------------------------------------------*/
  void onDraw(){

    
    if (bSetMouse) point = calcMouse3D();


    for (int i =0;i<10;++i){
      float t= (float)i/10;
      auto flp =(point^Inf(1));
      auto D =  flp*sinh(t/2) + cosh(t/2);//Gen::dil(point,t*amt);

      auto c= CXY(1).spin(D);
      Draw(c,t,0,1-t);

    }

    auto va = Vec(.2,3,0).unit();
    auto vb = Vec(.8,0,2).unit();

    auto R = va*vb;//Gen::rot(va^vb);

   // cout << R << endl;
    cout << !R << endl;
    cout << ~R << endl;

    

  }
  
};


int main(){
                             
  MyApp app;
  app.start();

  return 0;

}

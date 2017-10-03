#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "CinderCerealImGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class Simple{
    
public:
    float mFloat = 3.14;
    int   mInt = 42;
    ci::vec2 mVec2 {10, 20};
    
    ci::Color mColor{ 1.0f, 1.0f, 0.0f };
    ci::ColorA mColorAlpha{ 0.0f, 0.0f, 1.0f, 0.5 };
    
    glm::quat mRotation;
    
    std::string mString = "hello world";
};

namespace  cereal {
    

    template< class Archive>
    void save(Archive& archive, const Simple& simple){

        archive(
                CEREAL_NVP_("Name", simple.mString),
                CEREAL_NVP_( "custom ImGui name ", simple.mFloat),
                simple.mInt,
                CEREAL_NVP_("position", simple.mVec2),
                CEREAL_NVP_("rotation", simple.mRotation),

                CEREAL_NVP_("color", simple.mColor),
                CEREAL_NVP_("colorA", simple.mColorAlpha) );
        
    }
    template<class Archive>
    void load( Archive& archive, Simple& simple ){

        archive(
                CEREAL_NVP_("Name", simple.mString),
                CEREAL_NVP_( "custom ImGui name ", simple.mFloat),
                simple.mInt,
                CEREAL_NVP_("position", simple.mVec2),
                CEREAL_NVP_("rotation", simple.mRotation),
                
                CEREAL_NVP_("color", simple.mColor),
                CEREAL_NVP_("colorA", simple.mColorAlpha) );

    }

}



class CerealImGuiApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    Simple simpleObject;
};

void CerealImGuiApp::setup()
{

    
    ui::initialize();
    
}

void CerealImGuiApp::mouseDown( MouseEvent event )
{
}

void CerealImGuiApp::update()
{
}

void CerealImGuiApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    
    
    // Draw imGui from an cereal::archive
    cereal::ImGuiArchive uiAr;
    uiAr.setOption("position", cereal::ImGuiArchive::Options().setMinMax(-10, 10) );
    uiAr.setOption("rotation", cereal::ImGuiArchive::Options().setStep(0.001f) );
    
    uiAr.setOption("color", cereal::ImGuiArchive::Options().setSpacing(10) );
    
    uiAr(simpleObject);
    
    
    if( ui::Button("save") ){
        
        std::ofstream file("cereal.json");
        cereal::JSONOutputArchive archive(file);
        
        archive(simpleObject);
    }
    
    
    if( ui::Button("load") ){
        
        std::ifstream file("cereal.json");
        cereal::JSONInputArchive archive(file);

        archive(simpleObject);
    }
    
    
    console() << simpleObject.mString << endl;
    
}

CINDER_APP( CerealImGuiApp, RendererGl )

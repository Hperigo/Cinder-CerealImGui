
//
//  CinderCerealImGui.h
//
//
//  Created by Henrique on 8/9/17.
//
//

#ifndef CinderCerealImGui_h
#define CinderCerealImGui_h

// Cereal
#include "CinderCereal.h"
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>


// UI
#include "CinderImGui.h"

namespace cereal {
    
    class ImGuiArchive : public InputArchive<ImGuiArchive>, public traits::TextArchive{
    public:
        
        class Options{
            
        public:
            
            Options(){
                
            }
            ~Options(){
                
            }
            
            Options(float _min, float _max, float _stepAmt  ) : mMin(_min), mMax(_max), mStepAmt(_stepAmt){
                mHasStep = false;
                mHasMinMax = true;
            }
            
            
            Options& setMinMax(float _min, float _max ){
                mMin = _min;
                mMax = _max;
                mHasMinMax = false;
                return *this;
            }
            
            
            Options& setStep( float amt ){
                mStepAmt = amt;
                return *this;
            }
            
            float getMin(){
                return mMin;
            }
            
            float getMax(){
                return mMax;
            }
            
            float getStep(){
                return mStepAmt;
            }
            
            
            bool hasStep(){
                return mHasStep;
            }
            
            bool hasMinMax(){
                return mHasMinMax;
            }
            
            
        private:
            
            float mStepAmt = 0.1;
            bool mHasStep = true;

            float mMin = 0;
            float mMax = 10.0;
            bool mHasMinMax = false;
            
        };
        
        ImGuiArchive(  ) : InputArchive<ImGuiArchive>(this){
            
            
        }
        
        ~ImGuiArchive( ) {
            
        }
        
        template <class T> inline
        void draw(const char * name, T & value){
            
            auto opt = mElementOptions[name];
            
            draw(name, value, opt);
        }
        
        
        void draw(const char * name, int & value, Options opt = Options() ){
            
            
            if(opt.hasStep()){
                ui::DragInt(name, &value, opt.getStep() );
            }
            else if(opt.hasMinMax()){
                ui::DragInt(name, &value, opt.getStep(), opt.getMin(), opt.getMax() );
            }else{
                ui::DragInt(name, &value);
            }
        }
        
        void draw(const char * name, float & value, Options opt = Options()){
            if(opt.hasStep()){
                ui::DragFloat(name, &value, opt.getStep() );
            }
            else if(opt.hasMinMax()){
                ui::DragFloat(name, &value, opt.getStep(), opt.getMin(), opt.getMax() );
            }else{
                ui::DragFloat(name, &value);
            }
        }
        
        void draw(const char* name, bool& value, Options opt = Options()){
            ui::Checkbox(name, &value);
        }
        
        
        void draw(const char* name, std::string& value, Options opt = Options()){
            ui::InputText(name, &value[0], 1000);
            
        }

        
        void draw(const char* name, glm::vec2& value, Options opt = Options()){
            
            if(opt.hasStep()){
                ui::DragFloat2(name, &value[0], opt.getStep() );
            }
            else if(opt.hasMinMax()){
                ui::DragFloat2(name, &value[0], opt.getStep(), opt.getMin(), opt.getMax() );
            }else{
                ui::DragFloat2(name, &value[0]);
            }
        }
        
        void draw(const char* name, glm::vec3& value,Options opt = Options()){
            if(opt.hasStep()){
                ui::DragFloat3(name, &value[0], opt.getStep() );
            }
            else if(opt.hasMinMax()){
                ui::DragFloat3(name, &value[0], opt.getStep(), opt.getMin(), opt.getMax() );
            }else{
                ui::DragFloat3(name, &value[0]);
            }
            
            
        }
        
        
        void draw(const char* name, glm::quat& value, Options opt = Options()){
            
            glm::vec3 euler = glm::eulerAngles(value);
            
            if(ui::DragFloat3("quaternion", &euler[0])){
                value = glm::quat(euler);
            }
            
        }
        
        void draw(const char* name, ci::Color& value, Options opt = Options()){
            
            ui::ColorPicker3(name, &value[0]);
            
        }
        
        void setOption(const std::string& elementName, const Options& opt ){
            mElementOptions[elementName] = opt;
        }
        
        int elementCount = 0;
        std::map<std::string, Options> mElementOptions;
    };
    
    
    
    template <class T> inline
    void prologue( ImGuiArchive &, NameValuePair<T> const & )
    { }
    
    template <class T> inline
    void epilogue( ImGuiArchive &, NameValuePair<T> const & )
    {
    }
    
    template <class T, traits::DisableIf<traits::has_minimal_base_class_serialization<T, traits::has_minimal_input_serialization, ImGuiArchive>::value ||
    traits::has_minimal_input_serialization<T, ImGuiArchive>::value> = traits::sfinae> inline
    void prologue( ImGuiArchive & ar, T const & )
    {
        
    }
    
    template <class T, traits::DisableIf<traits::has_minimal_base_class_serialization<T, traits::has_minimal_input_serialization, ImGuiArchive>::value ||
    traits::has_minimal_input_serialization<T, ImGuiArchive>::value> = traits::sfinae> inline
    void epilogue( ImGuiArchive & ar, T const & )
    {
        
    }
    
    template <class T> inline
    void CEREAL_LOAD_FUNCTION_NAME( ImGuiArchive & ar, NameValuePair<T> & t )
    {
        ar.elementCount += 1;
        ar.draw<T>(t.name, t.value);
    }
    
    template <class T> inline
    void CEREAL_LOAD_FUNCTION_NAME( ImGuiArchive & ar, NameValuePair<ci::Color> & t )
    {
        
        ci::app::console() << "color..." << std::endl;
        ar.elementCount += 1;
        ar.draw<T>(t.name, t.value);
    }

    
    template <class T, traits::EnableIf<std::is_arithmetic<T>::value> = traits::sfinae> inline
    void CEREAL_LOAD_FUNCTION_NAME(ImGuiArchive & ar, T & t)
    {
        ar.elementCount += 1;
        std::string name = "." + std::to_string(ar.elementCount);
        ar.draw<T>(name.c_str(), t);
        
    }
    // ######################################################################
    template<class CharT, class Traits, class Alloc> inline
    void CEREAL_LOAD_FUNCTION_NAME(ImGuiArchive & ar, std::basic_string<CharT, Traits, Alloc> & str)
    {
        ar.elementCount += 1;
        std::string name = "." + std::to_string(ar.elementCount);
        ar.draw(name.c_str(), str);
    }
    
    template<class CharT, class Traits, class Alloc> inline
    void CEREAL_LOAD_FUNCTION_NAME(ImGuiArchive & ar, ci::Color& c)
    {
        ci::app::console() << "color" << std::endl;
        
        ar.elementCount += 1;
        std::string name = "." + std::to_string(ar.elementCount);
        ar.draw(name.c_str(), c);
    }
    
} // namespace cereal

// register archives for polymorphic support
CEREAL_REGISTER_ARCHIVE(cereal::ImGuiArchive)

#endif

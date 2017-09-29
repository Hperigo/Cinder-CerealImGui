
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
        ImGuiArchive(  ) : InputArchive<ImGuiArchive>(this){
            
            
        }
        
        ~ImGuiArchive( ) {
            
        }
        
        template <class T> inline
        void draw(const char * name, T & value){
            draw(name, value);
        }
        
        
        void draw(const char * name, int & value){
            ui::DragInt(name, &value);
        }
        
        void draw(const char * name, float & value){
            ui::DragFloat(name, &value);
        }
        
        void draw(const char* name, bool& value){
            ui::Checkbox(name, &value);
        }
        
        
        void draw(const char* name, std::string& value){
            ui::InputText(name, &value[0], 1000);
            
        }

        
        void draw(const char* name, glm::vec2& value){
            ui::DragFloat2(name, &value[0]);
        }
        
        void draw(const char* name, glm::vec3& value){
            ui::DragFloat3(name, &value[0]);
        }
        
        
        void draw(const char* name, glm::quat& value){
            
            glm::vec3 euler = glm::eulerAngles(value);
            
            if(ui::DragFloat3("quaternion", &euler[0])){
                value = glm::quat(euler);
            }
            
        }
        
        int elementCount = 0;
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
} // namespace cereal

// register archives for polymorphic support
CEREAL_REGISTER_ARCHIVE(cereal::ImGuiArchive)

#endif

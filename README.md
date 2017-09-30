Cinder-CerealImGui
===================
#### Bridge between [Immediate mode GUI Library](https://github.com/ocornut/imgui/)  and [Cereal](http://uscilab.github.io/cereal/)  for use with Cinder 0.9.


##### How to use
you need to define a serialize function in your object:

```c++

class Simple{

    public:
    float ffloat = 3.14;
    int   iint = 42;
    ci::vec2 vvec2 {10, 20};

    std::string sstring = "hello world";
};

template<class Archive>
void serialize( Archive& archive, Simple& simple ){
    archive( CEREAL_NVP_( ". custom name ", simple.ffloat), simple.iint, simple.vvec2, simple.sstring  );
}

```

To use the ImGuiArchive, you can just declare it in the draw function
```c++

Simple simpleObject;

void CinderApp::draw()
{
    cereal::ImGuiArchive uiArchive;
    uiArchive(simpleObject);
    
}
```

suports drawing float, int, bool, string ( buggy), glm::vec2, glm::vec3, glm::quat
![e](https://github.com/Hperigo/Cinder-CerealImGui/blob/master/example.png?raw=true "example")

### TODO:
1. fix bug in std::string input
2. add more types?

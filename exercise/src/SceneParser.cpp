#include "SceneParser.hpp"
#include <fstream>
#include "picojson.h"

glm::vec4 to_vec4(picojson::value v){
    glm::vec4 res;
    auto array = v.get<picojson::array>();
    for (int i=0;i<4;i++){
        res[i] = (float)array[i].get<double>();
    }
    return res;
}

glm::vec3 to_vec3(picojson::value v){
    glm::vec3 res;
    auto array = v.get<picojson::array>();
    for (int i=0;i<3;i++){
        res[i] = (float)array[i].get<double>();
    }
    return res;
}



std::vector<GameObjectDescriptor> SceneParser::parseFile(std::string filename){
    std::fstream file(filename);
    picojson::value v;
    file >> v;

    std::vector<GameObjectDescriptor> res;
    for (auto o : v.get("gameobjects").get<picojson::array>()){
        GameObjectDescriptor d;
        d.uniqueId = (int)o.get("uniqueId").get<double>();
        d.meshName = o.get("meshName").get<std::string>();
        d.color = to_vec4(o.get("color"));
        d.position = to_vec3(o.get("position"));
        d.rotationEuler = to_vec3(o.get("rotationEuler"));
        d.scale = to_vec3(o.get("scale"));
        d.parentId = (int)o.get("parentId").get<double>();

        res.push_back(d);
    }
    return res;
}

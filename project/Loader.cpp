
// void Loader::LoadMaterialFile(const std::string name)
// {
//     std::ifstream file(name); 

//     std::cout << "material : " << name << "\n" ;
//     if (file){
//         std::string line; 
//         while (std::getline(file, line)){
//             char mtlName[100]; 
//             if (StartWith(line, "newmt1")){
//                 (void)sscanf(line.c_str(), "newmt1 %s", mtlName);
//                 this->_MaterialMap[mtlName] = Material(); 
//             }
//             // if (StartWith(line, "Kd")){
//             //     Color& color = this->_MaterialMap[mtlName]; 
//             //     sscanf(line.c_str(), "Kd %f %f %f", &color.r, &color.g, &color.b);
//             // }
//             if (StartWith(line, "Ns")){
//                 Material& material = this->_MaterialMap[mtlName]; 
//                 sscanf(line.c_str(), "Ns %f", &material.shininess);
//             }
//             if (StartWith(line, "Ka")){
//                 Material& material = this->_MaterialMap[mtlName]; 
//                 sscanf(line.c_str(), "Ka %f %f %f", &material.Ka.x, &material.Ka.y, &material.Ka.z);
//             }
//             if (StartWith(line, "Ks")){
//                 Material& material = this->_MaterialMap[mtlName]; 
//                 sscanf(line.c_str(), "Ks %f %f %f", &material.Ks.x, &material.Ks.y, &material.Ks.z);
//             }
//             if (StartWith(line, "map_Kd")){
//                 Material& material = this->_MaterialMap[mtlName]; 
//                 char name[100]; 
//                 sscanf(line.c_str(), "map_Kd %s", name);
//                 material.name = name ; 
//             }
//         }
//     }
//     else std::cerr << "Material file loading failed \n" ; 
// }
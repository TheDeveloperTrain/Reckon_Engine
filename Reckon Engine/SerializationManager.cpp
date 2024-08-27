#include "SerializationManager.h"
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <unordered_map>

//Format used
/*
TestScene
-hierarchy
--root
id: 0
parent id: -1
children: 1
--SceneObject
name: root
id: 0
parent id: -1
children: 1
gameobject:
    transform:
     position: 0.000000 0.000000
     rotation: 0.000000
     scale: 1.000000 1.000000
--
--SceneObject
name: Demo object
id: 1
parent id: 0
children:
gameobject:
    transform:
     position: 0.400000 0.600000
     rotation: 0.000000
     scale: 1.000000 1.000000
--

*/

std::string SerializeTransformComponent(Transform transform);
std::string FormatChildIdsAsString(const std::vector<int>& ids);
std::vector<int> GetAllChildIds(std::shared_ptr<SceneObject> object);
int numOrMaxSubStrLength(std::string input, int intentedVal);

// Serialize the scene into a file
void SerializationManager::SerializeScene(Scene scene, std::string relpath)
{
    std::ofstream outFile(relpath + scene.name + ".scene");

    if (!outFile.is_open())
    {
        std::cerr << "Failed to open file for writing: " << relpath + scene.name + ".scene" << std::endl;
        return;
    }

    outFile << scene.name << "\n";
    outFile << "-hierarchy\n";
    outFile << "--root\n";
    outFile << "id: 0\n";
    outFile << "parent id: -1\n";
    outFile << "children: " << FormatChildIdsAsString(GetAllChildIds(scene.root)) << "\n";

    SerializeSceneObject(outFile, scene.root);

    outFile.close();
}

// Serialize a single SceneObject and its children recursively
void SerializationManager::SerializeSceneObject(std::ofstream& outFile, std::shared_ptr<SceneObject> object)
{

    outFile << "--SceneObject\n";
    outFile << "name: " << object->object.name << "\n";
    outFile << "id: " << object->id << "\n";
    outFile << "parent id: " << (object->parent.expired() ? -1 : object->parent.lock()->id) << "\n";
    outFile << "children: " << FormatChildIdsAsString(GetAllChildIds(object)) << "\n";
    outFile << "gameobject:\n";
    outFile << "    transform: \n" << SerializeTransformComponent(object->object.transform);
    outFile << "--\n";
    

    for (auto& child : object->children)
    {
        SerializeSceneObject(outFile, child);
    }
}

Scene SerializationManager::DeserializeScene(std::string relpath)
{
    Scene output;
    std::ifstream inFile(relpath);

    if (!inFile.is_open())
    {
        std::cerr << "Failed to open file for reading: " << relpath << std::endl;
        return output;
    }

    std::unordered_map<int, std::shared_ptr<SceneObject>> idMap;
    std::shared_ptr<SceneObject> currentObject = output.root;
    std::string line;

    while (std::getline(inFile, line))
    {
        // Check for "name" field
        if (line.find("name: ") == 0)
        {
            if (currentObject)
            {
                idMap[currentObject->id] = currentObject;
            }

            currentObject = output.CreateGameObject();
            currentObject->object.name = line.substr(6);
        }
        // Check for "id" field
        else if (line.find("id: ") == 0)
        {
            int objectId = std::stoi(line.substr(4));
            if (currentObject)
            {
                currentObject->id = objectId;

                // Check for duplicate IDs
                if (idMap.find(objectId) != idMap.end())
                {
                    std::cerr << "Duplicate ID found: " << objectId << std::endl;
                    output.root->RemoveChild(currentObject);
                    currentObject = nullptr;
                }
                idMap[objectId] = currentObject;
            }
            else
            {
                std::cout << "current object not initialized but attempted to read id: " << objectId << "\n";
            }
        }
        // Check for "parent id" field
        else if (line.find("parent id: ") == 0)
        {
            if (currentObject)
            {
                int parentId = std::stoi(line.substr(11));
                if (parentId != -1)
                {
                    auto parent = idMap[parentId];
                    if (parent)
                    {
                        currentObject->parent = parent;
                        parent->children.push_back(currentObject);
                    }

                }
            }

        }
        // Check for "position" field
        else if (line.find("position: ") == 5)
        {
            if (currentObject)
            {
                std::istringstream ss(line.substr(15));
                ss >> currentObject->object.transform.position.x >> currentObject->object.transform.position.y >> currentObject->object.transform.position.z;
            }

        }
        // Check for "rotation" field
        else if (line.find("rotation: ") == 5)
        {
            if (currentObject)
            {
                std::istringstream ss(line.substr(15));
                glm::mat4 rotationMatrix;
                for (int i = 0; i < 4; ++i)
                {
                    for (int j = 0; j < 4; ++j)
                    {
                        float value;
                        ss >> value;
                        rotationMatrix[i][j] = value;
                    }
                }
                currentObject->object.transform.rotation = rotationMatrix;
            }

        }
        // Check for "scale" field
        else if (line.find("scale: ") == 5)
        {
            if (currentObject)
            {
                std::istringstream ss(line.substr(12));
                ss >> currentObject->object.transform.scale.x >> currentObject->object.transform.scale.y >> currentObject->object.transform.scale.z;
            }

        }
        else
        {
            std::cout << "Unrecognized line: " << line << "\n";
        }
    }

    inFile.close();
    return output;
}






// ---------------------Helper Functions----------------------------
std::vector<int> GetAllChildIds(std::shared_ptr<SceneObject> object)
{
    std::vector<int> output;
    for (auto& child : object->children)
    {
        output.push_back(child->id);
    }
    return output; // Return the collected child IDs
}

std::string FormatChildIdsAsString(const std::vector<int>& ids)
{
    std::string output;
    for (int id : ids)
    {
        output.append(std::to_string(id) + ";");
    }
    if (!output.empty())
    {
        output.pop_back(); // Remove the trailing semicolon
    }
    return output;
}

std::string SerializeTransformComponent(Transform transform)
{
    std::string output = "";
    output.append("     position: " + std::to_string(transform.position.x) + " " + std::to_string(transform.position.y) + " " + std::to_string(transform.position.z) + "\n");
    output.append("     rotation: ");

    // Serialize the 4x4 rotation matrix
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            output.append(std::to_string(transform.rotation[i][j]) + " ");
        }
    }
    output.append("\n");

    output.append("     scale: " + std::to_string(transform.scale.x) + " " + std::to_string(transform.scale.y) + " " + std::to_string(transform.scale.z) + "\n");
    return output;
}


int numOrMaxSubStrLength(std::string input, int intentedVal)
{
    if (input.length() > intentedVal)
    {
        return intentedVal;
    }
    else 
    {
        return input.length();
    }
}


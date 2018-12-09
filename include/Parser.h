#pragma once

#include "General.h"
#include "Scene.h"
#include <fstream>

/**
 * Undefined behaviour
 *  Input is not according to the specification
 */
struct Parser
{
public:
    static void parse(const std::string& inputFilename);
};

inline void Parser::parse(const std::string& inputFilename)
{
    // Intialize scene and output file name.
    Scene scene;

    // Create an input stream for reading.
    std::ifstream fin(inputFilename);
    if (!fin)
    {
        throw std::runtime_error("File "+inputFilename+" could not be opened for reading.");
    }

    // Parse the scene.
    std::string line;
    while (std::getline(fin, line))
    {
        // Skip comments and blank lines.
        if ((line.find_first_not_of(" \t\r\n") == std::string::npos) || (line[0] == '#'))
        {
            continue;
        }

        // Parse the command in each line.
        std::stringstream pargv(line);
        std::string cmd;
        pargv >> cmd;

        if (cmd == "size")
        {
            int width, height;
            pargv >> width >> height;
            scene.setSize(width, height);
        }
        else if (cmd == "maxdepth")
        {
            int maxDepth;
            pargv >> maxDepth;
            scene.setMaxDepth(maxDepth);
        }
        else if (cmd == "output")
        {
            std::string outputFilename;
            pargv >> outputFilename;
            scene.setOutputFilename(outputFilename);
        }
        else if (cmd == "camera")
        {
            glm::vec3 lookfrom, lookat, up;
            float fovy;
            pargv
                >> lookfrom[0] >> lookfrom[1] >> lookfrom[2]
                >> lookat[0] >> lookat[1] >> lookat[2]
                >> up[0] >> up[1] >> up[2]
                >> fovy;
            scene.setCamera(lookfrom, lookat, up, glm::radians(fovy));
        }
        else if (cmd == "sphere")
        {
            glm::vec3 center;
            float radius;
            pargv
                >> center[0] >> center[1] >> center[2]
                >> radius;
            scene.addSphere(center, radius);
        }
        else if (cmd == "maxverts")
        {
            int maxVerts;
            pargv >> maxVerts;
            scene.setMaxVerts(maxVerts);
        }
        else if (cmd == "vertex")
        {
            glm::vec3 vertex;
            pargv >> vertex[0] >> vertex[1] >> vertex[2];
            scene.addVertex(vertex);
        }
        else if (cmd == "tri")
        {
            int A, B, C;
            pargv >> A >> B >> C;
            scene.addTriangle(A, B, C);
        }
        else if (cmd == "directional")
        {
            glm::vec3 dir, color;
            pargv
                >> dir.x >> dir.y >> dir.z
                >> color.x >> color.y >> color.z;
            scene.addDirLight(dir, color);
        }
        else if (cmd == "point")
        {
            glm::vec3 point, color;
            pargv
                >> point.x >> point.y >> point.z
                >> color.x >> color.y >> color.z;
            scene.addPointLight(point, color);
        }
        else if (cmd == "attenuation")
        {
            glm::vec3 attenuation;
            pargv >> attenuation.x >> attenuation.y >> attenuation.z;
            scene.setAttenuation(attenuation);
        }
        else if (cmd == "ambient")
        {
            glm::vec3 ambient;
            pargv >> ambient.x >> ambient.y >> ambient.z;
            scene.setAmbient(ambient);
        }
        else if (cmd == "diffuse")
        {
            glm::vec3 diffuse;
            pargv >> diffuse.x >> diffuse.y >> diffuse.z;
            scene.setDiffuse(diffuse);
        }
        else if (cmd == "specular")
        {
            glm::vec3 specular;
            pargv >> specular.x >> specular.y >> specular.z;
            scene.setSpecular(specular);
        }
        else if (cmd == "shininess")
        {
            float shininess;
            pargv >> shininess;
            scene.setShininess(shininess);
        }
        else if (cmd == "emission")
        {
            glm::vec3 emission;
            pargv >> emission.x >> emission.y >> emission.z;
            scene.setEmission(emission);
        }
        else if (cmd == "translate")
        {
            glm::vec3 translation;
            pargv >> translation.x >> translation.y >> translation.z;
            scene.translate(translation);
        }
        else if(cmd == "rotate")
        {
            glm::vec3 axis;
            float angle;
            pargv
                >> axis.x >> axis.y >> axis.z
                >> angle;
            scene.rotate(axis, glm::radians(angle));
        }
        else if (cmd == "scale")
        {
            glm::vec3 scaling;
            pargv >> scaling.x >> scaling.y >> scaling.z;
            scene.scale(scaling);
        }
        else if (cmd == "pushTransform")
        {
            scene.pushTransform();
        }
        else if (cmd == "popTransform")
        {
            scene.popTransform();
        }
        else
        {
            std::cerr << "Unrecognised command " << cmd << std::endl;
        }
    }

    scene.render();
}

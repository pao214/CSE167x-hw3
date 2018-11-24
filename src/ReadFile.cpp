#include <ReadFile.h>
#include <sstream>

void ReadFile::readFile(Scene& scene, String& outputFileName)
{
    // Intialize scene and output file name.
    scene.clear();
    outputFileName.clear();

    // Create an input stream for reading.
    std::ifstream fin(fileName);
    if (!fin)
    {
        throw std::runtime_error("File "+fileName+"could not be opened for reading.");
    }

    // Parse the scene.
    std::string line;
    while (std::getline(fin, line))
    {
        // Skip comments and blank lines.
        if ((str.find_first_not_of(" \t\r\n") == string::npos) || (str[0] == '#'))
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
            scene
        }
        else if (cmd == "maxdepth")
        {
            pargv >> maxDepth;
        }
        else if (cmd == "output")
        {
            pargv >> outputFileName;
        }
        else if (cmd == "camera")
        {
            pargv
                >> lookfrom[0] >> lookfrom[1] >> lookfrom[2]
                >> lookat[0] >> lookat[1] >> lookat[2]
                >> up[0] >> up[1] >> up[2]
                >> fovy;
            fovy = fovy*(PI/180.);
            fovx = 2.*atan(tan(fovy/2)*width/height);
        }
    }
}

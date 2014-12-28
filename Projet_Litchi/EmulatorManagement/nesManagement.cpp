#include "nesManagement.h"

NesManagement::NesManagement()
{
}

void NesManagement::configureEmulator(const QString path, std::vector<JoystickType> joysticksType)
{
    /*if you want to make fceux full screen, you need to change
    a line in the cfg.*/

    int numberOfJoystick = joysticksType.size();
    std::map<std::string,std::string> lineToDeleteAndReplace;

    int i;
    for(i = 0; i < numberOfJoystick; i++)
    {
        JoystickType joystickType = joysticksType.at(i);

        std::ostringstream oss;
        oss << i;
        std::string manetteChoosen = oss.str();

        switch(joystickType)
        {
            case 0 : //Playstation
            {
                lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "A "] = "SDL.Input.GamePad." + manetteChoosen + "A = 1 \n";
                lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "B "] = "SDL.Input.GamePad." + manetteChoosen + "B = 2 \n";
                lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "Up "] = "SDL.Input.GamePad." + manetteChoosen + "Up = 8193 \n";
                lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "Down "] = "SDL.Input.GamePad." + manetteChoosen + "Down = 8196 \n";
                lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "Left "] = "SDL.Input.GamePad." + manetteChoosen + "Left = 8200 \n";
                lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "Right "] = "SDL.Input.GamePad." + manetteChoosen + "Right = 8194 \n";
                lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "Select "] = "SDL.Input.GamePad." + manetteChoosen + "Select = 8 \n";
                lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "Start "] = "SDL.Input.GamePad." + manetteChoosen + "Start = 9 \n";
                break;
            }

            case 1 : //XBox
            {
                lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "A "] = "SDL.Input.GamePad." + manetteChoosen + "A = 2 \n";
                lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "B "] = "SDL.Input.GamePad." + manetteChoosen + "B = 3 \n";
                lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "Up "] = "SDL.Input.GamePad." + manetteChoosen + "Up = 8193 \n";
                lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "Down "] = "SDL.Input.GamePad." + manetteChoosen + "Down = 8196 \n";
                lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "Left "] = "SDL.Input.GamePad." + manetteChoosen + "Left = 8200 \n";
                lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "Right "] = "SDL.Input.GamePad." + manetteChoosen + "Right = 8194 \n";
                lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "Select "] = "SDL.Input.GamePad." + manetteChoosen + "Select = 6 \n";
                lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "Start "] = "SDL.Input.GamePad." + manetteChoosen + "Start = 7 \n";
                break;
            }

            default :
                break;
        }

        lineToDeleteAndReplace["SDL.Input." + manetteChoosen + " "] = "SDL.Input." + manetteChoosen + " = GamePad." + manetteChoosen + " \n";
        lineToDeleteAndReplace["SDL.Input.GamePad." + manetteChoosen + "DeviceType "] = "SDL.Input.GamePad." + manetteChoosen + "DeviceType = Joystick \n";
    }

    lineToDeleteAndReplace["SDL.Fullscreen "] = "SDL.Fullscreen = 1 \n";
    std::string buffer = "";

    std::string configFilePath = path.toStdString() + "/../Emulators/Nes/fceux.cfg";
    std::ifstream readFile(configFilePath);
    if (readFile)
       {
           std::string line;
           int lineNumber = 0;
           while ( std::getline(readFile, line))
           {
               lineNumber++;
               std::string changedLine = line.substr(0, line.find_last_of('='));

               if(lineToDeleteAndReplace.find(changedLine) != lineToDeleteAndReplace.end())
               {
                   buffer += lineToDeleteAndReplace[changedLine];
               }
               else
               {
                   buffer += line + "\n";
               }
           }
       }
       readFile.close();

       std::ofstream writeFile(configFilePath);
          writeFile << buffer;
          writeFile.close();

}

void NesManagement::checkRoms(const QString)
{
}


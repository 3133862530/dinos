#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include <vector>
#include <string>

using namespace sf;
using namespace std;


#include "headers/dino.hpp"
#include "headers/obstacle.hpp"
#include "headers/cloud.hpp"
#include "headers/bird.hpp"
#include "headers/dinoGame.hpp"

//"the animation get frozen in a jump after a death"

int main()
{
  DinoGame dinoGame(1500,750);
  while (!Start()) {};

  dinoGame.Run();
  return 0;
}

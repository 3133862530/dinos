#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <fstream>

using namespace sf;
using namespace std;


#include "dino.h"
#include "obstacle.h"
#include "cloud.h"
#include "bird.h"
#include "dinoGame.h"
#include "Login.h"


//"��Ծ״̬�����ᵼ����̬�쳣"

int main()
{
	if (Login())//�ɹ�ע��Ϳ�ʼ��Ϸ
	{
		DinoGame dinoGame(1500, 750);
	    dinoGame.Run();
	}
	
	return 0;
}

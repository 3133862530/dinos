#pragma once
class DinoGame
{
private:
    int w, h;//窗口大小
    Dino* dino;//龙龙
    bool gameover;
    int gravity;
    float speed;

    int score;
    int bestScore;

    vector<Obstacle*> obstacles;// 障碍物列表

    vector<Cloud*> clouds;// 云朵列表

    vector<Bird*> birds;// 鸟列表

    int obstacleTimer, randomAdditionObstacle, cloudTimer, randomAdditionCloud, birdTimer, randomAdditionBird;
    //生成计时器和随机附加值

    Texture cactiTexture;
    Texture smallCactusTexture;
    Texture bigCactusTexture;


    bool death;

    bool isPaused;

public:
    DinoGame(int height, int width)
    {
        srand(time(NULL));
        //将随机距离初始化为0
        randomAdditionObstacle = 0;
        randomAdditionCloud = 0;
        randomAdditionBird = 0;

        //设定尺寸
        h = height; w = width;
        isPaused = false;
        //创建龙龙
        dino = new Dino(100, 600);

        //重置
        gameover = false;

        //设置物理量
        gravity = 1;
        speed = 10;


        obstacleTimer = 0;
        cloudTimer = 0;
        birdTimer = 0;


        score = 0;
        bestScore = 0;

        //载入皮
        cactiTexture.loadFromFile("art/cacti.png");
        smallCactusTexture.loadFromFile("art/cactusSmall.png");
        bigCactusTexture.loadFromFile("art/cactusBig.png");


        death = true;
    }

    ~DinoGame() {
        delete dino;
        for (int i = 0; i < obstacles.size(); i++) {
            delete obstacles[i];
        }
        for (int i = 0; i < clouds.size(); i++) {
            delete clouds[i];
        }
        for (int i = 0; i < birds.size(); i++) {
            delete birds[i];
        }
    }



    void Run()
    {
        RenderWindow window(VideoMode(h, w), "Dino Game", Style::Close | Style::Resize);
        //创建一个游戏窗口，宽度为 w，高度为 h，标题为“Dino Game”。窗口样式允许关闭和调整大小
        //SFML好麻烦

        window.setFramerateLimit(60);//设定窗口帧率

        Font font;//字体对象
        font.loadFromFile("art/font.ttf");

        window.clear(sf::Color(255, 255, 255));

        Text StartText("Press any key to start", font, 48);
        StartText.setOrigin(0, 0);
        StartText.setPosition(350, 250);
        StartText.setFillColor(Color::Black);
        window.draw(StartText);
        Text UsingText("Press the space to jump  down to duck", font, 25);
        UsingText.setOrigin(0, 0);
        UsingText.setPosition(410, 350);
        UsingText.setFillColor(Color::Black);
        window.draw(UsingText);

        Texture Begin;//初始界面加只小恐龙美化
        Begin.loadFromFile("art/dino.png");
        //这个向量表示一个大小为 90 像素宽、110 像素高的矩形，用于绘制站立或跳跃状态的恐龙。
        RectangleShape dinoShape(Vector2f(90.0f, 110.0f));
        dinoShape.setTexture(&Begin);
        dinoShape.setOrigin(45.0f, 55.0f);

        dinoShape.setPosition(370, 200); //设置矩形形状的位置

        window.draw(dinoShape);//绘制

        window.display();

        bool start = false;
        while (!start && window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    window.close();
                }
                else if (event.type == Event::KeyPressed)
                {
                    start = true;
                }
            }
        }


        while (window.isOpen())
        {
            Event evnt;
            while (window.pollEvent(evnt))//检查并处理所有的窗口事件
            {
                switch (evnt.type)
                {
                case Event::Closed:window.close(); break;

                case Event::KeyPressed:
                    if (gameover)
                    {//游戏结束后的重置
                        dino->Reset();

                        obstacles.clear();
                        clouds.clear();
                        birds.clear();

                        speed = 10;
                        score = 0;

                        gameover = false;
                    }
                }
            }

            //检查游戏是否还在运行
            if (!gameover)
            {

                Input();//处理输入

                if (isPaused)
                {
                    window.clear(sf::Color(255, 255, 255));
                    DrawAll(window, font);




                    Text PauseText("Press P to restart", font, 48);
                    PauseText.setOrigin(0, 0);
                    PauseText.setPosition(370, 350);
                    PauseText.setFillColor(Color::Black);
                    window.draw(PauseText);

                    window.display();
                    continue;//循环至此跳出并仅渲染当前帧

                }

                window.clear(sf::Color(255, 255, 255));

                DrawAll(window, font);//绘制当下的一切

                dino->Update(gravity, false);

                updateObstacles();
                updateClouds();
                updateBirds();

                if (death)
                    Logic();
                //持续加速
                speed += 0.002;

                //不断累积分数
                score++;
            }
            else
            {//鼠了
                if (score > bestScore)//记录最高分
                {
                    bestScore = score;
                }

                window.clear(sf::Color(255, 255, 255));

                dino->unduck();

                DrawAll(window, font);

                dino->Update(gravity, true);

                Text RestartText("Press Any Key to restart", font, 48);
                RestartText.setOrigin(0, 0);
                RestartText.setPosition(350, 250);
                RestartText.setFillColor(Color::Black);

                Text FinishText("Or Press B to Break", font, 48);
                FinishText.setOrigin(0, 0);
                FinishText.setPosition(390, 380);
                FinishText.setFillColor(Color::Black);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
                {
                    window.close();
                }

                window.draw(RestartText);
                window.draw(FinishText);

            }

            window.display();//显示当前帧内容


        }
    }

    string getScoreString(int score)//记分牌
    {
        switch (to_string(score / 10).length()) {
        case 1:
            return "0000" + to_string(score / 10);
            break;
        case 2:
            return "000" + to_string(score / 10);
            break;
        case 3:
            return "00" + to_string(score / 10);
            break;
        case 4:
            return "0" + to_string(score / 10);
            break;
        case 5:
            return to_string(score / 10);
            break;
        default:
            return "99999";
            break;
        }
    }
    void DrawAll(RenderWindow& window, Font& font) {

        RectangleShape ground(Vector2f(1500.0f, 125.0f));
        ground.setOrigin(750.0f, 62.5f);
        ground.setFillColor(Color::White);
        ground.setPosition(750, 700);
        ground.setOutlineColor(Color::Black);
        ground.setOutlineThickness(2.0f);//设置地面轮廓线的厚度为 2 像素

        window.draw(ground);


        //绘制所有物体
        for (int i = 0; i < obstacles.size(); i++)
        {
            obstacles[i]->Draw(window);
        }
        for (int i = 0; i < clouds.size(); i++)
        {
            clouds[i]->Draw(window);
        }
        for (int i = 0; i < birds.size(); i++)
        {
            birds[i]->Draw(window);
        }

        dino->Draw(window);

        //创建分数的文本
        Text scoreText(getScoreString(score), font, 30);
        scoreText.setOrigin(0, 0);
        scoreText.setPosition(w + 600, 30);
        scoreText.setFillColor(Color::Black);
        window.draw(scoreText);

        if (bestScore != 0) {
            //high score
            Text bestScoreText("Hi " + getScoreString(bestScore), font, 30);
            bestScoreText.setOrigin(0, 0);
            bestScoreText.setPosition(w + 350, 30);
            bestScoreText.setFillColor(Color::Black);
            window.draw(bestScoreText);
        }
    }

    //----------------------------------------------------------------------------
    //                                   Vectors
    //----------------------------------------------------------------------------
    void addCloud()
    {
        Cloud* cloud = new Cloud(w);//使用游戏窗口的宽度 w 作为参数来初始化云的位置
        clouds.push_back(cloud);

        randomAdditionCloud = rand() % 75;//随机数，控制下一次添加云的时间间隔
        cloudTimer = 0;
    }


    void updateClouds()
    {

        cloudTimer++;


        for (int i = 0; i < clouds.size(); i++)
        {
            clouds[i]->Update(speed);
            if (clouds[i]->getX() < 5)//移动至边界
            {
                clouds.erase(clouds.begin() + i);//删除
            }
        }


        if (randomAdditionCloud + 200 == cloudTimer)
        {
            addCloud();
        }

    }

    void addBird() {
        Bird* bird = new Bird();
        birds.push_back(bird);

        randomAdditionBird = rand() % 100;
        birdTimer = 0;

        obstacleTimer = 0;
    }

    void updateBirds() {
        birdTimer++;


        for (int i = 0; i < birds.size(); i++)
        {
            birds[i]->Update(speed);//都是实时更新速度
            if (birds[i]->getX() < 5)
            {
                birds.erase(birds.begin() + i);
            }
        }


        if (randomAdditionBird + 200 <= birdTimer && obstacleTimer > 55 && score / 10 > 300)//鸟在得分大于300后开始刷新
        {
            addBird();
        }
    }
    void addObstacle()
    {
        int type = rand() % 3;
        switch (type)
        {
        case 0:
        {
            Obstacle* obstacle = new Obstacle(1500, type, bigCactusTexture);
            obstacles.push_back(obstacle); }
        break;
        case 1:
        {
            Obstacle* obstacle = new Obstacle(1500, type, smallCactusTexture);
            obstacles.push_back(obstacle); }
        break;
        case 2:
        {
            Obstacle* obstacle = new Obstacle(1500, type, cactiTexture);
            obstacles.push_back(obstacle); }
        break;
        }


        randomAdditionObstacle = (int)(rand() % (50 / (int)((float)speed * .1)));
        //随机数 用于下次生成
        obstacleTimer = 0;
    }

    void updateObstacles()
    {

        obstacleTimer++;


        for (int i = 0; i < obstacles.size(); i++)
        {
            obstacles[i]->Update(speed);
            if (obstacles[i]->getX() < 5)
            {
                obstacles.erase(obstacles.begin() + i);
            }
        }


        if (randomAdditionObstacle + 60 == obstacleTimer)
        {
            addObstacle();
        }

    }
    //----------------------------------------------------------------------------
    //                              Input & Logic
    //----------------------------------------------------------------------------



    void Input()
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
        {
            isPaused = !isPaused;

            sf::sleep(sf::milliseconds(100));//添加短暂延迟来防止快速切换状态
        }


        if (isPaused)
        {
            return;
        }

        //keyboard input
        if (Keyboard::isKeyPressed(Keyboard::Key::Space))
        {
            dino->Jump();
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Down))
        {
            dino->Duck();
        }
        else
        {
            dino->unduck();
        }

    }
    bool checkCollision(int x, int y, int oWidth, int oHeight, int xTwo, int yTwo, int oTwoWidth, int oTwoHeight)//碰撞测试
    {
        // AABB 1
        int x1Min = x;
        int x1Max = x + oWidth;
        int y1Max = y + oHeight;
        int y1Min = y;

        // AABB 2
        int x2Min = xTwo;
        int x2Max = xTwo + oTwoWidth;
        int y2Max = yTwo + oTwoHeight;
        int y2Min = yTwo;

        // Collision tests
        if (x1Max < x2Min || x1Min > x2Max)
        {
            return false;
        }
        if (y1Max < y2Min || y1Min > y2Max)
        {
            return false;
        }

        return true;
    }

    void Logic()
    {
        int dinoX = 100;
        int dinoY = dino->getY();
        int dinoW = 80;
        int dinoH = 100;

        if (dino->isDuck())
        {
            dinoW = 140;
            dinoH = 44;
        }

        for (int i = 0; i < obstacles.size(); i++)
        {
            int obstacleX = obstacles[i]->getX();
            int obstacleY = obstacles[i]->getY();
            int obstacleW = obstacles[i]->getW();
            int obstacleH = obstacles[i]->getH();

            if (checkCollision(dinoX, dinoY, dinoW, dinoH, obstacleX, obstacleY, obstacleW, obstacleH))
            {
                gameover = true;
            }

        }

        int birdW = 90;
        int birdH = 100;

        for (int i = 0; i < birds.size(); i++)
        {
            int birdX = birds[i]->getX();
            int birdY = birds[i]->getY();

            if ((birdY == 510 || birdY == 550) && dino->isDuck())
            {

            }
            else
            {
                if (checkCollision(dinoX, dinoY, dinoW, dinoH, birdX, birdY, birdW, birdH))
                {
                    gameover = true;
                }
            }


        }
    }
};

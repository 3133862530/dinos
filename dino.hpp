class Dino
{
private:
  int y;//恐龙y轴位置
  int velocityY, thrust;//恐龙的纵向速度和跳跃力
  int originalY;//恐龙的初始纵向位置
  int runTimer;//控制动画切换的计时器
  int textureIndex;//当前纹理的索引
  bool duck;//标志位，表示恐龙是否处于蹲下状态

  bool dead;//标志位，表示恐龙是否死亡

  vector<Texture> textures;//存储各种状态下恐龙的纹理

  Texture dinoTexture;
  Texture dinoRun1;
  Texture dinoRun2;
  Texture dinoJump;
  Texture dinoDead;
  Texture dinoDuck1;
  Texture dinoDuck2;


  void animate()//控制恐龙动画的播放
  {
    cout<<dead<<endl;
    if(!dead){
      if (y == originalY)//在地面
      {
        if(runTimer == 5)//切换动画帧
        {
          if(!duck)//在跑步形态中切换
          {
            switch(textureIndex)
            {
              case 0: //start
                textureIndex = 1;
                break;
              case 1: //run
                textureIndex = 2;
                break;
              case 2: //run
                textureIndex = 1;
                break;
              case 3: //run
                textureIndex = 1;
                break;
              default:
                textureIndex = 1;
                break;
            }
          }else//在蹲下状态中切换
          {
            switch(textureIndex)
            {
              case 5:
                textureIndex = 6;
                break;
              case 6:
                textureIndex = 5;
                break;
              default:
                textureIndex = 6;
                break;
            }
          }

          runTimer = 0;
        }
      }else//在空中
      { 
        textureIndex = 3;
        runTimer = 0;
      }
    }else//死了
    {
      textureIndex = 4;
    }
    runTimer++;
  }
public:
  inline int getY()//返回当前y坐标
  {
      return y;
  }

  Dino(int posX, int posY)//初始化恐龙对象，设定位置和状态
  {
    y=posY;
    velocityY = 0;
    thrust = 22;
    originalY=posY;
    runTimer = 0;
    textureIndex = 0;
    duck = false;
    dead = false;

    dinoTexture.loadFromFile("art/dino.png");//初始状态

    dinoRun1.loadFromFile("art/dinoRun1.png");
    dinoRun2.loadFromFile("art/dinoRun2.png");//两种跑步形态

    dinoJump.loadFromFile("art/dinoJump.png");

    dinoDead.loadFromFile("art/dinoDead.png");

    dinoDuck1.loadFromFile("art/dinoDuck1.png");
    dinoDuck2.loadFromFile("art/dinoDuck2.png");//两种躲避形态

    textures.push_back(dinoTexture);
    textures.push_back(dinoRun1);
    textures.push_back(dinoRun2);
    textures.push_back(dinoJump);
    textures.push_back(dinoDead);
    textures.push_back(dinoDuck1);
    textures.push_back(dinoDuck2);

  }
  void Duck()//蹲下
  {
      duck = true;
  }

  inline void unduck()//站起来
  {
      duck = false;
  }

  inline bool isDuck()
  {
      return duck;
  }

  inline void Reset()//重置恐龙的状态和位置
  {
      y=originalY;
      unduck();
  }

  void Update(int gravity, bool quit)
  {
    dead = quit ? true : false;
    if (!quit){
      animate();
      if(y < originalY){//above ground
        velocityY += gravity;
      }else if(y > originalY){//below ground
        y = originalY;
      }else{//on ground
        if(velocityY == thrust){
          velocityY = 0;
        }
      }

      y += velocityY;
    }else{
      animate();
    }
  }

  void Jump()
  {
    if (y == originalY)
    {
      velocityY -= thrust;
    }
  }

  void Draw(RenderWindow& window)
  {
    if(duck && y==originalY)// 判断恐龙是否蹲下并且在地面上
    {
      //这个向量表示一个大小为 120 像素宽、44 像素高的矩形，用于绘制蹲下状态的恐龙。
      RectangleShape dinoShape(Vector2f(120.0f,44.0f));
      
      
      //设置矩形形状的纹理，使用当前的纹理索引
      dinoShape.setTexture(&textures[textureIndex]);
      //设置矩形形状的原点，方便旋转和平移
      dinoShape.setOrigin(60.0f, 22.0f);

      //设置矩形形状的位置，蹲下时需要向下移动一点
      dinoShape.setPosition(100,y+30);
      //设置矩形形状的轮廓颜色和厚度
      dinoShape.setOutlineColor(Color::Black);
      dinoShape.setOutlineThickness(2.0f);

      //将矩形形状绘制到窗口中
      window.draw(dinoShape);
    }
    else// 恐龙未蹲下或者不在地面上
    {
      //这个向量表示一个大小为 90 像素宽、110 像素高的矩形，用于绘制站立或跳跃状态的恐龙。
      RectangleShape dinoShape(Vector2f(90.0f,110.0f));
      
      
      //设置矩形形状的纹理，使用当前的纹理索引
      dinoShape.setTexture(&textures[textureIndex]);
      //设置矩形形状的原点，方便旋转和平移
      dinoShape.setOrigin(45.0f, 55.0f);

      //设置矩形形状的位置
      dinoShape.setPosition(100,y);
      //绘制
      window.draw(dinoShape);
    }

  }

};

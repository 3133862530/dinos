class Dino
{
private:
  int y;//����y��λ��
  int velocityY, thrust;//�����������ٶȺ���Ծ��
  int originalY;//�����ĳ�ʼ����λ��
  int runTimer;//���ƶ����л��ļ�ʱ��
  int textureIndex;//��ǰ���������
  bool duck;//��־λ����ʾ�����Ƿ��ڶ���״̬

  bool dead;//��־λ����ʾ�����Ƿ�����

  vector<Texture> textures;//�洢����״̬�¿���������

  Texture dinoTexture;
  Texture dinoRun1;
  Texture dinoRun2;
  Texture dinoJump;
  Texture dinoDead;
  Texture dinoDuck1;
  Texture dinoDuck2;


  void animate()//���ƿ��������Ĳ���
  {
    cout<<dead<<endl;
    if(!dead){
      if (y == originalY)//�ڵ���
      {
        if(runTimer == 5)//�л�����֡
        {
          if(!duck)//���ܲ���̬���л�
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
          }else//�ڶ���״̬���л�
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
      }else//�ڿ���
      { 
        textureIndex = 3;
        runTimer = 0;
      }
    }else//����
    {
      textureIndex = 4;
    }
    runTimer++;
  }
public:
  inline int getY()//���ص�ǰy����
  {
      return y;
  }

  Dino(int posX, int posY)//��ʼ�����������趨λ�ú�״̬
  {
    y=posY;
    velocityY = 0;
    thrust = 22;
    originalY=posY;
    runTimer = 0;
    textureIndex = 0;
    duck = false;
    dead = false;

    dinoTexture.loadFromFile("art/dino.png");//��ʼ״̬

    dinoRun1.loadFromFile("art/dinoRun1.png");
    dinoRun2.loadFromFile("art/dinoRun2.png");//�����ܲ���̬

    dinoJump.loadFromFile("art/dinoJump.png");

    dinoDead.loadFromFile("art/dinoDead.png");

    dinoDuck1.loadFromFile("art/dinoDuck1.png");
    dinoDuck2.loadFromFile("art/dinoDuck2.png");//���ֶ����̬

    textures.push_back(dinoTexture);
    textures.push_back(dinoRun1);
    textures.push_back(dinoRun2);
    textures.push_back(dinoJump);
    textures.push_back(dinoDead);
    textures.push_back(dinoDuck1);
    textures.push_back(dinoDuck2);

  }
  void Duck()//����
  {
      duck = true;
  }

  inline void unduck()//վ����
  {
      duck = false;
  }

  inline bool isDuck()
  {
      return duck;
  }

  inline void Reset()//���ÿ�����״̬��λ��
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
    if(duck && y==originalY)// �жϿ����Ƿ���²����ڵ�����
    {
      //���������ʾһ����СΪ 120 ���ؿ�44 ���ظߵľ��Σ����ڻ��ƶ���״̬�Ŀ�����
      RectangleShape dinoShape(Vector2f(120.0f,44.0f));
      
      
      //���þ�����״������ʹ�õ�ǰ����������
      dinoShape.setTexture(&textures[textureIndex]);
      //���þ�����״��ԭ�㣬������ת��ƽ��
      dinoShape.setOrigin(60.0f, 22.0f);

      //���þ�����״��λ�ã�����ʱ��Ҫ�����ƶ�һ��
      dinoShape.setPosition(100,y+30);
      //���þ�����״��������ɫ�ͺ��
      dinoShape.setOutlineColor(Color::Black);
      dinoShape.setOutlineThickness(2.0f);

      //��������״���Ƶ�������
      window.draw(dinoShape);
    }
    else// ����δ���»��߲��ڵ�����
    {
      //���������ʾһ����СΪ 90 ���ؿ�110 ���ظߵľ��Σ����ڻ���վ������Ծ״̬�Ŀ�����
      RectangleShape dinoShape(Vector2f(90.0f,110.0f));
      
      
      //���þ�����״������ʹ�õ�ǰ����������
      dinoShape.setTexture(&textures[textureIndex]);
      //���þ�����״��ԭ�㣬������ת��ƽ��
      dinoShape.setOrigin(45.0f, 55.0f);

      //���þ�����״��λ��
      dinoShape.setPosition(100,y);
      //����
      window.draw(dinoShape);
    }

  }

};

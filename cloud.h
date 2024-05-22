#pragma once
class Cloud
{
private:
    int x, y;
    Texture cloudTexture;
public:
    Cloud(int posX)
    {
        x = 2 * (posX + 50);//�Ƶ�ˮƽλ��
        y = rand() % 250 + 50;//������ɲ������Ƶĳ�ʼ y ����
        cloudTexture.loadFromFile("art/cloudTexture.JPG");
    }
    inline int getX()
    {
        return x;
    }

    void Update(float speed)//������Ϸ�ٶȸ����Ƶ�λ��
    {
        x -= (speed / 4);
    }
    void Draw(RenderWindow& window)
    {
        RectangleShape cloudShape(Vector2f(200.0f, 80.0f));
        cloudShape.setOrigin(100.0f, 40.0f);
        cloudShape.setPosition(x, y);//���þ�����״��λ��Ϊ��ǰ�Ƶ�����
        cloudShape.setTexture(&cloudTexture);

        window.draw(cloudShape);
    }

};

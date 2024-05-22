#pragma once
class Cloud
{
private:
    int x, y;
    Texture cloudTexture;
public:
    Cloud(int posX)
    {
        x = 2 * (posX + 50);//云的水平位置
        y = rand() % 250 + 50;//随机生成并设置云的初始 y 坐标
        cloudTexture.loadFromFile("art/cloudTexture.JPG");
    }
    inline int getX()
    {
        return x;
    }

    void Update(float speed)//根据游戏速度更新云的位置
    {
        x -= (speed / 4);
    }
    void Draw(RenderWindow& window)
    {
        RectangleShape cloudShape(Vector2f(200.0f, 80.0f));
        cloudShape.setOrigin(100.0f, 40.0f);
        cloudShape.setPosition(x, y);//设置矩形形状的位置为当前云的坐标
        cloudShape.setTexture(&cloudTexture);

        window.draw(cloudShape);
    }

};

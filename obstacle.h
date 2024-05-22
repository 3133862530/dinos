#pragma once
class Obstacle
{
private:
    int x, y;
    float w, h;// 障碍物的宽度和高度
    int type;
    Texture texture;

    void drawBigCactus(RenderWindow& window)
    {
        RectangleShape cactusBigShape(Vector2f(w, h));
        cactusBigShape.setOrigin(25.0f, 55.0f);
        cactusBigShape.setPosition(x, y);
        cactusBigShape.setTexture(&texture);
        //cactusBigShape.setOutlineColor(Color::Black);
        cactusBigShape.setOutlineThickness(2.0f);

        window.draw(cactusBigShape);
    }

    void drawSmallCactus(RenderWindow& window)
    {
        RectangleShape cactusSmallShape(Vector2f(w, h));
        cactusSmallShape.setOrigin(20.0f, 40.0f);
        cactusSmallShape.setPosition(x, y);
        cactusSmallShape.setTexture(&texture);
        //cactusSmallShape.setOutlineColor(Color::Black);
        cactusSmallShape.setOutlineThickness(2.0f);
        window.draw(cactusSmallShape);
    }

    void drawCacti(RenderWindow& window)
    {
        RectangleShape cactiShape(Vector2f(w, h));
        cactiShape.setOrigin(45.0f, 40.0f);
        cactiShape.setPosition(x, y);
        cactiShape.setTexture(&texture);
        //cactiShape.setOutlineColor(Color::Black);
        cactiShape.setOutlineThickness(2.0f);
        window.draw(cactiShape);
    }
public:
    Obstacle() {}
    Obstacle(int posX, int typeNum, Texture& textureRef)
    {
        x = posX;
        type = typeNum;
        texture = textureRef;
        switch (type)
        {
        case 0: //大
            y = 600;
            w = 50.0f;
            h = 110.0f;
            break;
        case 1: //小
            y = 615;
            w = 40.0f;
            h = 80.0f;
            break;
        case 2: //组
            y = 615;
            w = 90.0f;
            h = 80.0f;
            break;
        };
    };

    inline int getX() { return x; }
    inline int getY() { return y; }
    inline int getW() { return w; }
    inline int getH() { return h; }

    void Update(int speed)
    {
        x -= speed;
    }

    void Draw(RenderWindow& window)
    {
        switch (type)
        {
        case 0:
            drawBigCactus(window);
            y = 600;
            break;
        case 1:
            drawSmallCactus(window);
            y = 615;
            break;
        case 2:
            drawCacti(window);
            y = 615;
            break;
        }

    }

};


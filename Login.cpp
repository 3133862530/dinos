#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <fstream>
#include"Login.h"
using namespace sf;
/*
art/font.ttf
*/
struct Account
{
    std::string username;
    std::string password;
};
//检查用户输入的用户名和密码是否与已注册的账号信息匹配
bool login(const std::string& username, const std::string& password, const std::vector<Account>& accounts)
{
    for (const auto& acc : accounts)//C++11循环的新写法！
    {
        if (acc.username == username && acc.password == password)
        {
            return true; // Login successful
        }
    }
    return false; // Login failed
}
//注册新账号
void registerAccount(const std::string& username, const std::string& password, std::vector<Account>& accounts)
{
    accounts.push_back({ username, password });
    std::ofstream outputFile("accounts.txt", std::ios::app);
    if (outputFile.is_open()) {
        outputFile << username << " " << password << "\n";
        outputFile.close();
        std::cout << "成功注册！\n";
    }
    else {
        std::cerr << "文件读取大失败！\n";
    }
}

bool Login()
{
    sf::RenderWindow window(sf::VideoMode(900, 800), "Login System");

    sf::Font font;
    if (!font.loadFromFile("art/font.ttf"))
    {
        std::cerr << "Failed to load font\n";
        return false;
    }

   

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    std::vector<Account> accounts;
    std::ifstream inputFile("accounts.txt");
    if (inputFile.is_open())
    {
        std::string line;
        while (std::getline(inputFile, line)) 
        {
            std::istringstream iss(line);
            std::string username, password;
            if (iss >> username >> password) 
            {
                accounts.push_back({ username, password });
            }
        }
        inputFile.close();
    }
    else
    {
        std::cout << "文件鼠了。\n";
    }

    std::string usernameInput;
    std::string passwordInput;
    bool loggedIn = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)//关则关
                window.close();

            if (!loggedIn && event.type == sf::Event::TextEntered)//如果用户尚未登录，并且输入了文本事件
            {
                if (event.text.unicode == '\n') // 检查是否按下回车
                {//如果按下了回车键，表示用户完成了一次输入
                    if (usernameInput.empty()) 
                    {
                        usernameInput = text.getString();//将输入的文本赋值
                        text.setString(""); // 清空文本框
                    }
                    else {
                        passwordInput = text.getString();//同上
                        text.setString(""); //清空文本框
                        if (usernameInput.empty() || passwordInput.empty()) //检查用户名和密码是否为空
                        {
                            std::cout << "Username or password cannot be empty.\n";
                            continue; // Skip login/register logic if username or password is empty
                        }
                        if (!login(usernameInput, passwordInput, accounts)) //判断是否存在账号
                        {
                            std::cout << "Login failed. Registering new account.\n";
                            //这里的逻辑是判断库中未存在这组账号密码
                            //自动为用户注册新账号
                            registerAccount(usernameInput, passwordInput, accounts);//测！
                        }
                        else
                        {
                            std::cout << "Login successful.\n";
                        }
                        loggedIn = true;
                        return loggedIn;
                    }
                }
                else if (event.text.unicode == '\b' && !text.getString().isEmpty()) // 处理<-键的情况
                {
                    sf::String str = text.getString();//给
                    str.erase(str.getSize() - 1);//减
                    text.setString(str);//还
                }
                else if (event.text.unicode < 128) // 只能输入普通字符
                {
                    text.setString(text.getString() + static_cast<char>(event.text.unicode));
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(text);
        Texture LoginDino;//初始界面加只小恐龙美化
        LoginDino.loadFromFile("art/dino.png");
        //这个向量表示一个大小为 90 像素宽、110 像素高的矩形，用于绘制站立或跳跃状态的恐龙。
        RectangleShape LoginDinoShape(Vector2f(180.0f, 220.0f));
        LoginDinoShape.setTexture(&LoginDino);
        LoginDinoShape.setOrigin(45.0f, 55.0f);

        LoginDinoShape.setPosition(150, 300); //设置矩形形状的位置

        window.draw(LoginDinoShape);//绘制

        Text LoginText("Please Login!\ninput ID and Password with CTRL+ENTER", font, 30);
        LoginText.setOrigin(0, 0);
        LoginText.setPosition(10, 490);
        LoginText.setFillColor(Color::Black);
        window.draw(LoginText);

        
        window.display();
    }
}


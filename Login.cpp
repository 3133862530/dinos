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
//����û�������û����������Ƿ�����ע����˺���Ϣƥ��
bool login(const std::string& username, const std::string& password, const std::vector<Account>& accounts)
{
    for (const auto& acc : accounts)//C++11ѭ������д����
    {
        if (acc.username == username && acc.password == password)
        {
            return true; // Login successful
        }
    }
    return false; // Login failed
}
//ע�����˺�
void registerAccount(const std::string& username, const std::string& password, std::vector<Account>& accounts)
{
    accounts.push_back({ username, password });
    std::ofstream outputFile("accounts.txt", std::ios::app);
    if (outputFile.is_open()) {
        outputFile << username << " " << password << "\n";
        outputFile.close();
        std::cout << "�ɹ�ע�ᣡ\n";
    }
    else {
        std::cerr << "�ļ���ȡ��ʧ�ܣ�\n";
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
        std::cout << "�ļ����ˡ�\n";
    }

    std::string usernameInput;
    std::string passwordInput;
    bool loggedIn = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)//�����
                window.close();

            if (!loggedIn && event.type == sf::Event::TextEntered)//����û���δ��¼�������������ı��¼�
            {
                if (event.text.unicode == '\n') // ����Ƿ��»س�
                {//��������˻س�������ʾ�û������һ������
                    if (usernameInput.empty()) 
                    {
                        usernameInput = text.getString();//��������ı���ֵ
                        text.setString(""); // ����ı���
                    }
                    else {
                        passwordInput = text.getString();//ͬ��
                        text.setString(""); //����ı���
                        if (usernameInput.empty() || passwordInput.empty()) //����û����������Ƿ�Ϊ��
                        {
                            std::cout << "Username or password cannot be empty.\n";
                            continue; // Skip login/register logic if username or password is empty
                        }
                        if (!login(usernameInput, passwordInput, accounts)) //�ж��Ƿ�����˺�
                        {
                            std::cout << "Login failed. Registering new account.\n";
                            //������߼����жϿ���δ���������˺�����
                            //�Զ�Ϊ�û�ע�����˺�
                            registerAccount(usernameInput, passwordInput, accounts);//�⣡
                        }
                        else
                        {
                            std::cout << "Login successful.\n";
                        }
                        loggedIn = true;
                        return loggedIn;
                    }
                }
                else if (event.text.unicode == '\b' && !text.getString().isEmpty()) // ����<-�������
                {
                    sf::String str = text.getString();//��
                    str.erase(str.getSize() - 1);//��
                    text.setString(str);//��
                }
                else if (event.text.unicode < 128) // ֻ��������ͨ�ַ�
                {
                    text.setString(text.getString() + static_cast<char>(event.text.unicode));
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(text);
        Texture LoginDino;//��ʼ�����ֻС��������
        LoginDino.loadFromFile("art/dino.png");
        //���������ʾһ����СΪ 90 ���ؿ�110 ���ظߵľ��Σ����ڻ���վ������Ծ״̬�Ŀ�����
        RectangleShape LoginDinoShape(Vector2f(180.0f, 220.0f));
        LoginDinoShape.setTexture(&LoginDino);
        LoginDinoShape.setOrigin(45.0f, 55.0f);

        LoginDinoShape.setPosition(150, 300); //���þ�����״��λ��

        window.draw(LoginDinoShape);//����

        Text LoginText("Please Login!\ninput ID and Password with CTRL+ENTER", font, 30);
        LoginText.setOrigin(0, 0);
        LoginText.setPosition(10, 490);
        LoginText.setFillColor(Color::Black);
        window.draw(LoginText);

        
        window.display();
    }
}


#pragma once

class Player
{
  public:
    Player(std::string name, char stone_color);
    std::string get_name();
    std::string get_score();
    void        set_name(std::string name);
    void        set_score(int score);

  private:
    std::string name;
    int         score;
};

class Human : public Player
{
  public:
    Human();
};

class Computer : public Player
{
  public:
    Computer();
};
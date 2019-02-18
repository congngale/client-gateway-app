#ifndef ACTION_H
#define ACTION_H

class Action {
  public:
    Action(std::string json);
    ~Action();

    int action(void);
    std::string sender(void);
  
  private:
    int m_action;
    std::string m_sender;
};
#endif //ACTION_H
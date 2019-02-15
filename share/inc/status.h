#ifndef STATUS_H
#define STATUS_H

class Status {
  public:
    enum {
      NEW = 0,
      EXISTED = 1,
      INVALID = 2
    };
};
#endif //STATUS_H
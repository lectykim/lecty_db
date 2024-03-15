//
// Created by root on 24. 3. 14.
//

#ifndef UNTITLED_RESPONSER_H
#define UNTITLED_RESPONSER_H
#include "JobQueue.h"
#include "Parser.h"
class Responser : public JobQueue{

    explicit Responser(Connection conn):_conn(conn){

    }
public:
    void Response(uint8_t responseCode,uint8_t output,uint32_t len);

private:
    Connection _conn;
};


#endif //UNTITLED_RESPONSER_H

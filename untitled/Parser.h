//
// Created by root on 24. 3. 12.
//

#ifndef UNTITLED_PARSER_H
#define UNTITLED_PARSER_H
#include <stdlib.h>
#include <string>
#include <vector>
#include <cstring>
#include <map>
#include "Connection.h"
#include "PacketQueue.h"
enum {
    RES_OK = 0,
    RES_ERR = 1,
    RES_NX = 2,
    RES_CONN_REFUSED=3
};
class Parser {
public:
    int32_t parseReq(const char* data,size_t len, std::vector<std::string>&out)
    {
        if(len < 4)
            return -1;

        char* token = strtok(const_cast<char*>(data), " "); // strtok은 const char*을 인자로 받지 않으므로 const_cast 사용
        while (token != nullptr) {
            out.emplace_back(token);
            token = strtok(nullptr, " ");
        }
        return 0;
    };

    static bool cmdIs(const std::string& word,const char* cmd){
        return 0 == strcasecmp(word.c_str(),cmd);
    }

    uint32_t doGet(const std::vector<std::string> &cmd,std::string& buffer)
            {
        if(!db.count(cmd[1])){
            return RES_NX;
        }
        buffer = db[cmd[1]];
        return RES_OK;
    }

    uint32_t doSet(const std::vector<std::string>&cmd)
            {
        db[cmd[1]] = cmd[2];
        return RES_OK;

    }

    bool doDel(const std::vector<std::string>&cmd){
        db.erase(cmd[1]);
        return RES_OK;
    }

    int32_t doRequest(
            const char *req, uint32_t reqLen,uint32_t *resCode,Connection* conn
            ){
        std::vector<std::string> cmd;
        if(0 != parseReq(req,reqLen,cmd)){
            return -1;
        }
        std::string buffer;
        PacketItem packetItem;
        if(cmd.size()==2 && cmdIs(cmd[0],"get"))
        {
            *resCode = doGet(cmd,buffer);
            if(*resCode == RES_NX)
            {
                buffer = "null";
                packetItem.conn= conn;
                packetItem.buffer=buffer.c_str();
                packetItem.len = buffer.size();
            }
            else
            {

                packetItem.conn = conn;
                packetItem.buffer = buffer.c_str();
                packetItem.len = buffer.size();

            }
            packetItem.code=*resCode;
            GPacketQueue->Push(packetItem);

        }
        else if(cmd.size() == 3 && cmdIs(cmd[0],"set"))
        {
            *resCode = doSet(cmd);
            if(*resCode == RES_OK)
            {
                buffer = "OK";
                packetItem.conn= conn;
                packetItem.buffer=buffer.c_str();
                packetItem.len = buffer.size();
            }
            packetItem.code = *resCode;
            GPacketQueue->Push(packetItem);
        }
        else if(cmd.size() == 2 && cmdIs(cmd[0],"del")){
            *resCode = doDel(cmd);
            if(*resCode == RES_OK)
            {
                buffer = "OK";
                packetItem.conn= conn;
                packetItem.buffer=buffer.c_str();
                packetItem.len = buffer.size();
            }
            packetItem.code = *resCode;
            GPacketQueue->Push(packetItem);
        }
        else
        {
            *resCode = RES_ERR;
            buffer = "cmd is not recognized";
            packetItem.conn= conn;
            packetItem.buffer=buffer.c_str();
            packetItem.len = buffer.size();
            packetItem.code = *resCode;
            GPacketQueue->Push(packetItem);
        }

        return 0;
    }

private:
    std::map<std::string,std::string> db;
};
extern Parser* GParser;

#endif //UNTITLED_PARSER_H

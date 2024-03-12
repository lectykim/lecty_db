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
enum {
    RES_OK = 0,
    RES_ERR = 1,
    RES_NX = 2,
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

    bool cmdIs(const std::string& word,const char* cmd){
        return 0 == strcasecmp(word.c_str(),cmd);
    }

    uint32_t doGet(
            const std::vector<std::string> &cmd,uint8_t *res,uint32_t &resLen)
            {
        if(!db.count(cmd[1])){
            return RES_NX;
        }
        std::string &val = db[cmd[1]];
        assert(val.size() <= K_MAX_BUF);
        memcpy(res,val.data(),val.size());
        resLen = static_cast<uint32_t>(val.size());
        return RES_OK;
    }

    uint32_t doSet(
            const std::vector<std::string>&cmd, uint8_t *res,uint32_t &resLen)
            {
        db[cmd[1]] = cmd[2];
        return RES_OK;

    }

    int32_t doRequest(
            const char *req, uint32_t reqLen,uint32_t *resCode
            ,uint8_t *res, uint32_t *resLen
            ){
        std::vector<std::string> cmd;
        if(0 != parseReq(req,reqLen,cmd)){
            return -1;
        }

        if(cmd.size()==2 && cmdIs(cmd[0],"get"))
        {
            *resCode = doGet(cmd,res,resLen);
        }
        else if(cmd.size() == 3 && cmdIs(cmd[0],"set"))
        {
            *resCode = doSet(cmd,res,resLen);
        }
        else if(cmd.size() == 2 && cmdIs(cmd[0],del)){
            *resCode = do_del(cnd,res,resLen);
        }
        else
        {
            //cmd is not recognized
            *resCode = RES_ERR;
            const char* msg = "Unknown cmd";
            strcpy((char*)res,msg);
            *resLen = strlen(msg);
            return 0;
        }
        return 0;
    }

private:
    std::map<std::string,std::string> db;
};


#endif //UNTITLED_PARSER_H

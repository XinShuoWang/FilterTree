#include "FilterTree.h"
#include "timer.h"

#include <iostream>
#include <string>
#include <cassert>

// must install hiredis in sys path
#include "hiredis/hiredis.h"

int main(int argc, char **argv)
{
    /*{
        std::cout << "TEST 1" << std::endl;
        std::string str1 = "and(equals(toYear(LO_ORDERDATE), 1993), and(greaterOrEquals(LO_DISCOUNT, 1), "
                           "lessOrEquals(LO_DISCOUNT, 3.1), less(LO_QUANTITY, 25)))";
        std::string str2 = "and(equals(toYear(LO_ORDERDATE), 1993), and(greaterOrEquals(LO_DISCOUNT, 1), "
                           "lessOrEquals(LO_DISCOUNT, 3.1), less(LO_QUANTITY, 27)))";
        FilterTree tree1(str1);
        int times = 1000;
        while(times <= 10000 * 1000) {
            std::cout << "Data size is:" << times << std::endl;
            Timer timer;
            for(int i = 0; i < times; ++i) {
                FilterTree tree2(str2);
                tree1.Contain(tree2);
            }
            times *= 10;
        }
    }*/
    {
        std::cout << "TEST 2" << std::endl;
        std::string str1 = "and(equals(toYear(LO_ORDERDATE), 1993), and(greaterOrEquals(LO_DISCOUNT, 1), "
                           "lessOrEquals(LO_DISCOUNT, 3.1), less(LO_QUANTITY, 25)))";
        std::string str2 = "and(equals(toYear(LO_ORDERDATE), 1993), and(greaterOrEquals(LO_DISCOUNT, 1), "
                           "lessOrEquals(LO_DISCOUNT, 3.1), less(LO_QUANTITY, 27)))";
        FilterTree tree1(str1);
        int times = 1000;
        while(times <= 10000 * 1000) {
            std::cout << "Data size is:" << times << std::endl;
            redisContext* context = redisConnect("127.0.0.1", 6379);
            // set in redis
            std::cout << "Setting!" << std::endl;
            for(int i = 0; i < times; ++i) {
                void* reply = redisCommand(context, "SET %s_%d %d", str2.c_str(), i, i);
                freeReplyObject(reply);
            }
            std::cout << "Endding!" << std::endl;
            // begin timer
            redisReply* reply = nullptr;
            {
                Timer timer;
                reply = (redisReply*)redisCommand(context, "KEYS %s_*", str2.c_str());
                for(int i = 0; i < reply->elements; ++i) {
                    std::string k(reply->element[i]->str, str2.length());
                    FilterTree tree2(k);
                    tree1.Contain(tree2);
                }
            }
            freeReplyObject(reply);
            times *= 10;
        }
    }
    return 0;
}
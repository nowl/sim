#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

#include <string>

union Payload
{
    int i;
    Point p;
    char *s;
};

#endif /* __MESSAGE_HPP__ */

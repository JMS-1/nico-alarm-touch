#pragma once

#include <WString.h>
#include <functional>

class ApiServer
{
public:
    typedef std::function<void(const String &when, const String &message)> TOnChange;

public:
    void loop(bool isConnected, TOnChange onChange);
};
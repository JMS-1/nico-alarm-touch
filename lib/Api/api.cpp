#include <WebServer.h>
#include <html.h>

#include "api.h"

static WebServer server(80);

static bool isInitialized = false;

static String lastMessage;
static String lastTime;

void process(String cmd, ApiServer::TOnChange onChange)
{
    String when;

    if (!cmd.isEmpty())
    {
        if (server.hasArg("text"))
        {
            auto text = server.arg("text");

            if (!text.isEmpty())
                cmd = text;
        }

        if (server.hasArg("time"))
            when = server.arg("time");
    }

    lastMessage = cmd;
    lastTime = when;

    server.send(204);

    onChange(lastTime, lastMessage);
}

void ApiServer::loop(bool isConnected, TOnChange onChange)
{
    if (!isConnected)
        return;

    if (!isInitialized)
    {
        isInitialized = true;

        server.on(
            "/RR",
            [onChange]
            { process("RR", onChange); });

        server.on(
            "/RG",
            [onChange]
            { process("RG", onChange); });

        server.on(
            "/RY",
            [onChange]
            { process("RY", onChange); });

        server.on(
            "/GR",
            [onChange]
            { process("GR", onChange); });

        server.on(
            "/GG",
            [onChange]
            { process("GG", onChange); });

        server.on(
            "/GY",
            [onChange]
            { process("GY", onChange); });

        server.on(
            "/YR",
            [onChange]
            { process("YR", onChange); });

        server.on(
            "/YG",
            [onChange]
            { process("YG", onChange); });

        server.on(
            "/YY",
            [onChange]
            { process("YY", onChange); });

        server.on(
            "/OFF",
            [onChange]
            { process("", onChange); });

        server.on(
            "/TEXT",
            [onChange]
            { process("TEXT", onChange); });

        server.onNotFound(
            []
            { server.send(200, "text/html", getHomePage()); });

        server.begin();
    }

    server.handleClient();
}
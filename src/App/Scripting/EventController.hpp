#pragma once

namespace App
{
class CallbackSystem;

class EventController
{
public:
    virtual Core::Vector<Red::CName> GetEvents() = 0;
    virtual bool Initialize() = 0;
    virtual bool Uninitialize() = 0;
};
}

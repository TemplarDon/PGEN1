#ifndef AUDIO_HANDLER_H_
#define AUDIO_HANDLER_H_

#include "cocos2d.h"
#include "../Common/SingletonNode.h"

#include <map>
#include <bitset>
#include <vector>
#include <functional>

using std::map;
using std::bind;
using std::bitset;
using std::vector;
using std::function;

class AudioHandler : SingletonNode<AudioHandler>
{
public:

    AudioHandler();
    virtual ~AudioHandler();

    bool init();

private:




};

#endif
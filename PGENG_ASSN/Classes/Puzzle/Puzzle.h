#ifndef __PUZZLE_H__
#define __PUZZLE_H__

#include "cocos2d.h"
#include "PuzzleElement.h"

class Puzzle : public Node
{
public:
    Puzzle();
    ~Puzzle();

    bool init();
    bool CheckPuzzleComplete();
    //void SetPuzzleElementStatus(PuzzleElement* element, bool status);
    //void SetPuzzleElementStatus(int elementIdx, bool status);

    std::vector<PuzzleElement*> m_elementList; // list of puzzle elements, all must be complete for puzzle to be complete
};

#endif

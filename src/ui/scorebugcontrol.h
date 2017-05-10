#ifndef SCOREBUGCONTROL_H
#define SCOREBUGCONTROL_H

#include "control.h"

class ScoreBug : public Control
{
    std::string _score;
    std::string _downAndYards;
    std::string _topscore;
    std::string _scoreFontFamily;

public:
    ScoreBug(const std::string& id);
    virtual ~ScoreBug();

    virtual void render(NVGcontext* vg, float scale = 1.0f);

    void setScore(int score);
    void setDownAndYards(int down, int yards);
    void setTopscore(int score);

    void setScoreFontFamily(const std::string& font);
    const std::string& scoreFontFamily() const;

    static std::string timeInSecondsToString(int timeInSeconds);
};

#endif // SCOREBUGCONTROL_H

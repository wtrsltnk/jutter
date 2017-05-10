#include "scorebugcontrol.h"
#include "colors.h"
#include "fonts.h"

#include <sstream>
#include <iomanip>

ScoreBug::ScoreBug(const std::string& id)
    : Control(id), _scoreFontFamily("collegiate")
{
    this->setSize(glm::vec2(320, 50));
}

ScoreBug::~ScoreBug()
{ }

void ScoreBug::setScore(int score)
{
    std::stringstream ss;
    ss << score;
    this->_score = ss.str();
}

void ScoreBug::setDownAndYards(int down, int yards)
{
    std::stringstream ss;
    ss << down << (down == 1 ? "st" : (down == 2 ? "nd" : (down == 3 ? "rd" : "th"))) << " & " << (yards > 0 ? yards : 0);
    this->_downAndYards = ss.str();
}

void ScoreBug::setTopscore(int score)
{
    std::stringstream ss;
    ss << score;
    this->_topscore = ss.str();
}

std::string ScoreBug::timeInSecondsToString(int timeInSeconds)
{
    std::stringstream ss;
    ss << (timeInSeconds / 60) << ":" << std::setw(2) << std::setfill('0') << (timeInSeconds % 60);
    return ss.str();
}

void ScoreBug::render(NVGcontext* vg, float scale)
{
    nvgSave(vg);

    nvgTranslate(vg, this->position().x, this->position().y);
    nvgScale(vg, scale, scale);

    auto scoreScale = 7.0f;
    nvgBeginPath(vg);
    nvgRect(vg, -(this->size().x / 2.0f), (this->size().y * 0.6f), this->size().x, (this->size().y * 0.6f));
    nvgFillColor(vg, Colors::ToNvgColor(Colors::Secondary));
    nvgFill(vg);

    nvgBeginPath(vg);
    nvgRect(vg, -(this->size().x / 2.0f), (this->size().y * 0.6f), this->size().x, (this->size().y * 0.6f));
    nvgStrokeColor(vg, Colors::ToNvgColor(Colors::Secondary));
    nvgStrokeWidth(vg, 4.0f);
    nvgStroke(vg);


    // grijze vak
    nvgBeginPath(vg);
    nvgRect(vg, -(this->size().x / 2.0f), (this->size().y * 0.2f), this->size().x, (this->size().y * 0.6f));
    nvgStrokeColor(vg, Colors::ToNvgColor(Colors::Bright));
    nvgStrokeWidth(vg, 4.0f);
    nvgStroke(vg);

    nvgBeginPath(vg);
    nvgRect(vg, -(this->size().x / 2.0f), (this->size().y * 0.2f), this->size().x, (this->size().y * 0.6f));
    nvgFillColor(vg, nvgRGBA(114, 104, 95, 255));
    nvgFill(vg);



    // bottom
    nvgBeginPath(vg);
    nvgRect(vg, -(this->size().x / scoreScale), -(this->size().y * 0.05f), (this->size().x / (scoreScale/2.0f)), (this->size().y * 1.1f));
    nvgFillColor(vg, nvgRGBA(243, 226, 172, 255));
    nvgFill(vg);

    nvgBeginPath(vg);
    nvgRect(vg, -(this->size().x / scoreScale), -(this->size().y * 0.05f), (this->size().x / (scoreScale/2.0f)), (this->size().y * 1.1f));
    nvgFillColor(vg, Colors::ToNvgColor(Colors::Secondary));
    nvgFill(vg);


    // score box
    nvgBeginPath(vg);
    nvgRect(vg, -(this->size().x / (scoreScale * 1.1f)), (this->size().y * 0.05f), (this->size().x / (scoreScale / 1.8f)), this->size().y);
    nvgFillColor(vg, nvgRGBA(255, 255, 255, 100));
    nvgFill(vg);



    // texts
    nvgFontSize(vg, this->size().y);
    nvgFontFace(vg, this->scoreFontFamily().c_str());
    nvgFillColor(vg, Colors::ToNvgColor(Colors::Bright));
    nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
    nvgText(vg, 0.0f, (this->size().y / 2.0f), this->_score.c_str(), NULL);

    nvgFontSize(vg, this->size().y * 0.55f);
    nvgFontFace(vg, this->fontFamily().c_str());
    nvgFillColor(vg, Colors::ToNvgColor(Colors::Bright));
    nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
    nvgText(vg, -(this->size().x / 3.0f), (this->size().y / 2.0f), this->_downAndYards.c_str(), NULL);

    char icon[8];
    nvgFontSize(vg, 20);
    nvgFontFace(vg, "fontawesome");
    nvgFillColor(vg, Colors::ToNvgColor(Colors::Bright));
    nvgTextAlign(vg,NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
    nvgText(vg, (this->size().x / 4.0f), (this->size().y / 2.0f), cpToUTF8(int(eFontAwesomeIcons::FA_TROPHY), icon), NULL);

    nvgFontSize(vg, this->size().y * 0.55f);
    nvgFontFace(vg, this->fontFamily().c_str());
    nvgFillColor(vg, Colors::ToNvgColor(Colors::Bright));
    nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_MIDDLE);
    nvgText(vg, (this->size().x / 2.5f), (this->size().y / 2.0f), this->_topscore.c_str(), NULL);

    nvgRestore(vg);
}

void ScoreBug::setScoreFontFamily(const std::string& font)
{
    this->_scoreFontFamily = font;
}

const std::string& ScoreBug::scoreFontFamily() const
{
    return this->_scoreFontFamily;
}

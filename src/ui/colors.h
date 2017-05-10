#ifndef COLORS_H
#define COLORS_H

class Colors
{
public:
    static glm::vec4 Primary;
    static glm::vec4 Secondary;
    static glm::vec4 Bright;
    static glm::vec4 Dark;
    static glm::vec4 Highlight;

    static NVGcolor ToNvgColor(const glm::vec4& color);
};

#endif // COLORS_H

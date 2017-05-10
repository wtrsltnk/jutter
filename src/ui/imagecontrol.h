#ifndef IMAGECONTROL_H
#define IMAGECONTROL_H

#include "control.h"

class Image : public Control
{
    std::string _imageFilename;
    int _image;
public:
    Image(const std::string& id);
    virtual ~Image();

    virtual void render(NVGcontext* vg, float scale = 1.0f);

    void setImage(const std::string& image);
};

#endif // IMAGECONTROL_H

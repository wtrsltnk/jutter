#include "imagecontrol.h"

Image::Image(const std::string &id)
    : Control(id), _image(0)
{ }

Image::~Image()
{ }

void Image::render(NVGcontext* vg, float scale)
{
    if (this->_image == 0) this->_image = nvgCreateImage(vg, this->_imageFilename.c_str(), 0);

    nvgSave(vg);

    nvgTranslate(vg, this->_position.x, this->_position.y);
    nvgScale(vg, scale, scale);

    auto imgPaint = nvgImagePattern(vg, 0, 0, this->size().x, this->size().y, 0.0f / 180.0f * NVG_PI, this->_image, this->color().a / 255.0f);
    nvgBeginPath(vg);
    nvgRect(vg, 0, 0, this->size().x, this->size().y);
    nvgFillPaint(vg, imgPaint);
    nvgFill(vg);

    nvgRestore(vg);
}

void Image::setImage(const std::string& image)
{
    this->_imageFilename = image;
    this->_image = 0;
}

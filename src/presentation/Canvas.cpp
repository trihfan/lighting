#include <cctype>
#include <algorithm>
#include "Canvas.h"
#include "CanvasPPMExporter.h"

using namespace lighting;

std::unordered_map<std::string, std::shared_ptr<CanvasExporter>> Canvas::exporters
{
    std::make_pair("ppm", std::make_shared<CanvasPPMExporter>())
};

Canvas::Canvas(size_t width, size_t height) : w(width), h(height)
{
    content.resize(w * h);
}

size_t Canvas::width() const
{
    return w;
}

size_t Canvas::height() const
{
    return h;
}

Color& Canvas::operator()(size_t index)
{
    return content[index];
}

const Color& Canvas::operator()(size_t index) const
{
    return content[index];
}

Color& Canvas::operator()(size_t x, size_t y)
{
    return content[y * w + x];
}

const Color& Canvas::operator()(size_t x, size_t y) const
{
    return content[y * w + x];
}

bool Canvas::exportTo(std::ostream& output, std::string type) const
{
    std::transform(type.begin(), type.end(), type.begin(), [](unsigned char c){ return std::tolower(c); });
    auto it = exporters.find(type);
    if (it != exporters.end())
    {
        (*it->second)(*this, output);
        return true;
    }
    return false;
}

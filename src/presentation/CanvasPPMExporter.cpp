#include <algorithm>
#include <string>
#include "CanvasPPMExporter.h"
#include "Canvas.h"
#include "maths/Color.h"

using namespace lighting;

void CanvasPPMExporter::operator()(const Canvas& canvas, std::ostream& output) const
{
    output << "P3" << std::endl;
    output << canvas.width() << " " << canvas.height()  << std::endl;
    output << "255" << std::endl;
    
    for (size_t y = 0; y < canvas.height(); y++)
    {
        size_t current = 0;
        for (size_t x = 0; x < canvas.width(); x++)
        {
            Color color = canvas(x, y);
            for (size_t i = 0; i < 3; i++)
            {
                std::string value = std::to_string(std::clamp(static_cast<int>(std::round(color(i) * 255)), 0, 255));
                if (current + value.size() >= 70)
                {
                    output << std::endl;
                    current = 0;
                }
                current += value.size() + 1;
                output << value << ' ';
            }
        }
        output << std::endl;
    }
}
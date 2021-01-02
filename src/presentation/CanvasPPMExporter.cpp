#include "CanvasPPMExporter.h"
#include "Canvas.h"

using namespace lighting;

void CanvasPPMExporter::operator()(const Canvas& canvas, std::ostream& output) const
{
    output << "P3" << std::endl;
    output << canvas.width() << " " << canvas.height()  << std::endl;
    output << "255" << std::endl;
    
    for (size_t x = 0; x < 10; x++)
    {
        int current = 0;
        for (size_t y = 0; y < 20; y++)
        {
            Color color = canvas(x, y);

            // red
            std::string value = std::to_string(std::clamp(static_cast<int>(color.r * 255), 0, 255));
            if (current + value.size() >= 70)
            {
                output << std::endl;
                current = 0;
            }
            current += value.size() + 1;
            output << value << ' ';

            // green
            value = std::to_string(std::clamp(static_cast<int>(color.g * 255), 0, 255));
            if (current + value.size() >= 70)
            {
                output << std::endl;
                current = 0;
            }
            current += value.size() + 1;
            output << value << ' ';

            // blue
            value = std::to_string(std::clamp(static_cast<int>(color.b * 255), 0, 255));
            if (current + value.size() >= 70)
            {
                output << std::endl;
                current = 0;
            }
            current += value.size() + 1;
            output << value << ' ';
        }
        output << std::endl;
    }
}
#include "CanvasPPMExporter.h"
#include "Canvas.h"

using namespace lighting;

void CanvasPPMExporter::operator()(const Canvas& canvas, std::ostream& output) const
{
    output << "P3" << std::endl;
    output << canvas.width() << " " << canvas.height()  << std::endl;
    output << "255" << std::endl;
}
#ifndef CANVASEXPORTER_H
#define CANVASEXPORTER_H

#include <ostream>

namespace lighting
{
    class Canvas;

    class CanvasExporter
    {
    public:
        // export
        virtual void operator()(const Canvas& canvas, std::ostream& output) const = 0;
    };
}
#endif

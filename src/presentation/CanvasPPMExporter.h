#ifndef CANVASPPMEXPORTER_H
#define CANVASPPMEXPORTER_H

#include "CanvasExporter.h"

namespace lighting
{
    class CanvasPPMExporter : public CanvasExporter
    {
    public:
        // export
        void operator()(const Canvas& canvas, std::ostream& output) const override;
    };
}
#endif

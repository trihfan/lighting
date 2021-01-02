#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <ostream>
#include <unordered_map>
#include <memory>
#include "maths/Tuple.h"
#include "CanvasExporter.h"

namespace lighting
{
    class Canvas
    {
    public:
        // construction
        Canvas(size_t width = 0, size_t height = 0);
        ~Canvas() = default;

        // size
        size_t width() const;
        size_t height() const;

        // access
        Tuple& operator()(size_t index);
        const Tuple& operator()(size_t index) const;
        Tuple& operator()(size_t x, size_t y);
        const Tuple& operator()(size_t x, size_t y) const;

        // export
        bool exportTo(std::ostream& output, std::string type) const;

    private:
        size_t w;
        size_t h;
        std::vector<Tuple> content;
        static std::unordered_map<std::string, std::shared_ptr<CanvasExporter>> exporters;
    };
}
#endif

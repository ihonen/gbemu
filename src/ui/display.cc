#include "display.hh"

#include <QGraphicsRectItem>

/*
static const uint32_t colors[4] =
{
    0xFFE0F8D0, // very light green
    0xFF88C070, // light green
    0xFF346856, // green
    0xFF081820, // dark green
};

static const uint32_t colors[4] =
{
    0xFFABC418, // very light green
    0xFF9DB618, // light green
    0xFF3B7440, // green
    0xFF0C4714, // dark green
};
*/

static const uint32_t colors[4] =
{
    0xFFCDDE75, // light green
    0xFF98AA4B, // very light green
    0xFF406A3E, // green
    0xFF142B13, // dark green
};

#include <chrono>

void Display::on_frame_ready()
{
    auto frame_buffer = renderer.get_frame_buffer();

    for (size_t y = 0; y < 144; ++y)
    {
        for (size_t x = 0; x < 160; ++x)
        {
            set_pixel(x, y, colors[frame_buffer[y * 160 + x]]);
       }
    }

    item->setPixmap(QPixmap::fromImage(image));
}

Display::Display(PPU& ppu_, Renderer& renderer_, QObject* parent) :
    QGraphicsScene(parent),
    renderer(renderer_),
    ppu(ppu_)
{
    image = QImage(160 * 4, 144 * 4, QImage::Format_ARGB32);
    image.fill(QColor(colors[3]));
    item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    addItem(item);
}

void Display::set_pixel(int x, int y, uint32_t color)
{
    for (auto x_offset = 0; x_offset < 4; ++x_offset)
    {
        for (auto y_offset = 0; y_offset < 4; ++y_offset)
        {
            image.setPixelColor(x * 4 + x_offset,
                                y * 4 + y_offset,
                                QColor(color));
        }
    }
}

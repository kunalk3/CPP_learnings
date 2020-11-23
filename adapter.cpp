/**
 * ---------------------------------------------------------------------------------------
 * Author  : Kunal K.
 * Title   : Adapter design pattern
 * Purpose : To demonstrate the concepts of design patterns
 * Version : 1.0
 * ---------------------------------------------------------------------------------------
**/

#include <iostream>
#include <memory>

// old button with old interface
class OldButton {
    int _x1, _y1, _x2, _y2;

  public:
    OldButton(int x1, int y1, int x2, int y2)
        : _x1{x1}, _y1{y1}, _x2{x2}, _y2{y2} {}
    void draw_old() const {
        std::cout << "Old button. Coordinates: (" << _x1 << ", " << _y1
                  << "), (" << _x2 << ", " << _y2 << ")\n";
    }
};

// our shinny new button interface
struct IButton {
    virtual void draw() const = 0;
    virtual ~IButton() = default;
};

// new button with new interface
class Button : public IButton {
    int _x1, _y1, _x2, _y2;

  public:
    Button(int x, int y, int length, int height)
        : _x1{x}, _y1{y}, _x2{x + length}, _y2{y + height} {}
    void draw() const override {
        std::cout << "New button. Coordinates: (" << _x1 << ", " << _y1
                  << "), (" << _x2 << ", " << _y2 << ")\n";
    }
};

// adapter for legacy buttons
class AdapterOldButton : public IButton, private OldButton {
  public:
    AdapterOldButton(int x, int y, int length, int height)
        : OldButton(x, y, x + length, y + height) {}
    void draw() const override { draw_old(); }
};

int main() {
    // new button
    Button new_button(100, 100, 40, 10);
    new_button.draw();

    // create old button via the interface of the new button
    std::unique_ptr<IButton> adapter_old_button =
        std::make_unique<AdapterOldButton>(100, 100, 40, 10);
    adapter_old_button->draw();
}

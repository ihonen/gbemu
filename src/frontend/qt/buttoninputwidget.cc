#include "buttoninputwidget.hh"

#include "keybindings.hh"

void ButtonInputWidget::button_hover_enter()
{

}

void ButtonInputWidget::button_hover_exit()
{

}

void ButtonInputWidget::button_clicked()
{

}

ButtonInputWidget::ButtonInputWidget(DebugCore* debugger, QWidget* parent) :
    QFrame(parent),
    debugger(debugger)
{
    setStyleSheet("background-color: #232629");

    up_button = new Button(Joypad::Button::Up, this);
    down_button = new Button(Joypad::Button::Down, this);
    left_button = new Button(Joypad::Button::Left, this);
    right_button = new Button(Joypad::Button::Right, this);
    center_button = new Button(Joypad::Button::None, this);
    select_button = new Button(Joypad::Button::Select, this);
    start_button = new Button(Joypad::Button::Start, this);
    a_button = new Button(Joypad::Button::A, this);
    b_button = new Button(Joypad::Button::B, this);

    buttons =
    {
        {Joypad::Button::Up, up_button},
        {Joypad::Button::Down, down_button},
        {Joypad::Button::Left, left_button},
        {Joypad::Button::Right, right_button},
        {Joypad::Button::Start, start_button},
        {Joypad::Button::Select, select_button},
        {Joypad::Button::A, a_button},
        {Joypad::Button::B, b_button}
    };

    layout = new QGridLayout(this);
    // Placeholder widgets that can be stretched.
    auto placeholderwidget1 = new QWidget(this);
    auto placeholderwidget2 = new QWidget(this);
    auto placeholderwidget3 = new QWidget(this);
    auto placeholderwidget4 = new QWidget(this);
    layout->addWidget(placeholderwidget1, 0, 0, 1, 5);
    layout->addWidget(placeholderwidget2, 4, 0, 1, 5);
    layout->addWidget(placeholderwidget3, 1, 0, 3, 1);
    layout->addWidget(placeholderwidget4, 1, 6, 3, 1);

    layout->addWidget(up_button, 1, 2);
    layout->addWidget(down_button, 3, 2);
    layout->addWidget(left_button, 2, 1);
    layout->addWidget(right_button, 2, 3);
    layout->addWidget(center_button, 2, 2);
    layout->addWidget(select_button, 3, 4);
    layout->addWidget(start_button, 3, 5);
    layout->addWidget(a_button, 2, 4);
    layout->addWidget(b_button, 2, 5);
    layout->setSpacing(0);
    layout->setMargin(0);
}

void ButtonInputWidget::keyPressEvent(QKeyEvent* event)
{
    auto button = buttons[JOYPAD_KEYMAP.at(event->key())];
    // TODO: Find a better solution.
    button->keyPressEvent(event);
    QWidget::keyPressEvent(event);

    debugger->button_pressed(Joypad::Button::Start);
}

void ButtonInputWidget::keyReleaseEvent(QKeyEvent* event)
{
    auto button = buttons[JOYPAD_KEYMAP.at(event->key())];
    // TODO: Find a better solution.
    button->keyReleaseEvent(event);
    debugger->button_pressed(button->id);
    QWidget::keyReleaseEvent(event);
}

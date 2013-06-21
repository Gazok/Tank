#ifndef TANK_WINDOW_HPP
#define TANK_WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "IWindow.hpp"
#include "../Utility/Vector.hpp"

namespace sf
{
    class Event;
}

namespace tank {

class Window : public IWindow
{
public:
    Window(Vector<unsigned int> const& size, std::string caption = "");
    virtual ~Window();

    virtual Vector<unsigned int> const& getSize() override;
    virtual std::string getCaption() override;

    virtual void render() override;
    virtual void flipDisplay() override;

    virtual void resize(Vector<unsigned int> const& size) override;
    virtual void setCaption(std::string caption) override;

    /*!
     * \brief SFML-specific polling code (temporary)
     */
    bool pollEvent(sf::Event&);

    /*!
     * \brief Not implemented
     */
    virtual void setIcon(std::string path); 
private:
    sf::RenderWindow window;
    std::string caption_;
    Vector<unsigned int> size_;

    //Is this window instance the current window?
    bool valid_;

    //Unfortunately we can only have one window right now
    static bool windowExists_;
};

}

#endif /* WINDOW_H */

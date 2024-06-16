#pragma once

#include "component/InputComponent.hpp"

namespace ramboindustries
{
    namespace object
    {
        class Pause 
        :
            public component::InputComponent
        {
            public:
                Pause();
                bool is_paused() const;
                void input() override;
            private:
                bool paused;
        };

    };

};
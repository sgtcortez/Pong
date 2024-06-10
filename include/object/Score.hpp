#pragma once

#include "component/RenderComponent.hpp"

namespace ramboindustries 
{

    namespace object
    {

        class Score 
        :
            public component::RenderComponent
        {
            public:
                Score(
                    const int x,
                    const int y
                );
                void render() const override;

                Score& operator+(const int value);
                Score& operator+=(const int value);

            private:
                const int x;
                const int y;
                unsigned int value;
        };     

    };

};
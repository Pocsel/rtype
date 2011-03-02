#ifndef __INTERACTIONMANAGER_HPP__
#define __INTERACTIONMANAGER_HPP__

#include "AInteraction.hpp"
#include "QuadTree.hpp"
#include "SmartPtr.hpp"

namespace Gmgp
{
    namespace Server
    {

        template <typename T> class InteractionManager :
            private b00st::NonCopyable
        {
        private:
            QuadTree<T>* _curReadGrid;
            QuadTree<T>* _curWriteGrid;
            QuadTree<T>* _nextReadGrid;
            QuadTree<T>* _nextWriteGrid;

        public:
            explicit InteractionManager(size_t width, size_t height, size_t levels = 5)
            {
                Rect screen(0, 0, width, height);
                this->_curReadGrid = new QuadTree<T>(screen, levels);
                this->_nextReadGrid = new QuadTree<T>(screen, levels);
                this->_curWriteGrid = this->_nextReadGrid;
                this->_nextWriteGrid = this->_curReadGrid;
            }

            ~InteractionManager()
            {
                delete this->_curReadGrid;
                delete this->_nextReadGrid;
            }

            void AddInteraction(b00st::SmartPtr<AInteraction<T> > const& interaction, Shape const& shape)
            {
                this->_curWriteGrid->AddInteraction(interaction, shape);
            }

            void ClearInteractions(void)
            {
                this->_curWriteGrid->ClearInteractions();
            }

            void SwapReadBuffers(void)
            {
                QuadTree<T>* tmp;
                tmp = this->_curReadGrid;
                this->_curReadGrid = this->_nextReadGrid;
                this->_nextReadGrid = tmp;
            }

            void SwapWriteBuffers(void)
            {
                QuadTree<T>* tmp;
                tmp = this->_curWriteGrid;
                this->_curWriteGrid = this->_nextWriteGrid;
                this->_nextWriteGrid = tmp;
            }

            void Interact(T& entity, Shape const& area)
            {
                this->_curReadGrid->Interact(entity, area);
            }
        };

    }
}

#endif


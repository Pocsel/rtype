#ifndef __QUADTREE_HPP__
#define __QUADTREE_HPP__

#include <list>
#include <set>

#include "AInteraction.hpp"
#include "SmartPtr.hpp"
#include "Shape.hpp"

namespace Gmgp
{
    namespace Server
    {

        template<typename Entity> class QuadTree
        {
        private:
            struct Interaction
            {
                explicit Interaction(b00st::SmartPtr<AInteraction<Entity> > const& interaction_, Shape const& shape_, bool del = true)
                    : interaction(interaction_), shape(*shape_.Clone()), _del(del)
                {
                }
                explicit Interaction(Interaction const& i)
                    : interaction(i.interaction), shape(i.shape), _del(true)
                {
                }
                ~Interaction(void)
                {
                    if (this->_del)
                        delete &shape;
                }
                b00st::SmartPtr<AInteraction<Entity> > interaction;
                Shape& shape;
            private:
                bool _del;
            };
            QuadTree* _childs[4];
            std::list<Interaction> _interactions;
            int _interactionCount;
            Rect _area;

        public:
            QuadTree(Rect const& area, size_t levels) : _interactionCount(0)
            {
                this->_area = area;
                this->_childs[0] = 0;
                this->_childs[1] = 0;
                this->_childs[2] = 0;
                this->_childs[3] = 0;
                if (levels - 1 > 0)
                {
                    this->_childs[0] = new QuadTree(Rect(area.position.x, area.position.y, area.width / 2, area.height / 2), levels - 1);
                    this->_childs[1] = new QuadTree(Rect(area.position.x + area.width / 2, area.position.y, area.width / 2, area.height / 2), levels - 1);
                    this->_childs[2] = new QuadTree(Rect(area.position.x, area.position.y + area.height / 2, area.width / 2, area.height / 2), levels - 1);
                    this->_childs[3] = new QuadTree(Rect(area.position.x + area.width / 2, area.position.y + area.height / 2, area.width / 2, area.height / 2), levels - 1);
                }
            }

            ~QuadTree()
            {
                for (int i = 0; i < 4; ++i)
                    delete this->_childs[i];
            }

            void AddInteraction(b00st::SmartPtr<AInteraction<Entity> > const& interaction, Shape const& shape)
            {
                if (!this->_area.Intersect(shape))
                    return;
                ++this->_interactionCount;
                if (this->_childs[0] == 0 || shape.Contain(this->_area))
                    this->_interactions.push_back(Interaction(interaction, shape, false));
                else
                {
                    for (int i = 0; i < 4; ++i)
                        this->_childs[i]->AddInteraction(interaction, shape);
                }
            }

            void ClearInteractions(void)
            {
                if (this->_interactionCount == 0)
                    return;
                this->_interactionCount = 0;
                this->_interactions.clear();
                if (this->_childs[0] != 0)
                    for (int i = 0; i < 4; ++i)
                        this->_childs[i]->ClearInteractions();
            }

            void Interact(Entity& entity, Shape const& area)
            {
                if (this->_interactionCount == 0 || !this->_area.Intersect(area))
                    return;
                std::set< AInteraction<Entity>* > interactions;
                this->_Interact(entity, area, interactions);

                typename std::set< AInteraction<Entity>* >::iterator it = interactions.begin();
                for (; it != interactions.end() && (*it)->Interact(entity); ++it);
            }

        private:
            void _Interact(Entity& entity, Shape const& area, std::set<AInteraction<Entity>*>& interactions)
            {
                if (this->_interactionCount == 0 || !this->_area.Intersect(area))
                    return;
                if (area.Contain(this->_area))
                    this->_MustInteract(entity, interactions);
                else
                {
                    typename std::list<Interaction>::iterator it = this->_interactions.begin();
                    typename std::list<Interaction>::iterator ite = this->_interactions.end();
                    for (; it != ite; ++it)
                        if ((*it).shape.Intersect(area) && (*it).interaction->GetCreator() != &entity)
                            interactions.insert(interactions.end(), ((*it).interaction.Get()));
                    if (this->_childs[0] != 0)
                        for (int i = 0; i < 4; ++i)
                            this->_childs[i]->_Interact(entity, area, interactions);
                }
            }

            void _MustInteract(Entity& entity, std::set<AInteraction<Entity>*>& interactions)
            {
                if (this->_interactionCount == 0)
                    return;
                typename std::list<Interaction>::iterator it = this->_interactions.begin();
                typename std::list<Interaction>::iterator ite = this->_interactions.end();
                for (; it != ite; ++it)
                    if ((*it).interaction->GetCreator() != &entity)
                        interactions.insert((*it).interaction.Get());
                if (this->_childs[0] != 0)
                    for (int i = 0; i < 4; ++i)
                        this->_childs[i]->_MustInteract(entity, interactions);
            }
        };

    }
}

#endif

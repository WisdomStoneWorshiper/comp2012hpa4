#include "hashtable.h"

Hashtable::Hashtable()
{
}

void Hashtable::insertVertex(Vertex *target)
{
    table[target->getId() * HASHKEY % 50].push_back(target);
}

void Hashtable::removeVertex(Vertex *target)
{
    table[target->getId() * HASHKEY % 50].remove(target);
}

Vertex *Hashtable::getVertex(const int &id)
{
    if (table[id * HASHKEY % 50].front()->getId() == id)
        return table[id * HASHKEY % 50].front();
    else
    {
        return *find_if(table[id * HASHKEY % 50].begin(), table[id * HASHKEY % 50].end(),
                        [&](Vertex *v) { return v->getId() == id; });
    }
}

bool Hashtable::containVertex(Vertex *target)
{
    return !(find(table[target->getId() * HASHKEY % 50].begin(), table[target->getId() * HASHKEY % 50].end(), target) == table[target->getId() * HASHKEY % 50].end());
}

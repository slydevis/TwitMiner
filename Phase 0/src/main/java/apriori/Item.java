package apriori;

/**
 * Created by guillaume on 19/03/14.
 */
public class Item {
    public:

    Item(int i) :
    id(i), support(0), children(0)
    {
    }
    Item(const Item &i) :
    id(i.id), support(i.support), children(i.children)
    {
    }

    int getId()
    {
        return id;
    }

    int Increment(int inc)
    {
        if(inc > 1) inc = 1;
        return support += inc;
    }

    std::set<Item> *makeChildren() const;
    int deleteChildren() const;

    int getSupport() const
    {
        return support;
    }
    std::set<Item> *getChildren() const
    {
        return children;
    }

    bool operator<(const Item &i) const
    {
        return id < i.id;
    }

    private:

            const int id;

    mutable int support;
    mutable std::set<Item> *children;
};
}

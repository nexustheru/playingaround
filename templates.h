#ifndef TEMPLATES_H
#define TEMPLATES_H
#include <QFile>
#include <QTreeWidgetItem>
#include <includesnif.h>

template<class T>
T getchildren(vector<T> myvec)
{
    for(unsigned int i=0 ;i < myvec.size();i++)
    {
        return myvec[i];
    }
}
template<class U>
U gettypename(Niflib::NiObjectRef ob)
{
    return ob->GetType().GetTypeName();
}
template<class V>
V convert(QTreeWidgetItem* item)
{
    Niflib::NiObjectRef temp=reinterpret_cast<Niflib::NiObject*>(&item);
    Niflib::NiObjectRef nob=temp;
    return nob;
}

template<class T>
T createclassonfly(string classna)
{
    return new T;
}


#endif // TEMPLATES_H

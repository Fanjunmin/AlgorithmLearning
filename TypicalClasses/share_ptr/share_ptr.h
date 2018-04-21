#ifndef SHARE_PTR_H_INCLUDED
#define SHARE_PTR_H_INCLUDED

template<typename T>
class share_ptr
{
private:
    T& operator* () const { return *px; }
    T* operator-> () const { return px; w`}
    share_ptr(T* p) : px(p) {}
private:
    T* px;
    long* pn;
};

#endif // SHARE_PTR_H_INCLUDED

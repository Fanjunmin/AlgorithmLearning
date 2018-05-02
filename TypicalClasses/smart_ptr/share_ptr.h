#ifndef SHARE_PTR_H_INCLUDED
#define SHARE_PTR_H_INCLUDED

template<typename T>
class shared_ptr
{
private:
    shared_ptr(T* p) : px(p), pn(new int(1)) { }
    template<typename U>
    shared_ptr(shared_ptr<U>& rhs) : px(rhs.px), pn(++*rhs.pn) { }
    template<typename U>
    shared_ptr<T>& operator=(shared_ptr<U>& rhs) {
        ++*rhs.pn;
        if(this->px && 0 == --*this->pn) {
            delete px;
            delete pn;
        }
        this->px = rhs.px;
        this->pn = rhs.pn;
        return *this;
    }
    ~shared_ptr() {
        if(--*pn == 0) {
            delete px;
            delete pn;
        }
    }
    T& operator* () const { return *px; }
    T* operator-> () const { return px; }
    share_ptr(T* p) : px(p) {}
    int getRef() { return *pn; }
private:
    T* px;
    long* pn;
};

#endif // SHARE_PTR_H_INCLUDED

#ifndef AUTO_PTR_H_INCLUDED
#define AUTO_PTR_H_INCLUDED

template <class T>
class auto_ptr
{
public:
    explicit auto_ptr(T* p = 0) : pointee(p) { }
    template<class U>
    auto_ptr(auto_ptr<U>& rhs) : pointee(rhs.release()) { }
    ~auto_ptr() { delete pointee; }
    template<class U>
    auto_ptr<T>& operator=(auto_ptr<U>& rhs) {
        if(this != &rhs)    //֤ͬ����
            reset(rhs.release());
        return *this;
    }
    T& operator*() const { return *pointee; }
    T* operator->() const { return pointee; }
    T* get() const { return pointee; }
    T* release() {
        T* oldpointee = pointee;
        pointee = 0;
        return oldpointee;
    }
    void reset(T* p = 0) {
        if(pointee != p) {
            delete pointee;
            pointee = p;
        }
    }
//template <class U>      //��auto_ptr������classes����Ϊ��һ��auto_ptr ��friends
//friend class auto_ptr<U>;

private:
    T* pointee;
};

#endif // AUTO_PTR_H_INCLUDED

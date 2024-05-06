#include <iostream>

#include <cstring>
#include "EmptyApplication.h"
#include "StackMemoryManager.h"
#include "SingleFrameMemoryManager.h"
#include "ObjectMemoryManager.h"

#undef _DEBUG

using slimenano::IApplication;
using slimenano::memory::ObjectMemoryManager;
using slimenano::memory::SingleFrameMemoryManager;
using slimenano::memory::StackMemoryManager;

template <typename T>
class Vector
{
public:
    Vector(T x, T y)
        : m_X(x), m_Y(y)
    {
    }

    Vector operator+(Vector const& obj)
    {
        return Vector(this->m_X + obj.m_X, this->m_Y + obj.m_Y);
    }

public:
    T m_X;
    T m_Y;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, Vector<T>& vector) {
    return out << "vec(" << vector.m_X << "," << vector.m_Y << ")";
}

EmptyApplication g_App;
StackMemoryManager g_pMemoryAllocator(ObjectMemoryManager<Vector<float>>::FrameSize(5), 1);
ObjectMemoryManager<Vector<float>> s1(g_pMemoryAllocator, 5);

namespace slimenano
{
    IApplication *g_pApp = &g_App;
}

int EmptyApplication::Initialize()
{
    return 0;
}

void EmptyApplication::Tick()
{
    Vector<float> *p1 = s1.New(1.f, 1.f);
    Vector<float> *p2 = s1.New(3.f, 3.f);
    Vector<float> *p3 = s1.New(2.5f, 4.f);
    Vector<float> *p4 = s1.New(2.5f, 1.f);
    Vector<float> *p5 = s1.New(2.5f, 2.f);
    Vector<float> *p6 = s1.New(2.5f, 3.f);
    std::cout << *p1 << std::endl;
    std::cout << *p2 << std::endl;
    std::cout << *p3 << std::endl;
    std::cout << *p4 << std::endl;
    std::cout << *p5 << std::endl;
    s1.Delete(p1);
    s1.Delete(p2);
    p1 = s1.New(0.f, 1.f);
    std::cout << *p1 << std::endl;
    this->m_bQuit = true;
}

void EmptyApplication::Finalize()
{
}
#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>
// shared_ptr → 增加 strong count
// weak_ptr → 不增加 strong count
// weak_ptr::use_count() 返回的是它观察对象的 strong count

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;//weak ptr
    ASSERT(observer.use_count() == 4, "");

    ptrs[0].reset();
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "");

    ptrs[2] = std::make_shared<int>(*shared);//这里创建了一个新对象，两个的 use_count 独立
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);// move 不改变引用计数，它只是转移 shared_ptr 内部保存的指针和控制块指针。
    ASSERT(observer.use_count() == 3, "");

    std::ignore = std::move(ptrs[0]);// 真正移动需要'目标对象'
    ptrs[1] = std::move(ptrs[1]);    // 不变
    ptrs[1] = std::move(ptrs[2]);    // -1
    ASSERT(observer.use_count() == 2, "");

    shared = observer.lock();// weak_ptr::lock() 会创建一个新的 shared_ptr（增加强引用）
                             // 释放 shared_ptr 不会影响 weak_ptr，只会减少 strong count
    ASSERT(observer.use_count() == 3, "");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");

    shared = observer.lock();//如果对象已经被销毁，它返回一个空的 shared_ptr
    ASSERT(observer.use_count() == 0, "");

    return 0;
}

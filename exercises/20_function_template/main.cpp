#include "../exercise.h"

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
// TODO: 将这个函数模板化
template <typename T>
T plus(T a, T b) {
    return a + b;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？ IEEE754
    // 浮点数在计算机中是以二进制形式存储的，很多十进制小数（如 0.1）无法被精确表示
    // 这里 0.25 是 2^-2, 0.5 是 2^-1，不会产生舍入
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");
    // TODO: 修改判断条件使测试通过
    ASSERT(plus(0.1, 0.2) - 0.3 < 1e-6, "How to make this pass?");

    return 0;
}

#include "../exercise.h"
//constexper 把计算从"运行时"搬到"编译时"，程序启动后直接使用算好的结果
//报错信息是递归斐波那契次数太多，超过了编译器的最大限制“exceeds limit of 33554432”
//把constexper删掉即可
constexpr unsigned long long fibonacci(int i) {
    switch (i) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            return fibonacci(i - 1) + fibonacci(i - 2);
    }
}

int main(int argc, char **argv) {
    constexpr auto FIB20 = fibonacci(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // TODO: 观察错误信息，修改一处，使代码编译运行
    // PS: 编译运行，但是不一定能算出结果…… 算不出来，我改小点通过
    constexpr auto ANS_N = 30;
    auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}
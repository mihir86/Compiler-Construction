#include <parser.hpp>

int32_t main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    assert(argc == 2);
    Parser parser(argv[1]);
    parser.LR1();
}

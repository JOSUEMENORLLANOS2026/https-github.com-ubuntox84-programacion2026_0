#include <iostream>
#include <stdexcept>
using namespace std;

class MiError : public runtime_error
{
public:
    MiError(string msg) : runtime_error(msg) {}
};

int main()
{
    try
    {
        throw MiError("Error personalizado");
    }
    catch (const exception &e)
    {
        cout << e.what();
    }
}
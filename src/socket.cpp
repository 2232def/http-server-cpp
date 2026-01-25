#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

int main()
{
    int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    int sock2 = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    cout << "Socket created: " << sock  << endl;
    return 0;
}

#include <Common.h>
#include <DBusProxy.h>

using namespace std;

int main()
{
    int count = 0;
    bool b_deinit = false;
    printf("GDbus Client app start!!!\n");

    DBusProxy dBusProxy;
    dBusProxy.init();
    while (true)
    {
        std::cout << "Waiting for calls... (Abort with CTRL+C)$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        printf("########## send client -> server\n");
        dBusProxy.sendMessage("client_ID", "Client_MSG");
        printf("count: [%d] b_deinit: [%d]\n", count, b_deinit);
        // if (count == 5 && b_deinit == false)
        // {
        //     dBusProxy.deinit();
        //     b_deinit = true;
        // }
        // else if (count == 8 && b_deinit == true)
        // {
        //     dBusProxy.init();
        //     b_deinit = false;
        // }
        // else if (count == 11 && b_deinit == false)
        // {
        //     dBusProxy.deinit();
        //     b_deinit = true;
        // }
        // else if (count == 14 && b_deinit == true)
        // {
        //     dBusProxy.init();
        //     b_deinit = false;
        // }
        // else if (count == 17 && b_deinit == false)
        // {
        //     dBusProxy.deinit();
        //     b_deinit = true;
        // }
        // else if (count == 20 && b_deinit == true)
        // {
        //     dBusProxy.init();
        //     b_deinit = false;
        // }
        // else if (count == 23 && b_deinit == false)
        // {
        //     dBusProxy.deinit();
        //     b_deinit = true;
        // }
        // else if (count == 27 && b_deinit == true)
        // {
        //     dBusProxy.init();
        //     b_deinit = false;
        // }
        count++;
    }
    return 0;
}

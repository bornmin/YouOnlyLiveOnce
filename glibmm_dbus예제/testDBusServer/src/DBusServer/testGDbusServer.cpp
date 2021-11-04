#include <Common.h>
#include <DBusStub.h>

int main()
{
    int count = 0;
    bool b_deinit = false;
    std::cout << "Checking availability!" << std::endl;

    DBusStub dbusStub;

    dbusStub.init();

    while (true)
    {
        std::cout << "\nWaiting for calls... (Abort with CTRL+C)$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        printf("########## send server -> client\n");
        dbusStub.sendMessage("Server_id", "Server_msg");
        printf("count: [%d] b_deinit: [%d]\n", count, b_deinit);
        // if (count == 5 && b_deinit == false)
        // {
        //     dbusStub.deinit();
        //     b_deinit = true;
        // }
        // else if (count == 8 && b_deinit == true)
        // {
        //     dbusStub.init();
        //     b_deinit = false;
        // }
        // else if (count == 11 && b_deinit == false)
        // {
        //     dbusStub.deinit();
        //     b_deinit = true;
        // }
        // else if (count == 14 && b_deinit == true)
        // {
        //     dbusStub.init();
        //     b_deinit = false;
        // }
        // else if (count == 17 && b_deinit == false)
        // {
        //     dbusStub.deinit();
        //     b_deinit = true;
        // }
        // else if (count == 20 && b_deinit == true)
        // {
        //     dbusStub.init();
        //     b_deinit = false;
        // }
        // else if (count == 23 && b_deinit == false)
        // {
        //     dbusStub.deinit();
        //     b_deinit = true;
        // }
        // else if (count == 27 && b_deinit == true)
        // {
        //     dbusStub.init();
        //     b_deinit = false;
        // }
        count++;
    }

    return 0;
}

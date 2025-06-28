#include <gtest/gtest.h>

#include <silk/core/signal.h>

namespace silk::test
{

    TEST(SilkCore, SignalSlot)
    {
        Signal<void()> signal{};

        bool slotATriggered{ false };
        bool slotBTriggered{ false };
        Slot<void()> slotA{ [&slotATriggered]() { slotATriggered = true; } };
        Slot<void()> slotB{ [&slotBTriggered]() { slotBTriggered = true; } };

        signal.Connect(slotA);
        signal.Connect(slotB);
        signal.Raise();
        ASSERT_TRUE(slotATriggered);
        ASSERT_TRUE(slotBTriggered);


        slotATriggered = false;
        slotBTriggered = false;
        signal.Disconnect(slotA);
        signal.Raise();
        ASSERT_FALSE(slotATriggered);
        ASSERT_TRUE(slotBTriggered);


        slotATriggered = false;
        slotBTriggered = false;
        signal.Clear();
        signal.Raise();
        ASSERT_FALSE(slotATriggered);
        ASSERT_FALSE(slotBTriggered);
    }

}

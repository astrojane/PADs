#include <chrono>
#include <gtest/gtest.h>
#include <functional>

#include "HTTPPostClientSpy.h"
#include "Postman.h"

#include "TestPin.hpp"
#include "TestTime.hpp"
#include "Switch.hpp"

#include "Cabinet.h"

using namespace ::testing;
using namespace ::std::chrono;

class HangerTests : public Test
{
public:

    std::string boxID = "114";
    std::string URL = "http://gibberish.invalid/";
    HTTPPostClientSpy client;
    Postman postie;
    Cabinet cabinet;

    HangerTests() : client(),
                     postie(URL, &client),
                     cabinet(&postie, boxID)
    {
    }

};

TEST_F(HangerTests, Cabinet_sends_event_on_hanger_down)
{

    //setDoorSwitchState(false);

    client.sendPostMsgResult = true;

    cabinet.HangerEventCallback(true);
    ASSERT_TRUE(cabinet.IsSubstringPresentInOutputString("  \"hanger_status\" : \"Down\" \n", client.lastPOSTData));
    ASSERT_EQ(URL, client.lastPOSTURL);

}

TEST_F(HangerTests, Cabinet_sends_event_on_hanger_up)
{

    //setDoorSwitchState(false);

    client.sendPostMsgResult = true;

    cabinet.HangerEventCallback(false);
    ASSERT_TRUE(cabinet.IsSubstringPresentInOutputString("  \"hanger_status\" : \"Up\" \n", client.lastPOSTData));
    ASSERT_EQ(URL, client.lastPOSTURL);

}

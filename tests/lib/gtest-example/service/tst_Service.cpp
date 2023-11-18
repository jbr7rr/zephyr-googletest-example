#include "gtest/gtest.h"

// Just some class to demonstrate a class that is being tested
class MockService {
public:
    bool subscribe(int eventType, void* listener) {
        // Mock implementation
        return true;
    }

    void unsubscribe(int eventType, void* listener) {
        // Mock implementation
    }

    void dispatch(int eventType, int data) {
        // Mock implementation
    }
};

class MockListener {
public:
    int lastDataValue = 0;

    void onDataReceived(int data) {
        lastDataValue = data;
    }
};

class ServiceTest : public ::testing::Test {
protected:
    MockService service;
    MockListener listener;
};

TEST_F(ServiceTest, Should_SubscribeListener_When_SubscribingToEventType) {
    // Arrange

    // Act
    bool subscribed = service.subscribe(1, &listener);

    // Assert
    ASSERT_TRUE(subscribed);
}

TEST_F(ServiceTest, Should_UnsubscribeListener_When_UnsubscribingFromEventType) {
    // Arrange
    service.subscribe(1, &listener);

    // Act
    service.unsubscribe(1, &listener);

    // Assert
    // Add assertions if needed
}

TEST_F(ServiceTest, Should_NotifyListener_When_DataIsDispatched) {
    // Arrange
    service.subscribe(1, &listener);
    int testData = 42;

    // Act
    service.dispatch(1, testData);

    // Assert
    ASSERT_EQ(listener.lastDataValue, 42);
}

struct SubscribeParams {
    int numListeners;
    bool shouldSucceed;
};

class ServiceParameterizedTest : public ::testing::TestWithParam<SubscribeParams> {
protected:
    MockService service;
};

INSTANTIATE_TEST_SUITE_P(Default, ServiceParameterizedTest,
                         ::testing::Values(
                             SubscribeParams{1, true},
                             SubscribeParams{5, true},
                             SubscribeParams{10, true}, // Assuming 10 is MAX_LISTENERS
                             SubscribeParams{11, false} // More than MAX_LISTENERS, should fail
                         ));

TEST_P(ServiceParameterizedTest, Should_SubscribeCorrectly_BasedOnNumberOfListeners) {
    // Arrange
    SubscribeParams params = GetParam();
    MockListener extraListeners[11]; // Ensure enough listeners for the test

    // Act
    bool result = true;
    for (int i = 0; i < params.numListeners; ++i) {
        if (!service.subscribe(1, &extraListeners[i])) {
            result = false;
            break;
        }
    }

    // Assert
    ASSERT_EQ(result, params.shouldSucceed);
}

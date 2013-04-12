#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <IOKit/hidsystem/IOHIDLib.h>
#include <IOKit/hidsystem/IOHIDParameter.h>
#include <IOKit/hidsystem/event_status_driver.h>

int main(int argc, char *argv[]) {
    CFStringRef device;
    const int32_t accel_amount = INT32_MIN;
    io_connect_t handle;
    kern_return_t set_accel;

    device = CFSTR(kIOHIDMouseAccelerationType);
    if (argc > 1 && (!(strncmp(argv[1], "-t", 3))))
        device = CFSTR(kIOHIDTrackpadAccelerationType);

    handle = NXOpenEventStatus();
    assert(handle);

    set_accel = IOHIDSetParameter(
        handle,
        device,
        &accel_amount,
        sizeof(accel_amount)
    );
    assert(set_accel == KERN_SUCCESS);

    NXCloseEventStatus(handle);
    return EXIT_SUCCESS;
}

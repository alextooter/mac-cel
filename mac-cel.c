#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <IOKit/hidsystem/IOHIDLib.h>
#include <IOKit/hidsystem/IOHIDParameter.h>
#include <IOKit/hidsystem/event_status_driver.h>

int main(int argc, char *argv[]) {
    io_connect_t hnd;
    const int32_t accel = INT32_MIN;
    CFStringRef type;

    if (argc > 1 && (!(strncmp(argv[1], "-t", 3))))
        type = CFSTR(kIOHIDTrackpadAccelerationType);
    else
        type = CFSTR(kIOHIDMouseAccelerationType);

    hnd = NXOpenEventStatus();
    if (!hnd) {
        fputs("Couldn't acquire hnd.\n", stderr);
        return EXIT_FAILURE;
    }
    if (IOHIDSetParameter(hnd, type, &accel, sizeof(accel)) != KERN_SUCCESS) {
        NXCloseEventStatus(hnd);
        fputs("Failed to set HID parameters.\n", stderr);
        return EXIT_FAILURE;
    }
    NXCloseEventStatus(hnd);
    return EXIT_SUCCESS;
}

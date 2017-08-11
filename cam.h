#ifndef __CAM_HEADER_GUARD
#define __CAM_HEADER_GUARD

#include <stdbool.h>
#include <gphoto2/gphoto2-camera.h>

typedef struct _cam {
    GPContext *context;
    struct _Camera *camera;
    int error;
} cam;

typedef CameraFile camFile;
typedef CameraFilePath camFilePath;

bool camAlloc(cam *);
void camFree(cam *);
cam *camCreate();
void camDestroy(cam *);
bool camIsConnected(cam *);
bool camConnect(cam *);
const char *camError(cam *);
bool camCapture(cam *, camFilePath*);
bool camGetFile(cam *, const char *, camFilePath, bool);

#endif // __CAM_HEADER_GUARD

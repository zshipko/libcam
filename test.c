#include "camera.h"

#include <stdio.h>

int main(int argc, char **argv){
    cam *ctx = camCreate();
    if (!camConnect(ctx)){
        printf("Unable to connect to camera: %s\n", camError(ctx));
        return 1;
    }

    camFilePath path;

    if (!camCapture(ctx, &path)){
        printf("Unable to capture image: %s\n", camError(ctx));
        return 2;
    }

    if (!camGetFile(ctx, "test.cr2", path, true)){
        printf("Unable to  get file: %s\n", camError(ctx));
        return 2;
    }

    camDestroy(ctx);
    return 0;
}

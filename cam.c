#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "camera.h"

static inline bool _check(cam *ctx, int res){
    ctx->error = res;
    return ctx->error == 0;
}

bool camAlloc(cam *ctx){
    ctx->context = gp_context_new();
    ctx->camera = NULL;
    ctx->error = 0;
    return ctx->context != NULL;
}

void camFree(cam *ctx){
    gp_context_unref(ctx->context);

    if (ctx->camera){
        gp_camera_unref(ctx->camera);
    }
}

cam *camCreate(){
    cam *c = malloc(sizeof(cam));
    if (!c){
        return NULL;
    }

    if (!camAlloc(c)){
        free(c);
        return NULL;
    }

    return c;
}

void camDestroy(cam *ctx){
    camFree(ctx);
    free(ctx);
}

bool camIsConnected(cam *ctx){
    return ctx->camera != NULL;
}

bool camConnect(cam *ctx){
    if (!_check(ctx, gp_camera_new(&ctx->camera))){
        return false;
    }

    return _check(ctx, gp_camera_init(ctx->camera, ctx->context));
}

const char *camError(cam *ctx){
    if (ctx->error == 0){
        return NULL;
    }

    return gp_result_as_string(ctx->error);
}

bool camCapture(cam *ctx, camFilePath *p){
    return _check(ctx, gp_camera_capture(ctx->camera, GP_CAPTURE_IMAGE, p, ctx->context));
}

bool camGetFile(cam *ctx, const char *dst, camFilePath p, bool delete){
    int fd = open(dst ? dst : p.name, O_CREAT | O_WRONLY, 0644);
    if (fd < 0){
        ctx->error = GP_ERROR;
        return false;
    }

    CameraFile *file;
    gp_file_new_from_fd(&file, fd);
    if (!_check(ctx, gp_camera_file_get(ctx->camera, p.folder, p.name, GP_FILE_TYPE_NORMAL, file, ctx->context))){
        goto error;
    }

    if (delete){
        gp_camera_file_delete(ctx->camera, p.folder, p.name, ctx->context);
    }

    gp_file_free(file);

    return true;

error:
    gp_file_free(file);
    return false;
}


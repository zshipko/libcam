CFLAGS+= -I/usr/local/include
LDFLAGS+= -L/usr/local/lib -lgphoto2

lib:
	$(CC) -fPIC -shared -o libcam.so cam.c $(CFLAGS) $(LDFLAGS)

build:
	$(CC) -fPIC -o test cam.c test.c $(CFLAGS) $(LDFLAGS)

/* awake.c — aviso UNA vez + mantener la consola despierta.
 * Notificación: "2026 awake by Franchi"
 * Sin dependencias extra: el keep-awake se pide en runtime con dlopen,
 * así el payload carga con las mismas libs que los que sí funcionan.
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>

/* libkernel_web (enlazada por defecto) */
typedef struct {
  char useless1[45];
  char message[3075];
} notify_request_t;
extern int sceKernelSendNotificationRequest(int, notify_request_t *, size_t, int);

static void notify(const char *msg) {
  notify_request_t req;
  memset(&req, 0, sizeof req);
  snprintf(req.message, sizeof req.message, "%s", msg);
  int rc = sceKernelSendNotificationRequest(0, &req, sizeof req, 0);
  printf("awake: notify(\"%s\") rc=%d\n", msg, rc);
  fflush(stdout);
}

int main(void) {
  printf("awake: START\n");
  fflush(stdout);

  notify("2026 awake by Franchi");          /* una sola vez */

  /* Keep-awake: sceSystemServicePowerTick, resuelto en runtime. */
  int (*tick)(void) = 0;
  void *h = dlopen("libSceSystemService.sprx", RTLD_LAZY);
  if (h) tick = (int (*)(void))dlsym(h, "sceSystemServicePowerTick");
  printf("awake: powertick=%p\n", (void *)tick);
  fflush(stdout);

  for (unsigned i = 0;; i++) {
    if (tick) tick();                        /* reinicia el temporizador de reposo */
    sleep(15);
  }
  return 0;
}

#include <uuid/uuid.h>
#include <time.h>

/**
 * Generates a UUID.
 * Source: https://stackoverflow.com/a/51068240.
 * @return A UUID.
 */
char *genUUID() {
    uuid_t BinUUID;
    uuid_generate_random(BinUUID);
    char *UUID = malloc(37);
    uuid_unparse(BinUUID, UUID);
    return UUID;
}

time_t now = time(NULL);

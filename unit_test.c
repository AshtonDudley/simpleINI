/* Example: parse a simple configuration file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"

typedef struct
{
    int maxFrameCount;
    const char* configFilepath;
    const char* serialNumber;
} configuration;

static int handler(void* user, const char* section, const char* name,
    const char* value)
{
    configuration* pconfig = (configuration*)user;

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("camara_info", "maxFrameCount")) {
        pconfig->maxFrameCount = atoi(value);
    }
    else if (MATCH("camara_info", "configFilepath")) {
        pconfig->configFilepath = _strdup(value);
    }
    else if (MATCH("camara_info", "serialNumber")) {
        pconfig->serialNumber = _strdup(value);
    }
    else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

int main(int argc, char* argv[])
{
    configuration config;
    config.maxFrameCount = 0;  /* set defaults */
    config.configFilepath = NULL;
    config.serialNumber = NULL;

    if (ini_parse("config.ini", handler, &config) < 0) {
        printf("Can't load 'config.ini'\n");
        return 1;
    }
    printf("Config loaded from 'test.ini': \nmaxFrameCount = %d, \nconfigFilepath = %s, \nserialNumber = %s\n",
        config.maxFrameCount, config.configFilepath, config.serialNumber);

    if (config.configFilepath)
        free((void*)config.configFilepath);
    if (config.serialNumber)
        free((void*)config.serialNumber);

    return 0;
}
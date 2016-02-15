#include <stdio.h>
#include <string.h>
#include <unistd.h>
//#define VERBOSE



const char *adbversion()
{
    static char version[100];
    version[0] = '\0';
    FILE *handle = popen("adb version 2>&1", "r");

    if (handle == NULL)
    {
        return 0;
    }
    char buf[64];
    size_t readn;
    int ret = 1;
    while ((readn = fread(buf, 1, sizeof(buf), handle)) > 0)
    {
        buf[readn] = '\0';
        if ( version[0] == '\0')
        {
            strcpy(version, buf);
            if ( version[0]) version[strlen(version)-1] =  '\0';
           // printf ("%s", version);
        }
#ifdef VERBOSE
        printf("%s\n", buf);
#endif
    }
    pclose(handle);

    

    return version;
}

// 0 = no device
// 1 = device without redirection
// 2 = device with redirection
int checkconnect()
{
    FILE *handle = popen("adb reverse --list 2>&1", "r");

    if (handle == NULL)
    {
        return 0;
    }
    char buf[64];
    size_t readn;
    int ret = 1;
    while ((readn = fread(buf, 1, sizeof(buf), handle)) > 0)
    {
        buf[readn] = '\0';
        if (strstr(buf, "tcp:2222 tcp:22") != NULL)
        {
            ret = 2;
        }
        if (strstr(buf, "device not found") != NULL)
        {
            ret = 0;
        }


#ifdef VERBOSE
        printf("%s\n", buf);
#endif
    }
    pclose(handle);

    return ret;
}

// Redirect port 22 to 2222 on android
int redirect()
{
    FILE *handle = popen("adb reverse tcp:2222 tcp:22 2>&1", "r");

    if (handle == NULL)
    {
        return 0;
    }
    char buf[64];
    size_t readn;
    while ((readn = fread(buf, 1, sizeof(buf), handle)) > 0)
    {
        buf[readn] = '\0';
#ifdef VERBOSE
        printf("%s\n", buf);
#endif
    }
    pclose(handle);

    return 0;
}

int wait()
{
    FILE *handle = popen("adb wait-for-device 2>&1", "r");

    if (handle == NULL)
    {
        return 0;
    }
    char buf[64];
    size_t readn;
    int ret = 1;
    while ((readn = fread(buf, 1, sizeof(buf), handle)) > 0)
    {
        buf[readn] = '\0';

        if (strstr(buf, "not found") != NULL)
        {
            ret = 0;
        }
#ifdef VERBOSE
        printf("%s\n", buf);
#endif
    }
    pclose(handle);

    return ret;
}


int main(int narg, char *arg[])
{
    if ( narg > 1 && !strcmp(arg[1], "-v") )
    {
        printf("version 1.0\n");
        return 0;
    }
    int v2 = -1;

    const char *ver = adbversion();
    if ( strstr(ver,"1.0.32")  == NULL ) {
        printf("adb wrong version (%s)\n",ver);
        return -1;
    }

    while(true)
    {

        int v = 0;

        while ( v != 2 )
        {
            v = checkconnect();
            switch (v)
            {
            case 0:
                if ( v2 != v ) printf("no device\n");
                wait();
                break;
            case 1:
                if ( v2 != v ) printf("device without redirection\n");
                redirect();
                break;
            case 2:
                if ( v2 != v ) printf("device with redirection\n");
                break;

            }
            v2 = v;
        }
        sleep(10);
    }
    return 0;
}

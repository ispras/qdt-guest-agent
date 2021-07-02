#include <stdio.h>
#include <string.h>
#include <libserialport.h>
#include <vector>

#define _STR(X) #X
#define STR(X) _STR(X)

using namespace std;

struct QDTAgentServer {
    struct sp_port *port;

    QDTAgentServer(struct sp_port *port): port(port) {};

    void main(void);
    void start(void);
};


void QDTAgentServer::start(void)
{

}

int check(enum sp_return result);

#define QDT_AGENT_VERSION 1
#define QDT_AGENT_HELLO ("QDTAgent" STR(QDT_AGENT_VERSION) "\r\n")

static inline enum sp_return sp_nonblocking_write_str(struct sp_port *port,
                                                      const char *str)
{
    return sp_nonblocking_write(port, str, strlen(str));
}

int main(int argc, char **argv)
{
    struct sp_port **port_list;

    printf("Getting port list.\n");

    enum sp_return result = sp_list_ports(&port_list);

    if (check(result)) {
        printf("sp_list_ports() failed!\n");
        return -1;
    }

    int i;
    vector<sp_port*> usable_ports;

    for (i = 0; port_list[i] != NULL; i++) {
        struct sp_port *port = port_list[i];

        char *port_name = sp_get_port_name(port);

        printf("Found port: %s\n", port_name);

        result = sp_open(port, SP_MODE_READ_WRITE);

        if (check(result)) {
            printf("Can't open the port\n");
            continue;
        }

        /* Under Qemu parameters are not very meaningful. But the configuration
         * itself must be done. Else, output can be lost. */
        if (   check(sp_set_baudrate(port, 9600))
            || check(sp_set_bits(port, 8))
            || check(sp_set_parity(port, SP_PARITY_NONE))
            || check(sp_set_stopbits(port, 1))
            || check(sp_set_flowcontrol(port, SP_FLOWCONTROL_NONE))) {

            printf("Can't configure the port\n");

            sp_close(port); /* ignore result, it's already failed */
            continue;
        }

        result = sp_nonblocking_write_str(port, QDT_AGENT_HELLO);

        if (check(result)) {
            printf("Can't write hello to the port\n");

            sp_close(port); /* ignore result, it's already failed */
            continue;
        } else {
            printf("Hello is sent\n");
        }

        usable_ports.push_back(port);
    }

    if (usable_ports.empty()) {
        printf("No usable ports found\n");
    } else {
        /* TODO */
    }

    sp_free_port_list(port_list);

    return 0;
}

/* Helper function for error handling. */
int check(enum sp_return result)
{
    /* For this example we'll just exit on any error by calling abort(). */
    char *error_message;

    switch (result) {
    case SP_ERR_ARG:
        printf("Error: Invalid argument.\n");
        return 1;
    case SP_ERR_FAIL:
        error_message = sp_last_error_message();
        printf("Error: Failed: %s\n", error_message);
        sp_free_error_message(error_message);
        return 1;
    case SP_ERR_SUPP:
        printf("Error: Not supported.\n");
        return 1;
    case SP_ERR_MEM:
        printf("Error: Couldn't allocate memory.\n");
        return 1;
    case SP_OK:
    default:
        return 0;
    }
}

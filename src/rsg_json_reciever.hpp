/*
 * rsg_json_reciever microblx function block (autogenerated, don't edit)
 */

#include <ubx.h>

/* includes types and type metadata */

ubx_type_t types[] = {
        { NULL },
};

/* block meta information */
char rsg_json_reciever_meta[] =
        " { doc='A block that recieves and decodes JSON based updates for the Robot Scene Graph',"
        "   real-time=false,"
        "}";

/* declaration of block configuration */
ubx_config_t rsg_json_reciever_config[] = {
        { .name="wm_handle", .type_name = "struct rsg_wm_handle", .doc="Handle to the world wodel instance. This parameter is mandatory." },
    	{ .name="buffer_len", .type_name = "uint32_t", .doc="Maximum number of data elements the of the input buffer." },
        { .name="log_level", .type_name = "int", .doc="Set the log level: LOGDEBUG = 0, INFO = 1, WARNING = 2, LOGERROR = 3, FATAL = 4" },
        { .name="enable_input_filter", .type_name = "int", .doc="If true every deserialized message gets filtered and potentially rejected. Default is false." },
        { .name="input_filter_pattern", .type_name = "char" , .doc="Pattern to exclude name spaces." },
        { NULL },
};

/* declaration port block ports */
ubx_port_t rsg_json_reciever_ports[] = {
        { .name="rsg_in", .in_type_name="unsigned char", .doc="JSON based byte stream for updates on RSG based world model."  },
        { NULL },
};

/* declare a struct port_cache */
struct rsg_json_reciever_port_cache {
        ubx_port_t* rsg_in;
};

/* declare a helper function to update the port cache this is necessary
 * because the port ptrs can change if ports are dynamically added or
 * removed. This function should hence be called after all
 * initialization is done, i.e. typically in 'start'
 */
static void update_port_cache(ubx_block_t *b, struct rsg_json_reciever_port_cache *pc)
{
        pc->rsg_in = ubx_port_get(b, "rsg_in");
}


/* for each port type, declare convenience functions to read/write from ports */
//def_read_fun(read_rsg_in, unsigned char)

/* block operation forward declarations */
int rsg_json_reciever_init(ubx_block_t *b);
int rsg_json_reciever_start(ubx_block_t *b);
void rsg_json_reciever_stop(ubx_block_t *b);
void rsg_json_reciever_cleanup(ubx_block_t *b);
void rsg_json_reciever_step(ubx_block_t *b);


/* put everything together */
ubx_block_t rsg_json_reciever_block = {
        .name = "rsg_json_reciever",
        .type = BLOCK_TYPE_COMPUTATION,
        .meta_data = rsg_json_reciever_meta,
        .configs = rsg_json_reciever_config,
        .ports = rsg_json_reciever_ports,

        /* ops */
        .init = rsg_json_reciever_init,
        .start = rsg_json_reciever_start,
        .stop = rsg_json_reciever_stop,
        .cleanup = rsg_json_reciever_cleanup,
        .step = rsg_json_reciever_step,
};


/* rsg_json_reciever module init and cleanup functions */
int rsg_json_reciever_mod_init(ubx_node_info_t* ni)
{
        DBG(" ");
        int ret = -1;
        ubx_type_t *tptr;

        for(tptr=types; tptr->name!=NULL; tptr++) {
                if(ubx_type_register(ni, tptr) != 0) {
                        goto out;
                }
        }

        if(ubx_block_register(ni, &rsg_json_reciever_block) != 0)
                goto out;

        ret=0;
out:
        return ret;
}

void rsg_json_reciever_mod_cleanup(ubx_node_info_t *ni)
{
        DBG(" ");
        const ubx_type_t *tptr;

        for(tptr=types; tptr->name!=NULL; tptr++)
                ubx_type_unregister(ni, tptr->name);

        ubx_block_unregister(ni, "rsg_json_reciever");
}

/* declare module init and cleanup functions, so that the ubx core can
 * find these when the module is loaded/unloaded */
UBX_MODULE_INIT(rsg_json_reciever_mod_init)
UBX_MODULE_CLEANUP(rsg_json_reciever_mod_cleanup)

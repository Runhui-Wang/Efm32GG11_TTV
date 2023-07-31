#include "sl_cli.h"
#include "sl_cli_instances.h"
#include "sl_cli_arguments.h"
#include "sl_cli_handles.h"
void cli_app_init();
void set_time (sl_cli_command_arg_t *arguments);
void uart_init();
void spi_init();
extern uint64_t time_offset;

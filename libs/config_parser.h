#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#define MAX_LINE_LENGTH 100
#define MAX_KEY_LENGTH 50
#define MAX_VALUE_LENGTH 50

#define CONFIG_FILE "/etc/hamlinkd.conf"

typedef struct {
    // AX.25
    char ax25_ip[16];
    char ax25_netmask[16];
    char ax25_callsign[10];
    unsigned int ax25_baudrate;
    unsigned short ax25_enable_fx25;
    unsigned short ax25_ptt_gpio;
    unsigned short ax25_ptt_inverted;

    // Gateway
    unsigned short gateway_enable;

    // Ethernet Gateway
    unsigned short eth_gateway_enable;
    char eth_gateway_ip[16];
    char eth_gateway_netmask[16];

    // WiFi Gateway
    unsigned short wifi_gateway_enable;
    char wifi_gateway_ssid[32];
    char wifi_gateway_psk[64];
    unsigned short wifi_gateway_channel;

    // Gateway DHCP
    unsigned short gateway_dhcp_enable;
    char gateway_dhcp_start[16];
    char gateway_dhcp_end[16];

    // Audio Device
    char audio_device[32];
} hamlinkd_config;

/**
 * \brief Parse the configuration file and store the values in the config struct
 * 
 * \param config 
 */
void hamlinkd_parse_config(hamlinkd_config* config);

/**
 * \brief Print the configuration to stdout
 * 
 * \param config 
 */
void hamlinkd_print_config(hamlinkd_config* config);

/**
 * \brief Save the configuration to the configuration file
 * 
 * \param config 
 */
void hamlinkd_save_config(hamlinkd_config* config);

#endif
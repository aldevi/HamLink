#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HamLinkStart.h"
#include "../libs/config_parser.h"

/**
 * \brief Configure the Direwolf AX.25 modem
 *
 * \param config
 */
void hamlinkd_configure_direwolf(hamlinkd_config* config) {
    // Create the configuration file
    FILE* fp = fopen(DIREWOLF_CONFIG_FILE, "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    // Write the configuration
    fprintf(fp, "ADEVICE %s\n", config->audio_device);
    fprintf(fp, "CHANNEL 0\n");
    fprintf(fp, "MYCALL %s\n", config->ax25_callsign);
    fprintf(fp, "MODEM %d\n", config->ax25_baudrate);
    fprintf(fp, "PTT GPIO -%d\n", config->ax25_ptt_gpio);

    // Close the file
    fclose(fp);
}

/**
 * \brief Start the Direwolf AX.25 modem
 * 
 * \param config
 */
void hamlinkd_start_direwolf(hamlinkd_config* config) {
    // Restart the Direwolf AX.25 modem
    system("systemctl start direwolf");
}

/**
 * \brief Stop the Direwolf AX.25 modem
 * 
 * \param config
 */
void hamlinkd_stop_direwolf(hamlinkd_config* config) {
    // Stop the Direwolf AX.25 modem
    system("systemctl stop direwolf");
}

/**
 * \brief Configure the AX.25 port
 * 
 * \param config
 */
void hamlinkd_configure_ax25(hamlinkd_config* config) {
    // Create the configuration file
    FILE* fp = fopen(AX25_CONFIG_FILE, "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    // Write the configuration
    fprintf(fp, "1\t%s\t%d\t225\t2\tPacket IP Link\n", config->ax25_callsign, config->ax25_baudrate);

    // Close the file
    fclose(fp);
}

/**
 * \brief Bind the AX.25 port with the TNC
 * 
 * \param config
 */
void hamlinkd_bind_ax25(hamlinkd_config* config) {
    // Binding with the /sbin/kissattach command
    char command[256];
    sprintf(command, "/sbin/kissattach %s 1 %s", KISS_TNC_TERMINAL, config->ax25_ip);
    system(command);

    // Configuring the AX.25 port to not append the CRC (handled by the TNC)
    sprintf(command, "kissparms -c 1 -p 1");
    system(command);
}

/**
 * \brief Configure the WiFi gateway
 * 
 * \param config
 */
void hamlinkd_configure_wifi_gateway(hamlinkd_config* config) {
    // Configuring the WiFi interface with the IP command
    char command[256];
    sprintf(command, "ip addr add %s netmask %s dev wlan0", config->eth_gateway_ip, config->eth_gateway_netmask);
    system(command);

    // Enabling the WiFi interface with the IP command
    sprintf(command, "ip link set wlan0 up");
    system(command);
}

/**
 * \brief Configure the dnsmasq DHCP server
 * 
 * \param config
 */
void hamlinkd_configure_dnsmasq(hamlinkd_config* config) {
    // Create the configuration file
    FILE* fp = fopen(DNSMASQ_CONFIG_FILE, "w");
    if (fp == NULL) {
        printf("Error opening file");
    }

    // Write the configuration
    fprintf(fp, "interface=wlan0\n");
    fprintf(fp, "dhcp-range=%s,%s,12h\n", config->gateway_dhcp_start, config->gateway_dhcp_end);
    fprintf(fp, "listen-address=%s\n", config->eth_gateway_ip);
    fprintf(fp, "server=8.8.8.8\n");
    fprintf(fp, "bind-interfaces\n");
    fprintf(fp, "domain-needed\n");
    fprintf(fp, "bogus-priv\n");
}

/**
 * \brief Start the dnsmasq DHCP server
 * 
 * \param config
 */
void hamlinkd_start_dnsmasq(hamlinkd_config* config) {
    // Restart the dnsmasq DHCP server
    system("systemctl restart dnsmasq");
}

/**
 * \brief Configure the hostapd WiFi access point
 * 
 * \param config
 */
void hamlinkd_configure_hostapd(hamlinkd_config* config) {
    // Create the configuration file
    FILE* fp = fopen(HOSTAPD_CONFIG_FILE, "w");
    if (fp == NULL) {
        printf("Error opening file");
    }

    // Write the configuration
    fprintf(fp, "interface=wlan0\n");
    fprintf(fp, "driver=nl80211\n");
    fprintf(fp, "ssid=%s\n", config->wifi_gateway_ssid);
    fprintf(fp, "hw_mode=g\n");
    fprintf(fp, "channel=%d\n", config->wifi_gateway_channel);
    fprintf(fp, "ieee80211n=1\n");
    fprintf(fp, "wmm_enabled=1\n");
    fprintf(fp, "ht_capab=[HT40][SHORT-GI-20][DSSS_CCK-40]\n");
    fprintf(fp, "macaddr_acl=0\n");
    fprintf(fp, "auth_algs=1\n");
    fprintf(fp, "ignore_broadcast_ssid=0\n");
    fprintf(fp, "wpa=2\n");
    fprintf(fp, "wpa_passphrase=%s\n", config->wifi_gateway_psk);
    fprintf(fp, "wpa_key_mgmt=WPA-PSK\n");
    fprintf(fp, "wpa_pairwise=CCMP\n");
}

/**
 * \brief Start the hostapd WiFi access point
 * 
 * \param config
 */
void hamlinkd_start_hostapd(hamlinkd_config* config) {
    // Restart the hostapd WiFi access point
    system("systemctl restart hostapd");
}

int main() {
    // Parse the configuration file
    hamlinkd_config config;
    hamlinkd_parse_config(&config);

    // Stop the Direwolf AX.25 modem
    hamlinkd_stop_direwolf(&config);

    // Configure the Direwolf AX.25 modem
    hamlinkd_configure_direwolf(&config);

    // Start the Direwolf AX.25 modem
    hamlinkd_start_direwolf(&config);

    // Wait for the Direwolf AX.25 modem to start
    sleep(1);

    // Configure the AX.25 port
    hamlinkd_configure_ax25(&config);

    // Bind the AX.25 port with the TNC
    hamlinkd_bind_ax25(&config);

    // Configure the WiFi gateway
    // hamlinkd_configure_wifi_gateway(&config);

    // // Configure the dnsmasq DHCP server
    // hamlinkd_configure_dnsmasq(&config);

    // // Start the dnsmasq DHCP server
    // hamlinkd_start_dnsmasq(&config);

    // // Configure the hostapd WiFi access point
    // hamlinkd_configure_hostapd(&config);

    // // Start the hostapd WiFi access point
    // hamlinkd_start_hostapd(&config);

    return 0;
}
/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   FreeRTOS V9.0.0 + STM32 LwIP
  *********************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32ȫϵ�п����� 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */ 
 
/*
*************************************************************************
*                             ������ͷ�ļ�
*************************************************************************
*/ 
#include "main.h"

#include <lwip/opt.h>
#include <lwip/arch.h>
#include "tcpip.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "ethernetif.h"
#include "netif/ethernet.h"
#include "lwip/def.h"
#include "lwip/stats.h"
#include "lwip/etharp.h"
#include "lwip/ip.h"
#include "lwip/snmp.h"
#include "lwip/timeouts.h"
#include "lwip/dhcp.h"
#include "tcpclient.h"

struct netif gnetif;
ip4_addr_t ipaddr;
ip4_addr_t netmask;
ip4_addr_t gw;
uint8_t IP_ADDRESS[4];
uint8_t NETMASK_ADDRESS[4];
uint8_t GATEWAY_ADDRESS[4];

void LwIP_Init(void)
{
  /* IP addresses initialization */

  IP4_ADDR(&ipaddr,IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3);
  IP4_ADDR(&netmask,NETMASK_ADDR0,NETMASK_ADDR1,NETMASK_ADDR2,NETMASK_ADDR3);
  IP4_ADDR(&gw,GW_ADDR0,GW_ADDR1,GW_ADDR2,GW_ADDR3);
  
  /* USER CODE END 0 */
    
  /* Initilialize the LwIP stack without RTOS */
  lwip_init();
  
  /* add the network interface (IPv4/IPv6) without RTOS */
  netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);

  /* Registers the default network interface */
  netif_set_default(&gnetif);

  if (netif_is_link_up(&gnetif))
  {
    /* When the netif is fully configured this function must be called */
    netif_set_up(&gnetif);
  }
  else
  {
    /* When the netif link is down this function must be called */
    netif_set_down(&gnetif);
  }
  printf("����IP��ַ��:%ld.%ld.%ld.%ld\n\n",  \
        ((gnetif.ip_addr.addr)&0x000000ff),       \
        (((gnetif.ip_addr.addr)&0x0000ff00)>>8),  \
        (((gnetif.ip_addr.addr)&0x00ff0000)>>16), \
        ((gnetif.ip_addr.addr)&0xff000000)>>24);

}



int flag = 0;
int main(void)
{
  //�弶�����ʼ��
  BSP_Init();
  
  printf("��������ʾ�����巢�����ݵ�������\n\n");
  
  printf("��������ģ�����£�\n\t ����<--����-->·��<--����-->������\n\n");
  
  printf("ʵ����ʹ��TCPЭ�鴫�����ݣ�������ΪTCP Server����������ΪTCP Client\n\n");
  
  printf("�����̵�IP��ַ����main.h�ļ����޸�\n\n");
    
  printf("�����̲ο�<<LwIPӦ��ʵս����ָ��>>��17�� ʹ�� RAW API �ӿڱ��\n\n");
  
  printf("Ŀ��IP��ַ:%d.%d.%d.%d \t �˿ں�:%d\n\n",      \
          DEST_IP_ADDR0,DEST_IP_ADDR1,DEST_IP_ADDR2,DEST_IP_ADDR3,DEST_PORT);
  
  printf("�뽫������λ������ΪTCP Server.��main.h�ļ��н�Ŀ��IP��ַ�޸�Ϊ�������ϵ�IP��ַ\n\n");
  
  printf("�޸Ķ�Ӧ�ĺ궨��:DEST_IP_ADDR0,DEST_IP_ADDR1,DEST_IP_ADDR2,DEST_IP_ADDR3,DEST_PORT\n\n");
  
  //LwIPЭ��ջ��ʼ��
  LwIP_Init();  
  TCP_Client_Init();
  while (1)
  {
    if(flag)
    {
      flag = 0;
      //�����������պ���
      ethernetif_input(&gnetif);
    }
    //����LwIP�ж�ʱ�¼�
    sys_check_timeouts();
  }
}



/********************************END OF FILE****************************/

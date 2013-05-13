/**
 ******************************************************************************
 * @file       config.h
 * @brief      配置文件
 * @details    This file including all API functions's declare of config.h.
 * @copyright  Copyrigth(C), 2008-2012,Sanxing Electric Co.,Ltd.
 *
 ******************************************************************************
 */
#ifndef CONFIG_H_
#define CONFIG_H_ 

/*-----------------------------------------------------------------------------
 Section: Macro Definitions
 ----------------------------------------------------------------------------*/
#define DEFAULT_INI_FILE        "./MStationCfg.ini"     /**< 默认配置文件 */
#define DEFAULT_LOG_FILE_NAME   "./MStationServer.txt"  /**< 默认日志文件 */
#define DEFAULT_SOCKET_IP       "10.2.236.60"           /**< 默认tcp服务器 */
#define DEFAULT_SOCKET_PORT     (2083)                  /**< 默认tcp端口 */
#define DEFAULT_SOCKET_MAX      (100)                   /**< 默认最大连接数量 */
#define DEFAULT_SOCKET_TIMEOUT  (15u)                   /**< 默认超时时间 */
#define DEFAULT_LOG_ON          (1u)                    /**< 默认打开日志记录 */

#endif /* CONFIG_H_ */
/*-----------------------------End of config.h-------------------------------*/
